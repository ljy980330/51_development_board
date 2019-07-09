/*********************************************************************************************************
*名称：pwm.h
*功能：外部所用到的pwm调速函数声明
创建时间：2019/7/8
修改时间：2019/7/8
作者：黄彦钊
*********************************************************************************************************/

#ifndef _PWM_H
#define _PWM_H

sbit right2=P2^1;       
sbit right1=P2^2;       
sbit left2=P2^3;       
sbit left1=P2^4;	      
void stop();
void Time1();
void goahead();
void turnleft();   
void turnright();
void goahead1();
void turnback();
void turnback1();
void turnback2();
void turnback3();
void wentleft();
void offsetright();	
void offsetright1();
void offsetleft();
void offsetleft1();

#endif