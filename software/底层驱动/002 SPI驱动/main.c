/*********************************************************************************************************
*名称：spi驱动
*功能：每隔50ms，从SPI发送32个字节数据
创建时间：2019/7/10
修改时间：2019/XX/XX
作者：李诗琪
*********************************************************************************************************/

#include "includes.h"

#define		BUF_LENTH	64		//定义串口接收缓冲长度
U8	uart_wr;		//写指针
U8 	uart_rd;		//读指针
U8 	idata RX_Buffer[BUF_LENTH];
bit		B_TI;

int main()
{
	uart_init();
	spi_init();
	
	while(1)
	{
		if(uart_rd != uart_wr)	//串口0转发
		{
			SPI_CS = 0;							//允许外部PSI器件
			SPSTAT = SPIF + WCOL;			//清0 SPIF和WCOL标志
			SPDAT = RX_Buffer[uart_rd];	//发送一个字节
			while((SPSTAT & SPIF) == 0)	;	//等待发送完成
			SPSTAT = SPIF + WCOL;				//清0 SPIF和WCOL标志
			SPI_CS = 1;							//禁止外部PSI器件

			if(++uart_rd >= BUF_LENTH)		uart_rd = 0;
		}
	}			 
}

void UART_RCV (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		RX_Buffer[uart_wr] = SBUF;
		if(++uart_wr >= BUF_LENTH)	uart_wr = 0;
	}

	if(TI)
	{
		TI = 0;
		B_TI = 1;
	}
}