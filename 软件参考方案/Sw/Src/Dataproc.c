 
#define AP_DATAPROC_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: CheckCRCWord
* @function_file: Dataproc.c
* @描述: 检测清零状态字是否正确
* 
* @参数: 
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-06-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 CheckCRCWord(uint8 *WrodSt)
{
    Word16 TempCrcCode;
    uint8 i;
    TempCrcCode.byte[0]=WrodSt[8];
    TempCrcCode.byte[1]=WrodSt[9];
    if(TempCrcCode.word==do_CRC(WrodSt,8))
    {
        for(i=0;i<8;i++)
        {
            if(WrodSt[i]==i)
            {
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;  
    }
} 
/*=========================================================================================\n
* @function_name: ClRCRCWord
* @function_file: Dataproc.c
* @描述: 清楚电表清零状态字
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void ClRCRCWord(uint8 *WrodSt)
{
//  uint8 i;
//  for(i=0;i<10;i++)
//  {
//      WrodSt[i]=55;
//  }
    WrodSt[8]=0;
    WrodSt[9]=0;
}
/*=========================================================================================\n
* @function_name: SetCRCWord
* @function_file: Dataproc.c
* @描述: 设置电表清零状态字
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void SetCRCWord(uint8 *WrodSt)
{
    uint8 i;
    Word16 TempCrcCode;
    for(i=0;i<8;i++)
    {
        WrodSt[i]=i;
    }
    TempCrcCode.word=do_CRC(WrodSt,8);
    WrodSt[8]=TempCrcCode.byte[0];
    WrodSt[9]=TempCrcCode.byte[1];
}
/*=========================================================================================\n
* @function_name: Data_ClearMeter
* @function_file: Dataproc.c
* @描述: 总清
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Data_ClearMeter(void)
{
    uint8 i;
    if(CheckCRCWord(guc_InitWd))
    {
        ClRCRCWord(guc_InitWd);
 
        MemSet(XDATA_RAMZONE,0x00,64);          //先清零外部RAM
        //总清
        for(i=0;i<12;i++)                                       //清历史电量和事件
        {
            CLRWDT();               //喂狗
            BE_WriteP(EEP_EPHIS_PT+64*i,XDATA_RAMZONE,64);     
        }

 
        Eny_EnergyClrCur(ENERGY_CLR);                               //清楚当前电量
        MemSet((uint8*)&gs_PowerCf,0,sizeof(S_POWERCF));            //脉冲数
        MemSet((uint8*)&gs_Energy,0,sizeof(S_ENERGY));              //脉冲能量
//        DemandClrCur();
        InitDemand();
        SleepTimeProc();                                            //从RTC读取时钟到RAM中
    }
}
/*=========================================================================================\n
* @function_name: Data_HourProc
* @function_file: Dataproc.c
* @描述: 小时处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Data_HourProc(void)
{
    //过抄表日处理
    EnergyCBRManage();
    //需量过抄表日
}
/*=========================================================================================\n
* @function_name: Data_MinProc
* @function_file: Dataproc.c
* @描述: 数据处理的分钟处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Data_MinProc(void)
{
    if(gui_DyPgmOut>0)
    {
        gui_DyPgmOut--;
        if(gui_DyPgmOut==0)
        {
            gui_SystemState &= ~flgStSys_Program;
        }
    }
    else
    {
        gui_SystemState &= ~flgStSys_Program;
    }

    if(guc_DyProDmOut>0)
    {
        guc_DyProDmOut--;
        if(guc_DyProDmOut==0)
        {
            guc_FactoryType=0;
        }
    }
    else
    {
        guc_FactoryType=0;
    }

    Eny_RefVar(); 
    getFee();       //每分钟刷新费率
//  E2ParaCheck();  //E2检测
}
/*=========================================================================================\n
* @function_name: DataProcWriteRound2
* @function_file: Dataproc.c
* @描述:
*
*
* @参数:
* @param:ucRound    0表示指针不需要移动,非零表示指针需要卷绕移动
* @param:ucPos      数据类型,卷绕表2中的位置,对应一种数据类型
* @param:pucBuf     数据缓存,其有效数据长度由卷绕表2中的数据项长度指定,建立卷绕表时确保其正确
* @返回:
* @作者:   lwb (2012-04-06)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void DataProcWriteRound2(uint8 ucRound, uint8 ucPos, uint8* pucBuf)
{
    uint8   ucPt;                       //指针
    uint16  uiAddr;                     //E2地址
    S_ROUND2 code* psR2;                     //指向卷绕表1某一个单元的指针
       
    if(ucPos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
    {
        return;
    }
    ucPt=0;
    
    psR2 = (S_ROUND2 code*)&gCs_Round2Tab +ucPos;

    BE_ReadB(psR2->uiPtAddr, (uint8*)&ucPt);    //指针


    if(ucRound != R2_NO_MOVE)
    {//需要向后移动一位
        if(ucPt == 0)
        {
            ucPt = psR2->ucMod - 1;
        }
        else
        {
            ucPt--;
        }
    }
    ucPt %= psR2->ucMod;                //得到需要查找的事件指针,实际为数据保护

    uiAddr = psR2->uiDataAddr + ucPt * psR2->ucLen;

    BE_WriteP(uiAddr, pucBuf, psR2->ucLen);
    if(ucRound != R2_NO_MOVE)
    {
        BE_WriteP(psR2->uiPtAddr, (uint8*)&ucPt,1);//写入指针数据
    }
}
/*=========================================================================================\n
* @function_name: DataProcRead2Slice
* @function_file: Dataproc.c
* @描述:
*
*
* @参数:
* @param:ucR2Pos  数据类型,卷绕表2中的位置,对应一种数据类型
* @param:ucCnt    前第几次数据  0最近一次/1上上次/...
* @param:ucOffset  在对应数据块中的偏移,单位是字节
* @param:ucLen      需要读取的数据长度
* @param:pucBuf  数据缓存,其有效数据长度由卷绕表2中的数据项长度指定,建立卷绕表时确保其正确
* @返回:
* @作者:   lwb (2012-04-06)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void DataProcRead2Slice(uint8 ucR2Pos, uint8 ucCnt, uint8 ucOffset, uint8 ucLen, uint8* pucBuf)
{
    uint8   ucPt;                       //指针
    uint16  uiAddr;                     //E2地址
    S_ROUND2 code* psR2;                     //指向卷绕表1某一个单元的指针

    if(ucR2Pos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
    {
        return;
    }
    
    ucPt=0;
    
    psR2 = (S_ROUND2 code*)&gCs_Round2Tab + ucR2Pos;
 
    BE_ReadP( psR2->uiPtAddr, (uint8*)&ucPt,1);//读取指针
 
    ucPt += ucCnt;
    ucPt %= psR2->ucMod;                //得到需要查找的事件指针,实际为数据保护

    uiAddr = psR2->uiDataAddr + ucPt * psR2->ucLen + ucOffset;

    BE_ReadP(uiAddr, pucBuf, ucLen);
}

/*=========================================================================================\n
* @function_name: Data_DayProc
* @function_file: Dataproc.c
* @描述: 天处理
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-03-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void Data_DayProc(void)
//{
//    gui_SystemState &= ~flgStSys_IsTodayJS;         //去掉已经进行过广播校时标记
//}
/*=========================================================================================\n
* @function_name: CalPowDwTm
* @function_file: Dataproc.c
* @描述: 计算掉电时间
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void CalPowDwTm(void)
//{
//    uint32 ul_SecTm;
//    uint32 ul_MinTm;
//    InitCLRWDT();               //喂狗
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);                //读取最近一次掉电记录
//    BE_ReadP(EEP_PRODUCELEFTTM,(uint8*)&gui_DyProDmOut,0x02);       //厂内剩余时间
//    BE_ReadP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);             //读取编程剩余时间
//    BE_ReadP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x04);  //读取闭锁时间
//    BE_ReadP(EEP_POWERDWTM,(uint8*)&gul_PowerTm,4);                 //停电时间
//    if(XDATA_RAMZONE[3+6]!=XDATA_RAMZONE[3])                         //判断是否过天
//    {
//        gui_SystemState &= ~flgStSys_IsTodayJS;                     //去掉已经进行过广播校时标记
//    }
//
//    ul_SecTm=CalcTimeGap((S_TIMEDATA*)(XDATA_RAMZONE+6),(S_TIMEDATA*)XDATA_RAMZONE);
//    ul_MinTm=ul_SecTm/60;
//    gul_PowerTm+=ul_MinTm;
//    if(ul_MinTm==0)                                                 //如果上下电小于分钟，判断实际走时是否过分，过分则加1；
//    {
//        if(XDATA_RAMZONE[7]!=XDATA_RAMZONE[1])
//        {
//            ul_MinTm=1;
//        }
//    }
//
//    if(ul_MinTm>=gui_DyPgmOut)                                      //编程时间
//    {
//        gui_DyPgmOut=0;
//        gui_SystemState &= ~flgStSys_Program;                       // 设置编程状态标志
//        gs_MeterState.ui_MeterState3.RunCode3Word.Program=false;
//
//    }else
//    {
//        gui_SystemState|=flgStSys_Program;
//        gs_MeterState.ui_MeterState3.RunCode3Word.Program=true;
//        gui_DyPgmOut-=ul_MinTm;
//    }
//
//    BE_WriteP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);    //写入编程剩余时间
//
//    BE_ReadP(EEP_PRODUCE,(uint8*)&guc_FactoryType,1);        //读取入厂内状态
//    if(guc_FactoryType==FactorMd)                           //读取厂内状态
//    {
//        if(ul_MinTm>=gui_DyProDmOut)                        //厂内时间
//        {
//            gui_DyProDmOut=0;
//            guc_FactoryType=0;                              // 退出厂内状态
//        }else
//        {
//            guc_FactoryType=FactorMd;
//            gui_DyProDmOut-=ul_MinTm;
//        }
//        BE_WriteP(EEP_PRODUCELEFTTM,(uint8*)&gui_DyProDmOut,0x02);  //厂内剩余时间
//        SysE2ParaSetManage(EEP_PRODUCE,(uint8*)&guc_FactoryType,1);  //写入厂内状态
//    }
//
//    if(gs_PassWordCtr.ucSt02==BSST && ul_MinTm>=gs_PassWordCtr.uiDyPW2Out)
//    {
//        gs_PassWordCtr.uiDyPW2Out=0;            //闭锁时间清零
//        gs_PassWordCtr.ucSt02=0;
//        gs_PassWordCtr.ucPW2ErrCnt=0;
//
//    }else
//    {
//        gs_PassWordCtr.uiDyPW2Out-=ul_MinTm;
//    }
//
//    if(gs_PassWordCtr.ucSt04==BSST && ul_MinTm>=gs_PassWordCtr.uiDyPW4Out)
//    {
//        gs_PassWordCtr.uiDyPW4Out=0;            //闭锁时间清零
//        gs_PassWordCtr.ucSt04=0;
//        gs_PassWordCtr.ucPW4ErrCnt=0;
//
//    }else
//    {
//        gs_PassWordCtr.uiDyPW4Out-=ul_MinTm;
//    }
//    //闭锁时间
//    BE_WriteP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x04);    //写入闭锁剩余时间
//}

/*=========================================================================================\n
* @function_name: RecoverJSRData
* @function_file: Dataproc.c
* @描述: 上电补抄表日
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-06-07)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void RecoverJSRData(void)
//{
//    uint8 CbrCnt;
//    uint8 ucDay;
//    uint8 ucHour;
//    uint8 i,j;
//    uint16 temp;
//    S_TIMEDATA LastCbrTm;
//    Word32 CurTime;
//    Word16 W16_JSR[3];
//    uint8 ucYdCnt;
//    uint8 JSRflg;
//    uint8 ucData;
//    uint8 CurJSRcnt;
//
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);    //读取最近一次掉电记录
//
//    MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);        //读取掉电时间
//
//    BE_ReadP(EEP_CBR1,W16_JSR[0].byte, 6);              //读取3个结算日
//                                                        //去除相同的抄表日
//    for(i=0;i<2;i++)
//    {
//        for(j=i+1;j<3;j++)
//        {
//            if(W16_JSR[i].word==W16_JSR[j].word)
//            {
//                W16_JSR[j].word=0x9999;
//            }else                                       //比较大小，小日期再前
//            {
//                if(W16_JSR[i].word > W16_JSR[j].word)
//                {
//                    temp=W16_JSR[i].word;
//                    W16_JSR[i].word=W16_JSR[j].word;
//                    W16_JSR[j].word=temp;
//                }
//            }
//        }
//    }
//    JSRflg=0;
//    for(i=0;i<3;i++)                          //判断有效结算日个数
//    {
//        if(W16_JSR[i].word==0x9999)
//        {
//            break;
//        }else
//        {
//            JSRflg++;
//        }
//    }
//
//    CbrCnt=0;
//    //读取结算日
//    for(i=0;i<JSRflg;i++)
//    {
//       if(W16_JSR[i].word==0x9999)
//       {
//           continue;
//       }
//
//       ucDay=W16_JSR[i].byte[1];
//       ucHour=W16_JSR[i].byte[0];
//       //判断过去几个结算日
//       CbrCnt+=CalCBRCount(&LastCbrTm.ucMinute,&gs_DateTime.ucMinute,ucDay,ucHour);
//       if(i==0)             //第一个结算日补冻次数
//       {
//           ucYdCnt = CbrCnt;
//       }
//    }
//
//    if(CbrCnt>12)
//    {
//        CbrCnt = 12;
//    }
//
//    MemCpy((uint8*)CurTime.byte,(uint8*)&gs_DateTime.ucHour,4); //拷贝当前时间
//
//    CurJSRcnt=JudgeJSR(CurTime.byte,W16_JSR[0].byte,JSRflg);       //判断需要从哪个结算日开始
//
//    for(i=0;i<CbrCnt;i++)
//    {
//      if(CurJSRcnt == 0)
//      {                                                       //下面减掉1个月
//            CurJSRcnt=JSRflg;
//            if(CurTime.byte[2]>0x01)
//            {
//                ucData=APIByteBCD2HEX(CurTime.byte[2]);
//                ucData--;
//                CurTime.byte[2] = APIByteHEX2BCD(ucData);
//            }else
//            {
//                CurTime.byte[2] = 0x12;
//                ucData = APIByteBCD2HEX(CurTime.byte[3]);
//                ucData--;
//                CurTime.byte[3] = APIByteHEX2BCD(ucData);
//            }
//        }
//
//        CurTime.byte[0] = W16_JSR[CurJSRcnt-1].byte[0];
//        CurTime.byte[1] = W16_JSR[CurJSRcnt-1].byte[1];
//        MemCpy(XDATA_RAMZONE+i*4,CurTime.byte,4);         //存结算日时间
//        CurJSRcnt--;
//    }
//
//
//    //转存多少次过结算日数据
//    while(CbrCnt)
//    {
//        CbrCnt--;
//        WriteHisEP();
//        DataProcWriteRound2(R2_MOVE,JSSJJLID,XDATA_RAMZONE+CbrCnt*4);   //写入数据，倒序
//    }
//
//    if(ucYdCnt>2)
//    {
//        ucYdCnt=2;
//    }
//
//    while(ucYdCnt)
//    {
//        ucYdCnt--;
//        MonthLYDL(0);
//    }
//}
/*=========================================================================================\n
* @function_name: RecoverDayDjData
* @function_file: Dataproc.c
* @描述: 上电补日冻结
* 
* @参数: 
* @返回: 
* @作者:   lm (2012-12-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void RecoverDayDjData(void)
//{
//    uint8 CbrCnt;
//    uint8 ucMin;
//    uint8 ucHour;
//    S_TIMEDATA LastCbrTm;
//    S_CURTIME CurTime;
//    Word16 RdjTm;
//    int16 Eadd;
//    Word32 data1;
//    uint8 i;
//
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);                //读取最近一次掉电记录
//
//    MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);            //读取掉电时间
//
//    BE_ReadP(EEP_RFREEZTM,RdjTm.byte,2);                    //读取日冻结时间
//
//    ucHour=RdjTm.byte[1];
//    ucMin=RdjTm.byte[0];
//    CurTime.ucDay=gs_DateTime.ucDay;
//    CurTime.ucMonth=gs_DateTime.ucMonth;
//    CurTime.ucYear=gs_DateTime.ucYear;
//
//           //判断过去几次日冻结
//    CbrCnt=CalRDJCount(&LastCbrTm.ucMinute,&gs_DateTime.ucMinute,ucHour,ucMin);
//    CalDayBack(&CurTime,JudgeCurTime(&gs_DateTime.ucMinute,RdjTm.byte));
//
//    for(uint8 i=0;i<CbrCnt;i++)
//    {
//        WriLastDJTime(&CurTime,RdjTm.byte,XDATA_RAMZONE1+i*5);
//        CalDayBack(&CurTime,1);
//    }
//
//    for(i = 0; i <= 4; i++)
//    {
//        Eadd = Eny_GetEp1(1, i);                            //取得某个费率的电量增量
//        data1.lword= gs_EnergyA.ulP[i]+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+5+i*4,(void*)data1.byte,4);    //正向 总尖峰平谷电量
//    }
//
//    for(i = 0; i <= 4; i++)
//    {
//        Eadd = Eny_GetEp1(2, i);                            //取得某个费率的电量增量
//        data1.lword= gs_EnergyA.ulN[i]+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+25+i*4,(void*)data1.byte,4);   //反向 总尖峰平谷电量
//    }
//
//    MemSet(XDATA_RAMZONE+45,0,4);                           //功率
//
//    //转存多少次过日冻结数据
//    while(CbrCnt)
//    {
//        CbrCnt--;
//        DataProcEvCountAdd(RDJNUMID);                       //增加日冻结次数
////      StructFreezeDate();
//        MemCpy(XDATA_RAMZONE,(XDATA_RAMZONE1+CbrCnt*5),5);
//        DataProcWriteRound2(R2_MOVE,RDJID,XDATA_RAMZONE);   //写入数据
//    }
//}
/*=========================================================================================\n
* @function_name: RecoverEnegyData
* @function_file: Dataproc.c
* @描述: 
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-09-27)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void RecoverEnegyData(void)
{
    uint16 CRC;
    BE_ReadP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,9);
    CRC=Uint8_To_Uint16(XDATA_RAMZONE+7);
    if(CRC==do_CRC(XDATA_RAMZONE, 7))                          //掉电保存数据正确
    {
        MemCpy((uint8*)&gs_EnergyData.uiEP,XDATA_RAMZONE,4);    //恢复电量增量

        MemCpy((uint8*)&gs_FeeData.uc_FeeNo,XDATA_RAMZONE+6, 1);//当前费率
 
        Eny_EnergyActiveSave();                                 //保存电量

        MemCpy((uint8*)&gs_PowerCf.uc_P,XDATA_RAMZONE+4,1);     //当前CF数
        MemCpy((uint8*)&gs_Energy.ucP, XDATA_RAMZONE+5, 1);     //当前CF对于的能量

        CRC=0;
        BE_WriteP(EEP_POWDWENERGY+7,(uint8*)&CRC,2);           //使掉电数据无效
    }
    else
    {
        MemSet((uint8*)&gs_PowerCf.uc_P,0,1);                   //当前CF数
        MemSet((uint8*)&gs_Energy.ucP, 0, 1);                   //当前CF对于的能量
    }

//  Eny_EnergyActiveSave();                                 //保存电量

    gui_SystemState &= ~flgStSys_PowOff;
}
/*=========================================================================================\n
* @function_name: JudgeCurTime
* @function_file: Dataproc.c
* @描述: 判断当前时间有无过日冻结时间。若没过冻结时间，返回true。
* 
* 
* @参数: 
* @param:CurTime  
* @param:RdjTime  
* 
* @返回: 
* @return: uint8 
* @作者:   xuqf (2013-3-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//uint8 JudgeCurTime(uint8* CurTime,uint8* RdjTime)
//{
//    if(*(CurTime+1) < *(RdjTime+1))             //判断时，如果当前hour小于日冻结hour
//    {
//        return true;
//    }else
//    {
//        if(*(CurTime+1) == *(RdjTime+1))        //若hour相等
//        {
//            if(*CurTime < *RdjTime)             //判断Minute
//            {
//                return true;
//            }
//        }
//        return 0;
//    }
//}
/*=========================================================================================\n
* @function_name: CalLastDJTime
* @function_file: Dataproc.c
* @描述: 写入日期
* 
* 
* @参数: 
* @param:CurTime  
* @param:time  
* @param:pucBuf  
* @返回: 
* @作者:   xuqf (2013-3-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void WriLastDJTime(S_CURTIME *CurTime,uint8* time,uint8* pucBuf)
//{
//    CurTime->ucMinute = *time;                    //日冻结的分
//    CurTime->ucHour = *(time+1);                  //日冻结的时
//    MemCpy(pucBuf,&CurTime->ucMinute,5);
//}
/*=========================================================================================\n
* @function_name: CalDayBack
* @function_file: Dataproc.c
* @描述: 日前减一天判断，包括过年，过月
* 
* 
* @参数: 
* @param:CurTime  
* @param:offset  
* @返回: 
* @作者:   xuqf (2013-3-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void CalDayBack(S_CURTIME *CurTime,uint8 offset)
//{
//    uint8 ucData;
//    if(offset)                                //如果标记有效，需要减1天
//    {
//        if(CurTime->ucDay>0x01)                  //判断day是不是大于1日。如果是，减1天
//        {
//            ucData=APIByteBCD2HEX(CurTime->ucDay);
//            ucData--;                                                            //增加1分
//            CurTime->ucDay = APIByteHEX2BCD(ucData);
//        }else                                 //如果不是
//        {
//            if(CurTime->ucMonth > 0x01)          //判断月份是不是1月。如果不是
//            {
//                ucData=APIByteBCD2HEX(CurTime->ucMonth);
//                ucData--;                                                            //增加1分
//                CurTime->ucMonth = APIByteHEX2BCD(ucData);
//
//                if(((APIByteBCD2HEX(CurTime->ucYear) & 0x03) == 0)&& CurTime->ucMonth == 0x02)
//                {//判断当前月是不是润年的2月份
//                    CurTime->ucDay = MonthDays[CurTime->ucMonth] + 1; //闰年加1天
//                }else
//                {
//                    CurTime->ucDay = MonthDays[CurTime->ucMonth];
//                }
//                CurTime->ucDay=APIByteHEX2BCD(CurTime->ucDay);
//            }else                             //如果是1月，即1月1日，
//            {
//
//                ucData=APIByteBCD2HEX(CurTime->ucYear);
//                ucData--;                                                            //增加1分
//                CurTime->ucYear = APIByteHEX2BCD(ucData);
//                CurTime->ucMonth = 0x12;
//                CurTime->ucDay = 0x31;
//            }
//        }
//    }
//}
/*=========================================================================================\n
* @function_name: JudgeJSR
* @function_file: Dataproc.c
* @描述: 判断当前时间与结算日比较
* 
* 
* @参数: 
* @param:CurTime  
* @param:JSRTime  
* @param:flg  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-03-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//uint8 JudgeJSR(uint8* CurTime,uint8* JSRTime,uint8 flg)
//{
//    uint8 i;
//    for(i=0;i<flg;i++)
//    {
//        if(*(CurTime+1) < *(JSRTime+1+i*2))         //判断日
//        {
//            return i;
//        }else
//        {
//            if(*(CurTime+1) == *(JSRTime+1+i*2))    //若Day相等
//            {
//                if(*CurTime < *(JSRTime+i*2))       //判断Hour
//                {
//                    return i;                       //
//                }
//            }
//        }
//    }
//
//    return flg;
//}
