    #ifndef FORMPOSTDATA_H
#define FORMPOSTDATA_H

#include "abstractdata.h"
#include "global.h"

#include <QQmlListProperty>
#include <QVariantMap>

class FileItem;
class FormPostData : public AbstractData
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Pair> data READ data DESIGNABLE false)
//    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data");

    QList<Pair*> m_data;
public:
    FormPostData(QObject *parent = nullptr);

    QQmlListProperty<Pair> data();
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void addData2(const QString &name, const QVariant &value);
    static void addData(QQmlListProperty<Pair> *property, Pair *pair);
    static Pair *dataAt(QQmlListProperty<Pair> *property, int index);
    static void clearData(QQmlListProperty<Pair> *property);
    static int dataCount(QQmlListProperty<Pair> *property);

private:
    void processWithFiles(QNetworkRequest &request, QList<Pair *> data, QList<FileItem*> files);
    void processFormData(QNetworkRequest &request, QList<Pair *> data);
};

#endif // FORMPOSTDATA_H
