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
    uint8 Status;       //����״̬�����£��ͷ�
    uint8 TmStu;        //��ʱ��״̬
    uint8 DlyCnt;       //��ʱ����
    uint8 KeyThd;       //��������ֵ
    uint8 LgKeyThd;     //����������ֵ
}KEYCTR;

KEY_EXT KEYCTR idata gs_KeyCtr[KeyNums];
KEY_EXT uint8   guc_DyBLed;                 // ������ʱ���ƼĴ���
KEY_EXT uint16  gui_DyPgmOut;

 

#define KeyPortIn()     {P1OE|=(BIT3);P1IE|=(BIT3);\
                         P1OE|=(BIT4);P1IE|=(BIT4);}        //

#define KeyUpEnable()   {P1IE|=BIT3;P1OE|=BIT3;P13FS=0;}
#define KeyStUp()       (!(P1ID & BIT3))                // �Ϸ�����

#define KeyPrEnable()    {P1IE|=BIT4;P1OE|=BIT4;}
#define KeyStPr()       (!(P1ID & BIT4))               // ��̰���

#define InitKeyPort()   { }


#define Const_DyBLed   20

void KeyInit(void);
void KeyScan(void);
void KeyProc(void);
void ShowKeyProc(void);


#endif
