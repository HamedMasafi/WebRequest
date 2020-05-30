#ifndef FILEPOSTDATA_H
#define FILEPOSTDATA_H

#include "formpostdata.h"
#include "global.h"

#include <QMap>

class FilePostData : public FormPostData
{
    Q_OBJECT

    Q_PROPERTY(Rest::Files files READ files WRITE setFiles NOTIFY filesChanged)
    Rest::Files m_files;

public:
    FilePostData(WebRequest *parent = nullptr);
    Rest::Files files() const;
    QNetworkReply *send(QNetworkRequest &request) override;
    QString generateCacheKey() override;

public slots:
    void setFiles(Rest::Files files);
    void addFile(const QString &name, const QUrl &file);
    void addFile(const QString &name, const QString &path);

signals:
    void filesChanged(Rest::Files files);

};

#endif // FILEPOSTDATA_H
