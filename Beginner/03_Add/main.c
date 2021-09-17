
#include <stdio.h>

/* Global Variables */
int g_data1 = -4000 ;
int g_data2 = 200 ;
int result  = 0 ;

extern void initialise_monitor_handles(void);

int main(void)
{
	initialise_monitor_handles();

	result = g_data1 + g_data2 ;

	printf("Result = %d\n", result) ;

	for (;;) ;
}
