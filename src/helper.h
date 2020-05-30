#ifndef REST_H
#define REST_H

#include <QMap>
#include <QObject>
#include <QUrl>

#include "global.h"

class Helper : public QObject
{
    Q_OBJECT

public:
    explicit Helper(QObject *parent = nullptr);

    static void request(const QUrl &url, Rest::Callback<QString> cb,
                        Rest::ErrorCallback ecb = {},
                        Rest::Headers headers = Rest::Headers());
    static void request(const QUrl &url, Rest::Callback<QJsonValue> cb,
                        Rest::ErrorCallback ecb = {},
                        Rest::Headers headers = Rest::Headers());

    static void request(const QUrl &url,
                        QJsonValue json,
                        Rest::Callback<QJsonValue> cb,
                        Rest::ErrorCallback ecb = {},
                        Rest::Headers headers = Rest::Headers());
private:


};

#endif // REST_H
