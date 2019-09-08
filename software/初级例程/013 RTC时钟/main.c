#include <includes.h> 

void main() 
{ 
	uchar buffer[9] = {0};
	UartPrintInit();
	
	while(1)
	{
		get_show_time();
		
		sprintf(buffer, "%d%d%d%d%d%d%d%d", dis_buf[0], dis_buf[1], dis_buf[2], dis_buf[3], dis_buf[4], dis_buf[5], dis_buf[6], dis_buf[7]);
		buffer[8] = '\0';
		printf("rtc time : %s\n\r", buffer);
	}
}

