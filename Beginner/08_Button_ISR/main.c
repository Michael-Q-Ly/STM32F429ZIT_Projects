/*
 * Date:	June 19, 2021
 * Author:	Michael Ly
 * Details:	This program debounces a button and counts the amount of times
 * 			you press the user button on the STM32F429 Discovery 1 board.
 * 			It uses optimization level 3. Determine what is wrong before
 * 			using 'volatile' keyword.
 * BOARD:	stm32f4xxx
 */

#include <stdint.h>
#include <stdio.h>

/* Constants */
// MASKS
uint32_t const	M_CLK_A	= 1 << 0 ;												// Enables clk A
uint32_t const	M_APB2	= 1 << 14 ;												// APB2 clock sets SYSCF pin
uint32_t const	M_PEND	= 1 << 0 ;
uint32_t const	M_RTSR	= 1 << 0 ;												// Rising-edge Triggered Select Register for GPIOA0
uint32_t const	M_IMR	= 1 << 0 ;												// Interrupt Mask Register for GPIOA0
uint32_t const	M_NVIC	= 1 << 6 ;												// Position 6 in Ch.12 Vector Table sets EXTI0
// Delay
uint32_t const DELAY	= 10000 ;


/* Function Prototype(s) */
extern void initialise_monitor_handles(void);									// Semihosting Debugger
void button_init(void) ;

/* Global shared variable between main code and ISR */
uint8_t volatile g_button_pressed = 0 ;
uint32_t g_button_press_count = 0 ;

/* MMIO Addresses */
uint32_t volatile *pEXTIPendReg			= (uint32_t*) (0x40013C00 + 0x14) ;		// External Pending Register
uint32_t volatile *pClkCtrlReg			= (uint32_t*) (0x40023800 + 0x30) ;		// PA0 CLK en reg
uint32_t volatile *pClkCtrlRegApb2		= (uint32_t*) (0x40023800 + 0x44) ;		// SYSCFG en
uint32_t volatile *pGPIOAModeReg 		= (uint32_t*) (0x40020000 + 0x00) ;		// Mode Reg A
uint32_t volatile *pEXTIMaskReg 		= (uint32_t*) (0x40013C00 + 0x00) ;		// External Interrupt Mask Register
uint32_t volatile *pEXTIEdgeCtrlReg		= (uint32_t*) (0x40013C00 + 0x08) ;		// Rising trigger selection register (EXTI_RTSR)
uint32_t volatile *pNVICIRQEnReg 		= (uint32_t*) (0xE000E100		) ;		// Nested Vectored Interrupt Controller (NVIC)


int main(void) {
	initialise_monitor_handles();												// Semihosting Debugger

	/* Variables */
	uint32_t volatile timer ;
	
	/* Initialize register addresses */
	button_init() ;

    /* Loop forever */
	while (1) {
		// Disable interrupt (clear bit with NAND)
		*pEXTIMaskReg &= ~M_IMR ;
		
		if (g_button_pressed) {
			// Delay for button debouncing
			for (timer = 0; timer < DELAY/2; timer++) ;							// NOP
			g_button_press_count++ ;											// Increment button-press counter
			printf("Button is pressed: %lu\n", g_button_press_count) ;
			g_button_pressed = 0 ;												// Turn off button press variable
		}

		// Enable interrupt
		*pEXTIMaskReg |= M_IMR ;
	}
}


void button_init(void) {
	/* Set bit positions */
	// Enable Clocks
	*pClkCtrlReg		|=	M_CLK_A ;
	*pClkCtrlRegApb2	|=	M_APB2 ;

	// Enable external interrupt registers
	*pEXTIEdgeCtrlReg	|=	M_RTSR ;		// Enable bit 0 Rising-Edge Trigger Select Register
	*pEXTIMaskReg		|=	M_IMR ;			// Enable bit 0 Interrupt Mask Register
	*pNVICIRQEnReg		|=	M_NVIC ;		// Enable EXTI0
}

void EXTI0_IRQHandler(void) {
	// Make this flag SET if button pressed
	g_button_pressed = 1 ;
	*pEXTIPendReg	|= M_PEND ;
}
