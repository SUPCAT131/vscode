arch ?= arm
modname ?= demo

ifeq ($(arch),arm)
	KERNELDIR := /home/linux/linux-5.10.61/
else
	KERNELDIR := /lib/modules/$(shell uname -r)/build/
endif

PWD := $(shell pwd)

all:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
install:
	make -C $(KERNELDIR) M=$(PWD) INSTALL_MOD_PATH=/home/linux/rootfs modules_install

obj-m:=$(modname).o