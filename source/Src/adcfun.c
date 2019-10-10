
#include "Include.h"
#include "PubSet.h"
#include "adcfun.h"
#include "powerevent.h"
struct STADCFUN stAdcFun;
#define             _IsLvdin0(a)  ( _adc_lvdin0_ == a)
#define             _IsLvdin1(a)  (_adc_lvdin1_ == a)
#define             _IsLvd(a)  (_IsLvdin0(a) || _IsLvdin1(a) )
void
Adc_DataInit (void)
{
  _Adc_DataInit_Data ();
  _Adc_DataInit_state ();
}

void
vol_fileter (struct STLVDBUF *stp, unsigned short cVol)
{
  char ctemp;
  ctemp = stp->cPoint++ % _stadcfunvollistlen_;
  stp->cVolList[ctemp] = cVol;
}

unsigned short
vol_Get (enum ENUMADCDATANOLIST cno)
{
  struct STLVDBUF *stp = &stAdcFun.stAdcData[cno];
  unsigned long ltemp;
  unsigned char i; 
  for (ltemp = 0, i = 0; i < _stadcfunvollistlen_; i++)
    ltemp += stp->cVolList[i];
  if (_IsLvd (cno))
    ltemp = ltemp * 10 / (263 * _stadcfunvollistlen_);
  else
    ltemp = ltemp /_stadcfunvollistlen_;
  stp->cVol = (unsigned short) ltemp;
  return stp->cVol;
}

unsigned short
Adc_DataGet (char cRESDIV)
{
  Word32 tempvalue;
  tempvalue.lword = EnyB_ReadMeterParaACK (DATAOM);
  if (tempvalue.byte[3] > 0x80)	//电池悬空的时候读取可能是负值
    {
      tempvalue.lword = (~tempvalue.lword) + 1;
    }
  tempvalue.lword = tempvalue.lword >> 16;
  if (0 == cRESDIV)
    return (unsigned short) tempvalue.lword;
  tempvalue.lword = ((tempvalue.lword * 100 + 5069) / 5959);
  return (unsigned short) tempvalue.lword;
}

char
cAdcApp_Get (enum ENUMADCDATANOLIST cno)
{
  struct STLVDBUF *stp = &stAdcFun.stAdcData[cno];
  char cRESDIV = _IsLvd (cno) ? 0 : 1;
  vol_fileter (stp, (unsigned short) Adc_DataGet (cRESDIV));
  return vol_Get (cno);
}

#define   _start_adc_Converio(control , statu) {  CtrlADC5 =   control ; (statu)++;}
#define   _start_adc_Conver(control , statu)   _start_adc_Converio(0x90|control , statu)

void
Adc_Function (enum ENADCSTATU *cStatu)
{
  short itemp;
  switch (*cStatu)
    {
    case _enAdc_In0Wait_:
      _start_adc_Converio (0x80 | _adcio_lvdin0_, *cStatu);
      break;
      
    case _enAdc_In0DataGet_:
      cAdcApp_Get (_adc_lvdin0_);
      _start_adc_Converio (0x80 | _adcio_lvdin1_, *cStatu);
      _SoftFilter_t ((_clvdin0 >= FData.sthardconfig.cSVD_On_Line_WorkVol),
		     stAdcFun.cLvdin0_HighTm, stAdcFun.cLvdin0_LowTm,
		     _cLvdFilter_);
      break;
      
    case _enAdc_In1DataGet_:
      cAdcApp_Get (_adc_lvdin1_);
      _SoftFilter_t ((_clvdin1 >= FData.sthardconfig.cSVD_On_Line_MinVol),
		     stAdcFun.cLvdin1_HighTm, stAdcFun.cLvdin1_LowTm,
		     _cLvdFilter_);
      if (++stAdcFun.cNormalState > 10)
	{
	  stAdcFun.cNormalState = 0;
	  _start_adc_Conver (_adcio_bat_, *cStatu);
	  *cStatu = _enAdc_BatGetData_;
	}
      else
	{
	  _start_adc_Converio (0x80 | _adcio_lvdin0_, *cStatu);
	  _Adc_DataInit_state ();
	}
      break;
      
    case _enAdc_BatGetData_:
      RamData.VBat[0] = cAdcApp_Get (_adc_bat_);
      _start_adc_Conver (_adcio_temp_, *cStatu);
      break;
      
    case _enAdc_TempDataGet_:
      _start_adc_Conver (_adcio_temp_, *cStatu);
      break;
    }
}

char
adc_appfun (void)
{
  _SoftFilter_t (_IsUpIo (), stAdcFun.cPwpUp1, stAdcFun.cPwpUp0,
		 _cLvdFilter_);
  _SoftFilter_t (_IsDnIo (), stAdcFun.cPwpDn1, stAdcFun.cPwpDn0,
		 _cLvdFilter_);
  if (stAdcFun.cBatStatu < _enAdc_StatuEnd_)
    {
      Adc_Function (&stAdcFun.cBatStatu);
      return 0;
    }
  else
    _Adc_DataInit_state ();
  return 1;
}
