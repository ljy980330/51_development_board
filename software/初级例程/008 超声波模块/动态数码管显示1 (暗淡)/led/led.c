#include "led.h"
 unsigned char code fseg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
 unsigned char code segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
 unsigned char  disbuf[4]={0,0,0,0};
 //-----------------------------------------------------------------------------
// 函数原形定义
uchar LED[8];	//用于LED的8位显示缓存

void LED4_Display ();			// LED显示
void LED_OUT(uchar X);				// LED单字节串行移位函数

unsigned char code LED_0F[];		// LED字模表

sbit DIO = P0^0;				//串行数据输入
sbit RCLK  = P0^1;				//时钟脉冲信号——上升沿有效
sbit SCLK = P0^2;				//打入信号————上升沿有效


void LED4_Display ()
{
	uchar code *led_table;          // 查表指针
	uchar i;
	//显示第1位
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK = 0;
	RCLK = 1;
	//显示第2位
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK = 0;
	RCLK = 1;
	//显示第3位
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK = 0;
	RCLK = 1;
	//显示第4位
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLK = 0;
	RCLK = 1;
}

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;
	}
}

unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

//
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

