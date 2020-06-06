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
    for (auto i = _headers.begin(); i != _headers.end(); ++i)
        if (!i.key().compare(headerName, Qt::CaseInsensitive))
            return i.value();
    return QString();
}

void AbstractResponse::setHeader(const QString &name, const QByteArray &value)
{
    _headers.insert(name, value);
}
