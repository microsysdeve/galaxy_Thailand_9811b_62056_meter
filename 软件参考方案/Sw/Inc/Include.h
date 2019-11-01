#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#ifndef VAREXT
    #define VAREXT extern
#endif

#include "LigReg.h"
#include "string.h"
#include "intrinsics.h"
#include "math.h"
#include "TypeDef.h"
#include "Api.h"
#include "E2AddTab.h"
#include "BEBottom.h"
#include "DataProtect.h"
#include "System.h"
#include "McuDrive.h"
#include "Key.h"
//#include "KeyProc.h"
#include "LcdBottom.h"
#include "ComConfig.h"
#include "ComBottom.h"
#include "Uart2.h"
#include "Uart4.h"
#include "ComApplication.h"
#include "Ptl_1107.h"
#include "Prcfrm.h"
#include "ComCoretab.h"
#include "DLT_645_2007.h"
#include "EnergyBottom.h"
#include "Energy.h"
#include "Demand.h"
#include "Multariff.h"
#include "Timeproc.h"
#include "Lcdmiddle.h"
#include "Lcdshow.h"
#include "Dataproc.h"
//#include "RtcCpt.h"
#include "Powmanger.h"
#include "InitPara.h"
#include "Version.h"



VAREXT uint16 gui_SystemEvent;
#define flgEtGlb_PowDown        0x01
#define flgEtGlb_EnergyCalc     0x04
#define flgEtGlb_RefreshLcd     0x08
#define flgEtGlb_NeedPrtclChk   0x10
#define flgEtGlb_ClearEv        0x20
#define flgEtGlb_ClearMeter     0x40
#define flgEtGlb_FirstPulse     0x80
#define flgEtGlb_DemadProc      0x100

VAREXT uint8 guc_TimeEvent;
#define flgEtTim_Second   0x01
#define flgEtTim_Minute   0x02
#define flgEtTim_Hour     0x04
#define flgEtTim_SecSoft  0x08
#define flgEtTim_Day      0x10


VAREXT uint8 guc_KeyEvent;
#define flgEtKey_Up             0x01
#define flgEtKey_Pr             0x02


VAREXT uint16 gui_RefreshEvent;
#define flgEtPara_Fee           0x0001
#define flgEtPara_EnyBottom     0x0002
#define flgEtPara_Config        0x0004
#define flgEtPara_RTC           0x0008
#define flgEtPara_Bode          0x0010
#define flgEtPara_Show          0x0020
#define flgEtPara_Init          0x0040
#define flgEtPara_RtcParaFsToE2 0x0080
#define flgEtPara_LoadCurve     0x0100
#define flgEtPara_PowDir        0x0200
#define flgEtPara_FrsJsr        0x0400
 
 


VAREXT uint16 gui_SystemState;
#define flgStSys_Program  0x01
#define flgStSys_IsTodayJS 0x02
#define flgStSys_PowOffing 0x04
#define flgStSys_PowOff 0x08
#define flgStSys_PowErr 0x10


VAREXT uint8  guc_SecCnt;
VAREXT uint8  guc_500msCnt;
VAREXT uint8 guc_MeterSysSta;
VAREXT uint16 gui_SystemSleepState;

#define  _IsSecuProduct  (gui_SystemState&flgStSys_Program)
#define _SYS_IS_PWR_OFF  (gui_SystemState&flgStSys_PowOff)

#endif

