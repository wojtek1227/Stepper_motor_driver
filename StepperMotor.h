/*
 * StepperMotor.h
 *
 * Created: 19.11.2016 13:14:55
 *  Author: caputa
 *  APLUS		RED	 ----		---- BPLUS BLUE
 *						}		{
 *						}		{
 *	COM1	 BLACK	 ----		---- COM2 WHITE
 *						}		{
 *						}		{
 *	AMINUS YELLOW	 ----		---- BMINUS oRANGE
 *
 * Connect 
 *		APLUS to PORTC0
 *		BPLUS to PORTC1
 *		AMINUS to PORTC2
 *		BMINUS to PORTC3
 */ 


#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include <avr/io.h>
#include <stdint.h>

#define SWITCH1 PORTB1
#define SWITCH2 PORTB2

#define MOTORDDR DDRC
#define MOTORPORT PORTC
#define SET_ALL_MASK 0x0f
#define CLEAR_ALL_MASK 0xf0

#define AP_MASK (1<<PORTC0)
#define BP_MASK (1<<PORTC1)
#define AM_MASK (1<<PORTC2)
#define BM_MASK (1<<PORTC3)

//Variables

enum states
{
	AP,			//0
	AP_BP,		//1
	BP,			//2
	BP_AM,		//3
	AM,			//4
	AM_BM,		//5
	BM,			//6
	BM_AP		//7
} CurrentState;

//Init Functions
void SwitchInit(void);
void StepperInit(void);

//One Step Functions
void FullStep(uint8_t direction);
void HalfStep(uint8_t direction);

//
inline uint8_t State_AP(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= AP_MASK;
	if (direction == 0) return 1;
	else return 7;
}

inline uint8_t State_AP_BP(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= AP_MASK| BP_MASK;
	if (direction == 0) return 2;
	else return 0;
}

inline uint8_t State_BP(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= BP_MASK;
	if (direction == 0) return 3;
	else return 1;
}

inline uint8_t State_BP_AM(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= BP_MASK|AM_MASK;
	if (direction == 0) return 4;
	else return 2;
}

inline uint8_t State_AM(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= AM_MASK;
	if (direction == 0) return 5;
	else return 3;
}

inline uint8_t State_AM_BM(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= AM_MASK | BM_MASK;
	if (direction == 0) return 6;
	else return 4;
}

inline uint8_t State_BM(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= BM_MASK;
	if (direction == 0) return 7;
	else return 5;
}

inline uint8_t State_BM_AP(uint8_t direction)
{
	MOTORPORT &= CLEAR_ALL_MASK;
	MOTORPORT |= BM_MASK | AP_MASK;
	if (direction == 0) return 0;
	else return 6;
}


#endif /* STEPPERMOTOR_H_ */
