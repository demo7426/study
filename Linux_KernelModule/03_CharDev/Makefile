ifneq ($(KERNELRELEASE),)
	obj-m := 03_CharDev.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

.PHONY:clean

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CXX) Test.cpp -o Test.elf

clean:
	$(RM) -rf *.o .* *.cmd *.ko *.mod.c .tmp_versions *.mod *.order *.symvers *.elf

endif
