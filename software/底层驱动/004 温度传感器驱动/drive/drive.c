/*********************************************************************************************************
*名称：drive.c
*功能：dht11数据采集
创建时间：2019/7/14
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "drive.h"

extern uint Temperature[3];
extern uint Humidity[2];
extern uchar Data_Receive[5];


/*******************************************************************************
* 函 数 名         : DHT_Collect
* 函数功能		   : 温度采集函数
*******************************************************************************/

void DHT_Collect()
{
	uchar i,j;//for循环变量
	uchar t;//超时判断
	uchar dat8=0;//一次读取的8位数据，需要读5次
	uint CheckValue=0;//校验和
	
	DHT=0;//主机发起始信号
	Delay_20ms();//主机拉低总线至少18ms
	DHT=1;//主机拉高总线20~40us
	Delay_30us();
	
	t=80;//设置超时等待时间
	while(DHT&&t--);//等待DHT11拉低总线
	if(t==0)//超时
	{
		DHT=1;
	}
	t=250;//设置超时等待时间
	while(!DHT&&t--);//等待DHT11拉高总线
	if(t==0)//超时
	{
		DHT=1;
	}
	t=250;//设置超时等待时间
	while(DHT&&t--);//等待DHT11拉低总线
	if(t==0)//超时
	{
		DHT=1;
	}

	for(j=0;j<5;j++)//5次读取
	{
		for(i=0;i<8;i++)//1次8个位
		{
	//等待50us开始时隙
			t=150;//设置超时等待时间
			while(!DHT&&t--);//等待DHT11拉高总线
			if(t==0)//超时
			{
				DHT=1;
			}
			t=0;//记录时间清零
			while(DHT&&++t);//等待并记录高电平持续时间
			dat8<<=1;
			if(t>30)//高电平持续时间较长(70us)
			dat8+=1;//传输值为1
		}
		Data_Receive[j]=dat8;
	}
	
	Delay_30us();//等待DHT11拉低50us
	Delay_30us();
	DHT=1;

	for(i=0;i<4;i++)
	{
		CheckValue+=Data_Receive[i];//计算校验值
	}
	if((uchar)CheckValue==Data_Receive[4])//比对
	{
		Temperature[0]=Data_Receive[2]/10;
		Temperature[1]=Data_Receive[2]%10;
		Temperature[2]=Data_Receive[3]%10;
		Humidity[0]=Data_Receive[0]/10;
		Humidity[1]=Data_Receive[0]%10;
	}
}
