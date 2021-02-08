cmake_minimum_required(VERSION 3.14)

project(flickable-qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)

add_subdirectory(kmisc)

if (ANDROID)
    add_library(flickable-qml SHARED
      main.cpp
      igraph.cpp
      igraph.h
      graphengine.cpp
      graphengine.h
      graphmodel.cpp
      graphmodel.h
      graphnodesproxymodel.cpp
      graphnodesproxymodel.h
      graphlineproxymodel.cpp
      graphlineproxymodel.h
      graphcalculator.cpp
      graphcalculator.h
      randomgraphexample.cpp
      randomgraphexample.h
      qml.qrc
    )
else()
    add_executable(flickable-qml
      main.cpp
      igraph.cpp
      igraph.h
      graphengine.cpp
      graphengine.h
      graphmodel.cpp
      graphmodel.h
      graphnodesproxymodel.cpp
      graphnodesproxymodel.h
      graphlineproxymodel.cpp
      graphlineproxymodel.h
      graphcalculator.cpp
      graphcalculator.h
      randomgraphexample.cpp
      randomgraphexample.h
      qml.qrc
    )
endif()

target_link_libraries(flickable-qml
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    kmisc
)
