/*
 * StepperMotorDriver.c
 *
 * Created: 18.11.2016 16:50:55
 * Author : caputa
 */ 


#include "StepperMotor.h"
#include "UART.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
	StepperInit();
	SwitchInit();
	UARTInit();
	sei();
    /* Replace with your application code */
    while (1) 
    {	
    }
}

