#define  ENERGYBOTTOMEXT
#include "Include.h"


/*=========================================================================================\n
* @function_name: EnyB_InitAnalog
* @function_file: EnergyBottom.c
* @描述: 将没有用到过的寄存器位清零
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_InitAnalog(void)
{
//  unsigned char xdata *point;
//  point = 0x285d;
//  *point = 0;
//  point++;
//  point++;
// *point = 0;
//  point = 0x2868;
//  *point = 0;
    CtrlSHORT=0;
    CtrlBAT=0;
    CtrlPLL=0;

}

/*=========================================================================================\n
* @function_name: EnyB_InitMeter
* @function_file: EnergyBottom.c
* @描述: 一般初次上电执行，完成清除所有计量寄存器，并设置门限值
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_InitMeter(void)
{
    uint8 i;
    volatile uint8x *p;

    p = (volatile uint8x *)0x2878;
   *p = 0x80;
    p  = (volatile uint8x *)0x10e8;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    for( i = 0x00; i <= 0xe3; i++)
    {
        p  =(volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    for( i = 0xf0; i <= 0xfd; i++)
    {
        p  = (volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    p = (volatile uint8x *)0x10e8;
    *p = 0xbc;
    p++;
    *p = 0x74;
    p++;
    *p = 0x93;
    p++;
    *p = 0x88;
    p++;
    *p = 0;
    for( i = 0xe4; i <= 0xe6; i++)
    {
        p  = (volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    p  = (volatile uint8x *)0x10e8;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0x8c;
    p++;
    *p = 0x01;
    p  = (volatile uint8x *)0x10f4;
    *p = 0;
    nop();nop();nop();
    p  = (volatile uint8x *)0x10fa;
    *p = 0;
    nop();nop();nop();
    p  = (volatile uint8x *)0x10e8;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0x00;
    p  = (volatile uint8x *)0x10f5;
    *p = 0;
    nop();nop();nop();
    p  =(volatile uint8x *) 0x10fb;
    *p = 0;
    nop();nop();nop();
    p =(volatile uint8x *) 0x2878;
    *p = 0x00;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfg
* @function_file: EnergyBottom.c
* @描述:  设置计量电路各项参数
*
*
* @参数:
* @param:addr  计量寄存器地址
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:    配置数据用全局变量u32PMdatal、8PMdatah
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_SetMeterCfg(uint16 addr)
{
    volatile uint8x   *p;

    p  = (volatile uint8x *)0x10e8;
    *p = (uint8)(u32PMdatal);
    p++;
    *p = (uint8)(u32PMdatal>>8);
    p++;
    *p = (uint8)(u32PMdatal>>16);
    p++;
    *p = (uint8)(u32PMdatal>>24);
    p++;
    *p = (uint8)(u8PMdatah);
    p  = (volatile uint8x *)addr;
    *p = 0;
    nop();nop();nop();
}
/*=========================================================================================\n
* @function_name: ReadMeterPara
* @function_file: EnergyBottom.c
* @描述: 读取计量电路各项参数
*
*
* @参数:
* @param:addr  计量寄存器地址
* @返回:
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint32 ReadMeterPara(uint16 addr)
{
    volatile uint8 xdata *u8Point;
    volatile uint32 xdata *u32Point;
    volatile uint8 i;


    u8Point = (volatile uint8x *)addr;
    i  = *u8Point;
    nop();nop();nop();

    u8Point = (volatile uint8x *)0x10ec;
    u8PMdatah = *u8Point;
    u32Point = (volatile uint32x *)0x10e8;
    return *u32Point;                       //这里看一下是否正确。
}
/*=========================================================================================\n
* @function_name: EnyB_SetADC
* @function_file: EnergyBottom.c
* @描述: 配置电流、电压通道
*
*
* @参数:
* @param:val_channel  ADC 选择通道
*                    SETADC_IA ----电流A 通道;
*                    SETADC_IB ----电流B 通道;
*                    SETADC_U ----电压通道
* @param:val_para  ADC 增益选择：
*                   SETADC_IT1 对应IA、IB通道1倍增益;
*                   SETADC_IT4 对应IA、IB通道4倍增益;
*                   SETADC_IT8 对应IA、IB通道8倍增益;
*                   SETADC_IT16 对应IA、IB通道16倍增益;
*                   SETADC_UT1 对应U通道1倍增益;
*                   SETADC_CLOSE 关闭相应通道
*
* @返回:
* @作者:   lwb (2012-03-02)
* @备注: 电压ADC只有1倍增益（无增益），电流ADC只有1、4、8、16四种增益
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_SetADC(uint8 val_channel,uint8 val_para)
{
    uint8  tmp;
    val_channel &= 0x03;
    tmp = CtrlADC;

    if(val_para&0x80)
    {
        CtrlADC =tmp&(~(0x01<<val_channel));
        return;
    }

    val_para = val_para&0x0f;
    tmp |=(0x01<< val_channel);

    CtrlADC = tmp;

    XBYTE[0x2858+val_channel] = val_para;
}

/*=========================================================================================\n
* @function_name: EnyB_SetMChannel
* @function_file: EnergyBottom.c
* @描述: 配置M通道
*
*
* @参数:
* @param:val_channel  M 通道的测量通道选择
*                   0x00: measure the ground;
*                   0x01: measure temperature
*                   0x22: measure battery SETM_VBAT1// 分压后
*                   0x23: measure battery SETM_VBAT2// 分压后
*                   0x03: measure external input VM // 不分压
*                   0x04: measure SEG33             // 不分压
*                   0x05: measure SEG34             // 不分压
*                   0x06: measure SEG35             // 不分压
*                   0x07: measure SEG36             // 不分压
*                   0x24: measure SEG33             // 分压后
*                   0x25: measure SEG34             // 分压后
*                   0x26: measure SEG35             // 分压后
*                   0x27: measure SEG36             // 分压后
* @param:val_para     M 通道增益选择
*                     SETM_T1 对应1倍增益
*                     SETM_T2 对应2倍增益
*                     SETM_CLOSE 表示关闭M通道
*
* @返回:
* @作者:   lwb (2012-03-02)
* @备注: M 通道增益选择：0x00,0x01,0x11,0x31 分别对应1,2,4,8 倍增益,0x80表示关闭M通道
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_SetMChannel(uint8 val_channel,uint8 val_para)
{
    if(val_para&0x80)
    {
        CtrlADC &= ~0x08;   //关M通道
        CtrlMEAS = 0;
        return;
    }

    CtrlADC |= 0x08;        //开m通道
    CtrlGM = val_para&0x01;
    CtrlMEAS &= 0x80;
    CtrlMEAS |= val_channel;
}
/*=========================================================================================\n
* @function_name: EnyB_SetAnlog
* @function_file: initial.c
* @描述: 初始模拟电路
*
* @参数：
* @返回：
* @作者：
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:  Lwb (2011-6-27)
* @修改内容:
===========================================================================================*/
void EnyB_SetAnlog(void)
{
    PMCtrl1 |= 0x50;                        //使能角差校正，使能计量，开启I1,I2通道
    PMCtrl2 = 0;
    PMCtrl3 = 0x20;                         //使能次谐波抑制功能

    EnyB_SetADC(SETADC_U ,SETADC_UT1);      //设置电压通道增益为1倍
    EnyB_SetADC(SETADC_IA ,SETADC_IT16);    //设置IA通道增益为16倍
    EnyB_SetADC(SETADC_IB ,SETADC_IT4);     //设置IB通道增益为4倍

    PMCtrl1 |= 0x0F;                        //打开电压通道 IA通道 IB通道
    PMCtrl4 &= ~BIT0;                       //有功累加
    CFCtrl = 0;                             //以正相以及反相能量之和为依据产生CF
}
/*=========================================================================================\n
* @function_name: EnyB_CalRMS
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
uint32 EnyB_CalRMS(uint16 addr)
{
  Word32 TempValue,TempValue2;
  uint32 TempValue1;
  TempValue.lword=ReadMeterPara(addr);

  switch (addr)
  {
    case DATAP:
        if(TempValue.byte[3]>0x7f)          //如果是负数的数，先变成正数
        {
            TempValue.lword=~TempValue.lword+1;
        }
       
        if(gs_JbPm.ul_PG==0)
        {    
            return 0;
        }
        else
        {     
             TempValue.lword=(TempValue.lword*100/gs_JbPm.ul_PG);
        }

//        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))      //小于启动电流的一半，直接清零
//        {
//            return 0;
//        }
//        else
        {
             TempValue1=Hex2BCD(TempValue.lword);                                   

//             if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //反向添加负号
//             {
//                 TempValue1|=0x800000;
//             }
        }
        break;
      case RMSU:
//    case RMSIU:
         if(gs_JbPm.ul_URmG==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/gs_JbPm.ul_URmG;
         }

//         if(TempValue.lword<(gs_JbPm.ui_Un/100))        //小于10%的电压，清零
//         {    
//             return 0;
//         }else
         {
             TempValue1=Hex2BCD(TempValue.lword);
         }
         break;
    case RMSI1:
        //电流的计算
        if(gs_JbPm.ul_I1RmG==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/gs_JbPm.ul_I1RmG;
        }
        
//        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2))   //小于启动电流的1半，清零
//        {    
//            return 0;
//        }
//        else
        {    

            TempValue1=Hex2BCD(TempValue.lword);
            //功率的计算
            TempValue2.lword=ReadMeterPara(DATAP);
            if(TempValue2.byte[3]>0x7f)                         //如果是负数的数，先变成正数
            {
                TempValue2.lword=~TempValue2.lword+1;
            }


            if(gs_JbPm.ul_PG==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=TempValue2.lword/gs_JbPm.ul_PG;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
            {
                //如果功率小于启动功率，这是电流小于0.2A,电流清零
                if(TempValue1<0x200)
                {
                    return 0;
                }
            }

//            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //反向添加负号
//            {
//                TempValue1|=0x800000;
//            }
        }
        break;
    case RMSI2:
        if(gs_JbPm.ul_I2RmG==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/gs_JbPm.ul_I2RmG;
        }

//        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2))   //小于启动电流的1半，清零
//        {    
//            return 0;
//        }
//        else 
        {    
            TempValue1=Hex2BCD(TempValue.lword);
            
//            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //反向添加负号
//            {
//                TempValue1|=0x800000;
//            }
        }
        break;
//    case DATAFREQ:
//        TempValue.lword=ADCFRE*100/TempValue.lword;
//        if(TempValue.lword>4950&&TempValue.lword<5050)
//        {
//            TempValue.lword=5000;
//        }else if(TempValue.lword<4500)
//        {
//            TempValue.lword=4500;
//        }else if(TempValue.lword>5500)
//        {
//            TempValue.lword=5500;
//        }
//        TempValue1=Hex2BCD(TempValue.lword);
//       break;
    default:
        TempValue1=0;
        break;
  }

  return TempValue1;
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
    if(guc_OpenCfTmCnt<3)
    {
        guc_OpenCfTmCnt++;
    }
    
    if ((!guc_CfOpenFlg)&&(guc_OpenCfTmCnt>=2))
    {
        guc_CfOpenFlg=true;

        u8PMdatah   =0;
        u32PMdatal = (gs_JbPm.ul_Gatecp<<1);
        EnyB_SetMeterCfg(GATECP);           //第一个脉冲潜动门限制夸大2倍
        EnyB_SetMeterCfg(GATECQ);
        EnyB_InitCFInt();                   //开启CF脉冲中断
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
    PMCtrl4 |= (BIT4+BIT3);         //开启CF
    EIE|=0x01;
    ExInt2IE|=BIT7;                 // 开启CF中断
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
void EnyB_SetMeterRule(void)
{
    EnyB_InitAnalog();      //初始化模式部分
    EnyB_InitMeter();       //初始化计量寄存器
    EnyB_SetAnlog();        //初始化模拟通道
    EnyB_PurInit();         //计量模块上电初始化
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
    Eny_RefVar();                           //计量参数刷新

    PMCtrl4 |= BIT5;                        // 开启潜动功能
    PMCtrl1 &= ~BIT5;                       //选择I1计量
    u32PMdatal = 1;
    EnyB_SetMeterCfg(GATECP);               //开启CF之前一直清能量桶数据
    EnyB_SetMeterCfg(GATECQ);

    //第一个脉冲，门限制扩大2倍

    u32PMdatal=(gs_JbPm.ul_GatepL<<1);      //第一个脉冲，门限制扩大2倍
    if(gs_JbPm.ul_GatepL>=0x80000000)
    {
        u8PMdatah=(gs_JbPm.uc_GatepH<<1)+1;
    }else
    {
        u8PMdatah=(gs_JbPm.uc_GatepH<<1);
    }
            

    EnyB_SetMeterCfg(GATEP);               //开启CF之前一直清能量桶数据
    EnyB_SetMeterCfg(GATEQ);
    guc_OpenCfTmCnt=0;                     //延时2s开启CF
    Eny_PurCheckRAMEny();                  //检测RAM电量
}
extern const uint8 code InitPara3[sizeof(S_JBPM)-2];
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

    FCpyTMem((uint8*)&gs_JbPm.ui_MeterC,InitPara3,sizeof(S_JBPM)-2);    //拷贝Flash数据到RAM中
    gs_JbPm.ui_JbCRC=do_CRC((uint8*)&gs_JbPm,sizeof(S_JBPM)-2);         // 校表参数的CRC结果
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
void EnyB_IntCF(void)
{
//  if(gs_PDirCnt.PDir==true)                           //判断是否是反向
//  {
//      gs_PowerCf.uc_N ++;                             // 正向能量累加
//      if(gs_PowerCf.uc_N>=guc_GateCF)                 // 判别是否需要走字
//      {
//          gs_PowerCf.uc_N -=guc_GateCF;               // 对CF脉冲进行分频，将分频结果进行能量累加
//          gs_Energy.ucN +=guc_UnitCF;
//          gui_SystemEvent|=flgEtGlb_EnergyCalc;       //设置能量处理事件
//      }
//  }
//  else
    {
        gs_PowerCf.uc_P ++;                             // 正向能量累加
        if(gs_PowerCf.uc_P>=guc_GateCF)                 // 判别是否需要走字
        {
            gs_PowerCf.uc_P -=guc_GateCF;               // 对CF脉冲进行分频，将分频结果进行能量累加
            gs_Energy.ucP +=guc_UnitCF;
            gui_SystemEvent|=flgEtGlb_EnergyCalc;       //设置能量处理事件
        }
    }
}
/*=========================================================================================\n
* @function_name: EnyB_Check_PowRev
* @function_file: EnergyBottom.c
* @描述: 检测功率是否反向
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-08)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_Check_PowRev(void)
{
    int32 l_pa;
    uint32 TempPara;
    uint32 ulPower;

    l_pa = ReadMeterPara(DATAP);
    if(l_pa<0)
    {                                       //功率反向
        l_pa=-l_pa;
        TempPara=gs_JbPm.ul_PG>>8;          //读取比例系数
        if(TempPara==0)
        {                                   //校表参数功率计算值为0的话，直接判断功率原始值
            if(l_pa>0x2000)
            {
                gs_PDirCnt.ucRevDirCnt++;
                gs_PDirCnt.ucDirCnt=0;
                if(gs_PDirCnt.ucRevDirCnt>=3)
                {
                    gs_PDirCnt.PDir=true;
                }
            }
            else
            {
                gs_PDirCnt.ucRevDirCnt=0;
                gs_PDirCnt.ucDirCnt++;
                if(gs_PDirCnt.ucDirCnt>3)
                {
                    gs_PDirCnt.PDir=false;
                }
            }
        }
        else
        {   
            ulPower=(l_pa*100/gs_JbPm.ul_PG);
            if(ulPower>110)
            {
                gs_PDirCnt.ucRevDirCnt++;
                gs_PDirCnt.ucDirCnt=0;
                if(gs_PDirCnt.ucRevDirCnt>=3)
                {
                   gs_PDirCnt.PDir=true;
                }
            }
            else
            {
                gs_PDirCnt.ucRevDirCnt=0;
                gs_PDirCnt.ucDirCnt++;
                if(gs_PDirCnt.ucDirCnt>=3)
                {
                    gs_PDirCnt.PDir=false;
                }
            }
        }
    }
    else
    {
        gs_PDirCnt.ucRevDirCnt=0;
        gs_PDirCnt.ucDirCnt++;
        if(gs_PDirCnt.ucDirCnt>=3)
        {
            gs_PDirCnt.PDir=false;
        }
    }
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
    if(guc_ResetFlg)                            //没有出脉冲的话
    {
        u32PMdatal=(gs_JbPm.ul_GatepL<<1);      //第一个脉冲，门限制扩大2倍
        if(gs_JbPm.ul_GatepL>=0x80000000)
        {
            u8PMdatah=(gs_JbPm.uc_GatepH<<1)+1;
        }else
        {
            u8PMdatah=(gs_JbPm.uc_GatepH<<1);
        }

    }else
    {
        u8PMdatah =gs_JbPm.uc_GatepH;     //门限制高位
        u32PMdatal=gs_JbPm.ul_GatepL;
    }
    EnyB_SetMeterCfg(GATEP);            //设置I1通道功率门限制
    EnyB_SetMeterCfg(GATEQ);            //设置I2通道功率门限制

    u8PMdatah = 0;
    if(guc_ResetFlg)
    {
        u32PMdatal=(gs_JbPm.ul_Gatecp<<1); //潜动门限制
    }else
    {
        u32PMdatal=gs_JbPm.ul_Gatecp;   //潜动门限制
    }

    EnyB_SetMeterCfg(GATECP);           //设置I1通道功率门限制
    EnyB_SetMeterCfg(GATECQ);           //设置I2通道功率门限制

    p=&gs_JbPm.ul_SCP;
    for(uint8 i=0;i<7;i++)              //设置功率，电压，电流比差值
    {
        u32PMdatal=*(p+i);
        EnyB_SetMeterCfg(SCP+i);
    }

    PHCCtrl1=gs_JbPm.uc_PhcCtrl1;       //设置I1角差值
    PHCCtrl2=gs_JbPm.uc_PhcCtrl2;       //设置I2角差值
    
    CtrlGA=(gs_JbPm.uc_ADCGain&0x03);
    CtrlGB=((gs_JbPm.uc_ADCGain>>2)&0x03);
    CtrlGU=((gs_JbPm.uc_ADCGain>>4)&0x03);

}
/*=========================================================================================\n
* @function_name: EnyB_FstPluseProc
* @function_file: EnergyBottom.c
* @描述: 第一个脉冲处理
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-09)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_FstPluseProc(void)
{

    u8PMdatah   =gs_JbPm.uc_GatepH;     //门限制高位
    u32PMdatal=gs_JbPm.ul_GatepL;
    EnyB_SetMeterCfg(GATEP);            //设置I1通道功率门限制
    EnyB_SetMeterCfg(GATEQ);            //设置I2通道功率门限制

    u8PMdatah = 0;
    u32PMdatal=gs_JbPm.ul_Gatecp;       //潜动门限制
    EnyB_SetMeterCfg(GATECP);           //设置I1通道功率门限制
    EnyB_SetMeterCfg(GATECQ);           //设置I2通道功率门限制
}

/*=============================================================================================\n
Function：自动校正算法
 ================================================================================================*/

