#define POWMANGE_EXT

#include "Include.h"

uint8 guc_ChkPowDn;                 // 下电检测寄存器
/*=========================================================================================\n
* @function_name: Pwr_DownChk
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
void Pwr_DownChk(void)
{
    guc_ChkPowDn <<= 1;
#if (CONFIG_PT == 0)
    if(!_IsUpIo())      // 判断是否电压低
#else
    if(!_IsUpIo() && PwrDetLow())      // 判断是否电压低
#endif
//    if(!_IsUpIo() && PwrDetLow())      // 判断是否电压低
    {
        guc_ChkPowDn |=0x1;                 // 把当前电压状态存入寄存器，只有连续有低电平才可以判定是下电
    }

    if(0x03 == (guc_ChkPowDn&0x03))                // 有连续的8次，也就是8ms低电平，设置下电事件
    {
        guc_ChkPowDn =0x0;
        gui_SystemEvent |= flgEtGlb_PowDown;// 设置下电事件标记
        Pwr_DownProc();                  //掉电处理       
    }
}
extern void Init_CfG(void);
/*=========================================================================================\n
* @function_name: LCDForPowerOff
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
void Pwr_LcdSet(void)
{         
//  要求显示    
    LCDInitSleep();                     //初始化LCD显示
    gs_DispStt.ucMode = Const_DispMode_TX;
    gs_DispStt.uiIndex = 0;
    gs_DispStt.ucTmr=gs_DispCont.ucLxTm;
    if(guc_PowOffRuning)
    {
        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
        ShowRefresh();                  //立即刷新
    }
    else
    {   //不要求显示     
        LCD_Off();
        CtrlLCDV=0x00;
    }
}
/*=========================================================================================\n
* @function_name: Pwr_E2Save
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

/*
void Pwr_E2Save(void)
{
    uint16 CRC;
    MemCpy(XDATA_RAMZONE,   (uint8*)&gs_EnergyData.uiEPZ,   6);        //当前电量增量
    MemCpy(XDATA_RAMZONE+6,  (uint8*)&gs_PowerCf.uc_Pz,  2);            //当前CF数
    MemCpy(XDATA_RAMZONE+8,  (uint8*)&gs_Energy.ucPz,  2);              //当前CF对应的能量    
//    MemCpy(XDATA_RAMZONE+4,  (uint8*)&gs_PowerCf.guc_EepromCFcntP,  1);
    CRC=do_CRC(XDATA_RAMZONE, 10);
    MemCpy(XDATA_RAMZONE+10,(uint8*)&CRC,2);
    BE_WriteP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,12);
}
*/
/*=========================================================================================\n
* @function_name: Pwr_DownProc
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
uint8 Pwr_DownProc(void)
{ 
    EA=0;
    IOOFF();                                              //关闭所有额外的IO
    IntOFF();                                             //关闭中断，清除中断标记
    UARTOFF();                                            //关闭所有UART       

    Tamp_Sleep();    

    Pwr_E2Save();   
    gui_SystemState |= flgStSys_PowOff;    //置掉电状态
//    guc_PowOffRuning = true; 
//    Pwr_LcdSet();
    //RTCWakeUpTm(RTC_SETSEC, 6);
    gs_WakeUp.ucType = RTC_SETSEC;
    gs_WakeUp.ucTmDly = 6;
    gs_WakeUp.ucSlpCnt = 0;
    gs_WakeUp.ucIncntA = 0;
    gs_WakeUp.ucIncntB = 0;
    if( gui_BatLowFlg == 0x5A5A) //电池电压低不去计量
    {
        CtrlADC6=0;      //关闭所有的ADC
        PMG=1;           //关闭计量时钟
        MEAFRQ=0; 
        while(MEAFRQ);
        
        RTCWakeUpTm(RTC_HOUR, 0); //小时唤醒
    }else
    {
        RTCWakeUpTm(gs_WakeUp.ucType, gs_WakeUp.ucTmDly);
    }
    //处理完写E2操作后，在处理E2端口
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();                     //I2C输出高
    
    OpenFD();
//#if (CONFIG_PT == 1)
//    OpenFD();
//#endif
//    OpenCurrentLed();
//    DelayXms(200);
    if(!POWERUP())
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
* @function_name: Pwr_WakeupProc
* @function_file: Powmanger.c
* @描述: 休眠唤醒处理
* 
* 
* @参数: 
* @返回:  
* @作者:   lm (2014-04-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
/*
void Pwr_WakeupProc(void)
{ 
    SLPWDT();     
    CloseFD();
    guc_SleepCnt = 0;    
    //计量寄存器配置优先完成
    gul_DataCP = gul_DataCP*24/103;                           //计算800k时常数计量值(大信号溢出)
    EnyB_SetMeterL2H(gul_DataCP,  DATACP);		              //写入常数功率寄存器，MEA切800k
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp, GATECP);           //写入800K潜动门限
    EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);                 //800K滤波器参数    
    EnyB_SetMeterCfgACK(0x00, PMCtrl3);                       //开启滤波器
    EnyB_SetMeterCfgACK(0x16, PMCtrl1);                       //开启双通道
    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);           //写800k电流比差
    EnyB_SetMeterCfgACK(0x10,CRPST);
    EnyB_SetMeterCfgACK(0xFA,PMCtrl4);                        //打开计量,保持潜动开启
    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800, SCI2);
    CtrlADC0 = gs_JbPm.uc_AnaG;                               //A通道ADC 16倍增益 B通道4倍
    CtrlADC6 = 0x03;	                                      //开启模拟A,B通道ADC      
    Init_Timer1(600);                                            //配置定时器1, 400ms    
    SLPWDT();
    Eny_SlpEnergyProc();              
    SLPWDT();  
    TR1 = 1;
    EA = 1;
    PCON = 1;                                                 //MCU挂起等待400ms
    EA = 0;
    SLPWDT();
    uint32 ul_PDRMI1 = EnyB_ReadMeterParaACK(RMSII1);         //读取双通道电流
    uint32 ul_PDRMI2 = EnyB_ReadMeterParaACK(RMSII2)/BMUL;       
    CtrlADC6 = 0;                                             //关AD通道   
    EnyB_SetMeterCfgACK(0, PMCtrl1);                          //停止计算，屏蔽信号
    //gul_DataCP = ul_PDRMI1;
    gul_DataCP = (ul_PDRMI1>ul_PDRMI2?ul_PDRMI1:ul_PDRMI2);   //得到大值 
    //gul_DataCP=0x6E5D5F; //DEBUG
    if(guc_PowOffRuning)
    {
        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
        ShowRefresh();                  //立即刷新
    }
    EnyB_SetMeterH2L(gul_DataCP, DATACP);                //常数计量值
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp/4, GATECP);           //写入32K潜动门限
    RTCWakeUpTm(RTC_SETSEC, 6); 
    OpenFD();
    SleepRTC();
}*/
void Pwr_WakeupProc(void)
{    
#if (MEA_SLP_PLL == 1)    
    CtrlBGP  &= 0x3f;                               //正常计量 ADC全局电流偏置 改善误差
    CtrlCLK = (CtrlCLK & 0xC3)| 0x28;               //MEA 3.2M  ADC 800K
#endif 
    gul_DataCP = gul_DataCP/MEA_AMUL;               //计算800k时常数计量值(大信号溢出)
    EnyB_SetMeterL2H(gul_DataCP,  DATACP);          //写入常数功率寄存器，MEA-32K切3.2M
#if (MEA_SLP_PLL == 0)
    EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);       //800K滤波器参数
