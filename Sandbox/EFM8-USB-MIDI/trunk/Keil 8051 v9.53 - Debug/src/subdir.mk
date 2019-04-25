################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
../src/SILABS_STARTUP.A51 

C_SRCS += \
../src/EFM8-USB-MIDI_main.c \
../src/InitDevice.c \
../src/callback.c \
../src/descriptors.c \
../src/joybutton.c 

OBJS += \
./src/EFM8-USB-MIDI_main.OBJ \
./src/InitDevice.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/callback.OBJ \
./src/descriptors.OBJ \
./src/joybutton.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/EFM8-USB-MIDI_main.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Lib/efm8_usb/inc/efm8_usb.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/common/drivers/efm8_rgb_led/rgb_led.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/common/bsp/bsp.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/disp.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/render.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/tick.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/joybutton.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/usbconfig.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDDEF.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/usb_0.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/rgb_led_config.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/EFM8UB2_SLSTK2001A/config/bsp_config.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/lib/bsp/efm8_memory_lcd/inc/config/render_config.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/memory_lcd_config.h

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Lib/efm8_usb/inc/efm8_usb.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/descriptors.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/usb_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/usbconfig.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDDEF.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDLIB.H C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h

src/%.OBJ: ../src/%.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/callback.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Lib/efm8_usb/inc/efm8_usb.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/descriptors.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/common/drivers/efm8_rgb_led/rgb_led.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/usbconfig.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDDEF.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/usb_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDLIB.H C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/rgb_led_config.h

src/descriptors.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/endian.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDLIB.H C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Lib/efm8_usb/inc/efm8_usb.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/descriptors.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_audio.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/usb_audio/inc/usb_midi.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/usbconfig.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDDEF.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/usb_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h

src/joybutton.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/common/bsp/bsp.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/joybutton.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/common/drivers/efm8_joystick/joystick.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/kits/EFM8UB2_SLSTK2001A/config/bsp_config.h C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/joystick_config.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h