/*=========================================================================================\n
* @function_name: CalculateSC
* @function_file: EnergyBottom.c
* @描述: 计算公式
*
*
* @参数:
* @param:CurValue
* @param:TarValue
* @param:LastSC
*
* @返回:
* @return: uint32
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint32 CalculateSC(int32 CurValue,int32 TarValue,int32 LastSC)
{
    //计算公式更换,雷文斌，2011年7月14日
    int16 Error;
    uint16 Stemp0remd,Stemp2remd;
    int32 Stemp0,Stemp1,Stemp2,Stemp3;//
    uint32 Result;

    //公式说明 计算误差公式 S=2^31(1/(1+e)-1)+S1(1/(1+e)),如果e扩大1000倍后，
    //化解公式得:  S=  2^31(-e/(1000+e))+S1(1000/(1000+e)=S1(1000/(1000+e)-2^31(e/(1000+e))
    //下面计算  2^31(e/(1000+e))
    Error=(CurValue-TarValue)*1000/TarValue;            //计算误差值。。扩大1000
    Stemp0=0x80000000/(1000+Error);                     //先保留整数部分 2^31/(1000+e)=0x80000000/(1000+e)
    Stemp0remd=0x80000000%(1000+Error);                 //保留余数
    Stemp0remd=Stemp0remd*1000/(1000+Error);            //计算小数部分，小数部分扩大1000
    Stemp1=Stemp0*Error+(Stemp0remd*Error)/1000;        //把计算的整数和小数部分都乘以ERROR，得2^31(e/(1000+e))

    //下面计算S1*(1000/(1000+e)
    Stemp2=LastSC/(1000+Error);                         //计算整数部分
    Stemp2remd=LastSC%(1000+Error);                     //计算余数部分
    Stemp2remd=Stemp2remd*1000/(1000+Error);            //小数部分
    Stemp3=Stemp2*1000+Stemp2remd;                      //整数部分加小数部分

    Result=Stemp3-Stemp1;                               //S=S1(1000/(1000+e)-2^31(e/(1000+e))
    return Result;

}
/*=========================================================================================\n
* @function_name: CalculateAC
* @function_file: EnergyBottom.c
* @描述: 计算角差
* 
* @param: CurValue 
* @param: TarValue 
* 
* @return: uint8 
* @作者: lwb (2014/3/19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 CalculateAC(int32 CurValue,int32 TarValue)
{
    //计算公式更换,雷文斌，2011年7月14日
    int16 Error;                    
    uint8 Result;

    Error=(CurValue-TarValue)*1000/TarValue;            //计算误差值。。扩大1000
    Result = (int32)3011*Error/2000;

    return Result; 
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkPW
* @function_file: EnergyBottom.c
* @描述: 校正功率和误差
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
//void EnyB_AutoChkPW(uint8 *buf)
//{
//    uint8 ucData[4];                        //单相标准功率值
//    uint32 ul_Scp;                          //原始比差数据
//    int32 l_SdPower;                        //标准功率值
//    int32 pa;
//
//    MemCpy((uint8*)ucData,buf,4);           //读取标准功率值
//    l_SdPower = Uint8_To_Uint32(ucData)/10; //获得标准功率值
//    ul_Scp = ReadMeterPara(SCP);            //读取比差值
//
//
//    pa =EnyB_CalRMS(DATAP);
//
//    gs_JbPm.ul_SCP = CalculateSC(pa, l_SdPower, ul_Scp);   //计算比差值
//    u32PMdatal = gs_JbPm.ul_SCP;
//    EnyB_SetMeterCfg(SCP);                                 //设置新比差值
//}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkIrms
* @function_file: EnergyBottom.c
* @描述:
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
//void EnyB_AutoChkIrms(uint8 *buf)
//{
//    uint8 ucData[2];
//    uint32  ul_SdCurrent;
//    uint32  ul_Irmg;
//    int32  l_IARms;
//
//
//    MemCpy((uint8*)ucData,buf,2);           //读取标准电流值
//    ul_SdCurrent=Uint8_To_Uint16(ucData);
//
//    ul_Irmg = ReadMeterPara(SCI1);  //读取比差值
//
//    l_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));
//
//    gs_JbPm.ul_SCI1 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //计算比差值
//
//    u32PMdatal = gs_JbPm.ul_SCI1;
//    EnyB_SetMeterCfg(SCI1);             //设置新比差值
//}


/*=========================================================================================\n
* @function_name: EnyB_AutoChkUrms
* @function_file: EnergyBottom.c
* @描述:
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
//void EnyB_AutoChkUrms(uint8 *buf)
//{
//    uint8 ucData[2];
//    uint32  ul_SdVoltage;
//    uint32  ul_Urmg;
//    int32  l_URms;
//
//    MemCpy((uint8*)ucData,buf,2);           //读取标准电流值
//    ul_SdVoltage=Uint8_To_Uint16(ucData);   //获得标准电压值
//    ul_Urmg = ReadMeterPara(SCU);           //读取比差值
//
//    l_URms= BCD2Hex(EnyB_CalRMS(RMSU))*10;
//
//    gs_JbPm.ul_SCU = CalculateSC(l_URms, ul_SdVoltage, ul_Urmg);   //计算比差值
//
//    u32PMdatal = gs_JbPm.ul_SCU;
//    EnyB_SetMeterCfg(SCU);                  //设置新比差值
//}
/*=========================================================================================\n
* @function_name: EnyB_AutoCheck
* @function_file: EnergyBottom.c
* @描述: 自动校表
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-08)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void EnyB_AutoCheck(uint8* buf)
{
    Word32 WdData;
    uint32 ul_Scp,ul_Irmg,ul_Urmg;                  //原始比差数据
    uint32 ul_SdPower,ul_SdCurrent,ul_SdVoltage;    //标准值
    uint32 ul_IARms,ul_URms,ul_PaRms;               //当前有效值

    MemCpy((uint8*)WdData.byte,buf,4);              //读取标准功率值
    ul_SdPower = WdData.lword/10;                   //获得标准功率值
    ul_Scp = ReadMeterPara(SCP);                    //读取比差值

    ul_PaRms =BCD2Hex(EnyB_CalRMS(DATAP));

    gs_JbPm.ul_SCP = CalculateSC(ul_PaRms, ul_SdPower, ul_Scp);   //计算比差值


    MemCpy((uint8*)WdData.byte,buf+12,2);   //读取标准电流值
    ul_SdCurrent=WdData.word[0];

    ul_Irmg = ReadMeterPara(SCI1);          //读取比差值

    ul_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));

    gs_JbPm.ul_SCI1 = CalculateSC(ul_IARms, ul_SdCurrent, ul_Irmg);   //计算比差值

    MemCpy((uint8*)WdData.byte,buf+18,2);   //读取标准电流值
    ul_SdVoltage=WdData.word[0];            //获得标准电压值
    ul_Urmg = ReadMeterPara(SCU);           //读取比差值

    ul_URms= BCD2Hex(EnyB_CalRMS(RMSU))*10;

    gs_JbPm.ul_SCU = CalculateSC(ul_URms, ul_SdVoltage, ul_Urmg);   //计算比差值


    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();                                             //跟新校表参数到计量芯片
}
/*=========================================================================================\n
* @function_name: EnyB_IBAutoCheck
* @function_file: EnergyBottom.c
* @描述: IB自动校表
* 
* @作者: lwb (2014/4/4)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void EnyB_IBAutoCheck(void)
{
                         
    uint32 ul_Scp,ul_Irmg,ul_Urmg;                  //原始比差数据
    uint32 ul_IARms,ul_URms,ul_PaRms;               //当前有效值

    ul_Scp = ReadMeterPara(SCP);                    //读取比差值

    ul_PaRms =BCD2Hex(EnyB_CalRMS(DATAP));

    gs_JbPm.ul_SCP = CalculateSC(ul_PaRms, 11000, ul_Scp);   //计算比差值
            

    ul_Irmg = ReadMeterPara(SCI1);                              //读取比差值

    ul_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));

    gs_JbPm.ul_SCI1 = CalculateSC(ul_IARms, 5000, ul_Irmg);      //计算比差值


    ul_Urmg = ReadMeterPara(SCU);                               //读取比差值

    ul_URms= BCD2Hex(EnyB_CalRMS(RMSU)); 

    gs_JbPm.ul_SCU = CalculateSC(ul_URms, 2200, ul_Urmg);       //计算比差值

    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();    
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkAngle
* @function_file: EnergyBottom.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnyB_AutoChkAngle(void)
{
                 
    int32 pa;
    PHCCtrl1=0;   //角差值写0
    //需要延时等待，故放到通信写入E2前
    DelayXms(10);
    pa=EnyB_CalRMS(DATAP);               //读取功率
    if(pa&0x800000)                 //判断方向
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

    gs_JbPm.uc_PhcCtrl1 = CalculateAC(pa, 5482);   //计算角差值
    PHCCtrl1=gs_JbPm.uc_PhcCtrl1;       //设置I1角差值
    PHCCtrl2=gs_JbPm.uc_PhcCtrl2;       //设置I2角差值
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
}
