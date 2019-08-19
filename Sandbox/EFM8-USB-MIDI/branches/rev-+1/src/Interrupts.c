//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8UB2_Register_Enums.h>

//-----------------------------------------------------------------------------
// USB0_ISR
//-----------------------------------------------------------------------------
//
// USB0 ISR Content goes here. Remember to clear flag bits:
// CMINT::RSTINT (Reset Interrupt Flag)
// CMINT::RSUINT (Resume Interrupt Flag)
// CMINT::SOF (Start of Frame Interrupt Flag)
// CMINT::SUSINT (Suspend Interrupt Flag)
// IN1INT::EP0 (Endpoint 0 Interrupt Flag)
// IN1INT::IN1 (IN Endpoint 1 Interrupt Flag)
// IN1INT::IN2 (IN Endpoint 2 Interrupt Flag)
// IN1INT::IN3 (IN Endpoint 3 Interrupt Flag)
// OUT1INT::OUT1 (OUT Endpoint 1 Interrupt Flag)
// OUT1INT::OUT2 (OUT Endpoint 2 Interrupt Flag)
// OUT1INT::OUT3 (OUT Endpoint 3 Interrupt Flag)
//
//-----------------------------------------------------------------------------
//SI_INTERRUPT (USB0_ISR, USB0_IRQn)
//{

//}

//-----------------------------------------------------------------------------
// TIMER2_ISR
//-----------------------------------------------------------------------------
//
// TIMER2 ISR Content goes here. Remember to clear flag bits:
// TMR2CN0::TF2H (Timer # High Byte Overflow Flag)
// TMR2CN0::TF2L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
#if 0
SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
{

}
#endif

//-----------------------------------------------------------------------------
// SPI0_ISR
//-----------------------------------------------------------------------------
//
// SPI0 ISR Content goes here. Remember to clear flag bits:
// SPI0CN0::MODF (Mode Fault Flag)
// SPI0CN0::RXOVRN (Receive Overrun Flag)
// SPI0CN0::SPIF (SPI# Interrupt Flag)
// SPI0CN0::WCOL (Write Collision Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (SPI0_ISR, SPI0_IRQn)
{

}

//-----------------------------------------------------------------------------
// ADC0EOC_ISR
//-----------------------------------------------------------------------------
//
// ADC0EOC ISR Content goes here. Remember to clear flag bits:
// ADC0CN0::ADINT (Conversion Complete Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (ADC0EOC_ISR, ADC0EOC_IRQn)
{

}

//-----------------------------------------------------------------------------
// TIMER3_ISR
//-----------------------------------------------------------------------------
//
// TIMER3 ISR Content goes here. Remember to clear flag bits:
// TMR3CN0::TF3H (Timer # High Byte Overflow Flag)
// TMR3CN0::TF3L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER3_ISR, TIMER3_IRQn)
{

}

//-----------------------------------------------------------------------------
// USB0_ISR
//-----------------------------------------------------------------------------
//
// USB0 ISR Content goes here. Remember to clear flag bits:
// CMINT::RSTINT (Reset Interrupt Flag)
// CMINT::RSUINT (Resume Interrupt Flag)
// CMINT::SOF (Start of Frame Interrupt Flag)
// CMINT::SUSINT (Suspend Interrupt Flag)
// IN1INT::EP0 (Endpoint 0 Interrupt Flag)
// IN1INT::IN1 (IN Endpoint 1 Interrupt Flag)
// IN1INT::IN2 (IN Endpoint 2 Interrupt Flag)
// IN1INT::IN3 (IN Endpoint 3 Interrupt Flag)
// OUT1INT::OUT1 (OUT Endpoint 1 Interrupt Flag)
// OUT1INT::OUT2 (OUT Endpoint 2 Interrupt Flag)
// OUT1INT::OUT3 (OUT Endpoint 3 Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (USB0_ISR, USB0_IRQn)
{

}


//-----------------------------------------------------------------------------
// TIMER2_ISR
//-----------------------------------------------------------------------------
//
// TIMER2 ISR Content goes here. Remember to clear flag bits:
// TMR2CN0::TF2H (Timer # High Byte Overflow Flag)
// TMR2CN0::TF2L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
{

}


//-----------------------------------------------------------------------------
// UART1_ISR
//-----------------------------------------------------------------------------
//
// UART1 ISR Content goes here. Remember to clear flag bits:

//
//-----------------------------------------------------------------------------
SI_INTERRUPT (UART1_ISR, UART1_IRQn)
{

}

