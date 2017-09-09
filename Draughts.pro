QT += core gui widgets network
QT += webenginewidgets

TARGET = Draughts
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    commonheader.cpp \
    board.cpp \
    draughtsboard.cpp \
    startuppage.cpp \
    connecttoserver.cpp \
    qnumberinput.cpp \
    gameserver.cpp \
    serversettings.cpp \
    waiting.cpp \
    gameclient.cpp \
    customboard.cpp

HEADERS += \
    mainwindow.h \
    commonheader.h \
    board.h \
    draughtsboard.h \
    startuppage.h \
    connecttoserver.h \
    qnumberinput.h \
    gameserver.h \
    serversettings.h \
    main.h \
    waiting.h \
    gameclient.h \
    customboard.h

FORMS += \
    mainwindow.ui \
    startuppage.ui \
    connecttoserver.ui \
    serversettings.ui \
    waiting.ui \
    customboard.ui

RESOURCES += \
    ui.qrc
