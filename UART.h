/*
 * UART.h
 *
 * Created: 21.11.2016 14:21:42
 *  Author: caputa
 */ 


#ifndef UART_H_
#define UART_H_

#define BAUD 230400

void uart_230400(void);
void UARTInit(void);

void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);

#endif /* UART_H_ */