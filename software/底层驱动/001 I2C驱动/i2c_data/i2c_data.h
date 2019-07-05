/*********************************************************************************************************
*���ƣ�i2c_data.h
*���ܣ���i2c�����ֽ������շ��õ�ͷ�ļ�����������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _I2C_DATA_H
#define _I2C_DATA_H

#include "config.h"
#include "i2c_set/i2c_set.h"

void I2C_send_byte(U8 byte);

U8 I2C_read_byte();

bit I2C_TransmitData(U8 ADDR, DAT);

U8 I2C_ReceiveData(U8 ADDR);

#endif