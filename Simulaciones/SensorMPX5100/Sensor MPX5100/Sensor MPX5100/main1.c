/*
 * Display.c
 *
 * Created: 30/06/2021 13:54:53
 * Author : Matias Ordo�ez
 */ 
#define F_CPU 4000000UL
#include <avr/io.h>
#include "lcd.h"
#include "adc_atmega_328.h"
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

double presion_atmosferica = 101.325;
int sensor = 0;
double Vs = 5;
double presion_sensor;
double Vout;
double presion_final;
double altura;
char alturaF[8];
char presion_finalF[8];

void ADC_Configuracion()
{
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned int ADC_Lectura(int canal){
	if(canal < 0 || canal > 7){
		return 1;
	}
	canal &= 0x7;
	ADMUX = (ADMUX & 0xF8)|canal;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}



int main(void)
{
	int ADC_val;
	int canal_seleccionado = 0;
	ADC_Configuracion();
	
	
	DDRD = 0b00000000;
	PORTD = 0b00000000;
	DDRC = 0b00000001;
	PORTC = 0b00000001;
	
	
	
	
	
	
    lcd_init(LCD_DISP_ON);
	lcd_clrscr();
    while (1) 
    {
		ADC_val = ADC_Lectura(canal_seleccionado);
		PORTC = ADC_val;
		double aux=0.0;
		for(double i=0;i<10;i++){
			aux=aux + (canal_seleccionado * 5.0/1023.0);
			_delay_ms(5);
		}
		Vout=aux/10.0;

		presion_sensor= Vout/Vs/0.009 - 0.04;
		presion_final= presion_atmosferica - presion_sensor;
		
		altura = (-7999.6527*log(presion_final/101.304))*3.28;
		
		sprintf(presion_finalF, "%0.2f", presion_final);
		sprintf(alturaF, "%0.2f", altura);
		
	
		lcd_gotoxy(0,0);
		lcd_puts("Presion= ");
		
		lcd_gotoxy(9,0);
		lcd_data(presion_final);
		
		lcd_gotoxy(12,0);
		lcd_puts("kPa");
		
		lcd_gotoxy(0,5);
		lcd_puts("Altura= ");
		
		lcd_gotoxy(8,5);
		lcd_data(altura);
		
		lcd_gotoxy(12,5);
		lcd_puts("fts");
		
		
    }
}

