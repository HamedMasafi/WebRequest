QT += network sql
CONFIG += c++11

INCLUDEPATH += $$PWD

DEFINES += WEB_REQUEST_LIB

SOURCES += \
   $$PWD/stringrequest.cpp \
   $$PWD/variantrequest.cpp \
   $$PWD/webrequest.cpp \
   $$PWD/webrequestcache.cpp \
   $$PWD/imagerequest.cpp \
   $$PWD/jsonrequest.cpp \
   $$PWD/webrequestmanager.cpp

HEADERS += \
   $$PWD/webrequestcache.h \
   $$PWD/stringrequest.h \
   $$PWD/variantrequest.h \
   $$PWD/webrequest_p.h \
   $$PWD/webrequest.h \
   $$PWD/imagerequest.h \
   $$PWD/jsonrequest.h \
   $$PWD/webrequestmanager.h
