cmake_minimum_required(VERSION 3.16)
project(xviewer LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 自动构建核心配置
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cjson ${CMAKE_CURRENT_SOURCE_DIR}/camera_config)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/cjson PROJECT_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/camera_config PROJECT_SOURCES)

set(PROJECT_SOURCES
    main.cpp
    xviewer.ui
    xviewer.h
    xviewer.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

qt_add_resources(${PROJECT_NAME} "APP_Resource"
    PREFIX "/"
    BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES Resource.qrc
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

