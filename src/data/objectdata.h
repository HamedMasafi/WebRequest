#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "abstractdata.h"

class ObjectData : public AbstractData
{
    Q_OBJECT

public:
    ObjectData(QObject *parent = nullptr);
    virtual QNetworkReply *send(QNetworkRequest &request) = 0;

protected:
    QVariantMap readProperties() const;
};

#endif // OBJECTDATA_H
