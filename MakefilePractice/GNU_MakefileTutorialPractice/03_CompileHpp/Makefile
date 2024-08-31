#编译带头文件的程序

CPP_SRCS:=$(shell find src -name *.cpp)
CPP_OBJS:=$(patsubst src/%.cpp,objs/%.o,$(CPP_SRCS))

INCLUDE_PAthS:=./include

I_FLAGS:=-g -w -O3 $(INCLUDE_PAthS:%=-I%)

objs/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $^ -o $@ $(I_FLAGS)

workspace/exec:$(CPP_OBJS)
	@mkdir -p $(dir $@)
	@$(CXX) $^ -o $@

run:workspace/exec
	@./$<

debug:
	@echo $(I_FLAGS)
	@echo $(CPP_OBJS)

.PHONY:debug run

clean:
	@echo "清理编译后文件"
	@$(RM) -rf objs workspace 