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
    TH0 = 0xFB;             //定时1ms
    TL0 = 0xBC;             // 
    PowDownChk();

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
    TH2 = 0xD5;             //定时10ms
    TL2 = 0x56;             //启动第一次进中断的时间设定
    Uart4_Dy10ms();         //485
    Uart2_Dy10ms();         //红外
#ifdef FRCom
    Uart1_Dy10ms();         //载波
#endif
    KeyScan();              //按键

    ComBom_10msDy();

    if(gs_SysRunSt.PluseType==true)         //时段投切
    {
        if(guc_PluseCount!=0)
        {
            guc_PluseCount--;
            RATESWITCHIOLOW();
        }else
        {
            RATESWITCHIOHIGH();
        }
    }

    if(guc_ComSendDy!=0)
    {
        guc_ComSendDy--;
    }

    guc_SecCnt++;
    if(guc_SecCnt>=100)
    {
        guc_SecCnt=0;
        guc_TimeEvent |= flgEtTim_Second;
    }
    guc_wdtCnt++;
    if(guc_wdtCnt>=10)
    {
        guc_wdtCnt=0;
        guc_wdtFlg = 1;
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
    #ifdef FRCom
        Uart1_Receive();      //接收中断
    #endif    
    }

    if(SCON1&BIT1)
    {
        SCON1&=~BIT1;      
    #ifdef FRCom
        Uart1_Transmit();       //发送中断
    #endif    
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
            //用户代码
            ExInt2IFG&=(~BIT7);
            EnyB_IntCF();
        }
        
        if(ucTemp&BIT4)          //UART2普通定时器中断
        {
            //用户代码
            ExInt2IFG&=(~BIT4);
        }
        
        if(ucTemp&BIT5)          //UART4普通定时器中断
        {
            //用户代码
            ExInt2IFG&=(~BIT5);
        }
       
        if(ucTemp&BIT2)          //UART4 发送中断
        {
            ExInt2IFG&=(~BIT2);
            SCON4&=(~BIT1);
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
  
        if(ucTemp&BIT6)      //RTC
        {
//          guc_TimeEvent|= flgEtTim_Second;
            ExInt3IFG&=(~BIT6);
        }
       
        if(ucTemp&BIT2)      //UART5发送
        {
            SCON5&=(~BIT1);
            ExInt3IFG&=(~BIT2);
            //Uart5_Transmit();            
        }
        
        if(ucTemp&BIT3)      //UART5接收
        {
            SCON5&=(~BIT0);
            ExInt3IFG&=(~BIT3);
            //Uart5_Receive();            
        }
        
        
        if(ucTemp&BIT4)          //UART3普通定时器中断
        {
            ExInt3IFG&=(~BIT4);
        }
        
        if(ucTemp&BIT5)          //UART5普通定时器中断
        {
            ExInt3IE&=~BIT5;        //关中断
            TCON5 &=~BIT0;          //停止定时
            ExInt3IFG&=(~BIT5);
        }         
        
        if(ucTemp&BIT7)          //CF2中断
        {

            ExInt3IFG&=(~BIT7);
        }
                
        if(ucTemp&BIT0)          //UART3发送
        {
            SCON3&=(~BIT1);
            ExInt3IFG&=(~BIT0);
            //Uart3_Transmit();            
        }
        
        if(ucTemp&BIT1)
        {
            SCON3&=(~BIT0);            
            ExInt3IFG&=(~BIT1);
            //Uart3_Receive();            
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

    if(EXIF&BIT6)
    {
        if(ExInt4IFG&BIT1)
        {
            if(INFOA&BIT5)
            {
                //ESAMRec=DATAA;
                //EUart_Receive();
                INFOA&=(~BIT5);
            }

            if(INFOA&BIT6)
            {
                //EUart_Transmit();
                INFOA&=(~BIT6);
            }
            ExInt4IFG&=(~BIT1);
        }
        EXIF&=(~BIT6);
    }
  
}


#pragma register_bank=2
#pragma vector=0x5B               //中断号11

__interrupt void TimerA(void)
{
  
 
  
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
 
 



 
