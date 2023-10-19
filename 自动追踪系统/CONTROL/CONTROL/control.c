//control.h中有一些宏定义

#include "control.h"	
#include "extix.h"
#include "motor.h"
#include "motorpwm.h"
#include "oled.h"
#include "key.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "xunji.h"
#include "delay.h"
#include "usart2.h"


//一些外部变量
//extern int decoder_left,decoder_right;     //左右编码器的脉冲计数
extern float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;		//陀螺仪原始数据


//5ms定时中断由MPU6050的INT引脚触发
//严格保证采样和数据处理的时间同步	
/*void EXTI15_10_IRQHandler(void)
{
	static int exti_flag;
	if(INT==0 && exti_flag%100==0)	 	//实际上为5ms*100=500ms读一次mpu6050数据	
	 {  
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}		//必须要加这个while循环
		//decoder_left=Read_Encoder(2);		//电机A的编码器
		//decoder_right=Read_Encoder(3);		//电机B的编码器
		OLED_Show();
	 } 
	 exti_flag++;
	EXTI_ClearITPendingBit(EXTI_Line12);//清除LINE12上的中断标志位  
}*/

void EXTI15_10_IRQHandler(void)
{
	//if(stop_key==1)
	//{
	//	while(stop_key!=0){}
	//}
	//usart2_detect();			//openmv信号接收	
	//暂停功能，按下按键暂停，松开取消暂停

	EXTI_ClearITPendingBit(EXTI_Line12);//清除LINE12上的中断标志位  
}


//计算PID，得到转90°和180°的pwm变化值，输入参数依次为kp，ki，kd，实际值，期望值
//int turn_pid(float kp,float ki,float kd,float actual_value,float truth_value )
//{
//	float bias;
//	static float bias_add;		//误差的积分项
//	static float bias_last;		//上一次中断的误差
//	double bias_d=0;
//	int pwm_pid=0;		//定义为int型，过会会强制转换为int返回
//	bias=truth_value-actual_value;	//误差，如期望真值转90度，当前为0度，则为正值
//	bias_add+=bias;				//积分项
//	bias_d=(bias_last-bias)/(0.005);	//微分项，单位为度每秒
//	pwm_pid=kp*bias+ki*bias_add-kd*bias_d;
//	bias_last=bias;		//将本次偏差值赋给bias_last静态变量
//	return pwm_pid;
//		//6.积分还没清零
//}






//PWM限幅函数，输入参数分别为待限幅输入、最小幅值、最大幅值，min<pwm<max,返回值为限幅后的值
//int Limit_Pwm(int IN,int min,int max)
//{	
//	int OUT=IN;
//	if(OUT>max) OUT = max;
//	if(OUT<min) OUT = min;
//	return OUT;
//		   
//}


//得到角度
//int Get_Angle(void)
//{ 
//	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
//	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
//	mpu_dmp_get_data(&pitch,&roll,&yaw);
//}

