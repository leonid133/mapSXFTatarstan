# -------------------------------------------------
# Project created by QtCreator 2010-05-16T16:37:29
# -------------------------------------------------
TARGET = howto_qpainter
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    lib/codepage.cpp \
    lib/file.cpp \
    lib/map.cpp \
    lib/point.cpp \
    lib/sxf.cpp \
    lib/sxf_height_map.cpp \
    lib/sxf_map.cpp \
    mapwidget.cpp
HEADERS += mainwindow.h \
    lib/all.h \
    lib/amv.h \
    lib/codepage.h \
    lib/file.h \
    lib/map.h \
    lib/point.h \
    lib/sxf.h \
    mapwidget.h \
    common.h
FORMS += mainwindow.ui
QT += widgets
QMAKE_CXXFLAGS += -std=c++11
