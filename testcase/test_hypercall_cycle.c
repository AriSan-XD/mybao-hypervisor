#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static void enable_cycle_counter(void) {
    uint64_t value;

    // Enable user-mode access to the performance counter
    asm volatile ("mrs %0, pmuserenr_el0" : "=r" (value));
    value |= 1;  // Set the EN bit
    asm volatile ("msr pmuserenr_el0, %0" : : "r" (value));

    // Enable cycle counter and reset all counters
    asm volatile ("mrs %0, pmcr_el0" : "=r" (value));
    value |= 1 | (1 << 2);  // Set the E bit to enable counting, and C bit to reset all counters
    asm volatile ("msr pmcr_el0, %0" : : "r" (value));

    // Enable cycle counter
    asm volatile ("mrs %0, pmcntenset_el0" : "=r" (value));
    value |= 1 << 31;  // Set the C bit to enable the cycle counter
    asm volatile ("msr pmcntenset_el0, %0" : : "r" (value));
}
static inline uint64_t hvc_call(void) {
    uint64_t start, end;
    asm volatile (
        "mov x0, #0xC6000000\n"     // Set the handler entry
        "add x0, x0, #0x2\n"        // Set the hypercall number (2 in this case)
        "mrs %0, pmccntr_el0\n"     // Read start counter
        "isb\n"
        "hvc #0\n"                  // Make the hypercall
        "mrs %1, pmccntr_el0\n"     // Read end counter
        "isb\n"
        : "=r" (start), "=r" (end)  // Output operands
        :               // No input
        : "x0"          // Clobber list
    );
    return end - start;
}

static int __init my_module_init(void)
{
    unsigned long flags;
    local_irq_save(flags); //close interrupt

    uint64_t cycles;

    enable_cycle_counter();

    printk(KERN_INFO "Initializing my_module\n");

    for(int i = 0; i < 100; i++)
    {
        cycles = hvc_call();             // Call the inline assembly function
        printk(KERN_INFO "hvc call took %llu cycles\n", cycles);
    }

    local_irq_restore(flags); // open interrupt
    
    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Exiting my_module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple kernel module to invoke hypercall #2 using hvc instruction");