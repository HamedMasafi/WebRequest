#include "filepostdata.h"

#include <QHttpPart>
#include <QFile>
#include <QDebug>
#include <QNetworkRequest>

#include "../webrequestmanager.h"
#include "../webrequest_p.h"


FilePostData::FilePostData(WebRequest *parent) : FormPostData(parent)
{

}

FilePostData::Files FilePostData::files() const
{
    return m_files;
}

void FilePostData::setFiles(FilePostData::Files files)
{
    if (m_files == files)
        return;

    m_files = files;
    emit filesChanged(m_files);
}

QNetworkReply *FilePostData::send(QNetworkRequest &request)
{
    if (!m_files.count())
        return FormPostData::send(request);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMap<QString, QString>::iterator i;
    for (i = m_files.begin(); i != m_files.end(); ++i) {
        QHttpPart filePart;
        QFile *f = new QFile(i.value());
        if (!f->exists())
            return nullptr;

        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        QString t = QString("Content-Disposition: form-data; name=\"%1\"; filename=\"%2\"")
                .arg(i.key()).arg(i.value());
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
        qDebug() << "form-data; name=\"" + i.key() + "\"";
        f->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(f);
        multiPart->append(filePart);
        f->setParent(multiPart);
    }
    QMap<QString, QVariant>::iterator data_it;
    auto dt = data();
    for (data_it = dt.begin(); data_it != dt.end(); ++data_it) {
        QHttpPart textPart;

        //            filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        QString t = QString("Content-Disposition: form-data; name=\"%1\"")
                .arg(data_it.key());
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, t);
        textPart.setBody(data_it.value().toString().toLocal8Bit());
        multiPart->append(textPart);
    }


    return d()->m_manager->request(request, multiPart);
}



void FilePostData::addFile(const QString &name, const QUrl &file)
{
    m_files.insert(name, file.toLocalFile());
}

void FilePostData::addFile(const QString &name, const QString &path)
{
    m_files.insert(name, path);
}
