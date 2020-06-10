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

#ifndef FILEPOSTDATA_H
#define FILEPOSTDATA_H

#include "formpostdata.h"
#include "global.h"

#include <QMap>

KAJ_REST_BEGIN_NAMESPACE

class FilePostData : public FormPostData
{
    Q_OBJECT

    Q_PROPERTY(Rest::Files files READ files WRITE setFiles NOTIFY filesChanged)
    Rest::Files m_files;

public:
    FilePostData(WebRequest *parent = nullptr);
    Rest::Files files() const;
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void setFiles(Rest::Files files);
    void addFile(const QString &name, const QUrl &file);
    void addFile(const QString &name, const QString &path);

signals:
    void filesChanged(Rest::Files files);

};

KAJ_REST_END_NAMESPACE

#endif // FILEPOSTDATA_H
