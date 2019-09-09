/*********************************************************************************************************
*名称：drive.c
*功能：dht11数据采集和系统初始化
创建时间：2019/7/14
修改时间：2019/7/30
作者：黄彦钊
**********************************************************************************************************/

#include "drive.h"
extern uint Temperature[3];
extern uint Humidity[2];
extern uchar Data_Receive[5];

sbit DHT = P2^0;

/*******************************************************************************
* 函 数 名         : OLED_Display
* 函数功能		   : OLED显示驱动函数
*******************************************************************************/

void OLED_Display()
{
	
	OLED_DataDisplay_T(56,4,Temperature);//在指定位置显示温度
	OLED_DataDisplay_H(56,6,Humidity);//在指定位置显示湿度
}

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
//	delay_ms(20);//主机拉低总线至少18ms
	Delay_20ms();//主机拉低总线至少18ms
	
	DHT=1;//主机拉高总线20~40us
//	delay_us(30);
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
		//printf("dat8 is : %c\n", dat8);
	}
	
//	delay_us(30);//等待DHT11拉低50us
//	delay_us(30);
	Delay_30us();
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

/*******************************************************************************
* 函 数 名         : sys_init
* 函数功能		   : 系统初始化函数
*******************************************************************************/

void sys_init()
{
	uchar i;
	
	//YLED=1;
	//RLED=1;
	OLED_Init(); //OLED初始化
	OLED_CLS();//清屏
	for(i = 0;i < 8;i++)//通过点整显示汉字 -- i表示字表数组的位置
	{
		OLED_P16x16Ch(i*16,0,i);
	}
	OLED_FormLine(0,3);//显示一条横线
	OLED_FormTemp(8,4);//显示温度文字
	OLED_FormHumi(16,6);//显示湿度文字
	OLED_AnyChar_16X16(96,4,TempChar);//在行4（每行高16像素），列96像素位置显示摄氏度℃字符
	OLED_AnyChar_8X16(88,6,HumiChar);//在行6（每行高16像素），列88像素位置显示百分号%字符
	OLED_AnyChar_8X16(72,4,PointChar);//在行4（每行高16像素），列72像素位置显示冒号:字符
}