#include <creates2.h>

#include <hypercall.h>
#include <bao.h>
#include <arch/sysregs.h>
#include <page_table.h>

unsigned long createS2(void)
{
    // unsigned long ret = -HC_E_SUCCESS;

    uint64_t vttbr_old = 0, id_aa64mmfr0_el1 = 0;
    size_t parange = 0;
    vttbr_old = sysreg_vttbr_el2_read();
    id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();
    parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;
    printk("vttbr_old: 0x%lx\n", vttbr_old);
    printk("parange: 0x%lx\n", parange);    

    return -HC_E_SUCCESS;
}