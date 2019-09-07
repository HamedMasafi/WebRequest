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
#include "webrequest_p.h"
#include "webrequestcache.h"
#include "webrequestmanager.h"

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

WebRequestPrivate::WebRequestPrivate(WebRequest *parent) : q_ptr(parent),
    calls(0), m_isBusy(false), m_cacheId(QString()),
    m_useCache(true), m_data(QVariantMap()), m_includeDataInCacheId(false),
    m_actualCacheId(QString()), m_expirationSeconds(0),
    m_method(WebRequest::Post), useUtf8(true)
{
//    net = new QNetworkAccessManager(parent);
//    net->setObjectName("net");
}

WebRequest::WebRequest(QObject *parent)
    : QObject(parent), d_ptr(new WebRequestPrivate(this))
{
//    Q_D(WebRequest);
//    connect(d->net, &QNetworkAccessManager::finished, this, &WebRequest::on_net_finished);

    setManager(WebRequestManager::instance());
    setCacheManager(WebRequestCache::instance());
}

WebRequest::~WebRequest()
{
    Q_D(WebRequest);

    if (d->calls)
        for (int i = 0; i < d->calls; ++i)
            manager()->removeCall(this);
    delete d;
}

void WebRequest::sendToServer(QVariantMap props, bool cache)
{
    Q_D(WebRequest);
    QByteArray postData = "";
    QUrlQuery queryData;
    beforeSend(props);
    if (props.count()) {
        foreach (auto key, props.keys()) {
            if (postData != "")
                postData.append("&");

            queryData.addQueryItem(key, props.value(key).toString());
            postData.append(key + "=" + props.value(key).toString());
        }
    }
    postData = queryData.toString(QUrl::FullyEncoded).toUtf8();

    if (d->m_useCache && cache) {
        QString id = generateCacheId(props);
        if (retriveFromCache(id)) {
            setCacheUsed(true);
            return;
        }
    }
    d->calls++;
    setCacheUsed(false);

    QNetworkRequest request;
    manager()->addCall(this);
    setIsBusy(true);

    if (!d->files.count())
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/x-www-form-urlencoded");

    request.setUrl(d->m_url);
    beforeSend(request);
/*
    QByteArray postData = "";
    foreach (auto key, props.keys()) {
        if (postData != "")
            postData.append("&");

        postData.append(key + "=" + props.value(key).toString());
    }

    calls.insert(requestId, callBack);
    net->post(request, postData);
*/

    QNetworkReply *reply = nullptr;
    if (d->files.count()) {
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QMap<QString, QString>::iterator i;
        for (i = d->files.begin(); i != d->files.end(); ++i) {
            QHttpPart filePart;
            QFile *f = new QFile(i.value());
            if (!f->exists())
                return;

            filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
            QString t = QString("Content-Disposition: form-data; name=\"%1\"; filename=\"%2\"")
                    .arg(i.key()).arg(i.value());
            filePart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
            qDebug() << "form-data; name=\"" + i.key() + "\"";
            f->open(QIODevice::ReadOnly);
            filePart.setBodyDevice(f);
            multiPart->append(filePart);
            f->setParent(multiPart);
        }
        QMap<QString, QVariant>::iterator data_it;
        for (data_it = d->m_data.begin(); data_it != d->m_data.end(); ++data_it) {
            QHttpPart textPart;

//            filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
            QString t = QString("Content-Disposition: form-data; name=\"%1\"")
                    .arg(data_it.key());
            textPart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
            textPart.setBody(data_it.value().toString().toLocal8Bit());
            multiPart->append(textPart);
        }

        reply = manager()->request(request, multiPart);
//                d->net->post(request, multiPart);
        multiPart->setParent(reply);
    } else {
        if (props.count()) {
            if (d->m_method == Get) {
                QUrl url = request.url();
                url.setQuery(postData);
                request.setUrl(url);
                //            d->net->get(request);
                reply = manager()->request(request);
            } else {
                //            d->net->post(request, postData);
                reply = manager()->request(request, postData);
            }
        } else {
            if (d->m_method == Get)
                //            d->net->get(request);
                reply = manager()->request(request);
            else
                //            d->net->post(request, QByteArray());
                reply = manager()->request(request, QByteArray());
        }
    }
    connect(reply, &QNetworkReply::finished, this, &WebRequest::finished);
}

