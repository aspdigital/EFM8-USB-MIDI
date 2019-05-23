/**
 * joybutton.c
 *
 * Roll up all functions and features necessary to read the joystick position
 * and the state of the two pushbuttons.
 *
 * Created from Silicon Labs example and extended and contracted.
 * The main program loop should periodically call JOYBUTTON_GetReport() to
 * obtain the latest button and joystick states.
 *
 * This code specifically targets the SiLabs EFM8UB2 Universal Bee Starter Kit
 * (SLSTK2001A).
 *
 * Today is 23 May 2019.
 *
 * (c) 2019 ASP Digital
 *
 */
#include "bsp_config.h"		//!< Board-specific definitions
#include "joystick.h"		//!< This is in the efm8 BSP library
#include "joybutton.h"		//!< Header for functions and defines for this source
#include <string.h>			//!< for memset

/**
 * Global set by the ADC ISR.
 */
volatile uint8_t joystickDirection = JOYSTICK_NONE;	//!< should be obvious, no?

/*!
 * Returns a report containing the state of the buttons and the joystick position.
 * This uses constants, etc defined in the efm8_joystick library, which we might
 * want to simplify.
 *
 * @param[out] jbr is structure which will contain the report.
 */
void JOYBUTTON_GetReport(joybuttonReport_t *jbr)
{
	uint8_t joyStatus = 0;

	memset(jbr, 0, sizeof(joybuttonReport_t));

	/*
	 * From most-recently-fetched joystick direction value, fill in the X and Y
	 * part of the report.
	 * Direction constants are as defined by the efm8_joystick library.
	 */
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

	/* Check button states to see if any were pressed. */
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

    /*
     * set the Button report value.
     */
	jbr->Button = joyStatus & BUTTON_MASK;

    /*
     * Determine X and Y report values from joystick direction.
     */
    if (joyStatus & JOY_UP) {
		jbr->Y = 0x7F;
	} else if (joyStatus & JOY_DOWN) {
		jbr->Y = 0x01;
	}

	if (joyStatus & JOY_LEFT) {
		jbr->X = 0x01;
	} else if (joyStatus & JOY_RIGHT) {
		jbr->X = 0x7F;
	}
} //JOYBUTTON_GetReport()

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


