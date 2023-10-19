#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define ZHONGZHI 0 
#define DIFFERENCE 100

void EXTI15_10_IRQHandler(void);
int turn_pid(float kp,float ki,float kd,float actual_value,float truth_value );
int Limit_Pwm(int IN,int min,int max);
#endif
