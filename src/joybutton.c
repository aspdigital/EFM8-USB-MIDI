/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
/////////////////////////////////////////////////////////////////////////////
// button.c
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "bsp.h"
//#include "retargetserial.h"
#include "joybutton.h"
#include "joystick.h"
#include <string.h>

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Joystick_GetStatus() Routine
// ----------------------------------------------------------------------------
//
// Description - Get joystick status.
//
// Return - Which direction on the joystick has been pushed as well as which
//          buttons have been pressed
//-----------------------------------------------------------------------------
uint8_t Joystick_GetStatus(void)
{
  uint8_t joyStatus = 0;
  uint8_t joystickDirection;
  uint16_t sample;
  uint32_t mv;

  // Manually initiate an ADC conversion
  ADC0CN0_ADBUSY = 1;
  // Wait for conversion to complete
  while (ADC0CN0_ADBUSY);

  sample = ADC0;
  mv = ((uint32_t)sample) * 3300 / 1024;

  joystickDirection = JOYSTICK_convert_mv_to_direction(mv);

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
}

/*
 * Structure which holds joystick and button-press information.
 * Yes, it's an HID report structure.
 */
struct joystickReportData
{
  uint8_t Button; /**< Button mask for currently pressed buttons in the game pad. */
  uint8_t X;
  uint8_t Y;
} joystickReportData;

static struct joystickReportData prevJoystickReportData;

//-----------------------------------------------------------------------------
// CreateJoystickReport() Routine
// ----------------------------------------------------------------------------
//
// Description - Generate joystick status report according Joystick and Button
//               status.
//
//-----------------------------------------------------------------------------
void CreateJoystickReport(void)
{
  uint8_t joyStatus = Joystick_GetStatus();

  memset(&joystickReportData, 0, sizeof(joystickReportData));

  if (joyStatus & JOY_UP)
  {
    joystickReportData.Y = 0xFF;
  }
  else if (joyStatus & JOY_DOWN)
  {
    joystickReportData.Y = 0x01;
  }

  if (joyStatus & JOY_LEFT)
  {
    joystickReportData.X = 0xFF;
  }
  else if (joyStatus & JOY_RIGHT)
  {
    joystickReportData.X = 0x01;
  }

  joystickReportData.Button = joyStatus & BUTTON_MASK;
}

