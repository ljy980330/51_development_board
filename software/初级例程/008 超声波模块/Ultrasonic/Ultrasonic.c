//������ģ�����
//���� �� Z H
//ʱ�� 2015/11/29
//Trig  = P3^6
//Echo  = P3^7
#include <STC12C5A.H>			  
#include "config.h"	  			  
#include "delay/delay.h"	 
#include <led/led.h> 
extern uchar LED[8];	//����LED��8λ��ʾ����

uint distance;
uint test =0;		
uint time = 0;
uint timeH = 0;
uint timeL = 0;
uint succeed_flag;
 
 
sbit Trig  = P3^7;
sbit Echo  = P3^2;
 
//
void delay(uint z)
{
 uint x,y;
  for(x=z;x>0;x--)
  for(y=125;y>0;y--);
}
//
void delay_20us()
 { 
    uchar a ;
    for(a=0;a<100;a++);
 }
//***************************************************************
//��ʾ����ת������
void display(uint temp) 
 { 
    uchar qian,ge,shi,bai;
	qian = temp/1000;
    bai=temp/100%10;
    shi=temp%100/10;  
    ge=temp%10;
	
	LED[4]=qian;
	LED[3]=bai;
	LED[2]=shi;
	LED[1]=ge;
	
 }	 
 void init()
 {
    Trig=0;       //��������������������
    EA=1;         //�����ж�0 
    TMOD=0x10;    //��ʱ��1��16λ������ʽ 
 }
 void run()
 {		
		EA=0;           //�����ж�
	    Trig=1;         //�����������
	    delay_20us();   //��ʱ20us
	    Trig=0;         //����һ��20us������
	    while(Echo==0); //�ȴ�Echo�ز����ű�ߵ�ƽ
	    succeed_flag=0; //������ɹ���־
	    EA=1; 
	    EX0=1;          //���ⲿ�ж�0
	    TH1=0;          //��ʱ��1����
	    TL1=0;          //��ʱ��1����
	    TF1=0;          //���������־
	    TR1=1;          //������ʱ��1
	    delay(20);   	
	    TR1=0;          //�رն�ʱ��1
	    EX0=0;          //�ر��ⲿ�ж�0
	   if(succeed_flag==1)
	   {   
	      time=timeH*256+timeL;
	      distance=time*0.172;  //����
	   }                         
	  if(succeed_flag==0)
	   {
	      distance=0;                    //û�лز�������
	      test = !test;                  //���ԵƱ仯
	    }		 		  
      display(distance);
	  LED4_Display ();
 }
//***************************************************************
//�ⲿ�ж�0�������жϻز���ƽ
void exter()  interrupt 0   // �ⲿ�ж�0��0��
 {   
     timeH =TH1;    //ȡ����ʱ����ֵ
     timeL =TL1;    //ȡ����ʱ����ֵ
     succeed_flag=1;//���ɹ������ı�־
     EX0=0;         //�ر��ⲿ�ж�	 
 }
//****************************************************************
//��ʱ��1�ж�,��������������ʱ
void timer1() interrupt 3  //
{
     TH1=0;
     TL1=0;
 }	