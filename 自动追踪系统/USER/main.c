//swd���أ����⵽��3.3v,CLK,GND,DIO
//��ͣ����ΪPD3
//steer1Ϊ�϶��������ΪPB15
//steer2Ϊ�¶��������ΪPE14
//������������ΪPB8


#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	

#include "led.h"
#include "key.h"
#include "steer.h"
#include "motor.h"
#include "usart3.h"
#include "extix.h"

//int count;




int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);				//��ʼ����ʱ����
	
	LED_Init();						//��ʼ��LED
	BEEP_Init();					//��ʼ��beep
	KEY_Init();		
	//��ʼ��KEY
	TIM1_PWM_Init(20000-1,84-1);
	steer_Init(20000-1,84-1);		//�����ʼ��

	usart3_init(9600);				//����3������openmvͨѶ��������19200,��TIM5
 	//OLED_Init();					//��ʼ��OLED
	
	//MPU_Init();						//��ʼ��MPU6050
	//mpu_dmp_init();					//DMP��ʼ��
	//EXTIX_Init();					//MPU6050��INT���ⲿ�жϳ�ʼ��

	//�����ʼλ�ã���Ҫ�����ܣ��Ǿ͵������ʱ����ʹ��Ϊ50-250
	steer1=1600;		//steer1Ϊ����Ķ����Ϊ100ʱΪ��ֱ���ϣ�Ϊ160ʱΪˮƽ��ǰ��Խ�������ת��500��2500
	steer2=1900;		//steer2Ϊ����Ķ����Ϊ160ʱΪ����Խ�������ת��50��250
	delay_ms(500);
	//steer_run();
  while(1)
{
	if(KEY==0)
	{
		while(KEY!=1){}
	}
	usart3_detect();			//openmv�źŽ���
	//delay_ms(20);

	//count++;
	//if(count%10==0) LED=~LED;
}
}


