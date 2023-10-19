#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


void KEY_Init(void);
u8 KEY_Scan(u8);
u8 click(void);
void Delay_ms(void);
u8 click_N_Double (u8 time);
u8 click_N_Double_MPU6050 (u8 time);
u8 Long_Press(void);


#define KEY			PDin(3) 

#endif 
