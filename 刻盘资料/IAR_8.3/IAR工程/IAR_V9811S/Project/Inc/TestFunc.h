
/************************************************************
           ���ܺ����ĵ��������Լ���ع��ܵĺ궨��
*************************************************************/
#ifndef __TESTFUNC_H__
#define __TESTFUNC_H__

#define TRUE  1
#define FALSE 0

//****************��λ��־�궨��*******************************
#define BIT0 0X01
#define BIT1 0X02
#define BIT2 0X04
#define BIT3 0X08
#define BIT4 0X10
#define BIT5 0X20
#define BIT6 0X40
#define BIT7 0X80
//**************************************************************

//****************�����Ժ궨�庯��******************************
#define LED_ON() {P1OE &= (~BIT4);P1IE &= ~BIT4; P1OD |= BIT4;}//����LED��PCBIO1.4
#define LED_OFF() {P1OE &= (~BIT4);P1IE &= ~BIT4;P1OD &= (~BIT4);}//�ر�LED
#define Flash_LowPowerConsum() {SPC_FNC=1;XBYTE[0x0402]=0x86;SPC_FNC=0;}//����FLASH�͹���ģʽ
#define ClearWDT() {WDTEN=0xa5;WDTCLR=0x5a;}//ι��
//**************************************************************

//******************�ⲿ������������������*********************	
extern void call_bank0(unsigned char i);
extern void call_bank1(unsigned char i);
extern void call_bank2(unsigned char i);

extern void delay(unsigned int sec);
extern void delayms(unsigned int j);

//-------------------------------------------------------------
/**************************************************************
���ܣ��жϵ�ǰƵ���Ƿ�Ϊ�û�Ŀ��Ƶ�ʣ�������ǣ��л�PLLƵ�ʣ�
	����ϵͳ��ʱ���л�����ǰPLLƵ�ʣ�
	����ADC���ģ�����ref�¶�ϵ������BGPCHOP
��ڣ�val_para��
		SETPLL_CLOSE �����ǰϵͳ��ʱ�Ӳ���32k����ϵͳ��ʱ���е�32k���ر�PLL��
		SETPLL_800K �����ǰPLL ���ǹ����� 800k����PLL�е�800k������ADC�͹���
		SETPLL_1_6M �����ǰPLL ���ǹ����� 1.6M����PLL�е�1.6M������ADC�͹���
		SETPLL_3_2M �����ǰPLL ���ǹ����� 3.2M����PLL�е�3.2M������ADC�߹���
		SETPLL_6_4M �����ǰPLL ���ǹ����� 6.4M����PLL�е�6.4M������ADC�߹���
***************************************************************/
extern unsigned char SetPLL(unsigned char val_para);
#define SETPLL_CLOSE 0x40
#define SETPLL_800K 0xc0
#define SETPLL_1_6M 0xD5
#define SETPLL_3_2M 0xEA
#define SETPLL_6_4M 0xEB
//--------------------------------------------------------------

//****************************RTC��ʼʱ����ض���***************
void SetRTCInt(unsigned char cInterval);
#define RTC_SEC 0X00	 //���Ѽ��ʱ��Ϊ1��
#define RTC_MIN 0x01	 //1����
#define RTC_HOUR 0X02	 //1Сʱ
#define RTC_DAY 0x03	 //1��
#define RTC_500MS 0x04	 //500����
#define RTC_250MS 0X05	 //250����
#define RTC_125MS 0X06	 //125����
#define RTC_62_5MS 0X07	 //62.5����
//**************************************************************


#endif