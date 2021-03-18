cmake_minimum_required(VERSION 3.14)

project(GraphLab LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets Qml QuickWidgets REQUIRED)

add_subdirectory(lib/graph-layout)

set(HEADERS_DIR "include")
set(SOURCES_DIR "src")

set(HEADERS
    ${HEADERS_DIR}/basicgraph.h
    ${HEADERS_DIR}/basicgraphparser.h
    ${HEADERS_DIR}/randomgraphexample.h
    ${HEADERS_DIR}/graphlab.h
)

set(SOURCES
    ${SOURCES_DIR}/main.cpp
    ${SOURCES_DIR}/basicgraph.cpp
    ${SOURCES_DIR}/basicgraphparser.cpp
    ${SOURCES_DIR}/graphlab.cpp
    ${SOURCES_DIR}/randomgraphexample.cpp
)

set(RESOURCES
    qml.qrc
    ${GRAPH_LAYOUT_QML_RESOURCES}
)

if (ANDROID)
    add_library(${PROJECT_NAME} SHARED
        ${HEADERS}
        ${SOURCES}
        ${RESOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${HEADERS}
        ${SOURCES}
        ${RESOURCES}
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS_DIR})

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    graphlayout
)
