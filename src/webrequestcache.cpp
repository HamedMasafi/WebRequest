/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kaj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "webrequestcache.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QVariant>
#ifdef QT_SQL_LIB
#   include <QtCore/QCoreApplication>
#   include <QtSql/QSqlQuery>
#   include <QtSql/QSqlError>
#   include <QtCore/QStandardPaths>
#endif

#define FILE_PERFIX "file-"

KAJ_REST_BEGIN_NAMESPACE


WebRequestCache::WebRequestCache(const QString &name) : QObject(), _fileName(name)
{
    init();
}

void WebRequestCache::setFileName(const QString &newFileName)
{
    _fileName = newFileName;
    init();
}

const QString &WebRequestCache::path() const
{
    return _path;
}

void WebRequestCache::setPath(const QString &newPath)
{
    _path = newPath;
    init();
}

bool WebRequestCache::contains(const QString &key) const
{
#ifdef QT_SQL_LIB
    QSqlQuery q(db);
    q.prepare("SELECT COUNT(*) FROM data WHERE cache_key=:cache_key");
    q.bindValue(":cache_key", key);
    q.exec();
    if (!q.first())
        return false;

    int n = q.value(0).toInt();
    return n;
#else
    return cache.contains(key);
#endif
}

int WebRequestCache::findId(const QString &key) const
{
#ifdef QT_SQL_LIB
    QSqlQuery q(db);
    q.prepare("SELECT id FROM data WHERE cache_key=:cache_key");
    q.bindValue(":cache_key", key);
    q.exec();
    if (!q.first())
        return 0;

    return q.value(0).toInt();
#else
    return 0;
#endif
}

int WebRequestCache::clean()
{
#ifdef QT_SQL_LIB
    QSqlQuery q(db);
    q.prepare("SELECT id FROM data WHERE has_file = 1 AND expire<:expire");
    q.bindValue(":expire", QDateTime::currentDateTime());
    q.exec();

    while (q.next()) {
        bool ok;
        int id = q.value(0).toInt(&ok);
        if (!ok)
            continue;
        ok = QFile::remove(generateFileName(id));
        if (!ok)
            qWarning("Unable to remove file %s", qPrintable(generateFileName(id)));
    }

    q.prepare("DELETE FROM data WHERE AND expire<:expire");
    q.bindValue(":expire", QDateTime::currentDateTime());
    q.exec();

    if (q.numRowsAffected() > 0)
        qDebug() << q.numRowsAffected() << "expired entries was deleted";

    return q.numRowsAffected();
#else
    return 0;
#endif
}

void WebRequestCache::clear()
{
#ifdef QT_SQL_LIB
    db.exec("DELETE FROM data");

    QStringList files = QDir(_path).entryList(QStringList() << FILE_PERFIX "*");
    foreach (QString f, files)
        QFile::remove(f);
#endif
}

bool WebRequestCache::databaseEnabled() const
{
#ifdef QT_SQL_LIB
    return true;
#else
    return false;
#endif
}

QString WebRequestCache::generateFileName(const int &id) const
{
    return _path + "/" FILE_PERFIX + QString::number(id);
}

void WebRequestCache::scheduleCleaninng()
{
    startTimer(1000);
}

WebRequestCache *WebRequestCache::instance()
{
    static WebRequestCache *ins = new WebRequestCache;
    ins->scheduleCleaninng();
    return ins;
}

QString WebRequestCache::value(const QString &key) const
{
#ifdef QT_SQL_LIB
    QSqlQuery q = db.exec(QString("SELECT id, value, expire FROM data WHERE cache_key='%1'").arg(key));
    printError();
    if (!q.first())
        return QString();

    QDateTime expire =  QDateTime::fromString(q.value("expire").toString());

    if (expire < QDateTime::currentDateTime()) {
        QSqlQuery qdelete(db);
        qdelete.prepare("DELETE FROM data WHERE id=:id");
        qdelete.bindValue(":id", q.value("id"));
        qdelete.exec();
        qDebug() << "Value of" << key << "was expired";
        return QString();
    }

    return q.value("value").toString();
#else
    if (cache.contains(key))
        return *cache.object(key);
    else
        return QString();
#endif
}

