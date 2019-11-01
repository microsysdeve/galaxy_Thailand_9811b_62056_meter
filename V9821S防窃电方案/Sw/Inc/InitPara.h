#ifndef _INITPARA_H_
#define _INITPARA_H_

#ifndef INIT_EXT
    #define INIT_EXT extern
#endif

INIT_EXT const uint8 code InitPara0[];
INIT_EXT const uint8 code InitPara1[];
INIT_EXT const uint8 code InitPara2[];
INIT_EXT const uint8 code InitADK[];
INIT_EXT const uint8 code InitFwVer[];
INIT_EXT const uint8 code InitHwVer[];
//INIT_EXT uint8 guc_RTCSave;
void InitE2Data(void);
//INIT_EXT __root const uint8 code InitPara38[];
void E2DataChk(void);

#endif