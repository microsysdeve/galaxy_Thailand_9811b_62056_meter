#include "Include.h"
#include "streamio.h"
#include "uartiobase.h"
//��������
uint8   guc_DyUart4Over;        //ģ�⴮�ڳ�ʱ����

/*=========================================================================================\n
* @function_name: Init_Uart4
* @function_file: Uart4.c
* @����: uart4�ĳ�ʼ��
* 
* 
* @����: 
* @param:ucBode  ������  0-600  1-1200 2-2400 3-4800 4-9600
* @����: 
* @����:   lwb (2012-05-31)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
 
 
void Init_Uart4(uint8 ucBode)
{
volatile char    stemp[5],j;
 int i;
 //ucBode =_bps9600_;
  _UartInit(ucBode,TMOD4,TCON4,TL41,TH41,SCON4); 

  //SCON4 = 0x50;     
    P2OE &= ~BIT1;                      //Uart4���Ϳ��������
    P2IE &= ~BIT1;                      //Uart4���Ϳ������ֹ
    P2OE |= BIT0;                       //Uart4���տ������ֹ
    P2IE |= BIT0;                       //Uart4���տ���������
    P20FS=2;                            //P2.0���ó�RXD
    P21FS=2;                            //P2.1���ó�TXD
    
    ExInt2IE|=BIT2;
    ExInt2IE|=BIT3;
    EIE|=BIT0;
#ifdef RS485_TWOLINE
    Uart4_CtrIoIdle();
#else
    Uart4_RevEn();
#endif
  /*
    SCON4&=(~BIT4);
     gs_ComGroup[ComIndex_Uart4].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart4].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��
gs_ComGroup[ComIndex_Uart4].ucLen =0;
    gs_ComGroup[ComIndex_Uart4].ucStt  = ComStt_Idle;
      
 
                while (1)
                {
                  for ( j =0;j<128;j++)
                  {
                   SLPWDT();               //800kι��
                   SCON4 &=~BIT1;         
                  //_EvenMod(j,SCON4)  ;
                   //_SendOper(j,SBUF4);
                   SCON4|=(BIT3);
                   SBUF4 =   c7bitParity_Get(j,  _Parity_Even_);
       for ( i =0 ;i < 1000;i++)
       {
            if (SCON4 & BIT1)
            goto a2;
          asm("nop"); asm("nop"); asm("nop");
        }       
                  a2:
                }
                
                }
                  
a1:    
                SCON4|=(BIT4);
                SCON4&=~BIT0;
                j =0;
                EA=1;
                while (1)
                {
                     SLPWDT();
                     continue;
                        if (  SCON4 & BIT0)
                       {
                              stemp[j++] = SBUF4;
                              if ( j>=sizeof(stemp))
                                  j =0;
                             SCON4&=~BIT0;
                       }
                        
                }
    */
            
}
#ifdef DEL
void Init_Uart41(uint8 ucBode,uint8 uctype)
{
//  if(uctype==0x00)                            //62056-21
    {
        if(ucBode>=6)
        {
            ucBode=0;                           //Ĭ��2400
        }
    }
//  else                                        //645 ��Լ
//  {
//      if(ucBode>=6)
//      {
//          ucBode=3;                           //Ĭ��2400
//      }
//  }

    TMOD4 = 0x20;                               // 8-bit counter with auto-reload
    TCON4 =BaudRateTable[ucBode].Type;          //ʱ��ѡ��CLK  clear SMOD  SET  T1M,TR1
    TL41=TH41=BaudRateTable[ucBode].THValue;    //����������
//    if(uctype==0x00)                            //62056-21
    {
        SCON4 = 0x50;                           //����λ8λ,7λ����λ+1У��λ
    }
//    else
//    {
//        SCON4=0xD0;                             //����λ9λ,8λ����λ+1У��λ
//    }
    P2OD |= BIT1;
    P2OE &= ~BIT1;                      //Uart4���Ϳ��������
    P2IE &= ~BIT1;                      //Uart4���Ϳ������ֹ
    P2OE |= BIT0;                       //Uart4���տ������ֹ
    P2IE |= BIT0;                       //Uart4���տ���������
    P20FS=2;                            //P2.0���ó�RXD
    P21FS=2;                            //P2.1���ó�TXD

    EIE|=BIT0;
    ExInt2IE&=~BIT2;
    SCON4&=~(BIT0+BIT1);
    ExInt2IFG&=~(BIT2+BIT3);
    ExInt2IE|=BIT3;
#ifdef RS485_TWOLINE
    Uart4_CtrIoIdle();
#else
    Uart4_RevEn();
#endif
}
#endif
/*=========================================================================================\n
* @function_name: Uart4_Dy10ms
* @function_file: Uart4.c
* @����: ģ�⴮�ڵĳ�ʱ����
*       Ϊ��ֹ��������ʱ��������û���κ����ݷ��ͺͽ��յ�ʱ�򣬳�ʼ��
* @����:
* @����:
* @����:   lwb (2012-03-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
 
void Uart4_Dy10ms(void)
{
 
   if ( guc_DyUart4Over )
   {
      guc_DyUart4Over--;
    if(0x00== guc_DyUart4Over)
    {
        Init_Uart4(guc_485Bode);        // ��ʼ��ģ�⴮��
        ComBom_Init(ComIndex_Uart4);    //��uart4 �˿ڶ�Ӧ�� COM��ʼ��
    }
   }

    if(guc_BodeDely>0)                  //�������л�
    {
        guc_BodeDely--;
        if(guc_BodeDely==0)
        {
            gui_RefreshEvent |= flgEtPara_Bode;
        }
    }
 
}
 

void Uart4_Receiveio( unsigned char cData )
{
//    uint8 temp,temp1;
    guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�

    //���ڿ���״̬���Ѿ�����uart����״̬
    gs_ComGroup[ComIndex_Uart4].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart4].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��

    if((gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Idle) 
      ||(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Recv))            //����ж��Ƿ�ֹ���͵�ʱ���н����жϽ���Ŀ���
    {
        if(gs_ComGroup[ComIndex_Uart4].ucLen < Const_MaxBufLen)     //�ж� com�е�buf�Ƿ����
        {
            //��ֹ�������
            gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucLen++] = cData ;//���ݴ��뻺������ָ��Ӽ�
        }
    }
}
/*=========================================================================================\n
* @function_name: Uart4_Receive
* @function_file: Uart4.c
* @����: UART4����,���ж��е��øú���
*
* @����:
* @����:
* @����:   lwb (2012-03-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Uart4_Receive(void)
{
   
  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_R485_Chanel_]);
    uint8 temp,temp1;
    //guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�
   
if ( _IsUse645ComProtocol(FlashInfo.SetInfo.cCommProtocl)) 
{
     ACC=SBUF4;                          //ACC ��У��
    temp=P;
    temp1=(SCON4>>2)&BIT0;              //żУ��

    if(temp!=temp1)                     //��żУ��λ����ȷ
    {
        return;
    }
    stream_rece_fun_645( usartcomp,SBUF4);
    if (usartcomp->bEventRec645) {
				//do {
			//		unitp->INTE.reg = unitp->INTE.reg & 0xff80;//_DISABLE_USART0_RECE_INT_);
			//	} while (unitp->INTE.reg & 0x7f);
			} else {
			//	if (flag & 0x4) {
			//		// iReRece =0x66;
			//		flag &= 0xb;
			//		goto a1;
			//	}

			}
}else
{
    unsigned char ctemp = SBUF4;
     if ( SUCCESS == c7bitParity_Set(&ctemp ,_Parity_Even_))
     {
        Uart4_Receiveio(ctemp);      
        char    cFilter(char cin);
        cFilter(ctemp);
     }
      return ;
  stream_rece_fun ( usartcomp,SBUF4);
}

    return ;
#ifdef DEL
    //���ڿ���״̬���Ѿ�����uart����״̬
    gs_ComGroup[ComIndex_Uart4].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart4].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��

    if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Idle)        //��ǰ�ǿ��е�״̬�Ļ����ж��Ƿ���֡ͷ68
    {
        if(SBUF4==COMHEAD)               //���ܵ���ʼ�ֽ�
        {
            gs_ComGroup[ComIndex_Uart4].ucStt = ComStt_Recv;
        }
    }

    if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Recv)            //����ж��Ƿ�ֹ���͵�ʱ���н����жϽ���Ŀ���
    {
        if(gs_ComGroup[ComIndex_Uart4].ucLen < Const_MaxBufLen)     //�ж� com�е�buf�Ƿ����
        {
            //��ֹ�������
            gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucLen++] = SBUF4;//���ݴ��뻺������ָ��Ӽ�

            if(gs_ComGroup[ComIndex_Uart4].ucLen>COMINITLEN)
            {
                if(gs_ComGroup[ComIndex_Uart4].ucBuf[7]!=COMHEAD)           //�����7������68���ش���
                {
                    gs_ComGroup[ComIndex_Uart4].ucStt=ComStt_Idle;
                }else if(gs_ComGroup[ComIndex_Uart4].ucLen>=(gs_ComGroup[ComIndex_Uart4].ucBuf[9]+COMINITLEN+2))   //���ȷ���Ҫ��
                {
                    if(SBUF4==COMTAIL)
                    {
                        guc_ComSendDy=3;                                        //��ʱ30ms����
                        gs_ComGroup[ComIndex_Uart4].ucStt=ComStt_WaitProc;
                        gui_SystemEvent |= flgEtGlb_NeedPrtclChk;               // ���ñ�־
                        gs_ComGroup[ComIndex_Uart4].ucRecvTmr=0;
                        //�رս���
                    }
                }
            }
        }
    }
#endif
}
/*=========================================================================================\n
* @function_name: Uart4_Transmit
* @function_file: Uart4.c
* @����: UART4����,�ж��е���
*
* @����:
* @����:
* @����:   lwb (2012-03-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/


                   
                    
void Uart4_Transmit(void)
{
  unsigned char ctemp;
  
  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_R485_Chanel_]);
if ( _IsUse645ComProtocol(FlashInfo.SetInfo.cCommProtocl)) 
{
  if (usartcomp->cStatu < _end_sendcom) 
  {
	ctemp  = stream_send_fun_645(usartcomp);
        _BitYX(SCON4,ctemp) ;   
        SBUF4 = ctemp;
	resetWdt();
        if ((0 == --(usartcomp->cHead)) && ( _workNormal_ == WorkState_ReCheck(_cIolist )))
          usartcomp->cStatu++;
	} else {
			do {
				usartcomp->cSilence = 1;
		} while (1 != usartcomp->cSilence);
	}

	return;
}else
{ 
  

  // guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����

    if(gs_ComGroup[ComIndex_Uart4].ucPort   == Port_Uart4)
    {   //���ڿ���״̬���Ѿ�����uart����״̬
        if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart4].ucPos >= gs_ComGroup[ComIndex_Uart4].ucLen)
            {   //�������,��ʼ��ͨѶ����״̬
            #ifdef RS485_TWOLINE
                Uart4_CtrIoIdle();
            #else
                Uart4_RevEn();
            #endif
                ComBom_Init(ComIndex_Uart4);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
            }else
            {
//          //�����������żУ������
              SCON4|=(BIT3);
              SBUF4 =  c7bitParity_Get(gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos++],_Parity_Even_);                   
               
            #ifdef RS485_TWOLINE
                Uart4_CtrIoIdle();
            #else
                Uart4_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
            #endif

            }
        }else
        {   //����ڷ����жϱ���У����뵫��״̬����ȷ�����ʼ��
            ComBom_Init(ComIndex_Uart4);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
        #ifdef RS485_TWOLINE
            Uart4_CtrIoIdle();
        #else
            Uart4_RevEn();
        #endif
        }
    }
}
    
}

