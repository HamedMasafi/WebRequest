#ifndef STRINGRESPONSE_H
#define STRINGRESPONSE_H

#include "abstractresponse.h"

class StringResponse : public AbstractResponse
{
    Q_OBJECT

public:
    StringResponse(QObject *parent = nullptr);

    void processReply(const QByteArray &buffer);

signals:
    void finished(QString data);
};

#endif // STRINGRESPONSE_H
