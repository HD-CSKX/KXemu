#include "kdb/kdb.h"
#include "cpu/cpu.h"
#include "log.h"
#include "isa/isa.h"
#include "common.h"

CPU *kdb::cpu = nullptr;

void kdb::init() {
    init_memory();

    logFlag = DEBUG | INFO | WARN | PANIC;

    cpu = new ISA_CPU();
    cpu->init(memory, 0, 1);
    cpu->reset();

    INFO("Init %s CPU", ISA_NAME);
}

void kdb::deinit() {
    delete cpu;
    cpu = nullptr;
}

int kdb::run_cpu() {
    while (!cpu->has_break()) {
        cpu->step();
    }

    Core *core = cpu->get_core(0);
    if (core->is_error()) {
        INFO(FMT_FG_RED "Error" FMT_FG_BLUE "at pc=" FMT_WORD, core->get_trap_pc());
        return 1;
    }

    int r = core->get_trap_code();
    if (r == 0) {
        INFO(FMT_FG_GREEN "HIT GOOD TRAP " FMT_FG_BLUE "at pc=" FMT_WORD, core->get_trap_pc()); 
    } else {
        INFO(FMT_FG_RED "HIT BAD TRAP " FMT_FG_BLUE "at pc=" FMT_WORD, core->get_trap_pc());
    }
    return r;
}
