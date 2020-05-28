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
