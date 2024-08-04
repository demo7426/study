ifneq ($(KERNELRELEASE),)
	obj-m := 01_Helloworld.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

.PHONY:clean

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(RM) -rf *.o .* *.cmd *.ko *.mod.c .tmp_versions *.mod *.order *.symvers

endif


# obj-m := modules.o                   #要生成的模块名
# modules-objs:= 01_Helloworld.o        #生成这个模块名所需要的目标文件

# KERNELDIR := /lib/modules/$(shell uname -r)/build
# PWD := $(shell pwd)

# default:
# 	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

# clean:
# 	$(RM) -rf *.o .* .cmd *.ko *.mod.c .tmp_versions *.mod *.order *.symvers