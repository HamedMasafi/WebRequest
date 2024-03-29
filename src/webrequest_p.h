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

#ifndef WEBREQUEST_P_H
#define WEBREQUEST_P_H

#include "webrequest.h"

#include <QSharedData>

class QNetworkAccessManager;

KAJ_REST_BEGIN_NAMESPACE

class AbstractData;
class AbstractResponse;
class WebRequest;
class ExpireTime;
class WebRequestPrivate : public QSharedData
{

public:
    WebRequestPrivate();

    int calls;
    QUrl m_url;
    bool m_isBusy;
    QString m_cacheId;
//    bool m_useCache;
    bool m_includeDataInCacheId;
    bool m_cacheUsed;
    qint64 m_expirationSeconds;
    QString loadingText;
    WebRequestManager *m_manager;
    WebRequestCache *m_cacheManager;
    Rest::Files files;
    bool useUtf8;
    Rest::Headers headers;
    AbstractData *data;
    AbstractResponse *response;
    ExpireTime* expireTime;
    WebRequest::Method method;
    WebRequest::CacheMode cacheMode;
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUEST_P_H
