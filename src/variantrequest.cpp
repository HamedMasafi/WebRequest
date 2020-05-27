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

#include "variantrequest.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

VariantRequest::VariantRequest(QObject *parent) : WebRequest(parent)
{

}

void VariantRequest::processResponse(QByteArray buffer)
{
    QJsonDocument doc = QJsonDocument::fromJson(buffer);

    if (doc.isArray()) {
        QJsonArray a = doc.array();

        if (a.isEmpty())
            emit replyError(0, "");
        else
            emit finished(a.toVariantList());

        return;
    }
    if (doc.isObject()) {
        QJsonObject o = doc.object();

        if (o.isEmpty())
            emit replyError(0, "");
        else
            emit finished(o.toVariantMap());

        return;
    }

    emit replyError(0, "");
}
