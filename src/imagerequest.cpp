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

#include "imagerequest.h"
#include "webrequestcache.h"
#include "webrequest_p.h"

#include "response/imageresponse.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>

#include <QNetworkRequest>

KAJ_REST_BEGIN_NAMESPACE

ImageRequest::ImageRequest(QObject *parent) : WebRequest(parent)
{
    setUseUtf8(false);
    auto _response = new ImageResponse(this);
    connect(_response, &ImageResponse::fileNameChanged, this, &ImageRequest::setFileName);
    setResponse(_response);
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

KAJ_REST_END_NAMESPACE
