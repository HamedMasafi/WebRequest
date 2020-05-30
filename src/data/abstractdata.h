#ifndef ABSTRACTDATA_H
#define ABSTRACTDATA_H

#include "../webrequest_p.h"
#include "../abstracthelper.h"

#include <QObject>

class QNetworkRequest;
class WebRequest;
class QNetworkReply;
class AbstractData : public AbstractHelper
{
    Q_OBJECT

public:
    explicit AbstractData(QObject *parent = nullptr);


    virtual QNetworkReply *send(QNetworkRequest &request) = 0;
    virtual QString generateCacheKey() = 0;

};

#endif // ABSTRACTDATA_H
