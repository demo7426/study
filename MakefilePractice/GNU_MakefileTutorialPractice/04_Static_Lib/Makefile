#编译、链接静态链接库

static_libpath:=lib/libxxx.a						#静态链接库路径及名称
cpp_srcs:=$(shell find src -name *.cpp)
cpp_srcs:=$(filter-out src/main.cpp,$(cpp_srcs))	#过滤掉除起始函数以外的文件
cpp_objs:=$(patsubst src/%.cpp,objs/%.o,$(cpp_srcs))

include_paths:=./include

I_options:=-w -O3 -g $(include_paths:%=-I%)
L_options:=$($(dir $(static_libpath)):%=-L%)

#######################编译静态链接库########################
objs/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $^ -o $@ $(I_options)

$(static_libpath):$(cpp_objs)
	@mkdir -p $(dir $@)
	@ar -r $@ $^

static_lib:$(static_libpath)
############################################################

#######################链接静态链接库########################
objs/main.o:src/main.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $^ -o $@ $(I_options)

workspace/exec:objs/main.o
	@mkdir -p $(dir $@)
	@$(CXX) $^ $(static_libpath) $(L_options) -o $@

run:static_lib workspace/exec
	@./workspace/exec

############################################################

debug:
	@echo $(I_options)

clean:
	@echo "清除编译后的文件"
	@$(RM) -rf objs workspace lib

.PHONY:debug static_lib run	 clean