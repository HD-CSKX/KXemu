cmake_minimum_required(VERSION 3.15...4.0)

# mini-gdbstub
project(mini-gdbstub VERSION 1.0 LANGUAGES C)

set(GDBSTUB_HOME ${PROJECT_SOURCE_DIR}/mini-gdbstub)
set(GDBSTUB_INCLUDE ${GDBSTUB_HOME}/include)
set(GDBSTUB_LIB ${GDBSTUB_HOME}/build/libgdbstub.a)
add_custom_command(
  OUTPUT ${GDBSTUB_LIB}
  COMMAND make -C ${GDBSTUB_HOME} -j ${CMAKE_BUILD_PARALLEL_LEVEL}
  COMMENT "BUILD UTIL: mini-gdbstub"
  VERBATIM
)

add_custom_target(clean-gdbstub
  COMMAND make -C ${GDBSTUB_HOME} clean
  COMMENT "Cleaning mini-gdbstub build"
)

add_library(gdbstub STATIC IMPORTED GLOBAL)
add_custom_target(build_gdbstub DEPENDS ${GDBSTUB_LIB})
add_dependencies(gdbstub build_gdbstub)
set_target_properties(gdbstub PROPERTIES
  IMPORTED_LOCATION "${GDBSTUB_LIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${GDBSTUB_INCLUDE}"
)

# SoftFloat
project(softfloat VERSION 1.0 LANGUAGES CXX)
set(SOFTFLOAT_SPECIALIZE_TYPE "RISCV" CACHE STRING "SoftFloat specialization type(RISCV for RISC-V, 8086-SSE for others)")
option(SOFTFLOAT_TARGET_SHARED "Softfloat for shared target" OFF)

set(SOFTFLOAT_HOME ${PROJECT_SOURCE_DIR}/softfloat)
set(SOFTFLOAT_INCLUDE ${SOFTFLOAT_HOME}/source/include ${SOFTFLOAT_HOME}/source/${SOFTFLOAT_SPECIALIZE_TYPE})
set(SOFTFLOAT_BUILD ${SOFTFLOAT_HOME}/build/Linux-x86_64-GCC)
set(SOFTFLOAT_LIB ${SOFTFLOAT_BUILD}/softfloat.a)
set(SOFTFLOAT_FLAGS "SPECIALIZE_TYPE=${SOFTFLOAT_SPECIALIZE_TYPE}")

if(SOFTFLOAT_TARGET_SHARED)
  set(SOFTFLOAT_FLAGS
    ${SOFTFLOAT_FLAGS} "SOFTFLOAT_OPTS=-DINLINE_LEVEL=5 -DSOFTFLOAT_FAST_DIV32TO16 -DSOFTFLOAT_FAST_DIV64TO32 -fPIC"
  )
endif()

add_custom_command(
  OUTPUT ${SOFTFLOAT_LIB}
  COMMAND make ${SOFTFLOAT_FLAGS} -C ${SOFTFLOAT_BUILD} -j ${CMAKE_BUILD_PARALLEL_LEVEL}
  COMMENT "BUILD UTIL: softfloat"
  VERBATIM
)

add_custom_target(clean-softfloat
  COMMAND make -C ${SOFTFLOAT_BUILD} clean
  COMMENT "Cleaning SoftFloat build"
)

add_library(softfloat STATIC IMPORTED GLOBAL)
add_custom_target(build_softfloat DEPENDS ${SOFTFLOAT_LIB})
add_dependencies(softfloat build_softfloat)
set_target_properties(softfloat PROPERTIES
  IMPORTED_LOCATION "${SOFTFLOAT_LIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${SOFTFLOAT_INCLUDE}"
)
