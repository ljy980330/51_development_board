/*********************************************************************************************************
*���ƣ�data_read.c
*���ܣ���ȡ��ʪ���Լ�У��λ����
����ʱ�䣺2019/7/6
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
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
		while((DATA) && flag++);	//��ʱ������forѭ��
	   	if(flag == 1) break; //�ж�����λ��0����1
	   	 				 // ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 comdata <<= 1;  
		 comdata |= temp;        //0
	   }
}


void RH(void)
{
	//��������18ms 
	DATA = low;
	Delay_ms(180);
	DATA = high;
	//������������������ ������ʱ20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź� 
	DATA = high;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	if( !DATA )		 //T !	  
	{
		flag = 2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
		while(( !DATA ) && flag++);
	    flag = 2;
	 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	   	while(( DATA )&& flag++);
	 //���ݽ���״̬		 
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

	 //����У�� 
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
	RH(); //������ʪ�ȶ�ȡ�ӳ��� 
	   //������ʾ���� 
	   str[0] = RH_data_H;
	   str[1] = RH_data_L;
	   str[2] = T_data_H;
	   str[3] = T_data_L;
	   str[4] = checkdata;
	   SendData(str) ;  //���͵�����  
	   //��ȡģ���������ڲ���С�� 2S 
	   Delay_ms(2500);
}