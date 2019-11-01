
#include <INTRINSICS.H>

void delay_100ms(unsigned int sec)//MCU=13MHZ时为100ms延时
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
void delayms(unsigned int ms)//mcu=13MHZ时为1ms延时
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