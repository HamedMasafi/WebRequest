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

#ifndef QUERYSTRING_H
#define QUERYSTRING_H

#include "abstractdata.h"

#include <QVariantMap>

KAJ_REST_BEGIN_NAMESPACE

class QueryString : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    QVariantMap m_data;

public:
    QueryString(QObject *parent = nullptr);

    QVariantMap data() const;
    QNetworkReply * send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void setData(QVariantMap data);

signals:
    void dataChanged(QVariantMap data);

};

KAJ_REST_END_NAMESPACE

#endif // QUERYSTRING_H
