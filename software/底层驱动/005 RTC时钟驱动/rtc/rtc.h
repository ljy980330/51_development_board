/*********************************************************************************************************
*名称：rtc.h
*功能：外部所用到的rtc驱动函数声明
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/
#include <STC12C5A.H>	
#include "config.h"	 
#ifndef __IIC_H
#define __IIC_H

uchar write_byte(uchar addr, uchar write_data);
void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec); //初始化时钟,ModifyTime(10,6,13,15,30,00)=2010/6/13,15/30/00
void get_show_date();	//显示日期 
void get_show_Temperature(); //显示温度
void get_show_time();	//显示时间 
#endif  