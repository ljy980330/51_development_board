/*********************************************************************************************************
*名称：config.h
*功能：数据类型以及通用变量的声明和定义
创建时间：2019/7/6
修改时间：2019/XX/XX
作者：李诗琪
**********************************************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

typedef unsigned char U8;	//新数据类型的声明定义
typedef unsigned int  U16;
typedef unsigned long U32;

extern U8  flag, k;
extern U8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;
extern U8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;
extern U8 comdata;
extern U8 count, temp;
extern U8 outdata[5];  //定义发送的字节数	   
extern U8 indata[5];
extern U8 count, count_r;
extern U8 str[5];
extern U16 temp1, temp2;	  

#define FSCLK	11059200	//#define FSCLK	12000000
#define   Data_0_time    4


#endif

