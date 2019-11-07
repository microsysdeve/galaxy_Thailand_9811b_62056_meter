#ifndef _adcfun_hpp_
#define _adcfun_hpp_

#define          _cLvdFilter_       2
#define    _stadcfunvollistlen_  4
enum  ENUMADCDATANOLIST
{
  _adc_lvdin0_ = 0,
  _adc_lvdin1_,
  _adc_bat_,
  _adc_end_,
};

enum   CHANELNAME
{
  _adcio_gnd_ =  0,//:测内部地；
  _adcio_temp_ =1,//: 测温度；
  _adcio_bat_ =2,//010: 测经BAT 引脚输入的电池电压信号或其它外部直流信号；
  _adcio_um_ =4,//100: 测经UM 引脚输入的外部直流信号；
  _adcio_m0_  =5,//101: 测经M0 引脚输入的外部直流信号；
    _adcio_m1_=6,//110: 测经M1 引脚输入的外部直流信号；
    _adcio_lvdin0_ =  _adcio_m1_,  
    _adcio_m2_=7,//111: 测经M2 引脚输入的外部直流信号。
    _adcio_lvdin1_ =_adcio_m2_,
};

#define    _clvdin0        stAdcFun.stAdcData[_adc_lvdin0_].cVol
#define    _clvdin1        stAdcFun.stAdcData[_adc_lvdin1_].cVol
#define    _cBat0          stAdcFun.stAdcData[_adc_bat_].cVol

enum ENUMADDCRUNSTATU
{
  _enAdc_Null_ = 0,
  //_enAdc_Start_ ,
  _enAdc_In0Wait_,// =_enAdc_Start_ ,
  _enAdc_In0DataGet_,
  //_enAdc_In1Wait_,
  _enAdc_In1DataGet_,
  _enAdc_Norend_,  

  _enAdc_BatSetChanel_,
  //_enAdc_BatWait_,
  _enAdc_BatGetData_,
  //_enAdc_TempWait_,
  _enAdc_TempDataGet_,
  _enAdc_StatuEnd_,
};

enum ENUMADCRETURNSTATU
{
  _enAdc_return_statu_allcycle_ = 0,
  _enAdc_return_statu_halcycle_ ,
  _enAdc_return_statu_going_ ,  
  _enAdc_return_statu_End_,
};

void Adc_Function (enum ENUMADDCRUNSTATU *cStatu);

struct STLVDBUF
{
  char cPoint;
  unsigned short cVol;
  unsigned short cVolList[_stadcfunvollistlen_];
};

struct STADCFUN
{

  struct STLVDBUF stAdcData[_adc_end_];
  unsigned short       iTime_Isr_no;
  unsigned char  cNormalState;
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
void vol_fileter (struct STLVDBUF *stp, unsigned short iVol);
unsigned short  vol_Get (enum  ENUMADCDATANOLIST  cno );
 
enum ENUMADCRETURNSTATU adc_appfun (void);

#define                 _IsLVol()       ( stAdcFun.cLvdin0_HighTm >= _cLvdFilter_ )  
#define                 _IsNVol()      ( stAdcFun.cLvdin1_HighTm >= _cLvdFilter_ )

#define                 _IsPowerOff()      ((  stAdcFun.cLvdin0_LowTm   >= _cLvdFilter_ )  &&  ( stAdcFun.cLvdin1_LowTm >= _cLvdFilter_ ))          

#define                 _IsUpEvent()   ( stAdcFun.cPwpUp1 >= _cLvdFilter_ )
#define                 _IsDnEvent()   ( stAdcFun.cPwpDn1>= _cLvdFilter_ )

#define _Adc_DataInit_Data()            {ClrRam((char *)&stAdcFun,sizeof(stAdcFun));}
#define _Adc_DataInit_state()           {stAdcFun.cBatStatu  = _enAdc_In0Wait_;}

#define         _GetBatVol(vol)             (vol/10)

#endif
