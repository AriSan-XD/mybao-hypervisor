    .section .text
    .globl hvc_call
    .type hvc_call, @function
hvc_call:
    mov x0, #2       // Set the hypercall number (2 in this case)
    hvc #0           // Make the hypercall
    ret              // Return from the function
