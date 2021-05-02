/*
 * LCD.h
 *
 *  Created on: 17 Jul 2020
 *      Author: root
 */

#ifndef LCD_H_
#define LCD_H_

#include<avr/io.h>
#include<util/delay.h>

#define  LCD_DATA_PORT      PORTB
#define  LCD_DATA__DDR      DDRB
#define  LCD_Control_PORT   PORTC
#define  LCD_Control_DDR    DDRC
#define  LCD_RS               6
#define  LCD_EN               7

void LCD_init(void);
void LCD_Send_CMD(unsigned char cmd);
void LCD_Send_data(unsigned char data);
void LCD_Send_string(unsigned char* str);
void LCD_go_to(unsigned char y,unsigned char x);

#endif /* LCD_H_ */
