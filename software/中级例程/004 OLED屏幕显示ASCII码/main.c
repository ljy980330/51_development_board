/*********************************************************************************************************
*���ƣ�OLED��ʾ��
*���ܣ�����Ļ����ʾASCII��
����ʱ�䣺2019/7/7
�޸�ʱ�䣺2019/XX/XX
���ߣ���ʫ��
*********************************************************************************************************/

#include "includes.h"

int main(void)
{
	OLED_Init();
	
	while(1)
	{

		OLED_P8x16Str(0,0,"ABCDEF");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��

		OLED_P8x16Str(0,2,"ABCD ABCDEFG");

		OLED_P8x16Str(0,4,"ABCDEFGHIJKLM");

		OLED_P6x8Str(0,6,"ABCDEFGHIJKLMNOPQRS");

		OLED_P6x8Str(0,7,"ABCDEFGHIJKLMNOPQ");

		Delay_ms(4000);

		OLED_CLS();

	}
}