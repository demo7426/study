OBJS=Start.o Main.o			
TARGET=02_Led.elf			#链接后的目标文件


default:$(OBJS)
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c Main.c -o Main.o
	arm-none-linux-gnueabihf-ld -Ttext 0x87800000 $^ -o $(TARGET)
	arm-none-linux-gnueabihf-objcopy -O binary -S $(TARGET) 02_Led.bin
	arm-none-linux-gnueabihf-objdump -D $(TARGET) > 02_Led.dis

%.o:%c	
#	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c Main.c -o Main.o		#TODO:会被编译成x64架构，待追踪bug

%.o:%.s
	arm-none-linux-gnueabihf-gcc -Wall -nostdlib -c $< -o $@

clean:
	$(RM) -rf *.o *.dis $(TARGET) *.bin *.imx