ifneq ($(KERNELRELEASE),)
	obj-m := 05_BlockDev.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

.PHONY:clean

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CXX)  -g -Wall -O2 Test.cpp -o Test.elf

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	$(RM) -rf Test.elf

endif
