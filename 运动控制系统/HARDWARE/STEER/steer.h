#ifndef _STEER_H
#define _STEER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#define steerx 	  TIM12->CCR1
#define steery 	  TIM12->CCR2


void steer_Init(u32 arr,u32 psc);
void steer_run(int x_max,int y_max,int x_min,int y_min);
void steer_run1(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4);
#endif