#else
    EnyB_SetMeterCfgACK(0x889374bc, PARABPF);       //3.2M滤波器参数
#endif
    EnyB_SetMeterCfgACK(0x00, IDET);                //开启采样与功率有效值计算
#if (MEA_SLP_CF == 1)    
    EnyB_SetMeterCfgACK(0x1A, PMCtrl4);             //常数计量，使能能量累加，CF输出
    EnyB_SetMeterCfgACK(0x10,CRPST);                //脉宽40ms
#else
    EnyB_SetMeterCfgACK(0x0A, PMCtrl4);             //常数计量，使能能量累加
#endif    
    EnyB_SetMeterCfgACK(0x00, PMCtrl3);             //禁止带通滤波器
    CtrlADC0 = gs_JbPm.uc_AnaG;                         //设置ADC增益
#if (MEA_SLP_FMCU == 1)     
    PowOffSetFmcu(PLL_800K);         //MCU频率3.2M降到800K
#endif      
    /*先开模拟，再开数字,还要等待时间再开IDET*/    
#if (CONFIG_CH == 1)  
    CtrlADC6 = 0x01;	                            //开启模拟通道ADC_A,只有A路带快速电流检测
    EnyB_SetMeterCfgACK(0x12, PMCtrl1);             //开启通道A,信号输入通道1
