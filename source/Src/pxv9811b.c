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
	cErrlistno = cErrno ;
	return (cErrlistno +1) ;
}

       
      const unsigned short   iRegList[] =
      {
       PMCtrl1 ,//        0x2878      //PM���ƼĴ���1
PMCtrl2,//         0x2879      //PM���ƼĴ���2
PMCtrl3   ,//      0x287a      //PM���ƼĴ���3
PHCCtrl1     ,//   0x287b      //�ǲ�У�����ƼĴ���1
PHCCtrl2    ,//    0x287c      //�ǲ�У�����ƼĴ���2
PMCtrl4     ,//    0x287d      //PM���ƼĴ���4
CFCtrl      ,//    0x287e      //����������ƼĴ���
CRPST       ,//    0x287F      //��Ǳ��־�Ĵ���
IDET         ,//   0x2886      //�������   
GATEP ,//      ���ü�����ʼֵ
GATEQ ,// 
 
  GATECP,     //Ǳ��1   
    GATECQ,      //Ǳ��2  
    SCP,      // 13      0x10e8
  SCQ ,      // 0x10e9
 SCU  ,      //    0x10ea
  SCI1  ,      //    0x10eb
  SCI2  ,      //    0x10ec
  PARAPC ,      //   0x10ed
  PARAQC  ,      //   0x10ee
  PARABPF  ,      //  0x10ef
      /* 
 0x10f0+0,
 0x10f0+1,
 0x10f0+2,
 0x10f0+3,
 0x10f6+0,
 0x10f6+1,
 0x10f6+2,
 0x10f6+3, 
 */
       };
  volatile  char       cFirst ;
unsigned  long  iReg[ sizeof(iRegList)/sizeof(iRegList[0])];


void            Value_put ( unsigned long lData, unsigned short iAddr )
{
  
    char          i  ;
    
     for ( i =0 ;i < sizeof(iRegList)/sizeof(iRegList[0]);i++)      
      {
          if ( iRegList[i] == iAddr )
          {
                iReg[i] = lData;
                break;
          }
       
      }
        if ( iAddr == SCP )
            debug_break( _debug_errno_ParaSCPWRITE_) ;
}

     
   void   DoSinglePhase_1(void)
   {
    
    volatile  unsigned long      ltemp ,ltemp1;
     
     char       ctemp ,i;
 
          
      for ( i =0 ;i < sizeof(iRegList)/sizeof(iRegList[0]);i++)      
      {
            ltemp = EnyB_ReadMeterParaACK(iRegList[i]);             
        if ( 0 == cFirst )
              iReg[i] = (ltemp & 0xffffffff);
        else
        {
                ltemp1 = ltemp & 0xffffffff ;
              if ( iReg[i] != ltemp1)
                    EnyB_SetMeterCfgACK(iReg[i],iRegList[i]);  //�򿪼���,����Ǳ������
        }
    
      }
        
   } 
      
void   iReg_Clear(void)
{
    ClrRam( (char *)iReg, sizeof(iReg));
}