ifneq ($(KERNELRELEASE),)
	obj-m := led_device.o led_driver.o
else
	KERNEL_DIR := /home/qianrui/workspace/kernel-driver/linux-xlnx-xlnx_rebase_v5.4_2020.2
	PWD := $(shell pwd)		

APP_NAME := led_app.cpp
APP_ELF := led_app.elf

.PHONY:all clean

all:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) modules
	$(CXX) ${APP_NAME} -o ${APP_ELF} -lpthread

clean:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) clean
	${RM} -rf ${APP_ELF}

endif
