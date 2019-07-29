/********************************************
*	名称：PWM.h
*	功能：根据按键加减PWM输出占空比用到的函数
	创建时间：2019/7/27
	修改时间：2019年7/29	
	作者：曾思茹
********************************************/

#ifndef _PWM_H
#define _PWM_H	  

void init();
void key();
void PWM_plus(uchar k);
void PWM_minus(uchar x);

#endif