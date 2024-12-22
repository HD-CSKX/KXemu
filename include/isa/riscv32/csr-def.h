#ifndef __ISA_RISCV32_CSR_DEF_H__
#define __ISA_RISCV32_CSR_DEF_H__

#define CSR_READ_ONLY  0b110000000000
#define IS_CSR_READ_ONLY(addr) ((addr & CSR_READ_ONLY) == CSR_READ_ONLY)

#define CSR_MISA   0xF10

#define CSR_MSTATUS  0x300
#define CSR_MEDELEG  0x302
#define CSR_MIDELEG  0x303
#define CSR_MIE      0x304
#define CSR_MTVEC    0x305
#define CSR_MEDELEGH 0x312

#define CSR_MEPC    0x341
#define CSR_MCAUSE  0x342
#define CSR_MTVAL   0x343
#define CSR_MIP     0x344

#define CSR_SSTATUS 0x100
#define CSR_SIE     0x104
#define CSR_STVEC   0x105

#define CSR_SEPC    0x141
#define CSR_SCAUSE  0x142
#define CSR_STVAL   0x143
#define CSR_SIP     0x144

#define CSR_SATP    0x180

#define MISA_A (1 <<  0) // Atomic Extension
#define MISA_B (1 <<  1) // B Extesnion
#define MISA_C (1 <<  2) // Compressed Extension
#define MISA_D (1 <<  3) // Double-precision Extension
#define MISA_E (1 <<  4) // RV32E/RV64E Base ISA
#define MISA_F (1 <<  5) // Single-precision Extension
#define MISA_H (1 <<  7) // Hypervisor Extension
#define MISA_I (1 <<  8) // RV32I/RV64I/RV128I Base ISA
#define MISA_M (1 << 12) // Integer Mutiply/Divide Extension
#define MISA_Q (1 << 16) // Quad-precision floating-point Extension
#define MISA_S (1 << 18) // Supervisor mode Implemented
#define MISA_U (1 << 20) // User mode Implemented
#define MISA_V (1 << 21) // Vector Extension

#define MSTATUS_SIE_OFF  1
#define MSTATUS_SPIE_OFF 5
#define MSTATUS_SPP_OFF  8

#define MSTATUS_MIE_OFF  3
#define MSTATUS_MPIE_OFF 7
#define MSTATUS_MPP_OFF  11
#define MSTATUS_MPRV_OFF 17

#define MSTATUS_SIE_MASK  (1 << 1)
#define MSTATUS_SPIE_MASK (1 << 5)

#define MSTATUS_SPP_MASK (1 << MSTATUS_SPP_OFF)

#define MSTATUS_MIE_MASK  (1 << MSTATUS_MIE_OFF)
#define MSTATUS_MPIE_MASK (1 << MSTATUS_MPIE_OFF)
#define MSTATUS_MPP_MASK  (3 << MSTATUS_MPP_OFF)
#define MSTATUS_MPRV_MASK (1 << MSTATUS_MPRV_OFF)

#define TVEC_MODE_MASK 0x3
#define TVEC_MODE_DIRECT 0
#define TVEC_MODE_VECTORED 1

#define SSTATUS_MASK 0b10000000000011011110011101100010

#endif