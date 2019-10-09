#include "Include.h"
#include "pubset.h"

#include "Timer0Capture.h"

#define                 _bCaptureBit_           BIT0
struct STPERIOD stperiod;

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
  PRCtrl0 |= BIT0;
  P9FS &= ~_bCaptureBit_;
}

void
TimerA_Capture_Reg_Init (void)
{
  PRCtrl0 &= ~BIT0;

  P9OE |= _bCaptureBit_;
  P9IE |= _bCaptureBit_;
  P9FS |= _bCaptureBit_;
  TACTL = 0xc0 + 0x28;		//00101000;//             ʱ��Դѡ�� 1, fMCU
  TACCTH0 = 0x41;		//0b01000001 ;
  TACCTL0 = 0x10;		//0b00010000;  //�����ж�ʹ��
  ExInt5IE |= BIT1;
 NSel_Low();
  LSel_Low();
  EIE |= BIT3;
}

void
TimerA_Capture_Init (void)	// �����жϳ���
{
  ClrRam ((char *) &stperiod, sizeof (stperiod));
  TimerA_Capture_Reg_Init ();
}

void
TimerA_Capture_Intfun (void)	// �����жϳ���
{

  unsigned short itemp;
  debug_ledshow ();
  itemp = ((unsigned short) TACCR0H);
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
  TACCTL0 = 0x10;

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
