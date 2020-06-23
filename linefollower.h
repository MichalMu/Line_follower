#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

void PWM(int lewy, int prawy);
void kalibracja();
void czytaj_adc();
int licz_blad();
int PD();
void petla_LF();

extern int prog, tab_czujnikow[2], czujniki[2];
extern int prev_err, przestrzelony;
extern int blad, pop_blad, Kp, Kd;
extern int V_zad;

extern volatile int petla;

#endif
