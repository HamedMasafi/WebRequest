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

#ifndef ABSTRACTRESPONSE_H
#define ABSTRACTRESPONSE_H

#include <QObject>
#include "../abstracthelper.h"

KAJ_REST_BEGIN_NAMESPACE

class AbstractResponse : public AbstractHelper
{
    Q_OBJECT
    QMap<QString, QByteArray> _headers;

public:
    explicit AbstractResponse(QObject *parent = nullptr);
    virtual void beforeSend(QNetworkRequest &request);
    virtual void processReply(const QByteArray &buffer) = 0;
    virtual bool storeCacheAsFile() const;

signals:
    void error(const int &code, const QString &descript);

public slots:
    QString header(const QString &headerName) const;

private:
    void setHeader(const QString &name, const QByteArray &value);
    friend class WebRequest;
};

KAJ_REST_END_NAMESPACE

Q_DECLARE_METATYPE(AbstractResponse*)

#endif // ABSTRACTRESPONSE_H
