#define  ENERGYBOTTOMEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: EnyB_Init
* @function_file: EnergyBottom.c
* @描述: 底层初始化
* 
* 
* @参数: 
* @返回: 
* @return:  
* @作者:   liming (2016-01-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//uint8  guc_FactoryType;

void EnyB_Init(void)
{
    gs_PDirCnt.ucDirCnt = 0;
    gs_PDirCnt.ucRevDirCnt = 0;
    gs_PDirCtr.ucDelayTm = CONFIG_POW_DLY;
    gs_PDirCtr.ulPDirGate = ((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/1000;
    
    gs_Channel.ucSta = 0;
    gs_Channel.ucACnt = 0;
    gs_Channel.ucBCnt = 0;
    gs_Channel.ucGate = CONFIG_CH_DLY;
}
/*=========================================================================================\n
* @function_name: WaitACK
* @function_file: EnergyBottom.c
* @描述: 等待延时，必须是ACK从0-1-0后
* 
* 
* @参数: 
* @返回: 
* @return:  
* @作者:   hexz (2015-02-11)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void WaitACK(void)
{
    uint16 i;

    if (MEAFRQ)                 //PM时钟为PLL
    {
        for (i = 0; i < 9; i++)
        {
            _nop();
        }
        for (i = 0; i < 76; i++)
        {
            if (!XBYTE[ACK])
                break;
        }
    }else                       //PM时钟为OSC
    {
        if (MCUFRQ)                     //MCU时钟为PLL
        {
            for (i = 0; i < 240; i++)
            {
                _nop();
            }
            for (i = 0; i < 1920; i++)
            {
                if (!XBYTE[ACK])
                break;
            }
        }else                           //MCU时钟为OSC
        {
            for (i = 0; i < 1; i++)
            {
                _nop();
            }
            for (i = 0; i < 2; i++)
            {
                if (!XBYTE[ACK])
                break;
            }
        }
        return;
    }
    return;
}
/*=========================================================================================\n
* @function_name: EnyB_ReadMeterParaACK
* @function_file: EnergyBottom.c
* @描述: 双口ram设置，使用ACK信号
* 
* 
* @参数: 
* @param:addr  数据的真正地址
* 
* @返回: 
* @return: uint32 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint32 EnyB_ReadMeterParaACK1(uint16 addr)
{
//    udata8 index;
    uint32  u32PMdatal;
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    u32PMdatal=XBYTE[addr];                          //读取真实地址，加载数据到缓冲
    WaitACK();
    if (XBYTE[ACK])
    {
      debug_break(_debug_errno_EnyB_ReadMeterParaACK_);
      return false;
    }
//    u32PMdatal=(uint32)XBYTE[BUFF0];
//    temp=(uint32)XBYTE[BUFF1]<<8;
//    u32PMdatal+= temp;
//    temp=(uint32)XBYTE[BUFF2];
//    temp=temp<<16;
//    u32PMdatal+=temp;
//    temp=(uint32)XBYTE[BUFF3];
//    temp=temp<<24;
//    u32PMdatal+=temp;
    u32PMdatal  = 0;
    u32PMdatal |= XBYTE[BUFF3];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF2];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF1];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF0];
    
    return u32PMdatal;
     
}

uint32 EnyB_ReadMeterParaACK (uint16 addr)
{
      uint32  u32PMdatal ;
      _Interrupt_AppDisable() ;
      u32PMdatal =EnyB_ReadMeterParaACK1( addr) ;
      _Interrupt_AppEnable();   
      return u32PMdatal;
}

/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @描述: 双口ram设置，使用ACK信号
* 
* 
* @参数: 
* @param:u32PMdatal  数据
* @param:addr        地址
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 EnyB_SetMeterL2H(uint32 u32PMdatal ,uint16 addr)
{
    uint8 i,index;
    volatile uint32 temp;
    index=0;
    
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }
    
    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    XBYTE[addr]=0;
    MEAFRQ = 1;                               //计量切高低频
    while(!MEAFRQ)
    {
        i++;
        if(i>30)
        {
            break ; //在一定时间内没有锁定
        }
    }    
                                  //向真正的地址写入0，启动缓冲输入到真正的地址
    	

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }

    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @描述: 双口ram设置，使用ACK信号
* 
* 
* @参数: 
* @param:u32PMdatal  数据
* @param:addr        地址
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
volatile unsigned long kiki;
uint8 EnyB_SetMeterH2L(uint32 u32PMdatal ,uint16 addr)
{
    uint8 i,index;
    volatile uint32 temp;
    index=0;
      kiki  =u32PMdatal ;
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }

    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    
    MEAFRQ = 0;                               //计量切高低频
    while(MEAFRQ)
    {
        i++;
        if(i>30)
        {
            break ; //在一定时间内没有锁定
        }
    }    
    
    XBYTE[addr]=0;                              //向真正的地址写入0，启动缓冲输入到真正的地址	

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }

    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @描述: 双口ram设置，使用ACK信号
* 
* 
* @参数: 
* @param:u32PMdatal  数据
* @param:addr        地址
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 EnyB_SetMeterCfgACK1(uint32 u32PMdatal ,uint16 addr)
{
    uint8 index;
    volatile uint32 temp;
    index=0;
    
    void            Value_put ( unsigned long lData, unsigned short iAddr ) ;
    extern unsigned  long  iReg[];
    
     Value_put ( u32PMdatal, addr );
    
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }

    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    XBYTE[addr]=0;                              //向真正的地址写入0，启动缓冲输入到真正的地址

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }


    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
uint8 EnyB_SetMeterCfgACK(uint32 u32PMdatal ,uint16 addr)
{
  uint8  cresult;
    _Interrupt_AppDisable();
      cresult = EnyB_SetMeterCfgACK1(u32PMdatal,  addr);
  _Interrupt_AppEnable();
  return cresult;
}


/*=========================================================================================\n
* @function_name: InitADC
* @function_file: EnergyBottom.c
* @描述: 初始化初始化ADC，设置增益和通道
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void InitADC(uint8 MeaClk)
{
    CtrlADC0 = 0x00;   //通道模拟增益配置, 校表参数配置
    CtrlADC1 = 0x00;   //ADC斩波与偏置电流配置，默认为0
    CtrlADC2 = 0x00;   //ADC斩波与偏置电流配置，通道复位，默认为0
    CtrlADC3 = 0x00;   //ADC时钟与通道短路配置，默认为0
    CtrlBAT  = 0x00;   //电池放电控制，默认为0
    CtrlADC4 = 0x00;   //ADC电流与偏置电压配置，默认为0
    CtrlADC5 = 0x00;   //M通道配置
    CtrlM    = BIT0;   //改善测温性能配置
    if(MeaClk)
    {
        CtrlADC6 = 0;   //模拟通道开关
    }
    else
    {
        CtrlADC6 = ADCAPDN+ADCBPDN+ADCUPDN+ADCMPDN;   //模拟通道开关
    }   
}
/*=========================================================================================\n
* @function_name: InitMeaClk
* @function_file: EnergyBottom.c
* @描述: 计量时钟
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void InitMeaClk(void)
{
    uint8 i;
    
    MEAFRQ=1;                 
    i=0;
    while(!(MEAFRQ))
    {
        i++;
        if(i>20)
        {
            return;       //在一定时间内没有锁定
        }
    }
}
/*=========================================================================================\n
* @function_name: InitPMDSP
* @function_file: EnergyBottom.c
* @描述: 计量寄存器初始化
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-12)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void InitPMDSP(uint8 MeaClk)
{
    uint8 i;
    
    PMG = 0;
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl1);   
    EnyB_SetMeterCfgACK(INITGATEP,GATEP);        //设置计量初始值
    EnyB_SetMeterCfgACK(INITGATEQ,GATEQ);
    if(MeaClk)
    {
        EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);      //800k滤波器参数  
    }
    else
    {
        EnyB_SetMeterCfgACK(0x889374bc, PARABPF);      //3.2M滤波器参数
    }
    
    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
    EnyB_SetMeterCfgACK(0xC8,PMCtrl4);
    EnyB_SetMeterCfgACK(0x08,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
    
    EnyB_SetMeterCfgACK(0x01,GATECP);       //潜动1   
    EnyB_SetMeterCfgACK(0x01,GATECQ);       //潜动2
    if(MeaClk)
    {
        EnyB_SetMeterCfgACK(0x13,PMCtrl1);      //关所有通道
        EnyB_SetMeterCfgACK(0x05,CFCtrl);       //正绝对值出CF
    }
    else
    {
        EnyB_SetMeterCfgACK(0x5F,PMCtrl1);      //开启所有通道
        EnyB_SetMeterCfgACK(0x00,CFCtrl);       //正+反绝对值出CF
    }
    EnyB_SetMeterCfgACK(0x00,PMCtrl2);      //
    EnyB_SetMeterCfgACK(0x70,PMCtrl3);      //开启两路有功，次谐波抑制
    EnyB_SetMeterCfgACK(0xc0,PMCtrl4);      //等待滤波器稳定后开启
//    if(MeaClk)    //800K常数计量
//    {
//        EnyB_SetMeterCfgACK(0x10,CRPST);        //等待滤波器稳定后开启
//        EnyB_SetMeterCfgACK(0xfA,PMCtrl4);      //等待滤波器稳定后开启
//    }
//    else
//    {
//        EnyB_SetMeterCfgACK(0x00,CRPST);        //等待滤波器稳定后开启
//        EnyB_SetMeterCfgACK(0xf8,PMCtrl4);      //等待滤波器稳定后开启
//    }
    EnyB_SetMeterCfgACK(0, PHCCtrl1);       //清0
    EnyB_SetMeterCfgACK(0, PHCCtrl2);
    guc_CfOpenFlg     = true;
    guc_CfOpenCnt     = 0;      //开CF计数
}
/*=========================================================================================\n
* @function_name: EnyB_Open_Cf
* @function_file: EnergyBottom.c
* @描述: 开启CF脉冲
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_Open_Cf(void)
{   
//    if(guc_RtcConflict==0x55)
//    {
//        gui_RefreshEvent|=flgEtPara_RTC;    
//        guc_RtcConflict=0x00;
//    }

    if(guc_CfOpenCnt<1)
    {
        guc_CfOpenCnt++;
    }else
    {
        if(guc_CfOpenFlg&&(guc_CfOpenCnt>=1))
        {   
            if(guc_WorkMd != NormalMode)
            {
                EnyB_SetMeterCfgACK(0x10,CRPST);
                EnyB_SetMeterCfgACK(0xFA,PMCtrl4);  //打开计量,保持潜动开启
            } 
            else
            {
                EnyB_SetMeterCfgACK(0x00,CRPST);
                if(gs_Channel.ucSta == SETB)                    //B通道                                        
                {
                    EnyB_SetMeterCfgACK(0xFC,PMCtrl4);  //打开计量,保持潜动开启
                }
                else
                {
                    EnyB_SetMeterCfgACK(0xF8,PMCtrl4);  //打开计量,保持潜动开启
                }
            }                         
            EnyB_InitCFInt();                   //开启CF脉冲中断
            guc_CfOpenFlg=false;
        }
    }
}
/*========================================================
* @function_name: EnyB_InitCFInt
* @function_file: EnergyBottom.c
* @描述: 初始化CF中断
* 
* @作者: lwb (2012/3/3)
* @备注: 
*----------------------------------------------------------
* @修改人: 
* @修改内容:  
============================================================*/
void EnyB_InitCFInt(void)
{
    EIE|=BIT0;
    ExInt2IE|=BIT7;
//    P9OE&=(~BIT6);                          //打开CF IO输出
//    P9FS|=(BIT6);
    _CfPluse_E1Out();  
    //P1OE&=(~BIT3);
    //P1IE&=(~BIT3);
    //P13FS = 0x04;  //CFx CF1输出
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterRule
* @function_file: EnergyBottom.c
* @描述: 设置计量模块流程
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Mea_Init(void)
{
    InitADC(MEA3D2M);     //初始化ADC，设置增益和通道
    InitMeaClk();         //切计量时钟后，才能读取数据
    SLPWDT();
    //Data_RecEnergy();     //恢复电量数据    
    //SLPWDT();
    InitPMDSP(MEA3D2M);   //PM DSP init，设置计量值，防止乱出脉冲
    SLPWDT();
    EnyB_PurInit();       //计量模块上电初始化
    _CfPluse_OutEnable() ;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterRule
* @function_file: EnergyBottom.c
* @描述: 设置计量模块流程
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_SetMeterRule(uint8 MeaClk)
{
    InitADC(MeaClk);       //初始化ADC，设置增益和通道
    CLRWDT();
    InitPMDSP(MeaClk);     //PM DSP init，设置计量值，防止乱出脉冲
    CLRWDT();
    Eny_RefVar();                                       //计量参数刷新
//    EnyB_PurInit();         //计量模块上电初始化
}
/*=========================================================================================\n
* @function_name: EnyB_PurInit
* @function_file: EnergyBottom.c
* @描述: 上电初始化
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_PurInit(void)                                 
{
    Eny_RefVar();                                       //计量参数刷新
    Eny_RefCalcType();                                  //计量方式字刷新
    Eny_PurCheckRAMEny();                               //检测RAM电量
}
//extern const uint8 code InitPara0[sizeof(S_JBPM)-2];
/*=========================================================================================\n
* @function_name: EnyB_JbPm_Init
* @function_file: EnergyBottom.c
* @描述: 校表参数的初始化
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_JbPm_Init(void)                                
{                                                        
    FCpyTMem((uint8*)&gs_JbPm.ui_MeterC, InitPara0, sizeof(S_JBPM)-2);              //拷贝Flash数据到RAM中
    gs_JbPm.ui_JbCRC=do_CRC((uint8*)&gs_JbPm,sizeof(S_JBPM)-2);     // 校表参数的CRC结果
}

/*=========================================================================================\n
* @function_name: EnyB_IntCF
* @function_file: EnergyBottom.c
* @描述: 脉冲中断
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#ifdef _DEL
void EnyB_IntCF(void)                       
{
    uint8 *pCfZ;
    uint8 *pEyZ;

//    uint8 *pCf;
//    uint8 *pEy;


    //if(gs_SysRunSt.Pdir)      //判断是否是反向
//    {
//        pEyZ=&gs_Energy.ucNz;
//        pCfZ=&gs_PowerCf.uc_Nz;
//    }
//    else
//    {
        pEyZ=&gs_Energy.ucPz;                                   //正向能量
        pCfZ=&gs_PowerCf.uc_Pz;                                 //正向脉冲数
//    }
    RamData.CF_Buf

    (*pCfZ)++;                                                  //总能量累加
    if(*pCfZ >= guc_GateCF)                                     //判别是否需要走字
    {
        *pCfZ -=guc_GateCF;                                     //对CF脉冲进行分频，将分频结果进行能量累加
        *pEyZ +=guc_UnitCF; 
        gui_SystemEvent |= flgEtGlb_EnergyCalc;                 //设置能量处理事件
    }
 
//    if((gs_FunCfg.uc_CfSaveCfg&0x0F)==0x05)                     //CF脉冲分费率计数
//    {
//        if(gs_MeterState.ui_MeterState2.RunCode2Word.PADIR)     //判断是否是反向
//        {
//            pEy=(&gs_Energy.ucN1+gs_FeeData.uc_FeeNo);          //分项反向能量
//            pCf=(&gs_PowerCf.uc_N1+gs_FeeData.uc_FeeNo);        //分项反向脉冲数
//
//        }else                                                   //正向
//        {
//            pEy=(&gs_Energy.ucP1+gs_FeeData.uc_FeeNo);          //分项正向能量
//            pCf=(&gs_PowerCf.uc_P1+gs_FeeData.uc_FeeNo);        //分项正向脉冲数
//        }
//
//        (*pCf)++;                                              //反向分费率能量累加
//        if(*pCf>=guc_GateCF)                                   // 判别是否需要走字
//        {
//            *pCf -=guc_GateCF;                                 // 对CF脉冲进行分频，将分频结果进行能量累加
//            *pEy +=guc_UnitCF; 
//            gui_SystemEvent |= flgEtGlb_EnergyCalc;             //设置能量处理事件
//        }
//    }
}
#endif
/*=========================================================================================\n
* @function_name: CalRMS
* @function_file: EnergyBottom.c
* @描述: 计算瞬时量
* 
* 
* @参数: 
* @param:addr  寄存器地址
* 
* @返回: 
* @return: uint32 返回有效值
* @作者:   lwb (2012-05-22)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint32 CalRMS(uint16 addr)
{
  Word32 TempValue,TempValue2;
  uint32 TempPara,TempValue1;
  //TempValue.lword=0;
  if(addr == DATAP && gs_Channel.ucSta == SETB)
  {
      addr = DATAQ;
  }
  TempValue.lword=EnyB_ReadMeterParaACK(addr);

  switch (addr)
  {
    case DATAP:
        if(TempValue.byte[3]>0x7f)          //如果是负数的数，先变成正数
        {
            TempValue.lword=~TempValue.lword+1;
        }

        TempPara=gs_JbPm.ul_PG/256;        //读取比例系数
       
        if(TempPara==0)
        {    
            TempValue1=0;
        }
         else
        {     
             TempValue.lword=((TempValue.lword*32)/TempPara)*8;
        }
        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
        {
             TempValue1=0;
        }
        else
        {
           //  TempValue1=Hex2BCD(TempValue.lword);
              TempValue1= TempValue.lword;
             if(gs_SysRunSt.Pdir==true)   //反向添加负号
             {
                 TempValue1 =-TempValue1 ;//_NegLogeo_Set(TempValue1);//=0x800000;
             }
        }
        break;
    case DATAQ:
        if(TempValue.byte[3]>0x7f)          //如果是负数的数，先变成正数
        {
            TempValue.lword=~TempValue.lword+1;
        }

        TempPara=gs_JbPm.ul_PG/256;        //读取比例系数
       
        if(TempPara==0)
        {    
            TempValue1=0;
        }
         else
        {     
             TempValue.lword=((TempValue.lword*32)/TempPara)*8;
        }
        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
        {
             TempValue1=0;
        }
        else
        {
             //  TempValue1=Hex2BCD(TempValue.lword);
              TempValue1= TempValue.lword;
             if(gs_SysRunSt.Pdir==true)   //反向添加负号
             {
                 TempValue1 =-TempValue1 ;//_NegLogeo_Set(TempValue1);//=0x800000;
             }
        }
        break;
    case RMSU:
         if(guc_PllSta == PLL_800K)
         {
             TempValue.lword=gul_Urms800k;   
         }
         TempPara=gs_JbPm.ul_URmG/65536;   //ReadRMSPara(1);
         if(TempPara==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/TempPara;
         }

         if(TempValue.lword<ULEVEL && guc_FactoryType != FactorMd)
         {    
             return 0;
         }else
         {
             TempValue1=Hex2BCD(TempValue.lword);
         }
         break;
    case RMSI1:
        //电流的计算
        if(guc_PllSta == PLL_800K)
        {
           TempValue.lword=gul_I1rms800k;    
        }

        TempPara=gs_JbPm.ul_I1RmG/65536;    //ReadRMSPara(2);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }
        
        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2) 
           && guc_FactoryType != FactorMd)
        {    
            return 0;
        }else
        {        
            TempValue1=Hex2BCD(TempValue.lword);

            //功率的计算
            TempValue2.lword=EnyB_ReadMeterParaACK(DATAP);
            if(TempValue2.byte[3]>0x7f)                         //如果是负数的数，先变成正数
            {
                TempValue2.lword=~TempValue2.lword+1;
            }

            TempPara=gs_JbPm.ul_PG/256;        //读取比例系数

            if(TempPara==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=((TempValue2.lword*32)/TempPara)*8;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)
               && guc_FactoryType != FactorMd)
            {
                //如果功率小于启动功率，这是电流小于0.2A,电流清零
                if(TempValue1<0x200)
                {
                    TempValue1=0;
                }
            }           
            
            if(gs_SysRunSt.Pdir==true)   //反向添加负号
            {
               _NegLogeo_Set(TempValue1);//|=0x800000;
            }
        }
        break;
    case RMSI2:
       if(guc_PllSta == PLL_800K)
        {
           TempValue.lword=gul_I2rms800k;    
        }

        TempPara=gs_JbPm.ul_I2RmG/65536;    //ReadRMSPara(3);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }

        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2)
           && guc_FactoryType != FactorMd)
        {    
            return 0;
        }else 
        {    
            TempValue1=Hex2BCD(TempValue.lword);

            //功率的计算
            TempValue2.lword=EnyB_ReadMeterParaACK(DATAQ);
            if(TempValue2.byte[3]>0x7f)                         //如果是负数的数，先变成正数
            {
                TempValue2.lword=~TempValue2.lword+1;
            }

            TempPara=gs_JbPm.ul_QG/256;        //读取比例系数

            if(TempPara==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=((TempValue2.lword*32)/TempPara)*8;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)
               && guc_FactoryType != FactorMd)
            {
                //如果功率小于启动功率，这是电流小于0.2A,电流清零
                if(TempValue1<0x200)
                {
                    TempValue1=0;
                }
            }           
            
            if(gs_SysRunSt.Pdir==true)   //反向添加负号
            {
                _NegLogeo_Set(TempValue1);//|=0x800000;
            }
        }
        break;
      case DATAFREQ:
          TempValue.lword=ADCFRE*100/TempValue.lword;
          if(TempValue.lword>4950&&TempValue.lword<5050)
          {
              TempValue.lword=5000;
          }else if(TempValue.lword<4500)
          {    
              TempValue.lword=4500;
          }else if(TempValue.lword>5500)
          {    
              TempValue.lword=5500;
          }
          TempValue1=Hex2BCD(TempValue.lword);
         break;
    case RMSIU:
         if(guc_PllSta == PLL_800K)
         {
             TempValue.lword=gul_Urms800k;   
         }
         TempPara=gs_JbPm.ul_URmG/65536;   //ReadRMSPara(1);
         if(TempPara==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/TempPara;
         }

         if(TempValue.lword<ULEVEL)
         {    
             return 0;
         }else
         {
             TempValue1=TempValue.lword;
         }
         break;
    default:
        TempValue1=0;
        break;
  }

  return TempValue1;
}
/*=========================================================================================\n
* @function_name: CalCos
* @function_file: EnergyBottom.c
* @描述: 计算功率因数
* 
* @参数: 
* 
* @返回: 
* @return: uint16 
* @作者:   lwb (2012-06-01)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint16 CalCos(void)
{
    uint8 flag;
    uint32 temp_p,temp_i,temp_u;
    Word32 temp_res,temp_ui;
    temp_p = CalRMS(DATAP);
    flag=0;
    if(temp_p&_NegLogo_)   //0x800000)     //负功率
    {
        temp_p&=~_NegLogo_ ;//0x800000;  //功率取正
        flag=1;
    }
    temp_p = BCD2Hex(temp_p);
    //temp_p = BCD2Hex(CalRMS(DATAP));
    //temp_q = BCD2Hex(CalRMS(DATAQ));
    temp_i = BCD2Hex(0x7fffff&CalRMS(RMSI1));
    temp_u = BCD2Hex(CalRMS(RMSU));
 
    
    temp_res.lword = temp_p*1000;
    temp_ui.lword = temp_u*temp_i/1000;
    temp_res.lword = temp_res.lword/temp_ui.lword;
    
    temp_res.lword = Hex2BCD(temp_res.lword);
    //功率因数处理
    if(temp_res.lword>=0x990)              //大于0.99的话直接显示1.0
    {    
        temp_res.lword=0x1000;
    }else if((temp_res.lword>=0x490)&&(temp_res.lword<=0x510))        //在0.49和0.51之间直接显示0.5
    {    
        temp_res.lword=0x500;
    }else if((temp_res.lword>=0x790)&&(temp_res.lword<=0x810))        //在0.79和0.81之间直接显示0.8
    {    
        temp_res.lword=0x800;
    }else if(temp_res.lword<=0x100)                                //小于0.1情况下,根据有功功率与电流显示
    {
        if(temp_i>0x050)                           //有电流 
        {    
            if(temp_p<0x500)                       //且没有有功功率，显示0.0 
            {
                temp_res.lword=0x0000;
            }
        }
        else
        {                                           //没电流，显示1.0
            temp_res.lword=0x1000; 
        }
    }
                                                  //其余根据计算显示
    if(flag==1&&temp_res.lword!=0)
    {
        temp_res.word[0]|=0x8000;
    }
    return (uint16)temp_res.word[0];                           
}
/*=========================================================================================\n
* @function_name: EnyB_Check_PowRev
* @function_file: EnergyBottom.c
* @描述: 检测功率是否反向
* 
* @参数: *channel-通道 junc-接线方式
* @返回: true-反向 false-正向
* @作者:   lwb (2012-03-08)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 EnyB_ChkPowRev(uint8 *channel, uint8 junc)
{
    int32 l_pa,l_pb,ltempa,ltempb;
    uint32 TempPara;
  volatile  uint32 ulPower;
    uint8 flag;
    
      
    if((*channel == SETA) ||(1))
    {
        l_pa = EnyB_ReadMeterParaACK(DATAP);       
        TempPara=gs_JbPm.ul_PG>>8;          //读取比例系数
    }
    //else
    {
        l_pb = EnyB_ReadMeterParaACK(DATAQ);
        TempPara=gs_JbPm.ul_QG>>8;          //读取比例系数
    }
    ltempa = (labs(l_pa) >labs(l_pb))?l_pa:l_pb;
    l_pa = ltempa;
    
    
    if(TempPara==0)
    {   //校表参数功率计算值为0的话，直接返回
        return false;
    }
    //默认反接
    if(l_pa<0)
    {                                       
        l_pa = -l_pa;
        if(junc == 0)
        {
            flag = false;       //功率正向
        }
        else
        {
            flag = true;        //功率反向
        }
    }
    else
    {
        if(junc == 0)
        {
            flag = true;        //功率反向
        }
        else
        {
            flag = false;       //功率正向
        }
    }
  
    ulPower=((l_pa*32)/TempPara)*8;
    if(ulPower > gs_PDirCtr.ulPDirGate)
    {
        if(flag == false)
        {
            gs_PDirCnt.ucRevDirCnt=0;
            gs_PDirCnt.ucDirCnt++;
            if(gs_PDirCnt.ucDirCnt>=gs_PDirCtr.ucDelayTm)
            {
               gs_SysRunSt.Pdir=false;
            }
        }
        else
        {
            gs_PDirCnt.ucRevDirCnt++;
            gs_PDirCnt.ucDirCnt=0;
            if(gs_PDirCnt.ucRevDirCnt>=gs_PDirCtr.ucDelayTm)
            {
               gs_SysRunSt.Pdir=true;
            }
        }
    }
    
    return gs_SysRunSt.Pdir;
}
/*=========================================================================================\n
* @function_name: EnyB_Cal_Cos
* @function_file: EnergyBottom.c
* @描述: 计算功率因数
* 
* @参数: 
* 
* @返回: 
* @return: int16 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//int16 EnyB_Cal_Cos(void)
//{
//    uint32 ul_PS;
//    int16 CosA = 0;
//    if(gs_EnyInsData.ul_IARms < 40)
//    {
//        return 1000;
//    }
//    ul_PS = gs_EnyInsData.ul_URms*gs_EnyInsData.ul_IARms;
//    ul_PS /= 10000;
//    CosA = (gs_EnyInsData.l_PowerPA * 1000)/ (int32)ul_PS;
//    return CosA;
//}
 
/*=========================================================================================\n
* @function_name: EnyB_JbPm_Updata
* @function_file: EnergyBottom.c
* @描述: 刷新校表参数到SFR中
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-02)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_JbPm_Updata(void)
{//把RAM中的校表参数跟新到SFR中
    uint32 *p;
   
    if(guc_PllSta == PLL_800K)
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gateq,GATEP); 
    }
    else
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEP);        //设置I1通道功率门限制

    }
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEQ);        //设置I2通道功率门限制 
    
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECP);      //设置I1通道功率门限制
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECQ);      //设置I2通道功率门限制  

    //EnyB_Check_RMSI();
    p=&gs_JbPm.ul_SCP;
    for(uint8 i=0;i<7;i++)                              //设置功率，电压，电流比差值
    {
        EnyB_SetMeterCfgACK(*(p+i),SCP+i);           
    }
    
    if(guc_PllSta == PLL_800K)
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gateq,GATEP); 
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1,SCI1);
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2,SCI2);
    }
    
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1,PHCCtrl1);  //设置I1角差值
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2,PHCCtrl2);  //设置I2角差值
    
    CtrlADC0 = gs_JbPm.uc_AnaG;                         //设置ADC增益
    // if((gs_JbPm.uc_AnaG&0x07)==0x07)                    //IA增益40倍的话，增加IA 偏置电流
    // {
        // CtrlADC4|=BIT4;             //增加偏置电流
    // }else
    // {
        // CtrlADC4&=~BIT4;            //减少偏置电流
    // }
}

void Enyb_Reg_ModData(uint16 iAddr ,uint32 lValue, char bitoper)
{
      uint32  lData  ;   
    lData = EnyB_ReadMeterParaACK(iAddr); 
    if ( _Bit_Res_ == bitoper)
    lData &= (lValue);
      else if (_Bit_Set_ == bitoper)
    lData |= lValue;
  EnyB_SetMeterCfgACK(lData  ,iAddr);  
}


void   Enyb_Reg_ModBif( uint16 iAddr ,  char bitnum, char bitoper)
{
  uint32  lData ;
  volatile unsigned long lValue = (( uint32 )1)<<bitnum;
  
  if ( _Bit_Res_ == bitoper)
    lData = (~lValue);
  else if (_Bit_Set_ == bitoper)
    lData = lValue;  
  Enyb_Reg_ModData( iAddr  ,lData,   bitoper);  
}


const struct      STS_JBPMFORMAT  st_jbpmformat[ ]=
{   
    {(int)&(((S_JBPM *)0)->ui_MeterC), sizeof(((S_JBPM *)0)->ui_MeterC)},		  // 表常数
    {(int)&(((S_JBPM *)0)->ui_Un),sizeof(((S_JBPM *)0)->ui_Un)},		      // 标称电压
    {(int)&(((S_JBPM *)0)->ui_Ib),sizeof(((S_JBPM *)0)->ui_Ib)},		      // 标称电流
    {(int)&(((S_JBPM *)0)->ul_Gatep),sizeof(((S_JBPM *)0)->ul_Gatep)},		   //有功能量脉冲门限值32位
    {(int)&(((S_JBPM *)0)->ul_Gateq),sizeof(((S_JBPM *)0)->ul_Gateq)},		   //有功能量脉冲门限值32位
    {(int)&(((S_JBPM *)0)->ul_Gatecp), sizeof(((S_JBPM *)0)->ul_Gatecp)},		  //有功能量潜动门限值32
    {(int)&(((S_JBPM *)0)->ul_GateOSC), sizeof(((S_JBPM *)0)->ul_GateOSC)},		 //
    {(int)&(((S_JBPM *)0)->ul_SCP),sizeof(((S_JBPM *)0)->ul_SCP)},		     //有功比差值 
    {(int)&(((S_JBPM *)0)->ul_SCQ),sizeof(((S_JBPM *)0)->ul_SCQ)},		     //无功功率比差
    {(int)&(((S_JBPM *)0)->ul_SCU),sizeof(((S_JBPM *)0)->ul_SCU)},		     //电压有效值比差
    {(int)&(((S_JBPM *)0)->ul_SCI1),sizeof(((S_JBPM *)0)->ul_SCI1)},		    //通道I1电流有效值比差
    {(int)&(((S_JBPM *)0)->ul_SCI2),sizeof(((S_JBPM *)0)->ul_SCI2)},		    //通道I2电流有效值比差 
    {(int)&(((S_JBPM *)0)->ul_PARAPC),sizeof(((S_JBPM *)0)->ul_PARAPC)},		  //有功功率二次补偿
    {(int)&(((S_JBPM *)0)->ul_PARAQC),sizeof(((S_JBPM *)0)->ul_PARAQC)},//无功功率二次补偿
    {(int)&(((S_JBPM *)0)->uc_PhcCtrl1), sizeof(((S_JBPM *)0)->uc_PhcCtrl1)},		 //I1通道角差
    {(int)&(((S_JBPM *)0)->uc_PhcCtrl2), sizeof(((S_JBPM *)0)->uc_PhcCtrl2)},		 //I2通道角差
    {(int)&(((S_JBPM *)0)->ul_PG),sizeof(((S_JBPM *)0)->ul_PG)},		      //功率比例系数
    {(int)&(((S_JBPM *)0)->ul_QG),sizeof(((S_JBPM *)0)->ul_QG)},		      //功率比例系数
    {(int)&(((S_JBPM *)0)->ul_URmG), sizeof(((S_JBPM *)0)->ul_URmG)},		    //电压通道比例系数
    {(int)&(((S_JBPM *)0)->ul_I1RmG), sizeof(((S_JBPM *)0)->ul_I1RmG)},		   //电流通道1比例系数
    {(int)&(((S_JBPM *)0)->ul_I2RmG), sizeof(((S_JBPM *)0)->ul_I2RmG)},		   //电流通道2比例系数
    {(int)&(((S_JBPM *)0)->ul_SCI1_800), sizeof(((S_JBPM *)0)->ul_SCI1_800)},		//通道I1电流有效值比差
    {(int)&(((S_JBPM *)0)->ul_SCI2_800), sizeof(((S_JBPM *)0)->ul_SCI2_800)},		//通道I2电流有效值比差
    {(int)&(((S_JBPM *)0)->uc_AnaG), sizeof(((S_JBPM *)0)->uc_AnaG)},		 //模拟增益(包含I2 bit[12:9]，I1 bit[7:4]，U bit[3:0])
    {(int)&(((S_JBPM *)0)->ui_JbCRC), sizeof(((S_JBPM *)0)->ui_JbCRC)},		   // 校表参数的CRC结果 
};

const unsigned char     st_jbpmformatlen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
 
char            st_jbMod(struct      STS_JBPMFORMAT code *sttext , char  *sin)
{
    unsigned char       clen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
    
   // struct      STS_JBPMFORMAT code *sttext = (struct      STS_JBPMFORMAT code *)&(st_jbpmformat[stp->cNo]);
    
    //if ( stp->cNo >=clen)
      //  return 1;
    
      Copy_FlashInfo(((char *)&gs_JbPm) + sttext->cOffset , (char *)sin  ,sttext->cLen);
      EnyB_JbPm_Updata();
    return 0;
}

 struct      STS_JBPMFORMAT code  *     st_jbread( char  *sin)
{
    unsigned char       clen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
    struct          STJBMOD  *stp = (struct          STJBMOD *)sin;
    struct      STS_JBPMFORMAT code *sttext = (struct      STS_JBPMFORMAT code *)&(st_jbpmformat[stp->cNo]);
    
    if ( stp->cNo >=clen)
        return NULL;
    return  sttext;    
}