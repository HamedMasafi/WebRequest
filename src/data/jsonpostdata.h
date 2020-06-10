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

#ifndef JSONPOSTDATA_H
#define JSONPOSTDATA_H

#include "abstractdata.h"

#include <QJsonValue>

KAJ_REST_BEGIN_NAMESPACE

class JsonPostData : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QJsonValue data READ data WRITE setData NOTIFY dataChanged STORED false)

    QJsonValue m_data;

public:
    JsonPostData(QObject *parent = nullptr);
    QJsonValue data() const;
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void setData(QJsonValue data);

signals:
    void dataChanged(QJsonValue data);

private:
    QJsonDocument json() const;
};

KAJ_REST_END_NAMESPACE

#endif // JSONPOSTDATA_H
