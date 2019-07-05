/*********************************************************************************************************
*���ƣ�i2c_set.h
*���ܣ�	i2c���������õ���ͷ�ļ��Լ�����������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _I2C_SET_H
#define _I2C_SET_H

#include "config.h"
#include "intrins.h"
#include "STC12C5A.H"

#define AT24C02_ADDR  0xa0	//AT24C02��ַ
#define high 1	//�ߵ�ƽ
#define low  0	//�͵�λ

sbit SCL = P2^0;	//����ʱ��
sbit SDA = P2^1;	//��������

void I2C_Init();

void I2C_Start();

void I2C_Stop();

void Master_ACK(bit i);

bit Test_ACK();


#endif

