#ifndef __BALANCE_H
#define __BALANCE_H			  	 
#include "sys.h"

void Set_Pwm(int motor_a,int motor_b);
void motorrun(int flag);
void run(void);
void back(void);
void turnleftsmall(void);
void turnleftbig(void);
void turnrightsmall(void);
void turnrightbig(void);
void stop(void);

#endif  

