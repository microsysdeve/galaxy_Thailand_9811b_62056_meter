
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"
extern const uint16 code CrcTab[256];// X16+X12+X5+1 余式表
/*************************************************
功能：在此页下设置LED闪烁次数
函数名：call_bank3
入口参数：unsinged char i
出口参数：返回值为空
*************************************************/
void call_bank3(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//如果在BANK1区间代码闪烁5次
	{  
		LED_ON();
		delay_100ms(2);
		LED_OFF();
		delay_100ms(2);		  
	}
}

