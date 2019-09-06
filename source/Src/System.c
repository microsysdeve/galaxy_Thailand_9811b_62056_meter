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
//    if(guc_PllSta == PLL_800K)
//    {
//        TH0 = 0xEF;          //��ʱ5ms
//        TL0 = 0xFF;          //������һ�ν��жϵ�ʱ���趨
//    }
//    else
//    {
//        TH0 = 0xBF;          //��ʱ5ms
//        TL0 = 0xFF;          //������һ�ν��жϵ�ʱ���趨
//    }
//    Pwr_DownChk();
    //������
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
    TF1 = 0;
    guc_PendSlpSta = 0;        // ���������־
    TR1 = 0;                // �ض�ʱ��1    
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
  
    TF2 = 0;

    
    if(guc_PllSta == PLL_800K)
    {
        TH2 = 0xFD;             //��ʱ10ms
        TL2 = 0x54;             //������һ�ν��жϵ�ʱ���趨
        Tamp_IntProc();
        
    }
    else
    {
        TH2 = 0xF5;             //��ʱ10ms
        TL2 = 0x54;             //������һ�ν��жϵ�ʱ���趨
//        Uart2_Dy10ms();         //485 
        Uart4_Dy10ms();         //485        
        KeyScan();              //����
    
        ComBom_10msDy();
    
        if(guc_ComSendDy!=0)
        {
            guc_ComSendDy--;
        }
        
        guc_Dmd250msCnt++;
        if(guc_Dmd250msCnt>=25)
        {
            guc_Dmd250msCnt=0;
            Demand_250ms();
        }
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
        SCON1&=~BIT0;
    }

    if(SCON1&BIT1)
    {   
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
    uint8 ucTemp;
    ucTemp  = ExInt2IFG;
    ucTemp &= ExInt2IE;
    if(ucTemp&BIT7)          //�����ж�
    {        
        ExInt2IFG&=(~BIT7);
        //�û�����
        EnyB_IntCF();
        Demand_EnergyPulse();       
    }
    
    if(ucTemp&BIT4)          //UART2��ͨ��ʱ���ж�
    {
        ExInt2IFG&=(~BIT4);
    }
    
    if(ucTemp&BIT5)          //UART4��ͨ��ʱ���ж�
    {
        ExInt2IFG&=(~BIT5);
    }
   
    if(ucTemp&BIT2)          //UART4 �����ж�
    {
        SCON4&=(~BIT1);
        ExInt2IFG&=(~BIT2); 
        Uart4_Transmit();               
    }
    
    if(ucTemp&BIT3)          //UART4 �����ж�
    {
        SCON4&=(~BIT0);
        ExInt2IFG&=(~BIT3);
        Uart4_Receive();        
    }

    if(ucTemp&BIT0)          //UART2 �����ж�
    {
        SCON2&=(~BIT1);
        ExInt2IFG&=(~BIT0);
        Uart2_Transmit();        
    }
    
    if(ucTemp&BIT1)          //UART2 �����ж�
    {
        SCON2&=(~BIT0);
        ExInt2IFG&=(~BIT1);
        Uart2_Receive();        
    }
    EXIF&=(~BIT4);
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
    uint8 ucTemp;
    ucTemp  = ExInt3IFG;
    ucTemp &= ExInt3IE;
    debug_ledshow();
    if(ucTemp&BIT6)      //RTC
    {
        guc_TimeEvent|= flgEtTim_Second;
        ExInt3IFG&=(~BIT6);
    }
       
    if(ucTemp&BIT2)      //UART5����
    {
        SCON5&=(~BIT1);
        ExInt3IFG&=(~BIT2);
    }
    
    if(ucTemp&BIT3)      //UART5����
    {
        SCON5&=(~BIT0);
        ExInt3IFG&=(~BIT3);
    }   
    
    if(ucTemp&BIT4)          //UART3��ͨ��ʱ���ж�
    {
        ExInt3IFG&=(~BIT4);
    }
    
    if(ucTemp&BIT5)          //UART5��ͨ��ʱ���ж�
    {
        ExInt3IFG&=(~BIT5);
        ExInt3IE&=~BIT5;        //���ж�
        TCON5 &=~BIT0;          //ֹͣ��ʱ       
    }         
    
    if(ucTemp&BIT7)          //CF2�ж�
    {
        ExInt3IFG&=(~BIT7);
    }
            
    if(ucTemp&BIT0)          //UART3����
    {
        SCON3&=(~BIT1);
        ExInt3IFG&=(~BIT0);
    }
    
    if(ucTemp&BIT1)
    {
        SCON3&=(~BIT0);            
        ExInt3IFG&=(~BIT1);
    }
    EXIF&=(~BIT5);
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
    EXIF&=(~BIT6);  
}


#pragma register_bank=2
#pragma vector=0x5B               //�жϺ�11
__interrupt void TimerA(void)
{
    EXIF&=(~BIT7);    
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
 
 



 
