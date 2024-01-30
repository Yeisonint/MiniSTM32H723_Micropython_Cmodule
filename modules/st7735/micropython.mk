USERMODULES_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(USERMODULES_DIR)/st7735_module.c
SRC_USERMOD += $(USERMODULES_DIR)/lcd.c
SRC_USERMOD += $(USERMODULES_DIR)/logo_160_80.c
SRC_USERMOD += $(USERMODULES_DIR)/lib/st7735_reg.c
SRC_USERMOD += $(USERMODULES_DIR)/lib/st7735.c

CFLAGS_USERMOD += -I$(USERMODULES_DIR)