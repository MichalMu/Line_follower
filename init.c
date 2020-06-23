#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"
#include "io_cfg.h"
void init(){
ENGINE_11_DIR =1;
ENGINE_11 = 0;
ENGINE_12_DIR =1;
ENGINE_12 = 0;
ENGINE_21_DIR = 1;
ENGINE_21 = 0;
ENGINE_22_DIR = 1;
ENGINE_22 = 0;

PWM1_DIR = 1;
PWM1 = 0;
PWM2_DIR =1;
PWM2 = 0;



czujnik1_DIR = 0;
czujnik1 = 1;
czujnik2_DIR = 0;
czujnik2 = 1;




//  TIMER 1 - PWM

TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
TCCR1B = _BV(CS10) | _BV(WGM12);
OCR1A = OCR1B = 0;


//  TIMER 0 - PRZERWANIE CZASOWE

TCCR0A |= _BV(WGM01);
TCCR0B |= _BV(CS02) | _BV(CS00);
OCR0A = 78;
TIMSK0 |= _BV(OCIE0A);


//  ADC

ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADEN);
ADMUX |= _BV(ADLAR) | _BV(REFS0);


//  GLOBALNE PRZERWANIA

sei();
}