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

    Core *core = cpu->getCore(0);
    if (core->is_error()) {
        INFO(FMT_COLOR_RED "Error" FMT_COLOR_BLUE "at pc=" FMT_WORD, core->trapPC);
        return 1;
    }

    int r = core->trapCode;
    if (r == 0) {
        INFO(FMT_COLOR_GREEN "HIT GOOD TRAP " FMT_COLOR_BLUE "at pc=" FMT_WORD, core->trapPC); 
    } else {
        INFO(FMT_COLOR_RED "HIT BAD TRAP " FMT_COLOR_BLUE "at pc=" FMT_WORD, core->trapPC);
    }
    return r;
}
