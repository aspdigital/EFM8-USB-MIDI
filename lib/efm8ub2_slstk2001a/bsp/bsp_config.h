/////////////////////////////////////////////////////////////////////////////
// bsp_config.h
/////////////////////////////////////////////////////////////////////////////

#ifndef BSP_CONFIG_H_
#define BSP_CONFIG_H_

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include <SI_EFM8UB2_Register_Enums.h>

/////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////

#define BSP_PB_PRESSED          0
#define BSP_PB_UNPRESSED        1

#define BSP_LED_ON              0
#define BSP_LED_OFF             1

// BSP_DISP_EN settings
#define BSP_DISP_BC_DRIVEN      0      // Board Controller drives display
#define BSP_DISP_EFM8_DRIVEN    1      // EFM8 drives display

// BSP_BC_EN settings
#define BSP_BC_DISCONNECTED     0      // Board Controller disconnected
                                       //   from EFM8 UART pins
#define BSP_BC_CONNECTED        1      // Board Controller connected
                                       //   to EFM8 UART pins

/////////////////////////////////////////////////////////////////////////////
// Port sbits
/////////////////////////////////////////////////////////////////////////////

SI_SBIT(BSP_DISP_EN, SFR_P1, 4);
SI_SBIT(BSP_DISP_CS, SFR_P0, 1);

SI_SBIT(BSP_PB0, SFR_P0, 2);
SI_SBIT(BSP_PB1, SFR_P0, 3);

SI_SBIT(BSP_JOYSTICK, SFR_P2, 5);

SI_SBIT(BSP_LED_G, SFR_P1, 6);
SI_SBIT(BSP_LED_B, SFR_P1, 7);
SI_SBIT(BSP_LED_R, SFR_P2, 0);

SI_SBIT(BSP_BC_EN, SFR_P0, 0);

/*
 * Defines specific to USB MIDI project.
 */

// The virtual MIDI port is Cable Number (Port Number) 1
#define VIRTUAL_CN 0x00
// Our hardware (UART) MIDI port is Cable Number (Port Number) 2.
#define UART_CN 0x01

#endif /* BSP_CONFIG_H_ */
