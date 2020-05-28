/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "imagerequest.h"
#include "webrequestcache.h"
#include "webrequest_p.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>

#include <QNetworkRequest>

ImageRequest::ImageRequest(QObject *parent) : WebRequest(parent)
{
    setUseUtf8(false);
}

QUrl ImageRequest::fileName() const
{
    return m_fileName;
}

void ImageRequest::setFileName(QUrl fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

void ImageRequest::processResponse(QByteArray buffer)
{
    Q_UNUSED(buffer);
    QUrl fn = fileName();
    if (fn.isValid())
        emit finished(QImage(fn.toLocalFile()));
    else
        emit replyError(-1, "Image is null");
}

//void ImageRequest::storeInCache(QDateTime expire, QByteArray buffer)
//{
//    QString cid = actualCacheId();
//    if (cid.isEmpty())
//        cid = url().toString().replace("'", "");
//    QString fn = cacheManager()->setValue(cid, buffer, expire);
//    setFileName(QUrl::fromLocalFile(fn));
//}

bool ImageRequest::retriveFromCache(const QString &key)
{
    QString fn = cacheManager()->fileName(key);
    if (fn != QString()) {
        setFileName(QUrl::fromLocalFile(fn));
        processResponse(QByteArray());
        return true;
    }
    return false;
}

void ImageRequest::beforeSend(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "");
}
