#define AP_ENERGYEXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: Eny_JbPm_GetE2
* @function_file: EnergyBottom.c
* @描述: 获取E2中的数据，同时进行相关的处理
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_JbPm_GetE2(void)
{
    uint8 ucjb[sizeof(S_JBPM)];

    BE_ReadP(EEP_JBTOTAL,ucjb,sizeof(S_JBPM));


    if(Uint8_To_Uint16(ucjb+sizeof(S_JBPM)-2)==do_CRC(ucjb,sizeof(S_JBPM)-2))
    {
        Eny_JbPm_UpdateRam(ucjb);
        EnyB_JbPm_Updata();
    }
    else
    {
    #if (_SW_SE_Type > 0)
        SE_ReadP(EEP_JBTOTAL,ucjb,sizeof(S_JBPM));
    #else
        BE_ReadP(EEP_JBTOTAL+EEP_BAK_LEN,ucjb,sizeof(S_JBPM));
    #endif
        if(Uint8_To_Uint16(ucjb+sizeof(S_JBPM)-2)==do_CRC(ucjb,sizeof(S_JBPM)-2))
        {
            Eny_JbPm_UpdateRam(ucjb);
            EnyB_JbPm_Updata();
        }
        else
        {
            if(gs_JbPm.ui_JbCRC == do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2))  //RAM中的数据是否完整
            {                                           //因为以下参数要求定义在两个结构体里面
                EnyB_JbPm_Updata();
            }
            else
            {
                EnyB_JbPm_Init();
                EnyB_JbPm_Updata();
            }
        }
    }
}


