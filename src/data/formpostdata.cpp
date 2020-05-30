#include "formpostdata.h"

#include <QFile>
#include <QFileInfo>
#include <QUrlQuery>
#include <QMetaProperty>
#include "../webrequestmanager.h"
#include "../webrequest_p.h"

FormPostData::FormPostData(QObject *parent) : AbstractData(parent)
{

}

QVariantMap FormPostData::data() const
{
    return m_data;
}

Rest::Files FormPostData::files() const
{
    return m_files;
}

void FormPostData::setData(QVariantMap data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

void FormPostData::setFiles(Rest::Files files)
{
    if (m_files == files)
        return;

    m_files = files;
    emit filesChanged(m_files);
}

QNetworkReply *FormPostData::send(QNetworkRequest &request)
{
    QUrlQuery queryData;

    if (m_data.count())
        foreach (auto key, m_data.keys())
            queryData.addQueryItem(key, m_data.value(key).toString());

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    auto body = queryData.toString(QUrl::FullyEncoded).toUtf8();

    return d()->m_manager->request(request, body);
}

QString FormPostData::generateCacheKey()
{
    QUrlQuery queryData;

    if (m_data.count())
        foreach (auto key, m_data.keys())
            queryData.addQueryItem(key, m_data.value(key).toString());

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    return queryData.toString(QUrl::FullyEncoded);
}

void FormPostData::addData(const QString &name, const QVariant &value)
{
    m_data.insert(name, value);
}
