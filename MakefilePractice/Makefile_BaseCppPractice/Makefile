#该文档使用系统常量、系统变量、自定义变量编写Makefile

#伪目标 .PHONY:clean
#	声明目标为伪目标后，makefile将不会判断目标是否存在或该目标是否需要更新（即使目标和文件重名，也不会影响make命令的执行）
.PHONY:clean show

OBJ=MyMax.o MySub.o main.o
TARGET=main.out

main:$(OBJ)
	@echo "最后一步"
	$(CXX) -lstdc++ $^ -o $(TARGET)

# %.o:%.cpp	.o依赖于对应的.cpp
%.o:%.cpp
	$(CXX) -c $^ -o $@

show:
#	获取当前目录下所有的 .cpp 文件
	echo $(wildcard ./*.cpp)
#	将对应的 cpp 文件名替换成 .o 文件名
	echo $(patsubst %.cpp, %.o, ./*.cpp)
	
#	@ls -l | grep ".cpp"
#	@ls -l | grep ".h"
clean:
	@echo "清除编译后的文件"
	@rm -f *.o *.out