#ifndef JSONPOSTDATA_H
#define JSONPOSTDATA_H

#include "objectdata.h"

#include <QJsonValue>

class JsonPostData : public ObjectData
{
    Q_OBJECT
    Q_PROPERTY(QJsonValue data READ data WRITE setData NOTIFY dataChanged STORED false)

    QJsonValue m_data;

public:
    JsonPostData(QObject *parent = nullptr);
    QJsonValue data() const;
    QNetworkReply *send(QNetworkRequest &request);

public slots:
    void setData(QJsonValue data);

signals:
    void dataChanged(QJsonValue data);

};

#endif // JSONPOSTDATA_H
