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

#include "jsonpostdata.h"

#include "../webrequest_p.h"
#include "../webrequestmanager.h"

#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaProperty>
#include <QDebug>

KAJ_REST_BEGIN_NAMESPACE

JsonPostData::JsonPostData(QObject *parent) : AbstractData(parent)
{

}

QJsonValue JsonPostData::data() const
{
    return m_data;
}

void JsonPostData::setData(QJsonValue data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

QJsonDocument JsonPostData::json() const
{
    QJsonDocument doc;

    if (m_data.isArray()) {
        doc.setArray(m_data.toArray());
    } else  {
        QJsonObject obj;
        if (m_data.isObject())
            QJsonObject obj = m_data.toObject();

        for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
            QMetaProperty prop = metaObject()->property(i);
            if (!prop.isStored())
                obj.insert(prop.name(), QJsonValue::fromVariant(prop.read(this)));
        }
        doc.setObject(m_data.toObject());
    }
    return doc;
}

QNetworkReply *JsonPostData::send(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");

    QByteArray body;
    body = json().toJson(QJsonDocument::Compact);

    qDebug() << body;
    return d()->m_manager->request(request, body);
}

QString JsonPostData::generateCacheKey()
{
    return json().toJson(QJsonDocument::Compact);
}

KAJ_REST_END_NAMESPACE
