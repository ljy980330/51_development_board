/*********************************************************************************************************
*���ƣ�OLED��ʾ��
*���ܣ�����Ļ����ʾ
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ���ʫ��
*********************************************************************************************************/

#include "includes.h"

int mian()
{
	
	U8 i;
	OLED_Init();	//OLED��ʼ��

	while(1)
	{
	 	OLED_P16x16Ch(24,0,1);

		OLED_P16x16Ch(40,0,2);

		OLED_P16x16Ch(57,0,3);

		OLED_P16x16Ch(74,0,4);

		OLED_P16x16Ch(91,0,5);

		for(i=0; i<8; i++)//ͨ��������ʾ���� -- i��ʾ�ֱ������λ��
		{

		 	OLED_P16x16Ch(i*16,2,i+8);

		 	OLED_P16x16Ch(i*16,4,i+16);

		 	OLED_P16x16Ch(i*16,6,i+24);

		}
		Delay_ms(4000);

		OLED_CLS();//����

		OLED_P8x16Str(0,0,"ABCDEF");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��

		OLED_P8x16Str(0,2,"ABCD ABCDEFG");

		OLED_P8x16Str(0,4,"ABCDEFGHIJKLM");

		OLED_P6x8Str(0,6,"ABCDEFGHIJKLMNOPQRS");

		OLED_P6x8Str(0,7,"ABCDEFGHIJKLMNOPQ");

		Delay_ms(4000);

		OLED_CLS();

	    Draw_BMP(0,0,128,8,BMP1);  //ͼƬ��ʾ

		Delay_ms(8000);

		Draw_BMP(0,0,128,8,BMP2);

		Delay_ms(8000);
	 }
}