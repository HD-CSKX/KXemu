SRC_DIR = ./src

EMU_SRCS += $(shell find $(SRC_DIR)/device -name "*.cpp")
EMU_SRCS += $(shell find $(SRC_DIR)/utils  -name "*.cpp")
EMU_SRCS += $(shell find $(SRC_DIR)/cpu/$(CONFIG_BASE_ISA) -name "*.cpp" -or -name "*.c" )
EMU_SRCS += $(shell find $(SRC_DIR)/isa/$(BASE_ISA) -name "*.cpp" -or -name "*.c" )
EMU_SRCS += $(SRC_DIR)/log.cpp

KDB_SRCS += $(shell find $(SRC_DIR)/kdb -name "*.cpp")
KDB_SRCS += $(SRC_DIR)/main.cpp
