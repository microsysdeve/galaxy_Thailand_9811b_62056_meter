#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#ifndef VAREXT
    #define VAREXT extern
#endif

#include "LeopardDReg.h"
//#include "LeoPartReg.h"
#include "string.h"
#include "intrinsics.h"
#include "math.h"
#include "TypeDef.h"
#include "BEBottom.h"
#include "DataProtect.h"
#include "Api.h"
#include "System.h"
#include "McuDrive.h"
#include "Key.h"
#include "Powmanger.h"
#include "ComConfig.h"
#include "ComBottom.h"
#include "Uart2.h"
#include "Uart1.h"
#include "Uart4.h"
#include "ComApplication.h"
#include "Prcfrm.h"
//#include "LoadCurve.h"
#include "ComCoretab.h"
#include "PrologFee.h"
#include "E2AddTab.h"
#include "DLT_645_2007.h"
#include "EnergyBottom.h"
#include "Energy.h"
//#include "Multariff.h"
#include "TamperProc.h"
#include "Timeproc.h"
#include "LcdBottom.h"
#include "Lcdmiddle.h"
#include "Lcdshow.h"
#include "Dataproc.h"
#include "FunCfg.h"
//#include "Event.h"
#include "InitPara.h"
#include "RtcCpt.h"
//#include "CmpCode.h"
#include "Demand.h"
#include "Version.h"
#include "ADKFunc.h"
#include "pxv9811b.h"
#include "pubset.h"
#include "Ptl_1107.h"

VAREXT uint16 gui_SystemEvent;
#define flgEtGlb_PowDown        0x01
#define flgEtGlb_EnergyCalc     0x04
#define flgEtGlb_RefreshLcd     0x08
#define flgEtGlb_NeedPrtclChk   0x10
//#define flgEtGlb_ClearEv        0x20
#define flgEtGlb_AutoCal        0x20
#define flgEtGlb_ClearMeter     0x40
#define flgEtGlb_DemadProc      0x80

VAREXT uint8 guc_TimeEvent;
#define flgEtTim_Second   0x01
#define flgEtTim_Minute   0x02
#define flgEtTim_Hour     0x04
#define flgEtTim_SecSoft  0x08
#define flgEtTim_Day      0x10
#define flgEtTim_Year     0x20

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
#define flgEtPara_ADKCal_11     0x0800
#define flgEtPara_ADKCal_15     0x1000
#define flgEtPara_ADKCal_31     0x2000

VAREXT uint8 guc_DjCheckFlg;    
#define flgDsDjCheck        0x01        
#define flgZdDjCheck        0x02
#define flgDayDjCheck       0x04
#define flgInsDjEvent       0x08
 
//VAREXT uint8  guc_SleepFlg;
VAREXT uint8  guc_PowOffRuning;
//VAREXT uint16 gui_WakeUpCnt;
//VAREXT uint8  guc_SysSecCnt;

VAREXT uint16 gui_SystemState;
#define flgStSys_Program  0x01
#define flgStSys_IsTodayJS 0x02
#define flgStSys_PowOffing 0x04
#define flgStSys_PowOff 0x08
#define flgStSys_PowErr 0x10

VAREXT uint16 gui_SysSleepSta;

#define  _IsSecuProduct  (gui_SystemState&flgStSys_Program)
#define _SYS_IS_PWR_OFF  (gui_SystemState&flgStSys_PowOff)


#define                 _ChipDataSet_Bz_                0x12345678

#define                   _NegLogo_  0x800000
#define                   _NegLogeo_Set(a)   { a |=_NegLogo_;}


#define        R485Com      (*(( S_COM *)(&USARTCOM[0])))
#define              IRCom        (*(( S_COM *)(&USARTCOM[0])))

#define                 OpenGJLed()             {}
#endif

