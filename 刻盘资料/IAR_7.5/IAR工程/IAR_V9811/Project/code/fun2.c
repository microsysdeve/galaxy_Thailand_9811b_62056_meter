
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"

/*************************************************
���ܣ��ڴ�ҳ������LED��˸����
��������call_bank2
��ڲ�����unsinged char i
���ڲ���������ֵΪ��
*************************************************/
void call_bank2(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)
	{  
		LED_ON();
		delay_100ms(2);
		LED_OFF();
		delay_100ms(2);		  
	}
}
