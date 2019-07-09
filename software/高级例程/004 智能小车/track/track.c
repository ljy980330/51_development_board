/*********************************************************************************************************
*名称：track.c
*功能：寻迹功能所用到的函数
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/
#include <STC12C5A.H>
#include "delay/delay.h"
#include "pwm/pwm.h"
#include "color/color.h"
#include "voice/voice.h"	
#include "flame/flame.h"
#include "config.h"
//OUT开头的变量代表循迹模块状态
sbit OUT1 = P1^0;
sbit OUT2 = P1^1;
sbit OUT3 = P1^2;
sbit OUT4 = P1^3;
sbit OUT5 = P1^4;
sbit OUT6 = P1^5;
sbit OUT7 = P1^6;
sbit OUT  = P1;
#define flag1 /*1110111*/ (OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1) 
#define flag2 /*1110011或者1111011*/((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==0)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==0)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))
#define flag3 /*1100111或者1101111*/((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==0))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==0))
#define flag4 (OUT2==0)&&(OUT3==0)&&((OUT4==0)||(OUT5==0))
#define flag5 ((OUT3==0)||(OUT4==0))&&(OUT5==0)&&(OUT6==0)
#define flag6 (OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1)
#define flag7 (OUT5==1)&&(OUT4==0)&&(OUT3==0)&&(OUT2==1)
#define flag8 (OUT5==0)&&(OUT4==0)&&(OUT3==0)&&(OUT2==1)
#define flag9 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))//向左后转停止标准
#define flag10 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||(((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1)))//向右后转停止标准
#define flag11 (OUT1==1)&&(OUT2==1)&&((OUT3==0)||(OUT4==0)||(OUT5==0))&&(OUT6==1)&&(OUT7==1)
#define flag12 (OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1)
#define flag13 ((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==0)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==0)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==0)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==1)&&(OUT7==1))
#define flag14 ((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==0)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==1)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==0)&&(OUT6==0)&&(OUT7==1))||((OUT1==1)&&(OUT2==1)&&(OUT3==1)&&(OUT4==1)&&(OUT5==1)&&(OUT6==0)&&(OUT7==1))

int i=0,a=0;	//路段
int term=0;	   //当前执行模式
extern int left;   //左转速率
extern int right;  //右转速率

void run();			  //主程序启动
void gohuadu();       //从华广到花都广场
void gobaiyun();      //从花都广场到白云山
void gohuanan();      //从白云山到华南植物园
void gobuowu();       //从华南植物园到广东博物馆
void gogzta();	      //从广东博物馆到广州塔
void gozhongs();      //从广州塔到中山纪念馆
void gohuanpu();      //从中山纪念馆到黄埔军校
void gochanglong();   //从黄埔军校到长隆动物园
void goshanxia();	  //从长隆动物园到上下九步行街
void goliuxihe();	  //从上下九步行街到流溪河国家森林公园
void gohuanguang();   //从流溪河国家森林公园到华广
void go_and_adjust(); //直走加调整
void go_and_adjust1();//慢速直走加调整
void go_and_adjust2();//慢速直走加调整方式2
void go_and_adjust3();//慢速直走加调整方式2
void goleft();	 //左转
void goleft1();	 //左转方式2
void goright();	 //右转
void goright1(); //右转方式2
void goback1();	 //后转
void goback2();	 //后转方式2
void goback3();	 //后转方式3
void goback4();	 //后转方式4


