#include "jsonresponse.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkRequest>

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
    request.setRawHeader("Accept", "application/json");
}
