#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T16:49:12
#
#-------------------------------------------------

QT       += core gui
QT += datavisualization
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OptionX
TEMPLATE = app

# Include path
INCLUDEPATH += C:\Users\Asus\Documents\armadillo-9.200.6\include

# Add external libraries
LIBS += -LC:\Users\Asus\Documents\armadillo-9.200.6\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        optionx.cpp \
    AmericanPayoff.cpp \
    AsianPayoff.cpp \
    EuropeanPayoff.cpp \
    Option.cpp \
    Payoff.cpp \
    PowerPayoff.cpp \
    AmericanPayoff.cpp \
    AsianPayoff.cpp \
    BlackScholes.cpp \
    ConvectionDiffusion.cpp \
    ConvectionDiffusionEulerExplicit.cpp \
    ConvectionDiffusionEulerImplicit.cpp \
    ConvectionDiffusionFEMBase.cpp \
    EuropeanPayoff.cpp \
    FEMInterface.cpp \
    Hyperbolic.cpp \
    Option.cpp \
    Payoff.cpp \

HEADERS += \
        optionx.h \
    AmericanPayoff.h \
    AsianPayoff.h \
    BlackScholes.h \
    ConvectionDiffusion.h \
    ConvectionDiffusionEulerExplicit.h \
    ConvectionDiffusionEulerImplicit.h \
    ConvectionDiffusionFEMBase.h \
    EuropeanPayoff.h \
    Hyperbolic.h \
    Option.h \
    Payoff.h \
    PowerPayoff.h \
    FEMInterface.h

FORMS += \
        optionx.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
