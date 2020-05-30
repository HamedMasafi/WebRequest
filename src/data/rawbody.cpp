#include "rawbody.h"

#include "../webrequestmanager.h"

RawBody::RawBody(QObject *parent) : AbstractData(parent)
{

}

QString RawBody::data() const
{
    return m_data;
}

QNetworkReply *RawBody::send(QNetworkRequest &request)
{
    return d()->m_manager->request(request, m_data.toUtf8());
}

QString RawBody::generateCacheKey()
{
    return m_data.replace("'", "");
}

void RawBody::setData(QString data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}
