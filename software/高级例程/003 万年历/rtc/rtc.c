/*********************************************************************************************************
*名称：rtc.c
*功能：时钟模块包括的函数
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/
#include <STC12C5A.H>		
#include <intrins.h>  
#include "delay/delay.h"	
#include "oled/oled.h"		 
#include "rtc.h"
#define uint unsigned int	
#define uchar unsigned char

sbit key1=P0^2;	//设置
sbit key2=P0^5;	//加
sbit key3=P0^6;	//减
sbit key4=P0^7;	//确定
sbit laba=P3^7;	//喇叭
bit laba_flag;									 //蜂鸣器标志位
bit Open_Flag;									 //蜂鸣器标志位
bit RTC_Save_Flag;							  	 //设置时间标志位
bit shezhi_display_flag;	
bit T0_Flag;									 //定时器T01ms标志位

#define Imax 14000//此处为晶振为11.0592时的取值,   //时间计算	  //红外接口P3.3
#define Imin 8000 //如用其它频率的晶振时,
#define Inum1 1450//要改变相应的取值。 
#define Inum3 3000 
#define Inum2 700	

extern uchar display_buff[16];
extern uchar RTC_Data[8];
extern uchar RTC_Data1[8];
extern uchar RTC_Set_ID;
uchar f;
uchar IrOK;
unsigned long m,Tc;
uchar Im[4]={0x00,0x00,0x00,0x00};
/**************************************************************************
* 函数名称： Ram_init()
* 功能：     时间初始化
******************************************************************************/
 void Ram_init()
{
	DS3231_Read_time();	                        //读取 秒分时日月周年
	if((!RTC_Data[6])&&(!RTC_Data[5])&&(!RTC_Data[4])&&(!RTC_Data[3])&&(!RTC_Data[2])&&(!RTC_Data[1])&&(!RTC_Data[0]))
	{
		RTC_Data[0]=0;       //秒      			//秒分时日月周年 最低位读写位
		RTC_Data[1]=0;		 //分
		RTC_Data[2]=12;		 //时
		RTC_Data[3]=3;		 //日
		RTC_Data[4]=11;		 //月
		RTC_Data[5]=2;		 //周
		RTC_Data[6]=15;		 //年
		DS3231_write_time();                    //写入 秒分时日月周年
	}
	RTC_Set_ID=0;	
}

/**************************************************************************
* 函数名称： interrupt_init()
* 功能：     主程序初始化
******************************************************************************/
 void main_init()
{
	
	EA=1;        				//开总中断
	IT1=1;						//下降沿有效
	EX1=1;						//外部中断开
	ET1=1;						//打开允许开关

	TMOD=0x11;   				//定时/计数器 工作于方式1
	TH1=0xff;					//50ms定时常数
	TL1=256-131; 				
	TR1=1;      				 //启动定时/计数器 中断 

	TH0=0;						//赋初值
	TL0=0;
	TR0=1;						//开始计时
	shezhi_display_flag=0;

	delay_ms(10);
	OLED_12864_Init();	
	delay_ms(10);	
	display1();					//显示
	display2();					//显示
	Ram_init();					//初始化时间
	DS3231_Init();				//模块初始化

}
/**************************************************************************
* 函数名称			：OLED_12864_Init
* 功能				：OLED12864初始化
******************************************************************************/

