
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"

/*************************************************
功能：在此页下设置LED闪烁次数
函数名：call_bank1
入口参数：unsinged char i
出口参数：返回值为空
*************************************************/
void call_bank1(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//如果在BANK1区间代码闪烁5次
	{  
		LED_ON();
		delay_100ms(5);
		LED_OFF();
		delay_100ms(5);		  
	}
}

/********************************************
功能：通过对FSC->FWC然后配置CtrlCLK来设置PLL ADC
      和计量相关的时钟频率。并通过MCUFRQ和MEAFRQ
	  检查PLL是否连接时钟源 
函数名：SetPLL
入口参数：unsigned char val_para
出口参数：返回TRUE(0) OR FALSE(1)
		  返回类型：unsigned char
*********************************************/
unsigned char SetPLL(unsigned char val_para)
{
    unsigned char i;
	i=0;
	FSC=0; //快速休眠控制，0关闭
	FWC = 0;//快速唤醒开始
	CtrlCLK = val_para;//时钟控制寄存器（CtrlCLK，0x2867）
	while(!(PLLLCK&BIT0))//判断PLL是否锁定，若PLLCK为1则锁定，0未锁定
	{
		i++;
		if(i>50)
		{
			return FALSE; //在一定时间内没有锁定
		}
	}
	MCUFRQ=1;//连接PLL作时钟源
	i=0;
    while(!(MCUFRQ))
	{
		i++;
		if(i>20)
		{
			return FALSE; //在一定时间内没有锁定
		}
	}
    MEAFRQ=1; //连接PLL作时钟源
	i=0;
    while(!(MEAFRQ))
	{
		i++;
		if(i>20)
		{
			return FALSE; //在一定时间内没有锁定
		}
	}

	XBYTE[0x2862]|=((BIT3)&(~BIT2)&(~BIT1));//调整BANDGAP温度系数为-40PPM
	XBYTE[0X2866]&=(~BIT5);

    return TRUE;
		
}
