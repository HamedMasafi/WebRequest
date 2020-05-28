#include "jsonpostdata.h"

#include "../webrequest_p.h"
#include "../webrequestmanager.h"

#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonPostData::JsonPostData(QObject *parent) : ObjectData(parent)
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
    } else  if (m_data.isObject()) {
        QJsonObject obj = m_data.toObject();
        auto props = readProperties();
        for (auto i = props.begin(); i != props.end(); ++i)
            obj.insert(i.key(), i.value().toString());


        doc.setObject(m_data.toObject());
    } else {
        QJsonObject obj;
        auto props = readProperties();

        for (auto i = props.begin(); i != props.end(); ++i)
            obj.insert(i.key(), i.value().toString());

        doc.setObject(m_data.toObject());
    }
    body = doc.toJson(QJsonDocument::Compact);

    return d()->m_manager->request(request, body);
}
