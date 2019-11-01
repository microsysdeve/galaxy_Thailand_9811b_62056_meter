
/************************************************************
           功能函数的调用声明以及相关功能的宏定义
*************************************************************/
#ifndef __TESTFUNC_H__
#define __TESTFUNC_H__

#define TRUE  1
#define FALSE 0

//****************置位标志宏定义*******************************
#define BIT0 0X01
#define BIT1 0X02
#define BIT2 0X04
#define BIT3 0X08
#define BIT4 0X10
#define BIT5 0X20
#define BIT6 0X40
#define BIT7 0X80
//**************************************************************

//****************功能性宏定义函数******************************
#define LED_ON() {P1OE &= (~BIT4);P1IE &= ~BIT4; P1OD |= BIT4;}//开启LED。PCBIO1.4
#define LED_OFF() {P1OE &= (~BIT4);P1IE &= ~BIT4;P1OD &= (~BIT4);}//关闭LED
#define Flash_LowPowerConsum() {SPC_FNC=1;XBYTE[0x0402]=0x86;SPC_FNC=0;}//设置FLASH低功耗模式
#define ClearWDT() {WDTEN=0xa5;WDTCLR=0x5a;}//喂狗
//**************************************************************

//******************外部调用声明函数及变量*********************	
extern void call_bank0(unsigned char i);
extern void call_bank1(unsigned char i);
extern void call_bank2(unsigned char i);

extern void delay(unsigned int sec);
extern void delayms(unsigned int j);

//-------------------------------------------------------------
/**************************************************************
功能：判断当前频率是否为用户目标频率，如果不是，切换PLL频率，
	并将系统主时钟切换到当前PLL频率，
	设置ADC功耗，调整ref温度系数，开BGPCHOP
入口：val_para：
		SETPLL_CLOSE 如果当前系统主时钟不是32k，则将系统主时钟切到32k，关闭PLL。
		SETPLL_800K 如果当前PLL 不是工作在 800k，则将PLL切到800k，设置ADC低功耗
		SETPLL_1_6M 如果当前PLL 不是工作在 1.6M，则将PLL切到1.6M，设置ADC低功耗
		SETPLL_3_2M 如果当前PLL 不是工作在 3.2M，则将PLL切到3.2M，设置ADC高功耗
		SETPLL_6_4M 如果当前PLL 不是工作在 6.4M，则将PLL切到6.4M，设置ADC高功耗
***************************************************************/
extern unsigned char SetPLL(unsigned char val_para);
#define SETPLL_CLOSE 0x40
#define SETPLL_800K 0xc0
#define SETPLL_1_6M 0xD5
#define SETPLL_3_2M 0xEA
#define SETPLL_6_4M 0xEB
//--------------------------------------------------------------

//****************************RTC初始时钟相关定义***************
void SetRTCInt(unsigned char cInterval);
#define RTC_SEC 0X00	 //唤醒间隔时间为1秒
#define RTC_MIN 0x01	 //1分钟
#define RTC_HOUR 0X02	 //1小时
#define RTC_DAY 0x03	 //1天
#define RTC_500MS 0x04	 //500毫秒
#define RTC_250MS 0X05	 //250毫秒
#define RTC_125MS 0X06	 //125毫秒
#define RTC_62_5MS 0X07	 //62.5毫秒
//**************************************************************


#endif