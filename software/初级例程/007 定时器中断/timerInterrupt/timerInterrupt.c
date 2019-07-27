/*********************************************************************************************************
*名称：timerInterrupt.c
*功能：定时中断对应的函数
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄彦钊
********************************************************************************************************/
#include "timerInterrupt.h"	
#include "config.h"	  
#include "led/led.h"	
uint time;
/*********************************************************************************************************
** TMOD是八位定时器/计数器模式控制寄存器（TIMER/COUNTER MODE CONTROL REGISTER），其中低四位定义定时器/计数器T0,高四位定义定时器/计数器T1
**
** 配置定时器0模式（即配置低四位）：|GATE           |  C/T                  |    M1 | M0 				  |
**					                 0	               0      设置为定时模式     0    0		13位定时模式
** 	                                 1 要求INT0脚为高  1      设置为计数模式     0	  1		16位定时模式
** 		 		                                                                 1    0		8位自动装载模式
**
** 配置定时器1模式（即配置高四位）： |GATE           |  C/T                  |    M1 | M0 				  |
**					                 0	               0      设置为定时模式     0    0		13位定时模式
** 	                                 1 要求INT0脚为高  1      设置为计数模式     0	  1		16位定时模式
** 		 		                                                                 1    0		8位自动装载模式
** 详细的介绍请参看文档STC12C5A60S2.pdf中定时器计数器的章节
** 本例程采用16位定时模式，TH0,TL0全用
*********************************************************************************************************/


/*******************************************************************************************************
**函数：init
**功能：定时器0初始化
***********************************************************************************************************/
void init()
{
  TMOD = 0X01;	//设置定时器的工作方式						   
	TH0 = (65536-FSCLK/12/20)/256;	 //配置定时器的高8位
	TL0 = (65536-FSCLK/12/20)%256;	 //配置定时器的低8位
	ET0 = 1;					 //允许定时器0中断
	EA = 1;						 //打开总中断EA和ET0、TR0全部置1后，如果计数器计数溢出就马上执行中断处理函数void time0() interrupt 1 
	TR0 = 1;					 //打开定时器，开始计数
}

	
/*******************************************************************************
* 函 数 名         : timer0
* 函数功能		   : 定时器0程序
					 实现2秒定时，即每2秒就执行一次if里面的程序语句
*******************************************************************************/ 

void timer0() interrupt 1
{
	int i=0;
	TH0 = (65536-FSCLK/12/20)/256; //每一次进入中断都要给定时器赋值，以确定下一次进入中断的时间
	TL0 = (65536-FSCLK/12/20)%256;	
	time ++;
	if(time ==40)				
	{
		if(i==0)
			led1();	
		if(i==1)
			led2();
		if(i==2)
		{
			i=0;
			led3();
		}
		time = 0; 
		i++;
	}		
}

