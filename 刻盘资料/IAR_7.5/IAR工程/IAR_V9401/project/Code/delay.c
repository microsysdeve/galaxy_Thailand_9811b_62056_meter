
#include <INTRINSICS.H>

void delay_100ms(unsigned int sec)//mcu=3.2MʱΪ100ms��ʱ
{
	unsigned char i,j;
        unsigned int k;
	for(k=0;k<sec;k++)
	{	for(i=0;i<99;i++)
			for(j=0;j<82;j++)
			{
				__no_operation();
				__no_operation();
				__no_operation();
				__no_operation();
				
			}
	}
}
void delayms(unsigned int j)//mcu=3.2MʱΪ1ms��ʱ
{
	unsigned char i;
	
	while(j--)
	{
		for(i=0;i<57;i++)
		{
			__no_operation();
			__no_operation();
			__no_operation();

		}
	}
}

