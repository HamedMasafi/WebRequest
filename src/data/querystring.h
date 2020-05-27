#ifndef QUERYSTRING_H
#define QUERYSTRING_H

#include "abstractdata.h"

#include <QVariantMap>

class QueryString : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)

    QVariantMap m_data;

public:
    QueryString(QObject *parent = nullptr);

    QVariantMap data() const;
    QNetworkReply * send(QNetworkRequest &request) override;

public slots:
    void setData(QVariantMap data);

signals:
    void dataChanged(QVariantMap data);

};

#endif // QUERYSTRING_H
