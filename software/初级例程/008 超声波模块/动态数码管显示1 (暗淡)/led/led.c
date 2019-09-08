#include "led.h"
 unsigned char code fseg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
 unsigned char code segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
 unsigned char  disbuf[4]={0,0,0,0};
 //-----------------------------------------------------------------------------
// ����ԭ�ζ���
uchar LED[8];	//����LED��8λ��ʾ����

void LED4_Display ();			// LED��ʾ
void LED_OUT(uchar X);				// LED���ֽڴ�����λ����

unsigned char code LED_0F[];		// LED��ģ��

sbit DIO = P0^0;				//������������
sbit RCLK  = P0^1;				//ʱ�������źš�����������Ч
sbit SCLK = P0^2;				//�����źš���������������Ч


void LED4_Display ()
{
	uchar code *led_table;          // ���ָ��
	uchar i;
	//��ʾ��1λ
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK = 0;
	RCLK = 1;
	//��ʾ��2λ
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK = 0;
	RCLK = 1;
	//��ʾ��3λ
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK = 0;
	RCLK = 1;
	//��ʾ��4λ
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLK = 0;
	RCLK = 1;
}

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;
	}
}

unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

//
//***************************************************************
//��ʾ����ת������
void display(uint temp) 
 { 
    uchar qian,ge,shi,bai;
	qian = temp/1000;
    bai=temp/100%10;
    shi=temp%100/10;  
    ge=temp%10;
	
	LED[1]=qian;
	LED[2]=bai;
	LED[3]=shi;
	LED[4]=ge;
	
 }	

