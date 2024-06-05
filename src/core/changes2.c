#include <changes2.h>

#include <hypercall.h>
#include <printk.h>
long int changeS2(void)
{
    long int ret = -HC_E_SUCCESS;

    console_printk("hello from changes2\n");

    return ret;

}