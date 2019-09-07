/**************************************************************************************
*		              串口通信实验												  *
实现现象：下载程序后打开串口调试助手，将波特率设置为2400，选择发送的数据就可以显示
			在串口助手上。
注意事项：无。																				  
***************************************************************************************/
#include "STC12C5A.H"	  
#include "config.h"
#include "serial.h"
/*******************************************************************************
* 函 数 名         : UsartInit
* 函数功能		   : 串口初始化
*******************************************************************************/
void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器

}
	  
/*******************************************************************************		
* 函 数 名         : Usart
* 函数功能		   : 串口通信中断函数
*******************************************************************************/
void Usart() interrupt 4
{
	uchar receiveData;

	receiveData=SBUF;//出去接收到的数据
	RI = 0;//清除接收中断标志位
	SBUF=receiveData;//将接收到的数据放入到发送寄存器
	while(!TI);			 //等待发送数据完成
	TI=0;						 //清除发送完成标志位
}