void OLED_12864_Init()
{
	delay_ms(500);						//初始化之前的延时很重要！
	OLED_12864_Write_commomand(0xae);
	OLED_12864_Write_commomand(0x00);
	OLED_12864_Write_commomand(0x10);
	OLED_12864_Write_commomand(0x40);
	OLED_12864_Write_commomand(0x81);
	OLED_12864_Write_commomand(0xcf);
	OLED_12864_Write_commomand(0xa1);
	OLED_12864_Write_commomand(0xc8);
	OLED_12864_Write_commomand(0xa6);
	OLED_12864_Write_commomand(0xa8);
	OLED_12864_Write_commomand(0x3f);
	OLED_12864_Write_commomand(0xd3);
	OLED_12864_Write_commomand(0x00);
	OLED_12864_Write_commomand(0xd5);
	OLED_12864_Write_commomand(0x80);
	OLED_12864_Write_commomand(0xd9);
	OLED_12864_Write_commomand(0xf1);
	OLED_12864_Write_commomand(0xda);
	OLED_12864_Write_commomand(0x12);
	OLED_12864_Write_commomand(0xdb);
	OLED_12864_Write_commomand(0x40);
	OLED_12864_Write_commomand(0x20);
	OLED_12864_Write_commomand(0x02);
	OLED_12864_Write_commomand(0x8d);
	OLED_12864_Write_commomand(0x14);
	OLED_12864_Write_commomand(0xa4);
	OLED_12864_Write_commomand(0xa6); 
	OLED_12864_Write_commomand(0xaf);
	OLED_Fill(0x00); 					//清屏													 
	OLED_SetPos(0,0);
}
/*******************************************************************************
* 函 数 名         : display1
* 函数功能		   : 显示方式1
*******************************************************************************/

void display1()
{
	display_buff[0] =2;
	display_buff[1] =0;
	display_buff[2] =RTC_Data[6]/10;
	display_buff[3] =RTC_Data[6]%10;		//年
	
	display_buff[4] =RTC_Data[4]/10;
	display_buff[5] =RTC_Data[4]%10;		//月
	
	display_buff[6] =RTC_Data[3]/10;
	display_buff[7] =RTC_Data[3]%10;		//日
	
	display_buff[8] =RTC_Data[2]/10;
	display_buff[9] =RTC_Data[2]%10;		//时
	
	display_buff[10] =RTC_Data[1]/10;
	display_buff[11] =RTC_Data[1]%10;		//分
	
	display_buff[12] =RTC_Data[0]/10;
	display_buff[13] =RTC_Data[0]%10;		//秒
	
	display_buff[14] =RTC_Data[5]/10;
	display_buff[15] =RTC_Data[5]%10;		//星期

	display_buff[16] =RTC_Data[7]/10;
	display_buff[17] =RTC_Data[7]%10;		//温度
}	  
/*******************************************************************************
* 函 数 名         : display2
* 函数功能		   : 显示方式2
*******************************************************************************/

void display2()
{
	OLED_8x16Str(24, 0, display_buff[0]);// 年
	OLED_8x16Str(32, 0, display_buff[1]);
	OLED_8x16Str(40, 0, display_buff[2]);
	OLED_8x16Str(48, 0, display_buff[3]);
	OLED_8x16Str(56, 0, 10);			 // -
	OLED_8x16Str(64, 0, display_buff[4]);// 月
	OLED_8x16Str(72, 0, display_buff[5]);
	OLED_8x16Str(80, 0, 10);			 // -
	OLED_8x16Str(88, 0, display_buff[6]);// 日
	OLED_8x16Str(96, 0, display_buff[7]);

	OLED_16x32(0, 2, display_buff[8]);// 时
	OLED_16x32(16, 2, display_buff[9]);

	OLED_16x32(48, 2, display_buff[10]);// 分
	OLED_16x32(64, 2, display_buff[11]);

	OLED_16x32(96, 2, display_buff[12]);// 秒
	OLED_16x32(112, 2, display_buff[13]);

	if(RTC_Data[0]/1%2==0)  OLED_16x32(32, 2, 10);// :
	else  OLED_16x32(32, 2, 21);
	if(RTC_Data[0]/1%2==0)  OLED_16x32(80, 2, 10);// :
	else  OLED_16x32(80, 2, 21);

	OLED_16x16CN(8, 6, 8);// 星
	OLED_16x16CN(24, 6, 9);// 期
	OLED_16x16CN(40, 6, display_buff[15]);// ？

	OLED_8x16Str(96, 6, display_buff[16]);// 温度
	OLED_8x16Str(104, 6, display_buff[17]);
	OLED_16x16CN(112, 6, 10);// ℃
}

