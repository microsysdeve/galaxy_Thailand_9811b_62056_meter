#define Uart4_EXT
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
void Init_Uart4(uint8 ucBode,uint8 uctype)
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
        if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
           ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
        {
            Init_Uart4(0, 0);        // ��ʼ��ģ�⴮��
        }
        else
        {
            Init_Uart4(3, 0);        // ��ʼ��ģ�⴮��
        }
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
            gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucLen++] = (SBUF4&0x7F);//���ݴ��뻺������ָ��Ӽ�
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

    if(gs_ComGroup[ComIndex_Uart4].ucPort == Port_Uart4)
    {   //���ڿ���״̬���Ѿ�����uart����״̬
        if(gs_ComGroup[ComIndex_Uart4].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart4].ucPos >= gs_ComGroup[ComIndex_Uart4].ucLen)
            {   //�������,��ʼ��ͨѶ����״̬

                ComBom_Init(ComIndex_Uart4);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
                if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
                   ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
                {
                    DelayXms(60);
                    Init_Uart4(0, 0);        // ��ʼ��ģ�⴮��
                }
                else
                {
                    DelayXms(8);
                    Init_Uart4(3, 0);        // ��ʼ��ģ�⴮��
                }
            #ifdef RS485_TWOLINE
                Uart4_CtrIoIdle();
            #else
                Uart4_RevEn();
            #endif
            }
            else
            {
                Uart4_SendEn();
//              if(guc_PrtlTpye==Prtl_645)
//              {
//                  if(gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt<4)
//                  {
//                      SCON4|=(BIT3);
//                      SBUF4=0xfe;
//                      gs_ComGroup[ComIndex_Uart4].ucFrmHeadCnt++;
//                  }else
//                  {
//                      //�����������żУ������
//                      ACC = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos]; //����У��λ
//                      if(P==0)                                        //У��λ
//                      {
//                          SCON4&=(~BIT3);
//                      }
//                      else
//                      {
//                          SCON4|=(BIT3);
//                      }
//                      SBUF4 = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos++];
//                  }
//              }
//              else
                {
                    //�����������żУ������
                    ACC = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos]; //����У��λ
                    SBUF4 = gs_ComGroup[ComIndex_Uart4].ucBuf[gs_ComGroup[ComIndex_Uart4].ucPos++]| ((uint8)P)<<7;; 
                }
                
                #ifdef RS485_TWOLINE
                    Uart4_CtrIoIdle();
                #else
                    Uart4_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
                #endif
            }
        }else
        {   //����ڷ����жϱ���У����뵫��״̬����ȷ�����ʼ��
            ComBom_Init(ComIndex_Uart4);//��uart4 �˿ڶ�Ӧ�� COM��ʼ��
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart4(0, 0);        // ��ʼ��ģ�⴮��
            }
            else
            {
                Init_Uart4(3, 0);        // ��ʼ��ģ�⴮��
            }
        #ifdef RS485_TWOLINE
            Uart4_CtrIoIdle();
        #else
            Uart4_RevEn();
        #endif
            
        }
    }
}
