CONFIG_DIR := $(KXEMU_HOME)/configs
CONFIG_FILE := $(CONFIG_DIR)/include/config/auto.conf
CONF := $(KXEMU_HOME)/tools/kconfig/build/conf
MCONF := $(KXEMU_HOME)/tools/kconfig/build/mconf
rm-distclean := $(CONFIG_DIR)/.config $(CONFIG_DIR)/.config.old $(CONFIG_DIR)/include

ifeq ($(wildcard $(CONFIG_DIR)/.config),)
$(warning Warning: $(CONFIG_DIR)/.config does not exist!)
$(warning To build the project, first run 'make menuconfig'.)
endif

-include $(CONFIG_FILE)

$(CONF):
	@ make -C $(KXEMU_HOME)/tools/kconfig NAME=conf

$(MCONF):
	@ make -C $(KXEMU_HOME)/tools/kconfig NAME=mconf

menuconfig: $(CONF) $(MCONF)
	@ cd $(CONFIG_DIR) && $(MCONF) -s Kconfig
	@ cd $(CONFIG_DIR) && $(CONF) -s --syncconfig Kconfig
	@ cp $(CONFIG_DIR)/include/generated/autoconf.h ./include/config

distclean:
	-@ rm -rf $(rm-distclean)

.PHONY: distclean