/*******************************************************************************
* 函 数 名         : init
* 函数功能		   : 主函数初始化
*******************************************************************************/
void init()
{
	Int0Init();//外部中断初始化
	Int1Init();
	UART_Init();
	Time1();
	goahead();
	delay_ms(800);
}					 
/*******************************************************************************
* 函 数 名         : run
* 函数功能		   : 主函数启动
*******************************************************************************/
void run()
{
	init();
	while(1)
	{ 
     if(i==0){gohuadu();}     //从华广到花都广场
	 if(i==1){gobaiyun();}    //从花都广场到白云山
	 if(i==2){gohuanan();}    //从白云山到华南植物园
	 if(i==3){gobuowu();}     //从华南植物园到广东博物馆
	 if(i==4){gogzta();}	  //从广东博物馆到广州塔
	 if(i==5){gozhongs();}    //从广州塔到中山纪念馆
	 if(i==6){gohuanpu();}    //从中山纪念馆到黄埔军校
	 if(i==7){gochanglong();} //从黄埔军校到长隆动物园
	 if(i==8){goshanxia();}	  //从长隆动物园到上下九步行街
	 if(i==9){goliuxihe();}	  //从上下九步行街到流溪河国家森林公园
	 if(i==10){gohuanguang();}//从流溪河国家森林公园到华广
	}
}

/*******************************************************************************
* 函 数 名         : gohuadu
* 函数功能		   : 从华广到花都广场
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
* 函 数 名         : gobaiyun
* 函数功能		   : 从华广到花都白云山
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
	 if(term==2)  //从花都广场到白云山的第二个路口的特殊情况
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
* 函 数 名         : gohuanan
* 函数功能		   : 从白云山到华南植物园
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
* 函 数 名         : gobuowu
* 函数功能		   : 从华南植物园到广东博物馆
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
* 函 数 名         : gogzta
* 函数功能		   : 从广东博物馆到广州塔
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
* 函 数 名         : gozhongs
* 函数功能		   : 从广州塔到中山纪念馆
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
		case 1:turnleft();delay_ms(3000);goleft();term++;while(1){go_and_adjust1();if(flag1==1){break;}}left=45;right=40;left1=1;left2=0;right1=1;right2=0;delay_ms(200);break;//广州塔的标志有问题
		case 2:go_and_adjust3();break;
		case 3:turnright();delay_ms(3000);goright();term++;break;
		case 4:go_and_adjust1();break;
		case 5:a=6;Send_24bits(255,255,100);goahead();delay_ms(1000);stop();six();i++;term=0;turnback3();delay_ms(3000);goback4();break;
	 }
}	 
/*******************************************************************************
* 函 数 名         : gohuanpu
* 函数功能		   : 从中山纪念馆到黄埔军校
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
* 函 数 名         : gochanglong
* 函数功能		   : 从黄埔到长隆动物园
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
		case 5:a=8;Send_24bits(255,0,0);goahead1();delay_ms(2000);stop();eight();turnback2();delay_ms(4500);i++;term=0;goback2();break;//向左后转
	 }
}  
/*******************************************************************************
* 函 数 名         : goshanxia
* 函数功能		   : 从长隆动物园到上下九步行街
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
* 函 数 名         : goliuxihe
* 函数功能		   : 从上下九步行街到流溪河国家森林公园
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
* 函 数 名         : gohuanguang
* 函数功能		   : 从流溪河国家森林公园到华广
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
* 函 数 名         : go_and_adjust
* 函数功能		   : 直线直走
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
* 函 数 名         : go_and_adjust1
* 函数功能		   : 慢速直走加调整
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
* 函 数 名         : go_and_adjust2
* 函数功能		   : 慢速直走加调整
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
* 函 数 名         : gobaiyun
* 函数功能		   : 慢速直走加调整
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
* 函 数 名         : goleft
* 函数功能		   : 左转
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
* 函 数 名         : goleft1
* 函数功能		   : 左转方式2
*******************************************************************************/
/*void goleft1()
{
     while(1)
	 {
	  wentleft();	//小车向左前方前进
	  if(flag1==1)
	  {
	    break;
	  }
	 }
}	 */
  
/*******************************************************************************
* 函 数 名         : goright
* 函数功能		   : 右转
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
* 函 数 名         : goright
* 函数功能		   : 右转方式2，出白云山的特殊情况
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
* 函 数 名         : goback1
* 函数功能		   : 后转
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
* 函 数 名         : goback2
* 函数功能		   : 后转方式2
*******************************************************************************/
void goback2()	   //后转
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
* 函 数 名         : goback3
* 函数功能		   : 后转方式3
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
* 函 数 名         : goback4
* 函数功能		   : 后转方式4
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
