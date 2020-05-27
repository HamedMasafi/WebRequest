#include "imageresponse.h"
#include "../webrequestcache.h"

#include <QDebug>

ImageResponse::ImageResponse(QObject *parent) : AbstractResponse(parent)
{

}

QUrl ImageResponse::fileName() const
{
    return m_fileName;
}

void ImageResponse::processReply(const QByteArray &buffer)
{
//    QString cid = d()->m_actualCacheId;
//    if (cid.isEmpty())
//        cid = url().toString().replace("'", "");
//    QString fn = d()->m_cacheManager->setValue(cid, buffer, expire);
    setFileName(QUrl::fromLocalFile(buffer));
    qDebug() << buffer;
}

bool ImageResponse::storeCacheAsFile() const
{
    return true;
}

void ImageResponse::setFileName(QUrl fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}
