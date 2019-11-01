
/***************************** Copyright by Vango ***********************************

	文件类型：V9801TEST C51 Keil3编写编译
	文件作用：主要用于SuperDebug下载测试,下载完成后，若看见LED灯连续以500ms闪烁3次，停顿2S
			  时间后以300ms间隔连续闪烁5次，再次停顿1.8S时间后以200ms间隔连续闪烁7次。再停顿1.7S则
			  进入新的循环。则FLASH下载成功。SuperDebug可成功下载至V9801的4个CODE BANK中去。

	创 建 人：DL
	创建日期：2011年12月31日
	当前版本：V9801Test_Ver1.0
	
	版本信息：V9801Test_ver1.0
**************************************************************************************/
#include "delay.h"
#include "V98xx.h"
#include "TestFunc.h"

void GPIO_INIT()//端口初始化
{
 	P0OE = 0XFF;
	P0IE = 0X00;
	P1OE = 0XFF;
	P1IE = 0X00;
	P2OE = 0XFF;
	P2IE = 0X00;
	P3OE = 0XFF;
	P3IE = 0X00;
	P4OE = 0XFF;
	P4IE = 0X00;
	P5OE = 0XFF;
	P5IE = 0X00;
	P6OE = 0XFF;
	P6IE = 0X00;
	P7OE = 0XFF;
	P7IE = 0X00;
	P8OE = 0XFF;
	P8IE = 0X00;
	P9OE = 0XFF;
	P9IE = 0X00;
	P10OE = 0XFF;
	P10IE = 0X00;
}

void main()
{
	FSC=0; //快速休眠控制，0关闭
	FWC=1;//快速唤醒1开启，0关闭
	MCUFRQ=1;//电能计量模块时钟源，1选择PLL时钟，0选择OSC时钟
	SetPLL(SETPLL_6_4M);  //单步调试（F11）此函数会失去调试连接
	CtrlPLL = 0X40;	   //MCU 13M
	Flash_LowPowerConsum();//设置FLASH低功耗模式
//	SetRTCInt(RTC_DAY);//设置1天唤醒
	GPIO_INIT();  //端口初始化
	CtrlADC6 =0x0f ;//开启四个ADC通道
    ClearWDT();

	while(1)
	{
		call_bank1(3);
		delayms(500);
		delayms(500);//由于要加上call_bank1灭灯结束的后的延时，所以延时为1.5S+闪灯间隔时间=2S
		delayms(500);
		ClearWDT();

		call_bank2(5);
		delayms(500);
		delayms(500);//同理1.8S
		delayms(500);
		ClearWDT();

		call_bank3(7);
		delayms(500);//1.7s
		delayms(500);
		delayms(500);
		ClearWDT();

	}		
}