MOD_NAME := vsd_driver

ifneq ($(KERNELRELEASE),)
	obj-m := $(MOD_NAME).o
	header-y += vsd_ioctl.h
	$(MOD_NAME)-objs := module.o
else
	KDIR := ../../../linux/
	VM_PATH := ../../../../vm/
all:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp $(MOD_NAME).ko $(VM_PATH)/share/

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
