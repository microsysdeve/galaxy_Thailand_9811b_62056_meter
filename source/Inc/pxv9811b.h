#ifndef __pxv9811b_hpp_
#define __pxv9811b_hpp_


enum ENUMDEBUGLIST
{
	_debugnull_ = 0,
	_debugwdg_,
	_debugerrorbreak_,
	_debugend_ ,
};
/*
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
*/


typedef struct  
{
  char  bPWRUP:1;
  char  bPWRDN:1;
  char  bRTC_CF:1;
  char  bIO:1;
  char  bbtemp11:1;
  char  bPOR:1;
  char  btemp21:2;
}STSYSSTATE;


struct          STGLOBALlIST
{
  char               bDebugMode:1;
  char               bPwrup:1;
  
};

//__no_init volatile  struct STSYSSTATE  stsysstate @ 0xa1;
__no_init volatile    STSYSSTATE  stsysstate @ 0xa1;
void            debug_init(void);
void  debug_ledshow(void);
char 		debugprintf( enum ENUMDEBUGLIST cErrno);

#endif

