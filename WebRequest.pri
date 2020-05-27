QT += network sql
CONFIG += c++11

INCLUDEPATH += $$PWD/src

DEFINES += WEB_REQUEST_LIB

SOURCES += \
   $$PWD/src/response/abstractresponse.cpp \
   $$PWD/src/module.cpp \
   $$PWD/src/querystring.cpp \
   $$PWD/src/request/abstractpostdata.cpp \
   $$PWD/src/request/filepostdata.cpp \
   $$PWD/src/request/formpostdata.cpp \
   $$PWD/src/request/jsonpostdata.cpp \
   $$PWD/src/stringrequest.cpp \
   $$PWD/src/variantrequest.cpp \
   $$PWD/src/webrequest.cpp \
   $$PWD/src/webrequestcache.cpp \
   $$PWD/src/imagerequest.cpp \
   $$PWD/src/jsonrequest.cpp \
   $$PWD/src/webrequestmanager.cpp

HEADERS += \
   $$PWD/src/response/abstractresponse.h \
   $$PWD/src/module.h \
   $$PWD/src/querystring.h \
   $$PWD/src/request/abstractpostdata.h \
   $$PWD/src/request/filepostdata.h \
   $$PWD/src/request/formpostdata.h \
   $$PWD/src/request/jsonpostdata.h \
   $$PWD/src/webrequestcache.h \
   $$PWD/src/stringrequest.h \
   $$PWD/src/variantrequest.h \
   $$PWD/src/webrequest_p.h \
   $$PWD/src/webrequest.h \
   $$PWD/src/imagerequest.h \
   $$PWD/src/jsonrequest.h \
   $$PWD/src/webrequestmanager.h
