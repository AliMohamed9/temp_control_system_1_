/*
 * KEYPAD.h
 *
 *  Created on: 17 Jul 2020
 *      Author: root
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include<avr/io.h>
#include<util/delay.h>


void key_pad_init(void);
unsigned char key_pad_Scan(void);



#endif /* KEYPAD_H_ */
