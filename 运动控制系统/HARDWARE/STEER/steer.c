//二维云台下面舵机控制端白线：steer1，TIM12的CH2用于PWM，引脚为PB15
//二维云台上面舵机控制端白线：steer2，TIM12的CH1用于PWM，引脚为PB14
//舵机的红线为VCC：一般为5v-8.4v，黑线为GND
//控制舵机需要周期为20ms的PWM，高电平脉宽0.5ms-2.5ms对应舵机转动角度
//改steer_run()函数用于控制舵机的运动
//初始化有steer_Init(u32 arr,u32 psc)

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




//TIM12 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void steer_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12); //GPIOB15复用为定时器12
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOB14复用为定时器12
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;           //GPIOB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB15
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//初始化定时器12
	
	//初始化TIM12 Channe2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //根据T指定的参数初始化外设
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);  //根据T指定的参数初始化外设

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);  //使能TIM12在CCR2上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM12, ENABLE);  //使能TIM12
 
										  
}  


