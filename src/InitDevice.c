//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8UB2_Register_Enums.h>
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library Includes]
#include "efm8_usb.h"
#include "descriptors.h"
#include "usb_0.h"
// [Library Includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	// Save the SFRPAGE
	uint8_t SFRPAGE_save = SFRPAGE;
	PCA_0_enter_DefaultMode_from_RESET();
	PCACH_0_enter_DefaultMode_from_RESET();
	PCACH_1_enter_DefaultMode_from_RESET();
	PCACH_2_enter_DefaultMode_from_RESET();
	PCACH_4_enter_DefaultMode_from_RESET();
	PORTS_0_enter_DefaultMode_from_RESET();
	PORTS_1_enter_DefaultMode_from_RESET();
	PORTS_2_enter_DefaultMode_from_RESET();
	PBCFG_0_enter_DefaultMode_from_RESET();
	ADC_0_enter_DefaultMode_from_RESET();
	VREF_0_enter_DefaultMode_from_RESET();
	HFOSC_0_enter_DefaultMode_from_RESET();
	CLOCK_0_enter_DefaultMode_from_RESET();
	TIMER01_0_enter_DefaultMode_from_RESET();
	TIMER16_3_enter_DefaultMode_from_RESET();
	TIMER_SETUP_0_enter_DefaultMode_from_RESET();
	SPI_0_enter_DefaultMode_from_RESET();
	UART_0_enter_DefaultMode_from_RESET();
	UARTE_1_enter_DefaultMode_from_RESET();
	INTERRUPT_0_enter_DefaultMode_from_RESET();
	USBLIB_0_enter_DefaultMode_from_RESET();
	// Restore the SFRPAGE
	SFRPAGE = SFRPAGE_save;
	// [Config Calls]$

}

extern void PCA_0_enter_DefaultMode_from_RESET(void) {
	// $[PCA0MD - PCA Mode]
	/***********************************************************************
	 - Disable Watchdog Timer
	 - System clock divided by 12
	 - PCA continues to function normally while the system controller is in
	 Idle Mode
	 - Disable the CF interrupt
	 - Disable Watchdog Timer
	 - Watchdog Timer Enable unlocked
	 ***********************************************************************/
	SFRPAGE = 0x00;
	PCA0MD &= ~PCA0MD_WDTE__BMASK;
	PCA0MD = PCA0MD_CPS__SYSCLK_DIV_12 | PCA0MD_CIDL__NORMAL
			| PCA0MD_ECF__OVF_INT_DISABLED | PCA0MD_WDTE__DISABLED
			| PCA0MD_WDLCK__UNLOCKED;
	// [PCA0MD - PCA Mode]$

	// $[PCA0H - PCA Counter/Timer High Byte]
	// [PCA0H - PCA Counter/Timer High Byte]$

	// $[PCA0L - PCA Counter/Timer Low Byte]
	// [PCA0L - PCA Counter/Timer Low Byte]$

	// $[PCA0CN0 - PCA Control 0]
	/***********************************************************************
	 - Start the PCA Counter/Timer running
	 ***********************************************************************/
	PCA0CN0 |= PCA0CN0_CR__RUN;
	// [PCA0CN0 - PCA Control 0]$

}

extern void PCACH_4_enter_DefaultMode_from_RESET(void) {
	// $[PCA0CPM4 - PCA Channel 4 Capture/Compare Mode]
	/***********************************************************************
	 - Disable negative edge capture
	 - Disable CCF4 interrupts
	 - Enable match function
	 - 8-bit PWM selected
	 - Disable positive edge capture
	 - Disable comparator function
	 - Disable PWM function
	 - Disable toggle function
	 ***********************************************************************/
	PCA0CPM4 = PCA0CPM4_CAPN__DISABLED | PCA0CPM4_ECCF__DISABLED
			| PCA0CPM4_MAT__ENABLED | PCA0CPM4_PWM16__8_BIT
			| PCA0CPM4_CAPP__DISABLED | PCA0CPM4_ECOM__DISABLED
			| PCA0CPM4_PWM__DISABLED | PCA0CPM4_TOG__DISABLED;
	// [PCA0CPM4 - PCA Channel 4 Capture/Compare Mode]$

	// $[PCA0CPL4 - PCA Channel 4 Capture Module Low Byte]
	// [PCA0CPL4 - PCA Channel 4 Capture Module Low Byte]$

	// $[PCA0CPH4 - PCA Channel 4 Capture Module High Byte]
	PCA0CPH4 = 0x00;
	// [PCA0CPH4 - PCA Channel 4 Capture Module High Byte]$

	// $[PCA0 Start/Run restore]
	// [PCA0 Start/Run restore]$

}

