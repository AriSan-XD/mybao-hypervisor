#include <creates2.h>

#include <hypercall.h>
#include <bao.h>
#include <arch/sysregs.h>
#include <page_table.h>

unsigned long createS2(void)
{
    // unsigned long ret = -HC_E_SUCCESS;

    uint64_t vttbr_old = 0, id_aa64mmfr0_el1 = 0, vtcr_el2 = 0;
    uint64_t vttbr_new = 0, vttbr_confirm = 0;
    size_t parange = 0;
    vttbr_old = sysreg_vttbr_el2_read();
    vtcr_el2 = sysreg_vtcr_el2_read();
    id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();

    parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;

    printk("vttbr_old: 0x%lx\n", vttbr_old);
    printk("vtcr_el2: 0x%lx\n", vtcr_el2);
    printk("id_aa64mmfr0_el1: 0x%lx\n", id_aa64mmfr0_el1);
    printk("parange: 0x%lx\n", parange);    

    // printk("*vttbr_old: 0x%lx\n", ((uint64_t *)vttbr_old)[0]);
    // printk("*vttbr_old+8: 0x%lx\n", ((uint64_t *)vttbr_old)[1]);
    vttbr_new = vttbr_old + 0x4000;
    sysreg_vttbr_el2_write(vttbr_new);
    vttbr_confirm = sysreg_vttbr_el2_read();
    printk("vttbr_confirm: 0x%lx\n", vttbr_confirm);

    return -HC_E_SUCCESS;
}