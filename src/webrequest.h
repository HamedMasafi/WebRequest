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

#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include <QNetworkReply>
#include <QSharedDataPointer>

#include "global.h"

class QNetworkRequest;
class QNetworkReply;

KAJ_REST_BEGIN_NAMESPACE

class WebRequestPrivate;
class WebRequestManager;
class WebRequestCache;
class AbstractData;
class AbstractResponse;
class ExpireTime;
class WebRequest : public QObject
{
    Q_OBJECT

    QExplicitlySharedDataPointer<WebRequestPrivate> d;

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged STORED false)
    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged STORED false)
    Q_PROPERTY(QString cacheId READ cacheId WRITE setCacheId NOTIFY cacheIdChanged STORED false)
    Q_PROPERTY(bool useCache READ useCache WRITE setUseCache NOTIFY useCacheChanged STORED false)
    Q_PROPERTY(bool includeDataInCacheId READ includeDataInCacheId WRITE setIncludeDataInCacheId NOTIFY includeDataInCacheIdChanged STORED false)
    Q_PROPERTY(WebRequestManager* manager READ manager WRITE setManager NOTIFY managerChanged STORED false)
    Q_PROPERTY(WebRequestCache* cacheManager READ cacheManager WRITE setCacheManager NOTIFY cacheManagerChanged STORED false)
    Q_PROPERTY(AbstractData* data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(AbstractResponse* response READ response WRITE setResponse NOTIFY responseChanged)
    Q_PROPERTY(bool cacheUsed READ cacheUsed WRITE setCacheUsed NOTIFY cacheUsedChanged STORED false)
    Q_PROPERTY(QString loadingText READ loadingText WRITE setLoadingText NOTIFY loadingTextChanged STORED false)
    Q_PROPERTY(bool useUtf8 READ useUtf8 WRITE setUseUtf8 NOTIFY useUtf8Changed STORED false)
    Q_PROPERTY(QVariantMap headers READ headers WRITE setHeaders NOTIFY headersChanged STORED false)
    Q_PROPERTY(qint64 expirationSeconds READ expirationSeconds WRITE setExpirationSeconds NOTIFY expirationSecondsChanged STORED false)
    Q_PROPERTY(ExpireTime* expireTime READ expireTime WRITE setExpireTime NOTIFY expireTimeChanged)
    Q_PROPERTY(Method method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(CacheMode cacheMode READ cacheMode WRITE setCacheMode NOTIFY cacheModeChanged)


public:
    enum Method {
        Auto,
        Get,
        Post
    };
    Q_ENUM(Method);

    enum CacheMode {
        NoCache = 0,
        Restore = 1,
        Store = 2,
        FullCache = Restore | Store
    };

    explicit WebRequest(QObject *parent = nullptr);
    ~WebRequest();

    QUrl url() const;
    bool isBusy() const;
    QString cacheId() const;
    bool useCache() const;
    bool includeDataInCacheId() const;
    WebRequestManager *manager() const;
    WebRequestCache *cacheManager() const;
    bool cacheUsed() const;
    qint64 expirationSeconds() const;
    QString loadingText() const;
    bool useUtf8() const;
    Rest::Headers headers() const;
    AbstractData* data() const;
    AbstractResponse *response() const;

    ExpireTime* expireTime() const;

    Method method() const;
    Q_INVOKABLE void clearCache();
    Q_INVOKABLE void setHeader(const QString &name, const QByteArray &value);

    CacheMode cacheMode() const;
    void setCacheMode(CacheMode newCacheMode);

protected:
    void sendToServer();
    virtual void storeInCache(QDateTime expire, QByteArray &buffer);
    virtual bool retriveFromCache(const QString &key);
    QString actualCacheId() const;
    QString generateCacheId();
    void setCacheUsed(bool cacheUsed);

signals:
    void replyError(const int &code, const QString &descript);
    void urlChanged(QUrl url);
    void isBusyChanged(bool isBusy);
    void cacheIdChanged(QString cacheId);
    void useCacheChanged(bool useCache);
    void includeDataInCacheIdChanged(bool includeDataInCacheId);
    void managerChanged(WebRequestManager *manager);
    void cacheManagerChanged(WebRequestCache *cacheManager);
    void cacheUsedChanged(bool cacheUsed);
    void expirationSecondsChanged(qint64 expirationSeconds);
    void loadingTextChanged(QString loadingText);
    void useUtf8Changed(bool useUtf8);
    void headersChanged(Rest::Headers headers);
    void dataChanged(AbstractData* data);
    void responseChanged(AbstractResponse *response);
    void expireTimeChanged(ExpireTime* expireTime);
    void methodChanged(WebRequest::Method method);

    void cacheModeChanged();

private slots:
    void finished();
    void error(QNetworkReply::NetworkError);
    void removeCall();

public slots:
    Q_DECL_DEPRECATED_X("Use void send()")
    void send(bool cache);
    void send();
    void sendSync();

    void setUrl(QUrl url);
    void setIsBusy(bool isBusy);
    void setCacheId(QString cacheId);
    void setUseCache(bool useCache);
    void setIncludeDataInCacheId(bool includeDataInCacheId);
    void setManager(WebRequestManager *manager);
    void setCacheManager(WebRequestCache *cacheManager);
    void setExpirationSeconds(qint64 expirationSeconds);
    void setLoadingText(QString loadingText);
    void setUseUtf8(bool useUtf8);
    void setHeaders(Rest::Headers headers);
    void setData(AbstractData* data);
    void setResponse(AbstractResponse *response);
    void setExpireTime(ExpireTime* expireTime);
    void setMethod(WebRequest::Method method);
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUEST_H
