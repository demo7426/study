
OBJ=05_ThreadSignal.o
TARGET=05_ThreadSignal.out

.PHONY:clean main

main:$(OBJ)
	gcc -lstdc++ $^ -o $(TARGET) -lpthread

%.o:%.c
	gcc -std=c99 -c $^ -o $@

clean:
	echo "清除所有编译后文件"
	$(RM) -f *.out *.txt *.o