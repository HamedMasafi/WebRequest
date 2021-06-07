    #ifndef FORMPOSTDATA_H
#define FORMPOSTDATA_H

#include "abstractdata.h"
#include "global.h"

#ifdef QT_QML_LIB
#include <QQmlListProperty>
#endif

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

#ifdef QT_QML_LIB
    QQmlListProperty<Pair> data();
#endif
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void addData2(const QString &name, const QVariant &value);
#ifdef QT_QML_LIB
    static void addData(QQmlListProperty<Pair> *property, Pair *pair);
    static Pair *dataAt(QQmlListProperty<Pair> *property, int index);
    static void clearData(QQmlListProperty<Pair> *property);
    static int dataCount(QQmlListProperty<Pair> *property);
#endif

private:
    QNetworkReply *processWithFiles(QNetworkRequest &request, QList<Pair *> data, QList<FileItem*> files);
    QNetworkReply *processFormData(QNetworkRequest &request, QList<Pair *> data);
};

#endif // FORMPOSTDATA_H
