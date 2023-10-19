//С����̬����
//Set_Pwm(int motor_a,int motor_b)����PWM��ֵ
//motorrun(int flag)���Ը���flag��ȡֵ������С����̬����
//	flagΪ0��ֱ��	1����Сת		2�����ת	3����Сת	4�Ҵ�ת
//		  5����ת90��	6����ת90��		7����ͷ��ת180��			8:ͣ

#include "stm32f4xx.h"
#include "motorpwm.h"
#include "motor.h"
#include "delay.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

extern float pitch,roll,yaw; 		//ŷ����


//PWM��ֵ��������ڲ����ֱ�Ϊ���a��pwm�����b��pwm��pwmȡֵΪ0-16799
//pwm����Ϊ��ֵ��ֵ����ֵ��ת
void Set_Pwm(int motor_a,int motor_b)
{
	if(motor_a<0)			PWMA1=16799,PWMA2=16799+motor_a;
	else 	            PWMA2=16799,PWMA1=16799-motor_a;

	if(motor_b<0)			PWMB1=16799,PWMB2=16799+motor_b;
	else 	            PWMB2=16799,PWMB1=16799-motor_b;

}


//С��
void motorrun(int flag)
{
	int yaw_begin=0;
	 switch(flag)
		{
			
			case 0:run();break;
			case 1:turnleftsmall();break;
			case 2:turnleftbig();break;
			case 3:turnrightsmall();break;
			case 4:turnrightbig();break;
			case 5:yaw_begin=yaw;
					while((yaw<=yaw_begin+90 && yaw>=yaw_begin-10 )|| yaw<=yaw_begin+90-360)	//10��Ϊ�˷�ֹ��������while��Χ��
					{
						turnleftbig();
						mpu_dmp_get_data(&pitch,&roll,&yaw);
					}
					break;	//����ֱ��if��û��break��ִ������
			case 6:yaw_begin=yaw;
					while( (yaw>=yaw_begin-90 && yaw<=yaw+10 ) || yaw>=yaw_begin-90+360) 
					{
						turnrightbig();
						mpu_dmp_get_data(&pitch,&roll,&yaw);
					}
					break;
			case 7:yaw_begin=yaw;
					while((yaw<=yaw_begin+180 && yaw>=yaw_begin-10) || yaw<=yaw_begin+180-360)
					{
					turnleftbig();
					mpu_dmp_get_data(&pitch,&roll,&yaw);
					}
					break;
			default:delay_ms(4);stop();delay_ms(5000);break;	//��Ҫ�Ӹ����������䲻��
		}
	
}



void run()
{
	Set_Pwm(5000,5000);
 }

 
 void back()
{
	Set_Pwm(-3000,-3000);
 }

 
  void turnleftsmall()
{
	Set_Pwm(1000,5000);
 }

   void turnleftbig()
{
	Set_Pwm(-2000,5000);
 }

   void turnrightsmall()
{
	Set_Pwm(5000,1000);
 }

   void turnrightbig()
{
	Set_Pwm(5000,-2000);
 }
 
   void stop()
{
	Set_Pwm(0,0);	
}

