#include "helper.h"

#include "webrequest.h"

#include "response/stringresponse.h"
#include "response/jsonresponse.h"

#include "data/jsonpostdata.h"

Helper::Helper(QObject *parent) : QObject(parent)
{

}

void Helper::request(const QUrl &url, Rest::Callback<QString> cb,
                     Rest::ErrorCallback ecb,
                     Rest::Headers headers)
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

void Helper::request(const QUrl &url, Rest::Callback<QJsonValue> cb,
                     Rest::ErrorCallback ecb, Rest::Headers headers)
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
                     Rest::Callback<QJsonValue> cb
                     , Rest::ErrorCallback ecb, Rest::Headers headers)
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
