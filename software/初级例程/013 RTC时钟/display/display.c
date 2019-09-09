/*********************************************************************************************************
*名称：display.c
*功能：不同标准的屏幕显示
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#include "display.h"	  	
#include "../function/function.h" 
#include "../code_tab/code_tab.h"

/*******************************************************************************
* 函 数 名         : OLED_P6x8Str
* 函数功能		   : 显示6*8一组标准ASCII字符串	显示的坐标（x,y）y为页范围0～7
*******************************************************************************/

void OLED_P6x8Str(uchar x, y,uchar ch[])
{
	uchar c=0,i=0,j=0;

	while (ch[j]!='\0')
	{
		c =ch[j]-32;

		if(x>126){x=0;y++;}

		OLED_Set_Pos(x,y);

		for(i=0;i<6;i++)

		OLED_WrDat(F6x8[c][i]);

		x+=6;

		j++;
	}
}


/*******************************************************************************
* 函 数 名         : OLED_P8x16Str
* 函数功能		   : 显示8*16一组标准ASCII字符串 显示的坐标（x,y）y为页范围0～7
*******************************************************************************/

void OLED_P8x16Str(uchar x, y,uchar ch[])
{
	uchar c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c = ch[j]-32;

		if(x>120){x=0;y++;}

		OLED_Set_Pos(x,y);

		for(i=0;i<8;i++)

		OLED_WrDat(F8X16[c*16+i]);

		OLED_Set_Pos(x,y+1);

		for(i=0;i<8;i++)

		OLED_WrDat(F8X16[c*16+i+8]);

		x+=8;

		j++;
	}
}


/*******************************************************************************
* 函 数 名         : OLED_P16x16Ch
* 函数功能		   : 显示16*16点阵  显示的坐标（x,y）y为页范围0～7
*******************************************************************************/

void OLED_P16x16Ch(uchar x, y, N)
{
	uchar wm=0;

	uint adder=32*N;

	OLED_Set_Pos(x , y);

	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);

		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);

	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);

		adder += 1;
	} 	  	
}


/*******************************************************************************
* 函 数 名         : Draw_BMP
* 函数功能		   : 显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
*******************************************************************************/

void Draw_BMP(uchar x0, y0,x1, y1,uchar BMP[])
{
	uint j=0;

	uchar x,y;

   if(y1%8==0) y=y1/8;
         
   else y=y1/8+1;

	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);

        for(x=x0;x<x1;x++)
	     {      
	    	OLED_WrDat(BMP[j++]);
	     }
	}
}

