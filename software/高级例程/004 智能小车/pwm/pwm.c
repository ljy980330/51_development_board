/*********************************************************************************************************
*名称：pwm.c
*功能：pwm调速所用到的函数
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/

#include <STC12C5A.H>
#include "pwm.h"	   
#include "config.h"
sbit ENB1=P2^0;       //从后面看，控制左前电机的占空比
sbit ENA1=P2^5;       //从后面看，控制左后电机的占空比
int  left;	  //左转速率
int  right;	  //右转速率
int  t1;	  //pwm值      	  //小车停止	*/
	  
/*******************************************************************************
* 函 数 名         : Time1
* 函数功能		   : 串口初始化
*******************************************************************************/
void Time1()  
{ 
	 SCON=0x50;          //设定串口工作方式
     PCON=0x00;          //波特率不倍增
	 EA=1;
	 TMOD|=0x02;
	 TR0=1;
	 ET0=1;
	 TH0=(65535-100)/256;
	 TL0=(65535-100)%256; 
}	
/*******************************************************************************
* 函 数 名         : goahead
* 函数功能		   : 小车直走
*******************************************************************************/
void goahead()
{
     left=37;
	 right=38;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
} 	
/*******************************************************************************
* 函 数 名         : goahead1
* 函数功能		   : 小车直走方式2
*******************************************************************************/
void goahead1()
{
     left=35;
	 right=36;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
} 
/*******************************************************************************
* 函 数 名         : turnleft
* 函数功能		   : 左转
*******************************************************************************/
void turnleft() 	 
{
     left=0;
	 right=39;
	 left1=0;
	 left2=1;
	 right1=1;
	 right2=0;
}
/*******************************************************************************
* 函 数 名         : turnright
* 函数功能		   : 右转
*******************************************************************************/
void turnright()
{
     left=37;
	 right=0;
	 left1=1;
	 left2=0;
	 right1=0;
	 right2=1;
}
/*******************************************************************************
* 函 数 名         : turnback1
* 函数功能		   : 向右后转
*******************************************************************************/
void turnback1()
{
     left=40;
	 right=57;
	 left1=1;
	 left2=0;
	 right1=0;
	 right2=1;
}	
/*******************************************************************************
* 函 数 名         : turnback2
* 函数功能		   : 向右后转方式2
*******************************************************************************/
void turnback2()//向左后转
{
     left=54;
	 right=41;
	 left1=0;
	 left2=1;
	 right1=1;
	 right2=0;
}  		
/*******************************************************************************
* 函 数 名         : turnback3
* 函数功能		   : 向右后转方式3
*******************************************************************************/
void turnback3()//
{
     left=40;
	 right=57;
	 left1=1;
	 left2=0;
	 right1=0;
	 right2=1;
}  
/*******************************************************************************
* 函 数 名         : offsetleft
* 函数功能		   : 向左偏移
*******************************************************************************/
void offsetleft()	
{
	 left=0;
	 right=41;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
} 
/*******************************************************************************
* 函 数 名         : offsetleft1
* 函数功能		   : 向左偏移方式2
*******************************************************************************/
void offsetleft1()	
{
	 left=0;
	 right=37;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
}
/*******************************************************************************
* 函 数 名         : offsetright
* 函数功能		   : 向右偏移
*******************************************************************************/
void offsetright()	
{
     left=42;
	 right=0;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
} 
/*******************************************************************************
* 函 数 名         : offsetright1
* 函数功能		   : 向右偏移方式2
*******************************************************************************/
void offsetright1()	
{
     left=36;
	 right=0;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
}  
/*******************************************************************************
* 函 数 名         : stop
* 函数功能		   : 暂停
*******************************************************************************/
void stop()			  
{
     left=0;
	 right=0;
	 left1=0;
	 left2=0;
	 right1=0;
	 right2=0;
}  
/*******************************************************************************
* 函 数 名         : wentleft
* 函数功能		   : 小车向左前方前进
*******************************************************************************/
void wentleft()	  
{
     left=34;
	 right=45;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
}

/*******************************************************************************
* 函 数 名         : in1
* 函数功能		   : 定时器中断1.控制左电机的速度
*******************************************************************************/
void in1() interrupt 1	   
{
	TH0=(65535-100)/256;
	TL0=(65535-100)%256;
	t1++;
	if(t1==400) {t1=0;}
	if(t1<left){ENB1=1;}   //左前电机
	else{ENB1=0;}
	if(t1<right) {ENA1=1;}   //左后电机
	else{ENA1=0;}
}

