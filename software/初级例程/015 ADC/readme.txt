photoconductor.hex 是最终烧录到单片机上的程序

photoconductor.uvproj 是该程序的工程文件

main.c      是ADC的C源代码

ADC有很多种应用，本程序是用于光敏电阻将环境中的光强转换成模拟量输出，
所以该程序与光敏电阻的C源代码相同；
使用之前要将光敏电阻的AD口接到P1.0口。