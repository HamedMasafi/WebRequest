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

#ifndef EXPIRETIME_H
#define EXPIRETIME_H

#include <QObject>
#include "global.h"

KAJ_REST_BEGIN_NAMESPACE

class ExpireTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int second READ second WRITE setSecond NOTIFY secondChanged)
    Q_PROPERTY(int minute READ minute WRITE setMinute NOTIFY minuteChanged)
    Q_PROPERTY(int hour READ hour WRITE setHour NOTIFY hourChanged)
    Q_PROPERTY(int day READ day WRITE setDay NOTIFY dayChanged)
    Q_PROPERTY(int month READ month WRITE setMonth NOTIFY monthChanged)

    int m_second;
    int m_minute;
    int m_hour;
    int m_day;
    int m_month;

public:
    explicit ExpireTime(QObject *parent = nullptr);
    operator qint64();
    operator bool();
    qint64 totalSecs();

    int second() const;
    int minute() const;
    int hour() const;
    int day() const;
    int month() const;

public slots:
    void setSecond(int second);
    void setMinute(int minute);
    void setHour(int hour);
    void setDay(int day);
    void setMonth(int month);

signals:
    void secondChanged(int second);
    void minuteChanged(int minute);
    void hourChanged(int hour);
    void dayChanged(int day);
    void monthChanged(int month);
};

KAJ_REST_END_NAMESPACE

#endif // EXPIRETIME_H
