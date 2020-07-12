#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include "webrequest.h"
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

KAJ_REST_BEGIN_NAMESPACE

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

KAJ_REST_END_NAMESPACE

#endif // JSONREQUEST_H
