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

#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include "webrequest.h"
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

KAJ_REST_BEGIN_NAMESPACE

class JsonPostData;
class JsonObjectRequest : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QJsonValue data READ data WRITE setData NOTIFY dataChanged)

    JsonPostData *_jsonData;

public:
    explicit JsonObjectRequest(QObject *parent = nullptr);

QJsonValue data() const;

public slots:
void setData(QJsonValue data);

signals:
void finished(QJsonValue data);
void dataChanged(QJsonValue data);
};

KAJ_REST_END_NAMESPACE

#endif // JSONREQUEST_H
