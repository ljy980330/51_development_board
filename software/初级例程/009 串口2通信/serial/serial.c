/**************************************************************************************
*		              串口通信实验												  *
实现现象：下载程序后打开串口调试助手，将波特率设置为2400，选择发送的数据就可以显示
			在串口助手上。
注意事项：无。																				  
***************************************************************************************/
//#include "STC12C5A.H"
#include <STC12C5A60S2.H>
#include "config.h"
#include "serial.h"

/*--------------------------------
串口2范例程序
*
RXD--P1.2
TXD--P1.3

*/
#include <STC12C5A60S2.H>
#include "config.h"
#include "serial.h"


void Uart2Init(void)                //9600bps@11.0592MHz      
{
	AUXR |= 0x08;                //使能波特率倍速位S2SMOD：（波特率加倍）
	S2CON = 0x50;                //8位数据,可变波特率
	AUXR &= 0xFB;                //独立波特率发生器时钟为Fosc/12,即12T

	BRT = 0xFA;                //设定独立波特率发生器重装值

	AUXR |= 0x10;                //启动独立波特率发生器
	
	IE2 = 0x01;
	EA = 1;
	ES = 1; //允许UART串口的中断
}


void Uart2_send_byte(uchar date)//自己改下名称 不要一样 
{        
	S2BUF=date;
	while((S2CON&0X02)==0);
	S2CON&=~0X02;              //清除发送标志位

}

void Uart2_send_string(uchar *p)   //串口2发送一个字符串
{
	while(*p!='\0')
	{
			Uart2_send_byte(*p);
			p++;
	}
}

void Usart2() interrupt 8
{
	uchar dat;
	
	if(S2CON & S2RI)
	{
		S2CON &= ~S2RI;
		dat = S2BUF;
		Uart2_send_byte(dat);
	}
}


