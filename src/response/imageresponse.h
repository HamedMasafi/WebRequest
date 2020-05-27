#ifndef IMAGERESPONSE_H
#define IMAGERESPONSE_H

#include "abstractresponse.h"

#include <QUrl>

class ImageResponse : public AbstractResponse
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    QUrl m_fileName;

public:
    ImageResponse(QObject *parent = nullptr);
    QUrl fileName() const;
    void processReply(const QByteArray &buffer);
    bool storeCacheAsFile() const;

public slots:
    void setFileName(QUrl fileName);

signals:
    void fileNameChanged(QUrl fileName);
};

#endif // IMAGERESPONSE_H
