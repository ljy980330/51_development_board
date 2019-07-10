/*********************************************************************************************************
*���ƣ�spi����
*���ܣ�ÿ��50ms����SPI����32���ֽ�����
����ʱ�䣺2019/7/10
�޸�ʱ�䣺2019/XX/XX
���ߣ���ʫ��
*********************************************************************************************************/

#include "includes.h"

#define		BUF_LENTH	64		//���崮�ڽ��ջ��峤��
U8	uart_wr;		//дָ��
U8 	uart_rd;		//��ָ��
U8 	idata RX_Buffer[BUF_LENTH];
bit		B_TI;

int main()
{
	uart_init();
	spi_init();
	
	while(1)
	{
		if(uart_rd != uart_wr)	//����0ת��
		{
			SPI_CS = 0;							//�����ⲿPSI����
			SPSTAT = SPIF + WCOL;			//��0 SPIF��WCOL��־
			SPDAT = RX_Buffer[uart_rd];	//����һ���ֽ�
			while((SPSTAT & SPIF) == 0)	;	//�ȴ��������
			SPSTAT = SPIF + WCOL;				//��0 SPIF��WCOL��־
			SPI_CS = 1;							//��ֹ�ⲿPSI����

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