void WebRequest::send(bool cache)
{
    Q_D(WebRequest);
    if (d->m_data != QVariantMap()) {
        sendToServer(d->m_data);
        return;
    }
    QVariantMap map;
    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            map.insert(prop.name(), prop.read(this));
    }
    sendToServer(map, cache);
}

void WebRequest::sendSync(bool cache)
{
    QEventLoop eventLoop;
    connect(this, &WebRequest::rawDataRecived, &eventLoop, &QEventLoop::quit);
    connect(this, &WebRequest::replyError, &eventLoop, &QEventLoop::quit);
    send(cache);
    eventLoop.exec();
}

QUrl WebRequest::url() const
{
    Q_D(const WebRequest);
    return d->m_url;
}

bool WebRequest::isBusy() const
{
    Q_D(const WebRequest);
    return d->m_isBusy;
}

QString WebRequest::cacheId() const
{
    Q_D(const WebRequest);
    return d->m_cacheId;
}

bool WebRequest::useCache() const
{
    Q_D(const WebRequest);
    return d->m_useCache;
}

QVariantMap WebRequest::data() const
{
    Q_D(const WebRequest);
    return d->m_data;
}

bool WebRequest::includeDataInCacheId() const
{
    Q_D(const WebRequest);
    return d->m_includeDataInCacheId;
}

WebRequest::Method WebRequest::method() const
{
    Q_D(const WebRequest);
    return d->m_method;
}

WebRequestManager *WebRequest::manager() const
{
    Q_D(const WebRequest);
    return d->m_manager;
}

WebRequestCache *WebRequest::cacheManager() const
{
    Q_D(const WebRequest);
    return d->m_cacheManager;
}

bool WebRequest::cacheUsed() const
{
    Q_D(const WebRequest);
    return d->m_cacheUsed;
}

qint64 WebRequest::expirationSeconds() const
{
    Q_D(const WebRequest);
    return d->m_expirationSeconds;
}

QString WebRequest::loadingText() const
{
    Q_D(const WebRequest);
    return d->loadingText;
}

bool WebRequest::useUtf8() const
{
    Q_D(const WebRequest);
    return d->useUtf8;
}

void WebRequest::addFile(const QString &name, const QString &path)
{
    Q_D(WebRequest);
    d->files.insert(name, path);
}

void WebRequest::addData(const QString &name, const QVariant &value)
{
    Q_D(WebRequest);
    d->m_data.insert(name, value);
}

void WebRequest::beforeSend(QVariantMap &map)
{
    Q_UNUSED(map);
}

void WebRequest::beforeSend(QNetworkRequest &request)
{
    Q_UNUSED(request);
}

void WebRequest::processResponse(QByteArray buffer)
{
    rawDataRecived(buffer);
}

void WebRequest::storeInCache(QDateTime expire, QByteArray buffer)
{
    QString cid = cacheId();
    if (cid.isEmpty())
        cid = url().toString().replace("'", "");
    bool ok = cacheManager()->setValue(cid, QString(buffer), expire);
    if (!ok)
        qWarning() << "Unable to store cache";
}

bool WebRequest::retriveFromCache(const QString &key)
{
    Q_D(WebRequest);

    if (d->useUtf8) {
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString cache = codec->toUnicode(cacheManager()->value(key).toUtf8());
        if (cache != QString()) {
            processResponse(cache.toUtf8());
            return true;
        }
    } else {
        QString cache = cacheManager()->value(key);
        if (cache != QString()) {
            processResponse(cache.toLocal8Bit());
            return true;
        }
    }
    return false;
}

QString WebRequest::actualCacheId() const
{
    Q_D(const WebRequest);
    return d->m_actualCacheId;
}

QString WebRequest::generateCacheId(QVariantMap props)
{
    Q_D(WebRequest);

    QString postData = "";
    if (props.count()) {
        foreach (auto key, props.keys()) {
            if (postData != "")
                postData.append("&");

            postData.append(key + "=" + props.value(key).toString());
        }
    }
    if (d->m_actualCacheId == "") {
        if (d->m_cacheId != QString()) {
            d->m_actualCacheId = d->m_cacheId;
        } else {
            if (d->m_includeDataInCacheId)
                d->m_actualCacheId = d->m_url.toString() + "?" + postData;
            else
                d->m_actualCacheId = d->m_url.toString();
        }
    }

    return d->m_actualCacheId;
}

