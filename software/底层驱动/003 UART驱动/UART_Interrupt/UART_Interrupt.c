/*********************************************************************************************************
*名称：UART_Interrupt.c
*功能：串口的接收
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
*********************************************************************************************************/

#include "UART_Interrupt.h"

void UART_Interrupt()
{
	U8 date;

	date=SBUF;        //取出接受到的数据
	RI=0;			  //清除接受中断标志位
	SBUF=date;		  //接收到的数据放入发送缓存器发送
	while(!TI);        //等待发送数据完成
	TI=0;				//清除发送完成标志位

}