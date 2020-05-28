#ifndef ABSTRACTRESPONSE_H
#define ABSTRACTRESPONSE_H

#include <QObject>
#include "../abstracthelper.h"

class AbstractResponse : public AbstractHelper
{
    Q_OBJECT
public:
    explicit AbstractResponse(QObject *parent = nullptr);
    virtual void beforeSend(QNetworkRequest &request);
    virtual void processReply(const QByteArray &buffer) = 0;
    virtual bool storeCacheAsFile() const;

signals:
    void error(const int &code, const QString &descript);
};

#endif // ABSTRACTRESPONSE_H
