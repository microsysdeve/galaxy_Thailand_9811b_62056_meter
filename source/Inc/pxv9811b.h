#ifndef __pxv9811b_hpp_
#define __pxv9811b_hpp_


enum ENUMDEBUGLIST
{
  _debugnull_ = 0,
  _debug_errno_null_ = 0,
  _debugwdg_,
  _debug_errno_DataRestorestart_,
  _debug_errno_flashdatarestore_,
  _debug_errno_CFIn_,
  _debug_errno_4428_UsercardOver_,
  _debug_errno_KeyIn_,
  _debug_app_uart2_int_,
  _debug_errno_ComBom_Init_,

  _debug_int_0_,
  _debug_int_1_,
  _debug_int_2_,
  _debug_int_3_,
  _debug_int_4_,
  _debug_int_5_,
  _debug_int_6_,
  _debug_int_7_,
  _debug_int_8_,
  _debug_int_9_,
  _debug_int_10_,
  _debug_int_11_,
  _debug_int_12_,
  _debug_int_13_,     
  _debug_errno_EnyB_ReadMeterParaACK_,
  _debug_errno_62056_frame_CrcFAIL1_,
  _debug_errno_62056_frame_CrcFAIL2_,
  _debug_errno_62056_frame_CrcFAIL_,
  _debug_errno_62056_frame_FunFAIL_,

  _debug_errno_ParaSCPWRITE_,
  _debug_errno_SetPLL800K_FAIL1_,
  _debug_errno_SetPLL800K_FAIL2_,
  _debug_errno_SetPLL800K_FAIL3_,
  _debugerrorbreak_,		//===========================
  _debug_app_nobreak_ = _debugerrorbreak_,
  _debug_errno_resetvector_,
  _debug_errno_wdgout_,
  _debug_errno_WriteEEprom_,
  _debug_errno_WriteEEpromError_,
 _debug_errno_turonntstate_instate_,
  _debug_errno_turoffintstate_instate_,
  _debug_errno_StartupCheckState_,
  _debug_fun_vdcincheck_,
  _debug_fun_Pwr_SlpReset_,
  _debug_errno_prog_reset_,
  _debug_fun_PoweroffDisp_,
  _debug_fun_statuchange_,
  _debug_fun_IntOFF_,
  _debug_errno_JLChangeChanelL_,
  _debug_errno_JLChangeChanelN_,
  _debug_errno_ChangeClkSource_,
_debug_errno_ChangePmctrl4_,

  _debugh_fun_Pwr_WakeupProc_,
  _debug_gotosleep_,
  _debugh_fun_Mcu_PendTm_,
  

  _debug_errno_end_,
};




struct STSYSSTATE
{
  char bPWRUP:1;
  char bPWRDN:1;
  char bRTC_CF:1;
  char bIO:1;
  char bbtemp11:1;
  char bPOR:1;
  char btemp21:2;
};



struct STERRRLIST
{
  char bExtJlParaErr:1;		//       ���������ⲿ��ʼ������
  char btemp2:1;		//       ���������ⲿ��ʼ������
  char btemp3:1;		//       ���������ⲿ��ʼ������
  char btemp4:1;		//       ���������ⲿ��ʼ������
  char btemp5:1;		//       ���������ⲿ��ʼ������
  char btemp6:1;		//       ���������ⲿ��ʼ������
  char btemp7:1;		//       ���������ⲿ��ʼ������
  char btemp8:1;		//       ���������ⲿ��ʼ������

};

struct  STCRPST
{
  
  unsigned char  b2IAPHC:2; 
  unsigned char  b2IBPHC:2;
unsigned char  b3CFWD:3;
unsigned char  bCRPSTR:1;
unsigned char  bCRPST:1;
};

struct STGLOBALlIST
{
  struct STERRRLIST sterrlist;
  char bDebugMode:1;
  char bPwrup:1;
};


void debug_init (void);
void debug_ledshow (void);
char debug_break (enum ENUMDEBUGLIST cErrno);
extern char cDispprt;
void iReg_Clear (void);


typedef struct
{
  unsigned long _PMCtrl1;			//        0x2878      //PM���ƼĴ���1
  unsigned long _PMCtrl2;			//         0x2879      //PM���ƼĴ���2
  unsigned long _PMCtrl3;			//      0x287a      //PM���ƼĴ���3
  unsigned long _PHCCtrl1;			//   0x287b      //�ǲ�У�����ƼĴ���1
  unsigned long _PHCCtrl2;			//    0x287c      //�ǲ�У�����ƼĴ���2
  unsigned long _PMCtrl4;			//    0x287d      //PM���ƼĴ���4
  unsigned long _CFCtrl;			//    0x287e      //����������ƼĴ���
  unsigned long _CRPST;			//    0x287F      //��Ǳ��־�Ĵ���
  unsigned long _IDET;				//   0x2886      //�������   
  unsigned long _GATEP;			//    9  ���ü�����ʼֵ
  unsigned long _GATEQ;			//  10

  unsigned long _GATECP;			//Ǳ��1   
  unsigned long _GATECQ;			//Ǳ��2  
  unsigned long _SCP;			// 13      0x10e8
  unsigned long _SCQ;				// 0x10e9
  unsigned long _SCU;				//    0x10ea
  unsigned long _SCI1;				//    0x10eb
  unsigned long _SCI2;				//    0x10ec
  unsigned long _PARAPC;			//   0x10ed
  unsigned long _PARAQC;			//   0x10ee
  unsigned long _PARABPF;			//  0x10ef
  unsigned long _PPCNT;// ����E1 �����ۼӼĴ��� R/W 0 32-bit �޷�����
unsigned long _NPCNT;// ����E1 �����ۼӼĴ��� R/W 0 32-bit �޷�����
unsigned long _PPCFCNT;// ����E1 ������������� R/W 0 32-bit �޷�����
unsigned long _NPCFCNT;// ����E1 ������������� R/W 0 32-bit �޷�����
unsigned long _PQCNT;// ����E2 �����ۼӼĴ��� R/W 0 32-bit �޷�����
unsigned long _NQCNT;// ����E2 �����ۼӼĴ��� R/W 0 32-bit �޷�����
unsigned long _PQCFCNT;// ����E2 ������������� R/W 0 32-bit �޷�����
unsigned long _NQCFCNT;// ��
}STREG;

extern volatile    STREG  *streg;
void  debug_progdef(void);
#endif
