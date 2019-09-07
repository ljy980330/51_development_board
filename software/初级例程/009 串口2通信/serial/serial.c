/**************************************************************************************
*		              ����ͨ��ʵ��												  *
ʵ���������س����򿪴��ڵ������֣�������������Ϊ2400��ѡ���͵����ݾͿ�����ʾ
			�ڴ��������ϡ�
ע������ޡ�																				  
***************************************************************************************/
//#include "STC12C5A.H"
#include <STC12C5A60S2.H>
#include "config.h"
#include "serial.h"

/*--------------------------------
����2��������
*
RXD--P1.2
TXD--P1.3

*/
#include <STC12C5A60S2.H>
#include "config.h"
#include "serial.h"


void Uart2Init(void)                //9600bps@11.0592MHz      
{
	AUXR |= 0x08;                //ʹ�ܲ����ʱ���λS2SMOD���������ʼӱ���
	S2CON = 0x50;                //8λ����,�ɱ䲨����
	AUXR &= 0xFB;                //���������ʷ�����ʱ��ΪFosc/12,��12T

	BRT = 0xFA;                //�趨���������ʷ�������װֵ

	AUXR |= 0x10;                //�������������ʷ�����
	
	IE2 = 0x01;
	EA = 1;
	ES = 1; //����UART���ڵ��ж�
}


void Uart2_send_byte(uchar date)//�Լ��������� ��Ҫһ�� 
{        
	S2BUF=date;
	while((S2CON&0X02)==0);
	S2CON&=~0X02;              //������ͱ�־λ

}

void Uart2_send_string(uchar *p)   //����2����һ���ַ���
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


