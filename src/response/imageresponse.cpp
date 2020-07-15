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

#include "imageresponse.h"
#include "../webrequestcache.h"

#include <QDebug>

KAJ_REST_BEGIN_NAMESPACE

ImageResponse::ImageResponse(QObject *parent) : AbstractResponse(parent)
{

}

QUrl ImageResponse::fileName() const
{
    return m_fileName;
}

void ImageResponse::processReply(const QByteArray &buffer)
{
//    QString cid = d()->m_actualCacheId;
//    if (cid.isEmpty())
//        cid = url().toString().replace("'", "");
//    QString fn = d()->m_cacheManager->setValue(cid, buffer, expire);
    setFileName(QUrl::fromLocalFile(buffer));
}

bool ImageResponse::storeCacheAsFile() const
{
    return true;
}

void ImageResponse::setFileName(QUrl fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

KAJ_REST_END_NAMESPACE
