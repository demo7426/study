#[[
    生成链接库
]]


cmake_minimum_required(VERSION 3.6.2)
project(Cal)

set(CMAKE_CXX_STANDARD 11)

file(GLOB src_cpps ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
message(STATUS "----------" ${src_cpps})
include_directories(${HEADPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
add_library(${STATICLIBCAL} STATIC ${src_cpps})