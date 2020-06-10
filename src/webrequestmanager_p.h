#ifndef WEBREQUESTMANAGER_P_H
#define WEBREQUESTMANAGER_P_H

#include "global.h"

#include <QNetworkRequest>
#include <QMutex>
#include <QList>

class QNetworkAccessManager;

KAJ_REST_BEGIN_NAMESPACE

class WebRequest;
class WebRequestManager;
class WebRequestManagerPrivate : public QSharedData
{

public:

    WebRequestManagerPrivate(WebRequestManager *parent);

    QNetworkAccessManager *networdAccessManager;

    int calls;
    QList<WebRequest*> requests;
    bool isBusy;
    static WebRequestManager *_instance;
    QMutex mutex;
    QString seprator;
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUESTMANAGER_P_H
