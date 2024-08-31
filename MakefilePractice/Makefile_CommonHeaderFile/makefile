#makefile内部条件判断

VALUE=321
PRINTMESSAGE:=

ifeq ($(VALUE), 123)#ifeq (判断)之间必须用空格隔开
	PRINTMESSAGE:=123
else
	ifneq ($(VALUE), 321)
	PRINTMESSAGE:=flase
	endif
	
	PRINTMESSAGE:=321
endif

ifdef VALUE#只能单独直接使用变量
	PRINTMESSAGE+=_01
else
	PRINTMESSAGE+=_00
endif

printf:
	@echo $(PRINTMESSAGE)