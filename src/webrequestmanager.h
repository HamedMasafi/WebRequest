/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kaj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef WEBREQUESTMANAGER_H
#define WEBREQUESTMANAGER_H

#include "webrequestmanager_p.h"
#include "global.h"

#include <QMutex>
#include <QObject>
#include <QSharedDataPointer>

class QNetworkReply;
class QHttpMultiPart;
class QNetworkRequest;

KAJ_REST_BEGIN_NAMESPACE

class WebRequest;
class WebRequestManager : public QObject {
    Q_OBJECT

    QExplicitlySharedDataPointer<WebRequestManagerPrivate> d;

    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged)
    Q_PROPERTY(QString loadingText READ loadingText NOTIFY loadingTextChanged)
    Q_PROPERTY(QStringList loadingTexts READ loadingTexts NOTIFY loadingTextsChanged)
    Q_PROPERTY(QString seprator READ seprator WRITE setSeprator NOTIFY sepratorChanged)

//    static WebRequestManager *_instance;
//    QMutex mutex;
//    QString m_seprator;
//    int calls;
//    QList<WebRequest*> requests;
//    bool m_isBusy;

public:
    WebRequestManager();
    static WebRequestManager *instance();
    bool isBusy() const;

    friend class WebRequest;
    QStringList loadingTexts() const;
    QString loadingText() const;
    QString seprator() const;

    QNetworkReply *request(const QNetworkRequest &request);
    QNetworkReply *request(const QNetworkRequest &request, QByteArray postData);
    QNetworkReply *request(const QNetworkRequest &request, QHttpMultiPart *multipart);


private:

    void addCall(WebRequest *r);
    void removeCall(WebRequest *r);


public slots:
    void setIsBusy(bool isBusy);
    void setSeprator(QString seprator);

signals:
    void isBusyChanged(bool isBusy);
    void loadingTextsChanged(QStringList loadingTexts);
    void loadingTextChanged(QString loadingText);
    void sepratorChanged(QString seprator);
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUESTMANAGER_H