#else    
    if(gs_Channel.ucSta == SETA)                           
    {
        CtrlADC6 = 0x01;
        EnyB_SetMeterCfgACK(0x12, PMCtrl1);         //开启通道A,信号输入通道1
    }
    else
    {
        CtrlADC6 = 0x02;
        EnyB_SetMeterCfgACK(0x32, PMCtrl1);         //开启通道B,信号输入通道1
    }    
#endif
    EnyB_SetMeterCfgACK(0x05,CFCtrl);               //仅用正向能量桶累计    
#if (MEA_SLP_PLL == 0)                              //计量800K:需要等待时间在开启 3.2M:无需等待
    Init_Timer1(5);   //MCU挂起等待5ms 
    TR1 = 1;
    EA = 1;
    PCON = 1;   //MCU挂起等待Xms  
    EA = 0;                    
    EnyB_SetMeterCfgACK(0x13, IDET);                //MEA-800K 设置判断点数4 开始判断
#else
    EnyB_SetMeterCfgACK(0x1F, IDET);                //MEA-3.2M 设置判断点数16,开始判断
#endif  
    
//#if (MEA_SLP_FMCU == 1)   //MCU 3.2M 
//    Init_Timer1(15);                                //MCU挂起等待15ms
//#else
    Init_Timer1(15);                                //MCU挂起等待15ms
//#endif    
    TR1 = 1;
    EA = 1;
    PCON = 1;    //MCU挂起等待Xms  
    EA = 0;
    
    uint8 ucIdet = EnyB_ReadMeterParaACK(IDET);     //读取判断结果
    EnyB_SetMeterCfgACK(0x00, IDET);                //关闭快速电流检测
        
    if(ucIdet & 0x40)   //判断有电流
    {
#if (MEA_SLP_PLL == 0)
        Init_Timer1(400);                        //配置定时器1, 400ms  定时器的时间不够,只能工作在MCU 800K
#else
        Init_Timer1(125);                        //配置定时器1, 125ms  
#endif
        SLPWDT(); 
        TR1 = 1;
        EA = 1;
        PCON = 1;                                   //MCU挂起等待Xms
        EA = 0;
        SLPWDT();
#if (MEA_SLP_FMCU == 1) 
        PowOffSetFmcu(PLL_3D2M);   //MCU切3.2M 
#endif         
#if (CONFIG_CH == 1) 
        gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);      //读取A路有效值
        gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新A路直流值
//        gul_I1DCval = 0xFA7600;
        EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
        CtrlADC6 = 0;                                       //关AD通道 
        EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //设置A路直流偏置
        EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //设置B路电流判断阀值
        gul_DataCP = gul_I1rms800k;
        gs_WakeUp.ucIncntA = 0;  //清空A路没电流计数 
#else        
        if(gs_Channel.ucSta == SETA)
        {
            gul_Test = 1;  //测试用
            gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);      //读取A路有效值
            gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新A路直流值
//            gul_I1DCval = 0xFA7600;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
            CtrlADC6 = 0;                                       //关AD通道 
            EnyB_SetMeterCfgACK(gul_I2DCval,0x1001);            //设置B路直流偏置
            EnyB_SetMeterCfgACK(IDET_STARTB, IDETTH);           //设置B路电流判断阀值            
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800,SCI1);
            gs_Channel.ucSta = SETB;
            gs_WakeUp.ucIncntA = 0;  //清空A路没电流计数 
        }
        else
        {
          gul_Test = 2;  //测试用                                                       
            gul_I2rms800k = EnyB_ReadMeterParaACK(RMSII1)/MEA_BMUL; //读取B路有效值   
            gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新B路直流值
//            gul_I2DCval = 0xF41500;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
            CtrlADC6 = 0;                                       //关AD通道 
            EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //设置A路直流偏置
            EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //设置A路电流判断阀值
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
            gs_Channel.ucSta = SETA;
            gs_WakeUp.ucIncntB = 0;  //清空B路没电流计数 
        }
        //得到大值
        gul_DataCP = (gul_I1rms800k>gul_I2rms800k?gul_I1rms800k:gul_I2rms800k);
