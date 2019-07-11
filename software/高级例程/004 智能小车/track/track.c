/*********************************************************************************************************
*���ƣ�track.c
*���ܣ�Ѱ���������õ��ĺ���
����ʱ�䣺2019/7/8
�޸�ʱ�䣺2019/7/8
���ߣ�������
*********************************************************************************************************/
#include <STC12C5A.H>
#include "delay/delay.h"
#include "pwm/pwm.h"
#include "color/color.h"
#include "voice/voice.h"	
#include "flame/flame.h"
#include "config.h"
//OUT��ͷ�ı�������ѭ��ģ��״̬
sbit OUT1 = P1^0;
sbit OUT2 = P1^1;
sbit OUT3 = P1^2;
sbit OUT4 = P1^3;
sbit OUT5 = P1^4;
sbit OUT6 = P1^5;
sbit OUT7 = P1^6;
sbit OUT  = P1;
#define flag1 /*1110111*/ (OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1) 
#define flag2 /*1110011����1111011*/((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==0)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==0)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))
#define flag3 /*1100111����1101111*/((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==0))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==0))
#define flag4 (OUT2==0)&&(OUT3==0)&&((OUT4==0)||(OUT5==0))
#define flag5 ((OUT3==0)||(OUT4==0))&&(OUT5==0)&&(OUT6==0)
#define flag6 (OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1)
#define flag7 (OUT5==1)&&(OUT4==0)&&(OUT3==0)&&(OUT2==1)
#define flag8 (OUT5==0)&&(OUT4==0)&&(OUT3==0)&&(OUT2==1)
#define flag9 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))//�����תֹͣ��׼
#define flag10 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||(((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1)))//���Һ�תֹͣ��׼
#define flag11 (OUT1==1)&&(OUT2==1)&&((OUT3==0)||(OUT4==0)||(OUT5==0))&&(OUT6==1)&&(OUT7==1)
#define flag12 (OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1)
#define flag13 ((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))
#define flag14 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==1))

int i=0,a=0;	//·��
int term=0;	   //��ǰִ��ģʽ
extern int left;   //��ת����
extern int right;  //��ת����

void run();			  //����������
void gohuadu();       //�ӻ��㵽�����㳡
void gobaiyun();      //�ӻ����㳡������ɽ
void gohuanan();      //�Ӱ���ɽ������ֲ��԰
void gobuowu();       //�ӻ���ֲ��԰���㶫�����
void gogzta();	      //�ӹ㶫����ݵ�������
void gozhongs();      //�ӹ���������ɽ�����
void gohuanpu();      //����ɽ����ݵ����Ҿ�У
void gochanglong();   //�ӻ��Ҿ�У����¡����԰
void goshanxia();	  //�ӳ�¡����԰�����¾Ų��н�
void goliuxihe();	  //�����¾Ų��нֵ���Ϫ�ӹ���ɭ�ֹ�԰
void gohuanguang();   //����Ϫ�ӹ���ɭ�ֹ�԰������
void go_and_adjust(); //ֱ�߼ӵ���
void go_and_adjust1();//����ֱ�߼ӵ���
void go_and_adjust2();//����ֱ�߼ӵ�����ʽ2
void go_and_adjust3();//����ֱ�߼ӵ�����ʽ2
void goleft();	 //��ת
void goleft1();	 //��ת��ʽ2
void goright();	 //��ת
void goright1(); //��ת��ʽ2
void goback1();	 //��ת
void goback2();	 //��ת��ʽ2
void goback3();	 //��ת��ʽ3
void goback4();	 //��ת��ʽ4


