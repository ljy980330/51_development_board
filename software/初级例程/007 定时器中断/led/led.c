/*********************************************************************************************************
*名称：led.c
*功能：点亮LED对应的函数
创建时间：2019/7/4
修改时间：2019/7/4
作者：黄彦钊
*********************************************************************************************************/
#include "led.h"   
sbit LED1=P4^0;      //位定义，将stc12中的定义为LED
sbit LED2=P4^1; 	  //每一个IO口都要进行定义
sbit LED3=P4^4; 	 
			  
/*******************************************************************************
* 函 数 名         : led1
* 函数功能		   : 根据真值表点亮第1个LED
*******************************************************************************/ 
void led1()
{
     LED1=0;
	 LED2=0;  
	 LED3=0;
}		
/*******************************************************************************
* 函 数 名         : led2
* 函数功能		   : 根据真值表点亮第1，2个LED
*******************************************************************************/ 
void led2()
{
     LED1=0;
	 LED2=1; 
	 LED3=1;
} 	
/*******************************************************************************
* 函 数 名         : led3
* 函数功能		   : 根据真值表点亮第1，3个LED
*******************************************************************************/ 
void led3()
{
     LED1=1;
	 LED2=0; 
	 LED3=1;
}