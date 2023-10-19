//swd���أ����⵽��3.3v,CLK,GND,DIO



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
float pitch,roll,yaw; 				//ŷ����
short aacx,aacy,aacz;				//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;			//������ԭʼ����



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
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);				//��ʼ����ʱ����
	uart_init(115200);				//����1���������ͨ�ţ�������115200
	xunji_Init();
	LED_Init();						//��ʼ��LED
	BEEP_Init();					//��ʼ��beep
	KEY_Init();						//��ʼ��KEY
	steer_Init(20000-1,84-1);		//�����ʼ��
	Enable_Pin();					//���ʹ�ܿ��س�ʼ��
	usart2_init(9600);				//����2�������ֻ�����ͨ�ţ�������9600
	usart3_init(19200);				//����3������openmvͨѶ��������19200,��TIM5
 	OLED_Init();					//��ʼ��OLED
	
	MPU_Init();						//��ʼ��MPU6050
	mpu_dmp_init();					//DMP��ʼ��
	EXTIX_Init();					//MPU6050��INT���ⲿ�жϳ�ʼ��

	//�����ʼλ�ã���Ҫ�����ܣ��Ǿ͵������ʱ����ʹ��Ϊ500-2500
	//steery=1142;		//steer1Ϊ����Ķ������Ϊ140ʱΪˮƽ��ǰ��Խ�������ת��50��250
	//steerx=963;		//steer2Ϊ����Ķ����Ϊ110ʱΪ����Խ�������ת��50��250
	//delay_ms(500);
  while(1)
{

	if((cgq4==1)&&(cgq5==0))	//�м䰴�£��ұ��ɿ�������Ҫ��2��
	{
		steery=1291;
		steerx=1100;
		delay_ms(500);
		steer_run(967,1145,1238,1440);
	}
	if((cgq4==0)&&(cgq5==1))	//�м��ɿ����ұ߰��£�����Ҫ��3��
	{
		steery=1291;
		steerx=1100;
		delay_ms(500);
		steer_run(967,1145,1066,1310);
	}
	if((cgq4==1)&&(cgq5==1))  //�м��ұ߶����£�����Ҫ��4��
	{
		steery=1291;steerx=1100;delay_ms(500);
		if(x1!=0&&y1!=0&&x2!=0&&y2!=0&&x3!=0&&y3!=0&&x4!=0&&y4!=0)	{	steer_run1(x1,y1,x2,y2,x3,y3,x4,y4);	}			//��֤������Ϣ�����յ��ˣ��ſ�ʼ�˶�
		//steer_run1(965,1135,965,1450,1280,1450,1280,1135);
	}
	if((cgq4==0)&&(cgq5==0)) {}		
}
}

