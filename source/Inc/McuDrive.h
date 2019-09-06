#ifndef __MCUDRIVE_H__
    #define __MCUDRIVE_H__

#ifndef MCUDRIVEEXT
    #define MCUDRIVEEXT extern
#endif

#define SETPLL_CLOSE 0x00
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_5M 0x6f



#define SETLDO_25V 0
#define SETLDO_28V 1
#define SETLDO_22V 2
#define SETLDO_24V 3



#define SETLCD_30V 0x80 
#define SETLCD_33V 0
#define SETLCD_35V 0x10


#define POWERUP()       (Systate&BIT0)    //BIT0=1 有电  BIT0=0 没电
#define POWERDN()       (Systate&BIT1)    //BIT1=1 没电  BIT1=0 有电
#define RTCWAKEUP()     (Systate&BIT2)    //RTC RST
#define IOWAKEUP()      (Systate&BIT3)    //IO RST
#define OSCSTATE()      (VERSION&BIT7)    //晶振 1起振/0未起振
#define PORRESET()     ((Systate&BIT5))    //POR RST

#define SLPWDT()    {WDTEN=0xA5;WDTCLR=0x5A;}
#define CLRWDT()    {SLPWDT();SLPWDT()}

#define RTC_SEC         0x00
#define RTC_MIN         0x01
#define RTC_HOUR        0x02
#define RTC_DAY         0x03
#define RTC_SETSEC      0x07

#define LCDSETTING4COM  0x86    //256hz  600K 4COM
#define LCDSETTING6COM  0xD6    //256HZ  600K 6COM 1Byte=6Seg  


//#define BATDIV      403948
#define BATLEVEL    310
#define LCDREGLEN   17
//#define BATOFFSET   77428752//23836396//5353488
//LED
//打开背光
//#define OpenBeiGuang()      {if(CalRMS(RMSIU)>1540){P2OD|=BIT5;P2OE&=(~BIT5);}else if(CalRMS(RMSIU)<1430){P2OD&=(~BIT5);P2OE&=(~BIT5);}}
//#define OpenBeiGuang()      {P2OD |= BIT5; P2OE &=~ BIT5; P2IE&=~BIT5;  P25FS=0;}
//关闭背光
#define CloseBeiGuang()     {P0OE&=(~BIT1);P0OD&=(~BIT1);}//{P2OD &=~BIT5; P2OE &=~ BIT5; P2IE&=~BIT5;  P25FS=0;}
////Power指示
////#define OpenPowerLed()      //{P1OD |= BIT1; P1OE &=~ BIT1; P1IE&=~BIT1; P11FS=0;}
////#define ClosePowerLed()     //{P1OD &=~BIT1; P1OE &=~ BIT1; P1IE&=~BIT1; P11FS=0;}
//Earth指示 JD
//#define OpenEarthLed()      {P2OD |= BIT4; P2OE &=~ BIT4; P2IE&=~BIT4;  P24FS=0;}
//#define CloseEarthLed()     {P2OD &=~BIT4; P2OE &=~ BIT4; P2IE&=~BIT4;  P24FS=0;}
//Reverse指示
//#define OpenReverseLed()    {P0OD |= BIT0; P0OE &=~ BIT0; P0IE&=~BIT0; }
//#define CloseReverseLed()   {P0OD &=~BIT0; P0OE &=~ BIT0; P0IE&=~BIT0; }
//Current指示
//#define OpenCurrentLed()    {P0OD |= BIT1; P0OE &=~ BIT1; P0IE&=~BIT1; }
//#define CloseCurrentLed()   {P0OD &=~BIT1; P0OE &=~ BIT1; P0IE&=~BIT1; }
////按键
#define KeyPortIn()     {P0OE|=BIT0;P0IE|=BIT0;}//P1IE|=BIT4;P1OE|=BIT4;P14FS=0;P9OE|=BIT0;P9IE|=BIT0;P9FC&=~BIT0;}        //                                               
//
//#define KeyUpEnable()   {P1IE|=BIT4;P1OE|=BIT4;P14FS=0;}
//#define KeyUpDisable()  {P1IE&=(~BIT4);P1OE|=BIT4;}
//#define KeyStUp()       (!(P1ID & BIT4))                // 上翻按键
//硬件清零
//#define ClrEnable()   {P8IE|=BIT1;P8OE|=BIT1;}
//#define ClrStaLow()   !(P8ID & BIT1)
//#define ClrDisable()  {P8OE&=~BIT1;P8OE&=~BIT1;P8OD|=BIT1;}
//硬件校表
//#define CalEnable()   {P8IE|=BIT0;P8OE|=BIT0;}
//#define CalStaLow()   !(P8ID & BIT0)
//#define CalDisable()  {P8OE&=~BIT0;P8OE&=~BIT0;P8OD|=BIT0;}

