#ifndef	_LCD_H
#define _LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define	LCD_PORT	PORTD
#define LCD_DDR		DDRD
#define RS			PD0
#define EN			PD1
#define	D4			PD4
#define D5			PD5
#define D6			PD6
#define D7			PD7

void LCD_Port (char byte);
void LCD_Cmd (char bytel);
void LCD_Clear(void);
void LCD_Set_Cursor (char x, char y);
void LCD_Init(void);
void LCD_PutC(char byte);
void LCD_WriteString (char *string);
void LCD_WriteLong (long int int_);
void LCD_WriteFloat (double double_);

#endif	/* _LCD_H */
