/*********************************************************************************************************
*名称：LEDshanshuo.c
*功能：闪烁函数对应的函数
创建时间：2019/7/4
修改时间：2019/7/4
作者：黄剑桥
*********************************************************************************************************/
#include "LEDshanshuo.h"

void LED_Shan_Shuo()
{
while(1)
{
   P4SW=0xbb;	//定义P4IO口
   LED1=1;	   //点亮第一个led
   LED2=1;
   LED3=0;
   E3=~E3;	   //使其电平反转
   Delay_us(10000);
   
}
}