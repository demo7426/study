#编译、链接动态链接库

dynamic_libpath:=lib/libxxx.so
cpp_srcs:=$(shell find src -name *.cpp)
cpp_objs:=$(patsubst src/%.cpp,obj/%.o,$(cpp_srcs))
lib_objs:=$(filter-out obj/main.o,$(cpp_objs))

include_paths:=./include

I_options:=$(include_paths:%=-I%)
l_options:=$(basename $(notdir $(dynamic_libpath)))
l_options:=$(patsubst lib%,%,$(l_options))
l_options:=$(l_options:%=-l%)
L_options:=$(dir $(dynamic_libpath))
L_options:=$(L_options:%=-L%)
r_options:=$(dir $(dynamic_libpath))
r_options:=$(r_options:%=-Wl,-rpath=%)

compile_options:=-w -O3 -g -fPIC $(I_options)
link_options:=$(l_options) $(L_options) $(r_options)

#######################编译动态链接库########################

obj/%.o:src/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $^ -o $@ $(compile_options)

compile:$(cpp_objs)

dynamic_lib:compile 
	@mkdir -p $(dir $(dynamic_libpath))
	@$(CXX) -shared $(lib_objs) -o $(dynamic_libpath)

############################################################

#######################链接动态链接库########################
workspace/exec:obj/main.o dynamic_lib
	@mkdir -p $(dir $@)
	@$(CXX) $< -o $@ $(link_options)

run:workspace/exec
	@./$<

############################################################

debug:
	@echo $(link_options)

clean:
	@$(RM) -rf obj lib workspace

.PHONY:debug compile dynamic_lib clean