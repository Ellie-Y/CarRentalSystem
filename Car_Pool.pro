#-------------------------------------------------
#
# Project created by QtCreator 2019-03-12T15:16:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Car_Pool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        log_in.cpp \
    Sign_In.cpp \
    clickableLabel.cpp \
    updateProfile.cpp \
    MainScreen.cpp \
    findRidePage.cpp \
    reserveCar.cpp \
    createRide.cpp \
    adminstrator.cpp

HEADERS  += log_in.h \
    Sign_In.h \
    clickableLabel.h \
    updateProfile.h \
    findRidePage.h \
    mainScreen.h \
    reserveCar.h \
    createRide.h \
    adminstrator.h

FORMS    += log_in.ui \
    Sign_In.ui \
    mainScreen.ui \
    updateProfile.ui \
    findRidePage.ui \
    reserveCar.ui \
    createRide.ui \
    adminstrator.ui

RESOURCES += \
    images.qrc
