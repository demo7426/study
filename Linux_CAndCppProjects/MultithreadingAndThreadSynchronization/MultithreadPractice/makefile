
OBJ=main.o
TARGET=main.out

main:$(OBJ)
	$(CXX) -lpthread  $^ -o $(TARGET)

%.o:%.c
	$(CXX) -lstdc++ -c $^ -o $@

clean:
	echo "清除编译后的文件"
	$(RM) -f ./*.out ./*.o