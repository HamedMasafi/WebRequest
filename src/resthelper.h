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

#ifndef REST_H
#define REST_H

#include <QEventLoop>
#include <QMap>
#include <QObject>
#include <QUrl>

#include "response/abstractresponse.h"
#include "data/rawbody.h"
#include "data/jsonpostdata.h"
#include "data/filepostdata.h"

#include "global.h"

KAJ_REST_BEGIN_NAMESPACE

using namespace Rest;
class Helper : public QObject
{
    Q_OBJECT

public:
    explicit Helper(QObject *parent = nullptr);

    static void request(const QUrl &url, Rest::Callback<QString> cb,
                        ErrorCallback ecb = {},
                        Headers headers = Rest::Headers());
    static void request(const QUrl &url, Rest::Callback<QJsonValue> cb,
                        ErrorCallback ecb = {},
                        Headers headers = Rest::Headers());

    static void request(const QUrl &url,
                        QJsonValue json,
                        Callback<QJsonValue> cb,
                        ErrorCallback ecb = {},
                        Headers headers = Rest::Headers());
private:
};

class AbstractResponse;
class StringResponse;
class RawBody;

template<class _Data, class _Response>
class RestHelperBlocker;

template <class T>
struct DataType {
    using Type = void;
    static constexpr bool supports = false;
};

template <>
struct DataType<QString> {
    using Type = RawBody;
    static constexpr bool supports = true;
};

template <>
struct DataType<QJsonValue> {
    using Type = JsonPostData;
    static constexpr bool supports = true;
};
template <>
struct DataType<QJsonObject> {
    using Type = JsonPostData;
    static constexpr bool supports = true;
};
template <>
struct DataType<QJsonArray> {
    using Type = JsonPostData;
    static constexpr bool supports = true;
};
template<class _Data = AbstractData, class _Response = AbstractResponse>
class RestHelper
{
    _Data *_data{nullptr};
    Rest::Callback<_Response> _cb{};
    QMap<QByteArray, QByteArray> _headers;
    ErrorCallback _error;
    QUrl _url;
    WebRequest::CacheMode _cacheMode;
public:
    RestHelper() {}
    RestHelper(QUrl url)
        : _url{url}
    {}

    template<class T>
    constexpr RestHelper<T, _Response> setData(T *data)
    {
        static_assert(DataType<T>::supports);
        static_assert(std::is_same<_Data, AbstractData>().value || std::is_same<T, _Data>().value);
        auto d = new typename DataType<T>::Type;
        d->setData(data);
        _data = d;
        RestHelper<T, _Response> ret;
        ret._data = d;
        return ret;
    }

    /*template<class T>
    constexpr RestHelper<T, _Response> setData(const T &d)
    {
        static_assert(std::is_same<_Data, AbstractData>().value || std::is_same<T, _Data>().value);
        return RestHelper<T, _Response>();
    }*/

    constexpr RestHelper<RawBody, _Response> setData(const QString &d)
    {
        static_assert(std::is_same<_Data, AbstractData>().value || std::is_same<RawBody, _Data>().value);

        _data = new RawBody;
        _data->setData(d);
        return RestHelper<RawBody, _Response>();
    }

    constexpr RestHelper<_Data, _Response> error(const ErrorCallback &eb)
    {
        _error = eb;
        return *this;
    }

    constexpr RestHelper<_Data, _Response> header(const QByteArray &name, const QByteArray &value)
    {
        _headers.insert(name, value);
        return *this;
    }
    constexpr RestHelper<_Data, _Response> setCacheMode(WebRequest::CacheMode mode)
    {
        _cacheMode = mode;
        return *this;
    }
    constexpr RestHelper<FilePostData, _Response> addFile(const QString &name, const QString &path)
    {
        if constexpr (std::is_same<_Data, FilePostData>().value) {
            _data->addFile(name, path);
            return *this;
        } else {
            RestHelper<FilePostData, _Response> ret;
            auto data = new FilePostData;
            data->addFile(name, path);
            ret._data = data;
            return ret;
        }
    }

    template<class T>
    constexpr RestHelper<_Data, T> then(Rest::Callback<T> cb)
    {
        RestHelper<_Data, T> ret;
        ret._cb = cb;
        return RestHelper<_Data, T>();
    }

    void send() {
        auto r = new WebRequest;
        auto response = new _Response(r);

        r->setData(_data);
        r->setCacheMode(_cacheMode);

        QObject::connect(response, &_Response::finished, _cb);
        QObject::connect(response, &_Response::error, _error);
        QObject::connect(response, &_Response::finished, r, &QObject::deleteLater);
        QObject::connect(response, &_Response::error, r, &QObject::deleteLater);
        r->setResponse(response);
        r->setUrl(_url);
        r->send();
    }

    //RestHelperBlocker<_Data, _Response> block() {}
};
template<class _Data = AbstractData, class _Response = AbstractResponse>
class RestHelperBlocker : RestHelper<_Data, _Response>
{
    _Response send() {
        QEventLoop loop;
//        connect()
        RestHelper<_Data, _Response>::send();
    }
};


KAJ_REST_END_NAMESPACE

#endif // REST_H
