/*
 * Date:	June 24, 2021
 * Author:	Michael Ly
 * Details:	This program toggles an LED on and off with a software timer. It is a modification
 *			of Project 005led_toggle. Instead of using masks, we use structs and bitfields
 *			for the internal registers of our board.
 *			Check the main.h header file for the structs, bitfields, constants, and
 *			function prototypes.
 * BOARD:	stm32f429
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"

/* Function Prototype(s) */
extern void initialise_monitor_handles(void) ;								// Semihosting Debugger
void initLED(void) ;

/* Constants */
// Memory Addresses
uint32_t const	ADDR_RCC	= 0x40023800 + 0x30 ;							// Address of the RCC peripheral clock reg (AHB1ENR)
uint32_t const	ADDR_MODE	= 0x40021800 + 0x00;							// Address of GPIOG pin 13 (Green_LED)
uint32_t const	ADDR_OUT	= 0x40021800 + 0x14 ;							// Address of GPIOG output data register
// Timing
uint32_t const	DELAY		= 300000 ;										// Delay to set the bit on or off

// 0.) Assign addresses to pointers
RCC_AHB1ENR_t volatile *const	pClkCtrlReg		= (RCC_AHB1ENR_t*)	ADDR_RCC ;
GPIOx_MODER_t volatile *const	pPortGModeReg	= (GPIOx_MODER_t*)	ADDR_MODE ;
GPIOx_ODR_t   volatile *const	pPortGOutReg	= (GPIOx_ODR_t*) 	ADDR_OUT ;

int main(void)
{
	initialise_monitor_handles();											// Semihosting Debugger	

	initLED() ;

	/* Loop forever */
	while (1) {
		for (uint32_t count = 0; count < DELAY; count++) ;					// NOP several times for a delay
		pPortGOutReg -> pin_13 ^= 1 ;										// Dereference struct pointer and xor w/ 1 to toggle
	}
}

void initLED(void) {
	// 1.) Enable the clock for GPIOG peripheral in the AHB1ENR
	pClkCtrlReg	-> gpiog_en = SET_CLOCK ;

	// 2.) Configure the mode of the IO pin as output (01)
	pPortGModeReg -> pin_13 = SET_MODE ;

	// 3.) SET the 13th bit of the output data register to make I/O pin-13 HIGH
	pPortGOutReg -> pin_13 = SET_OUTPUT ;
}
