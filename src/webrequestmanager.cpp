/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "webrequest.h"
#include "webrequestmanager.h"
#include "webrequestmanager_p.h"
#include <QDebug>
#include <QNetworkAccessManager>

WebRequestManagerPrivate::WebRequestManagerPrivate(WebRequestManager *parent)
    : networdAccessManager(new QNetworkAccessManager(parent))
      , calls(0), isBusy(false), seprator("\n")
{

}

WebRequestManager::WebRequestManager() : QObject()
    , d(new WebRequestManagerPrivate(this))
{ }

void WebRequestManager::addCall(WebRequest *r)
{
    d->mutex.lock();
    d->calls++;
    d->requests.append(r);
    auto lt = loadingTexts();
    emit loadingTextsChanged(lt);
    emit loadingTextChanged(lt.join(d->seprator));
    setIsBusy(true);
    d->mutex.unlock();
}

void WebRequestManager::removeCall(WebRequest *r)
{
    d->mutex.lock();
    d->calls--;
    d->requests.removeOne(r);
    emit loadingTextsChanged(loadingTexts());
//    qDebug() << "Calls: " << calls << "--";
    setIsBusy(d->calls);
    d->mutex.unlock();
}

WebRequestManager *WebRequestManager::instance()
{
    static WebRequestManager *ins = new WebRequestManager;
    return ins;
}

bool WebRequestManager::isBusy() const
{
    return d->calls;
}

QStringList WebRequestManager::loadingTexts() const
{
    QStringList ret;
    foreach (WebRequest *r, d->requests)
        if (!r->loadingText().isEmpty())
            ret.append(r->loadingText());
    return ret;
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request)
{
    return d->networdAccessManager->get(request);
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request, QByteArray postData)
{
    return d->networdAccessManager->post(request, postData);
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request, QHttpMultiPart *multipart)
{
    return d->networdAccessManager->sendCustomRequest(request, "PATCH", multipart);
}

QString WebRequestManager::loadingText() const
{
    return loadingTexts().join(d->seprator);
}

QString WebRequestManager::seprator() const
{
    return d->seprator;
}

void WebRequestManager::setIsBusy(bool isBusy)
{
    if (d->isBusy == isBusy)
        return;

    d->isBusy = isBusy;
    emit isBusyChanged(isBusy);
}

void WebRequestManager::setSeprator(QString seprator)
{
    if (d->seprator == seprator)
        return;

    d->seprator = seprator;
    emit sepratorChanged(seprator);
}
