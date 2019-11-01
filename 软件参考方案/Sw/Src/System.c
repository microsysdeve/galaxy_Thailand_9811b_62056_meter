#define SYSTEMEXT

#include "Include.h"
/*=========================================================================================\n
* @function_name: EXINT0
* @function_file: System.c
* @����: �ⲿ�ж�0
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x03               //�жϺ�0,�ⲿ�ж�0
__interrupt void EXINT0(void)
{

}

/*=========================================================================================\n
* @function_name: Timer0Interrupt
* @function_file: System.c
* @����: ��ʱ��0�ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x0b               //�жϺ�1,  Timer0
__interrupt void Timer0Interrupt(void)
{
    TH0 = 0xFE;             //��ʱ1ms
    TL0 = 0xEF;             //������һ�ν��жϵ�ʱ���趨
    PowDownChk();
}
/*=========================================================================================\n
* @function_name: EXINT1
* @function_file: System.c
* @����: �ⲿ�ж�1
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x13               //�жϺ�2,  �ⲿ�ж�1
__interrupt void EXINT1(void)
{

}

/*=========================================================================================\n
* @function_name: Timer1Interrupt
* @function_file: System.c
* @����: ��ʱ��1�ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x1b               //�жϺ�3,  Timer1
__interrupt void Timer1Interrupt(void)
{

}

/*=========================================================================================\n
* @function_name: Timer2Interrupt
* @function_file: System.c
* @����: ��ʱ��2�ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x2b               //�жϺ�5,  Timer2
__interrupt void Timer2Interrupt(void)
{
    TF2=0;
    TH2=0xF5;
    TL2=0x65; 
    KeyScan();
    ComBom_10msDy();
    Uart2_Dy10ms();
    Uart4_Dy10ms();
    guc_SecCnt++;
    if(guc_SecCnt>=100)
    {
        guc_SecCnt=0;
        guc_TimeEvent |= flgEtTim_Second;
    }

    guc_500msCnt++;
    if(guc_500msCnt>=50)
    {
        guc_500msCnt=0;
        gui_SystemEvent |= flgEtGlb_RefreshLcd;             //����LCDˢ��
    }

    
    guc_Dmd250msCnt++;
    if(guc_Dmd250msCnt>=25)
    {
        guc_Dmd250msCnt=0;
        Demand_250ms();
    }
}

/*=========================================================================================\n
* @function_name: UATR1Interrupt
* @function_file: System.c
* @����: UART1���ͽ����ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x3b               //�жϺ�7,  UATR1�����ͺͽ����ж�
__interrupt void UATR1Interrupt(void)
{

    if(SCON1&BIT0)
    {
        //Uart1RevInt();      //�����ж�
        SCON1&=~BIT0;
    }

    if(SCON1&BIT1)
    {
        //Uart1SendInt();       //�����ж�
        SCON1&=~BIT1;
    }

}
/*=========================================================================================\n
* @function_name: UATRAndCFInterrupt
* @function_file: System.c
* @����: UATR2��UATR4��CF�ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x43               //�жϺ�8,  UATR2��UATR4��CF�ж�
__interrupt void UATRAndCFInterrupt(void)
{
   if(EXIF&BIT4)
    {
        if(ExInt2IFG&BIT7)          //�����ж�
        {
            //�û�����
            if(guc_ResetFlg==true)
            {
                guc_ResetFlg=false;
                gui_SystemEvent|=flgEtGlb_FirstPulse;   //���õ�һ�������¼�
            }
            EnyB_IntCF();
            Demand_EnergyPulse();
            ExInt2IFG&=(~BIT7);
        }

        if(ExInt2IFG&BIT4)          //UART2��ͨ��ʱ���ж�
        {
            //�û�����
            ExInt2IFG&=(~BIT4);
        }

        if(ExInt2IFG&BIT5)          //UART4��ͨ��ʱ���ж�
        {
            //�û�����
            ExInt2IFG&=(~BIT5);
        }

        if(ExInt2IFG&BIT2)          //UART4 �����ж�
        {
            Uart4_Transmit();
            ExInt2IFG&=(~BIT2);
            SCON4&=(~BIT1);
        }

        if(ExInt2IFG&BIT3)          //UART4 �����ж�
        {
            Uart4_Receive();
            SCON4&=(~BIT0);
            ExInt2IFG&=(~BIT3);
        }

        if(ExInt2IFG&BIT0)          //UART2 �����ж�
        {
            Uart2_Transmit();
            SCON2&=(~BIT1);
            ExInt2IFG&=(~BIT0);
        }

        if(ExInt2IFG&BIT1)          //UART2 �����ж�
        {
            Uart2_Receive();
            SCON2&=(~BIT0);
            ExInt2IFG&=(~BIT1);
        }
        EXIF&=(~BIT4);
    }

}
/*=========================================================================================\n
* @function_name: UATRAndRTCInterrupt
* @function_file: System.c
* @����: UATR5��RTC��CF2�ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x4b               //�жϺ�9,  UATR5��RTC��CF2�ж�
__interrupt void UATRAndRTCInterrupt(void)
{

   if(EXIF&BIT5)
    {
        if(ExInt3IFG&BIT6)      //RTC
        {
            ExInt3IFG&=(~BIT6);
        }

        if(ExInt3IFG&BIT2)      //UART5����
        {
            //Uart5_Transmit();
            SCON5&=(~BIT1);
            ExInt3IFG&=(~BIT2);
        }

        if(ExInt3IFG&BIT3)      //UART5����
        {
            //Uart5_Receive();
            SCON5&=(~BIT0);
            ExInt3IFG&=(~BIT3);
        }


        if(ExInt3IFG&BIT4)       //UART3��ͨ��ʱ���ж�
        {

            ExInt3IFG&=(~BIT4);
        }

        if(ExInt3IFG&BIT5)       //UART5��ͨ��ʱ���ж�
        {
            ExInt3IE&=~BIT5;        //���ж�
            TCON5 &=~BIT0;          //ֹͣ��ʱ
            ExInt3IFG&=(~BIT5);
        }

        if(ExInt3IFG&BIT7)       //CF2�ж�
        {

            ExInt3IFG&=(~BIT7);
        }

        /*if(ExInt3IFG&BIT0)      //UART3����
        {
            SCON3&=(~BIT1);
            ExInt3IFG&=(~BIT0);
        }

        if(ExInt3IFG&BIT1)
        {
            SCON3&=(~BIT0);
            ExInt3IFG&=(~BIT1);
        }*/


        EXIF&=(~BIT5);
    }

}

/*=========================================================================================\n
* @function_name: PLLAndExINT3
* @function_file: System.c
* @����: �ⲿ�ж�3��PLLƵ�������ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x53               //�жϺ�10,  �ⲿ�ж�3��PLLƵ�������ж�

__interrupt void PLLAndExINT3(void)
{

   if(EXIF&BIT6)
    {
        if(ExInt4IFG&BIT1)
        {
            ExInt4IFG&=(~BIT1);
        }
        EXIF&=(~BIT6);
    }

}

/*=========================================================================================\n
* @function_name: PowerOffInterrupt
* @function_file: System.c
* @����: �ⲿ�ж�3��PLLƵ�������ж�
*
* @����:
*
* @����:
* @return: __interrupt void
* @����:   lwb (2012-02-27)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x63               //�жϺ�10,  �ⲿ�ж�3��PLLƵ�������ж�
__interrupt void PowerOffInterrupt(void)
{

}






