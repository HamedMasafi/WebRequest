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

#ifndef IMAGERESPONSE_H
#define IMAGERESPONSE_H

#include "abstractresponse.h"

#include <QUrl>

KAJ_REST_BEGIN_NAMESPACE

class ImageResponse : public AbstractResponse
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    QUrl m_fileName;

public:
    ImageResponse(QObject *parent = nullptr);
    QUrl fileName() const;
    void processReply(const QByteArray &buffer);
    bool storeCacheAsFile() const;

public slots:
    void setFileName(QUrl fileName);

signals:
    void fileNameChanged(QUrl fileName);
};

KAJ_REST_END_NAMESPACE

#endif // IMAGERESPONSE_H
