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

#include "helper.h"

#include "webrequest.h"

#include "response/stringresponse.h"
#include "response/jsonresponse.h"

#include "data/jsonpostdata.h"

KAJ_REST_BEGIN_NAMESPACE

Helper::Helper(QObject *parent) : QObject(parent)
{

}

void Helper::request(const QUrl &url, Callback<QString> cb,
                     ErrorCallback ecb,
                     Headers headers)
{
    auto r = new WebRequest;
    auto response = new StringResponse(r);
    r->setHeaders(headers);
    connect(response, &StringResponse::finished, cb);
    connect(response, &StringResponse::error, ecb);
    connect(response, &StringResponse::finished, r, &QObject::deleteLater);
    connect(response, &StringResponse::error, r, &QObject::deleteLater);
    r->setResponse(response);
    r->setUrl(url);
    r->send();
}

void Helper::request(const QUrl &url, Callback<QJsonValue> cb,
                     ErrorCallback ecb, Headers headers)
{
    auto r = new WebRequest;
    auto response = new JsonResponse(r);
    r->setHeaders(headers);
    connect(response, &JsonResponse::finished, cb);
    connect(response, &JsonResponse::error, ecb);
    connect(response, &JsonResponse::finished, r, &QObject::deleteLater);
    connect(response, &JsonResponse::error, r, &QObject::deleteLater);
    r->setResponse(response);
    r->setUrl(url);
    r->send();
}

void Helper::request(const QUrl &url, QJsonValue json,
                     Callback<QJsonValue> cb
                     , ErrorCallback ecb, Headers headers)
{
    auto r = new WebRequest;
    auto response = new JsonResponse(r);
    r->setHeaders(headers);

    auto data = new JsonPostData(r);
    data->setData(json);

    connect(response, &JsonResponse::finished, cb);
    connect(response, &JsonResponse::error, ecb);
    connect(response, &JsonResponse::finished, r, &QObject::deleteLater);
    connect(response, &JsonResponse::error, r, &QObject::deleteLater);
    r->setResponse(response);
    r->setUrl(url);
    r->send();
}

KAJ_REST_END_NAMESPACE
