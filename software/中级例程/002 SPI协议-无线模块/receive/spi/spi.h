/*********************************************************************************************************
*���ƣ�spi.h
*���ܣ��ⲿ���õ���spi��������
����ʱ�䣺2019/7/8
�޸�ʱ�䣺2019/7/11
���ߣ�������
*********************************************************************************************************/	
#ifndef __SPI_H__
#define __SPI_H__
		
#include "config.h"	
#include "spi/spi.h"
						   
void RX_Mode();								
void TX_Mode();
void init_NRF24L01();
uchar NRF24L01_Check();
uchar nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);
#endif  
