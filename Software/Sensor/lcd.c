#include "LCD.h"

void LCD_Port (char byte) {

	if(byte & 1)
		LCD_PORT |= 1 << D4;
	else
		LCD_PORT &= ~(1 << D4);

	if(byte & 2)
		LCD_PORT |= 1 << D5;
	else
		LCD_PORT &= ~(1 << D5);

	if(byte & 4)
		LCD_PORT |= 1 << D6;
	else
		LCD_PORT &= ~(1 << D6);

	if(byte & 8)
		LCD_PORT |= 1 << D7;
	else
		LCD_PORT &= ~(1 << D7);
}

void LCD_Cmd (char byte) {

	LCD_PORT &= ~(1 << RS);             
	LCD_Port(byte);
	LCD_PORT |= 1 << EN;           
    _delay_ms(4);
    LCD_PORT &= ~(1 << EN);
}

void LCD_Clear (void) {

	LCD_Cmd(0);
	LCD_Cmd(1);
	_delay_ms(2);
}

void LCD_Set_Cursor (char x, char y) {

	char aux, high, low;
	if(y == 0) {
		aux = 0x40 + x;
		high = aux >> 4;
		low = aux & 0x0F;
		LCD_Cmd(high);
		LCD_Cmd(low);
	}
	else if (y == 1) {
		aux = 0xC0 + x;
		high = aux >> 4;
		low = aux & 0x0F;
		LCD_Cmd(high);
		LCD_Cmd(low);
	}
}

void LCD_Init (void) {

	LCD_DDR |= 1 << RS | 1 << EN | 1 << D4 | 1 << D5 | 1 << D6 | 1 << D7;
  	LCD_Port(0x00);
	_delay_ms(20);
  	LCD_Cmd(0x03);
	_delay_ms(5);
  	LCD_Cmd(0x03);
	_delay_ms(11);
  	LCD_Cmd(0x03);
  	LCD_Cmd(0x02);
  	LCD_Cmd(0x02);
  	LCD_Cmd(0x08);
  	LCD_Cmd(0x00);
  	LCD_Cmd(0x0C);
  	LCD_Cmd(0x00);
  	LCD_Cmd(0x06);
}

void LCD_PutC (char byte) {

   char nibbleL, nibbleH;

   nibbleL = byte & 0x0F;
   nibbleH = byte & 0xF0;
   LCD_PORT |= 1 << RS;            				
   LCD_Port(nibbleH>>4);      	//Transfer high nibble
   LCD_PORT |= 1 << EN;
   _delay_us(40);
   LCD_PORT &= ~(1 << EN);
   LCD_Port(nibbleL);				//Transfer lower nibble
   LCD_PORT |= 1 << EN;
   _delay_us(40);
   LCD_PORT &= ~(1 << EN);
}

void LCD_WriteString (char *string) {
	
	char index;
	for(index=0; string[index]!='\0'; index++)
		LCD_PutC(string[index]);
}

void LCD_WriteLong (long int int_) {

	char word[20];
	ltoa(int_,word,10);
	LCD_WriteString(word);
}

void LCD_WriteFloat (double double_) {

	char word[20];
	dtostrf(double_,6,2,word);
	LCD_WriteString(word);
}