QString WebRequestCache::fileName(const QString &key) const
{
#ifdef QT_SQL_LIB
    QSqlQuery q = db.exec(QString("SELECT id, value, expire, has_file FROM data WHERE has_file=1 AND cache_key='%1'").arg(key));
    printError();
    if (!q.first())
        return QString();

    QDateTime expire =  QDateTime::fromString(q.value("expire").toString());
    QString fileName = generateFileName(q.value("id").toInt());

    if (expire < QDateTime::currentDateTime()) {
        QSqlQuery qdelete(db);
        qdelete.prepare("DELETE FROM data WHERE id=:id");
        qdelete.bindValue(":id", q.value("id"));
        qdelete.exec();
        if (q.value("has_file").toInt() == 1)
            QFile::remove(fileName);

        qDebug() << "File removed";
        return QString();
    }

    if (QFile::exists(fileName))
        return fileName;
    else
        return QString();
#else
    if (cache.contains(key))
        return *cache.object(key);
    else
        return QString();
#endif
}

QString WebRequestCache::setValue(const QString &key, const QByteArray &value, const QDateTime &expire)
{
#ifdef QT_SQL_LIB
    int id = findId(key);

    QSqlQuery q(db);
    if (id)
        q.prepare("UPDATE data SET value=:value, expire=:expire WHERE cache_key=:cache_key");
    else
        q.prepare("INSERT INTO data (cache_key, value, expire, has_file) "
                  "VALUES (:cache_key, :value, :expire, 1)");

    q.bindValue(":cache_key", key);
    q.bindValue(":value", QVariant(QVariant::String));
//    q.bindValue(":file_size", value.size());
    q.bindValue(":expire", expire.toString());
    q.exec();

    if (!id && q.lastInsertId().isNull()) {
        printError();
        return QString();
    }

    if (!id)
        id = q.lastInsertId().toInt();

    QFile f(generateFileName(id));
    if (!f.open(QIODevice::WriteOnly))
        return QString();

    f.write(value);
    f.close();
    return f.fileName();
#else
    //TODO: !
    return QString();
#endif
}

bool WebRequestCache::setValue(const QString &key, const QString &value, const QDateTime &expire)
{
#ifdef QT_SQL_LIB
    bool exists = contains(key);

    QSqlQuery q(db);
    if (exists)
        q.prepare("UPDATE data SET value=:value, expire=:expire WHERE cache_key=:cache_key");
    else
        q.prepare("INSERT INTO data (cache_key, value, expire, has_file) "
                  "VALUES (:cache_key, :value, :expire, '0')");

    q.bindValue(":cache_key", key);
    q.bindValue(":value", value);
    q.bindValue(":expire", expire.toString());
    q.exec();

    printError();
    return q.numRowsAffected() > 0;;
#else
    //TODO:
//    cache.insert(key, value);
    return true;
#endif
}

bool WebRequestCache::removeValue(const QString &key)
{
#ifdef QT_SQL_LIB
    QSqlQuery q(db);
    q.prepare("DELETE FROM data WHERE cache_key=:cache_key");

    q.bindValue(":cache_key", key);
    q.exec();

    printError();
    return q.numRowsAffected() > 0;;
#else
    //TODO:
//    cache.insert(key, value);
    return true;
#endif
}

void WebRequestCache::printError() const
{
#ifdef QT_SQL_LIB
    if (db.lastError().type() != QSqlError::NoError)
        qWarning() << "Error database:" << db.lastError().text();
#endif
}

void WebRequestCache::timerEvent(QTimerEvent *)
{
    clean();
}

void WebRequestCache::init()
{
#ifdef QT_SQL_LIB
    if (db.isOpen())
        db.close();

    db = QSqlDatabase::addDatabase("QSQLITE");

    if (_path == QString())
        _path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QDir d(_path);
    if (!d.exists())
        d.mkpath(_path);

    if (_fileName == QString())
        db.setDatabaseName(_path + "/cache.dat");
    else
        db.setDatabaseName(_path + "/" + _fileName + ".dat");

    qDebug() << "WebRequestCache file is" << db.databaseName();
    bool ok = db.open();

    if (!ok) {
        qWarning() << "Unable to open database: " << db.databaseName();
        printError();
        return;
    }

    db.exec("CREATE TABLE IF NOT EXISTS data ("
            "id        INTEGER  PRIMARY KEY AUTOINCREMENT,"
            "cache_key TEXT     UNIQUE NOT NULL,"
            "value     TEXT,"
            "expire    DATETIME NOT NULL,"
            "has_file  BOOLEAN  NOT NULL DEFAULT (0)"
            ")");

    printError();
#endif
}

KAJ_REST_END_NAMESPACE