/*******************************************************************************
* �� �� ��         : init
* ��������		   : ��������ʼ��
*******************************************************************************/
void init()
{
	Int0Init();//�ⲿ�жϳ�ʼ��
	Int1Init();
	UART_Init();
	Time1();
	goahead();
	delay_ms(800);
}					 
/*******************************************************************************
* �� �� ��         : run
* ��������		   : ����������
*******************************************************************************/
void run()
{
	init();
	while(1)
	{ 
     if(i==0){gohuadu();}     //�ӻ��㵽�����㳡
	 if(i==1){gobaiyun();}    //�ӻ����㳡������ɽ
	 if(i==2){gohuanan();}    //�Ӱ���ɽ������ֲ��԰
	 if(i==3){gobuowu();}     //�ӻ���ֲ��԰���㶫�����
	 if(i==4){gogzta();}	  //�ӹ㶫����ݵ�������
	 if(i==5){gozhongs();}    //�ӹ���������ɽ�����
	 if(i==6){gohuanpu();}    //����ɽ����ݵ����Ҿ�У
	 if(i==7){gochanglong();} //�ӻ��Ҿ�У����¡����԰
	 if(i==8){goshanxia();}	  //�ӳ�¡����԰�����¾Ų��н�
	 if(i==9){goliuxihe();}	  //�����¾Ų��нֵ���Ϫ�ӹ���ɭ�ֹ�԰
	 if(i==10){gohuanguang();}//����Ϫ�ӹ���ɭ�ֹ�԰������
	}
}

/*******************************************************************************
* �� �� ��         : gohuadu
* ��������		   : �ӻ��㵽�����㳡
*******************************************************************************/
void gohuadu()	     
{
	 
	 if(flag4||flag5)
	 {
	   term++;
	 }
	 if(term==4)
	 {
	   if(OUT7==0)
	  {
	   	term=6;
		while(1)
		{
		   go_and_adjust1();
		   if(flag1||flag2||flag3)
		   {
		     break;
		   }
		}
	  }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();Send_24bits(240,0,240);break;
		case 1:term++;turnleft();delay_ms(2000);goleft(); break;// stop();delay_ms(1000);
		case 2:go_and_adjust();break;
		case 3:term++;turnright();delay_ms(3000);goright();break;// stop();delay_ms(1000);
		case 4:go_and_adjust();break;
		case 5:term++;turnleft();delay_ms(2000);goleft(); break; //stop();delay_ms(1000);
		case 6:go_and_adjust1();break;
		case 7:a=1;Send_24bits(0,0,0);goahead();delay_ms(1000);stop();one();i++;term=0;turnback1();delay_ms(4100);goback1();break; //stop();delay_ms(1000);
	 }
}

