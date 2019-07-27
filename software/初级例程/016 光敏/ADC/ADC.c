 /***********************************************/
/* 名称：ADC.c
/* 功能：用于AD转换的初始化
		 将AD转换后的数据用数码管输出
   修改时间：2019年7月27日
   作者：曾思茹	               
/***********************************************/

#include <STC12C5A.H>  
#include "ADC.h"
#include "config.h"
sbit DIO = P0^0;				//串行数据输入
sbit RCLK  = P0^1;				//时钟脉冲信号——上升沿有效
sbit SCLK = P0^2;				//打入信号————上升沿有效
uchar LED[10];	//用于LED显示缓存
void LED_OUT(uchar X);
int date;		 //储存AD转换产生的8位数据



/***************************************/
/*	初始化AD寄存器 
	打开ADC转换电源 90个机器周期转换一次
	P1^0口作为AD转换口 
    函数名：InitADC       
/***************************************/
void InitADC()
{
	P1ASF=0x01;//P1.0作为AD使用
	
	ADC_CONTR=0xe0;//ADC电源打开,每90个时钟转换1次,CHS选择P1.0
	
	//默认为8位模式
	
	ADC_RES=0;//清零数据寄存器
	
	//初始化结束
	
	ADC_CONTR|=0x08;//ADC_START置1开始转换
	
	while(!(ADC_CONTR&0x10));//等待转换完成(ADC_FLAG=1)
	date=ADC_RES;//将数据储存在date中
	  
}



/************************************/
/*             数码管段码
	   函数名 ：  LED_0F
/************************************/
uchar code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90
};




/************************************/
/*             数码管显示
	    函数名 ： Display
/************************************/
void Display ()
{
	uchar code *led_table;          // 查表指针
	uchar i;
	uchar ge,shi,bai;	//数码管显示的个位十位百位
	ge = (uchar)(date%10);
	shi = (uchar)((date/10)%10);
	bai = (uchar)((date/100)%10); 

	//显示第1位
	led_table = LED_0F + LED[ge];
	i = *led_table;

	LED_OUT(i);	//传入要显示的字符		
	LED_OUT(0x01); //传入要显示的位数		

	RCLK = 0;
	RCLK = 1;	//时钟脉冲信号——上升沿有效

	//显示第2位
	led_table = LED_0F+LED[shi];  
	i = *led_table;

	LED_OUT(i);		 //传入要显示的字符
	LED_OUT(0x02);	//传入要显示的位数	

	RCLK = 0;
	RCLK = 1;	 //时钟脉冲信号——上升沿有效

	//显示第3位
	led_table = LED_0F+LED[bai];
	i = *led_table;

	LED_OUT(i);		  //传入要显示的字符
	LED_OUT(0x04);	//传入要显示的位数	

	RCLK = 0;
	RCLK = 1;	  //时钟脉冲信号——上升沿有效
}



/************************************/
/*          传入数据到数码管
	   函数名 ：LED_OUT
/************************************/
void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;	  //打入信号————上升沿有效
	}
}


void init()
{
	LED[0]=0;
	LED[1]=1;
	LED[2]=2;
	LED[3]=3;
	LED[4]=4;
	LED[5]=5;
	LED[6]=6;
	LED[7]=7;
	LED[8]=8;
	LED[9]=9;//数码管缓存数据 用于定位要输入到led_table的地址
	
}


