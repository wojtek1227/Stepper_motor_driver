/*
 * StepperMotor.c
 *
 * Created: 19.11.2016 13:15:17
 *  Author: caputa
 */ 

#include <avr/io.h>

#include "StepperMotor.h"


//Init Functions
void SwitchInit(void)
{
	//Limit switch initialization
	DDRB &= ~((1<<SWITCH1) | (1<<SWITCH2));
	PORTB |= (1<<SWITCH1) | (1<<SWITCH2);
}

void StepperInit(void)
{
	MOTORDDR |= SET_ALL_MASK;
	PORTC &= CLEAR_ALL_MASK;
}

//One Step Functions

/* Full Step*/
void FullStep(uint8_t direction)
{
	switch(CurrentState)
	{
		case AP_BP:
			CurrentState = State_AP_BP(direction) + (direction ? (-1) : (1));
			break;
		case BP_AM:
			CurrentState = State_BP_AM(direction) + (direction ? (-1) : (1));
			break;
		case AM_BM:
			CurrentState = State_AM_BM(direction) + (direction ? (-1) : (1));
			break;
		default:
			CurrentState = State_BM_AP(direction) + (direction ? (-1) : (1));
			break;
	}
}

/* Half Step */
void HalfStep(uint8_t direction)
{
	switch(CurrentState)
	{
		case AP:
			CurrentState = State_AP(direction);
			break;
		case AP_BP:
			CurrentState = State_AP_BP(direction);
			break;
		case BP:
			CurrentState = State_BP(direction);
			break;
		case BP_AM:
			CurrentState = State_BP_AM(direction);
			break;
		case AM:
			CurrentState = State_AM(direction);
			break;
		case AM_BM:
			CurrentState = State_AM_BM(direction);
			break;
		case BM:
			CurrentState = State_BM(direction);
			break;
		default:
			CurrentState = State_BM_AP(direction);
			break;
	}
}
