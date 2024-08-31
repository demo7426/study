
.PHONY=clean
OBJ=05_SignalOtherFunc.o
TARGET=05_SignalOtherFunc.out

main:$(OBJ)
	gcc -lstdc++ $^ -o $(TARGET)

%.o:%.c
	gcc -std=c99 -c $^ -o $@

clean:
	echo "清除所有编译后文件"
	@$(RM) -f *.out *.o *.txt