#endif   
        if(gul_DataCP > RMSII1_TH) //防止小于启动电流时快速电流检测的误判
          EnyB_SetMeterH2L(gul_DataCP, DATACP);       //常数计量值
        else
        {
          gul_DataCP = 0x00;//测试用
          EnyB_SetMeterH2L(0x00, DATACP);       //常数计量值
        }
    }
    else
    {   
      SLPWDT();
      if(gs_Channel.ucSta == SETA) //A、B路没电流计数 
      {
        gs_WakeUp.ucIncntA++;
      }else
      {
        gs_WakeUp.ucIncntB++;
      }
      if((gs_WakeUp.ucIncntA>10)||(gs_WakeUp.ucIncntB>10))
      {                   
#if (MEA_SLP_PLL == 0)
        Init_Timer1(400);                        //配置定时器1, 400ms  定时器的时间不够,只能工作在MCU 800K  
#else
        Init_Timer1(125);                        //配置定时器1, 125ms  
#endif
        SLPWDT(); 
        TR1 = 1;
        EA = 1;
        PCON = 1;                                   //MCU挂起等待Xms
        EA = 0;
        SLPWDT();
      }
#if (MEA_SLP_FMCU == 1) 
      PowOffSetFmcu(PLL_3D2M);   //MCU切3.2M 
#endif 
#if (CONFIG_CH == 1) 
        gul_I1rms800k = 0;
        if(gs_WakeUp.ucIncntA>10)   //没电流大于10次唤醒间隔
        {
          gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新A路直流值
          gs_WakeUp.ucIncntA = 0;  //清空计数 
        }
//        gul_I1DCval = 0xFA7600;
        EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
        CtrlADC6 = 0;                                       //关AD通道 
        EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //设置A路直流偏置
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
        gul_DataCP = 0;
#else
        if(gs_Channel.ucSta == SETA)
        {
          gul_Test = 3;  //测试用
            gul_I1rms800k = 0;
            if(gs_WakeUp.ucIncntA>10)  //没电流大于10次唤醒间隔
            {
              gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新B路直流值
              gs_WakeUp.ucIncntA = 0;  //清空计数 
            }
//            gul_I1DCval = 0xFA7600;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
            CtrlADC6 = 0;                                       //关AD通道 
            EnyB_SetMeterCfgACK(gul_I2DCval,0x1001);            //设置B路直流偏置
            EnyB_SetMeterCfgACK(IDET_STARTB, IDETTH);           //设置B路电流判断阀值
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800,SCI1);
            gs_Channel.ucSta = SETB;
        }
        else
        {
          gul_Test = 4;  //测试用
            gul_I2rms800k = 0;
            if(gs_WakeUp.ucIncntB>10)  //没电流大于10次唤醒间隔
            {  
              gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新A路直流值
              gs_WakeUp.ucIncntB = 0;  //清空计数 
            }
//            gul_I2DCval = 0xF41500;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
            CtrlADC6 = 0;                                       //关AD通道 
            EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //设置A路直流偏置
            EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //设置A路电流判断阀值
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
            gs_Channel.ucSta = SETA;
        }
        gul_DataCP = (gul_I1rms800k>gul_I2rms800k?gul_I1rms800k:gul_I2rms800k);
#endif  
        if(gul_DataCP > RMSII1_TH)  //防止小于启动电流时快速电流检测的误判
          EnyB_SetMeterH2L(gul_DataCP, DATACP);       //常数计量值
        else
        {
          gul_DataCP = 0x00;//测试用
          EnyB_SetMeterH2L(0x00, DATACP);       //常数计量值
        }
    }    
    
#if (POW_OFF_ENYPROC == 1) 
    DelayXms(1);   //计量从高频切到32K时 在MCU 3.2M读计量寄存器时需要等待
    Eny_SlpEnergyProc(); //能量处理
#endif    
    
#if (POW_OFF_DISP == 1) 
    LCDInitSleep();    //初始化LCD显示
//    if(gs_Channel.ucSta == SETB)
//    {
//      gul_Test = (gul_I1DCval>>8)|(uint32)gul_Test<<20;
//    }else
//    {
//      gul_Test = (gul_I2DCval>>8)|(uint32)gul_Test<<20;
//    }
//    gul_Test = gul_DatCFcnt;
    gul_Test = ((uint16)(gul_DataCP>>8))|(gul_Test<<16)|(((uint32)gs_PowerCf.uc_Pz)<<20);
    PowOffShowRefresh();                  //立即刷新
#endif    
     
