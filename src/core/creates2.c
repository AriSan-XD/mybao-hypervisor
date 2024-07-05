#include <creates2.h>

#include <hypercall.h>
#include <bao.h>
#include <arch/sysregs.h>
#include <mem.h>
#include <cpu.h>
#include <page_table.h>
#include <cache.h>
#include <string.h>
#include <vm.h>
#include <fences.h>
#include <tlb.h>

unsigned long createS2(void)
{
    // unsigned long ret = -HC_E_SUCCESS;
    // uint64_t flat_offset = 0xfd8000000000;
    uint64_t vttbr_old = 0, id_aa64mmfr0_el1 = 0, vtcr_el2 = 0, lvl_0_pa = 0;
    // // uint64_t vttbr_new = 0, vttbr_confirm = 0;
    size_t parange = 0;
    // // vaddr_t new_lvl_0_va = 0;
    // vaddr_t assume_lvl_0_va = 0;
    // paddr_t old_lvl_0_pa = 0, new_lvl_0_pa = 0;
    vttbr_old = sysreg_vttbr_el2_read();
    vtcr_el2 = sysreg_vtcr_el2_read();
    id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();

    parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;

    printk("vttbr_old: 0x%lx\n", vttbr_old);
    printk("vtcr_el2: 0x%lx\n", vtcr_el2);
    printk("id_aa64mmfr0_el1: 0x%lx\n", id_aa64mmfr0_el1);
    printk("parange: 0x%lx\n", parange);

    lvl_0_pa = ((((vttbr_old >> 1) >> 7) & 0xffffffff) << 12);
    // assume_lvl_0_va = old_lvl_0_pa + flat_offset;
    printk("old_lvl_0_pa: 0x%lx\n", lvl_0_pa);
    // printk("assume_lvl_0_va: 0x%lx\n", assume_lvl_0_va);
    // // printk("value of assume_lvl_0_va: 0x%lx\n", *((uint64_t
    // // *)assume_lvl_0_va));
    // // printk("as: %d\n", &cpu()->as);
    // if (mem_translate(AS_HYP, assume_lvl_0_va, &new_lvl_0_pa)) {
    //     printk("new_lvl_0_pa: 0x%lx\n", new_lvl_0_pa);
    // } else {
    //     printk("translate falut");
    // }

    // new_lvl_0_va = copy_space((void *)vttbr_old, 1u << 5);
    // new_lvl_0_va = (vaddr_t)copy((void *)old_lvl_0_pa, 1u);
    // printk("copy done");

    // if (mem_translate(&cpu()->as, new_lvl_0_va, (paddr_t *)new_lvl_0_pa))
    // {
    //     printk("new_lvl_0_pa: 0x%lx\n", new_lvl_0_pa);
    // }
    // else
    // {
    //     printk("translate falut");
    // }

    // vttbr_new = (vttbr_old & ~((uint64_t)0xfffffffff << 8)) |
    //             (new_lvl_0_pa & ((uint64_t)0xfffffffff << 8));
    // printk("vttbr_new: 0x%lx\n", vttbr_new);
    // sysreg_vttbr_el2_write(vttbr_new);

    // vttbr_new = vttbr_old + 0xff;
    // sysreg_vttbr_el2_write(vttbr_new);
    // printk("expecting no error");

    // vttbr_new = vttbr_old + 0x1ff;
    // sysreg_vttbr_el2_write(vttbr_new);
    // printk("expecting error");

    // vttbr_confirm = sysreg_vttbr_el2_read();
    // printk("vttbr_confirm: 0x%lx\n", vttbr_confirm);

    // uint64_t flat_offset = 0x1111;
    // vaddr_t va = &flat_offset;
    // paddr_t par = 0, par_saved = 0;
    // printk("va of flat_offset: 0x%lx\n", va);
    // par_saved = sysreg_par_el1_read();
    // printk("par_saved: 0x%lx\n", par_saved);
    // arm_at_s1e2w(&flat_offset);
    // ISB();
    // par = sysreg_par_el1_read();
    // printk("par: 0x%lx\n", par);
    // sysreg_par_el1_write(par_saved);

    // printk("pa = 0x%lx\n", (par & PAR_PA_MSK) | (va & (PAGE_SIZE - 1)));

    // size_t lvl = 0;
    // pte_t *pte = pt_get_pte(&ass->pt, lvl, vas);
    // while (!pte_page(&ass->pt, pte, lvl)) {
    //     lvl += 1;
    //     pte = pt_get_pte(&ass->pt, lvl, vas);
    // }

    return -HC_E_SUCCESS;
}