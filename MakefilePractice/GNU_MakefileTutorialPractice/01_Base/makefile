#makefile常用函数测试

C_SRCS:=$(shell find  ./ -name "*.c")

#C_OBJS:=$(subst ./,./GNU_MakefileTutorialPractice,$(C_SRCS))		#subst字符串替换
#C_OBJS:=$(subst .c,.o,$(C_OBJS))									#subst字符串替换

#C_OBJS:=$(patsubst ./%.c,./%.o,$(C_SRCS))							#patsubst字符串替换
#C_OBJS:=$(foreach item,$(C_SRCS),-I$(item))						#foreach循环函数
#C_OBJS:=$(C_SRCS:%=-I%)											#等同于foreach循环函数

#dir函数测试
C_OBJS:=$(patsubst ./%.c,./Objs/%.o,$(C_SRCS))

debug:$(C_OBJS)
	g++ $^ -o ./Objs/main.out

./Objs/%.o:%.c
	@mkdir -p $(dir $@)
	$(CXX) -c $^ -o $@
#dir函数测试

show:
	@echo $(shell find  ./ -name "*")

clean:
	@$(RM) -rf *.o *.a *.so *.txt *.out ./Objs

.PHONY:debug clean show