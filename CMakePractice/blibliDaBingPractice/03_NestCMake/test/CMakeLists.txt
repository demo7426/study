
cmake_minimum_required(VERSION 3.6.2)
project(test)

set(CMAKE_CXX_STANDARD 11)

file(GLOB src_cpps ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${HEADPATH})

link_directories(${LIBPATH})
link_libraries(${STATICLIBCAL})

set(EXECUTABLE_OUTPUT_PATH ${EXCUTEPATH})
add_executable(${APPNAME01} ${src_cpps})
