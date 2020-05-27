#include "abstracthelper.h"

QExplicitlySharedDataPointer<WebRequestPrivate> AbstractHelper::d() const
{
    return _d;
}

void AbstractHelper::setD(const QExplicitlySharedDataPointer<WebRequestPrivate> &d)
{
    _d = d;
}

AbstractHelper::AbstractHelper(QObject *parent) : QObject(parent)
{

}
