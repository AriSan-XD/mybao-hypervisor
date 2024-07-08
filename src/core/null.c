#include <null.h>
#include <hypercall.h>
unsigned long null(void)
{
    return -HC_E_SUCCESS;
}