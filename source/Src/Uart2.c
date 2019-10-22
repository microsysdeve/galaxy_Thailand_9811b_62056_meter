#include "Include.h"
#include "streamio.h"
#include "uartiobase.h"
//��������
#define Uart2_CtrIoIdle()  {} 
enum   ENUMZBCONTROL
{
    _zb_exist =0,  //0, ����38kHz �ز���1,�������ز��� 
    _zb_noexti,
};

uint8   guc_DyUart2Over;        //ģ�⴮�ڳ�ʱ����
/*=========================================================================================\n
* @function_name: Init_Uart2
* @function_file: Uart2.c
* @����: uart2�ĳ�ʼ��
*
* @����:
* @����:
* @����:   lwb (2012-03-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Init_Uart2(uint8 ucBode)
{    
  unsigned char j;
  unsigned long i;
  char  stemp[10];
  
_UartInit(ucBode,TMOD2,TCON2,TL21,TH21,SCON2); 
 
    P2OE &= ~BIT5;                      //Uart4���Ϳ��������
    P2IE &= ~BIT5;                      //Uart4���Ϳ������ֹ
    P2OE |= BIT4;                       //Uart4���տ������ֹ
    P2IE |= BIT4;                       //Uart4���տ���������
    P24FS=2;                            //P2.0���ó�RXD
    P25FS=2;                            //P2.1���ó�TXD
    
    Txd2FS = _zb_noexti;
    ExInt2IE|=BIT0;
    ExInt2IE|=BIT1;
    EIE|=BIT0;
    //====================
   /*
    SCON2&=(~BIT4);
     gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart4;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��
gs_ComGroup[ComIndex_Uart2].ucLen =0;
    gs_ComGroup[ComIndex_Uart2].ucStt  = ComStt_Idle;
      
 
                while (1)
                {
                  for ( j =0;j<128;j++)
                  {
                   SLPWDT();               //800kι��
                   SCON2 &=~BIT1;         
                  //_EvenMod(j,SCON4)  ;
                   //_SendOper(j,SBUF4);
                   SCON2|=(BIT3);
                   SBUF2 =   c7bitParity_Get(j,  _Parity_Even_);
       for ( i =0 ;i < 1000;i++)
       {
            if (SCON2 & BIT1)
            goto a2;
          asm("nop"); asm("nop"); asm("nop");
        }       
                  a2:
                }
                
                }
                  
a1:    
                SCON2|=(BIT4);
                SCON2&=~BIT0;
                j =0;
                EA=1;
                while (1)
                {
                     SLPWDT();
                     continue;
                        if (  SCON2 & BIT0)
                       {
                              stemp[j++] = SBUF2;
                              if ( j>=sizeof(stemp))
                                  j =0;
                             SCON2&=~BIT0;
                       }
                        
                }
   */
    
}

