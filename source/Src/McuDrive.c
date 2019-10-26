#define MCUDRIVEEXT
#define RTCCPTEXT
#include "Include.h"
#include "powerevent.h"
#define V98x1A1
#include "Timer0Capture.h"
/*=========================================================================================\n
* @function_name: IO_Init
* @function_file: main.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-7-26)
* @修改内容:  
===========================================================================================*/
void IO_Init(void)
{
    //PxOE 1禁止输出 0允许输出
    //PxIE 1允许输入 0禁止输入
  	/*  IO      管脚       作用     LED与I2C单独配置
		P0.0	/TDO       输出0    FX    反向LED
		P0.1    /TDI       输出0    DLZS  电流指示
		P0.2    /TMS       输出0    SDA    
		P0.3	/TCK       输出0    SCL
		P0.4	/NO USE
		P0.5	/NO USE
		P0.6	/NO USE
		P0.7	/NO USE
	*/
    P0OE = 0; 
    P0IE = 0;
    P0OD = 0;
	/*  IO      管脚       作用
		P1.0   /NO USE		 
		P1.1   /RXD1/T1/INT2                       
		P1.2   /TXD1/T2EX/INT3/MEACLK                   
		P1.3   /RXD5/INT0/CFx/SP/PLLDIV/WAKEUP	 
		P1.4   /TXD5/INT1/PLLDIV/WAKEUP1 	     
		P1.5   /NO USE			
		P1.6   /NO USE	
		P1.7   /NO USE	
	*/
    P1OE  = 0;	
    P1IE  = 0;
    P1OD  = 0;
    P11FS = 0;
    P12FS = 0;
    P13FS = 0;
    P14FS = 0;  
	/*  IO      管脚       作用
		P2.0	/T2/RXD4/OSC     TXD4  
		P2.1    /T0/TXD4/PLL     RXD4        
		P2.2    /NO USE       
		P2.3	/NO USE       
		P2.4	/RXD2       JD   LED earth       
		P2.5	/TXD2       BG	 背光          
		P2.6	/NO USE        
		P2.7	/NO USE          
	*/
    P2OE = 0xff;    //LED与UART单独配置
    P2IE = 0;
	/*  IO      管脚       作用
		P3.0	/COM0      输出0       
		P3.1    /COM1      输出0        
		P3.2    /COM2      输出0       
		P3.3	/COM3      输出0       
		P3.4	/NO USE          
		P3.5	/NO USE  
		P3.6	/NO USE               
		P3.7	/NO USE 
	*/	
    P3OE = (BIT0+BIT1+BIT2+BIT3);
    P3IE = 0;
	/*  IO      管脚       作用
		P4.0	/COM4/SEG0 输出0       
		P4.1    /COM5/SEG1 输出0        
		P4.2    /NO USE        
		P4.3	/NO USE        
		P4.4	/NO USE          
		P4.5	/NO USE  
		P4.6	/NO USE               
		P4.7	/NO USE 
	*/			
    P4OE = 0xff;
    P4IE = 0;
    //P4OD &= ~(BIT0+BIT1);
	/*  IO      管脚       作用
		P5.0	/SEG1      输出0
		P5.1    /SEG2      输出0
		P5.2    /SEG3      输出0
		P5.3	/SEG4      输出0
		P5.4	/SEG5      输出0
		P5.5	/SEG6      输出0
		P5.6	/SEG7      输出0
		P5.7	/SEG8      输出0
	*/
	P5OE = 0xff;   //允许输出
    P5IE = 0;   //禁止输入
	/*  IO      管脚       作用
		P6.0	/NO USE
		P6.1    /NO USE
		P6.2    /SEG9      输出0
		P6.3	/SEG10     输出0
		P6.4	/SEG11     输出0
		P6.5	/SEG12     输出0
		P6.6	/SEG13     输出0
		P6.7	/SEG14     输出0
	*/
	P6OE = 0xff;   //允许输出
    P6IE = 0;   //禁止输入
    //P6OD = 0;   //输出0
	/*  IO      管脚       作用
		P7.0	/NO USE
		P7.1    /NO USE
		P7.2    /NO USE
		P7.3	/NO USE
		P7.4	/NO USE
		P7.5	/NO USE
		P7.6	/SEG15     输出0
		P7.7	/SEG16     输出0
	*/  
	P7OE = 0xFf;   //允许输出
    P7IE = 0x00;   //禁止输入
    //P7OD = 0;   //输出0
	/*  IO      管脚       作用
		P8.0	/SEG17     
		P8.1    /SEG18     
		P8.2    /SEG19     
		P8.3	/NO USE
		P8.4	/NO USE     
		P8.5	/NO USE
		P8.6	/NO USE      
		P8.7	/NO USE
	*/
    P8OE = 0;   //允许输出
    P8IE = 0;   //禁止输入
    //P8OD=0;   //输出0
    /*  IO      管脚       作用
		P9.0	/SEG20     
		P9.1    /TA1/SDSP  
		P9.2    /TA2       
		P9.3	/PLLDIV    
		P9.4	/NO USE         
		P9.5	/CF2       
		P9.6	/CF1       CF1      
		P9.7	/NO USE
	*/	
    P9OE = 0xf3;   //允许输出
    P9IE = 0x09;   //禁止输入
    P9OD = 0;   //输出0
//    P9FS = BIT6;
     _multiOut_Nor();
    CloseFD();
}
/*=========================================================================================\n
* @function_name: Init_Timer0
* @function_file: main.c
* @描述: 初始化定时器0
* 
* @参数: 
* @返回: 
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-8-8)
* @修改内容:  
===========================================================================================*/
void Init_Timer0(void)
{
    //CKCON &= ~BIT3;         //1/12clk
    CKCON |= BIT3;          //1clk
    TMOD  &= 0xf0;
    TMOD  |= 0x01;          //定时器为模式1    
    TH0    = 0xEF;          //定时5ms
    TL0    = 0xFF;          //启动第一次进中断的时间设定
    TR0    = 1;             //开定时器0
    IE    |= BIT1;
}
/*=========================================================================================\n
* @function_name: Init_Timer1
* @function_file: main.c
* @描述: 定时器1定时为10ms
* 
* @参数: 
* @返回: 
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-8-9)
* @修改内容:  
===========================================================================================*/
void Init_Timer1(uint16 tm)
{
    uint16 tmp;
    TR1 = 0;                // 暂时不开定时器1 
    CKCON &= ~BIT4;         // 1/12clk
    TMOD &=~ BIT3;          // 定时器为方式1 16位计数器
    TMOD |= BIT4;           // 定时器为方式1 16位计数器
//#if (MEA_SLP_FMCU == 1)
//    tmp = 65535 - tm*68*4;//mcu 3.2M
//#else  
    tmp = 65535 - tm*68;//mcu 800k
//#endif
    TH1 = tmp>>8;           // 定时400ms
    TL1 = tmp;              // 启动第一次进中断的时间设定    
    IE |= BIT3;             // TIME1 interrupt       
}
/*=========================================================================================\n
* @function_name: Init_Timer2
* @function_file: main.c
* @描述: 定时器2定时为10ms
* 
* @参数: 
* @返回: 
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  xuqf (2013-1-15)
* @修改内容:  
===========================================================================================*/
void Init_Timer2(void)
{
    CKCON &= ~BIT5;         // 1/12clk
    T2CON &= ~BIT1;         // 做定时器用
    TH2    = 0xF5;          // 定时10ms
    TL2    = 0x54;          // 启动第一次进中断的时间设定
    TR2    = 1;             // 开启定时器2
    IE    |= BIT5;          // TIME2 interrupt
}
/*=========================================================================================\n
* @function_name: Delay1OSC
* @function_file: McuDrive.c
* @描述: 延时1OSC 在13Mpll 下
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Delay1OSC(void)
{
    for(uint8 i=0;i<20;i++)
    {
    
    }
} 
/*=========================================================================================\n
* @function_name: DelayOSC
* @function_file: McuDrive.c
* @描述: 在13M主频下延时num个OSC
* 
* 
* @参数: 
* @param:num  个数
* @返回: 
* @作者:   lwb (2012-03-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void DelayOSC(uint8 num)
{
    for(uint8 i=0;i<num;i++)
    {
        Delay1OSC();
    }
}
/*=========================================================================================\n
* @function_name: RTCWakeUpTm
* @function_file: McuDrive.c
* @描述: RTC唤醒时间
* 
* 
* @参数: 
* @param:Tm  1s-00，1min-01   1hour-02  62.5ms,1~62S-07
* @返回: 
* @作者:   lwb (2012-10-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void RTCWakeUpTm(uint8 Tm, uint8 Sec)
{

    RTCPEN=0x96;            
    RTCPWD=0x57;
    DelayOSC(5);
    INTRTC=Tm;
    if(Tm == RTC_SETSEC)
    {
        SECINT = (BIT6|Sec);
    }
    DelayOSC(5);
    RTCPEN=0x96;
    RTCPWD=0x56;
    DelayOSC(5);
}
/*=========================================================================================\n
* @function_name: EnableRTCInt
* @function_file: McuDrive.c
* @描述: 开启RTC中断
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-28)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnableRTCInt(void)
{
    EIE|=BIT1;              //秒中断
    ExInt3IE|=BIT6;
}
/*=========================================================================================\n
* @function_name: DisableRTCInt
* @function_file: McuDrive.c
* @描述: 关闭RTC中断
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-28)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void DisableRTCInt(void)
{
    ExInt3IE&=~BIT6;    //秒中断
}
/*=========================================================================================\n
* @function_name: RTCInitForSleep
* @function_file: Timeproc.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
/*void RTCInitForSleep(void)
{
    RTCPEN=0x96;        //1S唤醒
    RTCPWD=0x57;
    DelayOSC(5);
    INTRTC=0x00;
    DelayOSC(5);
    RTCPEN=0x96;
    RTCPWD=0x56;
    DelayOSC(5);
}*/
/*=========================================================================================\n
* @function_name: Mcu_Init
* @function_file: Init.c
* @描述: 初始化MCU的LCD ，TIMER0和 
* 
* @参数: 
* @返回: 
* @作者:   lim (2011-12-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Mcu_I1nit(void)
{
    PRCtrl0 = CONFIG_PRCTRL0;
    PRCtrl1 = CONFIG_PRCTRL1;  
    IO_Init();              //IO初始化                
    InitLCD();             //LCD初始化
//    OpenBeiGuang();
 //    Disp_Full();            //显示全屏
    Init_Uart();            //Uart初始化
    Init_Timer0();          //注明？ms
    Init_Timer2();          //初始化定时器2
   // Key_Init();              //按键初始化
    KeyPortIn();
    OpenPortIn();
    RTCWakeUpTm(RTC_DAY, 0);   //RTC初始化 1HOUR
    EnableRTCInt();         //开启RTC秒中断
}
/*=========================================================================================\n
* @function_name: SetPLL13M
* @function_file: McuDrive.c
* @描述: PLL切换到13M
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 SetPLL13M(uint8 MEA)
{
    uint8 i=0;
    CtrlCLK=0xEb;               //ADC 800K  dsp 3.2M MCU 13M;
    CtrlPLL=BIT6;               //13M
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //在一定时间内没有锁定
        }
    }
    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //在一定时间内没有锁定
        }
    }
    if(MEA == MEA_ON)
    {
        MEAFRQ=1;
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
                return false;       //在一定时间内没有锁定
            }
        }
    }
    CtrlCry0 = 0x00;                //调整启振波形
    CtrlCry1 = 0x03;
    CtrlCry2 = BIT5;
    CtrlBGP  = 0x04;//0x34;//0x32;//0x3A;//0x30;
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //减小LDO25输出-未确认，关闭电池反馈
     CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    CtrlM    = BIT0;
    guc_PllSta = PLL_13M;
      
    return true;
} 
/*=========================================================================================\n
* @function_name: SetPLL3DOT2M
* @function_file: McuDrive.c
* @描述: PLL切换到3.2M
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 SetPLL3DOT2M(uint8 MEA)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;

    CtrlCLK=0xEA;               //MCU3.2M MEA3.2M ADC809.6K
    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //在一定时间内没有锁定
        }
    }

    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //在一定时间内没有锁定
        }
    }
    
    if(MEA)
    {
        MEAFRQ=1;                 
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
                return false;       //在一定时间内没有锁定
            }
        }
    }
    CtrlCry0 = 0x00;        //调整启振波形
    CtrlCry1 = 0x03;        //开停振检测
    CtrlCry2 = BIT5;        //启振电路复位使能
    CtrlBGP  = 0x04;//0x34;//0x32;//0x3A;//0x30;        //默认+20ppm，改善高低温误差
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //减小LDO25输出-未确认，关闭电池反馈
    CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    guc_PllSta = PLL_3D2M;
    
     TimerA_Capture_App_Init();
    return true;
}

/*=========================================================================================\n
* @function_name: PowOffSetPLL
* @function_file: McuDrive.c
* @描述: 休眠唤醒时PLL切换
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 PowOffSetFmcu(uint8 SetFmcu)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;
if(SetFmcu == PLL_3D2M)
    CtrlCLK = (CtrlCLK & 0xFC)| 0x02;      //MCU 3.2M 
else
    CtrlCLK = (CtrlCLK & 0xFC);            //MCU 800K

    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //在一定时间内没有锁定
        }
    }

    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //在一定时间内没有锁定
        }
    }
if(SetFmcu == PLL_3D2M)    
    guc_PllSta = PLL_3D2M;
else
    guc_PllSta = PLL_3D2M;
    return true;
}
/*=========================================================================================\n
* @function_name: SetPLL800K
* @function_file: McuDrive.c
* @描述: 800k
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-09-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 SetPLL800K(uint8 MEA)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;
  
    CtrlCLK=0xC0;               //MCU 800K  MEA 800K  ADC 200K
    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
         debug_break( _debug_errno_SetPLL800K_FAIL1_) ;   return false;       //在一定时间内没有锁定
        }
    }
    
    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            debug_break( _debug_errno_SetPLL800K_FAIL2_) ;   return false;       //在一定时间内没有锁定
        }
    }
    
    if(MEA == MEA_ON)
    {
        MEAFRQ=1;                 
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
               debug_break( _debug_errno_SetPLL800K_FAIL3_) ;    return false;       //在一定时间内没有锁定
            }
        }
    }
    
    CtrlCry0 = 0x00;        //调整启振波形
    CtrlCry1 = 0x03;        //开停振检测
    CtrlCry2 = BIT5;        //启振电路复位使能
    CtrlBGP  = 0xC4;//0xF4;//0xF2;//0xFA;//0xF0;        //默认+20ppm，改善高低温误差，减小偏置电流降低功耗
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //减小LDO25输出-未确认，关闭电池反馈
    CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    guc_PllSta = PLL_800K;
    
    return true;
}
/*=========================================================================================\n
* @function_name: MChannelCal
* @function_file: McuDrive.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-30)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
 

void MChannelCal(void)
{
 
    if((gs_DateTime.ucSecond==0x05))
    {
        //GetBat();                                                   //获取电池电压
       
      
    }else  if((gs_DateTime.ucSecond==0x07)||(gs_DateTime.ucSecond==0x08))
    {
        if(CtrlADC5!=0x81)
        {
            CtrlADC5=0x81;
        }
    }
//    else if(gs_DateTime.ucSecond==0x15 && guc_FrsCalRTCDelay == 0)  //每分钟第10s
//    {
//        CalRTC();
//    }
}

 
/*=========================================================================================\n
* @function_name: GetBat
* @function_file: McuDrive.c
* @描述: 计算电池电压
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-30)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/

 
void GetBat(void)
{
    volatile Word32 tempvalue;
//    {
        CtrlADC5=0x97;                              //M2通道开启电池测量功能

        DelayXms(30);                               //延时30ms
        tempvalue.lword=EnyB_ReadMeterParaACK(DATAOM);

        if(tempvalue.byte[3]>0x80)                  //电池悬空的时候读取可能是负值
        {
            tempvalue.lword=(~tempvalue.lword)+1;
        }
        tempvalue.lword = tempvalue.lword >> 16;
        tempvalue.lword = ((tempvalue.lword*100+5069)/5959);
//        tempvalue.lword=(tempvalue.lword+BATOFFSET)/BATDIV;     //计算电池电压

        gul_CellVoltage=tempvalue.lword;

        if(tempvalue.lword<=BATLEVEL)                       //电池电压低于门限制,电池告警
        {
            gui_BatLowFlg = 0x5A5A;
//            gul_ShowState|=flgShowSt_Bat;
            gut_SysWarn.SysWarn.BatLow=true;
//            gs_MeterState.ui_MeterState1.RunCode1Word.MeterCell=true;
//            gs_MeterState.ui_MeterState1.RunCode1Word.RTCCell=true;
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt == false      //时钟电池低 状态标志未置
//               && gs_ReportWord.ui_ReportWord1.ReportWord1.RtcBatRpt == 1)           //时钟电池低 需要主动上报
//            {
//                gs_ReportState.ui_ReportState1.ReportWord1.RtcBatRpt = true;         //时钟电池低 状态置位
//            }
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt == false      //时钟电池低 状态标志未置
//               && gs_ReportWord.ui_ReportWord1.ReportWord1.CutBatRpt == 1)           //时钟电池低 需要主动上报
//            {
//                gs_ReportState.ui_ReportState1.ReportWord1.CutBatRpt = true;         //时钟电池低 状态置位
//            }
        }
        else
        {
            gui_BatLowFlg = 0;
//            gul_ShowState&=~flgShowSt_Bat;
            gut_SysWarn.SysWarn.BatLow=false;
//            gs_MeterState.ui_MeterState1.RunCode1Word.MeterCell=false;
//            gs_MeterState.ui_MeterState1.RunCode1Word.RTCCell=false;
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt == true)     //时钟电池低 判断状态标志
//            {
//                gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt = false;
//            }
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt == true)     //时钟电池低 判断状态标志
//            {
//                gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt = false;
//            }
        }

//        guc_CheckBatFlg=false;
        CtrlADC5=0x81;      //切换到温度测量
//    }
}
/*=========================================================================================\n
* @function_name: ChangeBodeProc
* @function_file: McuDrive.c
* @描述: 修改波特率处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-31)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Init_Uart(void)
{
 
#ifndef  _ComUSE645_    
    guc_485Bode=_bps300_;
    
    Init_Uart2(guc_485Bode);
    ComBom_Init(ComIndex_Uart2);    //将uart2 端口对应的 COM初始化
    Init_Uart4(_bps300_);//guc_485Bode);
    ComBom_Init(ComIndex_Uart4);    //将uart4 端口对应的 COM初始化
#endif
}
/*=========================================================================================\n
* @function_name: IOOFF
* @function_file: McuDrive.c
* @描述: 掉电处理IO口
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void IOOFF(void)
{
    CloseBeiGuang();  //关闭背光
    P1OE |= BIT4; 
    P1IE &=~ BIT4;
    LCD_Off();
    
    //IR 485
    P20FS=0;
    P21FS=0;
    P24FS=0;
    P25FS=0;
    P2OE|=(BIT0+BIT1+BIT4+BIT5);   //禁止输出
    P2IE&=~(BIT0+BIT1+BIT4+BIT5);
    
    KeyPrDisable();//编程键
    
    P0OE |= BIT1;    //背光  高阻   
    P0IE &= ~BIT1;        
    P0OD &= ~BIT1;
    
    P0OE |= BIT2;    //TMS 高阻
    P0IE &= ~BIT2;   
    P0OE |= BIT3;    //TCK  高阻
    P0IE &= ~BIT3;  
    
    P9OE |= BIT0;    //pwrdet  高阻
    P9IE &= ~BIT0;   
    P1OE |= BIT4;    //DDjc  高阻
    P1IE &= ~BIT4;     
    
#if (MEA_SLP_CF == 0)    
    P1OE|= BIT3;        //CF IO高阻
    P1IE &= ~BIT3;
    P13FS = 0x0;
#else
    P1OE &= ~BIT3;
    P1IE &= ~BIT3;
    P13FS = 0x04;
#endif
    
#if(CONFIG_PT == 1)
    DetEnable();  
#endif
}
/*=========================================================================================\n
* @function_name: PowUpLedCtl
* @function_file: McuDrive.c
* @描述: 上电背光，LED控制
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void PowUpLedCtl(void)
{
    if(gs_DispCont.ucPowUpBgTm!=0)
    {
//        OpenBeiGuang();         //上电开背光，背光时间由显示初始化设置
    }
}
/*=========================================================================================\n
* @function_name: IntOFF
* @function_file: McuDrive.c
* @描述: 关闭中断
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void IntOFF(void)
{
  debug_break(_debug_fun_IntOFF_);
    IE=0;
    EIE=0;
    EXIF=0;
}
/*=========================================================================================\n
* @function_name: UARTOFF
* @function_file: McuDrive.c
* @描述: 关闭UART
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void UARTOFF(void)
{
    TCON2=0;
    TCON3=0;
    TCON4=0;
    CFGA=0;
}
/*=========================================================================================\n
* @function_name: MCUForPowerOff
* @function_file: McuDrive.c
* @描述: 掉电处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void MCUForPowerOff(void)
{
    uint8 i;
    CtrlADC6 = 0;                         //关AD通道
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);   //关CF
    EnyB_SetMeterCfgACK(0x00,PMCtrl1);   //停止计算，屏蔽信号

    for(i=0;i<20;i++);

    PMG=1;                              //关闭计量时钟
}

/*=========================================================================================\n
* @function_name: SwichPluseOutType
* @function_file: McuDrive.c
* @描述: 切换端子功能
* 
* 
* @参数: 
* @param:type  0-RTC  2-时段投切
* @返回: 
* @作者:   lwb (2012-06-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
/*
void SwichPluseOutType(uint8 type)
{
    if(type==0)
    {
        P9FS|=BIT3;                                                     //输出RTC
        P9OE&=(~BIT3);
    }
    if(type==2)
    {
        P9FS&=(~BIT3);
        P9OE&=(~BIT3);
    }
}
*/

