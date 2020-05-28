#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "abstractdata.h"

class ObjectData : public AbstractData
{
    Q_OBJECT

public:
    ObjectData(QObject *parent = nullptr);
    virtual QNetworkReply *send(QNetworkRequest &request) override = 0;
    QString generateCacheKey() override;

protected:
    QVariantMap readProperties() const;
};

#endif // OBJECTDATA_H
