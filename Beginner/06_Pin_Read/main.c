/*
 * Date:	June 19, 2021
 * Author:	Michael Ly
 * Details:	Write a program which reads the status of the pin PA0. If the
 * 			status of PA0 is LOW, then turn OFF the on-board LED(PG13), and if the
 * 			status of PA0 is HIGH, then turn ON the LED
 */

#include <stdint.h>
#include <stdio.h>

/* Function Prototype(s) */
extern void initialise_monitor_handles(void);							// Semihosting Debugger

/* Constants */
// RCC
uint32_t const	ADDR_RCC		= 0x40023830 ;						// Address of the RCC peripheral clock reg (AHB1ENR)
// PG13         
uint32_t const	ADDR_MODE_G		= 0x40021800 ;						// Address of GPIOG pin 13 (Green_LED)
uint32_t const	ADDR_OUT_G		= 0x40021814 ;						// Address of GPIOG output data register
uint32_t const	M_CLK_EN_G		= 1 << 6 ;							            // Mask to set the 6th bit: clk enable
uint32_t const	M_CLR_MODE_G	= 3 << 26 ;							// Clears the 24th and 25th bits by shifting 2'b11
uint32_t const	M_MODE_SET_G	= 1 << 26 ;							// Set bits [27:26] to 2'b01
uint32_t const	M_OUT_SET_G		= 1 << 13 ;						// SETs the 13th bit position of output data register
// PA0          
uint32_t const	ADD_MODE_A		= 0x40020000 ;						// Address of GPIOA pin 0
uint32_t const	ADDR_IN_A		= 0x40020010 ;						// Address of GPIOG input data register
uint32_t const	M_CLK_EN_A		= 1 << 0 ;						// Mask: Clock Enable A
uint32_t const	M_CLR_MODE_A	= 3 << 0;							// Mask: Clears  0th and 1st bit positions of MODER
uint32_t const	M_IN_SET_A		= 1 << 0;						// Mask: Sets 0th bit position in IDR


int main(void) {            
	initialise_monitor_handles();								// Semihosting Debugger

	// 0.) Assign addresses to pointers after calculating offsets           
	uint32_t volatile	*pClkCtrlReg	= (uint32_t*) ADDR_RCC ;	        	// Pointer address for RCC
	uint32_t volatile	*pPortGModeReg	= (uint32_t*) ADDR_MODE_G ;	            	// Pointer address for Port G Mode
	uint32_t volatile	*pPortGOutReg	= (uint32_t*) ADDR_OUT_G ;	            	// Pointer address for Port G Out

	uint32_t volatile	*pPortAModeReg	= (uint32_t*) ADD_MODE_A ;	            	// Pointer address for Port A Mode
	uint32_t volatile	*pPortAInReg	= (uint32_t*) ADDR_IN_A ;	            	// Pointer address for Port A In
	/* Flag */          
	uint8_t				pinStatus ;						// Tells whether or not pin is HI/LO

	// 1.) Enable the clock for GPIOG and GPIOA peripherals in the AHB1ENR
	*pClkCtrlReg |= M_CLK_EN_G ;								// SET G clk enable bit with mask
	*pClkCtrlReg |= M_CLK_EN_A ;								// SET A clk enable bit with mask


	// 2.) Configure the mode of the G IO pin as output (01)
	// a.) Clear the 26th and 27th bit positions
	*pPortGModeReg &= ~M_CLR_MODE_G ;
	// b.) Make 26th bit position as 1 (SET)
	*pPortGModeReg |=  M_MODE_SET_G ;

	// 2.) Configure the mode of the IO pin as input (00)
	// a.) Clear the 0th and 1st bit positions:
	*pPortAModeReg	&= ~M_CLR_MODE_A ;

	/* Loop forever */
	while (1) {
		// 3.) Read the pin status of the pin PA0 (GPIOA INPUT DATA REG):
		pinStatus = (uint8_t)(*pPortAInReg & M_IN_SET_A) ;				// Test PA0's LSB

		if (pinStatus) {
			// Turn ON the LED
			*pPortGOutReg |= M_OUT_SET_G ;
		}
		else {
			// Turn OFF the LED
			*pPortGOutReg &= ~M_OUT_SET_G ;
		}
	}
}
