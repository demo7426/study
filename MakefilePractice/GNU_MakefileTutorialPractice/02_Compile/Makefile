

CPP_SRCS:=$(shell find ./src -name *.cpp)
CPP_i:=$(patsubst %.cpp,%.i,$(CPP_SRCS))
CPP_s:=$(patsubst %.cpp,%.s,$(CPP_SRCS))
CPP_o:=$(patsubst %.cpp,%.o,$(CPP_SRCS))
CPP_exec:=./src/main.out

%.o:%.cpp
	@$(CXX) -c $^ -o $@

debug:$(CPP_o)
	@$(CXX) $^ -o $(CPP_exec)

run:debug
	@./$(CPP_exec)

show:
	@echo $(CPP_o) $(CPP_SRCS)

clean:
	@$(RM) -f *.i *.s *.o *.out *.txt ./src/*.i ./src/*.s ./src/*.o ./src/*.out ./src/*.txt

.PHONY: clean