
#include "LeoPardReg.h"
#include "TestFunc.h"


int call_bank0(unsigned char i)
{
	int vat;
	unsigned char count;
	count=i;
	while(count--)//如果在BANK1区间代码闪烁5次
	{  
		LED_ON();
		delay(400);
		LED_OFF();
		delay(400);		  
	}
   return vat;
}
