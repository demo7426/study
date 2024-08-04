
TARGET=01_led.bin

$(TARGET) : 01_led.s
	arm-none-linux-gnueabihf-gcc -g -c $^ -o 01_led.o
	arm-none-linux-gnueabihf-ld -Ttext 0x87800000 01_led.o -o 01_led.elf
	arm-none-linux-gnueabihf-objcopy -O binary -S -g 01_led.elf $@
	arm-none-linux-gnueabihf-objdump -D 01_led.elf > 01_led.dis

.PHONY : clean

# ./*.imx 为烧写.elf程序到tf卡生成的文件
clean : 
	$(RM) -rf ./*.o ./*.elf ./*.dis ./*.bin ./*.imx 



