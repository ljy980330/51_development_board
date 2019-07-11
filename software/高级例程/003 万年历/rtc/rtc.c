/*********************************************************************************************************
*���ƣ�rtc.c
*���ܣ�ʱ��ģ������ĺ���
����ʱ�䣺2019/XX/XX
�޸�ʱ�䣺2019/6/5
���ߣ�XXX
*********************************************************************************************************/
#include <STC12C5A.H>		
#include <intrins.h>  
#include "delay/delay.h"	
#include "oled/oled.h"		 
#include "rtc.h"
#define uint unsigned int	
#define uchar unsigned char

sbit key1=P0^2;	//����
sbit key2=P0^5;	//��
sbit key3=P0^6;	//��
sbit key4=P0^7;	//ȷ��
sbit laba=P3^7;	//����
bit laba_flag;									 //��������־λ
bit Open_Flag;									 //��������־λ
bit RTC_Save_Flag;							  	 //����ʱ���־λ
bit shezhi_display_flag;	
bit T0_Flag;									 //��ʱ��T01ms��־λ

#define Imax 14000//�˴�Ϊ����Ϊ11.0592ʱ��ȡֵ,   //ʱ�����	  //����ӿ�P3.3
#define Imin 8000 //��������Ƶ�ʵľ���ʱ,
#define Inum1 1450//Ҫ�ı���Ӧ��ȡֵ�� 
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
* �������ƣ� Ram_init()
* ���ܣ�     ʱ���ʼ��
******************************************************************************/
 void Ram_init()
{
	DS3231_Read_time();	                        //��ȡ ���ʱ��������
	if((!RTC_Data[6])&&(!RTC_Data[5])&&(!RTC_Data[4])&&(!RTC_Data[3])&&(!RTC_Data[2])&&(!RTC_Data[1])&&(!RTC_Data[0]))
	{
		RTC_Data[0]=0;       //��      			//���ʱ�������� ���λ��дλ
		RTC_Data[1]=0;		 //��
		RTC_Data[2]=12;		 //ʱ
		RTC_Data[3]=3;		 //��
		RTC_Data[4]=11;		 //��
		RTC_Data[5]=2;		 //��
		RTC_Data[6]=15;		 //��
		DS3231_write_time();                    //д�� ���ʱ��������
	}
	RTC_Set_ID=0;	
}

/**************************************************************************
* �������ƣ� interrupt_init()
* ���ܣ�     �������ʼ��
******************************************************************************/
 void main_init()
{
	
	EA=1;        				//�����ж�
	IT1=1;						//�½�����Ч
	EX1=1;						//�ⲿ�жϿ�
	ET1=1;						//��������

	TMOD=0x11;   				//��ʱ/������ �����ڷ�ʽ1
	TH1=0xff;					//50ms��ʱ����
	TL1=256-131; 				
	TR1=1;      				 //������ʱ/������ �ж� 

	TH0=0;						//����ֵ
	TL0=0;
	TR0=1;						//��ʼ��ʱ
	shezhi_display_flag=0;

	delay_ms(10);
	OLED_12864_Init();	
	delay_ms(10);	
	display1();					//��ʾ
	display2();					//��ʾ
	Ram_init();					//��ʼ��ʱ��
	DS3231_Init();				//ģ���ʼ��

}
/**************************************************************************
* ��������			��OLED_12864_Init
* ����				��OLED12864��ʼ��
******************************************************************************/

void OLED_12864_Init()
{
	delay_ms(500);						//��ʼ��֮ǰ����ʱ����Ҫ��
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
	OLED_Fill(0x00); 					//����													 
	OLED_SetPos(0,0);
}
/*******************************************************************************
* �� �� ��         : display1
* ��������		   : ��ʾ��ʽ1
*******************************************************************************/

void display1()
{
	display_buff[0] =2;
	display_buff[1] =0;
	display_buff[2] =RTC_Data[6]/10;
	display_buff[3] =RTC_Data[6]%10;		//��
	
	display_buff[4] =RTC_Data[4]/10;
	display_buff[5] =RTC_Data[4]%10;		//��
	
	display_buff[6] =RTC_Data[3]/10;
	display_buff[7] =RTC_Data[3]%10;		//��
	
	display_buff[8] =RTC_Data[2]/10;
	display_buff[9] =RTC_Data[2]%10;		//ʱ
	
	display_buff[10] =RTC_Data[1]/10;
	display_buff[11] =RTC_Data[1]%10;		//��
	
	display_buff[12] =RTC_Data[0]/10;
	display_buff[13] =RTC_Data[0]%10;		//��
	
	display_buff[14] =RTC_Data[5]/10;
	display_buff[15] =RTC_Data[5]%10;		//����

	display_buff[16] =RTC_Data[7]/10;
	display_buff[17] =RTC_Data[7]%10;		//�¶�
}	  
/*******************************************************************************
* �� �� ��         : display2
* ��������		   : ��ʾ��ʽ2
*******************************************************************************/

