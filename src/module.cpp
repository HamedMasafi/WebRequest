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

#include "imagerequest.h"
#include "jsonrequest.h"
#include "module.h"
#include "stringrequest.h"
#include "variantrequest.h"
#include "webrequest.h"
#include "webrequestcache.h"
#include "webrequestmanager.h"

#include "data/abstractdata.h"
#include "data/formpostdata.h"
#include "data/filepostdata.h"
#include "data/jsonpostdata.h"
#include "data/querystring.h"

#include "response/abstractresponse.h"
#include "response/stringresponse.h"
#include "response/jsonresponse.h"
#include "response/imageresponse.h"

#include <QtQml>
#include <QDebug>
#include <QJSEngine>

#define DECLARE_SINGELTON_METHOD(type) \
static QObject *createSingleton##type(QQmlEngine *, QJSEngine *) \
{ \
    return new type(); \
}

static QObject *createSingletonManager(QQmlEngine *, QJSEngine *)
{
    return WebRequestManager::instance();
}

static QObject *createSingletonCache(QQmlEngine *, QJSEngine *)
{
    return WebRequestCache::instance();
}


void KajModule::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj.Rest"));

    qRegisterMetaType<WebRequestCache*>();
    qRegisterMetaType<WebRequestManager*>();

    //Web request
    qmlRegisterType<WebRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequest");
    qmlRegisterType<StringRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "StringRequest");
    qmlRegisterType<JsonObjectRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonRequest");
    qmlRegisterType<VariantRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "VariantRequest");
    qmlRegisterType<ImageRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ImageRequest");
    qmlRegisterType<WebRequestCache>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "WebRequestCache");
    qmlRegisterType<WebRequestManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManager");
    qmlRegisterSingletonType<WebRequestCache>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "WebRequestCacheInstance", createSingletonCache);
    qmlRegisterSingletonType<WebRequestManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManagerInstance", createSingletonManager);

    //form data
    qmlRegisterType<FormPostData>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FormPostData");
    qmlRegisterType<FilePostData>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FilePostData");
    qmlRegisterType<JsonPostData>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonPostData");
    qmlRegisterType<QueryString>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "QueryString");
    qmlRegisterUncreatableType<AbstractData>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "AbstractData", "Abstract class");

    //response
    qmlRegisterType<StringResponse>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "StringResponse");
    qmlRegisterType<ImageResponse>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ImageResponse");
    qmlRegisterType<JsonResponse>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonResponse");
    qmlRegisterUncreatableType<AbstractResponse>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "AbstractResponse", "Abstract class");

}

void KajModule::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
