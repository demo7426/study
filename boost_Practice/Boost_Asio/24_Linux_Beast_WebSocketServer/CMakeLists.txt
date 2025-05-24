cmake_minimum_required(VERSION 3.10)
project(WebSocketServer)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)

#设置boost路径
set(BOOST_ROOT /usr)

#查找boost库组件
find_package(Boost REQUIRED COMPONENTS system thread)

#添加可执行文件和源文件
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(WebSocketServer ${SOURCES})

#包含头文件路径(包括其它目录)
target_include_directories(WebSocketServer
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#包含boost头文件路径
target_include_directories(WebSocketServer
PRIVATE
    ${Boost_INCLUDE_DIRS}
)

#链接boost库
target_link_libraries(WebSocketServer PRIVATE ${Boost_LIBRARIES})

