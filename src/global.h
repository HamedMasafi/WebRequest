#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>
#include <QString>
#include <QVariantMap>

class Pair;
namespace Rest {

template<class T>
using Callback = std::function<void(T)>;

using ErrorCallback = std::function<void(int, QString)>;
using Headers = QVariantMap;
using Files = QMap<QString, QString>;
using Data = QMap<QString, QByteArray>;
using Header = Pair;

}

#endif // GLOBAL_H
