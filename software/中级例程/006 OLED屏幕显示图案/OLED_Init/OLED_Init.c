/*********************************************************************************************************
*名称：OLED_Init.c
*功能：延时所用到的函数
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "OLED_Init.h"

/*******************************************************************************
* 函 数 名         : OLED_Init
* 函数功能		   : 初始化函数
*******************************************************************************/

void OLED_init(void)
{
	Delay_ms(500);	//初始化之前的延时

	OLED_WrCmd(0xae);	//--关闭oled面板

	OLED_WrCmd(0x00);	//---设置低列地址

	OLED_WrCmd(0x10);	//---设置高列地址

	OLED_WrCmd(0x40);	//--设置起始行地址集映射RAM显示起始行（0x00-0x3F)

	OLED_WrCmd(0x81);	//--设置对比度控制寄存器

	OLED_WrCmd(Brightness);	//--设置SEG输出电流亮度

	OLED_WrCmd(0xa1);	//--列映射     0xa0左右反置 0xa1正常

	OLED_WrCmd(0xc8);	//--设置扫描方向   0xc0上下反置 0xc8正常

	OLED_WrCmd(0xa6);	//--设置正常显示

	OLED_WrCmd(0xa8);	//--设置多路复用率(1 to 64)

	OLED_WrCmd(0x3f);	//--1/64 

	OLED_WrCmd(0xd3);	//--设置显示偏移位移映射RAM计数器 (0x00~0x3F)

	OLED_WrCmd(0x00);	//--不设置

	OLED_WrCmd(0xd5);	//--设置显示时钟分频比/振荡器频率

	OLED_WrCmd(0x80);	//--设置风频比，设置时钟为100

	OLED_WrCmd(0xd9);	//--设置 pre-charge 时期

	OLED_WrCmd(0xf1);	//--设置预充15个时钟，放电1个时钟

	OLED_WrCmd(0xda);	//--设置硬件配置

	OLED_WrCmd(0x12);

	OLED_WrCmd(0xdb);	//--设置 vcomh

	OLED_WrCmd(0x40);	//--设置 VCOM 取消选择级别

	OLED_WrCmd(0x20);	//--设置页面寻址模式 (0x00/0x01/0x02)

	OLED_WrCmd(0x02);	//

	OLED_WrCmd(0x8d);	//--设置充电泵启用/禁用

	OLED_WrCmd(0x14);	//--设置(0x10) 禁用

	OLED_WrCmd(0xa4);	//--禁止用整个显示 (0xa4/0xa5)

	OLED_WrCmd(0xa6);	//--在 (0xa6/a7)上禁止反向显示 

	OLED_WrCmd(0xaf);	//--开启 oled面板

	OLED_Fill(0x00); 	//--初始清屏

	OLED_Set_Pos(0,0);

}