/*******************************************************************************
* �� �� ��         : gobaiyun
* ��������		   : �ӻ��㵽��������ɽ
*******************************************************************************/
void gobaiyun()		
{
	 
	 if(term<4)
	 {
	  if((flag4||flag5)==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 if(term==2)  //�ӻ����㳡������ɽ�ĵڶ���·�ڵ��������
	 {
	 if(OUT7==0)
	 {
	   	term=4;
		while(1)
		{
		   go_and_adjust1();
		   if(flag1||flag2||flag3)
		   {
		     break;
		   }
		}
	 }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();break;
		case 1:term++;turnleft();delay_ms(2000);goleft();break;//stop();delay_ms(1000);
		case 2:go_and_adjust();break;
		case 3:term++;turnright();delay_ms(3000);goright();break;//stop();delay_ms(1000);
		case 4:go_and_adjust1();break;
		case 5:a=2;Send_24bits(255,0,0);goahead();delay_ms(1000);stop();two();i++;term=0;turnback1();delay_ms(4100);goback1();break;//stop();delay_ms(1000);
	 }
}	   
/*******************************************************************************
* �� �� ��         : gohuanan
* ��������		   : �Ӱ���ɽ������ֲ��԰
*******************************************************************************/
void gohuanan()		  
{
	 if(term<4)
	 {
	  if((flag4||flag5)==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();break;
		case 1:turnright();delay_ms(3000);goright1();term++;break;//stop();delay_ms(1000);
		case 2:go_and_adjust();break;
		case 3:turnleft();delay_ms(3000);goleft();term++;break;//stop();delay_ms(1000);
		case 4:go_and_adjust1();break;		   
		case 5:a=3;Send_24bits(50,255,50);goahead();delay_ms(1000);stop();third();i++;term=0;turnback1();delay_ms(4100);goback1();break;//stop();delay_ms(1000);
	 }
}	 
/*******************************************************************************
* �� �� ��         : gobuowu
* ��������		   : �ӻ���ֲ��԰���㶫�����
*******************************************************************************/
void gobuowu()	
{
     
	 if(term<4)
	 {
	  if((flag4||flag5)==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();break;
		case 1:turnleft();delay_ms(3000);goleft();term++;break;//stop();delay_ms(1000);
		case 2:go_and_adjust();break;
		case 3:turnleft();delay_ms(3000);goleft();term++;break;//stop();delay_ms(1000);
		case 4:go_and_adjust1();break;
		case 5:a=4;Send_24bits(0,197,255);goahead();delay_ms(1000);stop();four();i++;term=0;turnback1();delay_ms(4100);goback1();break;//stop();delay_ms(1000);
	 }
}	
/*******************************************************************************
* �� �� ��         : gogzta
* ��������		   : �ӹ㶫����ݵ�������
*******************************************************************************/
void gogzta()	  
{
     
	 if(term<4)
	 {
	  if((flag4||flag5)==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();break;
		case 1:turnleft();delay_ms(3000);goleft();term++;break;//stop();delay_ms(1000);
		case 2:go_and_adjust();break;
		case 3:turnleft();delay_ms(3000);goleft();term++;break;//stop();delay_ms(1000);
		case 4:go_and_adjust1();break;
		case 5:a=5;Send_24bits(0,0,255);goahead();delay_ms(1000);stop();five();i++;term=0;turnback1();delay_ms(3500);goback1();break;//stop();delay_ms(1000);
	 }
}	
/*******************************************************************************
* �� �� ��         : gozhongs
* ��������		   : �ӹ���������ɽ�����
*******************************************************************************/
void gozhongs()
{									
	 if(term<4)
	 {
	  if(((flag4)||(flag5))==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)  
	 {
	    case 0:go_and_adjust1();break;
		case 1:turnleft();delay_ms(3000);goleft();term++;while(1){go_and_adjust1();if(flag1==1){break;}}left=45;right=40;left1=1;left2=0;right1=1;right2=0;delay_ms(200);break;//�������ı�־������
		case 2:go_and_adjust3();break;
		case 3:turnright();delay_ms(3000);goright();term++;break;
		case 4:go_and_adjust1();break;
		case 5:a=6;Send_24bits(255,255,100);goahead();delay_ms(1000);stop();six();i++;term=0;turnback3();delay_ms(3000);goback4();break;
	 }
}	 
/*******************************************************************************
* �� �� ��         : gohuanpu
* ��������		   : ����ɽ����ݵ����Ҿ�У
*******************************************************************************/
void gohuanpu()	 
{
	 if(term<4)
	 {
	  if((flag4||flag5||((OUT4==0)&&(OUT5==0)&&(OUT3==0)))==1)
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))
	  {
	    term++;
	  }
	 }
	 switch(term)
	 {
	    case 0:go_and_adjust2();break;
		case 1:goahead();delay_ms(1200);while(1){goahead1();if(flag1||flag2||flag3){break;}}term++;break;
		case 2:go_and_adjust1();break;
		case 3:turnleft();delay_ms(3000);goleft();while(1){go_and_adjust1();if(flag1==1){break;}}term++;break;
		case 4:go_and_adjust1();break;
		case 5:a=7;Send_24bits(0,197,255);goahead();delay_ms(1000);stop();seven();i++;term=0;turnback3();delay_ms(3000);goback4();left=39;right=45;left1=1;left2=0;right1=1;right2=0;delay_ms(400);break;
	 }
}	
/*******************************************************************************
* �� �� ��         : gochanglong
* ��������		   : �ӻ��ҵ���¡����԰
*******************************************************************************/
void gochanglong()   
{
     go_and_adjust2();
	 
	 if(term<4)
	 {
	  if((OUT4==0)&&(OUT3==0)&&(OUT2==0))
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)
	 {
	    case 0:break;
		case 1:stop();delay_ms(1000);wentleft();delay_ms(1500);term++;while(1){go_and_adjust1();if(flag1){break;}}break;
		case 2:break;
		case 3:stop();delay_ms(1000);wentleft();delay_ms(1500);term++;while(1){go_and_adjust1();if(flag1){break;}}break;
		case 4:break;
		case 5:a=8;Send_24bits(255,0,0);goahead1();delay_ms(2000);stop();eight();turnback2();delay_ms(4500);i++;term=0;goback2();break;//�����ת
	 }
}  
/*******************************************************************************
* �� �� ��         : goshanxia
* ��������		   : �ӳ�¡����԰�����¾Ų��н�
*******************************************************************************/
void goshanxia() 
{
     go_and_adjust1();
	 if(term<6)
	 {
	  if((flag4||flag5)==1)
	  {
	    term++;
	  }
	 }
	 if(term==6)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)
	 {
	    case 0:if(OUT1==0){term=2;while(1){go_and_adjust1();if(flag1==1){break;}}}break;
		case 1:turnleft();delay_ms(3200);term++;goleft();break;
		case 2:break;
		case 3:turnright();delay_ms(3200);term++;goright();break;
		case 4:break;
		case 5:turnright();delay_ms(3200);term++;goright();break;
		case 6:break;
		case 7:a=9;Send_24bits(50,255,50);goahead();delay_ms(2000);stop();nine();turnback3();delay_ms(3000);i++;term=0;goback4();break;
	 }
}  
/*******************************************************************************
* �� �� ��         : goliuxihe
* ��������		   : �����¾Ų��нֵ���Ϫ�ӹ���ɭ�ֹ�԰
*******************************************************************************/
void goliuxihe()	 
{
     go_and_adjust1();
	 if(term<6)
	 {
	  if(((OUT4==0)&&(OUT3==0)&&(OUT2==0))||((OUT4==0)&&(OUT3==0)&&(OUT5==0))||((OUT4==0)&&(OUT5==0)&&(OUT6==0)))
	  {
	    term++;
	  }
	 }
	 if(term==6)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)
	 {
	    case 0:break;
		case 1:turnleft();delay_ms(3200);term++;goleft();break;
		case 2:go_and_adjust2();break;
		case 3:goahead1();delay_ms(1200);term++;while(1){go_and_adjust1();if(flag1){break;}};break;
		case 4:break;
		case 5:turnleft();delay_ms(2000);term++;goleft();break;
		case 6:break;
		case 7:stop();a=10;Send_24bits(0,0,250);ten();turnback1();delay_ms(5000);i++;term=0;goback1();break;
	 }
}	
/*******************************************************************************
* �� �� ��         : gohuanguang
* ��������		   : ����Ϫ�ӹ���ɭ�ֹ�԰������
*******************************************************************************/
void gohuanguang() 
{
     go_and_adjust1();
	 if(term<4)
	 {
	  if(((OUT4==0)&&(OUT3==0)&&(OUT2==0))||((OUT4==0)&&(OUT5==0)&&(OUT6==0)))
	  {
	    term++;
	  }
	 }
	 if(term==4)
	 {
	   if((flag11||flag3||flag2)==0)
	  {
	    term++;
	  }
	 }
	 switch(term)
	 {
        case 0:break;
	    case 1:stop();delay_ms(1000);wentleft();delay_ms(1000);term++;while(1){go_and_adjust1();if(flag1){break;}};break;
		case 2:break;
		case 3:turnleft();delay_ms(3000);term++;goleft();break;
		case 4:break;
		case 5:stop();a=11;Send_24bits(240,0,240);eleven();stop();while(1);
	 }
}	
/*******************************************************************************
* �� �� ��         : go_and_adjust
* ��������		   : ֱ��ֱ��
*******************************************************************************/
void go_and_adjust() 
{
     if(flag1==1)
	 {
	   	goahead1();
	 }
	 if(flag2)
	 {
	    offsetright();
	 }
	 if(flag3||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)||(OUT6==0)||(OUT7==0)))
	 {
	    offsetleft();
	 }
}  
/*******************************************************************************
* �� �� ��         : go_and_adjust1
* ��������		   : ����ֱ�߼ӵ���
*******************************************************************************/
void go_and_adjust1() 
{
     if(flag1==1)
	 {
	   	goahead();
	 }
	 if(flag2==1)
	 {
	    offsetright();
	 }
	 if(flag3==1)
	 {
	    offsetleft();
	 }
}	 
/*******************************************************************************
* �� �� ��         : go_and_adjust2
* ��������		   : ����ֱ�߼ӵ���
*******************************************************************************/
void go_and_adjust2()
{
     if(flag1==1)
	 {
	   	goahead();
	 }
	 if(((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1)))
	 {
	    offsetright1();
	 }
	 if(((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1)))
	 {
	    offsetleft1();
	 }
}  
/*******************************************************************************
* �� �� ��         : gobaiyun
* ��������		   : ����ֱ�߼ӵ���
*******************************************************************************/
void go_and_adjust3()
{
     if(flag1==1)
	 {
	   	goahead1();
	 }
	 if(flag2==1)
	 {
	    offsetright();
	 }
	 if(flag3==1)
	 {
	    offsetleft();
	 }
} 	
/*******************************************************************************
* �� �� ��         : goleft
* ��������		   : ��ת
*******************************************************************************/
void goleft()	   
{
     while(1)
	 {
	  turnleft();
	  if(flag1||flag13)
	  {
	    break;
	  }
	 }
	 left=39;
	 right=41;
	 left1=1;
	 left2=0;
	 right1=0;
	 right2=1;
	 delay_ms(200);	
	 left=42;
	 right=42;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
	 delay_ms(400); 
} 			 
/*******************************************************************************
* �� �� ��         : goleft1
* ��������		   : ��ת��ʽ2
*******************************************************************************/
/*void goleft1()
{
     while(1)
	 {
	  wentleft();	//С������ǰ��ǰ��
	  if(flag1==1)
	  {
	    break;
	  }
	 }
}	 */
  
