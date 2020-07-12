#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>
#include <QString>
#include <QVariantMap>

#if __cplusplus >= 201703L
#   define KAJ_REST_BEGIN_NAMESPACE
//namespace Kaj::Rest {
#   define KAJ_REST_END_NAMESPACE
//}
#else
#   define KAJ_REST_BEGIN_NAMESPACE
//namespace Kaj { namespace Rest {
#   define KAJ_REST_END_NAMESPACE
//} }
#endif

KAJ_REST_BEGIN_NAMESPACE
namespace Rest {

    template<class T>
    using Callback = std::function<void(T)>;

    using ErrorCallback = std::function<void(int, QString)>;
    using Headers = QVariantMap;
    using Files = QMap<QString, QString>;
    using Data = QMap<QString, QByteArray>;
}

KAJ_REST_END_NAMESPACE

#endif // GLOBAL_H
