TEMPLATE     = vcapp
TARGET       = TestCarte
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h centralwidget.h leds.h switches.h Vecteur.h VisiTest.h CommunicationFPGA.h
SOURCES     += TestVisiTest.cpp MonInterface.cpp Vecteur.cpp
INCLUDEPATH += ../TestCarte-main
LIBS	      += ../TestCarte-main/VisiTest.lib  ../TestCarte-main/CommunicationFPGA.lib
QT += widgets
