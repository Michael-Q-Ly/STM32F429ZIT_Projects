/*
 * Date:	June 18, 2021
 * Author:	Michael Ly
 * Details:	Modify your LED program from project 004 to toggle the LED
 * 			by creating a software delay between LED on and LED off
 */

#include <stdint.h>
#include <stdio.h>

extern void initialise_monitor_handles(void);				// Semihosting Debugger

/* Constants */
uint32_t const	ADDR_RCC	= 0x40023830 ;					// Address of the RCC peripheral clock reg (AHB1ENR)
uint32_t const	ADDR_MODE	= 0x40021800 ;					// Address of GPIOG pin 13 (Green_LED)
uint32_t const	ADDR_OUT	= 0x40021814 ;					// Address of GPIOG output data register
uint32_t const	M_CLK_EN	= 1 << 6 ;						// Mask to set the 6th bit: clk enable
uint32_t const	M_CLR_MODE	= 3 << 26 ;						// Clears the 24th and 25th bits by shifting 2'b11
uint32_t const	M_MODE_SET	= 1 << 26 ;						// Set bits [27:26] to 2'b01
uint32_t const	M_OUT_SET	= 1 << 13 ;						// SETs the 13th bit position of output data register
uint32_t const	DELAY		= 300000 ;						// Delay to set the bit on or off

int main(void)
{
	initialise_monitor_handles();							// Semihosting Debugger

	/* Variables */
	uint32_t count ;

	// 0.) Assign addresses to pointers after calculating offsets
	uint32_t *pClkCtrlReg	= (uint32_t*) ADDR_RCC ;		// Pointer address for RCC
	uint32_t *pPortGModeReg	= (uint32_t*) ADDR_MODE ;		// Pointer address for Port G Mode
	uint32_t *pPortGOutReg	= (uint32_t*) ADDR_OUT ;		// Pointer address for Port G Out


	// 1.) Enable the clock for GPIOG peripheral in the AHB1ENR
	*pClkCtrlReg |= M_CLK_EN ;								// Set clk enable bit with mask

	// 2.) Configure the mode of the IO pin as output (01)
	// a.) Clear the 26th and 27th bit positions
	*pPortGModeReg &= ~M_CLR_MODE ;
	// b.) Make 26th bit position as 1 (SET)
	*pPortGModeReg |=  M_MODE_SET ;

	// 3.) SET the 13th bit of the output data register to make I/O pin-13 HIGH
	*pPortGOutReg |= M_OUT_SET ;

	/* Loop forever */
	while (1) {
		// Toggle the LED  with a NAND operation after a delay
		for (count = 0; count < DELAY; count++) ;			// NOP
		*pPortGOutReg ^= M_OUT_SET ;
	}
}
