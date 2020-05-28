    #ifndef FORMPOSTDATA_H
#define FORMPOSTDATA_H

#include "objectdata.h"

#include <QVariantMap>

class FormPostData : public ObjectData
{
    Q_OBJECT
    typedef QMap<QString, QString> Files;
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)

    QVariantMap m_data;
    Files m_files;

public:
    FormPostData(QObject *parent = nullptr);

    QVariantMap data() const;
    Files files() const;
    QNetworkReply *send(QNetworkRequest &request);



public slots:
    void addData(const QString &name, const QVariant &value);
    void setData(QVariantMap data);
    void setFiles(Files files);

signals:
    void dataChanged(QVariantMap data);
    void filesChanged(Files files);
};

#endif // FORMPOSTDATA_H
