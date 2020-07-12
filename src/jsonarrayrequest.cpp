#include "jsonrequest.h"

#include <QtCore/QJsonDocument>

KAJ_REST_BEGIN_NAMESPACE

JsonRequest::JsonRequest(QObject *parent) : WebRequest(parent)
{ }

void JsonRequest::processResponse(QByteArray buffer)
{
    QJsonObject obj = QJsonDocument::fromJson(buffer).object();
    if (obj.isEmpty())
        emit replyError(0, "");
    else
        emit finished(obj);
}

KAJ_REST_END_NAMESPACE
