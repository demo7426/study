
cmake_minimum_required(VERSION 3.6.2)
project(03_NestCMake)

#设置库的存储目录
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)

#设置静态库名称
set(STATICLIBCAL Cal)

#设置头文件目录路径
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

#设置可执行程序的存储目录
set(EXCUTEPATH ${PROJECT_SOURCE_DIR}/bin)

#设置输出可执行程序的名称
set(APPNAME01 test.out)

#添加子节点
add_subdirectory(cal)
add_subdirectory(test)