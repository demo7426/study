
OBJ=Server.o
TARGET=Server.out
.PHONY=clean

main:$(OBJ)
	$(CC) -lstdc++ $^ -o $(TARGET)

%.o:%.c
	$(CC) -std=c99 -c $^ -o $@

clean:
	echo "清除所有编译后文件"
	@$(RM) -f *.out *.o *.txt