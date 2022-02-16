## 
 # Bao, a Lightweight Static Partitioning Hypervisor 
 #
 # Copyright (c) Bao Project (www.bao-project.org), 2019-
 #
 # Authors:
 #      Sandro Pinto <sandro@bao-project.org>
 #
 # Bao is free software; you can redistribute it and/or modify it under the
 # terms of the GNU General Public License version 2 as published by the Free
 # Software Foundation, with a special exception exempting guest code from such
 # license. See the COPYING file in the top-level directory for details. 
 #
##

cpu-objs-y+=$(ARCH_PROFILE)/cpu.o
cpu-objs-y+=$(ARCH_PROFILE)/mem.o
cpu-objs-y+=$(ARCH_PROFILE)/vmm.o
cpu-objs-y+=$(ARCH_PROFILE)/vm.o
cpu-objs-y+=$(ARCH_PROFILE)/exceptions.o