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

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/app/cjson 
    ${CMAKE_CURRENT_SOURCE_DIR}/app/camera_config 
    ${CMAKE_CURRENT_SOURCE_DIR}/app/debug 
    ${CMAKE_CURRENT_SOURCE_DIR}/app/camera_widget
    ${CMAKE_CURRENT_SOURCE_DIR}/app/video
    ${CMAKE_CURRENT_SOURCE_DIR}/xv
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ffmpeg 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sdl 
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/app/cjson PROJECT_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/app/camera_config PROJECT_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/app/camera_widget PROJECT_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/app/video PROJECT_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/xv PROJECT_SOURCES)  


link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/ffmpeg/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl
)

link_libraries(
    avcodec
    avdevice
    avfilter
    avformat
    avutil
    postproc
    swresample
    swscale
    SDL2
)

qt_add_executable(
    ${PROJECT_NAME}
    main.cpp
    xviewer.ui
    xviewer.h
    xviewer.cpp
    ${PROJECT_SOURCES}
)

qt_add_resources(${PROJECT_NAME} "APP_Resource"
    PREFIX "/"
    BASE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES Resource.qrc
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE FALSE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