extern void HFOSC_0_enter_DefaultMode_from_RESET(void) {
	// $[HFO0CN - High Frequency Oscillator Control]
	/***********************************************************************
	 - SYSCLK can be derived from Internal H-F Oscillator divided by 1 
	 ***********************************************************************/
	HFO0CN |= HFO0CN_IFCN__SYSCLK_DIV_1;
	// [HFO0CN - High Frequency Oscillator Control]$

}

extern void CLOCK_0_enter_DefaultMode_from_RESET(void) {
	// $[CLKSEL - Clock Select]
	/***********************************************************************
	 - Clock 
	 - USB clock 
	 - Enabling the Crossbar SYSCLK signal outputs SYSCLK
	 ***********************************************************************/
	CLKSEL = CLKSEL_CLKSL__HFOSC | CLKSEL_USBCLK__HFOSC | CLKSEL_OUTCLK__SYSCLK;
	// [CLKSEL - Clock Select]$

}

extern void TIMER01_0_enter_DefaultMode_from_RESET(void) {
	// $[Timer Initialization]
	//Save Timer Configuration
	uint8_t TCON_save;
	TCON_save = TCON;
	//Stop Timers
	TCON &= ~TCON_TR0__BMASK & ~TCON_TR1__BMASK;

	// [Timer Initialization]$

	// $[TH0 - Timer 0 High Byte]
	/***********************************************************************
	 - Timer 0 High Byte = 0xA0
	 ***********************************************************************/
	TH0 = (0xA0 << TH0_TH0__SHIFT);
	// [TH0 - Timer 0 High Byte]$

	// $[TL0 - Timer 0 Low Byte]
	/***********************************************************************
	 - Timer 0 Low Byte = 0xD0
	 ***********************************************************************/
	TL0 = (0xD0 << TL0_TL0__SHIFT);
	// [TL0 - Timer 0 Low Byte]$

	// $[TH1 - Timer 1 High Byte]
	// [TH1 - Timer 1 High Byte]$

	// $[TL1 - Timer 1 Low Byte]
	// [TL1 - Timer 1 Low Byte]$

	// $[Timer Restoration]
	//Restore Timer Configuration
	TCON |= (TCON_save & TCON_TR0__BMASK) | (TCON_save & TCON_TR1__BMASK);

	// [Timer Restoration]$

}

extern void TIMER_SETUP_0_enter_DefaultMode_from_RESET(void) {
	// $[CKCON0 - Clock Control 0]
	/***********************************************************************
	 - System clock divided by 12
	 - Counter/Timer 0 uses the system clock
	 - Timer 2 high byte uses the clock defined by T2XCLK in TMR2CN0
	 - Timer 2 low byte uses the clock defined by T2XCLK in TMR2CN0
	 - Timer 3 high byte uses the clock defined by T3XCLK in TMR3CN0
	 - Timer 3 low byte uses the clock defined by T3XCLK in TMR3CN0
	 - Timer 1 uses the clock defined by the prescale field, SCA
	 ***********************************************************************/
	CKCON0 = CKCON0_SCA__SYSCLK_DIV_12 | CKCON0_T0M__SYSCLK
			| CKCON0_T2MH__EXTERNAL_CLOCK | CKCON0_T2ML__EXTERNAL_CLOCK
			| CKCON0_T3MH__EXTERNAL_CLOCK | CKCON0_T3ML__EXTERNAL_CLOCK
			| CKCON0_T1M__PRESCALE;
	// [CKCON0 - Clock Control 0]$

	// $[CKCON1 - Clock Control 1]
	// [CKCON1 - Clock Control 1]$

	// $[TMOD - Timer 0/1 Mode]
	/***********************************************************************
	 - Mode 2, 8-bit Counter/Timer with Auto-Reload
	 - Mode 0, 13-bit Counter/Timer
	 - Timer Mode
	 - Timer 0 enabled when TR0 = 1 irrespective of INT0 logic level
	 - Timer Mode
	 - Timer 1 enabled when TR1 = 1 irrespective of INT1 logic level
	 ***********************************************************************/
	TMOD = TMOD_T0M__MODE2 | TMOD_T1M__MODE0 | TMOD_CT0__TIMER
			| TMOD_GATE0__DISABLED | TMOD_CT1__TIMER | TMOD_GATE1__DISABLED;
	// [TMOD - Timer 0/1 Mode]$

	// $[TCON - Timer 0/1 Control]
	/***********************************************************************
	 - Start Timer 0 running
	 ***********************************************************************/
	TCON |= TCON_TR0__RUN;
	// [TCON - Timer 0/1 Control]$

}

