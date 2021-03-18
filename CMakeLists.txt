cmake_minimum_required(VERSION 3.14)

project(flickable-qml LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#set(CMAKE_CXX_FLAGS_DEBUG   "-g")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)

add_subdirectory(graph-layout/)

if (ANDROID)
    add_library(flickable-qml SHARED
      main.cpp
      graphlab.h
      graphlab.cpp
      randomgraphexample.cpp
      randomgraphexample.h
      basicgraphparser.h
      basicgraphparser.cpp
      basicgraph.h
      basicgraph.cpp
      qml.qrc
      ${GRAPH_LAYOUT_QML_RESOURCES}
    )
else()
    add_executable(flickable-qml
      main.cpp
      graphlab.h
      graphlab.cpp
      randomgraphexample.cpp
      randomgraphexample.h
      basicgraphparser.h
      basicgraphparser.cpp
      basicgraph.h
      basicgraph.cpp
      qml.qrc
      ${GRAPH_LAYOUT_QML_RESOURCES}
    )
endif()

target_link_libraries(flickable-qml
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    graphlayout
)

#initWasmSupport(${PROJECT_NAME} deployWasm.json)
