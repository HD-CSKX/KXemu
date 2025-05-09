.DEFAULT_GOAL := all
KXEMU_HOME := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
SCRIPT_DIR := $(KXEMU_HOME)/scripts
SRC_DIR := $(KXEMU_HOME)/src
INCLUDE_DIR := $(KXEMU_HOME)/include
BUILD_DIR := $(KXEMU_HOME)/build
EXPORT_DIR := $(KXEMU_HOME)/export
include $(SCRIPT_DIR)/config.mk

all: kxemu

count:
	$(info Counting lines in src and include directories...)
	@ find -L $(SCRIPT_DIR) $(SRC_DIR) $(INCLUDE_DIR) -type f \( -name '*.c' -or -name "*.cpp" -or -name "*.h" -or -name "*.py" -or -name "*.instpat" -or -name "*.cmake" \) -exec cat {} + | sed '/^[[:space:]]*$$/d' | wc -l

kxemu:
	@ cmake -G Ninja -S $(KXEMU_HOME) -B $(BUILD_DIR)
	@ cmake --build $(BUILD_DIR)

run: kxemu
	@ cmake --build $(BUILD_DIR) --target run

export-include:
	@ mkdir -p $(EXPORT_DIR)
	$(info + Exporting Headers $(CONFIG_ISA))
	@ python3 $(SCRIPT_DIR)/export/export.py

clean:
	$(info + CLEAN $(BUILD_DIR))
	-@ cmake --build $(BUILD_DIR) --target clean

clean-all:
	$(info + CLEAN-ALL)
	-@ cmake --build $(BUILD_DIR) --target clean-all
	-@ rm -rf $(BUILD_DIR)
	-@$(MAKE) distclean


.PHONY: all count kxemu run export-include clean clean-all