extern void UARTE_1_enter_DefaultMode_from_RESET(void) {
	// $[SBCON1 - UART1 Baud Rate Generator Control]
	/***********************************************************************
	 - Enable the baud rate generator
	 - Prescaler = 12
	 ***********************************************************************/
	SBCON1 = SBCON1_BREN__ENABLED | SBCON1_BPS__DIV_BY_12;
	// [SBCON1 - UART1 Baud Rate Generator Control]$

	// $[SMOD1 - UART1 Mode]
	// [SMOD1 - UART1 Mode]$

	// $[SBRLH1 - UART1 Baud Rate Generator High Byte]
	/***********************************************************************
	 - UART1 Baud Rate Reload High = 0xFF
	 ***********************************************************************/
	SBRLH1 = (0xFF << SBRLH1_BRH__SHIFT);
	// [SBRLH1 - UART1 Baud Rate Generator High Byte]$

	// $[SBRLL1 - UART1 Baud Rate Generator Low Byte]
	/***********************************************************************
	 - UART1 Baud Rate Reload Low = 0xEF
	 ***********************************************************************/
	SBRLL1 = (0xEF << SBRLL1_BRL__SHIFT);
	// [SBRLL1 - UART1 Baud Rate Generator Low Byte]$

	// $[SCON1 - UART1 Serial Port Control]
	/***********************************************************************
	 - UART1 reception enabled
	 ***********************************************************************/
	SCON1 |= SCON1_REN__RECEIVE_ENABLED;
	// [SCON1 - UART1 Serial Port Control]$

}

extern void INTERRUPT_0_enter_DefaultMode_from_RESET(void) {
	// $[EIE1 - Extended Interrupt Enable 1]
	/***********************************************************************
	 - Disable ADC0 Conversion Complete interrupt
	 - Disable ADC0 Window Comparison interrupt
	 - Disable CP0 interrupts
	 - Disable CP1 interrupts
	 - Disable all PCA0 interrupts
	 - Disable all SMB0 interrupts
	 - Disable Timer 3 interrupts
	 - Enable interrupt requests generated by USB0
	 ***********************************************************************/
	EIE1 = EIE1_EADC0__DISABLED | EIE1_EWADC0__DISABLED | EIE1_ECP0__DISABLED
			| EIE1_ECP1__DISABLED | EIE1_EPCA0__DISABLED | EIE1_ESMB0__DISABLED
			| EIE1_ET3__DISABLED | EIE1_EUSB0__ENABLED;
	// [EIE1 - Extended Interrupt Enable 1]$

	// $[EIP1 - Extended Interrupt Priority 1]
	// [EIP1 - Extended Interrupt Priority 1]$

	// $[IE - Interrupt Enable]
	/***********************************************************************
	 - Enable each interrupt according to its individual mask setting
	 - Disable external interrupt 0
	 - Disable external interrupt 1
	 - Disable all SPI0 interrupts
	 - Disable all Timer 0 interrupt
	 - Disable all Timer 1 interrupt
	 - Disable Timer 2 interrupt
	 - Disable UART0 interrupt
	 ***********************************************************************/
	IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED
			| IE_ESPI0__DISABLED | IE_ET0__DISABLED | IE_ET1__DISABLED
			| IE_ET2__DISABLED | IE_ES0__DISABLED;
	// [IE - Interrupt Enable]$

	// $[IP - Interrupt Priority]
	// [IP - Interrupt Priority]$

	// $[EIE2 - Extended Interrupt Enable 2]
	// [EIE2 - Extended Interrupt Enable 2]$

	// $[EIP2 - Extended Interrupt Priority 2]
	// [EIP2 - Extended Interrupt Priority 2]$

}

