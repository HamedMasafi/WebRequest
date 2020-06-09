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

#include "expiretime.h"
#include "webrequest.h"
#include "webrequest_p.h"
#include "webrequestcache.h"
#include "webrequestmanager.h"

#include "response/abstractresponse.h"
#include "data/abstractdata.h"

#include <QEventLoop>
#include <QFile>
#include <QTextCodec>
#include <QUrlQuery>
#include <QtCore/QMetaMethod>
#include <QtCore/QRegularExpression>
#include <QtNetwork/QHttpPart>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

WebRequestPrivate::WebRequestPrivate() :
    calls(0), m_isBusy(false), m_cacheId(QString()),
    m_useCache(true), m_includeDataInCacheId(false),
    m_expirationSeconds(0),
    useUtf8(true),
    data(nullptr), response(nullptr)
{
}

WebRequest::WebRequest(QObject *parent)
    : QObject(parent), d(new WebRequestPrivate)
{
    setManager(WebRequestManager::instance());
    setCacheManager(WebRequestCache::instance());
    d->expireTime = new ExpireTime(this);
}

WebRequest::~WebRequest()
{
    if (d->calls)
        for (int i = 0; i < d->calls; ++i)
            manager()->removeCall(this);
}

void WebRequest::sendToServer(bool cache)
{
    if (!d->response) {
        qWarning() << "No response defined!";
        return;
    }

    if (d->m_useCache && cache) {
        QString id = generateCacheId();
        if (retriveFromCache(id)) {
            qDebug() << "cache found";
            setCacheUsed(true);
            return;
        }
    }

    d->calls++;
    setCacheUsed(false);

    QNetworkRequest request;
    manager()->addCall(this);
    setIsBusy(true);
    request.setUrl(d->m_url);


    if (d->headers.count())
        for (auto i = d->headers.begin(); i != d->headers.end(); ++i)
            request.setRawHeader(i.key().toUtf8(), i.value().toByteArray());

    d->response->beforeSend(request);
    QNetworkReply *r;
    if (d->data) {
        r = d->data->send(request);
    } else {
        r = manager()->request(request);
    }
    connect(r, &QNetworkReply::finished, this, &WebRequest::finished);
}

void WebRequest::send(bool cache)
{
    sendToServer(cache);
}

void WebRequest::sendSync(bool cache)
{
    QEventLoop eventLoop;
    connect(this, &WebRequest::finished, &eventLoop, &QEventLoop::quit);
    connect(this, &WebRequest::replyError, &eventLoop, &QEventLoop::quit);
    send(cache);
    eventLoop.exec();
}

QUrl WebRequest::url() const
{
    return d->m_url;
}

bool WebRequest::isBusy() const
{

    return d->m_isBusy;
}

QString WebRequest::cacheId() const
{

    return d->m_cacheId;
}

bool WebRequest::useCache() const
{

    return d->m_useCache;
}

bool WebRequest::includeDataInCacheId() const
{

    return d->m_includeDataInCacheId;
}

WebRequestManager *WebRequest::manager() const
{

    return d->m_manager;
}

WebRequestCache *WebRequest::cacheManager() const
{

    return d->m_cacheManager;
}

bool WebRequest::cacheUsed() const
{

    return d->m_cacheUsed;
}

qint64 WebRequest::expirationSeconds() const
{

    return d->m_expirationSeconds;
}

QString WebRequest::loadingText() const
{

    return d->loadingText;
}

bool WebRequest::useUtf8() const
{

    return d->useUtf8;
}

Rest::Headers WebRequest::headers() const
{
    return d->headers;
}

AbstractData *WebRequest::data() const
{
    return d->data;
}

AbstractResponse *WebRequest::response() const
{
    return d->response;
}

ExpireTime *WebRequest::expireTime() const
{
    return d->expireTime;
}

void WebRequest::storeInCache(QDateTime expire, QByteArray &buffer)
{
    QString cid = generateCacheId();

    if (d->response->storeCacheAsFile()) {
        buffer = cacheManager()->setValue(cid, buffer, expire).toUtf8();
    } else {
        cacheManager()->setValue(cid, QString(buffer), expire);
    }
}

bool WebRequest::retriveFromCache(const QString &key)
{
    if (d->response->storeCacheAsFile()) {
        QString fn = cacheManager()->fileName(key);
        if (fn != QString()) {
            d->response->processReply(fn.toUtf8());
            return true;
        }
    } else {
        QString cache = cacheManager()->value(key);
        if (cache != QString()) {
            d->response->processReply(cache.toLocal8Bit());
            return true;
        }
    }

    return false;
}

