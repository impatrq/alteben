/*
 * Diaplay.c
 *
 * Created: 30/06/2021 13:54:53
 * Author : User
 */ 
#define F_CPU 4000000UL
#include <avr/io.h>
#include "lcd.h"
#include "adc_atmega_328.h"
#include <stdlib.h>
#include <util/delay.h>



int sensor = 0;
char adc[5];
double Vs = 5;
double P;
double Vout;





int main(void)
{
	DDRD = 0x00000000;
	PORTD = 0x00000000;
	
	adc_referencia(1);
	
	
	adc_iniciar();
	
	
    lcd_init(LCD_DISP_ON);
	lcd_clrscr();
    while (1) 
    {
		adc_canal(0);
		int aux=0;
		for(int i=0;i<10;i++){
			aux=aux + (PINC0 * 5.0/1023.0);
			_delay_ms(5);
		}
		Vout=aux/10.0;

		P= Vout/Vs/0.009 - 0.04;
		
		sensor = adc_start();
		
	
		lcd_gotoxy(0,0);
		lcd_puts("Presion= ");
		
		lcd_gotoxy(9,0);
		lcd_data(P);
		
		lcd_gotoxy(12,0);
		lcd_puts("kPa");
		
		lcd_gotoxy(0,5);
		lcd_puts("Altura= ");
		
		
    }
}