/*******************************************************************************
* �� �� ��         : goright
* ��������		   : ��ת
*******************************************************************************/
void goright()	   
{
     while(1)
	 {
	  turnright();
	  if(flag1||flag14){break;}
	 }
	 left=43;
	 right=43;
	 left1=0;
	 left2=1;
	 right1=1;
	 right2=0;
	 delay_ms(200);
	 left=41;
	 right=43;
	 left1=1;
	 left2=0;
	 right1=1;
	 right2=0;
	 delay_ms(400);
	 	 
} 	 								   
/*******************************************************************************
* �� �� ��         : goright
* ��������		   : ��ת��ʽ2��������ɽ���������
*******************************************************************************/
void goright1()	 
{
     while(1)
	 {
	   turnright();
	   if(flag1||flag3||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==0))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==0)))
	   {
	     break;
	   }
	 } 
}  
/*******************************************************************************
* �� �� ��         : goback1
* ��������		   : ��ת
*******************************************************************************/
void goback1()	   
{
     while(1)
	 {
	  turnback1();
	  if(flag10==1)
	  {
	    break;
	  }
	 }
	 stop();
	 delay_ms(600);
	 while(1)
	 {
	  left=48;
	  right=45;
	  left1=0;
	  left2=1;
	  right1=1;
	  right2=0;
	  if(flag1==1)
	  {break;}
	 }
	  left=51;
	  right=54;
	  left1=1;
	  left2=0;
	  right1=1;
	  right2=0;
	  delay_ms(600);
}