/*=========================================================================================\n
* @function_name: Uart2_Dy10ms
* @function_file: Uart2.c
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
void Uart2_Dy10ms(void)
{
  #ifndef _ComUSE645_
    guc_DyUart2Over--;
    if(0x00== guc_DyUart2Over)
    {
        Init_Uart2(guc_485Bode);                   // ��ʼ��ģ�⴮��
        ComBom_Init(ComIndex_Uart2);    //��uart6 �˿ڶ�Ӧ�� COM��ʼ��
    }

    if(guc_BodeDely>0)                  //�������л�
    {
        guc_BodeDely--;
        if(guc_BodeDely==0)
        {
            gui_RefreshEvent|=flgEtPara_Bode;
        }
    }
    #endif
}

void Uart2_Receiveio( unsigned char cData )
{
//    uint8 temp,temp1;
    guc_DyUart2Over = Const_DyUart2Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�

    //���ڿ���״̬���Ѿ�����uart����״̬
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��

    if((gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle) 
      ||(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv))            //����ж��Ƿ�ֹ���͵�ʱ���н����жϽ���Ŀ���
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //�ж� com�е�buf�Ƿ����
        {
            //��ֹ�������
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = cData ;//���ݴ��뻺������ָ��Ӽ�
        }
    }
}
/*=========================================================================================\n
* @function_name: Uart2_Receive
* @function_file: Uart2.c
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
void Uart2_Receive(void)
{

  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_IR_Chanel_]);
    uint8 temp,temp1;
    //guc_DyUart2Over = Const_DyUart2Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�
 
#ifdef _ComUSE645_
    ACC=SBUF2;                          //ACC ��У��
    temp=P;
    temp1=(SCON2>>2)&BIT0;              //żУ��

    if(temp!=temp1)                     //��żУ��λ����ȷ
    {
        return;
    }
    stream_rece_fun_645( usartcomp,SBUF2);
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
#else
     unsigned char ctemp = SBUF2;
     if ( SUCCESS == c7bitParity_Set(&ctemp ,_Parity_Even_))
        Uart2_Receiveio(ctemp);      
      return ;
  stream_rece_fun ( usartcomp,SBUF2);
#endif
  
    return ;
#ifdef DEL
    //���ڿ���״̬���Ѿ�����uart����״̬
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��


    if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle)        //��ǰ�ǿ��е�״̬�Ļ����ж��Ƿ���֡ͷ68
    {

        if(SBUF2==COMHEAD)               //���ܵ���ʼ�ֽ�
        {
            gs_ComGroup[ComIndex_Uart2].ucStt = ComStt_Recv;
        }
    }
 
    //���ڿ���״̬���Ѿ�����uart����״̬
    if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv)            //����ж��Ƿ�ֹ���͵�ʱ���н����жϽ���Ŀ���
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //�ж� com�е�buf�Ƿ����
        {                                                           //��ֹ�������
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = SBUF2;//���ݴ��뻺������ָ��Ӽ�

            if(gs_ComGroup[ComIndex_Uart2].ucLen>COMINITLEN)
            {
                if(gs_ComGroup[ComIndex_Uart2].ucBuf[7]!=COMHEAD)           //�����7������68���ش���
                {
                    gs_ComGroup[ComIndex_Uart2].ucStt=ComStt_Idle;
                }else if(gs_ComGroup[ComIndex_Uart2].ucLen>=(gs_ComGroup[ComIndex_Uart2].ucBuf[9]+COMINITLEN+2))   //���ȷ���Ҫ��
                {
                    if(SBUF2==COMTAIL)
                    {
                        guc_ComSendDy=3;                                        //��ʱ30ms����
                        gs_ComGroup[ComIndex_Uart2].ucStt=ComStt_WaitProc;
                        gui_SystemEvent |= flgEtGlb_NeedPrtclChk;               // ���ñ�־
                        gs_ComGroup[ComIndex_Uart2].ucRecvTmr=0;
                        //�رս���
                    }
                }
            }
        }
    }
#endif
}
/*=========================================================================================\n
* @function_name: Uart2_Transmit
* @function_file: Uart2.c
* @����: UART2����,�ж��е���
*
* @����:
* @����:
* @����:   lwb (2012-03-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
                
void Uart2_Transmit(void)
{
  unsigned char ctemp;
 
  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_IR_Chanel_]);
 #ifdef  _ComUSE645_
  if (usartcomp->cStatu < _end_sendcom) 
  {
	ctemp  = stream_send_fun_645(usartcomp);
        _BitYX(SCON2,ctemp) ;   
        SBUF2 = ctemp;
	resetWdt();
        if ((0 == --(usartcomp->cHead)) && ( _workNormal_ == WorkState_ReCheck(_cIolist )))
          usartcomp->cStatu++;
	} else {
			do {
				usartcomp->cSilence = 1;
		} while (1 != usartcomp->cSilence);
	}

	return;
#else
  
  

  // guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����

    if(gs_ComGroup[ComIndex_Uart2].ucPort   == Port_Uart2)
    {   //���ڿ���״̬���Ѿ�����uart����״̬
        if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart2].ucPos >= gs_ComGroup[ComIndex_Uart2].ucLen)
            {   //�������,��ʼ��ͨѶ����״̬
            #ifdef RS485_TWOLINE
                Uart2_CtrIoIdle();
            #else
                Uart2_RevEn();
            #endif
                ComBom_Init(ComIndex_Uart2);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
            }else
            {
//          //�����������żУ������
              SCON2|=(BIT3);
              SBUF2 =  c7bitParity_Get(gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++],_Parity_Even_);                   
               
            #ifdef RS485_TWOLINE
                Uart2_CtrIoIdle();
            #else
                Uart2_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
            #endif

            }
        }else
        {   //����ڷ����жϱ���У����뵫��״̬����ȷ�����ʼ��
            ComBom_Init(ComIndex_Uart2);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
        #ifdef RS485_TWOLINE
        //    Uart2_CtrIoIdle();
        #else
            Uart2_RevEn();
        #endif
        }
    }
#endif
    
}

