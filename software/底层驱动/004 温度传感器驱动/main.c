/*********************************************************************************************************
*名称：温湿度驱动
*功能：串口发送温湿度数据
创建时间：2019/7/10
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "includes.h"

U8  flag, k;
U8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;
U8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;
U8  comdata;
U8  count, temp;
U8  outdata[5];  //定义发送的字节数	   
U8  indata[5];
U8  count, count_r = 0;
U8  str[5] = {"RS232"};
U16 temp1, temp2; 


int main()
{
	UART_Init();
	Delay_ms(1);
	
	while(1)
	{
	   Text();
	}	
}


void UART() interrupt 4 using 2
{
	U8 InPut3;
	if(TI == 1) //发送中断	  
	{
		TI = 0;
		if(count != 5) //发送完5位数据	 
		{
			SBUF = outdata[count];
			count++;
		}
	}

	if(RI==1)	 //接收中断		  
	{	
		InPut3 = SBUF;
		indata[count_r] = InPut3;
		count_r++;
		RI=0;								 
		if(count_r == 5)//接收完4位数据 
		{ 
		//数据接收完毕处理
			count_r = 0;
			str[0] = indata[0];
		 	str[1] = indata[1];
		  	str[2] = indata[2];
			str[3] = indata[3];
			str[4] = indata[4];
			P0 = 0;
		}
	}
}