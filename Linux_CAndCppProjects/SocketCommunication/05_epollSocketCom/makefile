
OBJ=epollETServer.o
TARGET=epollETServer.out
.PHONY=clean

main:$(OBJ)
	$(CC) -lstdc++ $^ -o $(TARGET) -lpthread

%.o:%.c
	$(CC) -std=c99 -c $^ -o $@

clean:
	echo "清除所有编译后文件"
	@$(RM) -f *.out *.o *.txt