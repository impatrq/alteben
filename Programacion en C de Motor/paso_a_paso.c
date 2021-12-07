#define VUELTAS_DEL_MOTOR_M0 PORTB2
#define VUELTAS_DEL_MOTOR_M1 PORTB3
#define VUELTAS_DEL_MOTOR_M2 PORTB4
#define VUELTAS_DEL_MOTOR PORTB4
#define CONTROL_DE_VUELTAS PORTB5
#define DIRECCION_DEL_MOTOR PORTB6
#define HABILITAR_EL_CONTROLADOR PORTB7
#define DDRB 0b00001111
#define F_CPU 16e6
#include <xc.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

void cerrar_valvula(){
 int step = 0;
    while (step<50) {
        PORTB|=(1<<VUELTAS_DEL_MOTOR);
        _delay_ms(100);
        PORTB&= ~(1<<VUELTAS_DEL_MOTOR);
        _delay_ms(100);
        step++;

}
}


   void abrir_valvula(){       
    int step = 0;
    while (step<50) {
        PORTB|=(1<<VUELTAS_DEL_MOTOR);
        _delay_ms(100);
        PORTB&= ~(1<<VUELTAS_DEL_MOTOR);
        _delay_ms(100);
        step++;
    }
}

int main(void) {
   DDRB = 0b11110000;
   PORTB = (1<<DIRECCION_DEL_MOTOR);
   PORTB = (1<<CONTROL_DE_VUELTAS)|(1<<VUELTAS_DEL_MOTOR_M1)|(1<<HABILITAR_EL_CONTROLADOR);
   PORTB&= ~(1<<VUELTAS_DEL_MOTOR_M0)| (1<<VUELTAS_DEL_MOTOR_M2);
  abrir_valvula();
  while (1){
  
  }
}          