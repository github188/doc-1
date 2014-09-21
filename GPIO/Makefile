obj-m := gpiodevice.o
PWDd := $(shell pwd)
KERNELDIR := /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) \
	-I/usr/src/linux-3.12.6/arch/x86/include/
clean:
	rm *.o *.ko *.mod* *.order *.symvers -rf
