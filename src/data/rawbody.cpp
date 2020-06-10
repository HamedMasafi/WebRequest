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

#include "rawbody.h"

#include "../webrequestmanager.h"

KAJ_REST_BEGIN_NAMESPACE

RawBody::RawBody(QObject *parent) : AbstractData(parent)
{

}

QString RawBody::data() const
{
    return m_data;
}

QNetworkReply *RawBody::send(QNetworkRequest &request)
{
    return d()->m_manager->request(request, m_data.toUtf8());
}

QString RawBody::generateCacheKey()
{
    return m_data.replace("'", "");
}

void RawBody::setData(QString data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

KAJ_REST_END_NAMESPACE
