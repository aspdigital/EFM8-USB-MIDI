################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/efm8_usb/src/efm8_usbd.c \
../lib/efm8_usb/src/efm8_usbdch9.c \
../lib/efm8_usb/src/efm8_usbdep.c \
../lib/efm8_usb/src/efm8_usbdint.c 

OBJS += \
./lib/efm8_usb/src/efm8_usbd.OBJ \
./lib/efm8_usb/src/efm8_usbdch9.OBJ \
./lib/efm8_usb/src/efm8_usbdep.OBJ \
./lib/efm8_usb/src/efm8_usbdint.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8_usb/src/%.OBJ: ../lib/efm8_usb/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8_usb/src/efm8_usbd.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/ASSERT.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDIO.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h

lib/efm8_usb/src/efm8_usbdch9.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h

lib/efm8_usb/src/efm8_usbdep.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h

lib/efm8_usb/src/efm8_usbdint.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h


