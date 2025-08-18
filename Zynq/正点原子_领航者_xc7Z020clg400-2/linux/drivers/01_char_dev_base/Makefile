ifneq ($(KERNELRELEASE),)
	obj-m := char_dev_base.o
else
	KERNEL_DIR := /home/qianrui/workspace/kernel-driver/linux-xlnx-xlnx_rebase_v5.4_2020.2
	PWD := $(shell pwd)		

APP_NAME := char_dev_base_app.cpp
APP_ELF := char_dev_base_app.elf

.PHONY:all clean

all:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) modules
	$(CXX) ${APP_NAME} -o ${APP_ELF}

clean:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) clean
	${RM} -rf ${APP_ELF}

endif
