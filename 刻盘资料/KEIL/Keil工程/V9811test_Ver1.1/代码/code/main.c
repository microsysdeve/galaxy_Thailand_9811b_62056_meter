
/***************************** Copyright by Vango ***********************************

	�ļ����ͣ�V9811TEST C51 Keil3��д����
	�ļ����ã���Ҫ����SuperDebug���ز���,������ɺ�������LED��������500ms��˸3�Σ�ͣ��2S
			  ʱ�����300ms���������˸5�Σ��ٴ�ͣ��1.8Sʱ�����200ms���������˸7�Ρ���ͣ��1.7S��
			  �����µ�ѭ������FLASH���سɹ���SuperDebug�ɳɹ�������V9801��Flash��ȥ��

	�� �� �ˣ�DL
	�������ڣ�2012��4��20��
	��ǰ�汾��V9811Test_Ver1.1
	
	�汾��Ϣ��V9811Test_ver1.0
			  V9811Test_ver1.1  
**************************************************************************************/
#include "delay.h"
#include "V98xx.h"
#include "TestFunc.h"

void GPIO_INIT()//�˿ڳ�ʼ��
{
 	P0OE = 0XFF;
	P0IE = 0X00;
	P1OE = 0XFF;
	P1IE = 0X00;
	P2OE = 0XFF;
	P2IE = 0X00;
	P3OE = 0XFF;
	P3IE = 0X00;
	P4OE = 0XFF;
	P4IE = 0X00;
	P5OE = 0XFF;
	P5IE = 0X00;
	P6OE = 0XFF;
	P6IE = 0X00;
	P7OE = 0XFF;
	P7IE = 0X00;
	P8OE = 0XFF;
	P8IE = 0X00;
	P9OE = 0XFF;
	P9IE = 0X00;
	P10OE = 0XFF;
	P10IE = 0X00;
}

void main()
{
	FSC=0; //�������߿��ƣ�0�ر�
	FWC=1;//���ٻ���1������0�ر�
	MCUFRQ=1;//���ܼ���ģ��ʱ��Դ��1ѡ��PLLʱ�ӣ�0ѡ��OSCʱ��
	SetPLL(SETPLL_6_4M);  //�������ԣ�F11���˺�����ʧȥ��������
	CtrlPLL = 0X40;	   //MCU 13M
	Flash_LowPowerConsum();//����FLASH�͹���ģʽ
	SetRTCInt(RTC_DAY);//����1�컽��
	GPIO_INIT();  //�˿ڳ�ʼ��
	CtrlADC6 =0x0f ;//�����ĸ�ADCͨ��
    ClearWDT();

	while(1)
	{
		Test1(3);
		delayms(500);//����Ҫ����Test1��ƽ����ĺ����ʱ��������ʱΪ1.5S+���Ƽ��ʱ��=2S
		delayms(500);
		delayms(500);

		Test2(5);
		delayms(500); //ͬ��1.8S
		delayms(500);
		delayms(500);

		Test3(7);
		delayms(500); //1.7s
		delayms(500);
		delayms(500);
		ClearWDT();

	}		
}