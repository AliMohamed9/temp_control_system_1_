/*
 * ADC.c
 *
 *  Created on: Sep 30, 2020
 *      Author: MeGa
 */
#include "ADC.h"

void ADC_init(void)
{

	ADMUX=0b01000000;
	ADCSRA=0b10000111;
}

unsigned int ADC_Get_Reading_mv(unsigned char CH)
{
	ADCSRA |=(1<<ADIF);


	ADMUX=((ADMUX&0xF8)|CH);
	ADCSRA |=(1<<ADSC);


	while(!(ADCSRA&(1<<ADIF)));

	return ADC;
}
