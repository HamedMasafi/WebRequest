#include "fileitem.h"

FileItem::FileItem(QObject *parent) : Pair(parent)
{

}


QUrl FileItem::source() const
{
    return m_source;
}

void FileItem::setSource(QUrl source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(m_source);
}
