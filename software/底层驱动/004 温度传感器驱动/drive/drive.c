/*********************************************************************************************************
*���ƣ�drive.c
*���ܣ�dht11���ݲɼ�
����ʱ�䣺2019/7/14
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#include "drive.h"

extern uint Temperature[3];
extern uint Humidity[2];
extern uchar Data_Receive[5];


/*******************************************************************************
* �� �� ��         : DHT_Collect
* ��������		   : �¶Ȳɼ�����
*******************************************************************************/

void DHT_Collect()
{
	uchar i,j;//forѭ������
	uchar t;//��ʱ�ж�
	uchar dat8=0;//һ�ζ�ȡ��8λ���ݣ���Ҫ��5��
	uint CheckValue=0;//У���
	
	DHT=0;//��������ʼ�ź�
	Delay_20ms();//����������������18ms
	DHT=1;//������������20~40us
	Delay_30us();
	
	t=80;//���ó�ʱ�ȴ�ʱ��
	while(DHT&&t--);//�ȴ�DHT11��������
	if(t==0)//��ʱ
	{
		DHT=1;
	}
	t=250;//���ó�ʱ�ȴ�ʱ��
	while(!DHT&&t--);//�ȴ�DHT11��������
	if(t==0)//��ʱ
	{
		DHT=1;
	}
	t=250;//���ó�ʱ�ȴ�ʱ��
	while(DHT&&t--);//�ȴ�DHT11��������
	if(t==0)//��ʱ
	{
		DHT=1;
	}

	for(j=0;j<5;j++)//5�ζ�ȡ
	{
		for(i=0;i<8;i++)//1��8��λ
		{
	//�ȴ�50us��ʼʱ϶
			t=150;//���ó�ʱ�ȴ�ʱ��
			while(!DHT&&t--);//�ȴ�DHT11��������
			if(t==0)//��ʱ
			{
				DHT=1;
			}
			t=0;//��¼ʱ������
			while(DHT&&++t);//�ȴ�����¼�ߵ�ƽ����ʱ��
			dat8<<=1;
			if(t>30)//�ߵ�ƽ����ʱ��ϳ�(70us)
			dat8+=1;//����ֵΪ1
		}
		Data_Receive[j]=dat8;
	}
	
	Delay_30us();//�ȴ�DHT11����50us
	Delay_30us();
	DHT=1;

	for(i=0;i<4;i++)
	{
		CheckValue+=Data_Receive[i];//����У��ֵ
	}
	if((uchar)CheckValue==Data_Receive[4])//�ȶ�
	{
		Temperature[0]=Data_Receive[2]/10;
		Temperature[1]=Data_Receive[2]%10;
		Temperature[2]=Data_Receive[3]%10;
		Humidity[0]=Data_Receive[0]/10;
		Humidity[1]=Data_Receive[0]%10;
	}
}
