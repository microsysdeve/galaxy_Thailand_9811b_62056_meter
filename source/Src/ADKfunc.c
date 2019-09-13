#define ADK_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: ADK_CalFun
* @function_file: DLT_645_2007.c
* @描述: 阿迪克校表与初始化
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @返回: 
* @作者:   lm (2013-07-31)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
#ifdef _DEL 
uint8 ADK_CalFun(S_FRAMEINFO *s_FrmInfo)
{
    //厂内，电量<1kwh
    if(s_FrmInfo->ucCmd != 0x11 || (guc_FactoryType!=FactorMd) || ((*(gs_EnergyA.lCP)+ Eny_GetEp1(0,0))>1000))
    {
        s_FrmInfo->ucErr.word = ComErrBit_Other;
        s_FrmInfo->ucLen = 1;
    }
    else if(guc_ADKcal == ADK_Init)
    {
        Word16 CRC;
        CLRWDT();               //喂狗
        FCpyTMem(XDATA_RAMZONE,InitPara0,sizeof(S_JBPM)-2);                     //拷贝Flash数据到RAM中
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //拷贝CRC到RAM中
        SysE2ParaSetManage(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));//写入到E2中 
//        BE_WriteP(EEP_JBTOTAL, (uint8*)&gs_JbPm, sizeof(S_JBPM));
//        BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN, (uint8*)&gs_JbPm, sizeof(S_JBPM));
        Eny_JbPm_GetE2();                                     //跟新校表参数到计量芯片
        s_FrmInfo->ucReply = 0;
    }
    else if(guc_ADKcal == ADK_Cal)
    {
        s_FrmInfo->ucReply = 0;
        if(s_FrmInfo->ucbuf[1]==0x11)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_11;
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else if(s_FrmInfo->ucbuf[1]==0x15)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_15;
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else if(s_FrmInfo->ucbuf[1]==0x31)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_31;                        
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else
        {
            s_FrmInfo->ucReply = 1;
            s_FrmInfo->ucErr.word = ComErrBit_Other;
            s_FrmInfo->ucLen = 1;
        }
    }             
    return Ret_OK;
}

/*=========================================================================================\n
* @function_name: ParaInit
* @function_file: DLT_645_2007.c
* @描述: 参数初始化
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @返回: 
* @作者:   lm (2013-08-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 ParaInit(S_FRAMEINFO *s_FrmInfo)
{
    MemCpy(s_FrmInfo->uiID.byte,s_FrmInfo->ucbuf,4);   //数据标识
    
    if(s_FrmInfo->uiID.lword != 0x80541413)
 //      || !(gui_SystemState & flgStSys_Program))
    {
        s_FrmInfo->ucErr.word = ComErrBit_Other;
        s_FrmInfo->ucLen = 1;
        return Ret_OK;
    }  
    
    SetCRCWord(guc_InitWd);
 //   guc_RTCSave = 0xAA;
 //   guc_RTCSave = 0x55;
    gui_RefreshEvent|=flgEtPara_Init;
    s_FrmInfo->ucLen = 0;
    
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: ADK_ReadVar
* @function_file: DLT_645_2007.c
* @描述: 参数初始化
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @返回: 
* @作者:   lm (2013-08-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/

uint8 ADK_ReadVar(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    int16 Eadd;
    uint32 *pEnyData;
    int32  data1; 
    uint32 ulVarValue;
    uint16 uiCosVal;
    
    pEnyData=(uint32*)gs_EnergyA.lCP;                    //获取电量数据结构首地址
    data1=*(pEnyData);
    Eadd = Eny_GetEp1(0,0);
    data1 += Eadd;                                                     //有功总能量
   /* if(data1>0x80000000)
    {
        guc_ShowEnergyFlag=0x55;
        data1=-data1;
        flag=1;
    }*/
    data1/=10;
    if(data1 > 80000000)
    {
        data1 = data1 % 80000000;
    }
    data1= Hex2BCD(data1);                              //转换为BCD码
   /* if(flag)
    {
        data1|=0x80000000;
    }*/
    data1 &=~0x80000000;
    MemCpy(s_FrmInfo->ucbuf,(uint8*)&data1,4);      //有功

    MemSet(s_FrmInfo->ucbuf+4,0x00,4);     //无功

    ulVarValue=CalRMS(RMSU);        
    MemCpy(s_FrmInfo->ucbuf+8,(uint8*)&ulVarValue,2);   //电压

    if(SETA == gs_Channel.ucSta)
    {
        ulVarValue=CalRMS(RMSI1);       
        MemCpy(s_FrmInfo->ucbuf+10,(uint8*)&ulVarValue,3);    //电流
        ulVarValue=CalRMS(DATAP);       
        MemCpy(s_FrmInfo->ucbuf+13,(uint8*)&ulVarValue,3);   //A有功功率
    }else if(SETB == gs_Channel.ucSta)
    {
        ulVarValue=CalRMS(RMSI2);       
        MemCpy(s_FrmInfo->ucbuf+10,(uint8*)&ulVarValue,3);    //零线电流
        ulVarValue=CalRMS(DATAQ);       
        MemCpy(s_FrmInfo->ucbuf+13,(uint8*)&ulVarValue,3);   //B有功功率
    }
    MemSet(s_FrmInfo->ucbuf+16,0x00,3);   //无功功率      
    uiCosVal=CalCos();                                      
    MemCpy(s_FrmInfo->ucbuf+19,(uint8*)&uiCosVal,2);      //功率因数
     
    s_FrmInfo->ucLen = 21;
    return Ret_OK;
}

