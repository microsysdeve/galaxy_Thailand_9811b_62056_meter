#ifndef __pxv9811b_hpp_
#define __pxv9811b_hpp_


enum ENUMDEBUGLIST
{
	_debugnull_ = 0,
	_debugwdg_,
	_debugerrorbreak_,
	_debugend_ ,
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
char 		debugprintf( enum ENUMDEBUGLIST cErrno);

#endif

