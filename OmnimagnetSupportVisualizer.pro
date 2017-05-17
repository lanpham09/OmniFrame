#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T11:53:23
#
#-------------------------------------------------

QT       += core gui\
            opengl

OBJECTS_DIR = ./Build
MOC_DIR = ./Build

TARGET = OmnimagnetSupportVisualizer
TEMPLATE = app

QMAKE_CXXFLAGS	 += -g -Wall

CONFIG += debug

LIBS += -L/usr/lib\
        -lGL\
        -lGLU\
        -L../Math_Lib\
        -L../AD_IO_Lib\
        -lAD_IO\
        -lMath\
        -lserial



#DEPENDPATH += 	../OmnimagnetCode\
#
#INCLUDEPATH += 	/usr/local/include/eigen3\
#                ../OmnimagnetCode\


#DEPENDPATH += 	/media/Telerobotics/code/Sandbox
#
#INCLUDEPATH += 	/usr/local/include/eigen3\
#                /media/Telerobotics/code/Sandbox\

DEPENDPATH += 	../Sandbox

INCLUDEPATH += 	/usr/local/include/eigen3\
                ../Sandbox\



SOURCES += main.cpp\
        mainwindow.cpp \
        GraphicsView3D.cpp \
        model.cpp \
        Assembly.cpp \
        OmnimagnetFrameScene.cpp \
        OpenGL_Object.cpp \
        virticalSupportAssy.cpp \
        horizontalSupportAssy.cpp \
        omnimagnetAssy.cpp \
        baseAssy.cpp \
        ArduinoUSBInterface.cpp \
    ../../../media/Telerobotics/code/Sandbox/Utilities/Thread.cpp

HEADERS  += mainwindow.h \
    GraphicsView3D.h \
    point3d.h \
    model.h \
    Assembly.h \
    OpenGL_Object.h \
    OmnimagnetFrameScene.h \
    virticalSupportAssy.h \
    horizontalSupportAssy.h \
    omnimagnetAssy.h \
    baseAssy.h \
    ArduinoUSBInterface.h \
    ../../../media/Telerobotics/code/Sandbox/Utilities/Thread.h

FORMS    += mainwindow.ui
