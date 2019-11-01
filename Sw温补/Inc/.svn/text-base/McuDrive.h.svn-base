#ifndef __MCUDRIVE_H__
    #define __MCUDRIVE_H__

#ifndef MCUDRIVEEXT
    #define MCUDRIVEEXT extern
#endif

#define V9811S    //9811S
#define FRCom     //载波表


#define SETPLL_CLOSE 0x00
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6f



#define SETLDO_25V 0
#define SETLDO_28V 1
#define SETLDO_22V 2
#define SETLDO_24V 3



#define SETLCD_30V 0x80 
#define SETLCD_33V 0
#define SETLCD_35V 0x10

#define RTCWAKEUP()     ((Systate&BIT2))    //RTC RST
#define IOWAKEUP()      ((Systate&BIT3))    //IO RST
#define POWERSTATE()    (!(Systate&BIT0))   //  1 有电  0 没电

#define CLRWDT()    {wdt0=0xA5;wdt1=0x5a;wdt0=0xA5;wdt1=0x5a;}

#ifdef V9811S
    #define InitCLRWDT()    {wdt0=0xA5;wdt1=0x5a;wdt0=0xA5;wdt1=0x5a;}
#else
    #define InitCLRWDT()    {for(uint8 i=0;i<64;i++){wdt0=0xA5;wdt1=0x5a;}}
#endif
#define RTC_SEC   0x00
#define RTC_MIN   0x01
#define RTC_HOUR  0x02


#define LCDSETTING4COM  0x82    //265hz  600K 4COM
#define LCDSETTING6COM  0x92    //265hz  600K 6com  


#define BATDIV      403948
#define BATLEVEL    2600
#define LCDREGLEN   17
#define BATOFFSET   77428752//23836396//5353488

//载波 接口
#define EVENTOUTHIGH() {P8OE&=(~BIT1);P8OD|=BIT1;}
#define EVENTOUTLOW()  {P8OE&=(~BIT1);P8OD&=(~BIT1);}
#define STAOUTHIGH()    {}
#define STAOUTLOW()     {}
#define FRRST()         {P8OE&=(~BIT0);P8OD&=(~BIT0);}  //输出低
#define FRRSTNO()       {P8OE|=BIT0;P8IE&=(~BIT0);}     //禁止输入输出

//LED
//打开背光
#define OpenBeiGuang()      {if(CalRMS(RMSIU)>1540){P8OE&=(~BIT2);P8OD|=BIT2;}else if(CalRMS(RMSIU)<1430){P8OE&=(~BIT2);P8OD&=(~BIT2);}}
//关闭背光
#define CloseBeiGuang()     {P8OE&=(~BIT2);P8OD&=(~BIT2);}
//三端口
#define CoverCheck()    {P0IE|=BIT2; P0OE&=~BIT1;P0OD|=BIT2;P0OD&=~BIT1;}
//按键
#define KeyPortIn()     {P1OE|=BIT3;P1IE|=BIT3;P13FS=0;P1IE|=BIT4;P1OE|=BIT4;P14FS=0;P9OE|=BIT0;P9IE|=BIT0;P9FC&=~BIT0;}        //                                               

#define KeyUpEnable()   {P1IE|=BIT4;P1OE|=BIT4;P14FS=0;}
#define KeyUpDisable()  {P1IE&=(~BIT4);P1OE|=BIT4;}
#define KeyStUp()       (!(P1ID & BIT4))                // 上翻按键

#define KeyPrEnable()    {P9IE|=BIT0;P9OE|=BIT0;P9FC&=~BIT0;}
#define KeyPrDisable()    {P9IE&=(~BIT0);P9OE|=BIT0;}
#define KeyStPr()       (!(P9ID & BIT0))               // 编程按键
//硬件接口预留
#define KeyBgEnable()    {P1IE|=BIT3;P1OE|=BIT3;P13FS=0;}
#define KeyBgDisable()    {P1IE&=(~BIT3);P1OE|=BIT3;}
#define KeyStBg()       (!(P1ID&BIT3))                           //表盖检测按键

//秒脉冲，多功能口
#define RATESWITCHIOHIGH() { P9OD|=(BIT3);}
#define RATESWITCHIOLOW() { P9OD&=(~BIT3);}

MCUDRIVEEXT uint8 guc_CoverCheck;     //掉电时开盖检测状态
MCUDRIVEEXT uint8 guc_PluseCount;
MCUDRIVEEXT int16 gi_BatCal;

uint16 Mcu_BatCal(void);
void CPUInit(void);
void Init_Timer0(void);
void Init_Timer1(void);
 

void GetExtRTC(void);           //获取硬时钟
void SetExtRTC(void);           //设置硬时钟
uint8 SetPLL13M(void);
void GetBat(void);
void DelayOSC(uint8 num);
void MChannelCal(void);
void ChangeBodeProc(void);
void SwichPluseOutType(uint8 type);
void MCUForPowerOff(void);
uint8 Sleep(void);
void UARTOFF(void);
void IntOFF(void);
void IOOFF(void);
uint8 SleepRTC(void);
uint8 SetPLL800K(void);
uint8 SetPLL3DOT2M(void);
void RTCWakeUpTm(uint8 Tm);
void BgCtrFun(void);
void PowUpLedCtl(void);
void EnableRTCInt(void);
void DisableRTCInt(void);
void Check_Sfr(void);
void EventOutProc(void);

#endif
