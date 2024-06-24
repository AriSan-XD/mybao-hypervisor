/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <hypercall.h>
#include <cpu.h>
#include <vm.h>
#include <ipc.h>
#include <changes2.h>
#include <creates2.h>

long int hypercall(unsigned long id) {
    long int ret = -HC_E_INVAL_ID;

    unsigned long ipc_id = vcpu_readreg(cpu()->vcpu, HYPCALL_ARG_REG(0));
    unsigned long arg1   = vcpu_readreg(cpu()->vcpu, HYPCALL_ARG_REG(1));
    unsigned long arg2   = vcpu_readreg(cpu()->vcpu, HYPCALL_ARG_REG(2));

    switch(id){
        case HC_IPC:
            WARNING("handle in HC_IPC");
            ret = ipc_hypercall(ipc_id, arg1, arg2);
            break;
        case HC_CHANGE_S2:
            WARNING("handle in HC_CHANGE_S2"); 
            ret = changeS2();
            break;
        case HC_CREATE_S2:
            WARNING("handle in HC_CREATE_S2"); 
            ret = createS2();
            break;
        default:
            WARNING("Unknown hypercall id %d", id);
    }

    return ret;
}
