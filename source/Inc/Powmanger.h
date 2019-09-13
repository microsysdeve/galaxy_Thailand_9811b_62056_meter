
#ifndef _POWMANGE_H_
#define _POWMANGE_H_

#ifndef POWMANGE_EXT
#define POWMANGE_EXT extern
#endif

typedef struct
{
    uint8 ucType;
    uint8 ucSlpCnt;
    uint8 ucTmDly; 
    uint8 ucIncntA;
    uint8 ucIncntB;
}GS_WAKEUP;

POWMANGE_EXT GS_WAKEUP gs_WakeUp;
POWMANGE_EXT uint8  guc_SleepCnt;
POWMANGE_EXT uint16 gs_powerErr;
POWMANGE_EXT uint32 gul_DataCP;
POWMANGE_EXT uint32 gul_DatCFcnt;
POWMANGE_EXT uint8 guc_DatCFrmd;
POWMANGE_EXT uint16 gui_DatCFdec;
POWMANGE_EXT uint32 gul_Test;


void Pwr_DownChk(void);
uint8 Pwr_DownProc(void);
void Pwr_WakeupProc(void);
void Pwr_SleepProc(void);
void Pwr_LcdSet(void);
//void Pwr_E2Save(void);
#define Pwr_E2Save()  {} 
void Pwr_SlpReset(void);
bool Pwr_ChkProc(void);

#endif
