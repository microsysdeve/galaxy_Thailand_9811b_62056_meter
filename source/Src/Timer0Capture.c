#include "Include.h"
#include "pubset.h"

#include "Timer0Capture.h"

#define                 _bCaptureBit_           BIT0
volatile  struct STPERIOD stperiod;

unsigned short
getwidth (unsigned short a, unsigned short b)
{
  if (a >= b)
    return (a - b);
  else
    return (65535 - b + a);
}

void
TimerA_Capture_Reg_Close (void)
{
  Vector11_Disable();    
  PRCtrl0 |= BIT0;
  P9FS &= ~_bCaptureBit_;
  _stperiod_Clr_app();
  stperiod.cInit =1;
}

void
TimerA_Capture_Reg_Init (void)   
{

  PRCtrl0 &= ~BIT0;
  P9OE |= _bCaptureBit_;
  P9IE |= _bCaptureBit_;
  P9FS |= _bCaptureBit_;
  TACTL = 0xc0 + 0x28;		//00101000;//             时钟源选择。 1, fMCU
  TACCTH0 = 0x41;		//0b01000001 ;
  TACCTL0 = 0x10;		//0b00010000;  //捕获中断使能
  ExInt5IE |= BIT1;
 NSel_Low();
  LSel_Low();
  Vector11_Enable() ; 
}
            
void
TimerA_Capture_Init (void)	// 捕获中断程序,初始化，并打开
{
  _stperiod_Clr_app();   
  stperiod.iLnCheckPreTm = _TimerACheckPreTm_;  
  //stperiod.iCheckTm = _TimerACheckTm_ ;
  //TimerA_Capture_Reg_Init ();
  debug_break(_debug_fun_TimerCheck_);
}

void
TimerA_Capture_Intfun (void)	// 捕获中断程序
{
  unsigned short itemp;
  debug_ledshow ();
  itemp = ((unsigned short) TACCR0H);
  TACCTL0 = 0x10;
  itemp *= 256;
  itemp += TACCR0L;
  if (0 == stperiod.cInit)
    {
      stperiod.cInit++;
    }
  stperiod.iData[stperiod.stdatano.cCurr++] =
    getwidth (itemp, stperiod.iPrev);
  stperiod.stdatano.cCurr %=
    sizeof (stperiod.iData) / sizeof (stperiod.iData[0]);
  stperiod.iPrev = itemp;
  /*
  do 
  {
    TACCTL0 = 0x10;
      itemp = TACCTL0 ;
  }while( itemp &0x3);
  */

}

void
TimerA_Capture_Mainfun (void)
{
  unsigned char i;
  unsigned long ltemp;
  const char cGate = 5;
   if (_nIsChangeState (stperiod.stdatano))
    {
      for (ltemp = 0, i = 0;
	   i < sizeof (stperiod.iData) / sizeof (stperiod.iData[0]); i++)
	ltemp += stperiod.iData[i];
      ltemp = ltemp / (sizeof (stperiod.iData) / sizeof (stperiod.iData[0]));
      stperiod.iCurr = (unsigned short) ltemp;

      _nStateGoOn (stperiod.stdatano);;
      _SoftFilter_t ((stperiod.iCurr > 20000), stperiod.cHighTm,
		     stperiod.cLowTm, cGate) _nGoon (stperiod.stLStatu);
      if (stperiod.cHighTm >= cGate)
	stperiod.stLStatu.bCurr = 1;
      if (stperiod.cLowTm >= cGate)
	stperiod.stLStatu.bCurr = 0;
    }
}

void TimerA_Catupre_Mainint_fun(void)
{
   if ( stperiod.iLnCheckPreTm )
   {
      stperiod.iLnCheckPreTm--;
      if ( 0 == stperiod.iLnCheckPreTm )
      {
            stperiod.iCheckTm = _TimerACheckTm_; 
            TimerA_Capture_Reg_Init ();
      } 
            
   } else
  if (stperiod.iCheckTm)
  {
      stperiod.iCheckTm--;
      if (0 == stperiod.iCheckTm)
        TimerA_Capture_Reg_Close ();
  }
}
