#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.
#
# ASIS configuration
ASIS_SCRIPT  = test_button
ASIS_LED     = -DLED_ENABLE      # Comment out to disable LED while running
ASIS_MAX_INSTRUCTION = 600       # Max instruction buffer size (including function)
ASIS_MAX_FUNCTION    = 200       # Max function section size
ASIS_MAX_STACK       = 8         # Max nested function call
ASIS_BUTTON_DURATION = 3         # Button duration for asis_click()
ASIS_WAIT_PERIOD     = 100       # Wait period in millisecond
                                 # Low value will allow more precise wait
																 # High value will save some power during long waits

# Set the MCU accordingly to your device (e.g. at90usb1286 for a Teensy 2.0++, or atmega16u2 for an Arduino UNO R3)
MCU          = at90usb1286
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = ./build/asis_build_$(ASIS_SCRIPT)
SRC          = ./src/Joystick.c \
							 ./src/Descriptors.c \
							 ./src/asis.c \
							 ./src/asis_util.c \
							 ./src/$(ASIS_SCRIPT).c \
							 $(LUFA_SRC_USB)
LUFA_PATH    = ./LUFA/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ $(ASIS_LED) \
							 -DASIS_MAX_INSTRUCTION=$(ASIS_MAX_INSTRUCTION) \
							 -DASIS_MAX_FUNCTION=$(ASIS_MAX_FUNCTION) \
							 -DASIS_MAX_STACK=$(ASIS_MAX_STACK) \
							 -DASIS_BUTTON_DURATION=$(ASIS_BUTTON_DURATION) \
							 -DASIS_WAIT_PERIOD=$(ASIS_WAIT_PERIOD)
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

clean:
	rm -f build/* obj/*



