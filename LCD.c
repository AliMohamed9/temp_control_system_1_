/*
 * LCD.c
 *
 *  Created on: 17 Jul 2020
 *      Author: root
 */
#include"LCD.h"


void LCD_init(void)
{
	LCD_DATA__DDR |=0xF0;
	LCD_Control_DDR |=(1<<LCD_EN)|(1<<LCD_RS);

	LCD_Control_PORT &=~(1<<LCD_EN);
	_delay_ms(1);

	LCD_Send_CMD(0x33);                //enable 4 bits mode
	_delay_us(100);
	LCD_Send_CMD(0x32);
	_delay_us(100);
	LCD_Send_CMD(0x28);
	_delay_us(100);
	LCD_Send_CMD(0x0e);          //display on cursor on
	_delay_us(100);
	LCD_Send_CMD(0x01);                    //clear LCD
	_delay_us(2000);
	LCD_Send_CMD(0x06);                    // shift cursor right
	_delay_us(100);


}


void LCD_Send_CMD(unsigned char cmd)
{
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(cmd&0xF0);

	LCD_Control_PORT &=~(1<<LCD_RS);

	LCD_Control_PORT |=(1<<LCD_EN);
	_delay_us(1);
	LCD_Control_PORT &=~(1<<LCD_EN);


	_delay_ms(1);


	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(cmd<<4);
	LCD_Control_PORT |=(1<<LCD_EN);
	_delay_us(1);
	LCD_Control_PORT &=~(1<<LCD_EN);


}


void LCD_Send_data(unsigned char data)
{

	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(data&0xF0);
	LCD_Control_PORT |=(1<<LCD_RS);
	LCD_Control_PORT |=(1<<LCD_EN);
	_delay_us(1);
	LCD_Control_PORT &=~(1<<LCD_EN);

	_delay_ms(1);

	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(data<<4);
	LCD_Control_PORT |=(1<<LCD_EN);
	_delay_us(1);
	LCD_Control_PORT &=~(1<<LCD_EN);
	_delay_ms(1);

}


void LCD_Send_string(unsigned char* str)
{

	while(*str!='\0')
	{
		LCD_Send_data(*str++);

	}


}

void LCD_go_to(unsigned char y,unsigned char x)
{

	if(y==1)
	{
		LCD_Send_CMD(0x80+x-1);
	}
	else if(y==2)
	{
		LCD_Send_CMD(0xC0+x-1);
	}
	_delay_ms(1);
}

