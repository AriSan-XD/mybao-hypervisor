#include <changes2.h>

#include <hypercall.h>
#include <bao.h>
unsigned long changeS2(void)
{
    // unsigned long ret = -HC_E_SUCCESS;
    // extern void create_stage2(void);
    // create_stage2();

    uint64_t vttbr_old = 0, vttbr_new = 0;
    uint64_t new_lvl_0_pa = 0x00041000000;
    uint64_t old_lvl_0_pa = 0x0;
    vttbr_old = sysreg_vttbr_el2_read();

    printk("vttbr_old: 0x%lx\n", vttbr_old);
    old_lvl_0_pa = ((vttbr_old >> 8) & 0xfffffffff) << 8;
    
    vttbr_new = (vttbr_old & ~((uint64_t)0xfffffffff << 8)) | (new_lvl_0_pa & ((uint64_t)0xfffffffff << 8));
    // printk("vttbr_new: 0x%lx\n", vttbr_new);
    sysreg_vttbr_el2_write(vttbr_new);

    printk("flushing TLB\n");
    asm volatile("tlbi alle2\n"
                 "dsb nsh\n"
                 "isb\n" ::: "memory");
    printk("TLB fulshed\n");

    printk("vttbr_confirm: 0x%lx\n", sysreg_vttbr_el2_read());

    return -HC_E_SUCCESS;

}