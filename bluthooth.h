/*
 * bluthooth.h
 *
 *  Created on: Sep 30, 2020
 *      Author: MeGa
 */

#ifndef BLUTHOOTH_H_
#define BLUTHOOTH_H_

#include<avr/io.h>
#include<util/delay.h>

void  receive_from_bluthooth(char *store,char length_array);

#endif /* BLUTHOOTH_H_ */
