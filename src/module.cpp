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

#include "imagerequest.h"
#include "jsonrequest.h"
#include "module.h"
#include "stringrequest.h"
#include "variantrequest.h"
#include "webrequest.h"
#include "webrequestcache.h"
#include "webrequestmanager.h"
#include "expiretime.h"

#include "data/abstractdata.h"
#include "data/formpostdata.h"
#include "data/filepostdata.h"
#include "data/jsonpostdata.h"
#include "data/querystring.h"
#include "data/rawbody.h"
#include "data/objectdata.h"

#include "response/abstractresponse.h"
#include "response/stringresponse.h"
#include "response/jsonresponse.h"
#include "response/imageresponse.h"

#include <QtQml>
#include <QDebug>
#include <QJSEngine>

using namespace Kaj::Rest;

static QObject *createSingletonManager(QQmlEngine *, QJSEngine *)
{
    return WebRequestManager::instance();
}

static QObject *createSingletonCache(QQmlEngine *, QJSEngine *)
{
    return WebRequestCache::instance();
}


void KajRestModule::registerTypes()
{
    qRegisterMetaType<WebRequestCache*>();
    qRegisterMetaType<WebRequestManager*>();

    //Web request
    qmlRegisterType<WebRequest>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequest");
    qmlRegisterType<StringRequest>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "StringRequest");
    qmlRegisterType<JsonObjectRequest>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonRequest");
    qmlRegisterType<VariantRequest>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "VariantRequest");
    qmlRegisterType<ImageRequest>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ImageRequest");
    qmlRegisterType<ExpireTime>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ExpireTime");
    qmlRegisterType<WebRequestCache>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "WebRequestCache");
    qmlRegisterType<WebRequestManager>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManager");
    qmlRegisterSingletonType<WebRequestManager>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManagerInstance", createSingletonManager);
    qmlRegisterSingletonType<WebRequestCache>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestCacheInstance", createSingletonCache);

    //form data
    qmlRegisterType<FormPostData>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FormPostData");
    qmlRegisterType<FilePostData>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FilePostData");
    qmlRegisterType<JsonPostData>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonPostData");
    qmlRegisterType<RawBody>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RawBody");
    qmlRegisterType<QueryString>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "QueryString");
    qmlRegisterUncreatableType<ObjectData>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ObjectData", "Abstract class");
    qmlRegisterUncreatableType<AbstractData>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "AbstractData", "Abstract class");

    //response
    qmlRegisterType<StringResponse>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "StringResponse");
    qmlRegisterType<ImageResponse>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ImageResponse");
    qmlRegisterType<JsonResponse>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonResponse");
    qmlRegisterUncreatableType<AbstractResponse>(KAJ_PACKAGE_NAME, KAJ_VERSION_MAJOR, KAJ_VERSION_MAJOR, "AbstractResponse", "Abstract class");
}

void KajRestModule::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String(KAJ_PACKAGE_NAME));

    registerTypes();
}

void KajRestModule::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
