/*********************************************************************************************************
*���ƣ�data_read.c
*���ܣ���ȡ��ʪ���Լ�У��λ����
����ʱ�䣺2019/7/10
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#include "data_read.h"

extern rec_dat[9];

void DHT11_start()
{
   Data=1;
   Delay_us(2);
   Data=0;
   Delay_ms(20);   //��ʱ18ms����
   Data=1;
   Delay_us(30);
}

U8 DHT11_rec_byte()	//����һ���ֽ�
{
	U8 i, dat = 0;
	for(i=0; i<8; i++)
	{
		while(!Data);
		Delay_us(8);
		dat <<= 1;
		if(Data == 1) dat += 1;
		while(Data);
	}
	return dat;
}

void DHT11_receive()      //����40λ������
{
    U8 R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //�ȴ�����     
        Delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        Delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
        /*���ݴ���������ʾ*/
        rec_dat[0]='0'+(RH/10);
        rec_dat[1]='0'+(RH%10);
        rec_dat[2]='R';
        rec_dat[3]='H';
        rec_dat[4]=' ';
        rec_dat[5]=' ';
        rec_dat[6]='0'+(TH/10);
        rec_dat[7]='0'+(TH%10);
        rec_dat[8]='C';
    }
}