extern void USBLIB_0_enter_DefaultMode_from_RESET(void) {
	// $[USBD Init]
	USBD_Init (&initstruct);
	// [USBD Init]$

}

extern void PORTS_1_enter_DefaultMode_from_RESET(void) {
	// $[P1 - Port 1 Pin Latch]
	// [P1 - Port 1 Pin Latch]$

	// $[P1MDOUT - Port 1 Output Mode]
	/***********************************************************************
	 - P1.0 output is push-pull
	 - P1.1 output is open-drain
	 - P1.2 output is open-drain
	 - P1.3 output is open-drain
	 - P1.4 output is open-drain
	 - P1.5 output is open-drain
	 - P1.6 output is push-pull
	 - P1.7 output is push-pull
	 ***********************************************************************/
	P1MDOUT = P1MDOUT_B0__PUSH_PULL | P1MDOUT_B1__OPEN_DRAIN
			| P1MDOUT_B2__OPEN_DRAIN | P1MDOUT_B3__OPEN_DRAIN
			| P1MDOUT_B4__OPEN_DRAIN | P1MDOUT_B5__OPEN_DRAIN
			| P1MDOUT_B6__PUSH_PULL | P1MDOUT_B7__PUSH_PULL;
	// [P1MDOUT - Port 1 Output Mode]$

	// $[P1MDIN - Port 1 Input Mode]
	/***********************************************************************
	 - P1.0 pin is configured for digital mode
	 - P1.1 pin is configured for digital mode
	 - P1.2 pin is configured for digital mode
	 - P1.3 pin is configured for digital mode
	 - P1.4 pin is configured for digital mode
	 - P1.5 pin is configured for analog mode
	 - P1.6 pin is configured for digital mode
	 - P1.7 pin is configured for digital mode
	 ***********************************************************************/
	P1MDIN = P1MDIN_B0__DIGITAL | P1MDIN_B1__DIGITAL | P1MDIN_B2__DIGITAL
			| P1MDIN_B3__DIGITAL | P1MDIN_B4__DIGITAL | P1MDIN_B5__ANALOG
			| P1MDIN_B6__DIGITAL | P1MDIN_B7__DIGITAL;
	// [P1MDIN - Port 1 Input Mode]$

	// $[P1SKIP - Port 1 Skip]
	/***********************************************************************
	 - P1.0 pin is not skipped by the crossbar
	 - P1.1 pin is skipped by the crossbar
	 - P1.2 pin is skipped by the crossbar
	 - P1.3 pin is skipped by the crossbar
	 - P1.4 pin is skipped by the crossbar
	 - P1.5 pin is skipped by the crossbar
	 - P1.6 pin is not skipped by the crossbar
	 - P1.7 pin is not skipped by the crossbar
	 ***********************************************************************/
	P1SKIP = P1SKIP_B0__NOT_SKIPPED | P1SKIP_B1__SKIPPED | P1SKIP_B2__SKIPPED
			| P1SKIP_B3__SKIPPED | P1SKIP_B4__SKIPPED | P1SKIP_B5__SKIPPED
			| P1SKIP_B6__NOT_SKIPPED | P1SKIP_B7__NOT_SKIPPED;
	// [P1SKIP - Port 1 Skip]$

}

extern void PBCFG_0_enter_DefaultMode_from_RESET(void) {
	// $[XBR1 - Port I/O Crossbar 1]
	/***********************************************************************
	 - Weak Pullups enabled 
	 - Crossbar enabled
	 - CEX0, CEX1, CEX2 routed to Port pins
	 - ECI unavailable at Port pin
	 - T0 unavailable at Port pin
	 - T1 unavailable at Port pin
	 ***********************************************************************/
	XBR1 = XBR1_WEAKPUD__PULL_UPS_ENABLED | XBR1_XBARE__ENABLED
			| XBR1_PCA0ME__CEX0_CEX1_CEX2 | XBR1_ECIE__DISABLED
			| XBR1_T0E__DISABLED | XBR1_T1E__DISABLED;
	// [XBR1 - Port I/O Crossbar 1]$

	// $[XBR0 - Port I/O Crossbar 0]
	// [XBR0 - Port I/O Crossbar 0]$

	// $[XBR2 - Port I/O Crossbar 2]
	// [XBR2 - Port I/O Crossbar 2]$

}

