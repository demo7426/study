ifneq ($(KERNELRELEASE),)
	obj-m := 02_ModuleHelloworldPara.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

.PHONY:clean

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(RM) -rf *.o .* *.cmd *.ko *.mod.c .tmp_versions *.mod *.order *.symvers

endif
