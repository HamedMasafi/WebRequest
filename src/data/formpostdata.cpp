#include "fileitem.h"
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
void FormPostData::addData(QQmlListProperty<Pair> *property, Pair *pair)
{
    FormPostData *postData = qobject_cast<FormPostData*>(property->object);
    Q_ASSERT(postData != 0);
    pair->setParent(postData);

    QList<Pair *> *list = reinterpret_cast<QList<Pair *> *>(property->data);
    Q_ASSERT(list != 0);

    list->append(pair);
}
Pair *FormPostData::dataAt(QQmlListProperty<Pair> *property, int index)
{
    FormPostData *store = qobject_cast<FormPostData*>(property->object);
    Q_ASSERT(store != 0);

    QList<Pair *> *products = reinterpret_cast<QList<Pair *> *>(property->data);
    Q_ASSERT(products != 0);

    return products->at(index);
}
void FormPostData::clearData(QQmlListProperty<Pair> *property)
{
    QList<Pair *> *list = reinterpret_cast<QList<Pair*> *>(property->data);
    Q_ASSERT(list != 0);

//    for (int i=0; i<products->size(); ++i) {
//        Pair *product = products->at(i);
//        product->setStore(0);
//    }
    list->clear();
}
int FormPostData::dataCount(QQmlListProperty<Pair> *property)
{
    QList<Pair *> *list = reinterpret_cast<QList<Pair *> *>(property->data);
    return list->count();
}

QNetworkReply *FormPostData::processWithFiles(QNetworkRequest &request, QList<Pair *> data, QList<FileItem *> files)
{
    return nullptr;
}

QNetworkReply *FormPostData::processFormData(QNetworkRequest &request, QList<Pair*> data)
{
    QUrlQuery queryData;

    if (data.count())
        foreach (auto dt, data)
            queryData.addQueryItem(dt->name(), dt->value());

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    auto body = queryData.toString(QUrl::FullyEncoded).toUtf8();

    return d()->m_manager->request(request, body);
}

QQmlListProperty<Pair> FormPostData::data()
{
    return {this, &m_data,
        &FormPostData::addData,
        &FormPostData::dataCount,
        &FormPostData::dataAt,
        &FormPostData::clearData};
            /*QQmlListProperty<Pair>(this,
                                  &m_data,
                                  &addData,
                                  &dataCount,
                                  &dataAt,
                                  &clearData);*/

}


QNetworkReply *FormPostData::send(QNetworkRequest &request)
{
    QUrlQuery queryData;

    QList<FileItem*> files;
    QList<Pair*> data;
    for (auto i = m_data.begin(); i != m_data.end(); ++i) {
        auto fi = qobject_cast<FileItem*>(*i);
        if (fi)
            files.append(fi);
        else
            data.append(*i);
    }

    if (files.count())
        return processWithFiles(request, data, files);
    else
        return processFormData(request, data);
}

QString FormPostData::generateCacheKey()
{
    QUrlQuery queryData;

    for (auto i = m_data.begin(); i != m_data.end(); ++i) {
        auto fi = qobject_cast<FileItem*>(*i);
        if (fi)
            queryData.addQueryItem(fi->name(), fi->source().toString());
        else
            queryData.addQueryItem((*i)->name(), (*i)->value());
    }

    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            queryData.addQueryItem(prop.name(), prop.read(this).toString());
    }

    return queryData.toString(QUrl::FullyEncoded);
}

void FormPostData::addData2(const QString &name, const QVariant &value)
{
//    m_data.insert(name, value);
}
