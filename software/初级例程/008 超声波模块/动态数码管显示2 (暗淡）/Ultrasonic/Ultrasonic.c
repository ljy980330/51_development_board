#include <STC12C5A.H>  
#include <stdio.h>		
#include "config.h"	
#include "delay/delay.h"
#include "Ultrasonic.h"		  
#include "led/led.h" 

sbit RX=P3^2;
sbit TX=P3^7;		 
uint time=0;
uint timer=0;
float   distance=0;
bit    flag =0;
/********************************************************/
void conut(void)
{
 time=TH0*256+TL0;
 TH0=0;
 TL0=0;
 distance=(time*1.88)/10;     //算出来是MM
 if((distance>=7000)||flag==1) //超出测量范围显示“-”
 {	 
    flag=0;
	display(7000);
	LED4_Display ();
 }
 else
 {
  	display(distance);
  	LED4_Display ();
  } 
}
void timer_Count(void)
{
	 TR0=1;			    //开启计数
     while(RX);			//当RX为1计数并等待
     TR0=0;				//关闭计数
     conut();			//计算

}			   		  
/********************************************************/
void  startModule() 		         //T1中断用来扫描数码管和计800MS启动模块
{
  TX=1;			                 //800MS  启动一次模块
  nop(20); 
  TX=0;
}

void init()
{
	TMOD=0x21;		   //设T0为方式1，GATE=1；
	SCON=0x50;
	TH1=0xFD;
	TL1=0xFD;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //允许T0中断
	TR1=1;			   //开启定时器
	TI=1;
	
	EA=1;			   //开启总中断
}

void run()
{			  
	uint valA;
	delay_ms(60);
	RX=1;
    startModule();
    for(valA=7510;valA>0;valA--)
    {
       if(RX==1)
	   {
       timer_Count();
	   }
	 }
}
/********************************************************/
 void timer0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
{
	flag=1;							 //中断溢出标志
	RX=0;
}
