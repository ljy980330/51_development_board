/*********************************************************************************************************
*名称：receive.h
*功能：外部所用到的spi发送功能函数声明
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/
#ifndef _SEND_H_
#define _SEND_H_	

#include <STC12C5A.H>
#include "intrins.h"
#include "config.h"	 
#include "UART/UART.h"	
#include "spi/spi.h"	
#include "delay/delay.h" 

void run();		  
void UART();
 
#endif