#ifndef FILEITEM_H
#define FILEITEM_H

#include "../pair.h"
#include <QObject>
#include <QUrl>

class FileItem : public Pair
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

    QUrl m_source;

public:
    explicit FileItem(QObject *parent = nullptr);

    QUrl source() const;

public slots:
    void setSource(QUrl source);

signals:
    void sourceChanged(QUrl source);
};

#endif // FILEITEM_H
