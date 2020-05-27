#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include "webrequest.h"
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

class JsonRequest : public WebRequest
{
    Q_OBJECT
public:
    explicit JsonRequest(QObject *parent = nullptr);

signals:
    void finished(QJsonObject data);

protected:
    void processResponse(QByteArray buffer) override;
};

#endif // JSONREQUEST_H
