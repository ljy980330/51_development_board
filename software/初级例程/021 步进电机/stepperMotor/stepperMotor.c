/*****************************/
/*  此程序用于步进电机       */
/*	修改时间：2019年7月7日   */
/*	作者：曾思茹			 */
/*****************************/

#include <STC12C5A.H>			  
#include "config.h"	  		  
#include "delay/delay.h"

#define speed 200 //宏定义延时函数要使用的大小

sbit a=P2^3;
sbit b=P2^4;
sbit c=P2^5;
sbit d=P2^6;	 //给管口命名




/************************************/
/*	转动函数						*/
/*	函数名：A_run B_run C_run D_run	*/
/*  正转A-B-C-D 反转D-C-B-A 		*/
/************************************/
void A_run()
{
	a=1;
	b=0;
	c=0;
	d=0;
}

void B_run()
{
	a=0;
	b=1;
	c=0;
	d=0;
}

void C_run()
{	
	a=0;
	b=0;
	c=1;
	d=0;
}
void D_run()
{
	a=0;
	b=0;
	c=0;
	d=1;
}
void run()
{
		
	P1=0x00;  //0000 0000	将所有的IO关闭
	A_run();		  //A相通电，其他相断电
	delay_ms(10);
	B_run();		  //B相通电，其他相断电
	delay_ms(10);
	C_run();		  //C相通电，其他相断电
	delay_ms(10);
	D_run();		  //D相通电，其他相断电
	delay_ms(10);
}