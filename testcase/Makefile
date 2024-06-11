KDIR := /home/arisan/HDD/src/bao-demos/wrkdir/srcs/linux-v6.1
ARCH := arm64
CROSS_COMPILE := aarch64-none-elf-
obj-m += test_hypercall_cycle.o test_hypercall_cycle_no_intr.o test_hypercall_instruction.o

all :
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules

clean :
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) clean
