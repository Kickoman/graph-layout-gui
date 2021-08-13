QT += gui widgets qml quickwidgets

TARGET = graphgui

CONFIG += c++11

RESOURCES += \
    ../qml.qrc

HEADERS += \
	../include/basicgraph.h \
	../include/basicgraphparser.h \
	../include/graphlab.h \
	../include/randomgraphexample.h
	
SOURCES += \
	basicgraph.cpp \
	basicgraphparser.cpp \
	graphlab.cpp \
	randomgraphexample.cpp \
	main.cpp

INCLUDEPATH += ../include

DEFINES += WASM_BUILD

contains(DEFINES, "WASM_BUILD"): DEFINES += DISABLE_THREADS

include($$PWD/../lib/graph-layout/graph-layout.pri)
