
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"
extern const uint16 code CrcTab[256];// X16+X12+X5+1 ��ʽ��
/*************************************************
���ܣ��ڴ�ҳ������LED��˸����
��������call_bank3
��ڲ�����unsinged char i
���ڲ���������ֵΪ��
*************************************************/
void call_bank3(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//�����BANK1���������˸5��
	{  
		LED_ON();
		delay_100ms(2);
		LED_OFF();
		delay_100ms(2);		  
	}
}

