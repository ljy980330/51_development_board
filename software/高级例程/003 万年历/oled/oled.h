#ifndef __OLED_H
#define __OLED_H	  
#include "config.h"	 

void OLED_12864_Write_commomand(uint dat);		 //����
void OLED_12864_Write_data(uint dat);			 //����
void OLED_12864_Init();							 //��ʼ��
void OLED_Fill(uchar bmp_dat);					 //��Ļ���
void OLED_SetPos(uchar x, uchar y);				 //��ʼ����
void OLED_8x16Str(uchar x, uchar y, uchar ch);	 //8*16�ĵ���
void OLED_16x16CN(uchar x, uchar y, uchar N);	 //16*16�ĵ���
void OLED_16x32(uchar x, uchar y, uchar ch);		
#endif  