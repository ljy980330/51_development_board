#include <STC12C5A.H>  
#include <stdio.h>		
#include "config.h"	
#include "delay/delay.h"
#include "Ultrasonic.h"		  
#include "led/led.h" 

sbit RX=P3^2;
sbit TX=P3^7;		 
uint time=0;
uint timer=0;
float   distance=0;
bit    flag =0;
/********************************************************/
void conut(void)
{
 time=TH0*256+TL0;
 TH0=0;
 TL0=0;
 distance=(time*1.88)/10;     //�������MM
 if((distance>=7000)||flag==1) //����������Χ��ʾ��-��
 {	 
    flag=0;
	display(7000);
	LED4_Display ();
 }
 else
 {
  	display(distance);
  	LED4_Display ();
  } 
}
void timer_Count(void)
{
	 TR0=1;			    //��������
     while(RX);			//��RXΪ1�������ȴ�
     TR0=0;				//�رռ���
     conut();			//����

}			   		  
/********************************************************/
void  startModule() 		         //T1�ж�����ɨ������ܺͼ�800MS����ģ��
{
  TX=1;			                 //800MS  ����һ��ģ��
  nop(20); 
  TX=0;
}

void init()
{
	TMOD=0x21;		   //��T0Ϊ��ʽ1��GATE=1��
	SCON=0x50;
	TH1=0xFD;
	TL1=0xFD;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //����T0�ж�
	TR1=1;			   //������ʱ��
	TI=1;
	
	EA=1;			   //�������ж�
}

void run()
{			  
	uint valA;
	delay_ms(60);
	RX=1;
    startModule();
    for(valA=7510;valA>0;valA--)
    {
       if(RX==1)
	   {
       timer_Count();
	   }
	 }
}
/********************************************************/
 void timer0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
	flag=1;							 //�ж������־
	RX=0;
}
