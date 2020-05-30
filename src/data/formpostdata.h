    #ifndef FORMPOSTDATA_H
#define FORMPOSTDATA_H

#include "abstractdata.h"
#include "global.h"

#include <QVariantMap>

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

#endif // FORMPOSTDATA_H
