/*********************************************************************************************************
*名称：delay.h
*功能：外部所用到的延迟功能函数声明
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/
#ifndef _SERIAL_H
#define _SERIAL_H	  

#define FOSC   18432000L
#define BAUD   115200

#define NONE_PARITY  0

#define PARITYBIT  NONE_PARITY

#define S2RI 0x01
#define S2TI 0x02
#define S2RB8 0x04
#define S2TB8 0x08

void UsartInit();


void Uart2Init(void);
void Uart2_send_byte(unsigned char date);
void Uart2_send_string(unsigned char *p);
#endif