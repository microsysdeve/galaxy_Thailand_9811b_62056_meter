#include "Include.h"
#include "pxv9811b.h"

struct          STGLOBALlIST  stgloballist;

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
{
	if ( cErrno>_debugerrorbreak_)		       
	cErrno +=1;
	return cErrno;
}

/*

 while(1)
    {
         CLRWDT();               //ι��
    BE_ReadP(12,(uint8 *)stemp,sizeof(stemp));
    stemp[0]*=2;
    for ( i =2 ; i < sizeof(stemp);i++)
        stemp[i]= stemp[i-1] + stemp[i-2];
    BE_WriteP(12,(uint8 *)stemp,sizeof(stemp));
    memset( stemp , 0 , sizeof(stemp));
    }

*/