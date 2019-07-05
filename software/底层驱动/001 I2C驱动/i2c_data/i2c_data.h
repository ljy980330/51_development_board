/*********************************************************************************************************
*名称：i2c_data.h
*功能：对i2c总线字节数据收发用到头文件，函数声明
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
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