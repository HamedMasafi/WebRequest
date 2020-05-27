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

#ifndef IMAGEREQUEST_H
#define IMAGEREQUEST_H

#include "webrequest.h"

#include <QtCore/QObject>
#include <QtGui/QImage>

class ImageRequest : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    QUrl m_fileName;

public:
    explicit ImageRequest(QObject *parent = nullptr);
    QUrl fileName() const;

public slots:
    void setFileName(QUrl fileName);

signals:
    void finished(QImage data);
    void fileNameChanged(QUrl fileName);

protected:
    void processResponse(QByteArray buffer) override;
//    void storeInCache(QDateTime expire, QByteArray buffer) override;
    bool retriveFromCache(const QString &key) override;
    void beforeSend(QNetworkRequest &request) override;
};

#endif // IMAGEREQUEST_H
