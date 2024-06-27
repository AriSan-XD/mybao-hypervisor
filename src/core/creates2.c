#include <creates2.h>

#include <hypercall.h>
#include <bao.h>
#include <arch/sysregs.h>
#include <page_table.h>
#include <mem.h>
#include <cpu.h>
#include <page_table.h>
#include <platform.h>
#include <cache.h>
#include <string.h>
#include <vm.h>
#include <fences.h>
#include <tlb.h>
#include <config.h>

void *copy(void *base, const size_t size)
{
    struct ppages *pages = {0};
    *pages = mem_alloc_ppages(cpu()->as.colors, NUM_PAGES(size), false);
    vaddr_t va = mem_alloc_vpage(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA, NUM_PAGES(size));
    mem_map(&cpu()->as, va, pages, NUM_PAGES(size), PTE_HYP_FLAGS);
    memcpy((void*)va, base, size);

    return (void*)va;
}
unsigned long createS2(void)
{
    // unsigned long ret = -HC_E_SUCCESS;

    uint64_t vttbr_old = 0, id_aa64mmfr0_el1 = 0, vtcr_el2 = 0;
    uint64_t vttbr_new = 0, vttbr_confirm = 0;
    size_t parange = 0;
    vaddr_t new_lvl_0_va = 0;
    paddr_t old_lvl_0_pa = 0, new_lvl_0_pa = 0;
    vttbr_old = sysreg_vttbr_el2_read();
    vtcr_el2 = sysreg_vtcr_el2_read();
    id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();

    parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;

    printk("vttbr_old: 0x%lx\n", vttbr_old);
    printk("vtcr_el2: 0x%lx\n", vtcr_el2);
    printk("id_aa64mmfr0_el1: 0x%lx\n", id_aa64mmfr0_el1);
    printk("parange: 0x%lx\n", parange); 

    old_lvl_0_pa = (((vttbr_old >> 8) & 0xfffffffff) << 8) | 0x00000000;

    // new_lvl_0_va = copy_space((void *)vttbr_old, 1u << 5);
    new_lvl_0_va = (vaddr_t)copy((void *)old_lvl_0_pa, 1u);

    if (mem_translate(&cpu()->as, new_lvl_0_va, (paddr_t *)new_lvl_0_pa))
    {
        printk("new_lvl_0_pa: 0x%lx\n", new_lvl_0_pa);
    }
    else
    {
        printk("translate falut");
    }

    vttbr_new = (vttbr_old & ~((uint64_t)0xfffffffff << 8)) | (new_lvl_0_pa & ((uint64_t)0xfffffffff << 8));
    sysreg_vttbr_el2_write(vttbr_new);

    // vttbr_new = vttbr_old + 0xff;
    // sysreg_vttbr_el2_write(vttbr_new);
    // printk("expecting no error");

    // vttbr_new = vttbr_old + 0x1ff;
    // sysreg_vttbr_el2_write(vttbr_new);
    // printk("expecting error");
    
    vttbr_confirm = sysreg_vttbr_el2_read();
    printk("vttbr_confirm: 0x%lx\n", vttbr_confirm);

    return -HC_E_SUCCESS;
}