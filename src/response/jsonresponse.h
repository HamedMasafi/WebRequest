#ifndef JSONRESPONSE_H
#define JSONRESPONSE_H

#include "abstractresponse.h"

#include <QJsonValue>

class JsonResponse : public AbstractResponse
{
    Q_OBJECT

public:
    JsonResponse(QObject *parent = nullptr);

    void processReply(const QByteArray &buffer) override;
    void beforeSend(QNetworkRequest &request) override;

signals:
    void finished(QJsonValue data);
};

#endif // JSONRESPONSE_H
