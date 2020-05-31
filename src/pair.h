#ifndef HEADER_H
#define HEADER_H

#include <QObject>

class Pair : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

    QString m_name;
    QString m_value;

public:
    explicit Pair(QObject *parent = nullptr);

    QString name() const;
    QString value() const;

public slots:
    void setName(QString name);
    void setValue(QString value);

signals:
    void nameChanged(QString name);
    void valueChanged(QString value);
};

#endif // HEADER_H
