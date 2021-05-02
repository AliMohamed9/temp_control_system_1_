/*
 * bluthooth.c
 *
 *  Created on: Sep 30, 2020
 *      Author: MeGa
 */
#include "bluthooth.h"
void  receive_from_bluthooth(char *store,char length_array)
{
	unsigned char i=0;
	while(length_array>0)
	{

		store[i]= UART_getChar();

		if((store[i-1]==0x0D)&&(store[i]==0x0A))
		{
			break;
		}
		i++;
		length_array--;

	}

}