/*******************************************************************************
* �� �� ��         : goback2
* ��������		   : ��ת��ʽ2
*******************************************************************************/
void goback2()	   //��ת
{
     while(1)
	 {
	  turnback2();
	  if(flag9==1)
	  {
	    break;
	  }
	 }
	 stop();
	 delay_ms(600);
	 while(1)
	 {
	  left=40;
	  right=57;
	  left1=1;
	  left2=0;
	  right1=0;
	  right2=1;
	  if(flag1==1)
	  {break;}
	 }
	  left=51;
	  right=52;
	  left1=1;
	  left2=0;
	  right1=1;
	  right2=0;
	  delay_ms(600);	 
}

/*******************************************************************************
* �� �� ��         : goback3
* ��������		   : ��ת��ʽ3
*******************************************************************************/
/*void goback3()
{
     while(1)
	 {
	  turnback1();
	  
	  if(flag10||((OUT4==0)&&(OUT5==0)&&(OUT6==0)))
	  {
	    stop();
		delay_ms(1000);
		if(flag10)
	   {
	    left=0;
	    right=45;
	    left1=1;
	    left2=0;
	    right1=1;
	    right2=0;
	    delay_ms(400);
	   }
		break;
	  }
	 }
	 
	 
}  */

/*******************************************************************************
* �� �� ��         : goback4
* ��������		   : ��ת��ʽ4
*******************************************************************************/
void goback4()
{
     while(1)
	 {
	  turnback1();
	  if(flag10==1)
	  {
	    break;
	  }
	 }
	 stop();
	 delay_ms(600);
	 while(1)
	 {
	  left=48;
	  right=45;
	  left1=0;
	  left2=1;
	  right1=1;
	  right2=0;
	  if(flag1==1)
	  {break;}
	 }
	  left=51;
	  right=52;
	  left1=1;
	  left2=0;
	  right1=1;
	  right2=0;
	  delay_ms(600);
}
