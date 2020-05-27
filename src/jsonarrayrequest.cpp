#include "jsonrequest.h"

#include <QtCore/QJsonDocument>

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
