cmake_minimum_required(VERSION 3.15...4.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/config.cmake)

project(kxemu-system VERSION 1.0 LANGUAGES C CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/utils)

if(CONFIG_BASE_ISA STREQUAL "riscv")
    set(SOFTFLOAT_SPECIALIZE_TYPE "RISCV")
else()
    set(SOFTFLOAT_SPECIALIZE_TYPE "8086-SSE")
endif()

set(SOFTFLOAT_TARGET_SHARED ${CONFIG_TARGET_SHARE})

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "The binary direction of CMake cannot be the same as the source direction!")
endif()

include(${PROJECT_SOURCE_DIR}/scripts/filelist.cmake)

find_package(Readline MODULE REQUIRED)
message(STATUS "Found Readline")
find_package(LLVM CONFIG REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(KXEMU_TARGET kxemu-system-${CONFIG_BASE_ISA})

if(NOT CONFIG_TARGET_SHARE)
    add_executable(${KXEMU_TARGET} ${EMU_SRCS} ${KDB_SRCS})
    target_include_directories(${KXEMU_TARGET}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${Readline_INCLUDE_DIRS}
    )
    target_link_libraries(${KXEMU_TARGET}
        PRIVATE
        gdbstub
        LLVM
        ${Readline_LIBRARY}
    )
else()
    add_library(${KXEMU_TARGET} SHARED ${EMU_SRCS})
    target_include_directories(${KXEMU_TARGET}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
    )
endif()

include(${PROJECT_SOURCE_DIR}/scripts/isa/${CONFIG_BASE_ISA}.cmake)

add_custom_target(clean-all
    COMMENT "CLEAN ALL"
    DEPENDS clean clean-gdbstub clean-softfloat
)

add_custom_target(run
    COMMENT "RUN KXemu"
    COMMAND $<TARGET_FILE:${KXEMU_TARGET}>
    DEPENDS ${KXEMU_TARGET}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    VERBATIM
    USES_TERMINAL
)
