 /***********************************************/
/* Ãû³Æ£ºADC.c
/* ¹¦ÄÜ£ºÓÃÓÚAD×ª»»µÄ³õÊ¼»¯
		 ½«AD×ª»»ºóµÄÊý¾ÝÓÃÊýÂë¹ÜÊä³ö
   ÐÞ¸ÄÊ±¼ä£º2019Äê7ÔÂ27ÈÕ
   ×÷Õß£ºÔøË¼Èã	               
/***********************************************/

#include <STC12C5A.H>  
#include "ADC.h"
#include "config.h"
sbit DIO = P0^0;				//´®ÐÐÊý¾ÝÊäÈë
sbit RCLK  = P0^1;				//Ê±ÖÓÂö³åÐÅºÅ¡ª¡ªÉÏÉýÑØÓÐÐ§
sbit SCLK = P0^2;				//´òÈëÐÅºÅ¡ª¡ª¡ª¡ªÉÏÉýÑØÓÐÐ§
uchar LED[10];	//ÓÃÓÚLEDÏÔÊ¾»º´æ
void LED_OUT(uchar X);
int date;		 //´¢´æAD×ª»»²úÉúµÄ8Î»Êý¾Ý



/***************************************/
/*	³õÊ¼»¯AD¼Ä´æÆ÷ 
	´ò¿ªADC×ª»»µçÔ´ 90¸ö»úÆ÷ÖÜÆÚ×ª»»Ò»´Î
	P1^0¿Ú×÷ÎªAD×ª»»¿Ú 
    º¯ÊýÃû£ºInitADC       
/***************************************/
void InitADC()
{
	
	P1ASF=0x02;//P1.0×÷ÎªADÊ¹ÓÃ
	
	ADC_CONTR=0xe1;//ADCµçÔ´´ò¿ª,Ã¿90¸öÊ±ÖÓ×ª»»1´Î,CHSÑ¡ÔñP1.0
	
	//Ä¬ÈÏÎª8Î»Ä£Ê½
	
	ADC_RES=0;//ÇåÁãÊý¾Ý¼Ä´æÆ÷
	
	//³õÊ¼»¯½áÊø
	
	ADC_CONTR|=0x08;//ADC_STARTÖÃ1¿ªÊ¼×ª»»
	
	while(!(ADC_CONTR&0x10));//µÈ´ý×ª»»Íê³É(ADC_FLAG=1)
	date=ADC_RES;//½«Êý¾Ý´¢´æÔÚdateÖÐ
	  
}



/************************************/
/*             ÊýÂë¹Ü¶ÎÂë
	   º¯ÊýÃû £º  LED_0F
/************************************/
uchar code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90
};




/************************************/
/*             ÊýÂë¹ÜÏÔÊ¾
	    º¯ÊýÃû £º Display
/************************************/
void Display ()
{
	uchar code *led_table;          // ²é±íÖ¸Õë
	uchar i;
	uchar ge,shi,bai;	//ÊýÂë¹ÜÏÔÊ¾µÄ¸öÎ»Ê®Î»°ÙÎ»
	ge = (uchar)(date%10);
	shi = (uchar)((date/10)%10);
	bai = (uchar)((date/100)%10); 
								  
	//ÏÔÊ¾µÚ°Ù»
	led_table = LED_0F+LED[ge];
	i = *led_table;

	LED_OUT(i);		  //´«ÈëÒªÏÔÊ¾µÄ×Ö·û
	LED_OUT(0x04);	//´«ÈëÒªÏÔÊ¾µÄÎ»Êý	

	RCLK = 0;
	RCLK = 1;	  //Ê±ÖÓÂö³åÐÅºÅ¡ª¡ªÉÏÉýÑØÓÐÐ§	

	//ÏÔÊ¾µÚÊ®Î»
	led_table = LED_0F+LED[shi];  
	i = *led_table;

	LED_OUT(i);		 //´«ÈëÒªÏÔÊ¾µÄ×Ö·û
	LED_OUT(0x02);	//´«ÈëÒªÏÔÊ¾µÄÎ»Êý	

	RCLK = 0;
	RCLK = 1;	 //Ê±ÖÓÂö³åÐÅºÅ¡ª¡ªÉÏÉýÑØÓÐÐ§
	  
	//ÏÔÊ¾µÚ¸öÎ»
	led_table = LED_0F + LED[bai];
	i = *led_table;

	LED_OUT(i);	//´«ÈëÒªÏÔÊ¾µÄ×Ö·û		
	LED_OUT(0x01); //´«ÈëÒªÏÔÊ¾µÄÎ»Êý		

	RCLK = 0;
	RCLK = 1;	//Ê±ÖÓÂö³åÐÅºÅ¡ª¡ªÉÏÉýÑØÓÐÐ§
}



/************************************/
/*          ´«ÈëÊý¾Ýµ½ÊýÂë¹Ü
	   º¯ÊýÃû £ºLED_OUT
/************************************/
void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;	  //´òÈëÐÅºÅ¡ª¡ª¡ª¡ªÉÏÉýÑØÓÐÐ§
	}
}
/************************************/
/*     ³õÊ¼»¯º¯Êý
	   º¯ÊýÃû £ºinit
/************************************/

void init()
{
	LED[0]=0;
	LED[1]=1;
	LED[2]=2;
	LED[3]=3;
	LED[4]=4;
	LED[5]=5;
	LED[6]=6;
	LED[7]=7;
	LED[8]=8;
	LED[9]=9;//ÊýÂë¹Ü»º´æÊý¾Ý ÓÃÓÚ¶¨Î»ÒªÊäÈëµ½led_tableµÄµØÖ·
	
}


