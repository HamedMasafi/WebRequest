QT += network sql
CONFIG += c++11

INCLUDEPATH += $$PWD/src

DEFINES += WEB_REQUEST_LIB

SOURCES += \
    $$PWD/src/abstracthelper.cpp \
    $$PWD/src/data/abstractdata.cpp \
    $$PWD/src/data/filepostdata.cpp \
    $$PWD/src/data/formpostdata.cpp \
    $$PWD/src/data/jsonpostdata.cpp \
    $$PWD/src/data/objectdata.cpp \
    $$PWD/src/data/querystring.cpp \
    $$PWD/src/data/rawbody.cpp \
    $$PWD/src/expiretime.cpp \
    $$PWD/src/helper.cpp \
    $$PWD/src/imagerequest.cpp \
    $$PWD/src/jsonrequest.cpp \
    $$PWD/src/kajrestmodule.cpp \
    $$PWD/src/response/abstractresponse.cpp \
    $$PWD/src/response/imageresponse.cpp \
    $$PWD/src/response/jsonresponse.cpp \
    $$PWD/src/response/stringresponse.cpp \
    $$PWD/src/stringrequest.cpp \
    $$PWD/src/variantrequest.cpp \
    $$PWD/src/webrequest.cpp \
    $$PWD/src/webrequestcache.cpp \
    $$PWD/src/webrequestmanager.cpp

HEADERS += \
    $$PWD/src/abstracthelper.h \
    $$PWD/src/data/abstractdata.h \
    $$PWD/src/data/filepostdata.h \
    $$PWD/src/data/formpostdata.h \
    $$PWD/src/data/jsonpostdata.h \
    $$PWD/src/data/objectdata.h \
    $$PWD/src/data/querystring.h \
    $$PWD/src/data/rawbody.h \
    $$PWD/src/expiretime.h \
    $$PWD/src/global.h \
    $$PWD/src/helper.h \
    $$PWD/src/imagerequest.h \
    $$PWD/src/jsonrequest.h \
    $$PWD/src/kajrestmodule.h \
    $$PWD/src/response/abstractresponse.h \
    $$PWD/src/response/imageresponse.h \
    $$PWD/src/response/jsonresponse.h \
    $$PWD/src/response/stringresponse.h \
    $$PWD/src/stringrequest.h \
    $$PWD/src/variantrequest.h \
    $$PWD/src/webrequest.h \
    $$PWD/src/webrequest_p.h \
    $$PWD/src/webrequestcache.h \
    $$PWD/src/webrequestmanager.h \
    $$PWD/src/webrequestmanager_p.h


