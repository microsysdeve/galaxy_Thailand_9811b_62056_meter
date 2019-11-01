#ifndef _LEOPARD_H_
#define _LEOPARD_H_
#include "type.h"
#ifdef LEOPARD
#define LEOPARDEX
#else
#define LEOPARDEX extern
#endif

LEOPARDEX u8 SetPLL(unsigned char val_para);
LEOPARDEX u8 DeepSleep(void);
LEOPARDEX u8 Sleep(void);
LEOPARDEX u8 SetMeterCfg(unsigned int addr,unsigned long u32PMdatal);
LEOPARDEX u32 ReadMeterPara(u16 addr);
LEOPARDEX void InitMeter(void);
LEOPARDEX void cfgmeter(void);
LEOPARDEX void FlashLPower(void);
LEOPARDEX void Init_Port(void);
LEOPARDEX void SetRTCInt(unsigned char cInterval);
LEOPARDEX void SETPLL_13MHZ(void);
LEOPARDEX void CLRPLL_13MHZ(void);
LEOPARDEX void SETPLL_26MHZ(void);
LEOPARDEX void CLRPLL_26MHZ(void);
LEOPARDEX void InitTestLCD(void);
LEOPARDEX void InitLCD(void);
LEOPARDEX unsigned char Read_50_60Hz(void);
#endif
