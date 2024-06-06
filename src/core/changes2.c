#include <changes2.h>

#include <hypercall.h>
#include <printk.h>
#include <bao.h>
long int changeS2(void)
{
    long int ret = -HC_E_SUCCESS;

    WARNING("hello from changes2\n");
    printk("hello from changes2\n");

    return ret;

}