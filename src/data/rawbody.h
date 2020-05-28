#ifndef RAWBODY_H
#define RAWBODY_H

#include "abstractdata.h"

class RawBody : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)

    QString m_data;

public:
    RawBody(QObject *parent = nullptr);
    QString data() const;
    QNetworkReply *send(QNetworkRequest &request);

public slots:
    void setData(QString data);
signals:
    void dataChanged(QString data);
};

#endif // RAWBODY_H
