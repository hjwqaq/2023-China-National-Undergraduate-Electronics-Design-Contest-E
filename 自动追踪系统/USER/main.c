//swd下载，从外到内3.3v,CLK,GND,DIO
//暂停引脚为PD3
//steer1为上舵机，引脚为PB15
//steer2为下舵机，引脚为PE14
//蜂鸣器，引脚为PB8


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
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);				//初始化延时函数
	
	LED_Init();						//初始化LED
	BEEP_Init();					//初始化beep
	KEY_Init();		
	//初始化KEY
	TIM1_PWM_Init(20000-1,84-1);
	steer_Init(20000-1,84-1);		//舵机初始化

	usart3_init(9600);				//串口3用于与openmv通讯，波特率19200,用TIM5
 	//OLED_Init();					//初始化OLED
	
	//MPU_Init();						//初始化MPU6050
	//mpu_dmp_init();					//DMP初始化
	//EXTIX_Init();					//MPU6050的INT的外部中断初始化

	//舵机初始位置，需要更精密，那就调舵机定时器，使得为50-250
	steer1=1600;		//steer1为上面的舵机，为100时为竖直向上，为160时为水平向前，越大就向下转，500—2500
	steer2=1900;		//steer2为下面的舵机，为160时为正，越大就向左转，50—250
	delay_ms(500);
	//steer_run();
  while(1)
{
	if(KEY==0)
	{
		while(KEY!=1){}
	}
	usart3_detect();			//openmv信号接收
	//delay_ms(20);

	//count++;
	//if(count%10==0) LED=~LED;
}
}


