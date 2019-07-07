/*********************************************************************************************************
*名称：OLED显示屏
*功能：在屏幕中显示ASCII码
创建时间：2019/7/7
修改时间：2019/XX/XX
作者：李诗琪
*********************************************************************************************************/

#include "includes.h"

int main(void)
{
	OLED_Init();
	
	while(1)
	{

		OLED_P8x16Str(0,0,"ABCDEF");//第一行 -- 8x16的显示单元显示ASCII码

		OLED_P8x16Str(0,2,"ABCD ABCDEFG");

		OLED_P8x16Str(0,4,"ABCDEFGHIJKLM");

		OLED_P6x8Str(0,6,"ABCDEFGHIJKLMNOPQRS");

		OLED_P6x8Str(0,7,"ABCDEFGHIJKLMNOPQ");

		Delay_ms(4000);

		OLED_CLS();

	}
}