#ifndef _Timer0capture_hpp_
#define _Timer0capture_hpp_

#include "pubset.h"

#define                 _TimerACheckTm_                     (3000/_cMain_sequentialTime_ )
#define                 _TimerACheckPreTm_                  (5000/_cMain_sequentialTime_ )
#define                 _IsTimerACheck()                (stperiod.iCheckTm)
struct STPERIOD
{
  volatile unsigned char cInit;   //            ���ֶαض�Ϊ��һ������
  unsigned short iCurr;                 //       ���ֶαض�Ϊ�ڶ�������
  volatile unsigned short iPrev;       
  
  volatile unsigned short iData[8];
  struct STBYTESTATU stdatano;
  struct STBITSTATU stLStatu;  
  unsigned short iCheckTm;
  unsigned short          iLnCheckPreTm;          //       ������LN�߼����ʱ
  unsigned char cHighTm;
  unsigned char cLowTm;
  
};

extern volatile struct STPERIOD stperiod;

#define              _stperiod_Clr_io()            ClrRam((char *) &(stperiod), sizeof (stperiod))
#define              _stperiod_Clr_app()            ClrRam((char *) &(stperiod.iPrev), sizeof (stperiod)-sizeof(stperiod.cInit))


void TimerA_Capture_Reg_Init (void);
void TimerA_Capture_Init (void);
void TimerA_Capture_Intfun (void);
void TimerA_Capture_Mainfun (void);
void
TimerA_Capture_Reg_Close (void) ;
void TimerA_Catupre_Mainint_fun(void);

#define _TimerA_Capture_Reg_CloseIo()  { TimerA_Capture_Reg_Close(); stperiod.cInit =0;}

#define         _Isstperiodfristcheck()         ( 0 == stperiod.cInit)
#define         TimerA_Capture_App_Init()	                { if (_Isstperiodfristcheck()) TimerA_Capture_Init();} // �����жϳ���,��ʼ��������
 
#endif
