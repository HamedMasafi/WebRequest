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

#include "jsonresponse.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>

KAJ_REST_BEGIN_NAMESPACE

JsonResponse::JsonResponse(QObject *parent) : AbstractResponse(parent)
{

}

void JsonResponse::processReply(const QByteArray &buffer)
{
    auto doc = QJsonDocument::fromJson(buffer);

    if (doc.isObject())
        emit finished(doc.object());
    else if (doc.isArray())
        emit finished(doc.array());
    else
        emit finished(QJsonValue());
}

void JsonResponse::beforeSend(QNetworkRequest &request)
{
//    qDebug() << "RedirectionTargetAttribute"<<request.attribute(QNetworkRequest::FollowRedirectsAttribute, 100);
//    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, false);
    request.setRawHeader("Accept", "application/json");
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

}

KAJ_REST_END_NAMESPACE
