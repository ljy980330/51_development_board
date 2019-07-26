/*********************************************************************************************************
*名称：DianLiangLED.c
*功能：点亮LED对应的函数
创建时间：2019/7/4
修改时间：2019/7/4
作者：黄剑桥
*********************************************************************************************************/
#include "led.h"	  										 
#include "config.h"
#include "delay/delay.h"

void run()
{
	 P4SW=0xbb;	//定义P4IO口
     LED1=0;LED2=0;LED3=0;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=0;LED2=0;LED3=1;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=0;LED2=1;LED3=0;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=0;LED2=1;LED3=1;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=1;LED2=0;LED3=0;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=1;LED2=0;LED3=1;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=1;LED2=1;LED3=0;delay_ms(50);   //根据真值表点亮第一个LED	 
     LED1=1;LED2=1;LED3=1;delay_ms(50);   //根据真值表点亮第一个LED	 
}