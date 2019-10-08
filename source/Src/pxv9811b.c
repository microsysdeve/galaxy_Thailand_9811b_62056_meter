#include "Include.h"
#include "pxv9811b.h"

char     cDispprt;
struct          STGLOBALlIST  stgloballist;
volatile enum ENUMDEBUGLIST   cErrlistno;
void  debug_ledshow(void)
{
    static char           xxxx ;
    if ( xxxx++ & 1)
    { R2_LED_On();}
    else
    {R2_LED_Off();}
}  
  
    
void            debug_init(void)
{
    stgloballist.bDebugMode =1;
    stgloballist.bPwrup =1;
}
  

char 	debug_break( enum ENUMDEBUGLIST cErrno)
{cErrlistno = cErrno ;
	if ( cErrno>_debugerrorbreak_)	
        {
            cErrlistno = cErrno+1 ;
            cErrlistno = cErrno-1 ;
        }
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
uint8 StrLen(const uint8 code *src);
const char stemp1[] = "/?!\r\n";	//"\/?!\r\n";   //2f 3f 21 0d 0a
const char  sAsk[]= { 0xAF,0x3F,0x21,0x8D,0x0A,0};
void   init62056frm(S_COM *ComProcCtrl)
{
  gs_PtlCrt.uc_ComStep = 0;
  
  
     ComProcCtrl->ucPort=Port_Uart4;
     ComProcCtrl->ucLen = (unsigned char)StrLen(stemp1);;
     ComProcCtrl->ucPos = 0;
     ComProcCtrl->ucFrmHeadCnt=0;
        //��ʼ��ͨѶ״̬
      ComProcCtrl->ucStt =0;// ComStt_Idle;
     ComProcCtrl->ucRecvTmr = 0;                // ��ʱ����Ч״̬
     ComProcCtrl->ucOverTmr = 0;                // ��ʱ����Ч״̬
        CopyRam(ComProcCtrl->ucBuf,(char *)stemp1,ComProcCtrl->ucLen);
        return ;
}