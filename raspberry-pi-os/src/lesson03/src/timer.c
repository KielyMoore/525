#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "peripherals/arm_timer.h"

const unsigned int interval = 2000;
unsigned int curVal = 0;

void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	printf("Timer interrupt received\n\r");
}

void arm_timer_init ( void )
{
	put32(ARM_TIMER_LOAD, interval);				// Set Timer Value
	put32(ARM_TIMER_CONTROL, ARM_TIMER_CTRL_VAL);	// Set Timer Control Register
}

void handle_arm_timer_irq ( void )
{
	put32(ARM_TIMER_IRQ_CA, 1);						// Clear the Interupt
	printf("ARM Timer Interrupt Recieved\n\r");
}
