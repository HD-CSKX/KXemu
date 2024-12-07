#ifndef __ISA_RISCV32_CPU_H__
#define __ISA_RISCV32_CPU_H__

#include "cpu/cpu.h"
#include "isa/riscv/core.h"

class RV32CPU : public CPU {
private:    
    RV32Core *core;

public:
    void init(Memory *memory, int flags, int coreCount) override;
    void reset() override;
    void step() override;
    bool has_break() override;

    Core *getCore(int coreID) override;

    ~RV32CPU() override;
};

#endif
