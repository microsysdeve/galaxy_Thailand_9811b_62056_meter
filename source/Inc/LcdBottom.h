#ifndef __LCDBOTTOM_H__
#define __LCDBOTTOM_H__

#ifndef LCDBOTTOMEXT
    #define LCDBOTTOMEXT extern
#endif


//#define Const_LCDRAMLen 40
 
enum            ENUMLCDRAMLIST
{
  _LCDM6_ = 0,
  _LCDM7_ ,
  _LCDM8_ ,
  _LCDM9_ ,
  _LCDM10_ ,
  _LCDM11_ ,
  _LCDM13_ ,
  _LCDM14_ ,
  _LCDM15_ ,
  _LCDM16_ ,
  _LCDM17_ ,
  _LCDMEnd_ ,
  Const_LCDRAMLen = _LCDMEnd_  ,
} ;
  

//LCDBOTTOMEXT uint8  guc_LCDRAM[Const_LCDRAMLen];

//extern  char   *guc_LCDRAM;

void Disp_Full(void);
void Disp_Clear(void);
void Disp_Clr(void);
void RefreshLCDRAM(char  *p);
void LCD_RAMUpdata(void);
void LCD_Off(void);
void LCDInitSleep(void);
void InitLCD(void);

enum    ENUMLCDDRIVERVOL
{
      _lcdvol_3do3_ =0,
      _lcdvol_3do0_ =1,
};

#define    LcdDriverVolSet_Con(a)              {if ( _lcdvol_3do3_ == a)  CtrlLCDV &=~BIT2; else CtrlLCDV |=BIT2;}
#define    _LcdDriverVolSet_33()         LcdDriverVolSet_Con(_lcdvol_3do3_)
#define    _LcdDriverVolSet_30()        LcdDriverVolSet_Con(_lcdvol_3do0_)
#endif