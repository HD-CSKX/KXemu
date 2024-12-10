#include "isa/riscv32/core.h"
#include "isa/riscv32/riscv32.h"
#include "log.h"
#include "macro.h"
#include "common.h"

void RV32Core::init(Memory *memory, int flags) {
    this->memory = memory;
    this->flags = flags;
    this->state = IDLE;

    this->init_decoder();
}

void RV32Core::reset() {
    this->pc = INIT_PC;
    this->state = RUNNING;
}

void RV32Core::step() {
    if (likely(this->state == RUNNING)) {
        this->execute();
        this->pc = this->npc;
    } else {
        WARN("Core is not running, nothing to do.");
    }
}

void RV32Core::execute() {
    this->inst = this->memory->read(this->pc, 4);
    bool valid = this->decoder.decode_and_exec(this->inst);
    if (!valid) {
        this->do_invalid_inst();
    }
}

word_t RV32Core::mem_read(word_t addr, int len) {
    return this->memory->read(addr, len);
}

int RV32Core::mem_write(word_t addr, word_t data, int len) {
    this->memory->write(addr, data, len);
    return 0;
}

void RV32Core::do_invalid_inst() {
    this->state = ERROR;
    this->haltPC = this->pc;
    WARN("Invalid instruction at pc=" FMT_WORD ", inst=" FMT_WORD, this->pc, this->inst);
}

void RV32Core::set_gpr(int index, word_t value) {
    if (likely(index != 0)) {
        this->gpr[index] = value;
        DEBUG("set gpr[%d] = " FMT_WORD_32, index, value);
    }
}

bool RV32Core::is_error() {
    return this->state == ERROR;
}

bool RV32Core::is_break() {
    return this->state == BREAK;
}

word_t RV32Core::get_pc() {
    return this->pc;
}

word_t RV32Core::get_gpr(int idx) {
    if (idx >= 32 || idx < 0) {
        WARN("GPR index=%d out of range, return 0 instead.", idx);
        return 0;
    }
    return gpr[idx];
}

word_t RV32Core::get_trap_pc() {
    return this->trapPC;
}

word_t RV32Core::get_trap_code() {
    return this->trapCode;
}

word_t RV32Core::get_halt_pc() {
    return this->haltPC;
}

RV32Core::~RV32Core() {}
