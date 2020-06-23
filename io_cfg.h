#ifndef IO_CFG_H
#define IO_CFG_H



#define F_CPU 16000000UL


typedef struct
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt

#define ENGINE_11                REGISTER_BIT(PORTB,1)
#define ENGINE_11_DIR            REGISTER_BIT(DDRB,1)
#define ENGINE_12                REGISTER_BIT(PORTB,0)
#define ENGINE_12_DIR            REGISTER_BIT(DDRB,0)
#define ENGINE_21                REGISTER_BIT(PORTB,4)
#define ENGINE_21_DIR            REGISTER_BIT(DDRB,4)
#define ENGINE_22                REGISTER_BIT(PORTB,5)
#define ENGINE_22_DIR            REGISTER_BIT(DDRB,5)

#define PWM1                REGISTER_BIT(PORTB,2)
#define PWM1_DIR            REGISTER_BIT(DDRB,2)
#define PWM2                REGISTER_BIT(PORTB,3)
#define PWM2_DIR            REGISTER_BIT(DDRB,3)


#define PWMP                OCR1B
#define PWML                OCR2A


#define czujnik1                    REGISTER_BIT(PORTC,0)
#define czujnik1_DIR                REGISTER_BIT(DDRC,0)
#define czujnik1_PIN                REGISTER_BIT(PINC,0)
#define czujnik2                    REGISTER_BIT(PORTC,1)
#define czujnik2_DIR                REGISTER_BIT(DDRC,1)
#define czujnik2_PIN                REGISTER_BIT(PINC,1)


#endif