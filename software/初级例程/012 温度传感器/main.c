/*********************************************************************************************************
*名称：OLED显示温湿度
*功能：在屏幕中显示DHT11所测得温湿度
创建时间：2019/7/14
修改时间：2019/7/30
作者：李诗琪
*********************************************************************************************************/

#include "includes.h"

uint Temperature[3]={1,1,1};//前两位为整数部分，后一位为小数部分
uint Humidity[2]={1,1};//传回的湿度数据只有整数部分
uchar Data_Receive[5];

//#define PRINT_LOG

int main()
{
	P3M0=0X00; //0000,0000 端口3模式寄存器0
	P3M1=0X00;
	//sys_init();
#ifdef PRINT_LOG
	PrintUartInit();
#endif
	while(1)
	{
#ifdef PRINT_LOG
		printf("-------DHT_Collect start.....-----------\n\r");
#endif
		DHT_Collect();//DHT11数据采集
#ifdef PRINT_LOG
		printf("-------DHT_Collect end.....-----------\n\r");
#endif
		//YLED=1;RLED=0;//灯状态转换
		//OLED_Display();//OLED显示函数
	//	RLED=1;YLED=0;//灯状态转换
		delay_ms(1000);
		delay_ms(1000);//注意：长时间的延时必须要有，不然会读出0
	}
}

