
#include "Include.h"
#include "PubSet.h"
#include "adcfun.h"
#include "powerevent.h"
struct STADCFUN stAdcFun;



void
Adc_DataInit (void)
{
  _Adc_DataInit_Data ();
  _Adc_DataInit_state ();

}


void
vol_fileter (struct STLVDBUF *stp, char cVol)
{
  stp->cPoint %= sizeof (stp->cVolList);
  stp->cVolList[stp->cPoint++] = cVol;
}

unsigned char
vol_Get (struct STLVDBUF *stp)
{
  unsigned short itemp;
  unsigned char i;

  for (itemp = 0, i = 0; i < sizeof (stp->cVolList); i++)
    itemp += stp->cVolList[i];
  itemp /= sizeof (stp->cVolList);
  stp->cVol = (unsigned char) itemp;
  return stp->cVol;
}

unsigned short
Adc_DataGet (void)
{
  Word32 tempvalue;
  tempvalue.lword = EnyB_ReadMeterParaACK (DATAOM);
  if (tempvalue.byte[3] > 0x80)	//电池悬空的时候读取可能是负值
    {
      tempvalue.lword = (~tempvalue.lword) + 1;
    }
  tempvalue.lword = tempvalue.lword >> 16;
  tempvalue.lword = ((tempvalue.lword * 100 + 5069) / 5959);
  return (unsigned short) tempvalue.lword;
}

char
cAdcApp_Get (struct STLVDBUF *stp)
{
  vol_fileter (stp, (unsigned char) Adc_DataGet ());
  return vol_Get (stp);
}

#define       _start_adc_Conver(control ,iIso , statu) {  CtrlADC5 = control ; iIso  = iTime_Isr_no ; (statu)++;}


void
Adc_Function (enum ENADCSTATU *cStatu)
{
  static unsigned short iMainState;
  short itemp;
  extern volatile unsigned short iTime_Isr_no;
  switch (*cStatu)
    {

    case _enAdc_BatSetChanel_:
      _start_adc_Conver (0x92, iMainState, *cStatu);
      break;

    case _enAdc_BatWait_:
    case _enAdc_In0Wait_:
    case _enAdc_In1Wait_:
    case _enAdc_TempWait_:
      if (iMainState == iTime_Isr_no)
	break;
      else
	{
	  itemp = abs (iTime_Isr_no - iMainState);
	  if (itemp > 2)
	    (*cStatu)++;
	}
      break;

    case _enAdc_BatGetData_:
      RamData.VBat[0] = cAdcApp_Get (&(stAdcFun.stAdcData[_adc_bat_]));
      _start_adc_Conver (0x96, iMainState, *cStatu);
      break;

    case _enAdc_In0DataGet_:
      cAdcApp_Get (&(stAdcFun.stAdcData[_adc_lvdin0_]));
      _start_adc_Conver (0x97, iMainState, *cStatu);
      _SoftFilter_t ((_clvdin0 >= FData.sthardconfig.cSVD_On_Line_WorkVol),
		     stAdcFun.cLvdin0_HighTm, stAdcFun.cLvdin0_LowTm,
		     _cLvdFilter_);
      break;

    case _enAdc_In1DataGet_:
      cAdcApp_Get (&(stAdcFun.stAdcData[_adc_lvdin1_]));
      _start_adc_Conver (0x81, iMainState, *cStatu);
      _SoftFilter_t ((_clvdin1 >= FData.sthardconfig.cSVD_On_Line_MinVol),
		     stAdcFun.cLvdin1_HighTm, stAdcFun.cLvdin1_LowTm,
		     _cLvdFilter_);
      break;

    case _enAdc_TempDataGet_:
      (*cStatu)++;
      break;

    case _enAdc_Null_:
    case _enAdc_StatuEnd_:
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
    stAdcFun.cBatStatu = _enAdc_BatSetChanel_;

  return 1;
}
