#ifndef __pxv9811b_hpp_
#define __pxv9811b_hpp_


enum ENUMDEBUGLIST
{
	_debugnull_ = 0,
	_debugwdg_,
        _debug_errno_DataRestorestart_,
        _debug_errno_flashdatarestore_,
	_debugerrorbreak_,
	_debug_app_nobreak_,
        _debug_errno_resetvector_,
	_debug_errno_wdgout_,
        _debug_errno_WriteEEprom_,
	 _debug_errno_WriteEEpromError_,
	
	
	_debug_errno_prog_reset_,
	_debug_errno_null_,
	_debug_errno_4428_UsercardOver_,
	_debug_errno_KeyIn_,
	_debug_app_uart2_int_,
	_debug_errno_end_,
};
 


 
struct STSYSSTATE
{
  char  bPWRUP:1;
  char  bPWRDN:1;
  char  bRTC_CF:1;
  char  bIO:1;
  char  bbtemp11:1;
  char  bPOR:1;
  char  btemp21:2;
};
 
 

struct  STERRRLIST
{
  char                bExtJlParaErr:1;          //       计量参数外部初始化错误
  char                btemp2:1;          //       计量参数外部初始化错误
  char                btemp3:1;          //       计量参数外部初始化错误
  char                btemp4:1;          //       计量参数外部初始化错误
  char                btemp5:1;          //       计量参数外部初始化错误
  char                btemp6:1;          //       计量参数外部初始化错误
  char                btemp7:1;          //       计量参数外部初始化错误
  char                btemp8:1;          //       计量参数外部初始化错误
  
};



struct          STGLOBALlIST
{
  struct  STERRRLIST   sterrlist;
  char               bDebugMode:1;
  char               bPwrup:1;  
};

 
void            debug_init(void);
void  debug_ledshow(void);
char 	debug_break( enum ENUMDEBUGLIST cErrno);
extern char     cDispprt;
#endif

