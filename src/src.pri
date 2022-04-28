QT += network sql qml
CONFIG += c++11

INCLUDEPATH += $$PWD

DEFINES += WEB_REQUEST_LIB

SOURCES += \
   $$PWD/abstracthelper.cpp \
   $$PWD/data/abstractdata.cpp \
   $$PWD/data/objectdata.cpp \
   $$PWD/data/rawbody.cpp \
   $$PWD/expiretime.cpp \
   $$PWD/response/abstractresponse.cpp \
   $$PWD/data/querystring.cpp \
   $$PWD/data/filepostdata.cpp \
   $$PWD/data/formpostdata.cpp \
   $$PWD/data/jsonpostdata.cpp \
   $$PWD/response/imageresponse.cpp \
   $$PWD/response/jsonresponse.cpp \
   $$PWD/response/stringresponse.cpp \
   $$PWD/resthelper.cpp \
   $$PWD/stringrequest.cpp \
   $$PWD/variantrequest.cpp \
   $$PWD/webrequest.cpp \
   $$PWD/webrequestbuilder.cpp \
   $$PWD/webrequestcache.cpp \
   $$PWD/imagerequest.cpp \
   $$PWD/jsonrequest.cpp \
   $$PWD/webrequestmanager.cpp

HEADERS += \
   $$PWD/abstracthelper.h \
   $$PWD/data/abstractdata.h \
   $$PWD/data/objectdata.h \
   $$PWD/data/rawbody.h \
   $$PWD/expiretime.h \
   $$PWD/global.h \
   $$PWD/response/abstractresponse.h \
   $$PWD/data/querystring.h \
   $$PWD/data/filepostdata.h \
   $$PWD/data/formpostdata.h \
   $$PWD/data/jsonpostdata.h \
   $$PWD/response/imageresponse.h \
   $$PWD/response/jsonresponse.h \
   $$PWD/response/stringresponse.h \
   $$PWD/resthelper.h \
   $$PWD/webrequestbuilder.h \
   $$PWD/webrequestcache.h \
   $$PWD/stringrequest.h \
   $$PWD/variantrequest.h \
   $$PWD/webrequest_p.h \
   $$PWD/webrequest.h \
   $$PWD/imagerequest.h \
   $$PWD/jsonrequest.h \
   $$PWD/webrequestmanager.h
