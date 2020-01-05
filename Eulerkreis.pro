QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graph.cpp \
    animation.cpp \
    animationwidget.cpp \
    dialoghelp.cpp \
    dockwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    control.cpp \
    paint.cpp \
    commands/moveCommand.cpp \
    commands/connectCommand.cpp \
    commands/removeNodeCommand.cpp \
    commands/addNodeCommand.cpp \
    memento.cpp

HEADERS += \
    Graph.h \
    animation.h \
    animationwidget.h \
    dialoghelp.h \
    dockwidget.h \
    mainwindow.h \
    control.h \
    paint.h \
    commands/moveCommand.h \
    commands/removeNodeCommand.h \
    commands/connectCommand.h \
    commands/addNodeCommand.h \
    memento.h

FORMS += \
    animationwidget.ui \
    dialoghelp.ui \
    dockwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Logo.qrc
