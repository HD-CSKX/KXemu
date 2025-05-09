file(
    GLOB_RECURSE EMU_SRCS CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/cpu/${CONFIG_BASE_ISA}/**.cpp
    ${PROJECT_SOURCE_DIR}/src/device/**.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/**.cpp
)
list(APPEND EMU_SRCS ${PROJECT_SOURCE_DIR}/src/log.cpp)

file(
    GLOB_RECURSE KDB_SRCS CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/kdb/**.cpp
    ${PROJECT_SOURCE_DIR}/src/isa/${CONFIG_BASE_ISA}/**.cpp
)
list(APPEND KDB_SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)