//    if(gul_DataCP >= RMSII1_TH)  //1A启动时寄存器RMSII1的值(经过比差计算之后的值)
//    {
//        gs_WakeUp.ucSlpCnt = 0;
//        gs_WakeUp.ucTmDly = 6;
//        gs_WakeUp.ucType = RTC_SETSEC;
//    }
//    else
//    {
//        gs_WakeUp.ucSlpCnt++;
//        if(gs_WakeUp.ucType == RTC_SETSEC && gs_WakeUp.ucSlpCnt>10)
//        {           
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly  = 0;
//            gs_WakeUp.ucType   = RTC_MIN;
//        }
//        else if(gs_WakeUp.ucType == RTC_MIN && gs_WakeUp.ucSlpCnt>59)
//        {
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly = 0;
//            gs_WakeUp.ucType = RTC_HOUR;
//        }
//        else if(gs_WakeUp.ucType == RTC_HOUR && gs_WakeUp.ucSlpCnt>23)
//        {
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly = 0;
//            gs_WakeUp.ucType = RTC_DAY;
//        }
//    }
//    RTCWakeUpTm(gs_WakeUp.ucType, gs_WakeUp.ucTmDly);  
    RTCWakeUpTm(RTC_SETSEC, 6);
    SleepRTC();
}
/*=========================================================================================\n
* @function_name: Pwr_WakeupProc
* @function_file: Powmanger.c
* @描述: 休眠唤醒处理
* 
* 
* @参数: 
* @返回:  
* @作者:   lm (2014-04-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void Pwr_SleepProc(void)
//{
//    SLPWDT();     
//    CloseFD();
//    if(guc_PowOffRuning)
//    {
//        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
//        ShowRefresh();                  //立即刷新
//    }
//    guc_SleepCnt++;
//    if(guc_SleepCnt>=3)
//    {
//        guc_SleepCnt = 3;
//        Data_RecEnergy();
//        MCUForPowerOff();
//        RTCWakeUpTm(RTC_HOUR,   0);
//    }
//    else
//    {
//        RTCWakeUpTm(RTC_SETSEC, 3);
//    }
//    SleepRTC();    
//}
/*=========================================================================================\n
* @function_name: Pwr_SlpReset
* @function_file: Powmanger.c
* @描述: 休眠唤醒处理
* 
* 
* @参数: 
* @返回:  
* @作者:   lm (2015-03-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Pwr_SlpReset(void)
{
//#if (CONFIG_PT != 0)
//    OpenFD();    
//    DetEnable();    
//#endif
//    P9OE = 0xbf;   //允许输出
    P1OE &= ~BIT3;
    P1IE &= ~BIT3;
//    P9FS |= BIT6;  //CF输出 
    P13FS = 0x04;
    
    CtrlBGP  &= 0x3f;                           //正常计量 ADC全局电流偏置 改善误差
    CtrlCLK = (CtrlCLK & 0xC3)| 0x28;           //MEA 3.2M  ADC 800K

    Mea_Init();    //计量初始化
    CtrlADC0 = gs_JbPm.uc_AnaG;                 //设置ADC增益
    CtrlADC6 = 0x03;                            //IA,IB
    EnyB_SetMeterCfgACK(0x16, PMCtrl1);         //开启通道A,信号输入通道1  I1、I2数字输入使能
    EnyB_SetMeterCfgACK(0x889374bc, PARABPF);   //3.2M滤波器参数
    
    EnyB_SetMeterCfgACK(gs_JbPm.ul_GateOSC, GATEP);   //配置常数计量门限    
    EnyB_SetMeterCfgACK(0x00, DATACP);       //常数计量值
    gul_I1rms800k = 0;
    gul_I2rms800k = 0;
    gs_WakeUp.ucIncntA = 10;   //直接更新直流值
    gs_WakeUp.ucIncntB = 10;
    gs_Channel.ucSta = SETA;

#if (MEA_SLP_FMCU == 1)     
    PowOffSetFmcu(PLL_800K);         //MCU频率3.2M降到800K
#endif    
    Init_Timer1(80);                //配置定时器1, MEA 3.2M,直流值的收敛时间 70ms  
    SLPWDT(); 
    TR1 = 1;
    EA = 1;
    PCON = 1;                                   //MCU挂起等待Xms
    EA = 0;
    SLPWDT();
#if (MEA_SLP_FMCU == 1)      
    PowOffSetFmcu(PLL_3D2M);       //MCU切3.2M
#endif    
    gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //更新A路直流值
    gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI2);    //更新B路直流值
    
    EnyB_SetMeterCfgACK(0, PMCtrl1);                    //停止计算，屏蔽信号 
    CtrlADC6 = 0;
    EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //设置A路直流偏置
    EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //设置A路电流判断阀值
    EnyB_SetMeterH2L(gs_JbPm.ul_SCI1_800,SCI1);         //写入比差值，同时计量频率切换到 低频
    
    CtrlBGP  |= 0xC0;
    CtrlCLK = (CtrlCLK & 0xC3);           //MEA 800K  ADC 200K    
    
    SLPWDT();
    guc_CfOpenFlg = false;
    gul_DataCP = 0;
    guc_SleepCnt = 0;
    gul_DatCFcnt = 0;
    guc_DatCFrmd = 0;
    gui_DatCFdec = 0;
    RecoverEnergyData();
    gui_SystemState = flgStSys_PowOff;    //置掉电状态 
    Init_CfG();
}
/*=========================================================================================\n
* @function_name: Pwr_ChkProc
* @function_file: Powmanger.c
* @描述: 上电判断处理
* 
* 
* @参数: 
* @返回:  
* @作者:   lm (2015-03-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
bool Pwr_ChkProc(void)
{
    uint8 i;
    //上电稳定时间
    
    for(i=0; i<CONFIG_DELAY; i++)
    {
        if(POWERUP())
        {
            break;
        }
//        SLPWDT();               //800k喂狗
//        DelayOSC(15); 
    }
    SLPWDT();               //800k喂狗
    if(i >= CONFIG_DELAY && !POWERUP())        //没电
    {  
#if (MEA_SLP_FMCU == 1)      
       if(PowOffSetFmcu(PLL_3D2M) == 0)   //MCU切3.2M
        {
          return false;
        }
#endif 
 //////////////////////////////////////////////////////
//        Init_Timer1(100);         //测试用
//        SLPWDT(); 
//        TR1 = 1;
//        EA = 1;
//        PCON = 1;                          
//        EA = 0;
//        SLPWDT();
//        RTCWakeUpTm(RTC_SETSEC, 6);
//        SleepRTC();
 //////////////////////////////////////////////////////       
        if((gs_FunCfg.ul_CRC != do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2)) || PORRESET())  //没电池导致ram乱
        {
            Pwr_SlpReset();         
        }
        SLPWDT();
//#if (POW_OFF_DISP == 1)        
//        guc_PowOffRuning = true;
//        Pwr_LcdSet();
//#endif        
//#if (CONFIG_PT != 0)        //带PT
//        if(!PwrDetLow())   //有电流        
//        {
//            Pwr_WakeupProc();       //唤醒处理
//        }
//        else              
//        {
//            Pwr_SleepProc();
//        }
//#else                   //不带PT
        if( gui_BatLowFlg == 0x5A5A) //电池电压低不去计量
        {
          CtrlADC6=0;      //关闭所有的ADC
          PMG=1;           //关闭计量时钟
          MEAFRQ=0; 
          while(MEAFRQ);
          
          RTCWakeUpTm(RTC_HOUR, 0); //小时唤醒
          SleepRTC();
        }else
        {
          Pwr_WakeupProc();       //唤醒处理
        }
//#endif
        return false;         //休眠失败
    }
    
    for(i=0; i<20; i++)      //整个周期400ms
    {
        SLPWDT();               //800k喂狗
        DelayOSC(15);           //
        if(!POWERUP())          //POWERDN调试不能用
        {
            IOOFF();                            //关闭所有额外的IO
            MCUForPowerOff();
            IntOFF();                           //关闭中断，清除中断标记
            UARTOFF();                          //关闭所有UART
            gs_FunCfg.ul_CRC = do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2) +1;//使CRC错误，恢复配置
            RTCWakeUpTm(RTC_SETSEC, 6);
//            RTCWakeUpTm(RTC_DAY,0x00);         //1hour唤醒
            Sleep();
            return false;
        }        
    }

    return true;
}
/*=========================================================================================\n
* @function_name: Pwr_ChkProc
* @function_file: Powmanger.c
* @描述: 上电判断处理
* 
* 
* @参数: 
* @返回:  
* @作者:   lm (2015-03-03)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Pwr_UpProc(void)
{
    
}
