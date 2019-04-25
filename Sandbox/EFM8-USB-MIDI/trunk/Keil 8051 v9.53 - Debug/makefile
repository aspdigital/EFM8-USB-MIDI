################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Keil tools exit code 1 is warnings only, so don't treat as an error in make
RC := test $$? -lt 2

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include midi/subdir.mk
-include lib/efm8ub2/peripheralDrivers/src/subdir.mk
-include lib/efm8ub2/peripheralDrivers/inc/subdir.mk
-include lib/efm8ub2/bsp/efm8_memory_lcd/src/subdir.mk
-include lib/efm8_usb/src/subdir.mk
-include lib/efm8_assert/subdir.mk
-include lib/bsp/efm8_rgb_led/subdir.mk
-include lib/bsp/efm8_memory_lcd/src/subdir.mk
-include lib/bsp/efm8_joystick/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: EFM8-USB-MIDI.omf

# Tool invocations
EFM8-USB-MIDI.omf: echo_path $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Keil 8051 Linker'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/LX51" "@EFM8-USB-MIDI.lnp" || $(RC)
	@echo 'Finished building target: $@'

# Change from all upper case to the expected case
	@-mv "EFM8-USB-MIDI.OMF.CRBUILD" "$@"

# Generate hex file: EFM8-USB-MIDI.hex
	@wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/Ohx51" "EFM8-USB-MIDI.omf" "HEXFILE (EFM8-USB-MIDI.hex)" "H386" 2>&1 >/dev/null

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS) EFM8-USB-MIDI.omf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
# echo the path
echo_path:
	@echo PATH=$$PATH
	@echo ' '

