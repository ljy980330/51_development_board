/*********************************************************************************************************
*名称：buzzer.h
*功能：蜂鸣器所用到函数
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄彦钊
*********************************************************************************************************/
#include "buzzer.h"	   
sbit  buzz=P2^7;
uint n=0;				 
uint p,m;   //m为频率常数变量    
uint i=0;  				
uint n; //n为节拍数变量
uint code music_tab[186]; 	
uint code music_tab[] ={   
0x18, 0x30, 0x1C , 0x10, //格式为: 频率常数, 节拍常数, 频率常数, 节拍常数,    
0x20, 0x40, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x10,   
0x1C, 0x10, 0x18 , 0x40,   
0x1C, 0x20, 0x20 , 0x20,   
0x1C, 0x20, 0x18 , 0x20,   
0x20, 0x80, 0xFF , 0x20,   
0x30, 0x1C, 0x10 , 0x18,   
0x20, 0x15, 0x20 , 0x1C,   
0x20, 0x20, 0x20 , 0x26,   
0x40, 0x20, 0x20 , 0x2B,   
0x20, 0x26, 0x20 , 0x20,   
0x20, 0x30, 0x80 , 0xFF,   
0x20, 0x20, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x20, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x20, 0x15 , 0x20,   
0x1C, 0x20, 0x20 , 0x20,   
0x26, 0x40, 0x20 , 0x20,   
0x2B, 0x20, 0x26 , 0x20,   
0x20, 0x20, 0x30 , 0x80,   
0x20, 0x30, 0x1C , 0x10,   
0x20, 0x10, 0x1C , 0x10,   
0x20, 0x20, 0x26 , 0x20,   
0x2B, 0x20, 0x30 , 0x20,   
0x2B, 0x40, 0x20 , 0x15,   
0x1F, 0x05, 0x20 , 0x10,   
0x1C, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x20, 0x15 , 0x20,   
0x1C, 0x20, 0x20 , 0x20,   
0x26, 0x40, 0x20 , 0x20,   
0x2B, 0x20, 0x26 , 0x20,   
0x20, 0x20, 0x30 , 0x30,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x40, 0x1C , 0x20,   
0x20, 0x20, 0x26 , 0x40,   
0x13, 0x60, 0x18 , 0x20,   
0x15, 0x40, 0x13 , 0x40,   
0x18, 0x80, 0x00   
};
			  
/*******************************************************************************
* 函 数 名         : init
* 函数功能		   : 定时器初始化
*******************************************************************************/ 
void init()
{ 
	TMOD&=0x0f;   
	TMOD|=0x01;   
	TH0=0xd8;TL0=0xef;   
	IE=0x82;   
}
/*******************************************************************************
* 函 数 名         : run
* 函数功能		   : 使蜂鸣器发出声音
*******************************************************************************/ 

void run()	  
{ 
   play: 
    while(1)   
    {   
     a:p=music_tab[i];   
       if(p==0x00)       { i=0, delay_us(1000); goto play;}     //如果碰到结束符,延时1秒,回到开始再来一遍，程序回到paly标志的地方    
       else if(p==0xff)  { i=i+1;delay_us(100),TR0=0; goto a;}  //若碰到休止符,延时100ms,继续取下一音符，程序回到a标志的地方    
            else         {m=music_tab[i++], n=music_tab[i++];}  //取频率常数 和 节拍常数    
             TR0=1;                                             //开定时器1    
           while(n!=0) buzz=~buzz,delay_us(3*m);                //等待节拍完成, 通过P1口输出音频(可多声道哦!)    
       TR0=0;                                             //关定时器1    
    }   
}		   
															  
/*******************************************************************************
* 函 数 名         : time0
* 函数功能		   : 采用中断0 控制节拍
*******************************************************************************/ 
 void time0()  interrupt 1       
{  TH0=0xd8;   
   TL0=0xef;   
   n--;   
}   