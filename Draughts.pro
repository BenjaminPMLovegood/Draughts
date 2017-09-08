QT += core gui widgets network
QT += webenginewidgets

TARGET = Draughts
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    commonheader.cpp \
    channel.cpp \
    board.cpp

HEADERS += \
    mainwindow.h \
    commonheader.h \
    channel.h \
    board.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    ui.qrc