extern void UART_0_enter_DefaultMode_from_RESET(void) {
	// $[SCON0 - UART0 Serial Port Control]
	/***********************************************************************
	 - UART0 reception enabled
	 ***********************************************************************/
	SCON0 |= SCON0_REN__RECEIVE_ENABLED;
	// [SCON0 - UART0 Serial Port Control]$

}

extern void PORTS_0_enter_DefaultMode_from_RESET(void) {
	// $[P0 - Port 0 Pin Latch]
	// [P0 - Port 0 Pin Latch]$

	// $[P0MDOUT - Port 0 Output Mode]
	/***********************************************************************
	 - P0.0 output is push-pull
	 - P0.1 output is open-drain
	 - P0.2 output is push-pull
	 - P0.3 output is open-drain
	 - P0.4 output is open-drain
	 - P0.5 output is open-drain
	 - P0.6 output is push-pull
	 - P0.7 output is open-drain
	 ***********************************************************************/
	P0MDOUT = P0MDOUT_B0__PUSH_PULL | P0MDOUT_B1__OPEN_DRAIN
			| P0MDOUT_B2__PUSH_PULL | P0MDOUT_B3__OPEN_DRAIN
			| P0MDOUT_B4__OPEN_DRAIN | P0MDOUT_B5__OPEN_DRAIN
			| P0MDOUT_B6__PUSH_PULL | P0MDOUT_B7__OPEN_DRAIN;
	// [P0MDOUT - Port 0 Output Mode]$

	// $[P0MDIN - Port 0 Input Mode]
	// [P0MDIN - Port 0 Input Mode]$

	// $[P0SKIP - Port 0 Skip]
	/***********************************************************************
	 - P0.0 pin is skipped by the crossbar
	 - P0.1 pin is skipped by the crossbar
	 - P0.2 pin is skipped by the crossbar
	 - P0.3 pin is skipped by the crossbar
	 - P0.4 pin is skipped by the crossbar
	 - P0.5 pin is skipped by the crossbar
	 - P0.6 pin is not skipped by the crossbar
	 - P0.7 pin is not skipped by the crossbar
	 ***********************************************************************/
	P0SKIP = P0SKIP_B0__SKIPPED | P0SKIP_B1__SKIPPED | P0SKIP_B2__SKIPPED
			| P0SKIP_B3__SKIPPED | P0SKIP_B4__SKIPPED | P0SKIP_B5__SKIPPED
			| P0SKIP_B6__NOT_SKIPPED | P0SKIP_B7__NOT_SKIPPED;
	// [P0SKIP - Port 0 Skip]$

}

extern void SPI_0_enter_DefaultMode_from_RESET(void) {
	// $[SPI0CKR - SPI0 Clock Rate]
	/***********************************************************************
	 - SPI0 Clock Rate = 0x17
	 ***********************************************************************/
	SPI0CKR = (0x17 << SPI0CKR_SPI0CKR__SHIFT);
	// [SPI0CKR - SPI0 Clock Rate]$

	// $[SPI0CFG - SPI0 Configuration]
	/***********************************************************************
	 - Enable master mode. Operate as a master
	 ***********************************************************************/
	SPI0CFG |= SPI0CFG_MSTEN__MASTER_ENABLED;
	// [SPI0CFG - SPI0 Configuration]$

	// $[SPI0CN0 - SPI0 Control]
	/***********************************************************************
	 - Enable the SPI module
	 - 3-Wire Slave or 3-Wire Master Mode
	 ***********************************************************************/
	SPI0CN0 &= ~SPI0CN0_NSSMD__FMASK;
	SPI0CN0 |= SPI0CN0_SPIEN__ENABLED;
	// [SPI0CN0 - SPI0 Control]$

}

