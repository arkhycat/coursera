TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS +=  -L/gmp_install/lib -lgmp

SOURCES += \
    crypto5.cpp

