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

#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include <QSharedDataPointer>

class QNetworkRequest;
class QNetworkReply;

class WebRequestPrivate;
class WebRequestManager;
class WebRequestCache;
class WebRequest : public QObject
{
    Q_OBJECT

    QExplicitlySharedDataPointer<WebRequestPrivate> d;

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged STORED false)
    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged STORED false)
    Q_PROPERTY(QString cacheId READ cacheId WRITE setCacheId NOTIFY cacheIdChanged STORED false)
    Q_PROPERTY(bool useCache READ useCache WRITE setUseCache NOTIFY useCacheChanged STORED false)
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(bool includeDataInCacheId READ includeDataInCacheId WRITE setIncludeDataInCacheId NOTIFY includeDataInCacheIdChanged)
    Q_PROPERTY(Method method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(WebRequestManager* manager READ manager WRITE setManager NOTIFY managerChanged)
    Q_PROPERTY(WebRequestCache* cacheManager READ cacheManager WRITE setCacheManager NOTIFY cacheManagerChanged)
    Q_PROPERTY(bool cacheUsed READ cacheUsed WRITE setCacheUsed NOTIFY cacheUsedChanged)
    Q_PROPERTY(qint64 expirationSeconds READ expirationSeconds WRITE setExpirationSeconds NOTIFY expirationSecondsChanged)
    Q_PROPERTY(QString loadingText READ loadingText WRITE setLoadingText NOTIFY loadingTextChanged)
    Q_PROPERTY(bool useUtf8 READ useUtf8 WRITE setUseUtf8 NOTIFY useUtf8Changed)

public:
    enum Method {
        Get,
        Post
    };
    Q_ENUMS(Method)

    explicit WebRequest(QObject *parent = nullptr);
    ~WebRequest();

    QUrl url() const;
    bool isBusy() const;
    QString cacheId() const;
    bool useCache() const;
    QVariantMap data() const;
    bool includeDataInCacheId() const;
    Method method() const;
    WebRequestManager *manager() const;
    WebRequestCache *cacheManager() const;
    bool cacheUsed() const;
    qint64 expirationSeconds() const;
    QString loadingText() const;
    bool useUtf8() const;

    void addFile(const QString &name, const QString &path);
    void addData(const QString &name, const QVariant &value);


protected:
    void sendToServer(QVariantMap props = QMap<QString, QVariant>(), bool cache = true);
    virtual void processResponse(QByteArray buffer);
    virtual void beforeSend(QVariantMap &map);
    virtual void beforeSend(QNetworkRequest &request);
    virtual void storeInCache(QDateTime expire, QByteArray buffer);
    virtual bool retriveFromCache(const QString &key);
    QString actualCacheId() const;
    QString generateCacheId(QVariantMap props);
    void setCacheUsed(bool cacheUsed);

signals:
    void replyError(const int &code, const QString &descript);
    void urlChanged(QUrl url);
    void isBusyChanged(bool isBusy);
    void rawDataRecived(QString data);
    void cacheIdChanged(QString cacheId);
    void useCacheChanged(bool useCache);
    void dataChanged(QVariantMap data);
    void includeDataInCacheIdChanged(bool includeDataInCacheId);
    void methodChanged(Method method);
    void managerChanged(WebRequestManager *manager);
    void cacheManagerChanged(WebRequestCache *cacheManager);
    void cacheUsedChanged(bool cacheUsed);
    void expirationSecondsChanged(qint64 expirationSeconds);
    void loadingTextChanged(QString loadingText);

    void useUtf8Changed(bool useUtf8);

private slots:
    void finished();

public slots:
    void send(bool cache = true);
    void sendSync(bool cache = true);
    void setUrl(QUrl url);
    void setIsBusy(bool isBusy);
    void setCacheId(QString cacheId);
    void setUseCache(bool useCache);
    void setData(QVariantMap data);
    void setIncludeDataInCacheId(bool includeDataInCacheId);
    void setMethod(Method method);
    void setManager(WebRequestManager *manager);
    void setCacheManager(WebRequestCache *cacheManager);
    void setExpirationSeconds(qint64 expirationSeconds);
    void setLoadingText(QString loadingText);
    void setUseUtf8(bool useUtf8);
};

#endif // WEBREQUEST_H
