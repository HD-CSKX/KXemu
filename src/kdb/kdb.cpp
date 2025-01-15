#include "kdb/kdb.h"
#include "cpu/cpu.h"
#include "isa/isa.h"
#include "kdb/rsp.h"
#include "log.h"
#include "isa/isa.h"
#include "isa/word.h"
#include "utils/utils.h"

#include <exception>
#include <fstream>
#include <string>
#include <iostream>

using namespace kxemu;
using kxemu::cpu::CPU;
using kxemu::cpu::ISA_CPU;

CPU *kdb::cpu = nullptr;
word_t kdb::programEntry;
int kdb::returnCode = 0;

void kdb::init() {
    init_bus();

    logFlag = DEBUG | INFO | WARN | PANIC;

    cpu = new ISA_CPU();
    cpu->init(bus, RVFlag::C | RVFlag::M | RVFlag::Zicsr | RVFlag::Priv, 1);
    cpu->reset(INIT_PC);
    programEntry = INIT_PC;

    INFO("Init %s CPU", ISA_NAME);
}

void kdb::deinit() {
    delete cpu;
    cpu = nullptr;
}

// run .kdb source file to exec kdb command
int kdb::run_source_file(const std::string &filename) {
    std::ifstream f;
    f.open(filename, std::ios::in);
    if (!f.is_open()) {
        std::cout << "FileNotFound: No such file: " << filename << std::endl;
        return 1;
    }

    std::string cmdLine;
    while (std::getline(f, cmdLine)) {
        run_command(cmdLine);
    }
    return 0;
}

word_t kdb::string_to_addr(const std::string &s, bool &success) {
    success = false;
    word_t addr = -1;
    try {
        addr = ::utils::string_to_word(s);
        success = true;
        return addr;
    } catch (std::exception &) {}
    
    for (auto iter : kdb::symbolTable) {
        if (iter.second == s) {
            addr = iter.first;
            success = true;
        }
    }
    return addr;
}

bool kdb::start_rsp(int port) {
    rsp::rsp_mainloop(port);
    return true;
}
