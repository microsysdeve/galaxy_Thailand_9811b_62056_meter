
#include <INTRINSICS.H>

void delay_100ms(unsigned int sec)//MCU=13MHZʱΪ100ms��ʱ
{
	unsigned char i,j;
        unsigned int k;
	for(k=0;k<sec;k++)
	{	for(i=0;i<230;i++)
			for(j=0;j<202;j++)
			{
				__no_operation();
			}
	}
}
void delayms(unsigned int ms)//mcu=13MHZʱΪ1ms��ʱ
{
	unsigned char i;
	while(ms--)
	{
		for(i=0;i<202;i++)
		{
			__no_operation();
			__no_operation();
			__no_operation();
			__no_operation();
			__no_operation();
		}
	}
}