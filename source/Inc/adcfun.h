#ifndef _adcfun_hpp_
#define _adcfun_hpp_

#define          _cLvdFilter_       2

enum
{
  _adc_lvdin0_ = 0,
  _adc_lvdin1_,
  _adc_bat_,
  _adc_end_,
};


#define    _clvdin0        stAdcFun.stAdcData[_adc_lvdin0_].cVol
#define    _clvdin1        stAdcFun.stAdcData[_adc_lvdin1_].cVol
#define    _cBat0          stAdcFun.stAdcData[_adc_bat_].cVol

enum ENADCSTATU
{
  _enAdc_Null_ = 0,
  _enAdc_BatSetChanel_,
  _enAdc_BatWait_,
  _enAdc_BatGetData_,
  _enAdc_In0Wait_,
  _enAdc_In0DataGet_,
  _enAdc_In1Wait_,
  _enAdc_In1DataGet_,
  _enAdc_TempWait_,
  _enAdc_TempDataGet_,
  _enAdc_StatuEnd_,
};

void Adc_Function (enum ENADCSTATU *cStatu);

struct STLVDBUF
{
  char cPoint;
  unsigned short cVol;
  unsigned short cVolList[4];
};

struct STADCFUN
{

  struct STLVDBUF stAdcData[_adc_end_];
  unsigned char cBatStatu;
  volatile unsigned char cLvdin0_LowTm;
  volatile unsigned char cLvdin0_HighTm;
  volatile unsigned char cLvdin1_LowTm;
  volatile unsigned char cLvdin1_HighTm;
  volatile unsigned char cPwpUp1;
  volatile unsigned char cPwpUp0;
  volatile unsigned char cPwpDn1;
  volatile unsigned char cPwpDn0;

};
extern struct STADCFUN stAdcFun;
void Adc_DataInit (void);
void vol_fileter (struct STLVDBUF *stp, unsigned short  cVol);
unsigned short  vol_Get (struct STLVDBUF *stp);
char adc_appfun (void);

#define                 _IsLVol()      ( stAdcFun.cLvdin0_HighTm >= _cLvdFilter_ )
#define                 _IsNVol()      ( stAdcFun.cLvdin1_HighTm >= _cLvdFilter_ )

#define                 _IsUpEvent()   ( stAdcFun.cPwpUp1 >= _cLvdFilter_ )
#define                 _IsDnEvent()   ( stAdcFun.cPwpDn1>= _cLvdFilter_ )

#define _Adc_DataInit_Data()            {ClrRam((char *)&stAdcFun,sizeof(stAdcFun));}
#define _Adc_DataInit_state()           {stAdcFun.cBatStatu  = _enAdc_BatSetChanel_;}



#endif
