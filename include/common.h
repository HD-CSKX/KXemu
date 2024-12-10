#ifndef __COMMON_H__
#define __COMMON_H__

#include <cinttypes>
#include <iomanip>

#define FMT_WORD_64 "0x%016" PRIx64
#define FMT_WORD_32 "0x%08" PRIx32

#ifdef ISA_64
    #define FMT_WORD FMT_WORD_64
    #define WORD_SIZE 64
    #define WORD_WIDTH 16
    using word_t = uint64_t;
#else
    #define FMT_WORD FMT_WORD_32
    #define WORD_SIZE 32
    #define WORD_WIDTH 8
    using word_t = uint32_t;
#endif // ISA_64

#define FMT_STREAM_WORD(word)  "0x" << std::hex << std::setw(WORD_WIDTH) << std::setfill('0') << word

#endif // __COMMON_H__
