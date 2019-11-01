
#define __MAIN__
#define VAREXT

#include "Include.h"

__root const unsigned char __code codepsword[4]@0x400=
{0xff,0xff,0xff,0xff};

/*=========================================================================================\n
* @function_name: Init_Var
* @function_file: main.c
* @描述: 初始化参数
* 
* @作者: lwb (2014/3/14)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void Init_Var(void)
{
    guc_ResetFlg = true;
    guc_CfOpenFlg=false;
    gs_PtlCrt.uc_ComStep=0;
    gs_PtlCrt.uc_CompLevel=0;
    guc_SecCnt=0;
    guc_500msCnt=0;
    gul_E2ParaStt = 0x0FFFFFFF;         //复位后默认参数区大E2有效
    gui_SystemSleepState=0;
    MemSet((uint8*)&gs_PDirCnt,0,sizeof(gs_PDirCnt));
    gui_SystemState = 0;
    gui_RefreshEvent=0;
    guc_KeyEvent=0;
    guc_TimeEvent=0;
    gui_SystemEvent=0;
    guc_ShowStCom=0;
    gui_DyPgmOut=0;
    gs_DispStt.ucIndex=0;
    guc_MeterSysSta=0;
    guc_DeamandTimer=0;
}
/*=========================================================================================\n
* @function_name: RTCWakeUPFunc
* @function_file: main.c
* @描述: RTC唤醒
* 
* 
* @return: uint8 
* @作者: lwb (2014/3/24)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 RTCWakeUPFunc(void)
{
    CLRWDT();
    SetPLL(SETPLL_800K);

    if(gs_DispStt.ucTmr>0)
    {
        gs_DispStt.ucTmr--;
        if(gs_DispStt.ucTmr==0)
        {
            gs_DispStt.ucIndex=0;
            //关屏
            LCD_Off();
            Init_RTC(RTC_DAY);                      //初始化为DAY RTC唤醒
        }else
        {
            Init_RTC(RTC_SEC);                      //初始化为1S RTC唤醒
            ShowRefresh();
        }
    }
    else
    {
        gs_DispStt.ucIndex=0;
        Init_RTC(RTC_DAY);                      //初始化为DAY RTC唤醒
        //关屏
        LCD_Off();
    }

    Sleep();
    return false;
}
/*=========================================================================================\n
* @function_name: IOWakeUPFunc
* @function_file: main.c
* @描述: IO口唤醒
* 
* 
* @return: uint8 
* @作者: lwb (2014/3/24)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 IOWakeUPFunc(void)
{
    CLRWDT();                           //喂狗

    SetPLL(SETPLL_800K);
    if(KeyStUp())
    {
        InitLCD();                      //初始化LCD显示
        ShowKeyProc();
    }
    Init_RTC(RTC_SEC);                  //初始化为1S RTC唤醒
//  CoverScanSleep();                   //开盖检测
    Sleep();
    return false;
}
/*=========================================================================================\n
* @function_name: SysEventProc
* @function_file: main.c
* @描述: 系统事件处理流程
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void SysEventProc(void)
{
    if(gui_SystemEvent & flgEtGlb_PowDown)
    {
        PowerDnPro();                  //掉电处理
        gui_SystemEvent &=~ flgEtGlb_PowDown;
        gui_SystemSleepState=0x55aa;
        //while(1);                                       //睡眠不成功，等待开门狗复位
    }
    else if(gui_SystemEvent & flgEtGlb_EnergyCalc)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        Eny_EnergyProc();                               // 能量事件
        gui_SystemEvent &=~ flgEtGlb_EnergyCalc;
    }
    else if(gui_SystemEvent&flgEtGlb_DemadProc)
    {
        DemandProc();
        gui_SystemEvent &=~flgEtGlb_DemadProc;
    }
    else if(gui_SystemEvent & flgEtGlb_RefreshLcd)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        ShowRefresh();                                  // 显示刷新
        gui_SystemEvent &=~ flgEtGlb_RefreshLcd;
    }
    else if(gui_SystemEvent & flgEtGlb_NeedPrtclChk)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        ComApp_Proc();                                  // 通讯事件
        gui_SystemEvent &=~flgEtGlb_NeedPrtclChk;
    }
    else if(gui_SystemEvent&flgEtGlb_ClearMeter)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        Data_ClearMeter();
        gui_SystemEvent&=~flgEtGlb_ClearMeter;
    }
    else if(gui_SystemEvent&flgEtGlb_FirstPulse)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        EnyB_FstPluseProc();
        gui_SystemEvent&=~flgEtGlb_FirstPulse;
    }
    else
    {
        gui_SystemEvent = 0;                            //防止出错时,整个循环下面的处理永远被挂起
    }
}
/*=========================================================================================\n
* @function_name: TimeEventProc
* @function_file: main.c
* @描述: 系统时间事件处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void TimeEventProc(void)
{
    if(guc_TimeEvent & flgEtTim_Second)                 // 秒处理
    {
        TimerProc();                                    // 在停电和有电下均处理
        EnyB_Open_Cf();
        ShowSecondProc();
        EnyB_Check_PowRev();                           //功率方向判断
        Demand_1s();
        guc_TimeEvent &= ~flgEtTim_Second;              //
    }
    else if(guc_TimeEvent&flgEtTim_Minute)
    {
         Data_MinProc();
         guc_TimeEvent&=~flgEtTim_Minute;
    }                                                   //
    else if(guc_TimeEvent & flgEtTim_Hour)              // 小时事件
    {                                                   //
        Data_HourProc();
        guc_TimeEvent &= ~flgEtTim_Hour;                //
    }
    else                                                //
    {                                                   //
        guc_TimeEvent = 0;                              //
    }
}
/*=========================================================================================\n
* @function_name: RefreshPara
* @function_file: DataProtect.c
* @描述: 参数刷新
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void RefreshPara(void)
{
    if(gui_RefreshEvent & flgEtPara_EnyBottom)
    {
        Eny_RefVar();
        gui_RefreshEvent &= ~flgEtPara_EnyBottom;
    }
    else if(gui_RefreshEvent&flgEtPara_Fee)
    {
        getFee();
        gui_RefreshEvent&=~flgEtPara_Fee;
    }
    else if(gui_RefreshEvent&flgEtPara_Bode)
    {
        Init_Uart2(0, 0);        // 初始化模拟串口
        Init_Uart4(0, 0);        // 初始化模拟串口
        gui_RefreshEvent&=~flgEtPara_Bode;
    } 
    else if(gui_RefreshEvent & flgEtPara_Init) 
    {
        if(CheckCRCWord(guc_InitWd))
        {
            InitE2Data();
        }
        gui_RefreshEvent&=~flgEtPara_Init;
    }
    else
    {
        gui_RefreshEvent =0;
    }
}
/*=========================================================================================\n
* @function_name: ShowKeyProc
* @function_file: main.c
* @描述: 
* 
* @作者: lwb (2014/3/25)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void ShowKeyProc(void)
{
    gs_DispStt.ucIndex++;
    if(gs_DispStt.ucIndex>=9)
    {
        gs_DispStt.ucIndex=0;
    }
    gs_DispStt.ucTmr=15;
    ShowRefresh(); 
}

/*=========================================================================================\n
* @function_name: main
* @function_file: main.c
* @描述: 入口主函数
*
* @参数:
* @返回:
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-7-20)
* @修改内容:
===========================================================================================*/
void main(void)
{
MAINSTART:
    SPC_FNC = 0x01;
    FlashPw = 0x86;
    SPC_FNC = 0;
    XRAMPWD=0x33;   //解除保护
    //判断是否掉电
    if(!(Systate&BIT0))         // 判断是否电压低
    {

        gui_SystemState |= flgStSys_PowOff;
        //判断是发是IO口唤醒，IO唤醒后键显。
        if(Systate&BIT2)
        {
            if(!RTCWakeUPFunc())
            {
                goto MAINSTART;
            }
        }

        //IO口处理
        if(Systate&BIT3)        //IO唤醒
        {
            if(!IOWakeUPFunc())
            {
                goto MAINSTART;
            }
        }

        SetPLL(SETPLL_800K);
        Eny_PurCheckRAMEny();
        InitLCD();              //LCD初始化
        PowerDnPro();
    }

    CtrlMEAS &=~ BIT7;          //1:LDO33开启
    SetPLL(SETPLL_3_2M);
    
//等待电源稳定
    SetLDOVolt(SETLDO_24V); 
    CPUInit();              //系统初始化
//    Disp_Full();
    SleepTimeProc();
    Init_Var();             //初始化参数
    InitDemand();
    EnyB_SetMeterRule();    //计量初始化
    RecoverEnegyData();     //恢复电量数据
    getFee(); 
    EA=1;                   //开中断
    while (1)
    {
        CLRWDT();               //喂狗
        Check_Sfr();            //检测sfr
        if(0x00 != gui_SystemEvent)                     //
        {                                               //
            SysEventProc();                             // 系统事件
        }
        else if(0x00!= guc_TimeEvent)                   //
        {
            if(!(Systate&BIT0))                         //
            {
                continue;
            }
            TimeEventProc();                            // 时间处理流程
        }                                               //
        else if(0x00 != gui_RefreshEvent)               //
        {   
            if(!(Systate&BIT0))                         //
            {
                continue;
            }                                            //
            RefreshPara();                              // 参数刷新
        }                                               //
        else if(0x00 != guc_KeyEvent)                   //
        {     
            if(!(Systate&BIT0))                         //
            {
                continue;
            }                                          //
            KeyProc();                                  // 按键处理
        }

        if(gui_SystemSleepState==0x55aa)
        {
            goto MAINSTART;
        }
    }
    
    
}