#define      _KeyBItDef_              BIT1

#define KeyPrEnable()    {P1IE|=_KeyBItDef_ ;P1OE|=_KeyBItDef_ ;} //{P0IE|=BIT0;P0OE|=BIT0;}
#define KeyPrDisable()   {P1IE&=(~_KeyBItDef_ );P1OE|=_KeyBItDef_ ;}  // P0IE&=(~BIT0);P0OE|=BIT0;}
#define KeyStPr()       ((P1ID & BIT1)?0:1)// (!(P0ID & BIT0))               // 编程按键


////硬件接口预留
//#define KeyBgEnable()    {P1IE|=BIT3;P1OE|=BIT3;P13FS=0;}
//#define KeyBgDisable()    {P1IE&=(~BIT3);P1OE|=BIT3;}
//#define KeyStBg()       (!(P1ID&BIT3))                           //表盖检测按键
#define OpenFD()     {P9OE |=BIT0;P9IE &= (~BIT0);P9FS&= (~BIT0);}//开放电使能
#define CloseFD()    {P9OE &= (~BIT0);P9IE &= (~BIT0);P9OD &= ~BIT0;P9FS&= (~BIT0);}//关放电使能

//#define DetEnable()  {P1OE|=BIT4;P1IE|=BIT4;P14FS=0;}	       //电压检测使能
//#define DetDisable() {P1OE&=(~BIT4);P1IE|=BIT4;P14FS=0;}	   //
//#define PwrDetLow()  (P1ID & BIT4)               //电源监测 
  

#define MEA_ON     0xFF
#define MEA_OFF    0x00

#define PLL_OSC    0x00
#define PLL_800K   0x01
#define PLL_3D2M   0x04
#define PLL_6D5M   0x08
#define PLL_13M    0x10
#define PLL_26M    0x20



MCUDRIVEEXT uint8 guc_PllSta;
//MCUDRIVEEXT uint8 guc_PluseCount;
MCUDRIVEEXT uint8 guc_PendSlpSta;
MCUDRIVEEXT uint16 gui_BatLowFlg;

void Mcu_Init(void);
void Init_Timer0(void);
void Init_Timer1(uint16);
uint8 Mcu_PendTm(uint8);
void  Mcu_RTCNormal(uint8);
void  Mcu_ChkSfr(void);
void GetExtRTC(void);           //获取硬时钟
void SetExtRTC(void);
//void SetExtRTC(uint8 ucSec, uint8 ucRTC);           //设置硬时钟
void GetBat(void);
void DelayOSC(uint8 num);
void MChannelCal(void);
void Init_Uart(void);
void SwichPluseOutType(uint8 type);
void MCUForPowerOff(void);
uint8 Sleep(void);
void UARTOFF(void);
void IntOFF(void);
void IOOFF(void);
uint8 SleepRTC(void);
uint8 SetPLL800K(uint8);
uint8 SetPLL3DOT2M(uint8);
uint8 PowOffSetFmcu(uint8);
uint8 SetPLL13M(uint8);
void RTCWakeUpTm(uint8, uint8);
void BgCtrFun(void);
void PowUpLedCtl(void);
void EnableRTCInt(void);
void DisableRTCInt(void);

void EventOutProc(void);

#endif