void WebRequest::finished()
{
    Q_D(WebRequest);
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    auto rawBuffer = reply->readAll();
    auto buffer = codec->toUnicode(rawBuffer);
    qDebug() << "buffer is" << buffer;
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error" << reply->error() << reply->errorString();
        qWarning() << buffer;
        emit replyError(reply->error(), reply->errorString());
        manager()->removeCall(this);
        return;
    }

    if (d->m_useCache) {
        QDateTime expire = QDateTime::currentDateTime();

        if (d->m_expirationSeconds) {
            expire = expire.addSecs(d->m_expirationSeconds);
        } else {
            QString cacheControl = QString(reply->rawHeader("cache-control"));
            QRegularExpression r("max-age=(\\d+)");
            QRegularExpressionMatch m = r.match(cacheControl);
            if (m.hasMatch()) {
                expire = expire.addSecs(m.captured(1).toInt());
            }
        }
        if (d->useUtf8)
            storeInCache(expire, buffer.toUtf8());
        else
            storeInCache(expire, rawBuffer);
    }
    if (d->useUtf8)
        processResponse(buffer.toUtf8());
    else
        processResponse(rawBuffer);

    d->calls--;
    setIsBusy(d->calls);
    manager()->removeCall(this);
}

void WebRequest::setUrl(QUrl url)
{
    Q_D(WebRequest);
    if (d->m_url == url)
        return;

    d->m_url = url;
    emit urlChanged(d->m_url);
}

void WebRequest::setIsBusy(bool isBusy)
{
    Q_D(WebRequest);
    if (d->m_isBusy == isBusy)
        return;

    d->m_isBusy = isBusy;
    emit isBusyChanged(d->m_isBusy);
}

void WebRequest::setCacheId(QString cacheId)
{
    Q_D(WebRequest);
    if (d->m_cacheId == cacheId)
        return;

    d->m_actualCacheId = "";
    d->m_cacheId = cacheId;
    emit cacheIdChanged(d->m_cacheId);
}

void WebRequest::setUseCache(bool useCache)
{
    Q_D(WebRequest);
    if (d->m_useCache == useCache)
        return;

    d->m_useCache = useCache;
    emit useCacheChanged(d->m_useCache);
}

void WebRequest::setData(QVariantMap data)
{
    Q_D(WebRequest);
    if (d->m_data == data)
        return;

    d->m_actualCacheId = "";
    d->m_data = data;
    emit dataChanged(d->m_data);
}

void WebRequest::setIncludeDataInCacheId(bool includeDataInCacheId)
{
    Q_D(WebRequest);
    if (d->m_includeDataInCacheId == includeDataInCacheId)
        return;

    d->m_actualCacheId = "";
    d->m_includeDataInCacheId = includeDataInCacheId;
    emit includeDataInCacheIdChanged(d->m_includeDataInCacheId);
}

void WebRequest::setMethod(WebRequest::Method method)
{
    Q_D(WebRequest);
    if (d->m_method == method)
        return;

    d->m_method = method;
    emit methodChanged(d->m_method);
}

void WebRequest::setManager(WebRequestManager *manager)
{
    Q_D(WebRequest);
    if (d->m_manager == manager)
        return;

    d->m_manager = manager;
    emit managerChanged(manager);
}

void WebRequest::setCacheManager(WebRequestCache *cacheManager)
{
    Q_D(WebRequest);
    if (d->m_cacheManager == cacheManager)
        return;

    d->m_cacheManager = cacheManager;
    emit cacheManagerChanged(cacheManager);
}

void WebRequest::setExpirationSeconds(qint64 expirationSeconds)
{
    Q_D(WebRequest);
    if (d->m_expirationSeconds == expirationSeconds)
        return;

    d->m_expirationSeconds = expirationSeconds;
    emit expirationSecondsChanged(expirationSeconds);
}

void WebRequest::setLoadingText(QString loadingText)
{
    Q_D(WebRequest);
    if (d->loadingText == loadingText)
        return;

    d->loadingText = loadingText;
    emit loadingTextChanged(d->loadingText);
}

void WebRequest::setUseUtf8(bool useUtf8)
{
    Q_D(WebRequest);
    if (d->useUtf8 == useUtf8)
        return;

    d->useUtf8 = useUtf8;
    emit useUtf8Changed(d->useUtf8);
}

void WebRequest::setCacheUsed(bool cacheUsed)
{
    Q_D(WebRequest);
    if (d->m_cacheUsed == cacheUsed)
        return;

    d->m_cacheUsed = cacheUsed;
    emit cacheUsedChanged(cacheUsed);
}
