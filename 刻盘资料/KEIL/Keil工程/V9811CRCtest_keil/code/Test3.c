
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"

/*************************************************
���ܣ��ڴ�ҳ������LED��˸����
��������Test3
��ڲ�����unsinged char i
���ڲ���������ֵΪ��
*************************************************/
void Test3(unsigned char i)
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
