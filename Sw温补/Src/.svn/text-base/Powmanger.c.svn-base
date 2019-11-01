
#define POWMANGE_EXT

#include "Include.h"

uint8 guc_ChkPowDn;                 // 下电检测寄存器
/*=========================================================================================\n
* @function_name: PowDownChk
* @function_file: Powmanger.c
* @描述:
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-23)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void PowDownChk(void)
{
    guc_ChkPowDn <<= 1;

    if(!(Systate&BIT0))                      // 判断是否电压低
    {
        guc_ChkPowDn |=0x1;                 // 把当前电压状态存入寄存器，只有连续有低电平才可以判定是下电
    }

    if(0xff == guc_ChkPowDn)                // 有连续的8次，也就是8ms低电平，设置下电事件
    {
        gui_SystemEvent |= flgEtGlb_PowDown;// 设置下电事件标记
        gui_SystemState |= flgStSys_PowOffing;
        guc_ChkPowDn =0x0;
    }
}
/*=========================================================================================\n
* @function_name: Pow_DnProc
* @function_file: System.c
* @描述: 掉电处理函数
*
* @参数:
* @返回:
* @作者:   lwb (2012-01-31)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 Pow_DnProc(void)
{
    Word32  ul_PowerDownRMU;
//  uint16 uiPowOffShowTm;
    uint16 CRC;
    EA=0;
    IOOFF();                            //关闭所有额外的IO
    ul_PowerDownRMU.lword = EnyB_ReadMeterParaACK(RMSIU);            //电源异常时读取电压值
    MCUForPowerOff();
    //保存电量处理
    CtrlM |= BIT7; //3.3V的时候POWSWT_ENN置1
    IntOFF();                           //关闭中断，清除中断标记
    UARTOFF();                          //关闭所有UART
    //Eny_EnergyActiveSave();
    MemCpy(XDATA_RAMZONE,   (uint8*)&gs_EnergyData.uiEPZ,   22);        //当前电量增量
    MemCpy(XDATA_RAMZONE+22,(uint8*)&gs_FeeData.uc_FeeNo,   1);         //当前费率
    MemCpy(XDATA_RAMZONE+23,(uint8*)&gs_DateTime.ucSecond,  6);         //当前时间
    MemCpy(XDATA_RAMZONE+29,(uint8*)&gs_PowerCf.uc_Pz,  10);            //当前CF数
    MemCpy(XDATA_RAMZONE+39,(uint8*)&gs_Energy.ucPz,  10);              //当前CF对于的能量
    MemCpy(XDATA_RAMZONE+49,(uint8*)&gui_DyPgmOut,          2);         //写入编程剩余时间
    MemCpy(XDATA_RAMZONE+51,(uint8*)&gui_DyProDmOut,        2);         //写入厂内剩余时间
    MemCpy(XDATA_RAMZONE+53,(uint8*)&gs_PassWordCtr.uiDyPW2Out,4);      //写入闭锁剩余时间
    MemCpy(XDATA_RAMZONE+57,(uint8*)&gul_PowerTm,4);                    //停电时间  
    MemCpy(XDATA_RAMZONE+61,(uint8*)&gs_PowDn.ucFlg,1);                    //停电时间  
    CRC=do_CRC(XDATA_RAMZONE, 62);

    MemCpy(XDATA_RAMZONE+62,(uint8*)&CRC,2);
    BE_WriteP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,64);    
    Rpt_Crc();//写入主动上报
    //ul_PowerDownRMU.lword = EnyB_ReadMeterParaACK(RMSU);            //电源异常时读取电压值
    if(JudgePowerDnValue(ul_PowerDownRMU.lword))
    {
        if(POWERSTATE())
        {
            gui_SystemState |= flgStSys_PowErr;  
            gs_powerErr=0x5A5A;
        }
    }
    gui_SystemState |= flgStSys_PowOff;                                 //掉电状态

    guc_PowOffRuning=false;
    LCD_Off();
    RTCWakeUpTm(RTC_HOUR);              //1hour唤醒

    //处理完写E2操作后，在处理E2端口
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();                     //I2C输出高
    
    
    if(POWERSTATE())
    {
        if(Sleep())
        {
        }
        else
        {
            return false;
        }
    }
    return false;
}
/*=========================================================================================\n
* @function_name: JudgePowerDnValue
* @function_file: Powmanger.c
* @描述: 判断下电时读取的电压瞬时值
* 
* 
* @参数: 
* @param:RMSUValue  
* 
* @返回: 
* @return: uint8 
* @作者:   xuqf (2013-1-30)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 JudgePowerDnValue(uint32 RMSUValue)
{
    uint32 TempPara;
    TempPara=gs_JbPm.ul_URmG/65536;   //ReadRMSPara(1);
    if(TempPara==0)
    {    
      return 0;
    }
    else
    {    
       RMSUValue=RMSUValue/TempPara;
    }
    
    if(RMSUValue>CRIULEVEL1&&RMSUValue<CRIULEVEL2)        //如果电压值大于0.8U=176V或者小于1.15U=253V
    {   
        return true;
    }else
    {
        return 0;
    }
    
}
/*=========================================================================================\n
* @function_name: RTCWakeUPFunc
* @function_file: main.c
* @描述: RTC唤醒处理
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
uint8 RTCWakeUPFunc(void)
{
    CLRWDT();
    SetPLL800K();
    CoverScanSleep();                   //开盖检测 
    if(guc_PowOffRuning)                //唤醒状态
    {
        gs_DispStt.ulPwrOffTmr=0;       //停显时间清零
        
        if(SleepDisp())                 //休眠显示
        {
        }
        else
        {
            if(guc_PoweroffCoverJl==0x50)
            {
                RTCWakeUpTm(InitPara38[1]);      //有电下是关表盖，停电开了表盖没有闭合，则分钟唤醒
            }else
            {
                RTCWakeUpTm(RTC_HOUR);      //1hour唤醒
            }
            SleepDispInit();            //关闭屏幕初始化显示指针
            LCD_Off();
            Sleep();
        }
    }                                   //小时唤醒
    else                                //普通休眠状态
    {
        if(guc_PoweroffCoverJl==0x50)
        {
            RTCWakeUpTm(InitPara38[1]);      //有电下是关表盖，停电开了表盖没有闭合，则分钟唤醒
            //这里考虑一下是否要RTC补偿
            gui_WakeUpCnt++;
            if(gui_WakeUpCnt>=60)
            {
                gui_WakeUpCnt=0;
                CtrlADC6=0x08;
                CtrlADC5=0x81;
                EnyB_SetMeterCfgACK(0x18,PMCtrl1);
                DelayXms(15);
                CalRTC();
            }
        }else
        {
            RTCWakeUpTm(RTC_HOUR);          //1hour唤醒
            CtrlADC6=0x08;
            CtrlADC5=0x81;
            EnyB_SetMeterCfgACK(0x18,PMCtrl1);
            DelayXms(15);
            CalRTC();
        }
    }

    if(SleepRTC())
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*=========================================================================================\n
* @function_name: IOWakeUPFunc
* @function_file: main.c
* @描述: IO口唤醒处理
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
uint8 IOWakeUPFunc(void)
{
    CLRWDT();                           //喂狗
    SetPLL800K();
    if(KeyStUp())
    {
        LCDInitSleep();                     //初始化LCD显示
        SleepTimeProc();                    //读取RTC时钟到RAM中,       
        if(guc_PowOffRuning==true)          //如果已经处在唤醒状态下
        {
            KeyDispSleepDown();             //检测按键
        }
        else
        {
            //唤醒后，轮显一轮
            gs_DispStt.ucMode = Const_DispMode_LX;
            gs_DispStt.uiIndex = 0;
            gs_DispStt.ucTmr=gs_DispCont.ucLxTm;
            gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
            ShowRefresh();                  //立即刷新
            guc_PowOffRuning=true;          //当前在唤醒状态
        }
    }
    RTCWakeUpTm(RTC_SEC);               //初始化为1S RTC唤醒
    CoverScanSleep();                   //开盖检测
    if(SleepRTC())
    {
        return true;
    }
    else
    {    
        return false;
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
    MemSet(&gs_FunCfg.uc_CfSaveCfg,0,sizeof(GSFUNCFG)-2);                          //清零配置项
}
/*=========================================================================================\n
* @function_name: Pow_UpProc
* @function_file: Powmanger.c
* @描述: 上电判断
* 
* 
* @参数: 
* @返回: 
* @return: uint8 
* @作者:   lm (2014-09-01)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 Pow_UpProc(void)
{
    if(POWERSTATE())
    {
        CtrlM |= BIT7; //3.3V的时候POWSWT_ENN置1
        SetPLL800K();
        if(gs_DispCont.ul_CRC != do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2)) //停电下CRC不对，使用默认
        {
          gs_DispCont.ucLxCnt = InitPara3[33];       //轮显屏数
          gs_DispCont.ucJxCnt = InitPara3[37];        //键显屏数
          gs_DispCont.ucLxTm = InitPara3[34];        //每屏显示时间
          gs_DispCont.ucJxTm = InitPara3[39];         //键显时间
          gs_DispCont.ucJxPowOffTm = InitPara3[40];    //停电键显时间
          gs_DispCont.ul_CRC = do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);
        }
        if(RTCWAKEUP())
        {
            if(RTCWakeUPFunc())
            {               
                //SleepRTC();
            }
            else
            {
                return false;
            }
        }

        if(IOWAKEUP())
        {
            if(IOWakeUPFunc())
            {
            }
            else
            {
                return false;
            }
        }
        Eny_PurCheckRAMEny();
        Init_CfG();
        IOOFF();                            //关闭所有额外的IO
        MCUForPowerOff();
        IntOFF();                           //关闭中断，清除中断标记
        UARTOFF();                          //关闭所有UART
        RTCWakeUpTm(RTC_HOUR);                          //1hour唤醒
        if(Sleep())
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}


