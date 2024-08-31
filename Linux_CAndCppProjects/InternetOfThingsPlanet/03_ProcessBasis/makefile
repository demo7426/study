
OBJ=05_MainFuncPam.o
TARGET=05_MainFuncPam.out

main:$(OBJ)
	gcc -lstdc++ $^ -o $(TARGET)

%.o:%.c
	gcc -lstdc++ -c $^ -o $@

clean:
	@echo "清除所有编译后文件"
	$(RM) -f *.txt *.out *.o
