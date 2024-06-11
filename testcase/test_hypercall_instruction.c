#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

// Enable performance counters and configure them for counting instructions
static void enable_instruction_counter(void) {
    uint64_t value;

    // Enable user-mode access to the performance counter
    asm volatile ("mrs %0, pmuserenr_el0" : "=r" (value));
    value |= 1;  // Set the EN bit
    asm volatile ("msr pmuserenr_el0, %0" : : "r" (value));

    // Enable performance counters and reset all counters
    asm volatile ("mrs %0, pmcr_el0" : "=r" (value));
    value |= 1 | (1 << 2);  // Set the E bit to enable counting and C bit to reset all counters
    asm volatile ("msr pmcr_el0, %0" : : "r" (value));

    // Select counter 0
    asm volatile ("msr pmselr_el0, %0" : : "r" (0));
    asm volatile ("isb");  // Instruction Synchronization Barrier to ensure selection is made

    // Set event type to 0x08 (instructions retired) for counter 0
    asm volatile ("msr pmxevtyper_el0, %0" : : "r" (0x08));

    // Enable counter 0
    asm volatile ("mrs %0, pmcntenset_el0" : "=r" (value));
    value |= 1 << 0;  // Enable counter 0
    asm volatile ("msr pmcntenset_el0, %0" : : "r" (value));
}


// Measure instructions executed during the HVC call
static inline uint64_t measure_hvc_instructions(void) {
    uint64_t start, end;

    asm volatile (
        "mov x0, #0xC6000000\n"     // Set the handler entry
        "add x0, x0, #0x2\n"        // Set the hypercall number (2 in this case)
        "mrs %0, pmxevcntr_el0\n"  // Read start instruction count
        "isb\n"
        "hvc #0\n"                 // Make the hypercall
        "mrs %1, pmxevcntr_el0\n"  // Read end instruction count
        "isb\n"
        : "=r" (start), "=r" (end)  // Output operands
        :                            // Input operands
        : "x0"                       // Clobber list
    );

    return end - start;
}

static int __init my_module_init(void)
{
    unsigned long flags;
    local_irq_save(flags); // close interrupts

    uint64_t instructions;

    printk(KERN_INFO "Initializing my_module\n");
    // Enable instruction counter
    enable_instruction_counter();
    for(int i = 0; i < 100; i++)
    {
        // Measure instructions for HVC call
        instructions = measure_hvc_instructions();
        printk(KERN_INFO "hvc call executed %llu instructions\n", instructions);
    }

    local_irq_restore(flags); // open interrupts

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
MODULE_DESCRIPTION("A kernel module to invoke hypercall #2 using hvc instruction and measure instructions executed with PMXEVTYPER_EL0");
