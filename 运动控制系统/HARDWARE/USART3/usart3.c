//HC-05的RXD：usart3_txd PC10黑色连openmvrx
//HC-05的TXD：usart3_rxd PC11
//VCC:5v或3.3v
//外接连接板子的串口3
//usart3_init()函数中包含有定时器5的初始化，只用在主函数中usart3_init()即可
//用了基本定时器定时器5作为计时，计时不需要IO口，最好不再用定时器5
//本文件下面还有HC-05的部分函数，若要使用，可以在主函数中HC05_Init()
//还有usart3_detect()函数用于检测串口3接收的信息，并根据信息做相应的程序

#include "delay.h"
#include "led.h"
#include "usart3.h"
#include <stdlib.h>
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	
#include "led.h"
#include "steer.h"


extern int x1;
extern int y1;
extern int x2;
extern int y2;
extern int x3;
extern int y3;
extern int x4;
extern int y4;


void usart3_detect()
{
	u16 t;
	u16 len=0;
	//char data_char[4]={0};
			
	char data_num[10]={0};
	if(USART3_RX_STA&0X8000)			//接收到一次数据了
		{
 			len=USART3_RX_STA&0X7FFF;	//得到数据长度
			USART3_RX_BUF[len]=0;	 	//加入结束符,C语言中字符串数组结束符为\0，而\0的ASCLL码值为0。
										//注意：必须要加结束符，否则只有第一次控制LED才有效果
			u3_printf("\r\n您收到的消息为:\r\n\r\n");

			for(t=2;t<len;t++)
			{
				data_num[t-2]=USART3_RX_BUF[t];
			}
			data_num[len-2]=0;
						
			for(t=0;t<len;t++)
			{
				USART_SendData(USART3, USART3_RX_BUF[t]);//向与串口3的TXD连接的RXD（即上位机可能时通过usb-TTL连的电脑，也可能是通过蓝牙模块连的手机）发送数据
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
			}
			if(len>2)				
			{
				if(strncmp((const char*)USART3_RX_BUF,"xa",2)==0){x1=atoi(data_num);}		
				if(strncmp((const char*)USART3_RX_BUF,"ya",2)==0){y1=atoi(data_num);}	
				if(strncmp((const char*)USART3_RX_BUF,"xb",2)==0){x2=atoi(data_num);}		
				if(strncmp((const char*)USART3_RX_BUF,"yb",2)==0){y2=atoi(data_num);}
				if(strncmp((const char*)USART3_RX_BUF,"xc",2)==0){x3=atoi(data_num);}		
				if(strncmp((const char*)USART3_RX_BUF,"yc",2)==0){y3=atoi(data_num);}	
				if(strncmp((const char*)USART3_RX_BUF,"xd",2)==0){x4=atoi(data_num);}		
				if(strncmp((const char*)USART3_RX_BUF,"yd",2)==0){y4=atoi(data_num);}	
			}
			u3_printf("\r\n\r\n");//插入换行
			USART3_RX_STA=0;	 
		}	
}




//串口发送缓存区 	
__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节
#ifdef USART3_RX_EN   								//如果使能了接收   	  
//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.


//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
u16 USART3_RX_STA=0;   	 
void USART3_IRQHandler(void)
{
	u8 res;	    
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{	 
 
	res =USART_ReceiveData(USART3);		
	if((USART3_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
	{ 
		if(USART3_RX_STA<USART3_MAX_RECV_LEN)		//还可以接收数据
		{
			TIM_SetCounter(TIM5,0);//计数器清空        				 
			if(USART3_RX_STA==0)		
				TIM_Cmd(TIM5, ENABLE);  //使能定时器5 
			USART3_RX_BUF[USART3_RX_STA++]=res;		//记录接收到的值	 
		}else 
		{
			USART3_RX_STA|=1<<15;					//强制标记接收完成
		} 
	}  	
 }										 
}  
#endif	
//初始化IO 串口3
//bound:波特率	  
void usart3_init(u32 bound)
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	USART_DeInit(USART3);  //复位串口3
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOD8和GPIOD9初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10
	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB11复用为USART3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB10复用为USART3	  
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断  
		
	USART_Cmd(USART3, ENABLE);                    //使能串口 
	
 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	TIM5_Int_Init(100-1,8400-1);	//10ms中断一次
	
  TIM_Cmd(TIM5, DISABLE); //关闭定时器5
	
	USART3_RX_STA=0;				//清零 
}

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART3,(uint8_t)USART3_TX_BUF[j]); 	 //发送数据到串口3 
	}
	
}
 
//初始化ATK-HC05模块
//返回值:0,成功;1,失败.

//定时器5中断服务程序		    
void TIM5_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		USART3_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIM5更新中断标志    
		TIM_Cmd(TIM5, DISABLE);  //关闭TIM5
	}	    
}
 
//通用定时器中断初始化
//这里始终选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数		 
void TIM5_Int_Init(u16 arr,u16 psc)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//TIM8时钟使能    
	
	//定时器TIM8初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //使能指定的TIM5中断,允许更新中断
   
	TIM_Cmd(TIM5,ENABLE);//使能定时器5
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;										//TIM5_IRQ没有
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
}
	 

 
 











