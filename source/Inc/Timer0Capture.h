#ifndef _Timer0capture_hpp_
#define _Timer0capture_hpp_

#define                 _TimerACheckTm_                     (2000/_cMain_sequentialTime_ )

#define                 _IsTimerACheck()                (stperiod.iCheckTm)
struct STPERIOD
{
  
  volatile unsigned short iData[8];
  unsigned short iCurr;
  volatile unsigned short iPrev;
  volatile unsigned char cInit;
  unsigned char cHighTm;
  unsigned char cLowTm;
  struct STBYTESTATU stdatano;
  struct STBITSTATU stLStatu;  
  unsigned short iCheckTm;
};

extern volatile struct STPERIOD stperiod;

void TimerA_Capture_Reg_Init (void);
void TimerA_Capture_Init (void);
void TimerA_Capture_Intfun (void);
void TimerA_Capture_Mainfun (void);
void
TimerA_Capture_Reg_Close (void) ;
void TimerA_Catupre_Mainint_fun(void);
#endif
