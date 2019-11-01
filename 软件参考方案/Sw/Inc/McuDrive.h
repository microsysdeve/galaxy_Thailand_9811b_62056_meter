#ifndef __MCUDRIVE_H__
    #define __MCUDRIVE_H__


#define RTC_SEC   0x00
#define RTC_MIN   0x01
#define RTC_HOUR  0x02
#define RTC_DAY   0x03

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

#define CLRWDT()    {EA=0;WDTEN = 0xa5;WDTCLR = 0x5a; EA=1;}

#define OpenGJLed()   {/*P2OE&=~(BIT1);P2IE&=~(BIT1); P2OD|=(BIT1);*/}

#define CloseGJLed()   {/*P2OE&=~(BIT1);P2IE&=~(BIT1); P2OD&=~(BIT1);*/}

#define FlashGJLed()   {/*P2OE&=~(BIT1);P2IE&=~(BIT1); P2OD^=(BIT1);*/}

uint8 SetPLL(uint8 PLLClk);
void SetLDOVolt(uint8 val_volt);
void InitLCD(void);
void CPUInit(void);
void Init_Timer0(void);
void Init_Timer1(void);
void Init_Timer2(void);
uint8 SetInterrupt(uint8 val_numb);
void Init_RTC(uint8 ucWakeUpTm);
void GetExtRTC(void);           //获取硬时钟
void SetExtRTC(void);           //设置硬时钟
void Sleep(void);
void IntOFF(void);
void UARTOFF(void);
void Check_Sfr(void);
void IdleIO(void);
#endif
