/*
 * UART.c
 *
 * Created: 21.11.2016 14:21:54
 *  Author: caputa
 */ 

#include "UART.h"
#include "StepperMotor.h"


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

void uart_230400(void)
{
	#define BAUD 230400
	#include <util/setbaud.h>
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
}

void UARTInit(void)
{
	uart_230400();
	//Frame format 8 data bits, 2 stop bits
	UCSRC |= (1<<URSEL) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);
	UCSRB |= (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);
	
}

 void UART_Transmit(unsigned char data)
 {
	 while ( !( UCSRA & (1<<UDRE)));
	 UDR = data;
 }
 
unsigned char UART_Receive(void)
{
	while ( !(UCSRA & (1<<RXC)));
	return UDR;
}

ISR(USART_RXC_vect)
{
	unsigned char data = UDR;
	switch (data)
	{
		case 'A':
			if (PINB & (1<<SWITCH1)) 
			{
				FullStep(1);//lewo
				UART_Transmit('G');
			}
			else UART_Transmit('E');
			break;
		case 'B':
			if (PINB & (1<<SWITCH2))
			{
				FullStep(0);//prawo
				UART_Transmit('G');
			}
			else UART_Transmit('E');
			break;
		case 'C':
			if (PINB & (1<<SWITCH1))
			{
				HalfStep(1);
				UART_Transmit('G');
			}
			else UART_Transmit('E');
			break;
		case 'D':
			if (PINB & (1<<SWITCH2))
			{
				HalfStep(0);
				UART_Transmit('G');
			}
			else UART_Transmit('E');
			break;
		default:
			break;
	}
}