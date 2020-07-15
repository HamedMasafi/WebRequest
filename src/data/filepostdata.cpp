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

#include "filepostdata.h"

#include <QHttpPart>
#include <QFile>
#include <QDebug>
#include <QNetworkRequest>
#include <QFileInfo>

#include "../webrequestmanager.h"
#include "../webrequest_p.h"

KAJ_REST_BEGIN_NAMESPACE

FilePostData::FilePostData(WebRequest *parent) : FormPostData(parent)
{

}

Rest::Files FilePostData::files() const
{
    return m_files;
}

void FilePostData::setFiles(Rest::Files files)
{
    if (m_files == files)
        return;

    m_files = files;
    emit filesChanged(m_files);
}

QNetworkReply *FilePostData::send(QNetworkRequest &request)
{
    if (!m_files.count())
        return FormPostData::send(request);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMap<QString, QString>::iterator i;
    for (i = m_files.begin(); i != m_files.end(); ++i) {
        QHttpPart filePart;
        QFile *f = new QFile(i.value(), multiPart);
        if (!f->exists()) {
            qWarning() << "The file" << i.value() << "does not exists";
            return nullptr;
        }

        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        QFileInfo fi(i.value());
        QString t = QString("form-data; name=\"%1\"; filename=\"%2\"")
                .arg(i.key()).arg(fi.fileName());
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
        f->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(f);
        multiPart->append(filePart);
    }
    QMap<QString, QVariant>::iterator data_it;
    auto dt = data();
    for (data_it = dt.begin(); data_it != dt.end(); ++data_it) {
        QHttpPart textPart;

        //            filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        QString t = QString("form-data; name=\"%1\"")
                .arg(data_it.key());
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
        textPart.setBody(data_it.value().toString().toLocal8Bit());
        multiPart->append(textPart);
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return d()->m_manager->request(request, multiPart);
}

QString FilePostData::generateCacheKey()
{
    if (!m_files.count())
        return FormPostData::generateCacheKey();

    QString key;
    for (auto i = m_files.begin(); i != m_files.end(); ++i) {
        key.append(i.key() + "&" + i.value() + ";;");
    }
    auto dt = data();
    for (auto data_it = dt.begin(); data_it != dt.end(); ++data_it) {
        key.append(data_it.key() + "&" + data_it.value().toString() + ";;");
    }

    return key;
}

void FilePostData::addFile(const QString &name, const QUrl &file)
{
    m_files.insert(name, file.toLocalFile());
}

void FilePostData::addFile(const QString &name, const QString &path)
{
    m_files.insert(name, path);
}

KAJ_REST_END_NAMESPACE
