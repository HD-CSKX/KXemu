.section entry, "ax"
.globl _start

_start:
    la sp, _stack_pointer # load stack pointer
    call __run_main
l:
    j l
