#ifndef __OLED_H
#define __OLED_H	  
#include "config.h"	 

void OLED_12864_Write_commomand(uint dat);		 //命令
void OLED_12864_Write_data(uint dat);			 //数据
void OLED_12864_Init();							 //初始化
void OLED_Fill(uchar bmp_dat);					 //屏幕填充
void OLED_SetPos(uchar x, uchar y);				 //起始坐标
void OLED_8x16Str(uchar x, uchar y, uchar ch);	 //8*16的点阵
void OLED_16x16CN(uchar x, uchar y, uchar N);	 //16*16的点阵
void OLED_16x32(uchar x, uchar y, uchar ch);		
#endif  