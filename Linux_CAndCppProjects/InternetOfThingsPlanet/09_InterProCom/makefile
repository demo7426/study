
OBJ=09_Posix_Shm.o
TARGET=09_Posix_Shm.out

.PHONY:clean

main:$(OBJ)
#	使用Posix标准消息队列、共享内存时，必须链接rt库
#	使用Posix标准信号量时，必须链接pthread库
	$(CC) -lstdc++ $^ -o $(TARGET) -lpthread -lrt

%.o:%.c
	$(CC) -std=c99 -c $^ -o $@

clean:
	echo "清除所有编译后文件"
#/tmp/03_NamedPipeTest.txt 为命名管道FIFO文件	
	@$(RM) -f *.out *.o *.txt /tmp/03_NamedPipeTest.txt