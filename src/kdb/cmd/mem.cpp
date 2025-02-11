#include "kdb/kdb.h"
#include "kdb/cmd.h"
#include "device/bus.h"
#include "device/memory.h"
#include "utils/utils.h"
#include "log.h"

#include <exception>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

using namespace kxemu;
using namespace kxemu::kdb;
using kxemu::kdb::word_t;
using kxemu::device::Memory;

static int cmd_mem_create(const cmd::args_t &);
static int cmd_mem_img   (const cmd::args_t &);
static int cmd_mem_elf   (const cmd::args_t &);
static int cmd_mem_map   (const cmd::args_t &);
static int cmd_mem_save  (const cmd::args_t &);

static const cmd::cmd_map_t cmdMap = {
    {"create"   , cmd_mem_create},
    {"img"      , cmd_mem_img   },
    {"elf"      , cmd_mem_elf   },
    {"map"      , cmd_mem_map   },
    {"save"     , cmd_mem_save  },
};

static bool check_memory_initialized() {
    if (kdb::bus == nullptr) {
        std::cout << "Memory not initialized" << std::endl;
        return false;
    }
    return true;
}

static int cmd_mem_create(const std::vector<std::string> &args) {
    if (!check_memory_initialized()) return cmd::MissingPrevOp;

    if (args.size() < 5) {
        std::cout << "Usage: mem create <name> <addr> <size> [type]" << std::endl;
        return cmd::InvalidArgs;
    }

    std::string name;
    word_t start, size;
    name = args[2];
    try {
        start = utils::string_to_unsigned(args[3]);
        size = utils::string_to_unsigned(args[4]);
    } catch (std::exception &) {
        std::cout << "Usage: mem create <name> <addr> <size> [type]" << std::endl;
        return cmd::InvalidArgs;
    }
    
    bool s = kdb::bus->add_memory_map(name, start, size, new Memory(size));
    if (s) {
        std::cout << "Create new memory map " << name << " at " << FMT_STREAM_WORD(start) << " with size=" << size << std::endl;
        return cmd::Success;
    } else {
        return cmd::CmdError;
    }
}

static int cmd_mem_img(const cmd::args_t &args) {
    const std::string filename = args[2];
    if (!check_memory_initialized()) return cmd::MissingPrevOp;

    std::ifstream f;
    f.open(filename, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "FileNotFound: No such file: " << filename << std::endl;
        return cmd::CmdError;
    }

    kdb::bus->load_from_stream(f, 0x80000000);

    return cmd::Success;
}

// load elf to memory and switch the program entry
static int cmd_mem_elf(const cmd::args_t &args) {
    if (args.size() < 3) {
        std::cout << "Missing elf file path" << std::endl;
        return cmd::InvalidArgs;
    }
    const std::string filename = args[2];
    word_t entry = kdb::load_elf(filename);
    if (entry == 0) {
        std::cout << "Error when load elf files" << std::endl;
        return cmd::CmdError;
    }
    std::cout << "Load ELF file success." << std::endl;
    std::cout << "Switch entry to " << FMT_STREAM_WORD(entry) << "." << std::endl;
    kdb::programEntry = entry;
    return cmd::Success;
}

static int cmd_mem_map(const cmd::args_t &) {
    if (kdb::bus->memoryMaps.empty()) {
        std::cout << "There is no any memory map." << std::endl;
        return cmd::Success;
    }

    std::cout << "Memory mapping info" << std::endl;
    std::cout << std::setfill(' ')
    << std::setw(10)  << "name" << " | "
    << std::setw(WORD_WIDTH + 2) << "start" << " | "
    << std::setw(WORD_WIDTH + 2) << "size" << " | "
    << "type"
    << std::setw(8) << std::endl;

    for (auto &m : kdb::bus->memoryMaps) {
        std::cout << std::setfill(' ')
        << std::setw(10) << m->name << " | "
        << FMT_STREAM_WORD(m->start)  << " | "
        << FMT_STREAM_WORD(m->length) << " | "
        << std::setw(6) << m->map->get_type_name() << std::endl;
    }
    return cmd::Success;
}

static int cmd_mem_save(const cmd::args_t &args) {
    if (args.size() < 3) {
        std::cout << "Usage: mem save <start> <length> <filename>" << std::endl;
        return cmd::InvalidArgs;
    }

    word_t start, length;
    std::string filename;
    try {
        start  = utils::string_to_unsigned(args[2]);
        length = utils::string_to_unsigned(args[3]);
        filename = args[4];
    } catch (std::exception &) {
        std::cout << "Usage: mem save <start> <length> <filename>" << std::endl;
        return cmd::InvalidArgs;
    }

    std::ofstream f;
    f.open(filename, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "Error open file " << filename << std::endl;
        return cmd::CmdError;
    }
    
    if (kdb::bus->dump(f, start, length)) {
        std::cout << "Save memory from " << FMT_STREAM_WORD(start) << " to " << FMT_STREAM_WORD(start + length) << " to " << filename << std::endl;
    } else {
        std::cout << "Error save memory to file " << filename << std::endl;
        f.close();
        return cmd::CmdError;
    }
    return cmd::Success;
}

int cmd::mem(const cmd::args_t &args) {
    int r = cmd::find_and_run(args, cmdMap, 1);
    if (r == EmptyArgs) {
        std::cout << "Usage: mem <create|img|elf>" << std::endl;
        return Success;
    } else if (r == CmdError) {
        std::cout << "Error running command " << args[1] << std::endl;
    } else if (r == InvalidArgs) {
        std::cout << "Invalid arguments for command " << args[1] << std::endl;
    }
    return r;
}