extern void PCACH_0_enter_DefaultMode_from_RESET(void) {
	// $[PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]
	/***********************************************************************
	 - Disable negative edge capture
	 - Disable CCF0 interrupts
	 - Disable match function
	 - 8-bit PWM selected
	 - Disable positive edge capture
	 - Enable comparator function
	 - Enable PWM function
	 - Disable toggle function
	 ***********************************************************************/
	PCA0CPM0 = PCA0CPM0_CAPN__DISABLED | PCA0CPM0_ECCF__DISABLED
			| PCA0CPM0_MAT__DISABLED | PCA0CPM0_PWM16__8_BIT
			| PCA0CPM0_CAPP__DISABLED | PCA0CPM0_ECOM__ENABLED
			| PCA0CPM0_PWM__ENABLED | PCA0CPM0_TOG__DISABLED;
	// [PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]$

	// $[PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]
	// [PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]$

	// $[PCA0CPH0 - PCA Channel 0 Capture Module High Byte]
	PCA0CPH0 = 0x00;
	// [PCA0CPH0 - PCA Channel 0 Capture Module High Byte]$

	// $[PCA0 Start/Run restore]
	// [PCA0 Start/Run restore]$

}

extern void PCACH_1_enter_DefaultMode_from_RESET(void) {
	// $[PCA0CPM1 - PCA Channel 1 Capture/Compare Mode]
	/***********************************************************************
	 - Disable negative edge capture
	 - Disable CCF1 interrupts
	 - Disable match function
	 - 8-bit PWM selected
	 - Disable positive edge capture
	 - Enable comparator function
	 - Enable PWM function
	 - Disable toggle function
	 ***********************************************************************/
	PCA0CPM1 = PCA0CPM1_CAPN__DISABLED | PCA0CPM1_ECCF__DISABLED
			| PCA0CPM1_MAT__DISABLED | PCA0CPM1_PWM16__8_BIT
			| PCA0CPM1_CAPP__DISABLED | PCA0CPM1_ECOM__ENABLED
			| PCA0CPM1_PWM__ENABLED | PCA0CPM1_TOG__DISABLED;
	// [PCA0CPM1 - PCA Channel 1 Capture/Compare Mode]$

	// $[PCA0CPL1 - PCA Channel 1 Capture Module Low Byte]
	// [PCA0CPL1 - PCA Channel 1 Capture Module Low Byte]$

	// $[PCA0CPH1 - PCA Channel 1 Capture Module High Byte]
	PCA0CPH1 = 0x00;
	// [PCA0CPH1 - PCA Channel 1 Capture Module High Byte]$

	// $[PCA0 Start/Run restore]
	// [PCA0 Start/Run restore]$

}

extern void PCACH_2_enter_DefaultMode_from_RESET(void) {
	// $[PCA0CPM2 - PCA Channel 2 Capture/Compare Mode]
	/***********************************************************************
	 - Disable negative edge capture
	 - Disable CCF2 interrupts
	 - Disable match function
	 - 8-bit PWM selected
	 - Disable positive edge capture
	 - Enable comparator function
	 - Enable PWM function
	 - Disable toggle function
	 ***********************************************************************/
	PCA0CPM2 = PCA0CPM2_CAPN__DISABLED | PCA0CPM2_ECCF__DISABLED
			| PCA0CPM2_MAT__DISABLED | PCA0CPM2_PWM16__8_BIT
			| PCA0CPM2_CAPP__DISABLED | PCA0CPM2_ECOM__ENABLED
			| PCA0CPM2_PWM__ENABLED | PCA0CPM2_TOG__DISABLED;
	// [PCA0CPM2 - PCA Channel 2 Capture/Compare Mode]$

	// $[PCA0CPL2 - PCA Channel 2 Capture Module Low Byte]
	// [PCA0CPL2 - PCA Channel 2 Capture Module Low Byte]$

	// $[PCA0CPH2 - PCA Channel 2 Capture Module High Byte]
	PCA0CPH2 = 0x00;
	// [PCA0CPH2 - PCA Channel 2 Capture Module High Byte]$

	// $[PCA0 Start/Run restore]
	// [PCA0 Start/Run restore]$

}

