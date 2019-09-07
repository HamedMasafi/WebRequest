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
    : q_ptr(parent), networdAccessManager(new QNetworkAccessManager(parent))
{

}

// RestRequestCallsManager
WebRequestManager* WebRequestManager::_instance = nullptr;

WebRequestManager::WebRequestManager() : d_ptr(new WebRequestManagerPrivate(this))
  , calls(0), m_isBusy(false)
{ }

void WebRequestManager::addCall(WebRequest *r)
{
    mutex.lock();
    calls++;
    requests.append(r);
    emit loadingTextsChanged(loadingTexts());
//    qDebug() << "Calls: " << calls << "++";
    setIsBusy(true);
    mutex.unlock();
}

void WebRequestManager::removeCall(WebRequest *r)
{
    mutex.lock();
    calls--;
    requests.removeOne(r);
    emit loadingTextsChanged(loadingTexts());
//    qDebug() << "Calls: " << calls << "--";
    setIsBusy(calls);
    mutex.unlock();
}

WebRequestManager *WebRequestManager::instance()
{
    if (_instance == nullptr)
        _instance = new WebRequestManager;
    return _instance;
}

bool WebRequestManager::isBusy() const
{
    return m_isBusy;
}

QStringList WebRequestManager::loadingTexts() const
{
    QStringList ret;
    foreach (WebRequest *r, requests)
        if (!r->loadingText().isEmpty())
            ret.append(r->loadingText());
    return ret;
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request)
{
    Q_D(WebRequestManager);
    return d->networdAccessManager->get(request);
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request, QByteArray postData)
{
    Q_D(WebRequestManager);
    return d->networdAccessManager->post(request, postData);
}

QNetworkReply *WebRequestManager::request(const QNetworkRequest &request, QHttpMultiPart *multipart)
{
    Q_D(WebRequestManager);
    return d->networdAccessManager->post(request, multipart);
}

void WebRequestManager::setIsBusy(bool isBusy)
{
    if (m_isBusy == isBusy)
        return;

    m_isBusy = isBusy;
    emit isBusyChanged(m_isBusy);
}
