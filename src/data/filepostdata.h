#ifndef FILEPOSTDATA_H
#define FILEPOSTDATA_H

#include "formpostdata.h"

#include <QMap>

class FilePostData : public FormPostData
{
    Q_OBJECT

    typedef QMap<QString, QString> Files;
    Q_PROPERTY(Files files READ files WRITE setFiles NOTIFY filesChanged)
    Files m_files;

public:
    FilePostData(WebRequest *parent = nullptr);
    Files files() const;
    QNetworkReply *send(QNetworkRequest &request);

public slots:
    void setFiles(Files files);
    void addFile(const QString &name, const QUrl &file);
    void addFile(const QString &name, const QString &path);

signals:
    void filesChanged(Files files);

};

#endif // FILEPOSTDATA_H
