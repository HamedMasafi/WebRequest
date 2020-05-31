#include "pair.h"

Pair::Pair(QObject *parent) : QObject(parent)
{

}

QString Pair::name() const
{
    return m_name;
}

QString Pair::value() const
{
    return m_value;
}

void Pair::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Pair::setValue(QString value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}
