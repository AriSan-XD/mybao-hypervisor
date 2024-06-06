KDIR := /home/arisan/HDD/src/bao-demos/wrkdir/srcs/linux-v6.1
ARCH := arm64
CROSS_COMPILE := aarch64-none-elf-
obj-m += test_hypercall.o
my_module-objs := test_hypercall.o hvc_hypercall.o

all :
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules

clean :
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) clean
