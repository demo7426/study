
OBJ=06_Sem.o
TARGET=06_Sem.out

.PHONY:clean

main:$(OBJ)
	$(CC) -lstdc++ $(OBJ) -o $(TARGET) -lpthread
%.o:%.c
	$(CC)  -std=c99 -c $^ -o $@ 

clean:
	echo "清除所有编译后文件"
	@$(RM) -f *.o *.out *.txt