/*******************************************************************************
* 函 数 名         : Time_Fun
* 函数功能		   : 时基、走时函数
*******************************************************************************/
void Time_Fun()
{
	if(T0_Flag)
	{		 
		static	uchar T10Ms_Cnt=0,T200Ms_Cnt=0;
		static uchar Buzz_On_Cnt=0,RTC_Save_Cnt=0;	
		T0_Flag=0;
		
		T10Ms_Cnt++;	
		if(T10Ms_Cnt>=5)
		{
			T10Ms_Cnt=0;
			KeyDataProcess();
			if(laba_flag)
			{
				Buzz_On_Cnt++;
				if(Buzz_On_Cnt>=10)
				{
					laba_flag=0;
					Buzz_On_Cnt=0;
				}
			}	
			if(RTC_Save_Flag)
			{
				RTC_Save_Cnt++;
				if(RTC_Save_Cnt>=50)
				{
					RTC_Save_Cnt=0;
					RTC_Save_Flag=0;
					RTC_Set_ID=0;
					DS3231_write_time();
				}
			}
		}
		T200Ms_Cnt++;
		if(T200Ms_Cnt>=100&&shezhi_display_flag==0)
		{
			T200Ms_Cnt=0;		
			if(!RTC_Set_ID)
				DS3231_Read_time();
			display1();
			display2();
		}
	
	}
}

/*******************************************************************************
* 函 数 名         : KeyDataProcess
* 函数功能		   : 键值处理
*******************************************************************************/

