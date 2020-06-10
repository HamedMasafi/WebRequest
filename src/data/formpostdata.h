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

#ifndef FORMPOSTDATA_H
#define FORMPOSTDATA_H

#include "abstractdata.h"
#include "global.h"

#include <QVariantMap>

KAJ_REST_BEGIN_NAMESPACE

class FormPostData : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)

    QVariantMap m_data;
    Rest::Files m_files;

public:
    FormPostData(QObject *parent = nullptr);

    QVariantMap data() const;
    Rest::Files files() const;
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void addData(const QString &name, const QVariant &value);
    void setData(QVariantMap data);
    void setFiles(Rest::Files files);

signals:
    void dataChanged(QVariantMap data);
    void filesChanged(Rest::Files files);
};

KAJ_REST_END_NAMESPACE

#endif // FORMPOSTDATA_H
