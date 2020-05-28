#ifndef EXPIRETIME_H
#define EXPIRETIME_H

#include <QObject>

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
    operator qlonglong();

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

#endif // EXPIRETIME_H
