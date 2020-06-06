#include "abstractresponse.h"

AbstractResponse::AbstractResponse(QObject *parent) : AbstractHelper(parent)
{

}

void AbstractResponse::beforeSend(QNetworkRequest &request)
{
    Q_UNUSED(request);
}

bool AbstractResponse::storeCacheAsFile() const
{
    return false;
}

QString AbstractResponse::header(const QString &headerName) const
{
    return _headers.value(headerName);
}

void AbstractResponse::setHeader(const QString &name, const QByteArray &value)
{
    _headers.insert(name, value);
}
