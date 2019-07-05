/*********************************************************************************************************
*名称：i2c协议
*功能：用i2c协议实现EEPROM芯片的通信 
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
*********************************************************************************************************/

#include "includes.h"

int main()
{
	I2C_Init();	//I2C初始化
	if(!I2C_TransmitData(255,0xf0));	//往AT24C02第255个单元中写入数据0xf0
	{
		P1 = 0;
	}
	_nop_();	//延时5us

	P1 = I2C_ReceiveData(255);	//从AT24C02第255个单元中读取数据

	while(1);
}