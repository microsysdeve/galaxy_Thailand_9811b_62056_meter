
#include "V98xx.h"
#include "TestFunc.h"
#include "delay.h"
extern const uint16 code CrcTab[256];// X16+X12+X5+1 ��ʽ��
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
	while(count--)//�����BANK1���������˸5��
	{  
		LED_ON();
		delay_100ms(3);
		LED_OFF();
		delay_100ms(3);		  
	}
}
/**************************************************
���ܣ�ͨ���޸�RTC�������޸�INTRTC�����û���ʱ�䣬ͬʱ
	  ��ɶ�ʱ����趨
��������SetRTCInt
��ڲ�����unsigned char cInterval
���ڲ���������ֵΪ��	
***************************************************/
void SetRTCInt(unsigned char cInterval)
{
	
	RTCPEN = 0x96; //RTC����ʹ�ܼĴ���
	RTCPWD = 0X57;//���ҽ���bit[7:1]��д��0101011Bʱ��bit0���ܱ���Чд�롣
				  // 1��ʹ�ܶ�INTRTC SFR��RTCУ���Ĵ�����RTCʱ�����üĴ�����д�����
	INTRTC = cInterval;//ϵͳ���߻��Ѽ���Ĵ���
	RTCHC = 0X01;	//Сʱ
	RTCMiC= 0x00;	//����
	RTCSC = 0X58;	//��
	RTCPEN = 0x96;
	RTCPWD = 0X56; //5��OSCʱ�Ӻ���RTCPWD SFR��bit[7:1]д��0101011B��
				   //����bit0д��0���ָ���INTRTC SFR��RTCУ���Ĵ�����RTCʱ�����üĴ�����д�뱣����
				   //5��OSCʱ�Ӻ�MCU�Զ��������Ĵ���������д��RTC���Ӷ����RTC���á�
	delayms(50); //
	
}


