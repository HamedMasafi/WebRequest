#include "querystring.h"

#include <QNetworkRequest>
#include <QUrlQuery>
#include "../webrequestmanager.h"
#include "../webrequest_p.h"

QueryString::QueryString(QObject *parent) : AbstractData(parent)
{

}

QVariantMap QueryString::data() const
{
    return m_data;
}

void QueryString::setData(QVariantMap data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

QNetworkReply *QueryString::send(QNetworkRequest &request)
{
    QUrlQuery queryData;

    if (m_data.count())
        foreach (auto key, m_data.keys())
            queryData.addQueryItem(key, m_data.value(key).toString());

    auto u = request.url();
    u.setQuery(queryData);
    request.setUrl(u);

    return d()->m_manager->request(request);
}

QString QueryString::generateCacheKey()
{
    QString queryData;
    for (auto i = m_data.begin(); i != m_data.end(); ++i) {
        queryData.append(i.key() + "&" + i.value().toString() + ";;");
    }

    return queryData;
}
