/*
 * Line_Follower.c
 *
 * Created: 20.06.2020 20:51:17
 * Author : Micha³ Mucha, Maciej Radym
 */ 

#include <avr/io.h>

void adc_init()
{
	ADMUX = (1<<REFS0); //ADC Multiplexer Slection Register, REFS0 odpowiada nadanie napiêcia odniesienia
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC Control and Status Register A
	//ADEN - ADC Enable
	//ADPS2:0 - ADC Prescaler Select Bits. prescaler zale¿y od ustawienia tych 3 bitów. Gdy wszystkie s¹ ustawione na stan wysoki dzielnik wynosi 128
}

uint16_t adc_read(uint8_t ch)
{
	ch &= 0b00000111;
	ADMUX = (ADMUX & 0xF8)|ch; //ustawienie dolnych 3 bitów na stan niski
	ADCSRA |= (1<<ADSC); //rozpoczêcie konwersji
	while(ADCSRA & (1<<ADSC)); //po skoñczonej konwersji ADSC przyjmuje stan '0'
	return (ADC);
}

int main()
{
	DDRC = 0x00; //ustawienie portu C jako wejœcie
	DDRB = 0xff; //ustawienie portu B jako wyjœcie
	DDRD = 0xff; //ustawienie portu D jako wyjœcie
	PORTB |= (1<<PORTB1); //ustawienie pinu 1 portu B w stan wysoki
	PORTB |= (1<<PORTB2); //ustawienie pinu 2 portu B w stan wysoki. Wyprowadzenia tych pinów pod³¹czone s¹ do L293D zastêpuj¹ sygna³ PWM.
	uint16_t adc_result0, adc_result1;
	adc_init();

	while(1)
	{
		adc_result0 = adc_read(0);      //wywo³anie funkcji odczytu z czujnika i zapisanie wartoœci w zmiennej
		adc_result1 = adc_read(1);      //wywo³anie funkcji odczytu z czujnika i zapisanie wartoœci w zmiennej

		if(adc_result0 > 5 && adc_result1 >5){ //warunek sprawdzaj¹cy czy czujniki wykrywaj¹ liniê, ten przypadek pokrywa stan gdy ¿aden z czujników nie znajduje siê nad lini¹
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
