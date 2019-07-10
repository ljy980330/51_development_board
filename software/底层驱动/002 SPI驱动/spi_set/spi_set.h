/*********************************************************************************************************
*名称：spi_set.h
*功能：发送接收数据函数和头文件以及IO口的声明和定义 
创建时间：2019/7/10
修改时间：2019/XX/XX
作者：XXX
*********************************************************************************************************/

#ifndef _SPI_SET_H
#define _SPI_SET_H					  

#include "config.h"
#include "reg51.h"

sbit	SPI_SCL	= P1^7;	//SPI卡同步时钟
sbit	SPI_MISO = P1^6;	//SPI卡同步数据
sbit	SPI_MOSI = P1^5;	//SPI卡同步数据
sbit	SPI_CS = P1^4;	//SPI卡片选

sfr AUXR1 = 0xA2;
sfr	AUXR  = 0x8E;


sfr SPSTAT = 0xCD;	
sfr SPCTL  = 0xCE;	
sfr SPDAT  = 0xCF;	

//sfr SPCTL   = 0x85;	SPI控制寄存器
//   7       6       5       4       3       2       1       0    	Reset Value
//	SSIG	SPEN	DORD	MSTR	CPOL	CPHA	SPR1	SPR0		0x00
#define	SSIG		1	//1: 忽略SS脚，由MSTR位决定主机还是从机		0: SS脚用于决定主从机。
#define	SPEN		1	//1: 允许SPI，								0：禁止SPI，所有SPI管脚均为普通IO
#define	DORD		0	//1：LSB先发，								0：MSB先发
#define	MSTR		1	//1：设为主机								0：设为从机
#define	CPOL		1	//1: 空闲时SCLK为高电平，					0：空闲时SCLK为低电平
#define	CPHA		1	//
#define	SPR1		0	//SPR1,SPR0   00: fosc/4,     01: fosc/16
#define	SPR0		0	//            10: fosc/64,    11: fosc/128
#define	SPEED_4		0	// fosc/4
#define	SPEED_16	1	// fosc/16
#define	SPEED_64	2	// fosc/64
#define	SPEED_128	3	// fosc/128

//sfr SPSTAT  = 0xCD;	//SPI状态寄存器
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		//SPI传输完成标志。写入1清0。
#define	WCOL	0x40		//SPI写冲突标志。写入1清0。


//自行定义参数
#define MAIN_Fosc		22118400L	//定义主时钟
#define Baudrate0		115200L		//定义波特率

#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate0)

void spi_init(void);

void uart_init(void);

#endif 