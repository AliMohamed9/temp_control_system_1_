/*
 * ADC.h
 *
 *  Created on: Sep 30, 2020
 *      Author: MeGa
 */

#ifndef ADC_H_
#define ADC_H_

#include<avr/io.h>
#include<util/delay.h>

void ADC_init(void);
unsigned int ADC_Get_Reading_mv( unsigned char CH);

#endif /* ADC_H_ */
