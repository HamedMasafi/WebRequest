#include "stringresponse.h"

StringResponse::StringResponse(QObject *parent) : AbstractResponse(parent)
{

}

void StringResponse::processReply(const QByteArray &buffer)
{
    emit finished(QString(buffer));
}
