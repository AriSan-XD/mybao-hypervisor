#include <changes2.h>

#include <hypercall.h>
#include <bao.h>
#include <arch/psci.h>
unsigned long changeS2(void)
{
    extern void create_stage2(void);
    // unsigned long ret = -HC_E_SUCCESS;
    
    // printk("hello from changes2\n");

    // uint64_t vttbr = 0;
    
    // vttbr = sysreg_vttbr_el2_read();

    // sysreg_vttbr_el2_write(vttbr);
    // if (/* condition */)
    // {
    //     /* code */;
    // }
    // else
    // {
    //     return -HC_E_FAILURE;
    // }
    int EL = 0;
    asm (
        "mrs %0, CurrentEL"
        : "=r"(EL)
        :
        : "memory"
    );
    printk("EL: %d\n", EL >> 2);
    // create_stage2();
    uint64_t vttbr_old = 0, vttbr_new = 0;
    uint64_t new_lvl_0_pa = 0x00041000000;
    uint64_t old_lvl_0_pa = 0x0;
    vttbr_old = sysreg_vttbr_el2_read();
    printk("vttbr_old: 0x%lx\n", vttbr_old);
    old_lvl_0_pa = ((vttbr_old >> 8) & 0xfffffffff) << 8;
    printk("old_lvl_0_pa: 0x%lx\n", old_lvl_0_pa);
    for (int i = 0; i < 512 * 8; i+=8)
    {
        asm volatile (
            "ldr x4, [%0], #8\n"
            "str x4, [%1], #8\n"
            : 
            : "r"(old_lvl_0_pa + i), "r"(new_lvl_0_pa + i)
            : "x4", "memory"
        );
    }
    printk("new_lvl_0_pa: 0x%lx\n", new_lvl_0_pa);
    vttbr_new = (vttbr_old & ~((uint64_t)0xfffffffff << 8)) | (new_lvl_0_pa & ((uint64_t)0xfffffffff << 8));
    printk("vttbr_new: 0x%lx\n", vttbr_new);
    sysreg_vttbr_el2_write(vttbr_new);
    printk("vttbr_confirm: 0x%lx\n", sysreg_vttbr_el2_read());

    // printk("flushing TLB\n");
    // asm volatile("tlbi alle2\n"
    //              "dsb nsh\n"
    //              "isb\n" ::: "memory");
    // printk("TLB fulshed\n");

    return -HC_E_SUCCESS;

}