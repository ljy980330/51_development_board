//超声波模块程序
//Trig  = P3^7
//Echo  = P3^2
#include <STC12C5A.H>			  
#include "config.h"	  			  
#include "delay/delay.h"	 
#include "led/led.h" 
extern uchar LED[8];	//用于LED的8位显示缓存

uint distance;
uint test =0;		
uint time = 0;
uint timeH = 0;
uint timeL = 0;
uint succeed_flag;
 
 
sbit Trig  = P3^7;
sbit Echo  = P3^2;
 
 
 void init()
 {
    Trig=0;       //首先拉低脉冲输入引脚
    EA=1;         //打开总中断0 
    TMOD=0x10;    //定时器1，16位工作方式 
 }
 
 void run()
 {		
		EA=0;           //关总中断
	    Trig=1;         //超声波输入端
	    delay_us(20);   //延时20us
	    Trig=0;         //产生一个20us的脉冲
	    while(Echo==0); //等待Echo回波引脚变高电平
	    succeed_flag=0; //清测量成功标志
	    EA=1; 
	    EX0=1;          //打开外部中断0
	    TH1=0;          //定时器1清零
	    TL1=0;          //定时器1清零
	    TF1=0;          //计数溢出标志
	    TR1=1;          //启动定时器1
	    delay_ms(20);   	
	    TR1=0;          //关闭定时器1
	    EX0=0;          //关闭外部中断0
	   if(succeed_flag==1)
	   {   
	      time=timeH*256+timeL;
	      distance=time*0.172;  //厘米
	   }                         
	  if(succeed_flag==0)
	   {
	      distance=0;                    //没有回波则清零
	      test = !test;                  //测试灯变化
	    }		 		  
		if(distance>=9999)
			distance=0;
		else
      		display(distance);
	  	LED4_Display ();
 }
//***************************************************************
//外部中断0，用做判断回波电平
void exter()  interrupt 0   // 外部中断0是0号
 {   
     timeH =TH1;    //取出定时器的值
     timeL =TL1;    //取出定时器的值
     succeed_flag=1;//至成功测量的标志
     EX0=0;         //关闭外部中断	 
 }
//****************************************************************
//定时器1中断,用做超声波测距计时
void timer1() interrupt 3  //
{
     TH1=0;
     TL1=0;
 }	