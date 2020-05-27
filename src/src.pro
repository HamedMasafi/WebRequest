QT += network sql
CONFIG += c++11

INCLUDEPATH += $$PWD

DEFINES += WEB_REQUEST_LIB

SOURCES += \
   $$PWD/response/abstractresponse.cpp \
   $$PWD/module.cpp \
   $$PWD/data/querystring.cpp \
   $$PWD/data/abstractpostdata.cpp \
   $$PWD/data/filepostdata.cpp \
   $$PWD/data/formpostdata.cpp \
   $$PWD/data/jsonpostdata.cpp \
   $$PWD/stringrequest.cpp \
   $$PWD/variantrequest.cpp \
   $$PWD/webrequest.cpp \
   $$PWD/webrequestcache.cpp \
   $$PWD/imagerequest.cpp \
   $$PWD/jsonrequest.cpp \
   $$PWD/webrequestmanager.cpp

HEADERS += \
   $$PWD/response/abstractresponse.h \
   $$PWD/module.h \
   $$PWD/data/querystring.h \
   $$PWD/data/abstractpostdata.h \
   $$PWD/data/filepostdata.h \
   $$PWD/data/formpostdata.h \
   $$PWD/data/jsonpostdata.h \
   $$PWD/webrequestcache.h \
   $$PWD/stringrequest.h \
   $$PWD/variantrequest.h \
   $$PWD/webrequest_p.h \
   $$PWD/webrequest.h \
   $$PWD/imagerequest.h \
   $$PWD/jsonrequest.h \
   $$PWD/webrequestmanager.h
