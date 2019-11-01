
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"
extern const uint16 code CrcTab[256];// X16+X12+X5+1 余式表
/*************************************************
功能：在此页下设置LED闪烁次数
函数名：call_bank2
入口参数：unsinged char i
出口参数：返回值为空
*************************************************/
void call_bank2(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//如果在BANK1区间代码闪烁5次
	{  
		LED_ON();
		delay_100ms(3);
		LED_OFF();
		delay_100ms(3);		  
	}
}
/**************************************************
功能：通过修改RTC密码来修改INTRTC来设置唤醒时间，同时
	  完成对时间的设定
函数名：SetRTCInt
入口参数：unsigned char cInterval
出口参数：返回值为空	
***************************************************/
void SetRTCInt(unsigned char cInterval)
{
	
	RTCPEN = 0x96; //RTC密码使能寄存器
	RTCPWD = 0X57;//当且仅当bit[7:1]被写入0101011B时，bit0才能被有效写入。
				  // 1，使能对INTRTC SFR、RTC校正寄存器和RTC时间设置寄存器的写入操作
	INTRTC = cInterval;//系统休眠唤醒间隔寄存器
	RTCHC = 0X01;	//小时
	RTCMiC= 0x00;	//分钟
	RTCSC = 0X58;	//秒
	RTCPEN = 0x96;
	RTCPWD = 0X56; //5个OSC时钟后，在RTCPWD SFR的bit[7:1]写入0101011B，
				   //再向bit0写入0，恢复对INTRTC SFR、RTC校正寄存器和RTC时间设置寄存器的写入保护，
				   //5个OSC时钟后，MCU自动将上述寄存器的数据写入RTC，从而完成RTC配置。
	delayms(50); //
	
}


