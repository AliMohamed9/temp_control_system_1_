/*
 * main.c
 *
 *  Created on: 11 Jul 2020
 *      Author: root
 */
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
void receive_from_bluthooth(char *store,char len);
#define ADC_code         1
#if ADC_code
#define TEMP 1

int main()
{

	char coming_data[30]={0};
	char turn_off_relay1[30]="turn off cooling\r\n";
	char turn_off_relay2[30]="turn off heating\r\n";
	char turn_on_relay1[30]="turn on cooling\r\n";
	char turn_on_relay2[30]="turn on heating\r\n";
	char stop_buzzer[30]="stop alarm\r\n";

	unsigned 	char x,y,z,a=0;   /// these variable for take temperature from the user and display it
	unsigned int ADC_reading=0;   //// to take the reading from ADC peripheral
	unsigned int reading_in_mv=0;  ////  to hold the reading from ADC peripheral in M V
	unsigned int desired_temp=0;   //// to hold the desired temperature that entered by the user

	unsigned char temp=0;
	init_UART();   ////// initialization  of UART module
	LCD_init();    ////// initialization  of LCD  module
	ADC_init();    ////// initialization  of ADC module
	key_pad_init();   ////// initialization  of KEYPAD  module
	DDRD |=(1<<PD7);
	DDRD |=(1<<PD6);
	DDRD|=(1<<PD4);
	DDRD|=(1<<PD5);

#if TEMP

	if(!(PIND&(1<<PD6)))    /// only display cooling off if relay is turned off
	{
	LCD_go_to(1,9);
	LCD_Send_string("cool off");
	}
	if(!(PIND&(1<<PD7)))
	{
	LCD_go_to(2,9);
	LCD_Send_string("heat off");   //only display heating off if relay is turned off
	}

	LCD_go_to(1,1);
	LCD_Send_string("des");
	while(!( key_pad_Scan()));
	x= key_pad_Scan();      /////  take  the first digit of desired temperature from keypad
	_delay_ms(1000);
	LCD_go_to(1,5);
	LCD_Send_data(x+'0');       /// display display the data that entered by user  in lcd

	_delay_ms(1000);
	while(!( key_pad_Scan()));

	y= key_pad_Scan();        /////// take  the second digit of desired temperature from keypad

	_delay_ms(1000);
	LCD_go_to(1,6);
	LCD_Send_data(y+'0');         /// display the data that entered by user  in lcd
	_delay_ms(1000);


	desired_temp=(x*10)+y;
	LCD_go_to(1,1);
	LCD_Send_string("des");
	z=desired_temp/10;
	LCD_go_to(1,5);
	LCD_Send_data(z+'0');
	a=desired_temp%10;
	LCD_go_to(1,5);
	LCD_Send_data(a+'0');


	LCD_go_to(2,1);
		LCD_Send_string("temp");

		while(1)
			{
		ADC_reading=ADC_Get_Reading_mv(6);    //// getting the actual temperature
		reading_in_mv=ADC_reading*4.88;
		temp=reading_in_mv/10;
		x=temp/10;

	LCD_go_to(2,6);
	LCD_Send_data(x+'0');
    y=  temp%10;
	 LCD_go_to(2,7);
	LCD_Send_data(y+'0');

  ////////   compare  the  temperatures ////////////

	if(desired_temp<=temp)
	{

	PORTD |=(1<<PD7);
	PORTD |=(1<<PD6);
	if(PIND&(1<<PD6))
		{
			    LCD_go_to(1,9);
				LCD_Send_string("cool on.");
				UART_SEND_string("\r\n the actual temperature exceed the desired temperature\r\n ");

		}
	}
	else if(desired_temp>temp)
	{
	PORTD|=(1<<PD4);
	if(PIND&(1<<PD4))
			{
		LCD_go_to(2,9);
			LCD_Send_string("heat on.");
			UART_SEND_string("\r\n the desired temperature bigger than the actual temperature\r\n ");

			}

	}


  //////////// this will display for the user if he used a blutooth terminal app as a help ///////////
	UART_SEND_string("\r\n  turn off cooling  \r\n ");
	UART_SEND_string("\r\n  turn off heating  \r\n ");
	UART_SEND_string("\r\n  turn on cooling   \r\n ");
	UART_SEND_string("\r\n  turn on heating   \r\n ");
	UART_SEND_string("\r\n  stop alarm        \r\n");


	///////////////////   receiving any commands from blutooth   ////////////////////////////

	memset(coming_data,0,50*sizeof(char));  //// to replace every value with 0
	receive_from_bluthooth(coming_data,50);
	if(strcmp(coming_data,turn_off_relay1)==0)   //// stop relay 1
	{
PORTD&=~(1<<PD7);
PORTD&=~(1<<PD6);
LCD_go_to(1,9);
				LCD_Send_string("cool off");      /// display the status of relay 2 on lcd
				_delay_ms(10000);
	}
	else if(strcmp(coming_data,turn_off_relay2)==0)    // stop relay 2
	{
		PORTD&=~(1<<PD4);
		_delay_ms(5000);
		LCD_go_to(2,9);
					LCD_Send_string("heat off");    /// display the status of relay 2 on lcd
					_delay_ms(10000);

	}
	else if(strcmp(coming_data,turn_on_relay1)==0)    /// turn on relay 1
	{
		PORTD |=(1<<PD7);
		 LCD_go_to(1,9);
						LCD_Send_string("cool on.");    /// display the status of relay 1 on lcd
						_delay_ms(10000);
	}
	else if(strcmp(coming_data,turn_on_relay2)==0)     /// turn on relay 2
	{
		PORTD|=(1<<PD4);
		LCD_go_to(2,9);
					LCD_Send_string("heat on.");    /// display the status of relay 2 on lcd
					_delay_ms(10000);

	}
	else if(strcmp(coming_data,stop_buzzer)==0)     ///stop the buzzer
	{
		PORTD &=~(1<<PD6);
	}
	}
#endif
	return 0;
}
#endif
