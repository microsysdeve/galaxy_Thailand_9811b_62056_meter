#ifndef __KEY_H__
    #define __KEY_H__


#ifndef KEY_EXT
    #define KEY_EXT extern
#else
    #define KEY_SELF
#endif

#define KeyNums     2
enum
{
  UpKey=0,
  PrKey,
};
enum
{
    TmOff=0,
    TmOn,
};

enum
{
    KeyRls=0,
    KeyDw,
    KeyDWLong,
};

typedef struct
{
    uint8 Status;       //按键状态，按下，释放
    uint8 TmStu;        //定时器状态
    uint8 DlyCnt;       //延时计数
    uint8 KeyThd;       //按键门限值
    uint8 LgKeyThd;     //长按键门限值
}KEYCTR;

KEY_EXT KEYCTR idata gs_KeyCtr[KeyNums];
KEY_EXT uint8   guc_DyBLed;                 // 背光延时控制寄存器
KEY_EXT uint16  gui_DyPgmOut;

 

#define KeyPortIn()     {P1OE|=(BIT3);P1IE|=(BIT3);\
                         P1OE|=(BIT4);P1IE|=(BIT4);}        //

#define KeyUpEnable()   {P1IE|=BIT3;P1OE|=BIT3;P13FS=0;}
#define KeyStUp()       (!(P1ID & BIT3))                // 上翻按键

#define KeyPrEnable()    {P1IE|=BIT4;P1OE|=BIT4;}
#define KeyStPr()       (!(P1ID & BIT4))               // 编程按键

#define InitKeyPort()   { }


#define Const_DyBLed   20

void KeyInit(void);
void KeyScan(void);
void KeyProc(void);
void ShowKeyProc(void);


#endif
