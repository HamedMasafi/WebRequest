#include "expiretime.h"

ExpireTime::ExpireTime(QObject *parent) : QObject(parent)
{

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

ExpireTime::operator qlonglong()
{
    return 0;
}
