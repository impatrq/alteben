/*
 * adc_atmega_328.h
 *
 * Created: 27/01/2019 23:20:04
 *  Author: Luis Vásquez
 */ 


#ifndef ADC_ATMEGA_328_H_
#define ADC_ATMEGA_328_H_

void adc_referencia(uint8_t referencia);
void adc_iniciar();
void adc_canal(uint8_t canal);
uint16_t  adc_start();
	

void adc_referencia(uint8_t referencia) {
	switch(referencia) {
	case 0:
	ADMUX &=~ ((1<<REFS1) | (1<<REFS0));
	break;
	
	case 1:
	ADMUX &=~ (1<<REFS1); 
	ADMUX |=  (1<<REFS0);
	break;
	
	case 2:
	ADMUX |= ((1<<REFS1) | (1<<REFS0)); 
	break;
	}
	}
	

void adc_iniciar() {
	ADCSRA |=  (1<<ADEN);
	ADCSRA &=~ (1<<ADLAR);
	ADCSRA &=~ (1<<ADATE);
	if(F_CPU == 1000000UL) {
		ADCSRA |=  ((1<<ADPS1) | (1<<ADPS0));
		ADCSRA &=~ (1<<ADPS2);
	}
	else if(F_CPU == 4000000UL) { 
		ADCSRA |=  ((1<<ADPS2) | (1<<ADPS0));
		ADCSRA &=~ (1<<ADPS1);
	}
	else if(F_CPU == 8000000UL) {
		ADCSRA |=  ((1<<ADPS2) | (1<<ADPS1));
		ADCSRA &=~ (1<<ADPS0);
	}
	else if(F_CPU == 16000000UL) {
		ADCSRA |=  ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));
	}
} 	


void adc_canal(uint8_t canal) {
	switch(canal) {
	case 0:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
	break;	
	
	case 1:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX2) | (1<<MUX1));
	ADMUX |=  (1<<MUX0);
	break;
	
	case 2:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX2) | (1<<MUX0));
	ADMUX |=  (1<<MUX1);
	break;
	
	case 3:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX2));
	ADMUX |=  ((1<<MUX1) | (1<<MUX0));
	break;
	
	case 4:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX1) | (1<<MUX0));
	ADMUX |=  (1<<MUX2);
	break;
	
	case 5:
	ADMUX &=~ ((1<<MUX3) | (1<<MUX1));
	ADMUX |=  ((1<<MUX2) | (1<<MUX0));
	break;
	}
}


uint16_t adc_start() {
	ADCSRA |= (1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return ADCW;
}




#endif /* ADC_ATMEGA_328_H_ */