/*=========================================================================================\n
* @function_name: Eny_JbPm_UpdateRam
* @function_file: EnergyBottom.c
* @描述: 校表参数的更新，从E2中更新
*
*
* @参数:
* @param:pjb
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_JbPm_UpdateRam(uint8 *pjb)
{                                                       //
    uint8 i;                                            //
    uint8 *p;                                           //
    p = (uint8 *)&gs_JbPm;                              //
    for(i=0;i<sizeof(S_JBPM);i++)                       //
    {                                                   //
        *p = * pjb;                                     //
        p++;                                            //
        pjb++;                                          //
    }                                                   //
}
/*=========================================================================================\n
* @function_name: Eny_RefVar
* @function_file: EnergyBottom.c
* @描述: 从E2中读出校表参数，同时进行完整性校验，如果正确，则进行刷新，不正确则用初始化数据
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_RefVar(void)
{
    uint16 uitmp;
    BE_ReadW(EEP_JBTOTAL+sizeof(S_JBPM)-2, &uitmp);                             //读E2中的CRC校验值

    if(uitmp == gs_JbPm.ui_JbCRC)                                               //判断他们E2中的数据是否与RAM中的相等
    {                                                                           //RAM中的数据与E2中的是一样的
        if(gs_JbPm.ui_JbCRC == do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2))      //RAM中的数据是否完整
        {                                                                       //因为以下参数要求定义在两个结构体里面
            EnyB_JbPm_Updata();
        }
        else
        {
            Eny_JbPm_GetE2();                                                  // RAM中的数据要不通不过CRC校验，要不与E2中CRC对不起来
        }
    }
    else
    {
        Eny_JbPm_GetE2();                                                      //RAM中的数据要不通不过CRC校验，要不与E2中CRC对不起来
    }
    Eny_JbPm_MeterConst();                                                     //表常数及其的更新
}
/*=========================================================================================\n
* @function_name: Eny_RefCalcType
* @function_file: Energy.c
* @描述: 刷新计量方式字
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_RefCalcType(void)
{
    guc_EPCalcType=0x55;                            //默认正加反
    //BE_ReadB(EEP_YGCALC,&guc_EPCalcType);               //刷新计量方式字
}
/*=========================================================================================\n
* @function_name: Eny_JbPm_MeterConst
* @function_file: EnergyBottom.c
* @描述: 脉冲常数
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_JbPm_MeterConst(void)
{
    uint8 i;
    for(i=0;i<MeterConstLen;i++)                                // 根据脉冲才常数实现走字控制
    {                                                           // 根据表常数，确定CF脉冲分频系数和单位能量大小
        if(gs_MeterConstT[i].ui_MC==gs_JbPm.ui_MeterC)
        {                                                       // 根据脉冲常数来确定CF分频系数和单位能量大小
            guc_GateCF = gs_MeterConstT[i].uc_CFGate;           // 出的脉冲个数
            guc_UnitCF = gs_MeterConstT[i].uc_CFUinit;          // 单位大小
            break;
        }
    }

    if(i>=MeterConstLen)                                        // 查找表格中，发现没有对应的常数的处理
    {                                                           // 如果表格中没有对应项，则设置状态，报警
        guc_GateCF = 10;                                        // 用一个比较大的数据，容易看出
        guc_UnitCF = 1;
    }
}

/*=========================================================================================\n
* @function_name: Eny_EnergyClrCur
* @function_file: Energy.c
* @描述: 清除当前正向有功电量
*        清除RAM中的数据，就是结构体中的数据，最大是2kWh
*        清除E2中的数据，是当前正向有功总电量数据
* @参数:
* @param:ucType
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_EnergyClrCur(uint8 ucType)
{
    if(ucType & ENERGY_CLR_RAM)
    {
        MemSet((uint8*)&gs_EnergyData, 0, sizeof(ENERGYDATA)-2);
        gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);
        MemCpy((uint8*)&gs_EnergyData_bak, (uint8*)&gs_EnergyData, sizeof(ENERGYDATA));
    }

    if(ucType & ENERGY_CLR_E2)
    {
        MemSet((void*)&gs_EnergyA, 0, sizeof(ENERGYACTIVE));
        gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE)- 2);
        BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));

    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #else
        BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #endif

    }
}

/*=========================================================================================\n
* @function_name: Eny_PurCheckRAMEny
* @function_file: Energy.c
* @描述: 上电检测RAM电量是否正确
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-02)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_PurCheckRAMEny(void)
{
    ENERGYACTIVE sEA;
    if(ENERGY_ERR_RAM==Eny_CheckEnergyActiveRAM())
    {                                                                       //RAM电量不正确
        BE_ReadP(EEP_EPS,(uint8*)&sEA,sizeof(ENERGYACTIVE));                //读取E2中的电量
        if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE)- 2) != sEA.uiCRC)      //检查E2中电量CRC是否正确
        {                                                                   //主E2电量不正确
        #if (_SW_SE_Type > 0)
            SE_ReadP(EEP_EPS+EEP_BAK_LEN,(uint8*)&sEA,sizeof(ENERGYACTIVE));
        #else
            BE_ReadP(EEP_EPS+EEP_BAK_LEN,(uint8*)&sEA,sizeof(ENERGYACTIVE)); //读取E2中的电量
        #endif
            if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE) - 2) == sEA.uiCRC)
            {                                                               //备份E2电量正确
                MemCpy((uint8*)&gs_EnergyA, (uint8*)&sEA, sizeof(ENERGYACTIVE));            //拷贝E2备份电量到RAM中
            }else
            {                                                               //备份E2电量不正确
                Eny_EnergyClrCur(ENERGY_CLR_E2);                                //清零RAM电量和E2中电量
            }
        }
        else
        {
            MemCpy((uint8*)&gs_EnergyA, (uint8*)&sEA, sizeof(ENERGYACTIVE));                //拷贝主E2电量到RAM中
        }
    }
}

/*=========================================================================================\n
* @function_name: Eny_CheckEnergy
* @function_file: Energy.c
* @描述: 检查结构体中的增量是否正确
*       电量增量crc校验出错次数标记,0必定主校验正确,1主校验错而备份对,2都错
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_CheckEnergy(void)
{
    uint8   ucErr = 0;
    uint16  uiCRC;

    uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);          // 电量增量CRC校验
    if (uiCRC != gs_EnergyData.uiCRC)
    {
        ucErr++;
        uiCRC = do_CRC((uint8 *)&gs_EnergyData_bak, sizeof(ENERGYDATA)-2);  // 备份电量增量CRC校验
        if (uiCRC != gs_EnergyData_bak.uiCRC)
        {
            ucErr++;
        }
    }

    if (ucErr & 1)
    {                                                                       // 第一块出错
        MemCpy((uint8*)&gs_EnergyData, (uint8*)&gs_EnergyData_bak, sizeof(ENERGYDATA));     // 更新数据
    }
    else if(ucErr >= 2)                                                     // 主区域和备份区域都出错
    {                                                                       // 都出错
        Eny_EnergyClrCur(ENERGY_CLR_RAM);                                       // 清零
    }
}

/*=========================================================================================\n
* @function_name: Eny_CheckEnergyActiveRAM
* @function_file: Energy.c
* @描述: 检查RAM电量是否正确
*
* @参数:
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 Eny_CheckEnergyActiveRAM(void)
{
    //验证数据CRC校验
    if(do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE)- 2) != gs_EnergyA.uiCRC)
    {
        return ENERGY_ERR_RAM;
    }

    return ENERGY_ERR_NONE;
}

/*=========================================================================================\n
* @function_name: Eny_GetEp1
* @function_file: Energy.c
* @描述: 计算当前正、反有功总电能增量（分费率)
*
*
* @参数:
* @param:index  0-组合（计量状态字决定）1-原正, , 2-反
* @param:fee   计费的费率
*
* @返回:
* @return: int16
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
int16 Eny_GetEp1(uint8 index, uint8 fee)
{
    int16 iRet=0;
#ifdef MultariffMeter
    if((fee != 0) && ((fee - 1) != gs_FeeData.uc_FeeNo))    //如果传入的费率参数不等于当前费率或者不等于总电量的话返回0
    {
        return 0;
    }
#endif

    Eny_CheckEnergy();                                      //检查电量增量有效性，是否通的过CRC校验

    if(index==0)
    {                                                       //下面是正向有功按照计量方式字来处理
        iRet = gs_EnergyData.uiEP;
//      iRet += gs_EnergyData.uiEN;
    }
//  else if(index==1)
//  {
//      iRet = gs_EnergyData.uiEP;                          //返回正向电量增量
//  }else if(index==2)
//  {
//      iRet =gs_EnergyData.uiEN;                           //返回反向电流增量
//
//  }
    return iRet;
}

/*=========================================================================================\n
* @function_name: Eny_EnergyActiveSave
* @function_file: Energy.c
* @描述: 当前电量写入E2中
*           这里还存在一个问题,就是数据分费率和与总电量不相等的话,将不再写数据到E2中
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_EnergyActiveSave(void)
{
    uint8 ucFlg = 0;
    int16 iDelta;
    ENERGYACTIVE sEA;
    //先验证E2数据CRC是否正确,如果有一个正确,则认为这部分内容有效
    BE_ReadP(EEP_EPS,(uint8*)&sEA,sizeof(ENERGYACTIVE));

    if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE)- 2) != sEA.uiCRC)
    {
    #if (_SW_SE_Type > 0)
        SE_ReadP(EEP_EPS, (uint8*)&sEA, sizeof(ENERGYACTIVE));
    #else
        BE_ReadP(EEP_EPS+EEP_BAK_LEN, (uint8*)&sEA, sizeof(ENERGYACTIVE));
    #endif

        if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE) - 2) == sEA.uiCRC)
        {
            ucFlg = 1;
        }
    }
    else
    {
        ucFlg = 1;
    }

    //如果E2数据CRC有效,则用E2数据覆盖RAM数据,当E2数据CRC不正确时,RAM数据CRC正确,那么相信RAM数据
    //如果都不正确,都将会用主E2的数据覆盖RAM数据
    if(ucFlg == 0)
    {
        if(do_CRC ((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2) != gs_EnergyA.uiCRC)
        {
            ucFlg = 1;
            return;
        }
    }

    if(ucFlg == 1)
    {
        MemCpy((void*)&gs_EnergyA, (void*)&sEA, sizeof(ENERGYACTIVE));
    }


//  //正向有功
//  iDelta = Eny_GetEp1(1, 0);
//  gs_EnergyA.ulP[0] += iDelta;
//  #ifdef MultariffMeter
//  gs_EnergyA.ulP[gs_FeeData.uc_FeeNo+1] += iDelta;
//  #endif
    //组合有功
    iDelta = Eny_GetEp1(0, 0);
    gs_EnergyA.lCP[0] += iDelta;

    #ifdef MultariffMeter
    gs_EnergyA.lCP[gs_FeeData.uc_FeeNo+1] += iDelta;
    #endif 
//  //反向有功
//  iDelta = Eny_GetEp1(2, 0);
//  gs_EnergyA.ulN[0] += iDelta;
//
//  #ifdef MultariffMeter
//  gs_EnergyA.ulN[gs_FeeData.uc_FeeNo+1] += iDelta;
//  #endif
    //计算CRC
    gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
    //需要RAM电量合法才能写E2
    if(Eny_CheckEnergyActiveRAM() == ENERGY_ERR_NONE)
    {
        if(BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA,sizeof(ENERGYACTIVE)))
        {
            return;
        }
    }
    else
    {
        return;
    }

    //这个判断加上,而不是沿用上面的判断是因为防错处理
    if(Eny_CheckEnergyActiveRAM() == ENERGY_ERR_NONE)
    {
        Eny_EnergyClrCur(ENERGY_CLR_RAM);

    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #else
        BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #endif
    }
}

/*=========================================================================================\n
* @function_name: Eny_EnergyProc
* @function_file: Energy.c
* @描述: 电量处理，接收到底层能量数据后，转存入RAM，同时增加CRC校验
*           同时判别是否需要把RAM中的电量转存入E2中
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-07)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Eny_EnergyProc(void)
{
//    uint8   i;
    uint8   ucDelta;
    uint8*  p;                                          // 合相有功能量的指针
    uint16*  p1;
    uint8 ucSaveflg;

    ucSaveflg=0;
    Eny_CheckEnergy();                                  // 检查电量有效性

    p = (uint8*)&gs_Energy;                             // 能量数据;

    p1 = (uint16*)&gs_EnergyData;
//  for (i=0; i<1; i++,p++,p1++)
    {                                                   // 检查有功脉冲标志（电量达到MAX_E，向EEPROM中写一次）
        if ( *p > 0)
        {                                               // 有电量脉冲
            __disable_interrupt();                      // 数据保护
            ucDelta = *p;                               // 把中断中产生的脉冲移动到RAM增量寄存器中
            *p = 0;
            __enable_interrupt();
            *p1 += ucDelta;                             // 将中断产生的能量数据累加到RAM中
        }

        if (*p1 > MAX_E)                                // RAM中的增量数据为无效数据
        {
            Eny_CheckEnergy();
        }

        if (*p1 > SAVEVALUE)                            // 判别是否需要写入
        { 
            ucSaveflg=0x55;                                              
        }  
    }

    gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);  // 电量增量CRC校验
    MemCpy((void*)&gs_EnergyData_bak, (void*)&gs_EnergyData, sizeof(ENERGYDATA));

    if(ucSaveflg==0x55)
    {
        Eny_EnergyActiveSave();
    }
}
/*=========================================================================================\n
* @function_name: WriteHisEP
* @function_file: Energy.c
* @描述: 写入历史电量
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-25)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void WriteHisEP(void)
{
    if(Eny_CheckEnergyActiveRAM() != ENERGY_ERR_NONE)
    {
        BE_ReadP(EEP_EPS, (uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
        if(Eny_CheckEnergyActiveRAM() != ENERGY_ERR_NONE)
        {
        #if (_SW_SE_Type > 0)
            SE_ReadP(EEP_EPS, (uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
        #else
            BE_ReadP(EEP_EPS+EEP_BAK_LEN, (uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
        #endif
        }
    }
    DataProcWriteRound2(R2_MOVE,LSDLID,(uint8*)&gs_EnergyA);    //写入历史电量
}
/*=========================================================================================\n
* @function_name: EnergyCBRManage
* @function_file: Energy.c
* @描述: 抄表日处理,一小时调用本函数判断抄表日时间一次
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-22)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void EnergyCBRManage(void)
{
    uint8 i,j;
    Word16 W16_JSR[3];

    BE_ReadP(EEP_CBR1, W16_JSR[0].byte,6);              // 得到抄表日的日期和小时
                                                    
    for(i=0;i<2;i++)                                    //去除相同的抄表日
    {
        for(j=i+1;j<3;j++)
        {
            if(W16_JSR[i].word==W16_JSR[j].word)
            {
                W16_JSR[j].word=0x9999;
            }
        }
    }


    for(i=0;i<3;i++)
    {
        if(W16_JSR[i].word==0x9999)
        {
            continue;
        }

        //需要需要检测结算日是否合法
        if(W16_JSR[i].byte[0] == gs_DateTime.ucHour && W16_JSR[i].byte[1]  == gs_DateTime.ucDay)
        {
            Eny_EnergyActiveSave();
            WriteHisEP();
            MemSet(XDATA_RAMZONE,0x00,8);
            DataProcWriteRound2(R2_MOVE,LSXLID,XDATA_RAMZONE);  // 写入最大需量数据及时间
            InitDemand();
//            DemandClrCur();                                     // 清零当前需量
            break;                                              //同一个时刻不可能转存好几次           
        }
    }
}
