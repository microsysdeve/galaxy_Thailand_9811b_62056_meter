#include "Include.h"
#include "streamio.h"
//��������
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
_UartInit(ucBode,TMOD2,TCON2,TL21,TH21,SCON2);
/*
    if(ucBode>=_bpsend_)
    {
        ucBode=_bps2400_;                           //Ĭ��2400
    }

    TMOD2 = 0x20;                               // 8-bit counter with auto-reload
    TCON2 =BaudRateTable[ucBode].Type;          //ʱ��ѡ��CLK  clear SMOD  SET  T1M,TR1
    TL21=TH21=BaudRateTable[ucBode].THValue;    //����������
    SCON2=0xD0;                                 //����λ9λ,8λ����λ+1У��λ
*/
    P2OE &= ~BIT5;                      //Uart4���Ϳ��������
    P2IE &= ~BIT5;                      //Uart4���Ϳ������ֹ
    P2OE |= BIT4;                       //Uart4���տ������ֹ
    P2IE |= BIT4;                       //Uart4���տ���������
    P24FS=2;                            //P2.0���ó�RXD
    P25FS=2;                            //P2.1���ó�TXD
    
    Txd2FS = 1;
    ExInt2IE|=BIT0;
    ExInt2IE|=BIT1;
    EIE|=BIT0;
  
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
}
void Uart2_Receiveio(void)
{

//    uint8 temp,temp1;
    guc_DyUart2Over = Const_DyUart2Over;//�˿ڳ�ʱ����

    //���ڿ���״̬���Ѿ�����uart����״̬
    gs_ComGroup[ComIndex_Uart2].ucPort   = Port_Uart2;

    gs_ComGroup[ComIndex_Uart2].ucRecvTmr = Const_DyRvPack;     //�������ݰ����ճ�ʱʱ��

    if((gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Idle)
       ||(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Recv))        //��ǰ�ǿ��е�״̬�Ļ����ж��Ƿ���֡ͷ68
    {
        if(gs_ComGroup[ComIndex_Uart2].ucLen < Const_MaxBufLen)     //�ж� com�е�buf�Ƿ����
        {                                                           //��ֹ�������
            gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucLen++] = (SBUF2&0x7F);//���ݴ��뻺������ָ��Ӽ�
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
extern volatile struct STSCIBUF USARTCOM[_Com_End_];
  struct STSCIBUF *usartcomp = (struct STSCIBUF *)&(USARTCOM[_IR_Chanel_]);
 
    uint8 temp,temp1;
    guc_DyUart2Over = Const_DyUart2Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�
    ACC=SBUF2;                          //ACC ��У��
    temp=P;
    temp1=(SCON2>>2)&BIT0;              //żУ��

    if(temp!=temp1)                     //��żУ��λ����ȷ
    {
        return;
    }
    #ifdef _ComUSE645_
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
    Uart2_Receiveio();
      return ;
  stream_rece_fun ( usartcomp,SBUF2);
#endif
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
    guc_DyUart2Over = Const_DyUart2Over;//�˿ڳ�ʱ����
#ifdef DEL
    if(gs_ComGroup[ComIndex_Uart2].ucPort   == Port_Uart2)
    {   //���ڿ���״̬���Ѿ�����uart����״̬
        if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart2].ucPos >= gs_ComGroup[ComIndex_Uart2].ucLen)
            {   //�������,��ʼ��ͨѶ����״̬
                //�����꣬���û�ȥ
//              P25FS=0;                            //P2.5���ó�GPIO,ֻ���ڷ��͵�ʱ���л���TXD
//              P2OE &= ~BIT5;                      //UART2���Ϳ��������
//              P2OD&=(~BIT5);
//              P2IE &= ~BIT5;                      //UART2���Ϳ������ֹ
//              ExInt2IE&=(~BIT0);                  //�رշ����ж�
                Uart2_RevEn();
                ComBom_Init(ComIndex_Uart2);//��uart2 �˿ڶ�Ӧ�� COM��ʼ��
            }else
            {
                if(gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt<4)
                {
                    SCON2|=(BIT3);
                    SBUF2=0xfe;
                    gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt++;
                }else
                {
                    //�����������żУ������
                    ACC = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos]; //����У��λ
                    if(P==0)                                        //У��λ
                    {
                        SCON2&=(~BIT3);
                    }
                    else
                    {
                        SCON2|=(BIT3);
                    }
                    Uart2_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
                    SBUF2 = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++];
                }

            }
        }else
        {   //����ڷ����жϱ���У����뵫��״̬����ȷ�����ʼ��
            ComBom_Init(ComIndex_Uart2);//��uart2 �˿ڶ�Ӧ�� COM��ʼ��
            Uart2_RevEn();
        }
    }
#endif
}