QString WebRequest::generateCacheId()
{
    if (d->m_cacheId != QString())
        return d->m_cacheId;

    if (d->m_includeDataInCacheId && d->data) {
        return d->m_url.toString()
                + "/" + d->data->generateCacheKey();
    }
    return d->m_url.toString();
}

void WebRequest::finished()
{
    if (!d->response)
        return;

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    auto rawBuffer = reply->readAll();

    auto headers = reply->rawHeaderList();
    foreach (auto h, headers) {
        d->response->setHeader(h, reply->rawHeader(h));
        qDebug() << "Header set:" << h << ":"<<reply->rawHeader(h);
    }

    auto buffer = codec->toUnicode(rawBuffer);

    if (reply->error() != QNetworkReply::NoError) {
        if (d->response)
            emit d->response->error(reply->error(), reply->errorString());

        emit replyError(reply->error(), reply->errorString());
        manager()->removeCall(this);
        return;
    }

    if (d->m_useCache) {
        QDateTime expire = QDateTime::currentDateTime();

        if (d->expireTime) {
            expire = expire.addSecs(d->expireTime->totalSecs());
        } else {
            QString cacheControl = QString(reply->rawHeader("cache-control"));
            QRegularExpression r("max-age=(\\d+)");
            QRegularExpressionMatch m = r.match(cacheControl);
            if (m.hasMatch()) {
                expire = expire.addSecs(m.captured(1).toInt());
            }
        }
        storeInCache(expire, rawBuffer);
    }

    d->response->processReply(rawBuffer);

    d->calls--;
    setIsBusy(d->calls);
    manager()->removeCall(this);
}

void WebRequest::setUrl(QUrl url)
{

    if (d->m_url == url)
        return;

    d->m_url = url;
    emit urlChanged(d->m_url);
}

void WebRequest::setIsBusy(bool isBusy)
{

    if (d->m_isBusy == isBusy)
        return;

    d->m_isBusy = isBusy;
    emit isBusyChanged(d->m_isBusy);
}

void WebRequest::setCacheId(QString cacheId)
{

    if (d->m_cacheId == cacheId)
        return;

    d->m_cacheId = cacheId;
    emit cacheIdChanged(d->m_cacheId);
}

void WebRequest::setUseCache(bool useCache)
{

    if (d->m_useCache == useCache)
        return;

    d->m_useCache = useCache;
    emit useCacheChanged(d->m_useCache);
}

void WebRequest::setIncludeDataInCacheId(bool includeDataInCacheId)
{

    if (d->m_includeDataInCacheId == includeDataInCacheId)
        return;

    d->m_includeDataInCacheId = includeDataInCacheId;
    emit includeDataInCacheIdChanged(d->m_includeDataInCacheId);
}

void WebRequest::setManager(WebRequestManager *manager)
{

    if (d->m_manager == manager)
        return;

    d->m_manager = manager;
    emit managerChanged(manager);
}

void WebRequest::setCacheManager(WebRequestCache *cacheManager)
{

    if (d->m_cacheManager == cacheManager)
        return;

    d->m_cacheManager = cacheManager;
    emit cacheManagerChanged(cacheManager);
}

void WebRequest::setExpirationSeconds(qint64 expirationSeconds)
{

    if (d->m_expirationSeconds == expirationSeconds)
        return;

    d->m_expirationSeconds = expirationSeconds;
    emit expirationSecondsChanged(expirationSeconds);
}

void WebRequest::setLoadingText(QString loadingText)
{

    if (d->loadingText == loadingText)
        return;

    d->loadingText = loadingText;
    emit loadingTextChanged(d->loadingText);
}

void WebRequest::setUseUtf8(bool useUtf8)
{

    if (d->useUtf8 == useUtf8)
        return;

    d->useUtf8 = useUtf8;
    emit useUtf8Changed(d->useUtf8);
}

void WebRequest::setHeaders(Rest::Headers headers)
{
    if (d->headers == headers)
        return;

    d->headers = headers;
    emit headersChanged(headers);
}

void WebRequest::setData(AbstractData *data)
{
    if (d->data == data)
        return;

    data->setD(d);
    d->data = data;
    emit dataChanged(data);
}

void WebRequest::setResponse(AbstractResponse *response)
{
    if (d->response == response)
        return;

    response->setD(d);
    d->response = response;
    emit responseChanged(response);
}

void WebRequest::setExpireTime(ExpireTime *expireTime)
{
    if (d->expireTime == expireTime)
        return;

    d->expireTime = expireTime;
    emit expireTimeChanged(expireTime);
}

void WebRequest::setCacheUsed(bool cacheUsed)
{

    if (d->m_cacheUsed == cacheUsed)
        return;

    d->m_cacheUsed = cacheUsed;
    emit cacheUsedChanged(cacheUsed);
}
