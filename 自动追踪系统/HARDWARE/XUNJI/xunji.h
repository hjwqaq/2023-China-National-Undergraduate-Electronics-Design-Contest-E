#ifndef __XUNJI_H
#define __XUNJI_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////	
#define xian_delay 25	//每个黑线状态检测的延时us

#define cgq1 PAin(13)	 
#define cgq2 PAin(2)	
#define cgq3 PAin(3)		
#define cgq4 PAin(6)	
#define cgq5 PAin(7)	

#define black 1	
#define white 0	

void xunji_Init(void);
int xunji_detect(void);
#endif