extern void PORTS_2_enter_DefaultMode_from_RESET(void) {
	// $[P2 - Port 2 Pin Latch]
	// [P2 - Port 2 Pin Latch]$

	// $[P2MDOUT - Port 2 Output Mode]
	/***********************************************************************
	 - P2.0 output is push-pull
	 - P2.1 output is open-drain
	 - P2.2 output is open-drain
	 - P2.3 output is open-drain
	 - P2.4 output is open-drain
	 - P2.5 output is open-drain
	 - P2.6 output is open-drain
	 - P2.7 output is open-drain
	 ***********************************************************************/
	P2MDOUT = P2MDOUT_B0__PUSH_PULL | P2MDOUT_B1__OPEN_DRAIN
			| P2MDOUT_B2__OPEN_DRAIN | P2MDOUT_B3__OPEN_DRAIN
			| P2MDOUT_B4__OPEN_DRAIN | P2MDOUT_B5__OPEN_DRAIN
			| P2MDOUT_B6__OPEN_DRAIN | P2MDOUT_B7__OPEN_DRAIN;
	// [P2MDOUT - Port 2 Output Mode]$

	// $[P2MDIN - Port 2 Input Mode]
	/***********************************************************************
	 - P2.0 pin is configured for digital mode
	 - P2.1 pin is configured for digital mode
	 - P2.2 pin is configured for digital mode
	 - P2.3 pin is configured for digital mode
	 - P2.4 pin is configured for digital mode
	 - P2.5 pin is configured for analog mode
	 - P2.6 pin is configured for digital mode
	 - P2.7 pin is configured for digital mode
	 ***********************************************************************/
	P2MDIN = P2MDIN_B0__DIGITAL | P2MDIN_B1__DIGITAL | P2MDIN_B2__DIGITAL
			| P2MDIN_B3__DIGITAL | P2MDIN_B4__DIGITAL | P2MDIN_B5__ANALOG
			| P2MDIN_B6__DIGITAL | P2MDIN_B7__DIGITAL;
	// [P2MDIN - Port 2 Input Mode]$

	// $[P2SKIP - Port 2 Skip]
	/***********************************************************************
	 - P2.0 pin is not skipped by the crossbar
	 - P2.1 pin is not skipped by the crossbar
	 - P2.2 pin is not skipped by the crossbar
	 - P2.3 pin is not skipped by the crossbar
	 - P2.4 pin is not skipped by the crossbar
	 - P2.5 pin is skipped by the crossbar
	 - P2.6 pin is not skipped by the crossbar
	 - P2.7 pin is not skipped by the crossbar
	 ***********************************************************************/
	P2SKIP = P2SKIP_B0__NOT_SKIPPED | P2SKIP_B1__NOT_SKIPPED
			| P2SKIP_B2__NOT_SKIPPED | P2SKIP_B3__NOT_SKIPPED
			| P2SKIP_B4__NOT_SKIPPED | P2SKIP_B5__SKIPPED
			| P2SKIP_B6__NOT_SKIPPED | P2SKIP_B7__NOT_SKIPPED;
	// [P2SKIP - Port 2 Skip]$

}

extern void ADC_0_enter_DefaultMode_from_RESET(void) {
	// $[ADC0CF - ADC0 Configuration]
	/***********************************************************************
	 - Data in the ADC0H:ADC0L registers is right-justified
	 - SAR Clock Divider = 0x05
	 ***********************************************************************/
	ADC0CF = ADC0CF_ADLJST__RIGHT_JUSTIFIED | (0x05 << ADC0CF_ADSC__SHIFT);
	// [ADC0CF - ADC0 Configuration]$

	// $[ADC0GTH - ADC0 Greater-Than High Byte]
	// [ADC0GTH - ADC0 Greater-Than High Byte]$

	// $[ADC0GTL - ADC0 Greater-Than Low Byte]
	// [ADC0GTL - ADC0 Greater-Than Low Byte]$

	// $[ADC0LTH - ADC0 Less-Than High Byte]
	// [ADC0LTH - ADC0 Less-Than High Byte]$

	// $[ADC0LTL - ADC0 Less-Than Low Byte]
	// [ADC0LTL - ADC0 Less-Than Low Byte]$

	// $[AMX0N - AMUX0 Negative Multiplexer Selection]
	/***********************************************************************
	 - Ground 
	 ***********************************************************************/
	AMX0N = AMX0N_AMX0N__GND;
	// [AMX0N - AMUX0 Negative Multiplexer Selection]$

	// $[AMX0P - AMUX0 Positive Multiplexer Selection]
	/***********************************************************************
	 - Select ADC0P.4
	 ***********************************************************************/
	AMX0P = AMX0P_AMX0P__ADC0P4;
	// [AMX0P - AMUX0 Positive Multiplexer Selection]$

	// $[ADC0CN0 - ADC0 Control]
	/***********************************************************************
	 - ADC0 Enabled 
	 - ADC0 conversion initiated on overflow of Timer 0
	 ***********************************************************************/
	ADC0CN0 &= ~ADC0CN0_ADCM__FMASK;
	ADC0CN0 |= ADC0CN0_ADEN__ENABLED | ADC0CN0_ADCM__TIMER0;
	// [ADC0CN0 - ADC0 Control]$

}

