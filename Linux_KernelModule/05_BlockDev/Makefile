ifneq ($(KERNELRELEASE),)
	obj-m := 05_BlockDev.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

.PHONY:clean

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CXX) Test.cpp -o Test.elf

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	$(RM) -rf Test.elf

endif
