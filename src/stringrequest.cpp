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

#include "stringrequest.h"
#include "response/stringresponse.h"

KAJ_REST_BEGIN_NAMESPACE

StringRequest::StringRequest(QObject *parent) : WebRequest(parent)
{
    auto _response = new StringResponse(this);
    connect(_response, &StringResponse::finished, this, &StringRequest::finished);
    setResponse(_response);
}

KAJ_REST_END_NAMESPACE
