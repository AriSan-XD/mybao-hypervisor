#include <changes2.h>

#include <hypercall.h>
#include <bao.h>
unsigned long changeS2(void)
{
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
    uint64_t vttbr_old = 0, vttbr_new = 0;
    vttbr_old = sysreg_vttbr_el2_read();
    vttbr_new = vttbr_old + 0xff;
    sysreg_vttbr_el2_write(vttbr_new);
    // printk("expecting no error");
    // printk("vttbr_old: 0x%lx\n", vttbr_old);
    // printk("vttbr_new: 0x%lx\n", vttbr_new);

    return -HC_E_SUCCESS;

}