extern void VREF_0_enter_DefaultMode_from_RESET(void) {
	// $[REF0CN - Voltage Reference Control]
	/***********************************************************************
	 - Disable the internal Temperature Sensor
	 - Disable the internal reference buffer
	 - The on-chip voltage reference buffer gain is 2
	 - The REFSL bit selects the voltage reference source
	 - Use VDD as the voltage reference
	 ***********************************************************************/
	REF0CN = REF0CN_TEMPE__DISABLED | REF0CN_REFBE__DISABLED
			| REF0CN_REFBGS__GAIN_2 | REF0CN_REGOVR__REFSL | REF0CN_REFSL__VDD;
	// [REF0CN - Voltage Reference Control]$

}

extern void CIP51_0_enter_DefaultMode_from_RESET(void) {
	// $[PFE0CN - Prefetch Engine Control]
	/***********************************************************************
	 - Each byte of a firmware flash write is written individually
	 - Disable the prefetch engine 
	 ***********************************************************************/
	PFE0CN = PFE0CN_FLBWE__BLOCK_WRITE_DISABLED | PFE0CN_PFEN__DISABLED;
	// [PFE0CN - Prefetch Engine Control]$

}

extern void TIMER16_3_enter_DefaultMode_from_RESET(void) {
	// $[Timer Initialization]
	// Save Timer Configuration
	uint8_t TMR3CN0_TR3_save;
	TMR3CN0_TR3_save = TMR3CN0 & TMR3CN0_TR3__BMASK;
	// Stop Timer
	TMR3CN0 &= ~(TMR3CN0_TR3__BMASK);
	// [Timer Initialization]$

	// $[TMR3CN0 - Timer 3 Control]
	// [TMR3CN0 - Timer 3 Control]$

	// $[TMR3H - Timer 3 High Byte]
	/***********************************************************************
	 - Timer 3 High Byte = 0xF8
	 ***********************************************************************/
	TMR3H = (0xF8 << TMR3H_TMR3H__SHIFT);
	// [TMR3H - Timer 3 High Byte]$

	// $[TMR3L - Timer 3 Low Byte]
	/***********************************************************************
	 - Timer 3 Low Byte = 0x30
	 ***********************************************************************/
	TMR3L = (0x30 << TMR3L_TMR3L__SHIFT);
	// [TMR3L - Timer 3 Low Byte]$

	// $[TMR3RLH - Timer 3 Reload High Byte]
	/***********************************************************************
	 - Timer 3 Reload High Byte = 0xF0
	 ***********************************************************************/
	TMR3RLH = (0xF0 << TMR3RLH_TMR3RLH__SHIFT);
	// [TMR3RLH - Timer 3 Reload High Byte]$

	// $[TMR3RLL - Timer 3 Reload Low Byte]
	/***********************************************************************
	 - Timer 3 Reload Low Byte = 0x60
	 ***********************************************************************/
	TMR3RLL = (0x60 << TMR3RLL_TMR3RLL__SHIFT);
	// [TMR3RLL - Timer 3 Reload Low Byte]$

	// $[TMR3CN0]
	/***********************************************************************
	 - Start Timer 3 running
	 ***********************************************************************/
	TMR3CN0 |= TMR3CN0_TR3__RUN;
	// [TMR3CN0]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	TMR3CN0 |= TMR3CN0_TR3_save;
	// [Timer Restoration]$

}

