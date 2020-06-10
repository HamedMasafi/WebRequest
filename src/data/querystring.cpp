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

#include "querystring.h"

#include <QNetworkRequest>
#include <QUrlQuery>
#include "../webrequestmanager.h"
#include "../webrequest_p.h"

KAJ_REST_BEGIN_NAMESPACE

QueryString::QueryString(QObject *parent) : AbstractData(parent)
{

}

QVariantMap QueryString::data() const
{
    return m_data;
}

void QueryString::setData(QVariantMap data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

QNetworkReply *QueryString::send(QNetworkRequest &request)
{
    QUrlQuery queryData;

    if (m_data.count())
        foreach (auto key, m_data.keys())
            queryData.addQueryItem(key, m_data.value(key).toString());

    auto u = request.url();
    u.setQuery(queryData);
    request.setUrl(u);

    return d()->m_manager->request(request);
}

QString QueryString::generateCacheKey()
{
    QString queryData;
    for (auto i = m_data.begin(); i != m_data.end(); ++i) {
        queryData.append(i.key() + "&" + i.value().toString() + ";;");
    }

    return queryData;
}

KAJ_REST_END_NAMESPACE
