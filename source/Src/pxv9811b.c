#include "Include.h"
#include "pxv9811b.h"

char cDispprt;
struct STGLOBALlIST stgloballist;
volatile enum ENUMDEBUGLIST cErrlistno;
void
debug_ledshow (void)
{
  static char xxxx;

  if (xxxx++ & 1)
    {
      R2_LED_On ();
    }
  else
    {
      R2_LED_Off ();
    }
}


void
debug_init (void)
{
  stgloballist.bDebugMode = 1;
  stgloballist.bPwrup = 1;
}


char
debug_break (enum ENUMDEBUGLIST cErrno)
{
  cErrlistno = cErrno;
  if (cErrno > _debugerrorbreak_)
    {
      NOP_ASM ();

    }
  return (cErrlistno + 1);
}

const unsigned short iRegList[] = {
  PMCtrl1,			//        0x2878      //PM控制寄存器1
  PMCtrl2,			//         0x2879      //PM控制寄存器2
  PMCtrl3,			//      0x287a      //PM控制寄存器3
  PHCCtrl1,			//   0x287b      //角差校正控制寄存器1
  PHCCtrl2,			//    0x287c      //角差校正控制寄存器2
  PMCtrl4,			//    0x287d      //PM控制寄存器4
  CFCtrl,			//    0x287e      //脉冲输出控制寄存器
  CRPST,			//    0x287F      //防潜标志寄存器
  IDET,				//   0x2886      //电流检测   
  GATEP,			//    9  设置计量初始值
  GATEQ,			//  10
 
  GATECP,			//潜动1   
  GATECQ,			//潜动2  
  SCP,				// 13      0x10e8
  SCQ,				// 0x10e9
  SCU,				//    0x10ea
  SCI1,				//    0x10eb
  SCI2,				//    0x10ec
  PARAPC,			//   0x10ed
  PARAQC,			//   0x10ee
  PARABPF,			//  0x10ef
  
  PPCNT,// 正向E1 能量累加寄存器 R/W 0 32-bit 无符号数
NPCNT,// 反向E1 能量累加寄存器 R/W 0 32-bit 无符号数
PPCFCNT,// 正向E1 能量脉冲计数器 R/W 0 32-bit 无符号数
NPCFCNT,// 反向E1 能量脉冲计数器 R/W 0 32-bit 无符号数
PQCNT,// 正向E2 能量累加寄存器 R/W 0 32-bit 无符号数
NQCNT,// 反向E2 能量累加寄存器 R/W 0 32-bit 无符号数
PQCFCNT,// 正向E2 能量脉冲计数器 R/W 0 32-bit 无符号数
NQCFCNT,// 反

};

volatile char cFirst;
unsigned long xdata   iReg[sizeof (iRegList) / sizeof (iRegList[0])];

extern volatile    STREG  *streg;
void
Value_put (unsigned long lData, unsigned short iAddr)
{

  char i;
    streg = ( STREG  *)iReg;
  for (i = 0; i < sizeof (iRegList) / sizeof (iRegList[0]); i++)
    {
      if (iRegList[i] == iAddr)
	{
	  iReg[i] = lData;
	  break;
	}

    }
  if (iAddr == SCP)
    debug_break (_debug_errno_ParaSCPWRITE_);
}


void
DoSinglePhase_1 (void)
{

  volatile unsigned long ltemp, ltemp1;

  char ctemp, i;


  for (i = 0; i < sizeof (iRegList) / sizeof (iRegList[0]); i++)
    {
      ltemp = EnyB_ReadMeterParaACK (iRegList[i]);
      if (0 == cFirst)
	iReg[i] = (ltemp & 0xffffffff);
      else
	{
	  ltemp1 = ltemp & 0xffffffff;
	  if (iReg[i] != ltemp1)
	    EnyB_SetMeterCfgACK (iReg[i], iRegList[i]);	//打开计量,保持潜动开启
	}

    }

}

void
iReg_Clear (void)
{
  ClrRam ((char *) iReg, sizeof (iReg));
}

uint8 StrLen (const uint8 code * src);
const char stemp1[] = "/?!\r\n";	//"\/?!\r\n";   //2f 3f 21 0d 0a
const char sAsk[] = { 0xAF, 0x3F, 0x21, 0x8D, 0x0A, 0 };

void
init62056frm (S_COM * ComProcCtrl)
{
  gs_PtlCrt.uc_ComStep = 0;


  ComProcCtrl->ucPort = Port_Uart4;
  ComProcCtrl->ucLen = (unsigned char) StrLen (stemp1);;
  ComProcCtrl->ucPos = 0;
  ComProcCtrl->ucFrmHeadCnt = 0;
  //初始化通讯状态
  ComProcCtrl->ucStt = 0;	// ComStt_Idle;
  ComProcCtrl->ucRecvTmr = 0;	// 定时器无效状态
  ComProcCtrl->ucOverTmr = 0;	// 定时器无效状态
  CopyRam (ComProcCtrl->ucBuf, (char *) stemp1, ComProcCtrl->ucLen);
  return;
}

void
INTERRUPT_DISABLE (void)
{
  EA = 0;
}


void
INTERRUPT_ENABLE (void)
{
  EA = 1;
}
