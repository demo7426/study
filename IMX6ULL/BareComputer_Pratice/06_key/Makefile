
CROSS_COMPILE?=arm-none-linux-gnueabihf-
TARGET?=key

CC			:=$(CROSS_COMPILE)gcc
LD			:=$(CROSS_COMPILE)ld
OBJCOPY		:=$(CROSS_COMPILE)objcopy
OBJDUMP		:=$(CROSS_COMPILE)objdump

#头文件路径
INCUDIRS	:=	imx6u		\
				bsp/clk		\
				bsp/delay	\
				bsp/led		\
				bsp/beep	\
				bsp/key

#源文件路径
SRCDIRS		:= 	project		\
				bsp/clk		\
				bsp/delay	\
				bsp/led		\
				bsp/beep	\
				bsp/key

INCLUDE		:=	$(patsubst %, -I %, $(INCUDIRS))

SFILES		:=	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES		:=	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILESNODIR	:=	$(notdir $(SFILES))
CFILESNODIR	:=	$(notdir $(CFILES))

SOBJS		:=	$(patsubst %, obj/%, $(SFILESNODIR:.s=.o))
COBJS		:=	$(patsubst %, obj/%, $(CFILESNODIR:.c=.o))
OBJS		:= 	$(SOBJS)$(COBJS)

VPATH		:= $(SRCDIRS)

.PHONY:relase clean

relase: $(OBJS)
	$(LD) -Timx6u.lds $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) $< -o $@

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) $< -o $@

clean:
	$(RM) -rf $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).dis