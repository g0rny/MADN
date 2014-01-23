# -------------------------------------------------
# Project created by QtCreator 2013-11-19T12:41:22
# -------------------------------------------------
QT += core \
    gui \
    network
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = test
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    dialog.cpp \
    erstellen.cpp \
    feld.cpp \
    wurfel.cpp \
    spielfeld.cpp \
    startposition.cpp \
    verzweigungsfeld.cpp \
    zielfeld.cpp \
    spielbrett.cpp \
    Server.cpp \
    startfeld.cpp \
    spiel.cpp \
    spieler.cpp \
    timeout.cpp \
    Client.cpp \
    figurBewegen.cpp \
    spielInit.cpp \
    figurBewegenKI.cpp \
    lobby.cpp
HEADERS += mainwindow.h \
    dialog.h \
    erstellen.h \
    feld.h \
    wurfel.h \
    spielfeld.h \
    startposition.h \
    verzweigungsfeld.h \
    zielfeld.h \
    zustand.h \
    Netzwerkverbindung.h \
    Server.h \
    Client.h \
    startfeld.h \
    spiel.h \
    spieler.h \
    timeout.h \
    lobby.h
FORMS += mainwindow.ui \
    dialog.ui \
    erstellen.ui \
    lobby.ui
RESOURCES += ressourcen/icons.qrc \
    ressourcen/felder.qrc \
    ressourcen/figuren.qrc \
    ressourcen/wurfel.qrc
