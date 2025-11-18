ifneq ($(KERNELRELEASE),)
	obj-m := pwm.o
else
	KERNEL_DIR := /home/qianrui/workspace/kernel-pwm/linux-xlnx-xlnx_rebase_v5.4_2020.2
	PWD := $(shell pwd)		

.PHONY:all clean

all:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) modules

clean:
	${MAKE} -C ${KERNEL_DIR} M=$(PWD) clean

endif
