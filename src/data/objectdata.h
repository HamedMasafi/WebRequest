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

#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "abstractdata.h"

KAJ_REST_BEGIN_NAMESPACE

class ObjectData : public AbstractData
{
    Q_OBJECT

public:
    ObjectData(QObject *parent = nullptr);
    virtual QNetworkReply *send(QNetworkRequest &request) override = 0;
    QString generateCacheKey() override;

protected:
    QVariantMap readProperties() const;
};

KAJ_REST_END_NAMESPACE

#endif // OBJECTDATA_H
