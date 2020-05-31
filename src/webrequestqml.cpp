#include "webrequestqml.h"
#include "pair.h"
#include "expiretime.h"

WebRequestQml::WebRequestQml()
{

}

QList<Pair *> WebRequestQml::headers() const
{
    return m_headers;
}

ExpireTime *WebRequestQml::expireTime() const
{
    return m_expireTime;
}

void WebRequestQml::setHeaders(QList<Pair *> headers)
{
    if (m_headers == headers)
        return;

    m_headers = headers;
    emit headersChanged(m_headers);
}

void WebRequestQml::send()
{
    foreach (auto h, m_headers)
        setHeader(h->name(), h->value());
    setExpirationSeconds(m_expireTime->totalSecs());
}

void WebRequestQml::setExpireTime(ExpireTime *expireTime)
{
    if (m_expireTime == expireTime)
        return;

    m_expireTime = expireTime;
    emit expireTimeChanged(m_expireTime);
}
