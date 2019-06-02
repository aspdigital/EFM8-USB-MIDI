/******************************************************************************
 * Copyright (c) 2014 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// rgb_led.h
/////////////////////////////////////////////////////////////////////////////

#ifndef RGB_LED_H_
#define RGB_LED_H_

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "rgb_led_config.h"

/**************************************************************************//**
 * @addtogroup rgb_led RGB LED Driver
 * @{
 *
 * @brief Board support driver for tri-color RGB LED
 *
 * # Introduction #
 *
 * This module contains all the driver content for using 3 PCA channels
 * in PWM mode to output an RGB color code with configurable intensity.
 *
 *****************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// Default Configuration Options
/////////////////////////////////////////////////////////////////////////////

/***************************************************************************//**
 * @addtogroup rgb_led_config Driver Configuration
 * @{
 *
 * @brief Driver configuration constants read from **rgb_led_config.h**
 *
 * This board support library will look for configuration constants in
 * **rgb_led_config.h**. This file is provided/written by the user and should be
 * located in a directory that is part of the include path.
 *
 ******************************************************************************/

/// @name Configuration Options
/// @{

#if !defined(RGB_CEX_GREEN) || defined(IS_DOXYGEN)
/***************************************************************************//**
 * @brief Sets the PCA CEX SFR for the green LED.
 *
 * Default setting is @c PCA0CPH0 and may be overridden by defining in
 * **rgb_led_config.h**.
 *
 ******************************************************************************/
#define RGB_CEX_GREEN               PCA0CPH0
#endif

#if !defined(RGB_CEX_BLUE) || defined(IS_DOXYGEN)
/***************************************************************************//**
 * @brief Sets the PCA CEX SFR for the blue LED.
 *
 * Default setting is @c PCA0CPH1 and may be overridden by defining in
 * **rgb_led_config.h**.
 *
 ******************************************************************************/
#define RGB_CEX_BLUE                PCA0CPH1
#endif

#if !defined(RGB_CEX_RED) || defined(IS_DOXYGEN)
/***************************************************************************//**
 * @brief Sets the PCA CEX SFR for the red LED.
 *
 * Default setting is @c PCA0CPH2 and may be overridden by defining in
 * **rgb_led_config.h**.
 *
 ******************************************************************************/
#define RGB_CEX_RED                 PCA0CPH2
#endif

/// @}

/** @} rgb_led_config */

/**************************************************************************//**
 * @addtogroup rgb_led_runtime Runtime API
 * @{
 *****************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// Structs
/////////////////////////////////////////////////////////////////////////////

/// A color structure used to store RGB color component values
typedef struct Color
{
    uint8_t red;    ///< The red LED component (0 = off, 255 = max)
    uint8_t green;  ///< The green LED component (0 = off, 255 = max)
    uint8_t blue;   ///< The blue LED component (0 = off, 255 = max)
} Color;

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

/***************************************************************************//**
 * @brief Set the tri-color LED output to the specified color and intensity
 *
 * @param color A ::Color structure specifying the desired color output
 * @param intensity A value from [0, 255] specifying the intensity of the LED
 * output (0 = off, 255 = max intensity)
 *
 *****************************************************************************/
void RGB_SetColor(Color color, uint8_t intensity);

/** @} rgb_led_runtime */

/** @} rgb_led */

#endif /* RGB_LED_H_ */
