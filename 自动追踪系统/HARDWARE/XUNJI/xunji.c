//5·ѭ��
//cgq1 PA13	 cgq2 PA2	cgq3 PA3	cgq4 PA6	cgq5 PA7
//xunji_detect���Լ�⣬����ֵΪ��Ӧ��̬
//����0��ֱ��	1����Сת		2�����ת	3����Сת	4�Ҵ�ת
//5����ת90��	6����ת90��		7����ͷ��ת180��			8:ͣ
//����xunji_detect�е����ڼ�������ת

//Ҫxunji_Init()��ʼ�����Թ�IO��
//Ҫ���ݾ������ĿҪ���blackleft��blackright��blackall���ж�

#include "xunji.h"
#include "delay.h"

void xunji_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13; //KEY��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOB14	

}

 
 //����ȥA������
 int xunji_detect()
 {
	static int a;
	static int b;
	static int c;
	static int blackleft;
	static int blackright;
	static int blackall;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //11011 ֱ��
		return 0;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //11111 ����
		return 0;	//����Ҫд��������
	 
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //10011 ��Сת��
		return 1;
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //10111 ��Сת��
		return 1;
	  
	 if((cgq1==black)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //01111 ���ת��
		return 2;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //11001 ��Сת��
		return 3;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //11101 ��Сת��
		return 3;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==black)) //11110 �Ҵ�ת��
		return 4;
	 	 
		if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //00011  ���ת��
	  {
		  blackleft++;
		  delay_us(xian_delay);
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //00111  ���ת��
	  {
		   blackleft++;
		  delay_us(xian_delay);
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //00111  ���ת��
	  {
		   blackleft++;
		  delay_us(xian_delay);
	  }
	  		if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //00011  ���ת��
	  {
		  blackleft++;
		  delay_us(xian_delay);
	  }

	  
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)) //11100 �Ҵ�ת��
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //11000 
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	  	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)) //11100 �Ҵ�ת��
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //11000 
	  {
		  blackright++;
		  delay_us(xian_delay);
	  }
	  
	if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)) //00000,����
		{
		blackall++;
		delay_us(xian_delay);//��ʱʱ��Ҫ��,֮ǰ��30
		}	  

	 
		 
	if(a!=blackleft)
	{
		 if(blackleft==1)
		 {a++;return 5;			//��⵽��һ�����ʱ����ת90
		 }	
		 if(blackleft==2)
		 {a++;return 6;			//��⵽��һ�����ʱ����ת90
		 }				 
	 }
	
	 if(b!=blackright)
	{
		 if(blackright==1||blackright==2)
		 {b++;return 6;			//��⵽��һ���Һ�ʱ����ת90
		 }	
	 }
	
	if(c!=blackall)
	{
		 if(blackall==1)
		 {c++;return 7;			//��⵽��һ��ȫ��ʱ����ͷ
		 }	
		 if(blackall==2)
		 {c++;return 8;			//��⵽�ڶ���ȫ��ʱ��ͣ
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
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //11011 ֱ��
		return 0;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //11111 ����
		return 0;	//����Ҫд��������
	 
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)) //10011 ��Сת��
		return 1;
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //10111 ��Сת��
		return 1;
	  
	 if((cgq1==black)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)) //01111 ���ת��
		return 2;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)) //11001 ��Сת��
		return 3;
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)) //11101 ��Сת��
		return 3;
	 
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==white)&&(cgq5==black)) //11110 �Ҵ�ת��
		return 4;
	 	 
		if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==white)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00011  ���ת��
	  {
		  blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==white)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00111  ���ת��
	  {
		   blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00011  ���ת��
	  {
		  blackleft++;
	  }
	  if((cgq1==black)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==white)&&(cgq1_ago==white)&&(cgq2_ago==white)) //00111  ���ת��
	  {
		   blackleft++;
	  }
	  
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11100 �Ҵ�ת��
	  {
		  blackright++;
	  }
	 if((cgq1==white)&&(cgq2==white)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11000 
	  {
		  blackright++;
	  }
	  	 if((cgq1==white)&&(cgq2==black)&&(cgq3==white)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11100 �Ҵ�ת��
	  {
		  blackright++;
	  }
	 if((cgq1==white)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq4_ago==white)&&(cgq5_ago==white)) //11000 
	  {
		  blackright++;
	  }
	  
	if((cgq1==black)&&(cgq2==black)&&(cgq3==black)&&(cgq4==black)&&(cgq5==black)&&(cgq1_ago==white)&&(cgq5_ago==white)) //00000,����
		{
		blackall++;
		}	  
 
	 
 
		 
	if(a!=blackleft)
	{
		 if(blackleft==1)
		 {a++;return 5;			//��⵽��һ�����ʱ����ת90
		 }		
		 if(blackleft==2)
		 {a++;return 6;			//��⵽��һ�����ʱ����ת90
		 }		 		 
	 }
	
	 if(b!=blackright)
	{
		 if(blackright==1||blackright==2)
		 {b++;return 6;			//��⵽��һ���Һ�ʱ����ת90
		 }	
	 }
	
	if(c!=blackall)
	{
		 if(blackall==1)
		 {c++;return 7;			//��⵽��һ��ȫ��ʱ����ͷ
		 }	
		 if(blackall==2)
		 {c++;return 8;			//��⵽�ڶ���ȫ��ʱ��ͣ
		 }	
	 }
	
	 return 0;
}*/

