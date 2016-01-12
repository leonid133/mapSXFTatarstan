# -------------------------------------------------
# Project created by QtCreator 2010-05-16T16:37:29
# -------------------------------------------------
TARGET = howto_qpainter
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    lib/sxf.cpp \
    lib/sxf_height_map.cpp \
    lib/sxf_map.cpp \
    common.cpp \
    map.cpp
HEADERS += mainwindow.h \
    lib/sxf.h \
    common.h \
    map.h
FORMS += mainwindow.ui
QT += widgets
QMAKE_CXXFLAGS += -std=c++11

