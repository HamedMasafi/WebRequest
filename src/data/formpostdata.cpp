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

#include "formpostdata.h"

#include <QFile>
#include <QFileInfo>
#include <QUrlQuery>
#include <QMetaProperty>
#include "../webrequestmanager.h"
#include "../webrequest_p.h"

KAJ_REST_BEGIN_NAMESPACE

FormPostData::FormPostData(QObject *parent) : AbstractData(parent)
{

}

QVariantMap FormPostData::data() const
{
    return m_data;
}

Rest::Files FormPostData::files() const
{
    return m_files;
}

void FormPostData::setData(QVariantMap data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

void FormPostData::setFiles(Rest::Files files)
{
    if (m_files == files)
        return;

    m_files = files;
    emit filesChanged(m_files);
}

QNetworkReply *FormPostData::send(QNetworkRequest &request)
{
    QUrlQuery queryData;

    if (m_data.count()) {
        auto keys = m_data.keys();
        for (const auto &key : keys)
            queryData.addQueryItem(key, m_data.value(key).toString());
    }

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    auto body = queryData.toString(QUrl::FullyEncoded).toUtf8();

    return d()->m_manager->request(request, body);
}

QString FormPostData::generateCacheKey()
{
    QUrlQuery queryData;

    if (m_data.count()) {
        auto keys = m_data.keys();
        for (const auto &key : keys)
            queryData.addQueryItem(key, m_data.value(key).toString());
    }

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    return queryData.toString(QUrl::FullyEncoded);
}

void FormPostData::addData(const QString &name, const QVariant &value)
{
    m_data.insert(name, value);
}

KAJ_REST_END_NAMESPACE
