QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += testlib
CONFIG += testcase

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArrayOperation.cpp \
    CalculateButtonLogic.cpp \
    Config.cpp \
    ControlArea.cpp \
    ControlAreaBuilder.cpp \
    FileParser.cpp \
    SimulationData.cpp \
    ThermalCalculation.cpp \
    ThermalCalculation_test.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ArrayOperation.h \
    CalculateButtonLogic.h \
    Config.h \
    ControlArea.h \
    ControlAreaBuilder.h \
    FileParser.h \
    SimulationData.h \
    ThermalCalculation.h \
    ThermalCalculation_test.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
