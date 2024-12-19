#ifndef __ISA_H__
#define __ISA_H__

#include <stdint.h>

#define NR_REGS 32

typedef struct Context {
    uintptr_t gpr[NR_REGS], mcause, mstatus, mepc;
    void *pdir;
} Context;

#ifdef __riscv_e
#define GPR1 gpr[15] // a5
#else
#define GPR1 gpr[17] // a7
#endif

#define GPR2 gpr[10]
#define GPR3 gpr[11]
#define GPR4 gpr[12]
#define GPRx gpr[10]

#define IRQ_TIMER 0x80000007 // timer interrupt

#endif
