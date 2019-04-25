################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
../src/SILABS_STARTUP.A51 

C_SRCS += \
../src/EFM8-USB-MIDI_main.c \
../src/InitDevice.c \
../src/adc.c \
../src/callback.c \
../src/descriptors.c \
../src/joybutton.c 

OBJS += \
./src/EFM8-USB-MIDI_main.OBJ \
./src/InitDevice.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/adc.OBJ \
./src/callback.OBJ \
./src/descriptors.OBJ \
./src/joybutton.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/C51" "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/EFM8-USB-MIDI_main.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/InitDevice.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_rgb_led/rgb_led.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/bsp.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/disp.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/render.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/tick.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/joybutton.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/midi/midi.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/midi/midi_uart.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/rgb_led_config.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2_slstk2001a/bsp/bsp_config.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/config/render_config.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/memory_lcd_config.h

src/InitDevice.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/InitDevice.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/descriptors.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDLIB.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h

src/%.OBJ: ../src/%.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	wine "/Applications/Simplicity Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/BIN/AX51" "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/adc.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/adc.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_joystick/joystick.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/bsp.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/joystick_config.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2_slstk2001a/bsp/bsp_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

src/callback.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/descriptors.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_rgb_led/rgb_led.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDLIB.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/rgb_led_config.h

src/descriptors.OBJ: /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDLIB.H /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8_usb/inc/efm8_usb.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/descriptors.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/usbconfig.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STDDEF.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2/peripheralDrivers/inc/usb_0.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h

src/joybutton.OBJ: /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/bsp.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/joybutton.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/bsp/efm8_joystick/joystick.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/toolchains/keil_8051/9.53/INC/STRING.H /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/lib/efm8ub2_slstk2001a/bsp/bsp_config.h /Users/andy/Projects/Workspaces/SiLabs_8051/EFM8-USB-MIDI/inc/config/joystick_config.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h /Applications/Simplicity\ Studio.app/Contents/Eclipse/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h


