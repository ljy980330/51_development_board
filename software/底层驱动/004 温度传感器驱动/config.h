/*********************************************************************************************************
*���ƣ�config.h
*���ܣ����������Լ�ͨ�ñ����������Ͷ���
����ʱ�䣺2019/7/6
�޸�ʱ�䣺2019/XX/XX
���ߣ���ʫ��
**********************************************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

typedef unsigned char U8;	//���������͵���������
typedef unsigned int  U16;
typedef unsigned long U32;

extern U8  flag, k;
extern U8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;
extern U8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;
extern U8 comdata;
extern U8 count, temp;
extern U8 outdata[5];  //���巢�͵��ֽ���	   
extern U8 indata[5];
extern U8 count, count_r;
extern U8 str[5];
extern U16 temp1, temp2;	  

#define FSCLK	11059200	//#define FSCLK	12000000
#define   Data_0_time    4


#endif

