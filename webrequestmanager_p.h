#ifndef WEBREQUESTMANAGER_P_H
#define WEBREQUESTMANAGER_P_H

#include "webrequestmanager.h"

#include <QNetworkRequest>
#include <QQueue>

class QNetworkAccessManager;

class WebRequestManagerPrivate
{
    WebRequestManager *q_ptr;
    Q_DECLARE_PUBLIC(WebRequestManager)

public:

    WebRequestManagerPrivate(WebRequestManager *parent);

    QNetworkAccessManager *networdAccessManager;
};

#endif // WEBREQUESTMANAGER_P_H
