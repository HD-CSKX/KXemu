#ifndef __ISA_RISCV32_CORE_H__
#define __ISA_RISCV32_CORE_H__

#include "cpu/cpu.h"
#include "cpu/decoder.h"
#include "isa/riscv32/isa.h"
#include "isa/word.h"
#include "memory/memory.h"

#include <cstdint>
#include <unordered_map>

class RV32Core : public Core {
private:
    int flags;
    enum state_t {
        IDLE,
        RUNNING,
        ERROR,
        BREAK,
    } state;

    using word_t = uint32_t;
    using sword_t = int32_t;

    word_t trapCode;
    word_t trapPC;
    word_t haltPC;

    Memory *memory;
    word_t mem_read(word_t addr, int len);
    int mem_write(word_t addr, word_t data, int len);

    // decoder
    Decoder<RV32Core> decoder;
    Decoder<RV32Core> cdecoder; // for compressed instructions
    void init_decoder();
    void init_c_decoder();

    // running
    uint32_t inst;
    word_t pc;
    word_t npc;
    void execute();
    
    word_t gpr[32];
    void set_gpr(int index, word_t value);

    // do instructions
    void do_add();
    void do_sub();
    void do_and();
    void do_or();
    void do_xor();
    void do_sll();
    void do_srl();
    void do_sra();
    void do_slt();
    void do_sltu();
    
    void do_addi();
    void do_andi();
    void do_ori();
    void do_xori();
    void do_slli();
    void do_srli();
    void do_srai();
    void do_slti();
    void do_sltiu();

    void do_lb();
    void do_lbu();
    void do_lh();
    void do_lhu();
    void do_lw();

    void do_sb();
    void do_sh();
    void do_sw();

    void do_beq();
    void do_bge();
    void do_bgeu();
    void do_blt();
    void do_bltu();
    void do_bne();

    void do_jal();
    void do_jalr();

    void do_lui();
    void do_auipc();

    void do_mul();
    void do_mulh();
    void do_mulhsu();
    void do_mulhu();
    void do_div();
    void do_divu();
    void do_rem();
    void do_remu();
    
    void do_ebreak();
    void do_invalid_inst();

    // compressed instructions
    void do_c_lwsp();
    void do_c_swsp();
    
    void do_c_lw();
    void do_c_sw();

    void do_c_j();
    void do_c_jal();
    void do_c_jr();
    void do_c_jalr();

    void do_c_beqz();
    void do_c_bnez();

    void do_c_li();
    void do_c_lui();

    void do_c_addi();
    void do_c_addi16sp();
    void do_c_addi4spn();

    void do_c_slli();
    void do_c_srli();
    void do_c_srai();
    void do_c_andi();

    void do_c_mv();
    void do_c_add();
    void do_c_sub();
    void do_c_xor();
    void do_c_or();
    void do_c_and();

    // Zicsr exntension

public:
    void init(Memory *memory, int flags);
    void reset(word_t entry = INIT_PC);
    void step() override;
    bool is_error() override;
    bool is_break() override;
    bool is_running() override;

    word_t get_pc() override;
    word_t get_gpr(int idx) override;

    word_t get_trap_pc() override;
    word_t get_trap_code() override;
    word_t get_halt_pc() override;

    ~RV32Core();
};

#endif
