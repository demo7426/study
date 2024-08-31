
OBJ=07_DaemonProcess.o
TARGET=07_DaemonProcess.out

main:$(OBJ)
#	在测试03_ExcuteProcess_exec.c文件时需要提前生成一个可执行文件，以供测试
#	gcc -lstdc++ 03_Test.c -o 03_Test.out
	gcc -lstdc++ $^ -o $(TARGET)

%.o:%.c
	gcc -std=c99 -c $^ -o $@

.PHONY:clean
clean:
	@echo "清除所有编译后文件"
	$(RM) -f *.out *.o *.txt
