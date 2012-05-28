#-------------------------------------------------
#
# Project created by QtCreator 2012-05-27T08:15:53
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += -lGL -lGLU -lglut -lfreetype -lftgl

TARGET = QtBSTOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bst.cpp \
    node.cpp \
    painter.cpp \
    bstgl.cpp

HEADERS  += mainwindow.h \
    bst.h \
    node.h \
    painter.h \
    bstgl.h

FORMS    += mainwindow.ui

RESOURCES += \
    QtBSTOpenGL.qrc
