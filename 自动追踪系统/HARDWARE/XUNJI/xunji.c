//5路循迹
//cgq1 PA13	 cgq2 PA2	cgq3 PA3	cgq4 PA6	cgq5 PA7
//xunji_detect可以检测，返回值为对应姿态
//返回0：直走	1：左小转		2：左大转	3：右小转	4右大转
//5：左转90度	6：右转90度		7：调头，转180度			8:停
//可在xunji_detect中调整第几条黑线转

//要xunji_Init()初始化光电对管IO口
//要根据具体的题目要求改blackleft，blackright，blackall的判断

#include "xunji.h"
#include "delay.h"

void xunji_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13; //KEY对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOB14	

}

 
 //三、去A区函数
 int xunji_detect()
 {
	static int a;
	static int b;
	static int c;
	static int blackleft;
	static int blackright;
	static int blackall;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //11011 直走
		return 0;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //11111 抖动
		return 0;	//可能要写个抖动的
	 
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //10011 左小转弯
		return 1;
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //10111 左小转弯
		return 1;
	  
	 if((cgq1==black)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //01111 左大转弯
		return 2;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //11001 右小转弯
		return 3;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //11101 右小转弯
		return 3;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==black)) //11110 右大转弯
		return 4;
	 	 
		if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //00011  左大转弯
	  {
		  blackleft++;
		  delay_us(xian_delay);
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //00111  左大转弯
	  {
		   blackleft++;
		  delay_us(xian_delay);
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //00111  左大转弯
	  {
		   blackleft++;
		  delay_us(xian_delay);
	  }
	  		if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //00011  左大转弯
	  {
		  blackleft++;
		  delay_us(xian_delay);
	  }

	  
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)) //11100 右大转弯
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //11000 
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	  	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)) //11100 右大转弯
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //11000 
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	  
	if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //00000,计数
		{
		blackall++;
		delay_us(xian_delay);//延时时间要改,之前是30
		}	  

	 
		 
	if(a!=blackleft)
	{
		 if(blackleft==1)
		 {a++;return 5;			//检测到第一条左黑时，左转90
		 }	
		 if(blackleft==2)
		 {a++;return 6;			//检测到第一条左黑时，左转90
		 }				 
	 }
	
	 if(b!=blackright)
	{
		 if(blackright==1||blackright==2)
		 {b++;return 6;			//检测到第一条右黑时，右转90
		 }	
	 }
	
	if(c!=blackall)
	{
		 if(blackall==1)
		 {c++;return 7;			//检测到第一条全黑时，掉头
		 }	
		 if(blackall==2)
		 {c++;return 8;			//检测到第二条全黑时，停
		 }	
	 }
	
	 return 0;
}
 
 
/*int xunji_detect()
 {
	static int a;
	static int b;
	static int c;
	static int blackleft;
	static int blackright;
	static int blackall;
	static int cgq1_ago;
	static int cgq2_ago;
//	static int cgq3_ago;
	static int cgq4_ago;
	static int cgq5_ago;
	cgq1_ago=cgq1;
	cgq2_ago=cgq2;
	//cgq3_ago=cgq3;
	cgq4_ago=cgq4;
	cgq5_ago=cgq5;	 
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //11011 直走
		return 0;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //11111 抖动
		return 0;	//可能要写个抖动的
	 
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //10011 左小转弯
		return 1;
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //10111 左小转弯
		return 1;
	  
	 if((cgq1==black)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //01111 左大转弯
		return 2;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //11001 右小转弯
		return 3;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //11101 右小转弯
		return 3;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==black)) //11110 右大转弯
		return 4;
	 	 
		if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00011  左大转弯
	  {
		  blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00111  左大转弯
	  {
		   blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00011  左大转弯
	  {
		  blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00111  左大转弯
	  {
		   blackleft++;
	  }
	  
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11100 右大转弯
	  {
		  blackright++;
	  }
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11000 
	  {
		  blackright++;
	  }
	  	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11100 右大转弯
	  {
		  blackright++;
	  }
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11000 
	  {
		  blackright++;
	  }
	  
	if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq1_ago==white)&&(cgq5_ago==white)) //00000,计数
		{
		blackall++;
		}	  
 
	 
 
		 
	if(a!=blackleft)
	{
		 if(blackleft==1)
		 {a++;return 5;			//检测到第一条左黑时，左转90
		 }		
		 if(blackleft==2)
		 {a++;return 6;			//检测到第一条左黑时，左转90
		 }		 		 
	 }
	
	 if(b!=blackright)
	{
		 if(blackright==1||blackright==2)
		 {b++;return 6;			//检测到第一条右黑时，右转90
		 }	
	 }
	
	if(c!=blackall)
	{
		 if(blackall==1)
		 {c++;return 7;			//检测到第一条全黑时，掉头
		 }	
		 if(blackall==2)
		 {c++;return 8;			//检测到第二条全黑时，停
		 }	
	 }
	
	 return 0;
}*/

