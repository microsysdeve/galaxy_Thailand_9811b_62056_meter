
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"

/*************************************************
���ܣ��ڴ�ҳ������LED��˸����
��������call_bank1
��ڲ�����unsinged char i
���ڲ���������ֵΪ��
*************************************************/
void call_bank1(unsigned char i)
{
	unsigned char count;
	count=i;
	while(count--)//�����BANK1���������˸5��
	{  
		LED_ON();
		delay_100ms(5);
		LED_OFF();
		delay_100ms(5);		  
	}
}

/********************************************
���ܣ�ͨ����FSC->FWCȻ������CtrlCLK������PLL ADC
      �ͼ�����ص�ʱ��Ƶ�ʡ���ͨ��MCUFRQ��MEAFRQ
	  ���PLL�Ƿ�����ʱ��Դ 
��������SetPLL
��ڲ�����unsigned char val_para
���ڲ���������TRUE(0) OR FALSE(1)
		  �������ͣ�unsigned char
*********************************************/
unsigned char SetPLL(unsigned char val_para)
{
    unsigned char i;
	i=0;
	FSC=0; //�������߿��ƣ�0�ر�
	FWC = 0;//���ٻ��ѿ�ʼ
	CtrlCLK = val_para;//ʱ�ӿ��ƼĴ�����CtrlCLK��0x2867��
	while(!(PLLLCK&BIT0))//�ж�PLL�Ƿ���������PLLCKΪ1��������0δ����
	{
		i++;
		if(i>50)
		{
			return FALSE; //��һ��ʱ����û������
		}
	}
	MCUFRQ=1;//����PLL��ʱ��Դ
	i=0;
    while(!(MCUFRQ))
	{
		i++;
		if(i>20)
		{
			return FALSE; //��һ��ʱ����û������
		}
	}
    MEAFRQ=1; //����PLL��ʱ��Դ
	i=0;
    while(!(MEAFRQ))
	{
		i++;
		if(i>20)
		{
			return FALSE; //��һ��ʱ����û������
		}
	}

	XBYTE[0x2862]|=((BIT3)&(~BIT2)&(~BIT1));//����BANDGAP�¶�ϵ��Ϊ-40PPM
	XBYTE[0X2866]&=(~BIT5);

    return TRUE;
		
}
