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
#include <xc.h>

double presion_atmosferica = 1013.25;
int sensor = 0;
double Vs = 5;
double presion_sensor;
double Vout;
double presion_final;
double altura;


void GPIO_Configuracion()
{
    DDRB = 0xFF;                 
    DDRC = 0b00000011;
	DDRD = 0b00000000;
	PORTD = 0b00000000;

}
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
	
	unsigned int valor_lectura;
  unsigned int canal_elegido = 5;
  GPIO_Configuracion();                   
  ADC_Configuracion();                   

  do
  {
    valor_lectura = ADC_Lectura(canal_elegido);            
    PORTB = valor_lectura;
    PORTC = valor_lectura >> 8;
    _delay_ms(1000);
    canal_elegido = (canal_elegido >=4) ? 2 : (1 + canal_elegido);
  }
  while(1);
  return 0;
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

		presion_sensor= Vout/Vs/0.009 - 0.04;
		presion_final= presion_atmosferica - presion_sensor;
		
		altura = -7999*log(presion_final);
		
		sensor = adc_start();
		
	
		lcd_gotoxy(0,0);
		lcd_puts("Presion= ");
		
		lcd_gotoxy(9,0);
		lcd_data(presion_final);
		
		lcd_gotoxy(12,0);
		lcd_puts("kPa");
		
		lcd_gotoxy(0,5);
		lcd_puts("Altura= ");
		
		lcd_gotoxy(9,5);
		lcd_data(altura);
		
    }
}

