#ifndef JSONPOSTDATA_H
#define JSONPOSTDATA_H

#include "abstractdata.h"

#include <QJsonValue>

class JsonPostData : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QJsonValue data READ data WRITE setData NOTIFY dataChanged STORED false)

    QJsonValue m_data;

public:
    JsonPostData(QObject *parent = nullptr);
    QJsonValue data() const;
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void setData(QJsonValue data);

signals:
    void dataChanged(QJsonValue data);

private:
    QJsonDocument json() const;
};

#endif // JSONPOSTDATA_H
