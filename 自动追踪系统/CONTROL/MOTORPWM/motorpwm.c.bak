//小车姿态控制
//Set_Pwm(int motor_a,int motor_b)可以PWM赋值
//motorrun(int flag)可以根据flag的取值来进行小车姿态控制
//	flag为0：直走	1：左小转		2：左大转	3：右小转	4右大转
//		  5：左转90度	6：右转90度		7：调头，转180度			8:停

#include "stm32f4xx.h"
#include "motorpwm.h"
#include "motor.h"
#include "delay.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

extern float pitch,roll,yaw; 		//欧拉角


//PWM赋值函数，入口参数分别为电机a的pwm，电机b的pwm，pwm取值为0-16799
//pwm可以为正值或负值，正值正转
void Set_Pwm(int motor_a,int motor_b)
{
	if(motor_a<0)			PWMA1=16799,PWMA2=16799+motor_a;
	else 	            PWMA2=16799,PWMA1=16799-motor_a;

	if(motor_b<0)			PWMB1=16799,PWMB2=16799+motor_b;
	else 	            PWMB2=16799,PWMB1=16799-motor_b;

}


//小车
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
					while((yaw<=yaw_begin+90 && yaw>=yaw_begin-10 )|| yaw<=yaw_begin+90-360)	//10是为了防止抖动不在while范围内
					{
						turnleftbig();
						mpu_dmp_get_data(&pitch,&roll,&yaw);
					}
					break;	//不能直接if，没有break会执行下面
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
			default:delay_ms(4);stop();delay_ms(5000);break;	//还要加个变量，让其不动
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

