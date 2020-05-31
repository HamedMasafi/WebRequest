#ifndef WEBREQUESTQML_H
#define WEBREQUESTQML_H

#include "webrequest.h"

class Pair;
class ExpireTime;
class WebRequestQml : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QList<Pair*> headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(ExpireTime* expireTime READ expireTime WRITE setExpireTime NOTIFY expireTimeChanged)

    QList<Pair*> m_headers;
    ExpireTime* m_expireTime;

public:
    WebRequestQml();

    QList<Pair*> headers() const;
    ExpireTime* expireTime() const;

public slots:
    void send();
    void setHeaders(QList<Pair*> headers);
    void setExpireTime(ExpireTime* expireTime);

signals:
    void headersChanged(QList<Pair*> headers);
    void expireTimeChanged(ExpireTime* expireTime);
};

#endif // WEBREQUESTQML_H
