#include "jsonpostdata.h"

#include "../webrequest_p.h"
#include "../webrequestmanager.h"

#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaProperty>

JsonPostData::JsonPostData(QObject *parent) : AbstractData(parent)
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

QJsonDocument JsonPostData::json() const
{
    QJsonDocument doc;

    if (m_data.isArray()) {
        doc.setArray(m_data.toArray());
    } else  {
        QJsonObject obj;
        if (m_data.isObject())
            QJsonObject obj = m_data.toObject();

        for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
            QMetaProperty prop = metaObject()->property(i);
            if (!prop.isStored())
                obj.insert(prop.name(), QJsonValue::fromVariant(prop.read(this)));
        }
        doc.setObject(m_data.toObject());
    }
    return doc;
}

QNetworkReply *JsonPostData::send(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");

    QByteArray body;
    body = json().toJson(QJsonDocument::Compact);

    return d()->m_manager->request(request, body);
}

QString JsonPostData::generateCacheKey()
{
    return json().toJson(QJsonDocument::Compact);
}
