#include "device/uart.h"
#include "isa/word.h"
#include "kdb/kdb.h"
#include <string>

std::vector<Uart16650 *> kdb::uart::list;

static bool add_uart_map(word_t base, Uart16650 *uart) {
    if (!kdb::memory->add_memory_map("uart" + std::to_string(kdb::uart::list.size()), base, UART_LENGTH, uart)) {
        // Add memory map failed, free
        delete uart;
        return false;
    }
    kdb::uart::list.push_back(uart);
    return true; 
}

bool kdb::uart::add(word_t base, std::ostream &os) {
    Uart16650 *uart = new Uart16650();
    if (!add_uart_map(base, uart)) {
        return false;
    }
    uart->set_output_stream(os);
    return true;
}

bool kdb::uart::add(word_t base, const std::string &ip, int port) {
    Uart16650 *uart = new Uart16650();
    if (!add_uart_map(base, uart)) {
        return false;
    }
    uart->open_socket(ip, port);
    return true;
}

bool kdb::uart::puts(std::size_t index, const std::string &s) {
    if (index >= kdb::uart::list.size()) {
        return false;
    }
    for (char c : s) {
        kdb::uart::list[index]->putch(c);
    }
    return true;
}
