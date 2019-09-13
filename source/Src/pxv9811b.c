#include "Include.h"
#include "pxv9811b.h"

char     cDispprt;
struct          STGLOBALlIST  stgloballist;
enum ENUMDEBUGLIST   cErrlistno;
void  debug_ledshow(void)
{
    static char           xxxx ;
    if ( xxxx++ & 1)
            P9OD |=BIT5;
    else
            P9OD &=~BIT5;
}  
    
void            debug_init(void)
{
    stgloballist.bDebugMode =1;
    stgloballist.bPwrup =1;
}
  

char 	debug_break( enum ENUMDEBUGLIST cErrno)
{cErrlistno = cErrno ;
	if ( cErrno>_debugerrorbreak_)		       
	cErrlistno = cErrno+2 ;
	return (cErrlistno +1) ;
}

/*

 while(1)
    {
         CLRWDT();               //Î¹¹·
    BE_ReadP(12,(uint8 *)stemp,sizeof(stemp));
    stemp[0]*=2;
    for ( i =2 ; i < sizeof(stemp);i++)
        stemp[i]= stemp[i-1] + stemp[i-2];
    BE_WriteP(12,(uint8 *)stemp,sizeof(stemp));
    memset( stemp , 0 , sizeof(stemp));
    }

*/