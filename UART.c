/*
 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Nmr
 */
#include <avr/io.h>
#include "UART.h"
#include<stdlib.h>




void init_UART(void)
{
	unsigned int Value_of_UBBR = 0;



	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
	Value_of_UBBR = FOSC/16/BAUD-1;
	UBRRL = (unsigned int)Value_of_UBBR;
	UBRRH = (unsigned int)(Value_of_UBBR>>8);
}


void UART_SendChar(char data)
{
	while (!( UCSRA & (1<<UDRE))) ;

	UDR = data;
}


char UART_getChar(void)
{
	while (!(UCSRA & (1<<RXC)));

	return UDR;
}


void UART_SEND_string(char *array)
{

	while(*array !='\0')
	{

		UART_SendChar(*array++);

	}

}




