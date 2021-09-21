/*
 * Date:	June 19, 2021
 * Author:	Michael Ly
 * Details:	Demonstration of data alignment
 * Target:  STM2F429ZIT
 */

#include <stdint.h>
#include <stdio.h>

/* Structs */
struct dataSet {
	char	data1 ;
	int		data2 ;
	char	data3 ;
	short	data4 ;
}__attribute__((packed));

/* Function Prototype(s) */
extern void initialise_monitor_handles(void);									// Semihosting Debugger

struct dataSet data ;

int main(void) {
	initialise_monitor_handles();												// Semihosting Debugger

	// Initialize struct dataSet variables
	data.data1 = 0xAA ;
	data.data2 = 0xFFFFEEEE ;
	data.data3 = 0x55 ;
	data.data4 = 0xA5A5 ;

	// Print out the data from dataSet
	printf("data.data1 = %d\n", data.data1) ;
	printf("data.data2 = %d\n", data.data2) ;
	printf("data.data3 = %d\n", data.data3) ;
	printf("data.data4 = %d\n", data.data4) ;

    /* Loop forever */
	while (1) {

	}
}

