################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/efm8ub2/peripheralDrivers/src/adc_0.c \
../lib/efm8ub2/peripheralDrivers/src/spi_0.c \
../lib/efm8ub2/peripheralDrivers/src/uart_1.c \
../lib/efm8ub2/peripheralDrivers/src/usb_0.c 

OBJS += \
./lib/efm8ub2/peripheralDrivers/src/adc_0.OBJ \
./lib/efm8ub2/peripheralDrivers/src/spi_0.OBJ \
./lib/efm8ub2/peripheralDrivers/src/uart_1.OBJ \
./lib/efm8ub2/peripheralDrivers/src/usb_0.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8ub2/peripheralDrivers/src/%.OBJ: ../lib/efm8ub2/peripheralDrivers/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8ub2/peripheralDrivers/src/adc_0.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/adc_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/ASSERT.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/efm8_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDIO.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

lib/efm8ub2/peripheralDrivers/src/spi_0.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/efm8_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/spi_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

lib/efm8ub2/peripheralDrivers/src/uart_1.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/uart_1.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/efm8_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

lib/efm8ub2/peripheralDrivers/src/usb_0.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h


