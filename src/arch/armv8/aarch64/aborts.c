/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <cpu.h>

void internal_abort_handler(unsigned long gprs[])
{
    for (size_t i = 0; i < 31; i++) {
        console_printk("x%d:\t\t0x%0lx\n", i, gprs[i]);
    }
    console_printk("SP:\t\t0x%0lx\n", gprs[31]);
    console_printk("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    console_printk("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
    console_printk("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("cpu%d internal hypervisor abort - PANIC\n", cpu()->id);
}
