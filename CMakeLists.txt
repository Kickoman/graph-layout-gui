cmake_minimum_required(VERSION 3.14)

project(flickable-qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

include(CMake/crossplatform/crossplatform.cmake)
include(CMake/QuasarAppCITargets.cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)

add_subdirectory(kmisc)

if (ANDROID)
    add_library(flickable-qml SHARED
      main.cpp
      graphlab.h
      graphlab.cpp
      igraph.h
      graphlayout.cpp
      graphlayout.h
      graphnodesproxymodel.cpp
      graphnodesproxymodel.h
      graphlineproxymodel.cpp
      graphlineproxymodel.h
      graphcalculator.cpp
      graphcalculator.h
      randomgraphexample.cpp
      randomgraphexample.h
      twodvector.cpp
      twodvector.h
      line.cpp
      line.h
      section.h
      section.cpp
      qml.qrc
    )
else()
    add_executable(flickable-qml
      main.cpp
      igraph.h
      graphlab.h
      graphlab.cpp
      graphlayout.cpp
      graphlayout.h
      graphnodesproxymodel.cpp
      graphnodesproxymodel.h
      graphlineproxymodel.cpp
      graphlineproxymodel.h
      graphcalculator.cpp
      graphcalculator.h
      randomgraphexample.cpp
      randomgraphexample.h
      twodvector.cpp
      twodvector.h
      line.cpp
      line.h
      section.h
      section.cpp
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

#initWasmSupport(${PROJECT_NAME} deployWasm.json)
