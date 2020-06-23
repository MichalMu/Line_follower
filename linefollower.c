#include <avr/io.h>
#include <stdlib.h>
#include "io_cfg.h"
#include "linefollower.h"

int prog = 0;
int tab_czujnikow[2] = {0,0};
int czujniki[2] = {0};

int prev_err = 0, przestrzelony = 0;
int blad = 0, pop_blad = 0, Kp = 1, Kd = 0;
int V_zad = 100;

volatile int petla = 0;

void PWM(int lewy, int prawy)
{
	if(lewy >= 0)
	{
		if(lewy>255)
		lewy = 255;
		ENGINE_12 = 1;
		ENGINE_11 = 0;
	}
	else
	{
		if(lewy<-255)
		lewy = -255;
		ENGINE_12 = 0;
		ENGINE_11 = 1;
	}
	
	if(prawy >= 0)
	{
		if(prawy>255)
		prawy = 255;
		ENGINE_22 = 1;
		ENGINE_21 = 0;
	}
	else
	{
		if(prawy<-255)
		prawy = -255;
		ENGINE_22 = 0;
		ENGINE_21 = 1;
	}
	
	PWML = abs(lewy);
	PWMP = abs(prawy);
}


void kalibracja()
{
	int bialy, czarny;
	
	ADMUX &= 0b11100000;				
	ADMUX |= 1;							
	ADCSRA |= _BV(ADSC);				
	while(ADCSRA & _BV(ADSC)) {};		
	bialy = ADCH;						
	
	ADMUX &= 0b11100000;
	ADMUX |= 2;
	ADCSRA |= _BV(ADSC);
	while(ADCSRA & _BV(ADSC)) {};
	czarny = ADCH;						
	
	prog = bialy + (czarny-bialy)/2;	
}
void czytaj_adc()
{
	for(int i=0; i<2; i++)
	{
		ADMUX &= 0b11100000;			
		ADMUX |= tab_czujnikow[i];		
		ADCSRA |= _BV(ADSC);			
		while(ADCSRA & _BV(ADSC)) {};	
		
		if(ADCH > prog)					
		czujniki[i] = 1;
		else
		czujniki[i] = 0;
	}
}


int licz_blad()
{
	int err = 0;						
	int ilosc = 0;						
	
	int waga = 10;						
	
	if(przestrzelony)					
	waga = 5;
	
	for(int i=0; i<2; i++)
	{
		err += czujniki[i]*(i-3)*waga;	
		ilosc += czujniki[i];
	}
	
	if(ilosc != 0)						
	{
		err /= ilosc;					
		prev_err = err;
	}
	else								
	{
		if(prev_err < -20)				
		{
			err = -40;					
			przestrzelony = 1;			
		}
		else if(prev_err > 20)			
		{
			err = 40;					
			przestrzelony = 2;			
		}
		else
		err = 0;
	}
	
	if(przestrzelony == 1 && err >= 0)	
	przestrzelony = 0;
	else if(przestrzelony == 2 && err <= 0)
	przestrzelony = 0;
	
	return err;
}


int PD()
{
	int rozniczka = blad - pop_blad;
	pop_blad = blad;
	
	return Kp*blad + Kd*rozniczka;
}


void petla_LF()
{
	czytaj_adc();
	blad = licz_blad();
	int regulacja = PD();
	PWM(V_zad + regulacja, V_zad - regulacja);
}