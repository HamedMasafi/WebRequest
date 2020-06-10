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

#include "abstractresponse.h"

KAJ_REST_BEGIN_NAMESPACE

AbstractResponse::AbstractResponse(QObject *parent) : AbstractHelper(parent)
{

}

void AbstractResponse::beforeSend(QNetworkRequest &request)
{
    Q_UNUSED(request);
}

bool AbstractResponse::storeCacheAsFile() const
{
    return false;
}

QString AbstractResponse::header(const QString &headerName) const
{
    for (auto i = _headers.begin(); i != _headers.end(); ++i)
        if (!i.key().compare(headerName, Qt::CaseInsensitive))
            return i.value();
    return QString();
}

void AbstractResponse::setHeader(const QString &name, const QByteArray &value)
{
    _headers.insert(name, value);
}

KAJ_REST_END_NAMESPACE
