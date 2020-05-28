#include "objectdata.h"

#include <QMetaMethod>

ObjectData::ObjectData(QObject *parent) : AbstractData(parent)
{

}

QVariantMap ObjectData::readProperties() const
{
    QVariantMap map;
    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            map.insert(prop.name(), prop.read(this));
    }
    return map;
}
