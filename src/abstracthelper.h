#ifndef ABSTRACTHELPER_H
#define ABSTRACTHELPER_H

#include "webrequest_p.h"

#include <QObject>
#include <QSharedDataPointer>

class AbstractHelper : public QObject
{
    Q_OBJECT
    QExplicitlySharedDataPointer<WebRequestPrivate> _d;

public:
    explicit AbstractHelper(QObject *parent = nullptr);

protected:
    QExplicitlySharedDataPointer<WebRequestPrivate> d() const;

private:

    void setD(const QExplicitlySharedDataPointer<WebRequestPrivate> &d);

    friend class WebRequest;
};

#endif // ABSTRACTHELPER_H
