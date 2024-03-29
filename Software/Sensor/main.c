/*
 * Display.c
 *
 * Created: 30/06/2021 13:54:53
 * Author : Matias Ordo�ez
 */ 
#include <avr/io.h>
#include "lcd.h"
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>

//definicion de variables
double presion_atmosferica = 1013.25;
int sensor = 0;
double Vs = 5;
double presion_sensor;
double Vout;
double presion_final;
double altura;
char alturaF[8];
char presion_finalF[8];

//---------------------------------------------------------------PROGRAMA-----------------------------------------------------------------------

//Configuracion del ADC
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

//---------------------------------------------------------------MAIN---------------------------------------------------------------------------

//Funcion principal
int main(void)
{
	int ADC_val;
	int canal_seleccionado = 0;
	ADC_Configuracion();
	
	//Puertos de conexion
	DDRD = 0b00000000;
	PORTD = 0b00000000;
	DDRC = 0b00000001;
	PORTC = 0b00000001;
	
	
	
	
	
	//iniciamos LCD
    LCD_Init();
	
    while (1) 
    {
		//Seleccion del canal
		ADC_val = ADC_Lectura(canal_seleccionado);
		PORTC = ADC_val;
		//Pasaje de ADC a un valor en Voltaje
		int aux=0;
		for(int i=0;i<10;i++){
			aux=aux + (canal_seleccionado * 5.0/1023.0);
			_delay_ms(5);
		}
		Vout=aux/10.0;
		//Calculos de presion 
		presion_sensor= Vout/Vs/0.009 - 0.04;
		presion_final= presion_atmosferica - presion_sensor;
		//Definicion de altura
		altura = (-7999.6527*log(presion_final/101.304))*3.28;
		//Pasaje de Float a String
		sprintf(presion_finalF, "%0.2f", presion_final);
		sprintf(alturaF, "%0.2f", altura);
		//Muestreo de valores en LCD
		
		LCD_Clear();
		LCD_WriteString("Presion= ");
		LCD_WriteFloat(presion_final);
		LCD_WriteString("kPa");
		
		LCD_Set_Cursor(0, 1);
		LCD_WriteString("Altura= ");
		LCD_WriteFloat(altura);
		
		_delay_ms(500);
    }
}

