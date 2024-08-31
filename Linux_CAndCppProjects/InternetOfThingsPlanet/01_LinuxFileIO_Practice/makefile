
OBJ=07_Metadata.o
TARGET=07_Metadata.out

main:$(OBJ)
	gcc -lstdc++ $^ -o $(TARGET)

%.o:%.c
	gcc -lstdc++ -c $^ -o $@

.PHONY:clean
clean:
	@echo "清除编译后的文件"
	$(RM) -f ./*.out ./*.o ./*.txt




