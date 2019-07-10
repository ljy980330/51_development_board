/*********************************************************************************************************
*名称：spi_set.c
*功能： 发送以及接收数据
创建时间：2019/7/10
修改时间：2019/XX/XX
作者：XXX
*********************************************************************************************************/

#include "spi_set.h"


/*******************************************************************************
* 函 数 名         : spi_init
* 函数功能		   : spi初始化
*******************************************************************************/

void spi_init(void)
{
	SPCTL = (SSIG << 7) + (SPEN << 6) + (DORD << 5) + (MSTR << 4) + (CPOL << 3) + (CPHA << 2) + SPEED_16;
}

/*******************************************************************************
* 函 数 名         :uart_init
* 函数功能		   : 串口初始化
*******************************************************************************/

void uart_init(void)
{
	PCON |= 0x80;		
	SCON = 0x50;	
	TMOD &= ~(1<<6);		//设置为定时器1
	TMOD = (TMOD & ~0x30) | 0x20;	
	TH1 = T1_TimerReload;	
	TR1  = 1;
	ES  = 1;
	EA = 1;
}