/*=========================================================================================\n
* @function_name: ADK_ReadVar
* @function_file: DLT_645_2007.c
* @描述: 参数初始化
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @返回: 
* @作者:   lm (2013-08-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 ADK_Backup(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    Eny_EnergyClrCur(ENERGY_CLR);                               //清楚当前电量
    MemSet((uint8*)&gs_PowerCf,0,sizeof(S_POWERCF));            //脉冲数
    MemSet((uint8*)&gs_Energy,0,sizeof(S_ENERGY));              //脉冲能量
    
    uint32 tmp;
    tmp = Uint8_To_Uint32(s_FrmInfo->ucbuf+12);
    gs_EnergyA.lCP[0] = gs_EnergyA.ulP = BCD2Hex(tmp)*10;  
    gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
    BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA,sizeof(ENERGYACTIVE));
    BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));

    s_FrmInfo->ucLen = 0;

    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: ADK_ReadFlash
* @function_file: ADKfunc.c
* @描述: 阿迪克部分只读命令支持
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @返回: 
* @作者:   lm (2013-08-09)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 ADK_ReadFlash(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    if(s_FrmInfo->uiID.lword == 0x04000404)       //额定电压
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+27, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000405)      //额定电流
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+33, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000406)      //最大电流
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+39, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000409)      //电表有功常数
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+45, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000501)      //电表运行状态字阿迪克改
    {
        gt_RunCode.ucSta = 0x42;   //默认配置，主回路，正向，区间需量
        if(gs_Channel.ucSta == SETB)
        {
            gt_RunCode.sSta.bChannel = 0;
        }
        if(gs_SysRunSt.Pdir)
        {
            gt_RunCode.sSta.bPdir = true;
        }
        s_FrmInfo->ucbuf[0] = gt_RunCode.ucSta;
    }
    else if(s_FrmInfo->uiID.lword == 0x04800001)      //厂家软件版本号
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitFwVer, CTable->ucLen);
    }
    else if(s_FrmInfo->uiID.lword == 0x04800002)      //厂家硬件版本号
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitHwVer, CTable->ucLen);
    }
    else
    {
        s_FrmInfo->ucErr.word = ComErrBit_Nodata;
        s_FrmInfo->ucLen = 1;
        return Ret_OK;
    }
    s_FrmInfo->ucLen = CTable->ucLen;
    return Ret_OK;
}
#endif
//以下校表部分
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
* @作者:   lwb (2012-06-18)
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
void ADK_AutoChkPW(uint8 ucSta)
{
    uint8 ucData[4];                        //单相标准功率值
    uint32 ul_Scp;                          //原始比差数据
    int32 l_SdPower;                        //标准功率值
    //int32  err;
    //int32  errPgain;
    int32 pa;
    uint16 tmpGa, tmpPW;
    
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //读取标准功率值  
    
    if(ucSta == SETA)
    {
        tmpGa = SCP;
        tmpPW = DATAP;
    }
    else
    {
        tmpGa = SCQ;
        tmpPW = DATAQ;
    }   
    ul_Scp = EnyB_ReadMeterParaACK(tmpGa);      //读取比差值
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);//BCD2Hex(Uint8_To_Uint32(ucData))/100;   //获得标准功率值

    pa=CalRMS(tmpPW);               //读取功率
    if(pa&0x800000)                 //判断方向
    {
        pa&=~0x800000;               
    } 

    pa =BCD2Hex(pa);
    
    if(ucSta == SETA)
    {
        gs_JbPm.ul_SCP = CalculateSC(pa, l_SdPower, ul_Scp);   //计算比差值
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);             //设置新比差值
    }
    else
    {
        gs_JbPm.ul_SCQ = CalculateSC(pa, l_SdPower, ul_Scp);   //计算比差值
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCQ, SCQ);             //设置新比差值
    }
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkTinyPW
* @function_file: EnergyBottom.c
* @描述: 校正功率二次补偿和误差
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-08)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ADK_AutoChkTinyPW(uint8 ucSta)
{
    uint8 ucData[4];                        //单相标准功率值
    uint8 i;
    int32 l_SdPower;                        //标准功率值   
    Word32 TempValue;
    uint32 TempSum;
    uint32 pa_sum,TempPara;
    uint16 tmpPw;
    
    pa_sum = 0;
    TempSum = 0;
 
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //读取标准功率值 
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>4);   //获得标准功率值
    
    if(ucSta == SETA)
    {
        tmpPw = DATAIP;
        TempPara = gs_JbPm.ul_PG/256;        //读取比例系数
    }
    else
    {
        tmpPw = DATAIQ;
        TempPara = gs_JbPm.ul_QG/256;        
    }
    for(i=0; i<16; i++)
    {
        TempValue.lword=EnyB_ReadMeterParaACK(tmpPw); 
        DelayXms(20);
        CLRWDT();                           //喂狗
        if(TempValue.byte[3]>0x7f)          //如果是负数的数，先变成正数
        {
            TempValue.lword=~TempValue.lword+1;
        }
        TempSum += TempValue.lword;
    }   
    
    TempSum = TempSum>>4;              //读取功率寄存器值
    
    pa_sum = (TempSum*2560)/TempPara;  //换算值
      
    //TempValue.lword = l_SdPower*TempPara/2560;    //理论寄存器值
    
    if(l_SdPower > pa_sum)
      TempSum = (TempValue.lword*(l_SdPower-pa_sum)/l_SdPower);    //计算二次补偿值
    else
      TempSum = -(TempValue.lword*(pa_sum-l_SdPower)/l_SdPower);   //计算二次补偿值
    
    if(ucSta == SETA)
    {
        gs_JbPm.ul_PARAPC = TempSum;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_PARAPC, PARAPC);                          //设置新比差值 
    }
    else
    {
        gs_JbPm.ul_PARAQC = TempSum;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_PARAQC, PARAQC);                          //设置新比差值
    }
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));  
    EnyB_JbPm_Updata(); 
}
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
void ADK_AutoChkIrms(uint8 ucSta)
{
    uint8 ucData[3];
    uint32  ul_SdCurrent;
    uint32  ul_Irmg;
    int32  l_IARms;
    uint16 tmpGa,tmpRMS;
    
    BE_ReadP(EEP_AUTOCAL+5,ucData,3);      //读取标准电流值
    ul_SdCurrent=BCD2Hex(Uint8_To_Uint24(ucData));    //获得标准电流值
    
    if(ucSta == SETA)
    {
        tmpGa = SCI1;
        tmpRMS = RMSI1;
    }
    else
    {
        tmpGa = SCI2;
        tmpRMS = RMSI2;
    }
    ul_Irmg = EnyB_ReadMeterParaACK(tmpGa);                    //读取比差值

    l_IARms= BCD2Hex(CalRMS(tmpRMS)&0x7FFFFF);
        
    if(ucSta == SETA)
    {
        gs_JbPm.ul_SCI1 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //计算比差值
        gs_JbPm.ul_SCI1_800 = gs_JbPm.ul_SCI1;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1, SCI1);
    }
    else
    {
        gs_JbPm.ul_SCI2 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //计算比差值
        gs_JbPm.ul_SCI2_800 = gs_JbPm.ul_SCI2;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2, SCI2);
    } 
}
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
void ADK_AutoChkUrms(void)
{
    uint8 ucData[3];
    uint32  ul_SdVoltage;
    uint32  ul_Urmg;
    int32  l_URms;

    BE_ReadP(EEP_AUTOCAL+1,ucData,3);      //读取标准电压值
    ul_SdVoltage=BCD2Hex(Uint8_To_Uint24(ucData))/10;    //获得标准电压值
    ul_Urmg = EnyB_ReadMeterParaACK(SCU);                    //读取比差值

    l_URms= BCD2Hex(CalRMS(RMSU))*10;//gs_EnyInsData.ul_URms;

    gs_JbPm.ul_SCU = CalculateSC(l_URms, ul_SdVoltage, ul_Urmg);   //计算比差值

    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCU, SCU);                                 //设置新比差值
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkAngle
* @function_file: EnergyBottom.c
* @描述: 角差校正
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ADK_AutoChkAngle(uint8 ucSta)
{
    uint8 ucData[4];                        //单相标准功率值
    uint32 l_SdPower;                        //标准功率值
    uint32 pa;
    uint16 tmpGa,tmpPw;
    
    if(ucSta == SETA)
    {
        tmpGa = PHCCtrl1;
        tmpPw = DATAP;
    }
    else
    {
        tmpGa = PHCCtrl2;
        tmpPw = DATAQ;
    }
    EnyB_SetMeterCfgACK(0, tmpGa);       //角差值写0
    //需要延时等待，故放到通信写入E2前
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //读取标准功率值  
   
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);///10;   //获得标准功率值

    pa=CalRMS(tmpPw);               //读取功率
    if(pa&0x800000)                 //判断方向
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

 //   l_SdPower=3000;
    if(ucSta == SETA)
    {
        gs_JbPm.uc_PhcCtrl1 = CalculateAC(pa, l_SdPower);   //计算角差值
        EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1, PHCCtrl1);  //设置角差值 
    }
    else
    {       
        gs_JbPm.uc_PhcCtrl2 = CalculateAC(pa, l_SdPower);   //计算角差值
        EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2, PHCCtrl2);  //设置角差值    
    }         
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();                                       //跟新校表参数到计量芯片
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChknAngle
* @function_file: EnergyBottom.c
* @描述: 零线角差校正
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ADK_AutoChknAngle(void)
{
    uint8 ucData[4];                        //单相标准功率值
    uint32 l_SdPower;                        //标准功率值
    uint32 pa;
    
    EnyB_SetMeterCfgACK(0, PHCCtrl2);       //角差值写0
    //需要延时等待，故放到通信写入E2前
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //读取标准功率值  
   
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);///10;   //获得标准功率值
//  pa = EnyB_ReadMeterParaACK(DATAP);        //读取功率值做方向判断
//
//  if(pa>0)           //首先把表计读取的功率值转存正值
//  {
//     pa= -BCD2Hex(CalRMS(DATAP));//gs_EnyInsData.l_PowerPA;
//  }else
//  {
//     pa= BCD2Hex(CalRMS(DATAP));//-gs_EnyInsData.l_PowerPA;
//  }
    pa=CalRMS(DATAQ);               //读取功率
    if(pa&0x800000)                 //判断方向
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

    l_SdPower=3000;
    gs_JbPm.uc_PhcCtrl2 = CalculateAC(pa, l_SdPower);   //计算角差值
 
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2, PHCCtrl2);  //设置角差值
    
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //计算CRC校验值

    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));

    EnyB_JbPm_Updata();                                       //跟新校表参数到计量芯片
}
