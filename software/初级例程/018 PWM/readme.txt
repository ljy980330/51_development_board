LEDindicator.hex 是最终烧录到单片机上的程序

LEDindicator.uvproj 是该程序的工程文件

main.c      是PWM的C源代码

本程序是基于PWM原理来使LED灯有呼吸效果，
故该程序的C源代码与呼吸灯的C源代码相同。
该程序是使用P1.3口作为PWM的输出口，
使用前用杜邦线连接P1.3口与LED灯正极即可。