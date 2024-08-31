#[[
    CMake基础练习
]]
#

cmake_minimum_required(VERSION 3.6.2)                       #CMake最低版本要求

project(Test)

# set(src_cpps ../src/main.cpp)                             #定义及设置变量的值
# aux_source_directory(./src src_cpps)                      #搜索目录下的所有文件 ${PROJECT_SOURCE_DIR}：cmake指令指定的路径和
file(GLOB_RECURSE src_cpps ./src/*.cpp)                     #搜索目录下的匹配的所有文件 ${CMAKE_CURRENT_SOURCE_DIR}：CMakeLists.txt目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)    #设置头文件路径

set(CMAKE_CXX_STANDARD 11)                                  #设置g++工具链标准
set(EXECUTABLE_OUTPUT_PATH ../bin)                          #设置可执行程序输出路径，如果目录不存在则创建

add_executable(main.out ${src_cpps})
