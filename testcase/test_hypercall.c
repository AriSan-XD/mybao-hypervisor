#include <linux/module.h>
#include <linux/kernel.h>

// Declare the assembly function
extern void hvc_call(void);

static int __init my_module_init(void)
{
    printk(KERN_INFO "Initializing my_module\n");
    // Call the assembly function
    hvc_call();
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
