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

    uint64_t vttbr_old = 0, id_aa64mmfr0_el1 = 0, vtcr_el2 = 0, lvl_0_pa = 0;
    uint64_t content = 0;
    size_t parange = 0;

    vttbr_old = sysreg_vttbr_el2_read();
    vtcr_el2 = sysreg_vtcr_el2_read();
    id_aa64mmfr0_el1 = sysreg_id_aa64mmfr0_el1_read();

    parange = id_aa64mmfr0_el1 & ID_AA64MMFR0_PAR_MSK;

    printk("vttbr_old: 0x%lx\n", vttbr_old);
    printk("vtcr_el2: 0x%lx\n", vtcr_el2);
    printk("id_aa64mmfr0_el1: 0x%lx\n", id_aa64mmfr0_el1);
    printk("parange: 0x%lx\n", parange);

    lvl_0_pa = ((((vttbr_old >> 1) >> 7) & 0xffffffff) << 12);
    printk("lvl_0_pa: 0x%lx\n", lvl_0_pa);

    asm volatile (
    "mrs x3, SCTLR_EL2\n" 
	"bic x3, x3, #0x7\n"	
	"msr SCTLR_EL2, x3\n" 
    
    "ldr %0, [%1]\n"

    "ldr x4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)\n"
	"msr SCTLR_EL2, x4\n"
    : "=r" (content)
    : "r" (lvl_0_pa)
    : "x3", "x4", "memory");

    printk("content of 0x%lx: 0x%lx\n", lvl_0_pa, content);
    
/*
    uint64_t src, dst = 0x00041000000;
    uint64_t num_words = 512;
    // Inline assembly to copy the 4KB page
    asm volatile (
        // Extract physical base address from VTTBR_EL2
        "mrs %0, VTTBR_EL2\n\t"          // Move VTTBR_EL2 to src
        "lsr %0, %0, #8\n\t"             // Logical shift right by 8 bits
        "and %0, %0, #0xfffffffff\n\t"   // Mask the lower 36 bits
        "lsl %0, %0, #8\n\t"             // Logical shift left by 8 bits
        
        // Setup loop variables
        "mov x1, %1\n\t"                 // Move dst to x1
        "mov x2, %2\n\t"                 // Move num_words to x2
        
        "1:\n\t"
        "ldr x4, [%0], #8\n\t"           // Load 8 bytes from source and increment source pointer
        "str x4, [x1], #8\n\t"           // Store 8 bytes to destination and increment destination pointer
        "subs x2, x2, #1\n\t"            // Decrement loop counter
        "b.ne 1b\n\t"                    // If counter is not zero, branch to 1
        
        : "=&r"(src)                     // Output operand, src register (modified)
        : "r"(dst), "r"(num_words)       // Input operands, dst and num_words
        : "x0", "x1", "x2", "x4"         // Clobbered registers
    );
*/


    return -HC_E_SUCCESS;
}