/*********************************************************************************************************
*名称：spi.h
*功能：外部调用到的spi驱动函数
创建时间：2019/7/8
修改时间：2019/7/11
作者：黄彦钊
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
