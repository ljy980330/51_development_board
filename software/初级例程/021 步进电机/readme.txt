steppingMotor.hex 是最终烧录到单片机上的程序

steppingMotor.uvproj 是该程序的工程文件

main.c      是步进电机的C源代码

该程序用于步进电机前，要注意用跳线帽将VCC与VCC#口短接（详细原理图请查阅ULN2003模块使用手册）。