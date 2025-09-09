ifneq ($(KERNELRELEASE),)
	obj-m := gpio_led_spinlock.o
else
	KERNEL_DIR := /home/qianrui/workspace/kernel-driver/linux-xlnx-xlnx_rebase_v5.4_2020.2
	PWD := $(shell pwd)		

APP_NAME := gpio_led_app_spinlock.cpp
APP_ELF := gpio_led_app_spinlock.elf

.PHONY:all clean

all:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) modules
	$(CXX) ${APP_NAME} -o ${APP_ELF} -lpthread

clean:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) clean
	${RM} -rf ${APP_ELF}

endif
