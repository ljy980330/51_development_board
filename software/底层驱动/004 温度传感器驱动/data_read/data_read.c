/*********************************************************************************************************
*名称：data_read.c
*功能：读取温湿度以及校验位数据
创建时间：2019/7/6
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "data_read.h"

SendData(U8 *a)
{
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	count = 1;
	SBUF = outdata[0];
	return 0;
}

void  COM(void)
{
     U8 i;
          
     for(i=0; i<8; i++)	   
	 {
		
	  	flag = 2;	
	   	while((!DATA) && flag++);
		Delay_10us();
		Delay_10us();
		Delay_10us();
	  	temp = 0;

	    if( DATA ) temp = 1;

		flag = 2;
		while((DATA) && flag++);	//超时则跳出for循环
	   	if(flag == 1) break; //判断数据位是0还是1
	   	 				 // 如果高电平高过预定0高电平值则数据位为 1 
	   	 comdata <<= 1;  
		 comdata |= temp;        //0
	   }
}


void RH(void)
{
	//主机拉低18ms 
	DATA = low;
	Delay_ms(180);
	DATA = high;
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//主机设为输入 判断从机响应信号 
	DATA = high;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	if( !DATA )		 //T !	  
	{
		flag = 2;
	 //判断从机是否发出 80us 的低电平响应信号是否结束	 
		while(( !DATA ) && flag++);
	    flag = 2;
	 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
	   	while(( DATA )&& flag++);
	 //数据接收状态		 
	   	COM();
	   	RH_data_H_temp = comdata;
	   	COM();
	   	RH_data_L_temp = comdata;
	   	COM();
	   	T_data_H_temp = comdata;
	   	COM();
	   	T_data_L_temp = comdata;
	   	COM();
	   	checkdata_temp = comdata;
	   	DATA = high;

	 //数据校验 
	   	temp = (T_data_H_temp + T_data_L_temp + RH_data_H_temp + RH_data_L_temp);
	   	if(temp == checkdata_temp)
	   	{
	   		RH_data_H = RH_data_H_temp;
	   	  	RH_data_L = RH_data_L_temp;
		  	T_data_H = T_data_H_temp;
	   	  	T_data_L = T_data_L_temp;
	   	  	checkdata = checkdata_temp;
	   	}
	}
}


void Text(void)
{
	RH(); //调用温湿度读取子程序 
	   //串口显示程序 
	   str[0] = RH_data_H;
	   str[1] = RH_data_L;
	   str[2] = T_data_H;
	   str[3] = T_data_L;
	   str[4] = checkdata;
	   SendData(str) ;  //发送到串口  
	   //读取模块数据周期不易小于 2S 
	   Delay_ms(2500);
}