################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/efm8ub2/peripheralDrivers/src/adc_0.c \
../lib/efm8ub2/peripheralDrivers/src/spi_0.c \
../lib/efm8ub2/peripheralDrivers/src/usb_0.c 

OBJS += \
./lib/efm8ub2/peripheralDrivers/src/adc_0.OBJ \
./lib/efm8ub2/peripheralDrivers/src/spi_0.OBJ \
./lib/efm8ub2/peripheralDrivers/src/usb_0.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8ub2/peripheralDrivers/src/%.OBJ: ../lib/efm8ub2/peripheralDrivers/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8ub2/peripheralDrivers/src/adc_0.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/adc_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/ASSERT.H C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/efm8_config.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDIO.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

lib/efm8ub2/peripheralDrivers/src/spi_0.OBJ: C:/Users/apeters.SPECSERV/Projects/EFM8-USB-MIDI/inc/config/efm8_config.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/spi_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h

lib/efm8ub2/peripheralDrivers/src/usb_0.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/peripheral_driver/inc/usb_0.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdbool.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/EFM8UB2/inc/SI_EFM8UB2_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.1.6/Device/shared/si8051Base/si_toolchain.h


