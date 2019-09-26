#define __MAIN__
#define VAREXT

#include "Include.h"
#include "PubSet.h"
__root const unsigned char __code codepsword[512]@0x400=
{ 
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

/*=========================================================================================\n
* @function_name: Init_Var
* @function_file: main.c
* @描述: 初始化系统全局变量和参数
*
* @参数:
* @返回:
* @作者:
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-8-9)
* @修改内容:
===========================================================================================*/
void Var_Init(void)
{
    gui_SystemState   = 0;  
    gui_SystemEvent   = 0;      //系统事件
    guc_TimeEvent     = 0;      //时间事件
    gui_RefreshEvent  = 0;      //刷新事件
    guc_KeyEvent      = 0;      //按键事件
    gui_SysSleepSta   = 0;      //非正常休眠标志
    
    guc_BodeDely      = 0;
//    guc_CfOpenFlg     = true;
//    guc_CfOpenCnt     = 0;      //开CF计数

    guc_ShowStCom     = 0;      //通信显示计数
    
//    guc_ErrSwPt=0;
//    guc_ErrCodeCnt=0;
    gs_SysRunSt.Pdir=0;
    gut_SysWarn.byte=0;
    
    guc_ComSendDy     = 0;      //645发送延时

    gs_Channel.ucSta = SETA;         //计量通道选择
    guc_SleepCnt = 0;           //休眠计数
   
    guc_FactoryType = 0;        //厂内状态标志
    gs_PtlCrt.uc_ComStep=0;
    gs_PtlCrt.uc_CompLevel=0;
    
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
        Pwr_DownProc();                  //掉电处理
        gui_SystemEvent &=~ flgEtGlb_PowDown;           
        gui_SysSleepSta = 0x55aa;
        //while(1);                                       //睡眠不成功，等待开门狗复位
    }                                                   
    else if(gui_SystemEvent & flgEtGlb_EnergyCalc)      
    {                                                   
        Eny_EnergyProc();                               // 能量事件
        gui_SystemEvent &=~ flgEtGlb_EnergyCalc;        
    }
    else if(gui_SystemEvent & flgEtGlb_DemadProc)
    {
        Demand_Proc();
        gui_SystemEvent &=~flgEtGlb_DemadProc;
    }
    else if(gui_SystemEvent & flgEtGlb_RefreshLcd)      
    {                                                   
        ShowRefresh();                                  // 显示刷新
        gui_SystemEvent &=~ flgEtGlb_RefreshLcd;        
    }                                                   
    else if(gui_SystemEvent & flgEtGlb_NeedPrtclChk)    
    {                                                   
        ComApp_Proc();                                  // 通讯事件
        gui_SystemEvent &=~flgEtGlb_NeedPrtclChk;       
    }
//    else if( gui_SystemEvent&flgEtGlb_ClearEv)         //清零事件事件
//    {
//        Data_ClearEvent();
//        gui_SystemEvent&=~flgEtGlb_ClearEv;
//    }
    else if(gui_SystemEvent&flgEtGlb_AutoCal)
    {
        //EnyB_AutoChkSP();
        gui_SystemEvent&=~flgEtGlb_AutoCal; 
    }
    else if(gui_SystemEvent&flgEtGlb_ClearMeter)
    {
        Data_ClearMeter();
        gui_SystemEvent&=~flgEtGlb_ClearMeter;
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
        Data_SecProc();
        guc_TimeEvent |= flgEtTim_SecSoft;
        guc_TimeEvent &= ~flgEtTim_Second;              
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
    }else if(guc_TimeEvent & flgEtTim_Day)
    {
        Data_DayProc();
        guc_TimeEvent &=~flgEtTim_Day;
    }
    else if(guc_TimeEvent & flgEtTim_Year)
    {
        Data_YearProc();
        guc_TimeEvent &=~flgEtTim_Year;
    }
    else if(guc_TimeEvent & flgEtTim_SecSoft)
    {
        if(guc_CfOpenFlg == false)
        {
            BgCtrFun();
        }
        MChannelCal();                                  // 测试M
//        KeyScan();
        guc_TimeEvent &= ~flgEtTim_SecSoft;
    }
    else                                                //
    {                                                   //
        guc_TimeEvent = 0;                              //  
    }
}
/*=========================================================================================\n
* @function_name: Init_CfG
* @function_file: main.c
* @描述: 初始化配置
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-11-05)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Init_CfG(void)
{
    if(gs_FunCfg.ul_CRC != do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2))
    {
        MemSet(&gs_FunCfg.uc_CbrCfg,0,sizeof(GSFUNCFG)-3);//清零配置项
        gs_FunCfg.uc_CfSaveCfg = 0x50;
        gs_FunCfg.uc_ENSHOWCfg = 0x02;
        gs_FunCfg.ul_CRC=do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2);       //计算配置项的crc
    }
}
/*=========================================================================================\n
* @function_name: App_Init
* @function_file: main.c
* @描述: 初始化配置
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-11-05)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void App_Init(void)
{
    Demand_Init();          //初始化需量参数
    DataSecurityInit();
    //ShowSysStart();         //显示上电初始化
    Mcu_RTCNormal(guc_PllSta);         //RTC默认初始化
    Tamp_Init();
    EnyB_Init();
}
/*=========================================================================================\n
* @function_name: Mea_Consumption_Dly
* @function_file: main.c
* @描述:
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-11-05)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
bool Mea_Consumption_Dly(void)
{
    OpenFD();
    for(uint8 i=0; i<5; i++)
    {
      SLPWDT();               //800k喂狗
      DelayOSC(20);
    }
    if(!(Systate&BIT0))      // 判断是否电压低
    {
      RTCWakeUpTm(RTC_SETSEC, 6);
      
      SLEEP0=1;
      return false;               //睡眠不成功返回错误
    }else
    {
      CloseFD();
      return true;
    }
}
/*=========================================================================================\n
* @function_name                    : main
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

__near_func void m1ain(void)
{
  
  debug_init();
  
MAINSTART:
    if(!(Systate&BIT0))      // 判断是否VDCIN低
    {  
        if(SetPLL800K(MEA_OFF) == 0)   //MCU切800K
        {
            goto MAINSTART;
        }
        SLPWDT();                      //喂狗   
        if(false == Pwr_ChkProc())     //系统上电判断
        {
            goto MAINSTART;
        }
    }
    SLPWDT();
    if(false == Mea_Consumption_Dly()) //放电延时判断供电是否稳定
    {
        goto MAINSTART;
    }
    if(SetPLL800K(MEA_OFF) == 0)   //VDCIN高时，MCU切800K
    {
      goto MAINSTART;
    }
    SLPWDT();               //800k喂狗
    Mcu_Init();             //系统底层初始化
    SLPWDT();               //800k喂狗
    App_Init();             //系统应用层初始化
    SLPWDT();               //800k喂狗
    // Mea_Init();             //计量初始化           
    SLPWDT();               //800k喂狗   
    Var_Init();             //系统参数初始化-应该能放到appinit中
    SLPWDT();               //800k喂狗
    Data_RecPara();         //系统数据恢复
    SLPWDT();               //800k喂狗
    GetBat();               //得到电池电压
    SLPWDT();               //800k喂狗
    EA = 1;                 //开总中断
    //InitE2Data();
    while (1)
    {
        CLRWDT();               //喂狗
        Mcu_ChkSfr();           //检测sfr
#if (CONFIG_PT == 0)
        if(!POWERUP())
#else
        if(!POWERUP() && PwrDetLow())
#endif       
        {
            gui_SystemEvent |= flgEtGlb_PowDown;
        }
        if(0x00 != gui_SystemEvent)                     //
        {                                               //
            SysEventProc();                             // 系统事件
        }   
        else if(0x00 != guc_TimeEvent)                  //
        {                                               //
            TimeEventProc();                            // 时间处理流程
        }                                               //
        else if(0x00 != gui_RefreshEvent)               // 
        {                                               //
            RefreshPara();                              // 参数刷新
        }                                               //
        else if(0x00 != guc_KeyEvent)                   //
        {                                               //
            KeyProc();                                  // 按键处理
        }

        if(gui_SysSleepSta == 0x55aa)
        {
            goto MAINSTART;
        }
    }
}
