
OBJ=06_CPUAffinity.o
TARGET=06_CPUAffinity.out

main:$(OBJ)
	gcc -lstdc++ $^ -o $(TARGET)

%.o:%.c
	gcc -std=c99 -c $^ -o $@

.PHONY:clean
clean:
	echo "清除所有编译后文件"
	@$(RM) -f *.o *.out *.txt