/*=========================================================================================\n
* @function_name: SleepRTC
* @function_file: McuDriver.c
* @描述: 关LDO33;
*        关AD;
*        禁止计量电路访问双口ram;
*        关闭所有计量通道;
*        关PM时钟;
*        将系统切到低频工作;
*        关PLL;
*        让系统慢速进入浅睡眠。 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lim (2011-12-11)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 SleepRTC(void)
{
    uint8 i;

   // gs_KeyCtr[UpKey].Status=KeyRls;             //按键设置为释放
      GPIO_Init_OffLine1();
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();                     //I2C输出高
//    FWC=0;
//    FSC=0;
//    if((Systate&BIT0)==0x01)
//    {   
//        return false;
//    }
//    CtrlADC6=0;                 //关闭所有的ADC
//
//    for(i=0;i<20;i++);          //等待

//    PMG=1; //关闭计量时钟
    if (_IsUpIo()) //  if((Systate&BIT0)==0x01)
    {   
        return false;
    }

    MCUFRQ=0;
    while(MCUFRQ);
    
//    MEAFRQ=0; 
//    while(MEAFRQ);

    if (  _IsUpIo()) //  if((Systate&BIT0)==BIT0)
    {   
        return false; 
    }

    for(i=0;i<3;i++);           //等待

    CtrlCLK=0x00;
    while(CtrlCLK); 
     
    SLEEP0=1;

    return false;               //睡眠不成功返回错误
}

/*=========================================================================================\n
* @function_name: Sleep
* @function_file: McuDrive.c
* @描述: 关LDO33;
*        关AD;
*       禁止计量电路访问双口ram;
*       关闭所有计量通道;
*       关PM时钟;
*       将系统切到低频工作;
*       关PLL;
*       让系统慢速进入浅睡眠;* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-06-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 Sleep(void)
{
    uint8 i;
    FWC=0;
    FSC=0;

    // RTCWakeUpTm(RTC_SEC);
    //gui_SystemState |= flgStSys_PowOff;    //置掉电状态

    if((Systate&BIT0)==0x01)    //有电
    {   
        return false;
    }

    //CtrlADC6=0;             //关闭所有的ADC
    //LCDCtrl=0;
    //LCDG=1;
    //CtrlLDO|=BIT5;
    

//    for(i=0;i<20;i++);      //等待
//
//    PMG=1;                  //关闭计量时钟

    if((Systate&BIT0)==0x01)
    {   
        return false;
    }

    MCUFRQ=0;
    while(MCUFRQ);

//    MEAFRQ=0;
//    while(MEAFRQ);

    if((Systate&BIT0)==0x01)
    {   
        return false; 
    }

    for(i=0;i<3;i++);       //等待

    CtrlCLK=0x00;
    while(CtrlCLK);

    SLEEP0 = 1;
    DelayOSC(5);
    return false;           //睡眠不成功，返回FLASE
}
/*=========================================================================================\n
* @function_name: BgCtrFun
* @function_file: McuDrive.c
* @描述: 背光控制
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void BgCtrFun(void)
{
    if(guc_WorkMd != NormalMode)
    {
//        CloseBeiGuang();//关闭背光
    }
    else
    {
//        OpenBeiGuang();       
    }
}
#ifdef _SW_EXT_RTC
/*=========================================================================================\n
* @function_name: GetExtRTC
* @function_file: McuDrive.c
* @描述: 读取硬件时钟
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-02-29)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void GetExtRTC(void)
{
    volatile uint8 RTCFLAG ;
    RTCFLAG = RDRTC;
    DelayOSC(5);
    gs_ClkTmp.ucSecond  = RTCSC;
    gs_ClkTmp.ucMinute  = RTCMiC;
    gs_ClkTmp.ucHour    = RTCHC;
    gs_ClkTmp.ucWeek    = RTCWC;
    gs_ClkTmp.ucDay     = RTCDC;
    gs_ClkTmp.ucMonth   = RTCMoC;
    gs_ClkTmp.ucYear    = RTCYC;
}
 
void SetExtRTC(void)
{
    //RTC允许写 
    RTCPEN = 0x96;      //password 1
    RTCPWD = 0x57;      //password 2
    DelayOSC(5);
    //写RTC时间
    RTCYC   = gs_DateTime.ucYear;
    RTCMoC  = gs_DateTime.ucMonth;
    RTCDC   = gs_DateTime.ucDay;
    RTCHC   = gs_DateTime.ucHour;
    RTCMiC  = gs_DateTime.ucMinute;
    RTCSC   = gs_DateTime.ucSecond;
    RTCWC   = gs_DateTime.ucWeek;
    DelayOSC(5);
    //RTC禁止写  
    RTCPEN = 0x96;
    RTCPWD = 0x56;
    DelayOSC(5);
}
#endif

/*=========================================================================================\n
* @function_name: Check_Sfr
* @function_file: McuDrive.c
* @描述: 保护特殊功能寄存器
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-07-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Mcu_ChkSfr(void)
{
//    if(!OSCSTATE())
//    {
//    }
    
    if(EIE!=0xE3)
    {
        EIE=0xE3;
    }
    if(IE!=0xA2)
    {
        IE=0xA2;
    }

    if(guc_CfOpenFlg==false)
    {
       if((ExInt2IE&0x8C)!=0x8C)
       {
           ExInt2IE|=0x8C;
       }
    }else
    {
        if((ExInt2IE&0x0C)!=0x0C)
        {
           ExInt2IE|=0x0C;
        }
    }

//  if(ExInt3IE!=0x40)
//  {
//      ExInt3IE=0x40;
//  }
    if( P20FS!=0x02
        ||P21FS!=0x02)
//        ||P24FS!=0x02
//        ||P25FS!=0x02)
    {
        P20FS=0x02;
        P21FS=0x02;
//        P24FS=0x02;
//        P25FS=0x02;
    }   
}
/*=========================================================================================\n
* @function_name: Mcu_RTCNormal
* @function_file: McuDrive.c
* @描述: 不使用RTC功能表默认配置
*
*
* @参数:
* @返回:
* @作者:   lm (2014-07-09)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Mcu_RTCNormal(uint8 Pll)
{
    uint32 ul_div;

    //FCpyTMem((uint8 *)&gs_DateTime, (uint8 code*)&InitTM, 7);      
    RTCPEN = 0x96;
    RTCPWD = 0x57;
    DelayOSC(2);
    RTCCH  = 0;
    RTCCL  = 0;
  //  ul_div = Pll * 4096UL *100 - 1;
   // DIVTHH = ul_div>>16;
   // DIVTHM = ul_div>>8;
  //  DIVTHL = ul_div;
    
    RTC_Format (FlashInfo.lRtcJZPara);
    DelayOSC(2);
    RTCPEN = 0x96;
    RTCPWD = 0x56;
#if (CONFIG_RTC==0)
    FCpyTMem((uint8 *)&gs_DateTime, (uint8 code*)&InitTM, 7);
    SetExtRTC();   
#endif
}
/*=========================================================================================\n
* @function_name: Mcu_PendTm
* @function_file: McuDrive.c
* @描述: Mcu挂起
*
*
* @参数:
* @返回:
* @作者:   lm (2014-04-22)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 Mcu_PendTm(uint8 Xms)
{	
    uint8 tmp;
	Debug_Break(	_debugh_fun_Mcu_PendTm_);
    tmp = EA;
//	if((CtrlCLK&0x03) == 0x02)
    if(guc_PllSta != PLL_800K)
    {       
        DelayXms(Xms);
        return 1;
    }
    else
    {
        Init_Timer1(Xms);          //配置定时器1
        EA = 1;
        TR1 = 1;
        guc_PendSlpSta = 0x01;
        while(guc_PendSlpSta)    
            PCON = 1;              //MCU挂起等待xms
        EA = tmp;
        return 0;
    }
}