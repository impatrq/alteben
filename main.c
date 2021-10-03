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
<<<<<<< HEAD:main.c
double presion_final;
double altura;
char alturaF[8];
char presion_finalF[8];
=======
float presion_final;
float altura;
char alturaF;
char presion_finalF;
>>>>>>> a9726fee2b01ea83c3015c45241f0bd94903119c:main1.c

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
<<<<<<< HEAD:main.c
    LCD_Init();
	
=======
    lcd_init(LCD_DISP_ON);
	lcd_clrscr();
>>>>>>> a9726fee2b01ea83c3015c45241f0bd94903119c:main1.c
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
		altura = -7999*log(presion_final);
		//Pasaje de Float a String
<<<<<<< HEAD:main.c
		sprintf(presion_finalF, "%0.2f", presion_final);
		sprintf(alturaF, "%0.2f", altura);
		//Muestreo de valores en LCD
		
		LCD_Clear();
		LCD_WriteString("Presion= ");
		LCD_WriteFloat(presion_final);
		LCD_WriteString("kPa");
		/*
		LCD_Set_Cursor(0, 1);
		LCD_WriteString("Altura= ");
		LCD_WriteFloat(altura);
		*/
		_delay_ms(500);
=======
		sprintf(presion_final, "%0.2f", presion_finalF);
		sprintf(altura, "%0.2f", alturaF);
		//Muestreo de valores en LCD
		lcd_gotoxy(0,0);
		lcd_puts("Presion= ");
		
		lcd_gotoxy(9,0);
		lcd_puts("presion_finalF");
		
		
		lcd_gotoxy(12,0);
		lcd_puts("kPa");
		
		lcd_gotoxy(0,5);
		lcd_puts("Altura= ");
		
		lcd_gotoxy(9,5);
		lcd_puts("alturaF");
		
>>>>>>> a9726fee2b01ea83c3015c45241f0bd94903119c:main1.c
    }
}
