/*********************************************************************************************************
*名称：main.c
*功能：按键控制数码管
		key1 增加
		key2 减少
		key3 清零
创建时间：2019/7/8
修改时间：2019/7/11
作者：黄彦钊
*********************************************************************************************************/
#include "includes.h"
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
*******************************************************************************/ 
void main()
{		   
	P4M1=0x00;//P4.1 P4.4 P4.5 P4.6推挽
	P4M0=0x72; 
	P4SW=0x70;//P4.4=I/O P4.5=I/O P4.6=I/O 
    P1=0x00;
	while(1)
	{
    	run();
	}
}