void KeyDataProcess()	//10mS处理一次
{	//按键操作部分
	if(key1==0)
	{
		delay_ms(10);
		if(key1==0)
		{
			while(!key1);
			laba_flag=1; //蜂鸣器响一声
			shezhi_display_flag=1;
			RTC_Set_ID++;
			if(RTC_Set_ID>=8)
				RTC_Set_ID=1;
			Open_Flag=1;

			display1();
			if(RTC_Set_ID==1)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 16);//年
				OLED_16x16CN(48, 0, 18);//份
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==2)
			{
				OLED_16x16CN(32, 0, 17);//月
				OLED_16x16CN(48, 0, 18);//份
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==3)
			{
				OLED_16x16CN(32, 0, 11);//日
				OLED_16x16CN(48, 0, 9);//期
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==4)
			{
				OLED_16x16CN(32, 0, 13);//小
				OLED_16x16CN(48, 0, 12);//时
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				OLED_16x16CN(32, 0, 19);//分
				OLED_16x16CN(48, 0, 20);//钟
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==6)
			{
				OLED_16x16CN(32, 0, 21);//秒
				OLED_16x16CN(48, 0, 22);//数
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==7)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 8);//星
				OLED_16x16CN(48, 0, 9);//期
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}
	}
	if(key2==0)
	{
		delay_ms(10);
		if(key2==0)
		{
			while(!key2);
			laba_flag=1;   //蜂鸣器响一声
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6]<99)	  //年+
					RTC_Data[6]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4]<12)	  //月+
					RTC_Data[4]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3]<31)	  //日+
					RTC_Data[3]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2]<23)	  //时+
					RTC_Data[2]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1]<59)	  //分+
					RTC_Data[1]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0]<59)	  //秒+
					RTC_Data[0]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5]<7)	  //周+
					RTC_Data[5]++;
				display1();
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}
	}
	if(key3==0)
	{
		delay_ms(10);
		if(key3==0)
		{
			while(!key3);
			laba_flag=1;	  //蜂鸣器响一声
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6])		   //年-
					RTC_Data[6]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4])		   //月-
					RTC_Data[4]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3])		   //日-
					RTC_Data[3]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2])		   //时-
					RTC_Data[2]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1])		   //分-
					RTC_Data[1]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0])		   //秒-
					RTC_Data[0]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5])		   //周-
					RTC_Data[5]--;
				display1();
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}
	}
	if(key4==0)
	{
		delay_ms(10);
		if(key4==0)
		{
			while(!key4);
			laba_flag=1;	  //蜂鸣器响一声
			shezhi_display_flag=0;
			RTC_Save_Flag=1;
		}
	}
	//红外遥控操作部分
	if(IrOK==1)						//设置/遥控器C键
	{
		if(Im[2]==0x0d)
		{
			laba_flag=1; //蜂鸣器响一声
			shezhi_display_flag=1;
			RTC_Set_ID++;
			if(RTC_Set_ID>=8)
				RTC_Set_ID=1;
			Open_Flag=1;

			display1();
			if(RTC_Set_ID==1)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 16);//年
				OLED_16x16CN(48, 0, 18);//份
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==2)
			{
				OLED_16x16CN(32, 0, 17);//月
				OLED_16x16CN(48, 0, 18);//份
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==3)
			{
				OLED_16x16CN(32, 0, 11);//日
				OLED_16x16CN(48, 0, 9);//期
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==4)
			{
				OLED_16x16CN(32, 0, 13);//小
				OLED_16x16CN(48, 0, 12);//时
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				OLED_16x16CN(32, 0, 19);//分
				OLED_16x16CN(48, 0, 20);//钟
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==6)
			{
				OLED_16x16CN(32, 0, 21);//秒
				OLED_16x16CN(48, 0, 22);//数
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
			}
			else if(RTC_Set_ID==7)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 8);//星
				OLED_16x16CN(48, 0, 9);//期
				OLED_16x16CN(64, 0, 14);//设
				OLED_16x16CN(80, 0, 15);//置
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}

		else if(Im[2]==0x40)//遥控器+键
		{
			laba_flag=1;   //蜂鸣器响一声
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6]<99)	  //年+
					RTC_Data[6]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4]<12)	  //月+
					RTC_Data[4]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3]<31)	  //日+
					RTC_Data[3]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2]<23)	  //时+
					RTC_Data[2]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1]<59)	  //分+
					RTC_Data[1]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0]<59)	  //秒+
					RTC_Data[0]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5]<7)	  //周+
					RTC_Data[5]++;
				display1();
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}

		else if(Im[2]==0x19)//遥控器-键
		{
			laba_flag=1;	  //蜂鸣器响一声
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6])		   //年-
					RTC_Data[6]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4])		   //月-
					RTC_Data[4]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3])		   //日-
					RTC_Data[3]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//年
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//月
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//日
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2])		   //时-
					RTC_Data[2]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1])		   //分-
					RTC_Data[1]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0])		   //秒-
					RTC_Data[0]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//时
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//分
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//秒
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5])		   //周-
					RTC_Data[5]--;
				display1();
				OLED_16x32(40, 2, 12);//星
				OLED_16x32(56, 2, 13);//期
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}
		else if(Im[2]==0x15)//遥控器播放键
		{
			laba_flag=1;
			shezhi_display_flag=0;
			RTC_Save_Flag=1;
		}
		IrOK=0;
	}
}
/*******************************************************************************
* 函 数 名         : Time1
* 函数功能		   : 125us定时 中断服务函数    
*******************************************************************************/
void Time1() interrupt 3
{
	static uchar timecount;
	TF1=0;
	TH1=0xff;//125us
	TL1=256-110;
	
	timecount++;
	if(timecount>=16)//1ms
	{
		timecount=0;
		T0_Flag=1;
	}
	if(laba_flag)
	{
		laba=~laba;
	}
	else
	laba=0;
}
/*******************************************************************************
* 函 数 名         : intersvr1
* 函数功能		   : 红外解码定时器程序  
*******************************************************************************/
void intersvr1() interrupt 2 using 1   //外部中断解码程序_外部中断1	  P3.3口
{
	Tc=TH0*256+TL0;//提取中断时间间隔时长
	TH0=0; 
	TL0=0;         //定时中断重新置零

	if((Tc>Imin)&&(Tc<Imax))
	{ 
		m=0;
		f=1;
		return;
	}              //找到启始码
	if(f==1)
	{
		if(Tc>Inum1&&Tc<Inum3) 
		{
			Im[m/8]=Im[m/8]>>1|0x80; m++; 
		}
		if(Tc>Inum2&&Tc<Inum1) 
		{
			Im[m/8]=Im[m/8]>>1; m++; //取码
		}
		if(m==32) 
		{
			m=0;  
			f=0;
			if(Im[2]==~Im[3]) 
			{
				IrOK=1; 
			}
			else IrOK=0;   //取码完成后判断读码是否正确
		}
	}
}