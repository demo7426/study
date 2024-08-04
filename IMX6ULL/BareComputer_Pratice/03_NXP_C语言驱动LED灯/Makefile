CROSS_COMPILE?=arm-none-linux-gnueabihf-
NAME?=03_Led

CC			:=$(CROSS_COMPILE)gcc
LD			:=$(CROSS_COMPILE)ld
OBJCOPY		:=$(CROSS_COMPILE)objcopy
OGJDUMP		:=$(CROSS_COMPILE)objdump

OBJS=Start.o Main.o			
TARGET=$(NAME).elf			#链接后的目标文件


default:$(OBJS)

#链接后的目标文件
#	$(LD) -Ttext 0x87800000 $^ -o $(TARGET)	
#自己编写链接脚本文件
	$(LD) -Timx6u.lds $^ -o $(TARGET)		

	$(OBJCOPY) -O binary -S $(TARGET) $(NAME).bin
	$(OGJDUMP) -D $(TARGET) > $(NAME).dis

%.o:%c	
	$(CC) -Wall -nostdlib -c Main.c -o Main.o
#	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c Main.c -o Main.o		#TODO:会被编译成x64架构，待追踪bug

%.o:%.s
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c $< -o $@

clean:
	$(RM) -rf *.o *.dis $(TARGET) *.bin