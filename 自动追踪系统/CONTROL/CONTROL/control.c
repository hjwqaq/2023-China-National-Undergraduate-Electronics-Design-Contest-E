//control.h����һЩ�궨��

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


//һЩ�ⲿ����
//extern int decoder_left,decoder_right;     //���ұ��������������
extern float pitch,roll,yaw; 		//ŷ����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;		//������ԭʼ����


//5ms��ʱ�ж���MPU6050��INT���Ŵ���
//�ϸ�֤���������ݴ����ʱ��ͬ��	
/*void EXTI15_10_IRQHandler(void)
{
	static int exti_flag;
	if(INT==0 && exti_flag%100==0)	 	//ʵ����Ϊ5ms*100=500ms��һ��mpu6050����	
	 {  
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}		//����Ҫ�����whileѭ��
		//decoder_left=Read_Encoder(2);		//���A�ı�����
		//decoder_right=Read_Encoder(3);		//���B�ı�����
		OLED_Show();
	 } 
	 exti_flag++;
	EXTI_ClearITPendingBit(EXTI_Line12);//���LINE12�ϵ��жϱ�־λ  
}*/

void EXTI15_10_IRQHandler(void)
{
	//if(stop_key==1)
	//{
	//	while(stop_key!=0){}
	//}
	//usart2_detect();			//openmv�źŽ���	
	//��ͣ���ܣ����°�����ͣ���ɿ�ȡ����ͣ

	EXTI_ClearITPendingBit(EXTI_Line12);//���LINE12�ϵ��жϱ�־λ  
}


//����PID���õ�ת90���180���pwm�仯ֵ�������������Ϊkp��ki��kd��ʵ��ֵ������ֵ
//int turn_pid(float kp,float ki,float kd,float actual_value,float truth_value )
//{
//	float bias;
//	static float bias_add;		//���Ļ�����
//	static float bias_last;		//��һ���жϵ����
//	double bias_d=0;
//	int pwm_pid=0;		//����Ϊint�ͣ������ǿ��ת��Ϊint����
//	bias=truth_value-actual_value;	//����������ֵת90�ȣ���ǰΪ0�ȣ���Ϊ��ֵ
//	bias_add+=bias;				//������
//	bias_d=(bias_last-bias)/(0.005);	//΢�����λΪ��ÿ��
//	pwm_pid=kp*bias+ki*bias_add-kd*bias_d;
//	bias_last=bias;		//������ƫ��ֵ����bias_last��̬����
//	return pwm_pid;
//		//6.���ֻ�û����
//}






//PWM�޷���������������ֱ�Ϊ���޷����롢��С��ֵ������ֵ��min<pwm<max,����ֵΪ�޷����ֵ
//int Limit_Pwm(int IN,int min,int max)
//{	
//	int OUT=IN;
//	if(OUT>max) OUT = max;
//	if(OUT<min) OUT = min;
//	return OUT;
//		   
//}


//�õ��Ƕ�
//int Get_Angle(void)
//{ 
//	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
//	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
//	mpu_dmp_get_data(&pitch,&roll,&yaw);
//}

