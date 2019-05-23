/**
 * joybutton.c
 *
 * Roll up all functions and features necessary to read the joystick position
 * and the state of the two pushbuttons.
 *
 * Created from Silicon Labs example and extended.
 *
 * This code specifically targets the SiLabs EFM8UB2 Universal Bee Starter Kit
 * (SLSTK2001A).
 *
 * Today is 22 May 2019.
 *
 * (c) 2019 ASP Digital
 *
 */
#include "bsp.h"
#include "joystick.h"		//!< This is in the efm8 BSP library
#include "joybutton.h"
#include <string.h>

/**
 * Global set by the ADC ISR.
 */
uint8_t joystickDirection = JOYSTICK_NONE;	//!< should be obvious, no?

//!-----------------------------------------------------------------------------
//! Joystick_GetStatus() Routine
//! ----------------------------------------------------------------------------
//!
//! Description - Get joystick status.
//!
//! Return - Which direction on the joystick has been pushed as well as which
//!          buttons have been pressed
//!-----------------------------------------------------------------------------

uint8_t Joystick_GetStatus(void)
{
  uint8_t joyStatus = 0;

  // joystickDirection is declared in adc.h
	switch (joystickDirection)
	{
	case JOYSTICK_N:    joyStatus |= JOY_UP;                break;
	case JOYSTICK_NE:   joyStatus |= JOY_UP | JOY_RIGHT;    break;
	case JOYSTICK_E:    joyStatus |= JOY_RIGHT;             break;
	case JOYSTICK_SE:   joyStatus |= JOY_DOWN | JOY_RIGHT;  break;
	case JOYSTICK_S:    joyStatus |= JOY_DOWN;              break;
	case JOYSTICK_SW:   joyStatus |= JOY_DOWN | JOY_LEFT;   break;
	case JOYSTICK_W:    joyStatus |= JOY_LEFT;              break;
	case JOYSTICK_NW:   joyStatus |= JOY_UP | JOY_LEFT;     break;
	}

    if (!LEFT_BUTTON_PIN)
    {
        joyStatus |= LEFT_BUTTON;
    }
    if (!RIGHT_BUTTON_PIN)
    {
        joyStatus |= RIGHT_BUTTON;
    }
    if (joystickDirection == JOYSTICK_C)
    {
        joyStatus |= CENTER_BUTTON;
    }

	return joyStatus;
} // Joystick_GetStatus()

/**
 * ADC ISR.
 * The ADC conversion is started by Timer 5 overflow.
 * When conversion is complete, this ISR is called.
 *
 * The ADC is read and we convert ADU to mV.
 * We obtain the joystick direction from those mV.
 *
 * joystickDirection is a global defined above.
 *
 * It might be better to simply make mV the global and do the conversion to
 * joystick direction out of the ISR.
 */
SI_INTERRUPT (ADC0EOC_ISR, ADC0EOC_IRQn)
{
  uint32_t mV;

  ADC0CN0_ADINT = 0; // Clear ADC0 conv. complete flag

  mV = (ADC0 * (uint32_t) 3300) / 1023;

  joystickDirection = JOYSTICK_convert_mv_to_direction(mV);
} // ADC0EOC_ISR


