/*********************************************************************************************************
*���ƣ���ʪ������
*���ܣ����ڷ�����ʪ������
����ʱ�䣺2019/7/10
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#include "includes.h"

U8  flag, k;
U8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;
U8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;
U8  comdata;
U8  count, temp;
U8  outdata[5];  //���巢�͵��ֽ���	   
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
	if(TI == 1) //�����ж�	  
	{
		TI = 0;
		if(count != 5) //������5λ����	 
		{
			SBUF = outdata[count];
			count++;
		}
	}

	if(RI==1)	 //�����ж�		  
	{	
		InPut3 = SBUF;
		indata[count_r] = InPut3;
		count_r++;
		RI=0;								 
		if(count_r == 5)//������4λ���� 
		{ 
		//���ݽ�����ϴ���
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