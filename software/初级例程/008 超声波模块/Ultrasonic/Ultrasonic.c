//超声波模块程序
//作者 ： Z H
//时间 2015/11/29
//Trig  = P2^0
//Echo  = P3^2
#include <STC12C5A.H>			  
#include "config.h"	 
#include <led/led.h> 
extern uchar LED[8];	//用于LED的8位显示缓存

uint distance;
uint test =0;		
uint time = 0;
uint timeH = 0;
uint timeL = 0;
uint succeed_flag;
 
 
sbit dula=P2^0;		//段选信号的锁存器控 制
sbit wela=P2^1;		//位选信号的锁存器控制
sbit Trig  = P2^2;
sbit Echo  = P3^2;
 
//
void delay(uint z)
{
 uint x,y;
  for(x=z;x>0;x--)
  for(y=125;y>0;y--);
}
//
void delay_20us()
 { 
    uchar a ;
    for(a=0;a<100;a++);
 }
//***************************************************************
//显示数据转换程序
void display(uint temp) 
 { 
    uchar qian,ge,shi,bai;
	qian = temp/1000;
    bai=temp/100%10;
    shi=temp%100/10;  
    ge=temp%10;
	
	LED[1]=qian;
	LED[2]=bai;
	LED[3]=shi;
	LED[4]=ge;
	
 }	 
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
    delay_20us();   //延时20us
    Trig=0;         //产生一个20us的脉冲
    while(Echo==0); //等待Echo回波引脚变高电平
    succeed_flag=0; //清测量成功标志
    EA=1; 
    EX0=1;          //打开外部中断0
    TH1=0;          //定时器1清零
    TL1=0;          //定时器1清零
    TF1=0;          //计数溢出标志
    TR1=1;          //启动定时器1
    delay(20);      //等待测量的结果
    TR1=0;          //关闭定时器1
    EX0=0;          //关闭外部中断0
   if(succeed_flag==1)
   {   
      time=timeH*256+timeL;
      distance=time*0.172;  //厘米
      display(distance);
	  LED4_Display ();
   }                         
  if(succeed_flag==0)
   {
      distance=0;                    //没有回波则清零
      test = !test;                  //测试灯变化
    }    
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