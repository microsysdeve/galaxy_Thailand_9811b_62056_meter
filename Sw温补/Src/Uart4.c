#include "Include.h"

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

    if(ucBode>=5)
    {
        ucBode=2;                           //Ĭ��2400
    }

    TMOD4 = 0x20;                               // 8-bit counter with auto-reload
    TCON4 =BaudRateTable[ucBode].Type;          //ʱ��ѡ��CLK  clear SMOD  SET  T1M,TR1
    TL41=TH41=BaudRateTable[ucBode].THValue;    //����������
    SCON4=0xD0;                                 //����λ9λ,8λ����λ+1У��λ

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
}

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
    guc_DyUart4Over--;
    if(0x00== guc_DyUart4Over)
    {
        Init_Uart4(guc_485Bode);        // ��ʼ��ģ�⴮��
        ComBom_Init(ComIndex_Uart4);    //��uart4 �˿ڶ�Ӧ�� COM��ʼ��
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
    uint8 temp,temp1;
    guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����
    //�����������żУ���ж�
    ACC=SBUF4;                          //ACC ��У��
    temp=P;
    temp1=(SCON4>>2)&BIT0;              //żУ��

    if(temp!=temp1)                     //��żУ��λ����ȷ
    {
        return;
    }

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
    guc_DyUart4Over = Const_DyUart4Over;//�˿ڳ�ʱ����

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
                #ifdef RS485_TWOLINE
                    Uart4_CtrIoIdle();
                #else
                    Uart4_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
                #endif
                if(gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt<4)
                {                    
                    SCON4|=(BIT3);
                    SBUF4=0xfe;
                    gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt++;
                }else
                {
                    //�����������żУ������
                    ACC = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos]; //����У��λ
                    if(P==0)                                        //У��λ
                    {
                        SCON4&=(~BIT3);
                    }
                    else
                    {
                        SCON4|=(BIT3);
                    }
                    SBUF4 = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos++]; 
                }

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

