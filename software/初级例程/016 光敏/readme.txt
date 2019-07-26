photoconductor.hex 是最终烧录到单片机上的程序

photoconductor.uvproj 是该程序的工程文件

main.c      是光敏电阻的C源代码

该程序原理是将环境中的光线亮度转换成模拟信号输出到数码管显示，
使用前注意将光敏电阻的AD口接到P1.0口。

由于光敏电阻的原理用到了AD转换，所以该程序的C源代码与ADC的一样的。