void display2()
{
	OLED_8x16Str(24, 0, display_buff[0]);// ��
	OLED_8x16Str(32, 0, display_buff[1]);
	OLED_8x16Str(40, 0, display_buff[2]);
	OLED_8x16Str(48, 0, display_buff[3]);
	OLED_8x16Str(56, 0, 10);			 // -
	OLED_8x16Str(64, 0, display_buff[4]);// ��
	OLED_8x16Str(72, 0, display_buff[5]);
	OLED_8x16Str(80, 0, 10);			 // -
	OLED_8x16Str(88, 0, display_buff[6]);// ��
	OLED_8x16Str(96, 0, display_buff[7]);

	OLED_16x32(0, 2, display_buff[8]);// ʱ
	OLED_16x32(16, 2, display_buff[9]);

	OLED_16x32(48, 2, display_buff[10]);// ��
	OLED_16x32(64, 2, display_buff[11]);

	OLED_16x32(96, 2, display_buff[12]);// ��
	OLED_16x32(112, 2, display_buff[13]);

	if(RTC_Data[0]/1%2==0)  OLED_16x32(32, 2, 10);// :
	else  OLED_16x32(32, 2, 21);
	if(RTC_Data[0]/1%2==0)  OLED_16x32(80, 2, 10);// :
	else  OLED_16x32(80, 2, 21);

	OLED_16x16CN(8, 6, 8);// ��
	OLED_16x16CN(24, 6, 9);// ��
	OLED_16x16CN(40, 6, display_buff[15]);// ��

	OLED_8x16Str(96, 6, display_buff[16]);// �¶�
	OLED_8x16Str(104, 6, display_buff[17]);
	OLED_16x16CN(112, 6, 10);// ��
}

/*******************************************************************************
* �� �� ��         : Time_Fun
* ��������		   : ʱ������ʱ����
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
* �� �� ��         : KeyDataProcess
* ��������		   : ��ֵ����
*******************************************************************************/

