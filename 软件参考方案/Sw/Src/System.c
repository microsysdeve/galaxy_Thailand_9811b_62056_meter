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
    TH0 = 0xFE;             //定时1ms
    TL0 = 0xEF;             //启动第一次进中断的时间设定
    PowDownChk();
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
        gui_SystemEvent |= flgEtGlb_RefreshLcd;             //设置LCD刷新
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
        //Uart1RevInt();      //接收中断
        SCON1&=~BIT0;
    }

    if(SCON1&BIT1)
    {
        //Uart1SendInt();       //发送中断
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
   if(EXIF&BIT4)
    {
        if(ExInt2IFG&BIT7)          //脉冲中断
        {
            //用户代码
            if(guc_ResetFlg==true)
            {
                guc_ResetFlg=false;
                gui_SystemEvent|=flgEtGlb_FirstPulse;   //设置第一个脉冲事件
            }
            EnyB_IntCF();
            Demand_EnergyPulse();
            ExInt2IFG&=(~BIT7);
        }

        if(ExInt2IFG&BIT4)          //UART2普通定时器中断
        {
            //用户代码
            ExInt2IFG&=(~BIT4);
        }

        if(ExInt2IFG&BIT5)          //UART4普通定时器中断
        {
            //用户代码
            ExInt2IFG&=(~BIT5);
        }

        if(ExInt2IFG&BIT2)          //UART4 发送中断
        {
            Uart4_Transmit();
            ExInt2IFG&=(~BIT2);
            SCON4&=(~BIT1);
        }

        if(ExInt2IFG&BIT3)          //UART4 接收中断
        {
            Uart4_Receive();
            SCON4&=(~BIT0);
            ExInt2IFG&=(~BIT3);
        }

        if(ExInt2IFG&BIT0)          //UART2 发送中断
        {
            Uart2_Transmit();
            SCON2&=(~BIT1);
            ExInt2IFG&=(~BIT0);
        }

        if(ExInt2IFG&BIT1)          //UART2 接收中断
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

   if(EXIF&BIT5)
    {
        if(ExInt3IFG&BIT6)      //RTC
        {
            ExInt3IFG&=(~BIT6);
        }

        if(ExInt3IFG&BIT2)      //UART5发送
        {
            //Uart5_Transmit();
            SCON5&=(~BIT1);
            ExInt3IFG&=(~BIT2);
        }

        if(ExInt3IFG&BIT3)      //UART5接收
        {
            //Uart5_Receive();
            SCON5&=(~BIT0);
            ExInt3IFG&=(~BIT3);
        }


        if(ExInt3IFG&BIT4)       //UART3普通定时器中断
        {

            ExInt3IFG&=(~BIT4);
        }

        if(ExInt3IFG&BIT5)       //UART5普通定时器中断
        {
            ExInt3IE&=~BIT5;        //关中断
            TCON5 &=~BIT0;          //停止定时
            ExInt3IFG&=(~BIT5);
        }

        if(ExInt3IFG&BIT7)       //CF2中断
        {

            ExInt3IFG&=(~BIT7);
        }

        /*if(ExInt3IFG&BIT0)      //UART3发送
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






