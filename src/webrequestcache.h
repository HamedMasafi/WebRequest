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

#ifndef WEBREQUESTCACHE_H
#define WEBREQUESTCACHE_H

#include <QObject>
#include "global.h"

#ifdef QT_SQL_LIB
#   include <QtSql/QSqlDatabase>
#else
#   include <QtCore/QCache>
#endif

KAJ_REST_BEGIN_NAMESPACE

class WebRequestCache : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool databaseEnabled READ databaseEnabled NOTIFY databaseEnabledChanged)

#ifdef QT_SQL_LIB
    QSqlDatabase db;
#else
    QCache<QString, const QString> cache;
#endif
    QString path;

    bool contains(const QString &key) const;
    int findId(const QString &key) const;

    QString generateFileName(const int &id) const;

    void scheduleCleaninng();

public:
    static WebRequestCache *instance();
    WebRequestCache(const QString &name = QString());

    QString value(const QString &key) const;
    QString fileName(const QString &key) const;
    QString setValue(const QString &key, const QByteArray &value, const QDateTime &expire);
    bool setValue(const QString &key, const QString &value, const QDateTime &expire);
    bool removeValue(const QString &key);
    void printError() const;
    int clean();
    void clear();

    bool databaseEnabled() const;

signals:
    void databaseEnabledChanged(bool databaseEnabled);

protected:
    void timerEvent(QTimerEvent *);
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUESTCACHE_H
