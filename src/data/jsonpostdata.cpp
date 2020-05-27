#include "jsonpostdata.h"

#include "../webrequest_p.h"
#include "../webrequestmanager.h"

#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonPostData::JsonPostData()
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

QNetworkReply *JsonPostData::send(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");

    QJsonDocument doc;
    QByteArray body;

    if (m_data.isArray()) {
        doc.setArray(m_data.toArray());
        body = doc.toJson(QJsonDocument::Compact);
    }

    if (m_data.isObject()) {
        doc.setObject(m_data.toObject());
        body = doc.toJson(QJsonDocument::Compact);
    }

    return d()->m_manager->request(request, body);
}
