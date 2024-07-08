#include <creates2.h>

#include <hypercall.h>
#include <bao.h>
unsigned long createS2(void)
{

    uint64_t vttbr_old = 0;
    
    uint64_t old_lvl_0_pa = 0, new_lvl_0_pa = 0;
    uint64_t content = 0;

    // uint64_t id_aa64mmfr0_el1 = 0, vtcr_el2 = 0;
    // size_t parange = 0;
    // uint64_t sctrl_saved = 0, sctrl_new = 0;
   
    // vtcr_el2 = sysreg_vtcr_el2_read();
    // id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();
    // parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;
 
    // printk("vtcr_el2: 0x%lx\n", vtcr_el2);
    // printk("id_aa64mmfr0_el1: 0x%lx\n", id_aa64mmfr0_el1);
    // printk("parange: 0x%lx\n", parange);

    vttbr_old = sysreg_vttbr_el2_read();
    printk("vttbr_old: 0x%lx\n", vttbr_old);
    old_lvl_0_pa = ((((vttbr_old >> 1) >> 7) & 0xfffffffff) << 8);
    printk("lvl_0_pa: 0x%lx\n", old_lvl_0_pa);

    asm volatile (   
        "ldr %0, [%1]\n"
        : "=r" (content)
        : "r" (old_lvl_0_pa)
        : "x3", "x4", "memory");

    printk("content of 0x%lx: 0x%lx\n", old_lvl_0_pa, content);
    
    new_lvl_0_pa = 0x00041000000;

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

    asm volatile (   
        "ldr %0, [%1]\n"
        : "=r" (content)
        : "r" (new_lvl_0_pa)
        : "x3", "x4", "memory");

    printk("content of 0x%lx: 0x%lx\n", new_lvl_0_pa, content);

    return -HC_E_SUCCESS;
}