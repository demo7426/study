#使用静态链接库（不能使用派生类，待查找原因）

TARGET=main.out

$(TARGET):../Generate_LinkedLib/libaQR.a
	$(CXX) -laQR -L./ main.cpp -o $@

#生成.o文件
../Generate_LinkedLib/QR_BaseClass.o:../Generate_LinkedLib/QR_BaseClass.cpp
	$(CXX) -c $^ -o $@
../Generate_LinkedLib/QR_SubClass.o:../Generate_LinkedLib/QR_SubClass.cpp
	$(CXX) -c $^ -o $@


../Generate_LinkedLib/libaQR.a:../Generate_LinkedLib/QR_BaseClass.o ../Generate_LinkedLib/QR_SubClass.o
	$(AR) -rcs $@ $^
	@cp $@ ./

show:
#	获取当前目录下所有的 .cpp 文件
	@echo $(wildcard ./*.cpp)
#	将对应的 cpp 文件名替换成 .o 文件名
	@echo $(patsubst %.cpp, %.o, ./*.cpp)
	
#	@ls -l | grep ".cpp"
#	@ls -l | grep ".h"

clean:
	@echo "清除编译后的文件"
	@rm -f ../Generate_LinkedLib/*.so ../Generate_LinkedLib/*.a ../Generate_LinkedLib/*.o *.o *.so  *.a *.out