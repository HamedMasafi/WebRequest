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

#include <QMap>
#include <QObject>
#include <QUrl>

#include "global.h"

KAJ_REST_BEGIN_NAMESPACE

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

KAJ_REST_END_NAMESPACE

#endif // REST_H
