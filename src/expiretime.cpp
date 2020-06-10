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

#include "expiretime.h"

KAJ_REST_BEGIN_NAMESPACE

ExpireTime::ExpireTime(QObject *parent) : QObject(parent)
{

}

qint64 ExpireTime::totalSecs()
{
    return m_second
            + (m_minute * 60)
            + (m_hour * 60 * 60)
            + (m_day * 60 * 60 * 24)
            + (m_month * 60 * 60 * 24 * 30);
}

ExpireTime::operator bool()
{
    return m_second && m_minute && m_hour && m_day && m_month;
}

int ExpireTime::second() const
{
    return m_second;
}

int ExpireTime::minute() const
{
    return m_minute;
}

int ExpireTime::hour() const
{
    return m_hour;
}

int ExpireTime::day() const
{
    return m_day;
}

int ExpireTime::month() const
{
    return m_month;
}

void ExpireTime::setSecond(int second)
{
    if (m_second == second)
        return;

    m_second = second;
    emit secondChanged(m_second);
}

void ExpireTime::setMinute(int minute)
{
    if (m_minute == minute)
        return;

    m_minute = minute;
    emit minuteChanged(m_minute);
}

void ExpireTime::setHour(int hour)
{
    if (m_hour == hour)
        return;

    m_hour = hour;
    emit hourChanged(m_hour);
}

void ExpireTime::setDay(int day)
{
    if (m_day == day)
        return;

    m_day = day;
    emit dayChanged(m_day);
}

void ExpireTime::setMonth(int month)
{
    if (m_month == month)
        return;

    m_month = month;
    emit monthChanged(m_month);
}

ExpireTime::operator qint64()
{
    return totalSecs();
}

KAJ_REST_END_NAMESPACE
