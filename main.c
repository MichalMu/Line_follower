/*
 * Line_Follower.c
 *
 * Created: 20.06.2020 20:51:17
 * Author : Micha� Mucha, Maciej Radym
 */ 

#include <avr/io.h>

void adc_init()
{
	ADMUX = (1<<REFS0); //ADC Multiplexer Slection Register, REFS0 odpowiada nadanie napi�cia odniesienia
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC Control and Status Register A
	//ADEN - ADC Enable
	//ADPS2:0 - ADC Prescaler Select Bits. prescaler zale�y od ustawienia tych 3 bit�w. Gdy wszystkie s� ustawione na stan wysoki dzielnik wynosi 128
}

uint16_t adc_read(uint8_t ch)
{
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xF8)|ch; //ustawienie dolnych 3 bit�w na stan niski
	ADCSRA |= (1<<ADSC); //rozpocz�cie konwersji
	while(ADCSRA & (1<<ADSC)); //po sko�czonej konwersji ADSC przyjmuje stan '0'
	return (ADC);
}

int main()
{
	DDRC = 0x00; //ustawienie portu C jako wej�cie
	DDRB = 0xff; //ustawienie portu B jako wyj�cie
	DDRD = 0xff; //ustawienie portu D jako wyj�cie
	PORTB |= (1<<PORTB1); //ustawienie pinu 1 portu B w stan wysoki
	PORTB |= (1<<PORTB2); //ustawienie pinu 2 portu B w stan wysoki. Wyprowadzenia tych pin�w pod��czone s� do L293D zast�puj� sygna� PWM.
	uint16_t adc_result0, adc_result1;
	adc_init();

	while(1)
	{
		adc_result0 = adc_read(0);      //wywo�anie funkcji odczytu z czujnika i zapisanie warto�ci w zmiennej
		adc_result1 = adc_read(1);      //wywo�anie funkcji odczytu z czujnika i zapisanie warto�ci w zmiennej

		if(adc_result0 > 5 && adc_result1 >5){ //warunek sprawdzaj�cy czy czujniki wykrywaj� lini�, ten przypadek pokrywa stan gdy �aden z czujnik�w nie znajduje si� nad lini�
			PORTD |= (1<<PORTD6); //ustawienie pinu 6 portu D w stan wysoki
			PORTD |= (1<<PORTD4); //ustawienie pinu 4 portu D w stan wysoki
		}
		if(adc_result0 > 5 && adc_result1 < 5){
			PORTD &= ~(1<<PORTD6); ////ustawienie pinu6 portu D w stan niski
			PORTD |= (1<<PORTD4);
		}
		if(adc_result0 < 5 && adc_result1 > 5){
			PORTD &= ~(1<<PORTD4);
			PORTD |= (1<<PORTD6);

		}
		if(adc_result0 < 5 && adc_result1 < 5){
			PORTD &= ~(1<<PORTD4);
			PORTD &= ~(1<<PORTD6);

		}
	}
}
