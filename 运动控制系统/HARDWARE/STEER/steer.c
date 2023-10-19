//��ά��̨���������ƶ˰��ߣ�steer1��TIM12��CH2����PWM������ΪPB15
//��ά��̨���������ƶ˰��ߣ�steer2��TIM12��CH1����PWM������ΪPB14
//����ĺ���ΪVCC��һ��Ϊ5v-8.4v������ΪGND
//���ƶ����Ҫ����Ϊ20ms��PWM���ߵ�ƽ����0.5ms-2.5ms��Ӧ���ת���Ƕ�
//��steer_run()�������ڿ��ƶ�����˶�
//��ʼ����steer_Init(u32 arr,u32 psc)

#include "steer.h"
#include "led.h"
#include "usart.h"
#include "delay.h"

void steer_run(int x_max,int y_max,int x_min,int y_min)
{
	int t;
	steerx=x_max;
	steery=y_max;
	delay_ms(2000);
	for(t=y_max;t<=y_min+12;t++)
	{
	steery=t;
	delay_ms(10);
	}
	for(t=x_max;t<=x_min+10;t++)
	{
	steerx=t;
	delay_ms(10);
	}	
	for(t=y_min+12;t>=y_max-20;t--)
	{
	steery=t;
	delay_ms(10);
	}	
	for(t=x_min+10;t>=x_max-10;t=t-1)
	{
	steerx=t;
	delay_ms(10);
	if((t<x_max+40)&&(t>x_max-10)&&(t%2==0))	steery=steery+2;
	}
	while(1)
	{}
}


void steer_run1(int x_1,int y_1,int x_2,int y_2,int x_3,int y_3,int x_4,int y_4)
{
	int t;
	steerx=x_1-15;
	steery=y_1-15;
	delay_ms(2000);
	if(y_2>=y_1)
	{
		y_2=y_2-20;
		for(t=y_1;t<=y_2;t=t+2)
		{
		steerx=(int)(x_1+(x_2-x_1)*(t-y_1)/(y_2-y_1));
		delay_ms(10);
		steery=t;
		delay_ms(10);
		}
	}else{
		y_2=y_2+20;
		for(t=y_1;t>=y_2;t=t-2)
		{
		steerx=(int)(x_1+(x_2-x_1)*(t-y_1)/(y_2-y_1));
		delay_ms(10);
		steery=t;
		delay_ms(10);
		}
	}
	steerx=x_2;
	steery=y_2;
	
	if(x_3>=x_2)
	{
		x_3=x_3-10;
		for(t=x_2;t<=x_3;t=t+1)
		{
		steery=(int)(y_2+(y_3-y_2)*(t-x_2)/(x_3-x_2));
		//delay_ms(10);
		steerx=t;
		delay_ms(10);
		}
	}else{
				x_3=x_3+10;
		for(t=x_2;t>=x_3;t=t-1)
		{
		steery=(int)(y_2+(y_3-y_2)*(t-x_2)/(x_3-x_2));
		//delay_ms(10);
		steerx=t;
		delay_ms(10);
		}				
	}	
	
		steerx=x_3;
	steery=y_3;
	if(y_3>=y_4)
	{
		y_4=y_4-35;
		for(t=y_3;t>=y_4;t=t-1)
		{
		steerx=(int)(x_3+(x_4-x_3)*(t-y_3)/(y_4-y_3));
		//delay_ms(10);
		steery=t;
		delay_ms(10);
		}	
	}else{
				y_4=y_4+35;
		for(t=y_3;t<=y_4;t=t+1)
		{
		steerx=(int)(x_3+(x_4-x_3)*(t-y_3)/(y_4-y_3));
		//delay_ms(10);
		steery=t;
		delay_ms(10);
		}			
	}
	
			steerx=x_4;
	steery=y_4;
	if(x_4>=x_1)
	{
		x_1=x_1-16;
		for(t=x_4;t>=x_1;t=t-1)
		{
		steery=(int)(y_4+(y_1-y_4)*(t-x_4)/(x_1-x_4));
		//delay_ms(10);
		steerx=t;
		delay_ms(10);
		}
	}else{
				x_1=x_1+16;
		for(t=x_4;t<=x_1;t=t+1)
		{
		steery=(int)(y_4+(y_1-y_4)*(t-x_4)/(x_1-x_4));
		//delay_ms(10);
		steerx=t;
		delay_ms(10);
		}		
	}
	steerx=x_1;
	steery=y_1-15;
	while(1)
	{}
}




//TIM12 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void steer_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12); //GPIOB15����Ϊ��ʱ��12
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOB14����Ϊ��ʱ��12
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;           //GPIOB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB15
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//��ʼ����ʱ��12
	
	//��ʼ��TIM12 Channe2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR2�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM12, ENABLE);  //ʹ��TIM12
 
										  
}  


