QT += gui widgets qml quickwidgets

TARGET = graph

CONFIG += c++11

RESOURCES += \
    qml.qrc

HEADERS += \
    basicgraph.h \
    basicgraphparser.h \
    graphcalculator.h \
    graphlab.h \
    graphlayout.h \
    graphlineproxymodel.h \
    graphnodesproxymodel.h \
    igraph.h \
    kmisc/kfunction/kfunction.h \
    line.h \
    randomgraphexample.h \
    section.h \
    twodvector.h

SOURCES += \
    basicgraph.cpp \
    basicgraphparser.cpp \
    graphcalculator.cpp \
    graphlab.cpp \
    graphlayout.cpp \
    graphlineproxymodel.cpp \
    graphnodesproxymodel.cpp \
    line.cpp \
    main.cpp \
    randomgraphexample.cpp \
    section.cpp \
    twodvector.cpp

DEFINES += WASM_BUILD

contains(DEFINES, "WASM_BUILD"): DEFINES += DISABLE_THREADS
