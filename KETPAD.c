/*
 * KETPAD.c
 *
 *  Created on: 17 Jul 2020
 *      Author: root
 */
#include"KEYPAD.h"



void key_pad_init(void)
{

	DDRA=0b00000111;      //key_pad_init
	PORTA=0b00111111;



}



unsigned char key_pad_Scan(void)
{

	while(1)
	{
	PORTA |=(1<<PA2);
	PORTA |=(1<<PA1);
	PORTA &=~(1<<PA0);

	if(!(PINA&(1<<PA5)))
	{
		return 1;

	}
	else if(!(PINA&(1<<PA4)))
	{
		return 2;
	}
	else if(!(PINA&(1<<PA3)))
	{
		return 3;
	}


	PORTA |=(1<<PA2);
	PORTA &=~(1<<PA1);
	PORTA |=(1<<PA0);

	if(!(PINA&(1<<PA5)))
	{
		return 4;
	}
	else if(!(PINA&(1<<PA4)))
	{
		return 5;
	}
	else if(!(PINA&(1<<PA3)))
	{
		return 6;
	}


	PORTA &=~(1<<PA2);
	PORTA |=(1<<PA1);
	PORTA |=(1<<PA0);

	if(!(PINA&(1<<PA5)))
	{
		return 7;
	}
	else if(!(PINA&(1<<PA4)))
	{
		return 8;
	}
	else if(!(PINA&(1<<PA3)))
	{
		return 9;
	}

	return 0;

	}
}



