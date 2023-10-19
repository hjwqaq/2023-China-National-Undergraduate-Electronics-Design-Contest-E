//swd下载，从外到内3.3v,CLK,GND,DIO



#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	

#include "led.h"
#include "key.h"
#include "steer.h"
#include "motor.h"
#include "encoder.h"
#include "usart2.h"
#include "usart3.h"
#include "oled.h"
#include "extix.h"
#include "xunji.h"
#include "motorpwm.h"

#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
int decoder_left,decoder_right;
int flag;
float pitch,roll,yaw; 				//欧拉角
short aacx,aacy,aacz;				//加速度传感器原始数据
short gyrox,gyroy,gyroz;			//陀螺仪原始数据



int x1=0;
int y1=0;
int x2=0;
int y2=0;
int x3=0;
int y3=0;
int x4=0;
int y4=0;

int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);				//初始化延时函数
	uart_init(115200);				//串口1用于与电脑通信，波特率115200
	xunji_Init();
	LED_Init();						//初始化LED
	BEEP_Init();					//初始化beep
	KEY_Init();						//初始化KEY
	steer_Init(20000-1,84-1);		//舵机初始化
	Enable_Pin();					//电机使能开关初始化
	usart2_init(9600);				//串口2用于与手机蓝牙通信，波特率9600
	usart3_init(19200);				//串口3用于与openmv通讯，波特率19200,用TIM5
 	OLED_Init();					//初始化OLED
	
	MPU_Init();						//初始化MPU6050
	mpu_dmp_init();					//DMP初始化
	EXTIX_Init();					//MPU6050的INT的外部中断初始化

	//舵机初始位置，需要更精密，那就调舵机定时器，使得为500-2500
	//steery=1142;		//steer1为上面的舵机，，为140时为水平向前，越大就向下转，50—250
	//steerx=963;		//steer2为下面的舵机，为110时为正，越大就向左转，50—250
	//delay_ms(500);
  while(1)
{

	if((cgq4==1)&&(cgq5==0))	//中间按下，右边松开，基本要求（2）
	{
		steery=1291;
		steerx=1100;
		delay_ms(500);
		steer_run(967,1145,1238,1440);
	}
	if((cgq4==0)&&(cgq5==1))	//中间松开，右边按下，基本要求（3）
	{
		steery=1291;
		steerx=1100;
		delay_ms(500);
		steer_run(967,1145,1066,1310);
	}
	if((cgq4==1)&&(cgq5==1))  //中间右边都按下，基本要求（4）
	{
		steery=1291;steerx=1100;delay_ms(500);
		if(x1!=0&&y1!=0&&x2!=0&&y2!=0&&x3!=0&&y3!=0&&x4!=0&&y4!=0)	{	steer_run1(x1,y1,x2,y2,x3,y3,x4,y4);	}			//保证坐标信息都接收到了，才开始运动
		//steer_run1(965,1135,965,1450,1280,1450,1280,1135);
	}
	if((cgq4==0)&&(cgq5==0)) {}		
}
}