void KeyDataProcess()	//10mS����һ��
{	//������������
	if(key1==0)
	{
		delay_ms(10);
		if(key1==0)
		{
			while(!key1);
			laba_flag=1; //��������һ��
			shezhi_display_flag=1;
			RTC_Set_ID++;
			if(RTC_Set_ID>=8)
				RTC_Set_ID=1;
			Open_Flag=1;

			display1();
			if(RTC_Set_ID==1)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 16);//��
				OLED_16x16CN(48, 0, 18);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==2)
			{
				OLED_16x16CN(32, 0, 17);//��
				OLED_16x16CN(48, 0, 18);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==3)
			{
				OLED_16x16CN(32, 0, 11);//��
				OLED_16x16CN(48, 0, 9);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==4)
			{
				OLED_16x16CN(32, 0, 13);//С
				OLED_16x16CN(48, 0, 12);//ʱ
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				OLED_16x16CN(32, 0, 19);//��
				OLED_16x16CN(48, 0, 20);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==6)
			{
				OLED_16x16CN(32, 0, 21);//��
				OLED_16x16CN(48, 0, 22);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==7)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 8);//��
				OLED_16x16CN(48, 0, 9);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
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
			laba_flag=1;   //��������һ��
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6]<99)	  //��+
					RTC_Data[6]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4]<12)	  //��+
					RTC_Data[4]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3]<31)	  //��+
					RTC_Data[3]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2]<23)	  //ʱ+
					RTC_Data[2]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1]<59)	  //��+
					RTC_Data[1]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0]<59)	  //��+
					RTC_Data[0]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5]<7)	  //��+
					RTC_Data[5]++;
				display1();
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
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
			laba_flag=1;	  //��������һ��
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6])		   //��-
					RTC_Data[6]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4])		   //��-
					RTC_Data[4]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3])		   //��-
					RTC_Data[3]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2])		   //ʱ-
					RTC_Data[2]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1])		   //��-
					RTC_Data[1]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0])		   //��-
					RTC_Data[0]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5])		   //��-
					RTC_Data[5]--;
				display1();
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
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
			laba_flag=1;	  //��������һ��
			shezhi_display_flag=0;
			RTC_Save_Flag=1;
		}
	}
	//����ң�ز�������
	if(IrOK==1)						//����/ң����C��
	{
		if(Im[2]==0x0d)
		{
			laba_flag=1; //��������һ��
			shezhi_display_flag=1;
			RTC_Set_ID++;
			if(RTC_Set_ID>=8)
				RTC_Set_ID=1;
			Open_Flag=1;

			display1();
			if(RTC_Set_ID==1)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 16);//��
				OLED_16x16CN(48, 0, 18);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);	
			}
			else if(RTC_Set_ID==2)
			{
				OLED_16x16CN(32, 0, 17);//��
				OLED_16x16CN(48, 0, 18);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==3)
			{
				OLED_16x16CN(32, 0, 11);//��
				OLED_16x16CN(48, 0, 9);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==4)
			{
				OLED_16x16CN(32, 0, 13);//С
				OLED_16x16CN(48, 0, 12);//ʱ
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				OLED_16x16CN(32, 0, 19);//��
				OLED_16x16CN(48, 0, 20);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==6)
			{
				OLED_16x16CN(32, 0, 21);//��
				OLED_16x16CN(48, 0, 22);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
			}
			else if(RTC_Set_ID==7)
			{
				OLED_Fill(0x00);
				OLED_16x16CN(32, 0, 8);//��
				OLED_16x16CN(48, 0, 9);//��
				OLED_16x16CN(64, 0, 14);//��
				OLED_16x16CN(80, 0, 15);//��
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}

		else if(Im[2]==0x40)//ң����+��
		{
			laba_flag=1;   //��������һ��
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6]<99)	  //��+
					RTC_Data[6]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4]<12)	  //��+
					RTC_Data[4]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3]<31)	  //��+
					RTC_Data[3]++;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2]<23)	  //ʱ+
					RTC_Data[2]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1]<59)	  //��+
					RTC_Data[1]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0]<59)	  //��+
					RTC_Data[0]++;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5]<7)	  //��+
					RTC_Data[5]++;
				display1();
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}

		else if(Im[2]==0x19)//ң����-��
		{
			laba_flag=1;	  //��������һ��
			shezhi_display_flag=1;
			if(RTC_Set_ID==1)
			{
				if(RTC_Data[6])		   //��-
					RTC_Data[6]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==2)
			{
				if(RTC_Data[4])		   //��-
					RTC_Data[4]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==3)
			{
				if(RTC_Data[3])		   //��-
					RTC_Data[3]--;
				display1();
				OLED_16x32(0, 2, display_buff[2]);//��
				OLED_16x32(16, 2, display_buff[3]);
				OLED_16x32(32, 2, 11);//-
				OLED_16x32(48, 2, display_buff[4]);//��
				OLED_16x32(64, 2, display_buff[5]);
				OLED_16x32(80, 2, 11);//-
				OLED_16x32(96, 2, display_buff[6]);//��
				OLED_16x32(112, 2, display_buff[7]);
			}
			else if(RTC_Set_ID==4)
			{
				if(RTC_Data[2])		   //ʱ-
					RTC_Data[2]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==5)
			{
				if(RTC_Data[1])		   //��-
					RTC_Data[1]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==6)
			{
				if(RTC_Data[0])		   //��-
					RTC_Data[0]--;
				display1();
				OLED_16x32(0, 2, display_buff[8]);//ʱ
				OLED_16x32(16, 2, display_buff[9]);
				OLED_16x32(32, 2, 10);//:
				OLED_16x32(48, 2, display_buff[10]);//��
				OLED_16x32(64, 2, display_buff[11]);
				OLED_16x32(80, 2, 10);//:
				OLED_16x32(96, 2, display_buff[12]);//��
				OLED_16x32(112, 2, display_buff[13]);
			}
			else if(RTC_Set_ID==7)
			{
				if(RTC_Data[5])		   //��-
					RTC_Data[5]--;
				display1();
				OLED_16x32(40, 2, 12);//��
				OLED_16x32(56, 2, 13);//��
				OLED_16x32(72, 2, display_buff[15]+13);
			}
		}
		else if(Im[2]==0x15)//ң�������ż�
		{
			laba_flag=1;
			shezhi_display_flag=0;
			RTC_Save_Flag=1;
		}
		IrOK=0;
	}
}
/*******************************************************************************
* �� �� ��         : Time1
* ��������		   : 125us��ʱ �жϷ�����    
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
* �� �� ��         : intersvr1
* ��������		   : ������붨ʱ������  
*******************************************************************************/
void intersvr1() interrupt 2 using 1   //�ⲿ�жϽ������_�ⲿ�ж�1	  P3.3��
{
	Tc=TH0*256+TL0;//��ȡ�ж�ʱ����ʱ��
	TH0=0; 
	TL0=0;         //��ʱ�ж���������

	if((Tc>Imin)&&(Tc<Imax))
	{ 
		m=0;
		f=1;
		return;
	}              //�ҵ���ʼ��
	if(f==1)
	{
		if(Tc>Inum1&&Tc<Inum3) 
		{
			Im[m/8]=Im[m/8]>>1|0x80; m++; 
		}
		if(Tc>Inum2&&Tc<Inum1) 
		{
			Im[m/8]=Im[m/8]>>1; m++; //ȡ��
		}
		if(m==32) 
		{
			m=0;  
			f=0;
			if(Im[2]==~Im[3]) 
			{
				IrOK=1; 
			}
			else IrOK=0;   //ȡ����ɺ��ж϶����Ƿ���ȷ
		}
	}
}