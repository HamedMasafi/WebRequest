#ifndef WEBREQUESTMANAGER_P_H
#define WEBREQUESTMANAGER_P_H

#include <QNetworkRequest>
#include <QMutex>
#include <QList>

class QNetworkAccessManager;
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

#endif // WEBREQUESTMANAGER_P_H
