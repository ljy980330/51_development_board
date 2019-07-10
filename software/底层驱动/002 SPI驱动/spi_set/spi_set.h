/*********************************************************************************************************
*���ƣ�spi_set.h
*���ܣ����ͽ������ݺ�����ͷ�ļ��Լ�IO�ڵ������Ͷ��� 
����ʱ�䣺2019/7/10
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
*********************************************************************************************************/

#ifndef _SPI_SET_H
#define _SPI_SET_H					  

#include "config.h"
#include "reg51.h"

sbit	SPI_SCL	= P1^7;	//SPI��ͬ��ʱ��
sbit	SPI_MISO = P1^6;	//SPI��ͬ������
sbit	SPI_MOSI = P1^5;	//SPI��ͬ������
sbit	SPI_CS = P1^4;	//SPI��Ƭѡ

sfr AUXR1 = 0xA2;
sfr	AUXR  = 0x8E;


sfr SPSTAT = 0xCD;	
sfr SPCTL  = 0xCE;	
sfr SPDAT  = 0xCF;	

//sfr SPCTL   = 0x85;	SPI���ƼĴ���
//   7       6       5       4       3       2       1       0    	Reset Value
//	SSIG	SPEN	DORD	MSTR	CPOL	CPHA	SPR1	SPR0		0x00
#define	SSIG		1	//1: ����SS�ţ���MSTRλ�����������Ǵӻ�		0: SS�����ھ������ӻ���
#define	SPEN		1	//1: ����SPI��								0����ֹSPI������SPI�ܽž�Ϊ��ͨIO
#define	DORD		0	//1��LSB�ȷ���								0��MSB�ȷ�
#define	MSTR		1	//1����Ϊ����								0����Ϊ�ӻ�
#define	CPOL		1	//1: ����ʱSCLKΪ�ߵ�ƽ��					0������ʱSCLKΪ�͵�ƽ
#define	CPHA		1	//
#define	SPR1		0	//SPR1,SPR0   00: fosc/4,     01: fosc/16
#define	SPR0		0	//            10: fosc/64,    11: fosc/128
#define	SPEED_4		0	// fosc/4
#define	SPEED_16	1	// fosc/16
#define	SPEED_64	2	// fosc/64
#define	SPEED_128	3	// fosc/128

//sfr SPSTAT  = 0xCD;	//SPI״̬�Ĵ���
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		//SPI������ɱ�־��д��1��0��
#define	WCOL	0x40		//SPIд��ͻ��־��д��1��0��


//���ж������
#define MAIN_Fosc		22118400L	//������ʱ��
#define Baudrate0		115200L		//���岨����

#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate0)

void spi_init(void);

void uart_init(void);

#endif 