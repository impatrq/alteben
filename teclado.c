#include <avr/io.h>
#include "keypad.h"
#include <stdint.h>

float cuenta = 0;
int contador = 0;

///////////////////////////////////////  PROGRAMA PRINCIPAL  ////////////////////////////////////////////////

int main(void)
{
	uint8_t key_pressed;
	DDRC = 0xFF;
    
	PORTC = 0;

	keypad_init();
    while (1) 
    {
	    key_pressed = keypad_scan();
	    if(key_pressed !=0)
	    {
            contador = contador + 1;
        }
        int entero = key_pressed - 48;
	    if (entero >= 0 && entero <= 9)
        {
            if(contador == 1)
            {
                cuenta = entero;
            }
            else
            {
                cuenta = cuenta*10 + entero;
            }
        }

        //Monitor Serial
        if (tecla_presionada)
        {
        //tipos de teclas
        switch(tecla_presionada)
        {
            case 'ENTER': 
            printf("Enter \n");
            break;
      
            case 'L':
            printf("Borrar \n");
            cuenta = 0;
            break;
      
            case ',':
            cuenta = cuenta / 10 ;
            break;
        }
        //cambiar printf por como se llame en la libreria del lcd 
        printf("Tecla: ");
        printf(cuenta);
        printf("\n");
        }
        key_pressed = 0;
    }
}
