/*
 * GccApplication1.c
 *
 * Created: 18.06.2020 19:00:11
 * Author : Win10
 */ 
#include "linefollower.h"
#include "io_cfg.h"
#include "init.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{

	init();
	
	while(1)
	{
		if(petla)
		{
			petla = 0;
			petla_LF();
		}
	}
}

ISR(TIMER0_COMPA_vect)			
{
	petla = 1;
}



