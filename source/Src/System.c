#define SYSTEMEXT

#include "Include.h"
/*=========================================================================================\n
* @function_name: EXINT0
* @function_file: System.c
* @描述: 外部中断0
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x03               //中断号0,外部中断0
__interrupt void EXINT0(void)
{
  
}

/*=========================================================================================\n
* @function_name: Timer0Interrupt
* @function_file: System.c
* @描述: 定时器0中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x0b               //中断号1,  Timer0
__interrupt void Timer0Interrupt(void)
{
//    if(guc_PllSta == PLL_800K)
//    {
//        TH0 = 0xEF;          //定时5ms
//        TL0 = 0xFF;          //启动第一次进中断的时间设定
//    }
//    else
//    {
//        TH0 = 0xBF;          //定时5ms
//        TL0 = 0xFF;          //启动第一次进中断的时间设定
//    }
//    Pwr_DownChk();
    //掉电检测
}
/*=========================================================================================\n
* @function_name: EXINT1
* @function_file: System.c
* @描述: 外部中断1
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x13               //中断号2,  外部中断1
__interrupt void EXINT1(void)
{
  
}

/*=========================================================================================\n
* @function_name: Timer1Interrupt
* @function_file: System.c
* @描述: 定时器1中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x1b               //中断号3,  Timer1
__interrupt void Timer1Interrupt(void)
{
    TF1 = 0;
    guc_PendSlpSta = 0;        // 结束挂起标志
    TR1 = 0;                // 关定时器1    
}
/*=========================================================================================\n
* @function_name: Timer2Interrupt
* @function_file: System.c
* @描述: 定时器2中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x2b               //中断号5,  Timer2
__interrupt void Timer2Interrupt(void)
{
  
    TF2 = 0;

    
    if(guc_PllSta == PLL_800K)
    {
        TH2 = 0xFD;             //定时10ms
        TL2 = 0x54;             //启动第一次进中断的时间设定
        Tamp_IntProc();
        
    }
    else
    {
        TH2 = 0xF5;             //定时10ms
        TL2 = 0x54;             //启动第一次进中断的时间设定
//        Uart2_Dy10ms();         //485 
        Uart4_Dy10ms();         //485        
        KeyScan();              //按键
    
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
* @描述: UART1发送接收中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x3b               //中断号7,  UATR1，发送和接收中断
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
* @描述: UATR2、UATR4、CF中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x43               //中断号8,  UATR2、UATR4、CF中断
__interrupt void UATRAndCFInterrupt(void)
{
    uint8 ucTemp;
    ucTemp  = ExInt2IFG;
    ucTemp &= ExInt2IE;
    if(ucTemp&BIT7)          //脉冲中断
    {        
        ExInt2IFG&=(~BIT7);
        //用户代码
        EnyB_IntCF();
        Demand_EnergyPulse();       
    }
    
    if(ucTemp&BIT4)          //UART2普通定时器中断
    {
        ExInt2IFG&=(~BIT4);
    }
    
    if(ucTemp&BIT5)          //UART4普通定时器中断
    {
        ExInt2IFG&=(~BIT5);
    }
   
    if(ucTemp&BIT2)          //UART4 发送中断
    {
        SCON4&=(~BIT1);
        ExInt2IFG&=(~BIT2); 
        Uart4_Transmit();               
    }
    
    if(ucTemp&BIT3)          //UART4 接收中断
    {
        SCON4&=(~BIT0);
        ExInt2IFG&=(~BIT3);
        Uart4_Receive();        
    }

    if(ucTemp&BIT0)          //UART2 发送中断
    {
        SCON2&=(~BIT1);
        ExInt2IFG&=(~BIT0);
        Uart2_Transmit();        
    }
    
    if(ucTemp&BIT1)          //UART2 接收中断
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
* @描述: UATR5、RTC、CF2中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x4b               //中断号9,  UATR5、RTC、CF2中断
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
       
    if(ucTemp&BIT2)      //UART5发送
    {
        SCON5&=(~BIT1);
        ExInt3IFG&=(~BIT2);
    }
    
    if(ucTemp&BIT3)      //UART5接收
    {
        SCON5&=(~BIT0);
        ExInt3IFG&=(~BIT3);
    }   
    
    if(ucTemp&BIT4)          //UART3普通定时器中断
    {
        ExInt3IFG&=(~BIT4);
    }
    
    if(ucTemp&BIT5)          //UART5普通定时器中断
    {
        ExInt3IFG&=(~BIT5);
        ExInt3IE&=~BIT5;        //关中断
        TCON5 &=~BIT0;          //停止定时       
    }         
    
    if(ucTemp&BIT7)          //CF2中断
    {
        ExInt3IFG&=(~BIT7);
    }
            
    if(ucTemp&BIT0)          //UART3发送
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
* @描述: 外部中断3、PLL频率锁定中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x53               //中断号10,  外部中断3、PLL频率锁定中断
__interrupt void PLLAndExINT3(void)
{
    EXIF&=(~BIT6);  
}


#pragma register_bank=2
#pragma vector=0x5B               //中断号11
__interrupt void TimerA(void)
{
    EXIF&=(~BIT7);    
}

/*=========================================================================================\n
* @function_name: PowerOffInterrupt
* @function_file: System.c
* @描述: 外部中断3、PLL频率锁定中断
* 
* @参数: 
* 
* @返回: 
* @return: __interrupt void 
* @作者:   lwb (2012-02-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#pragma register_bank=2
#pragma vector=0x63               //中断号10,  外部中断3、PLL频率锁定中断
__interrupt void PowerOffInterrupt(void)
{
  
}
 
 



 
