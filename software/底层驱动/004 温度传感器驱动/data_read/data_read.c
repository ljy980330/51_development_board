/*********************************************************************************************************
*名称：data_read.c
*功能：读取温湿度以及校验位数据
创建时间：2019/7/10
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "data_read.h"

extern rec_dat[9];

void DHT11_start()
{
   Data=1;
   delay_us(2);
   Data=0;
   delay_ms(20);   //延时18ms以上
   Data=1;
   delay_us(30);
}

uchar DHT11_rec_byte()	//接收一个字节
{
	uchar i, dat = 0;
	for(i=0; i<8; i++)
	{
		while(!Data);
		delay_us(8);
		dat <<= 1;
		if(Data == 1) dat += 1;
		while(Data);
	}
	return dat;
}

void DHT11_receive()      //接收40位的数据
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //等待拉高     
        delay_us(40);  //拉高后延时80us
        R_H=DHT11_rec_byte();    //接收湿度高八位  
        R_L=DHT11_rec_byte();    //接收湿度低八位  
        T_H=DHT11_rec_byte();    //接收温度高八位  
        T_L=DHT11_rec_byte();    //接收温度低八位
        revise=DHT11_rec_byte(); //接收校正位

        delay_us(25);    //结束

        if((R_H+R_L+T_H+T_L)==revise)      //校正
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
        /*数据处理，方便显示*/
        rec_dat[0]='0'+(RH/10);
        rec_dat[1]='0'+(RH%10);
        rec_dat[2]='R';
        rec_dat[3]='H';
        rec_dat[4]=' ';
        rec_dat[5]=' ';
        rec_dat[6]='0'+(TH/10);
        rec_dat[7]='0'+(TH%10);
        rec_dat[8]='C';
    }
}

