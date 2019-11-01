#define UART2_EXT
#include "Include.h"
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
void Init_Uart2(uint8 ucBode,uint8 uctype)
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

    TMOD2 = 0x20;                               // 8-bit counter with auto-reload
    TCON2 =BaudRateTable[ucBode].Type;          //ʱ��ѡ��CLK  clear SMOD  SET  T1M,TR1
    TL21=TH21=BaudRateTable[ucBode].THValue;    //����������
        
//    if(uctype==0x00)                            //62056-21
    {
        SCON2 = 0x50;                           //����λ8λ,7λ����λ+1У��λ
    }
//    else
//    {
//        SCON2=0xD0;                             //����λ9λ,8λ����λ+1У��λ
//    }
    P2OD|= BIT5; 
    P2OE &= ~BIT5;                      //UART2���Ϳ��������
    P2IE &= ~BIT5;                      //UART2���Ϳ������ֹ
    P2OE |= BIT4;                       //UART2���տ������ֹ
    P2IE |= BIT4;                       //UART2���տ���������
    P24FS=2;                            //P2.4���ó�RXD
    P25FS=2;                            //P2.5���ó�GPIO,ֻ���ڷ��͵�ʱ���л���TXD

    EIE|=(BIT0);                        //ʹ��uart2�ж�
    //�����⣬���������
    Txd2FS=0x01;
    ExInt2IE&=~BIT0;                    //�رշ����ж�
    SCON2&=~(BIT0+BIT1);
    ExInt2IFG&=~(BIT0+BIT1);
    ExInt2IE|=BIT1;                    //���������ж�
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
        if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
           ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
        {
            Init_Uart2(0,0);        //��ʼ������
        }
        else
        {
            Init_Uart2(3, 0);        //��ʼ������
        }
        ComBom_Init(ComIndex_Uart2);    //��uart6 �˿ڶ�Ӧ�� COM��ʼ��
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

    if(gs_ComGroup[ComIndex_Uart2].ucPort   == Port_Uart2)
    {   //���ڿ���״̬���Ѿ�����uart����״̬
        if(gs_ComGroup[ComIndex_Uart2].ucStt == ComStt_Send)
        {
            if(gs_ComGroup[ComIndex_Uart2].ucPos >= gs_ComGroup[ComIndex_Uart2].ucLen)
            {   //�������,��ʼ��ͨѶ����״̬
                //�����꣬���û�ȥ
                ComBom_Init(ComIndex_Uart2);//��uart2 �˿ڶ�Ӧ�� COM��ʼ��
                if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
                   ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
                {
                    DelayXms(60);
                    Init_Uart2(0,0);        //��ʼ������
                }
                else
                {
                    DelayXms(8);
                    Init_Uart2(3, 0);        //��ʼ������
                }
            }else
            {
                Uart2_SendEn();//���ƶ˿�����Ϊ����ģʽ��������ͨѶʹ�ã�  //����δ����������д�����跢�ͻ���
//              if(guc_PrtlTpye==Prtl_645)
//              {
//                  if(gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt<4)
//                  {
//                      SCON2|=(BIT3);
//                      SBUF2=0xfe;
//                      gs_ComGroup[ComIndex_Uart2].ucFrmHeadCnt++;
//                  }
//                  else
//                  {
//                      //�����������żУ������
//                      ACC = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos]; //����У��λ
//                      if(P==0)                                        //У��λ
//                      {
//                          SCON2&=(~BIT3);
//                      }
//                      else
//                      {
//                          SCON2|=(BIT3);
//                      }
//
//                      SBUF2 = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++];
//                  }
//              }
//              else
                {
                    //�����������żУ������
                    ACC = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos]; //����У��λ
                    SBUF2 = gs_ComGroup[ComIndex_Uart2].ucBuf[gs_ComGroup[ComIndex_Uart2].ucPos++]| ((uint8)P)<<7;; 
                }
            }
        }else
        {   //����ڷ����жϱ���У����뵫��״̬����ȷ�����ʼ��
            ComBom_Init(ComIndex_Uart2);//��uart2 �˿ڶ�Ӧ�� COM��ʼ��
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart2(0,0);        //��ʼ������
            }
            else
            {
                Init_Uart2(3, 0);        //��ʼ������
            }
            Uart2_RevEn();
        }
    }
}
