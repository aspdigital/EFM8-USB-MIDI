/*!
 * joybutton.h
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
#ifndef __BUTTON_H__
#define __BUTTON_H__

/**
 * Structure which holds joystick and button-press information.
 */
typedef struct {
	uint8_t Button; /**< Button mask for currently pressed buttons */
	uint8_t X;		/**< Joystick X axis position */
	uint8_t Y;		/**< Joystick Y axis position */
} joybuttonReport_t;

/*!
 * Define the bit masks used by the report.
 */
#define LEFT_BUTTON         (1 << 0)
#define RIGHT_BUTTON        (1 << 1)
#define CENTER_BUTTON       (1 << 2)
#define JOY_UP		        (1 << 3)
#define JOY_DOWN	        (1 << 4)
#define JOY_LEFT	        (1 << 5)
#define JOY_RIGHT	        (1 << 6)

#define JOY_MASK            (JOY_UP | JOY_DOWN | JOY_LEFT | JOY_RIGHT)
#define BUTTON_MASK         (LEFT_BUTTON | RIGHT_BUTTON | CENTER_BUTTON)

/*!
 * Define the GPIO pins used for the buttons.
 */
#define LEFT_BUTTON_PIN    (BSP_PB1)
#define RIGHT_BUTTON_PIN   (BSP_PB0)

/*!
  * Returns a report containing the state of the buttons and the joystick position.
 *
 * @param[out] jbr is structure which will contain the report.
 */
void JOYBUTTON_GetReport(joybuttonReport_t *jbr);

#endif
