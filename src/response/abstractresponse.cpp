#include "abstractresponse.h"

AbstractResponse::AbstractResponse(QObject *parent) : AbstractHelper(parent)
{

}

bool AbstractResponse::storeCacheAsFile() const
{
    return false;
}
