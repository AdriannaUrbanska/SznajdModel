TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../main.cpp \
    ../source/model.cpp \
    ../source/model1d.cpp \
    ../source/model2d.cpp

INCLUDEPATH += ../include/
INCLUDEPATH += ../QtTest/

HEADERS += \
    ../include/model.h \
    ../include/model1d.h \
    ../include/model2d.h \
    ../include/wyjatki.h
