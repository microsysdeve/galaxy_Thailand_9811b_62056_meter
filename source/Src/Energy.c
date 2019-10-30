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
    SLPWDT();               //800k喂狗
    BE_ReadP(EEP_JBTOTAL,ucjb,sizeof(S_JBPM));
    SLPWDT();               //800k喂狗
    if(Uint8_To_Uint16(ucjb+sizeof(S_JBPM)-2)==do_CRC(ucjb,sizeof(S_JBPM)-2))
    {
        Eny_JbPm_UpdateRam(ucjb);
        EnyB_JbPm_Updata();
    }                                                            
    else                                                         
    {
        SLPWDT();               //800k喂狗
    #if (_SW_SE_Type > 0)
        SE_ReadP(EEP_JBTOTAL,ucjb,sizeof(S_JBPM));
    #else
        BE_ReadP(EEP_JBTOTAL+EEP_BAK_LEN,ucjb,sizeof(S_JBPM));
    #endif
        SLPWDT();               //800k喂狗
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
   // BE_ReadW(EEP_JBTOTAL+sizeof(S_JBPM)-2, &uitmp);                             //读E2中的CRC校验值
    if(1) //(uitmp == gs_JbPm.ui_JbCRC)                                               //判断他们E2中的数据是否与RAM中的相等
    {                                                                           //RAM中的数据与E2中的是一样的
        if(1) //gs_JbPm.ui_JbCRC == do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2))      //RAM中的数据是否完整
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
//    EnyB_JbPm_Init();
//    EnyB_JbPm_Updata();
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
/*
void Eny_RefCalcType(void)
{
    //BE_ReadB(EEP_YGCALC,&guc_EPCalcType);               //刷新计量方式字
    guc_EPCalcType=0x05;
}
*/
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
        guc_UnitCF = 10;                                  
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

/*
void Eny_EnergyClrCur(uint8 ucType)
{                       
    if(ucType & ENERGY_CLR_RAM)
    {
        MemSet((uint8*)&gs_EnergyData, 0, sizeof(ENERGYDATA)-2);    //电量增量
        gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);
        MemCpy((uint8*)&gs_EnergyData_bak, (uint8*)&gs_EnergyData, sizeof(ENERGYDATA));
    }

    if(ucType & ENERGY_CLR_E2)
    {
        MemSet((uint8*)&gs_EnergyA, 0, sizeof(ENERGYACTIVE));
        gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE)- 2);
        BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));

    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #else
        BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
    #endif

    }
}
 */
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
/*
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
            }
        }
        else
        {
            MemCpy((uint8*)&gs_EnergyA, (uint8*)&sEA, sizeof(ENERGYACTIVE));                //拷贝主E2电量到RAM中
        }
    }
}
*/
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
/*
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
 */
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
/*
uint8 Eny_CheckEnergyActiveRAM(void)
{
   return ENERGY_ERR_NONE;
    //验证数据CRC校验
    if(do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE)- 2) != gs_EnergyA.uiCRC)
    {
        return ENERGY_ERR_RAM;
    }
    
    return ENERGY_ERR_NONE;
}
 */
/*=========================================================================================\n
* @function_name: Eny_GetEp1
* @function_file: Energy.c
* @描述: 计算当前正、反有功总电能增量（分费率)
* 
* 
* @参数: 
* @param:index  0-组合（计量状态字决定）, 1-原正, 2-反
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
/*
int16 Eny_GetEp1(uint8 index, uint8 fee)                 
{
    int16 iRet=0;
    uint16 *pEyP;
    uint16 *pEyN;

//    if((gs_FunCfg.uc_CfSaveCfg&0x0f)!=0x05)                             //CF脉冲分费率计数
//    {
//        if((fee != 0) && ((fee - 1) != gs_FeeData.uc_FeeNo))            //如果传入的费率参数不等于当前费率或者不等于总电量的话返回0
//        {
//            return 0;
//        }
//    }
  
    Eny_CheckEnergy();                                                  //检查电量增量有效性，是否通的过CRC校验


//    if((gs_FunCfg.uc_CfSaveCfg&0x0f)==0x05)                            //CF脉冲分费率计数
//    {
////        if(fee == 0)
//        {
//            pEyP=&gs_EnergyData.uiEPZ;           //正向总脉冲
//            pEyN=&gs_EnergyData.uiENZ;           //反向总脉冲
//        }
////        else
////        {
////            pEyP=(&gs_EnergyData.uiEP1 + (fee - 1));
////            pEyN=(&gs_EnergyData.uiEN1 + (fee - 1));
////        }       
//    }else
    {
        pEyP=&gs_EnergyData.uiEPZ;           //正向总脉冲
        pEyN=&gs_EnergyData.uiENZ;           //反向总脉冲
    }

    if(index==1)
    {
        iRet = *pEyP;                               //返回正向电量增量
    }else if(index==0)
    {   
                                                    //下面是正向有功按照计量方式字来处理
        //正向增量处理
        if(guc_EPCalcType&BIT0)
        {
            iRet = *pEyP;
        }
        else if(guc_EPCalcType&BIT1)
        {
            iRet -= *pEyP;
        }
        //反向增量处理
        if(guc_EPCalcType&BIT2)
        {
            iRet += *pEyN;
        }
        else if(guc_EPCalcType&BIT3)
        {
            iRet -= *pEyN;
        }
                       
    }else if(index==2)
    {
        iRet =*pEyN;                                             //返回反向电流增量
    }
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
#ifdef _DEL
void Eny_EnergyActiveSave(void)
{
    uint8 ucFlg = 0;
//    uint8 i = 0;
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
   // if(ucFlg == 0)
    //{
     //   if(do_CRC ((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2) != gs_EnergyA.uiCRC)
      //  {
       //     //如果电量都不正确，则都不处理，直接返回。
       //     return;
       // }
    //}

    //if(ucFlg == 1)
   // {
    //    MemCpy((void*)&gs_EnergyA, (void*)&sEA, sizeof(ENERGYACTIVE));
   // }

    {
          //正向有功
        iDelta = Eny_GetEp1(1, 0);
        gs_EnergyA.ulP += iDelta;
        //组合有功
        iDelta = Eny_GetEp1(0, 0);
        gs_EnergyA.lCP[0] += iDelta;
        //反向有功
        iDelta = Eny_GetEp1(2, 0);
        gs_EnergyA.ulN += iDelta;    
    }
//    if((gs_FunCfg.uc_CfSaveCfg&0x0f)==0x05)                            //CF脉冲分费率计数
//    {
//        for(i=0; i<5; i++)
//        {
//            iDelta = Eny_GetEp1(1, i);
//            gs_EnergyA.ulP[i] += iDelta; 
//            iDelta = Eny_GetEp1(0, i);
//            gs_EnergyA.lCP[i] += iDelta; 
//            iDelta = Eny_GetEp1(2, i);
//            gs_EnergyA.ulN[i] += iDelta; 
//        } 
//    }else
//    {
//          //正向有功
//        iDelta = Eny_GetEp1(1, 0);
//        gs_EnergyA.ulP[0] += iDelta;
//        gs_EnergyA.ulP[gs_FeeData.uc_FeeNo+1] += iDelta;
//        //组合有功
//        iDelta = Eny_GetEp1(0, 0);
//        gs_EnergyA.lCP[0] += iDelta;
//        gs_EnergyA.lCP[gs_FeeData.uc_FeeNo+1] += iDelta;
//        //反向有功
//        iDelta = Eny_GetEp1(2, 0);
//        gs_EnergyA.ulN[0] += iDelta;
//        gs_EnergyA.ulN[gs_FeeData.uc_FeeNo+1] += iDelta;     
//    }

    //计算CRC
    gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
    //需要RAM电量合法才能写E2
    if(Eny_CheckEnergyActiveRAM() == ENERGY_ERR_NONE)
    {
        BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA,sizeof(ENERGYACTIVE));
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
 #endif
/*=========================================================================================\n
* @function_name: Eny_EnergyProc
* @function_file: Energy.c
* @描述: 电量处理，接收到底层能量数据后，转存入RAM，同时增加CRC校验
*       同时判别是否需要把RAM中的电量转存入E2中
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
    uint8   i;                                           
    uint8   ucDelta;  
    uint8*  p;                                          // 合相有功能量的指针
    uint16*  p1;
    uint8 ucSaveflg;
    uint8 ctemp=0;
                                             
    ucSaveflg=0;                                                    
    Eny_CheckEnergy();                                  // 检查电量有效性
                                                        
    p = (uint8*)&gs_Energy;                             // 能量数据;
    p1 = (uint16*)&ctemp ;//gs_EnergyData;
                       
    for (i=0; i<sizeof(gs_Energy); i++,p++,p1++)
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
RamData.ImpBfr +=ctemp;//gs_EnergyData;//

  //  gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);  // 电量增量CRC校验
//    MemCpy((void*)&gs_EnergyData_bak, (void*)&gs_EnergyData, sizeof(ENERGYDATA));
 //   if(ucSaveflg==0x55)
  //  {
   //     Eny_EnergyActiveSave();
   // }
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
/*
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
*/
/*=========================================================================================\n
* @function_name: MonthLYDL
* @function_file: Energy.c
* @描述: 月度组合电量过月
* 
* @参数: 
* @返回: 
* @作者:   lwb (2013-03-01)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void MonthLYDL(uint8 uc_Save)
{
//    uint32 ulData;
//    uint8  ucPt;
//    int16 iDelta[2];
//    Word32 JSSJTime;
//    
//    BE_ReadB(EEP_SYZHLYDL_PT, (uint8*)&ucPt);       //指针
//    if(ucPt == 0)
//    {
//        ucPt = 1;
//    }
//    else
//    {
//        ucPt--;
//    }
//
//    iDelta[0] = Eny_GetEp1(1, 0);                   //当前正向电量增量
//    iDelta[1] = Eny_GetEp1(2, 0);                   //当前反向电量增量
//    ulData=gs_EnergyA.ulP[0]+gs_EnergyA.ulN[0]+iDelta[0]+iDelta[1];
//    BE_WriteP(EEP_SYZHLYDLADDR+ucPt*4,(uint8*)&ulData,4);
//    BE_WriteP(EEP_SYZHLYDL_PT, (uint8*)&ucPt,1);    //写入指针数据  
//   
//    if(uc_Save == 1)
//    {
//        JSSJTime.byte[0]=gs_DateTime.ucHour;
//        JSSJTime.byte[1]=gs_DateTime.ucDay;
//        JSSJTime.byte[2]=gs_DateTime.ucMonth;
//        JSSJTime.byte[3]=gs_DateTime.ucYear;
//        Eny_EnergyActiveSave();
//        WriteHisEP();
//        SaveJSTime(JSSJTime.lword);
//    }
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
//    uint8 i,j;
//    Word32 JSSJTime;
//    Word16 W16_JSR[3];
//
//    BE_ReadP(EEP_CBR1, W16_JSR[0].byte,6);              // 得到抄表日的日期和小时
//                                                    
//    for(i=0;i<2;i++)                                    //去除相同的抄表日
//    {
//        for(j=i+1;j<3;j++)
//        {
//            if(W16_JSR[i].word==W16_JSR[j].word)
//            {
//                W16_JSR[j].word=0x9999;
//            }
//        }
//    }
//
//
//    for(i=0;i<3;i++)
//    {
//        if(W16_JSR[i].word==0x9999)
//        {
//            continue;
//        }
//        //需要需要检测结算日是否合法
//
//        if(W16_JSR[i].byte[0] == gs_DateTime.ucHour && W16_JSR[i].byte[1]  == gs_DateTime.ucDay)
//        {
//            if(i==0)                                            //过第一个结算日，存组合有功总累用电量
//            {
//                MonthLYDL(1);
//            }
//            else
//            {
//            //抄表日时间到,开始数据转存
//                JSSJTime.byte[0]=W16_JSR[i].byte[0];
//                JSSJTime.byte[1]=W16_JSR[i].byte[1];
//                JSSJTime.byte[2]=gs_DateTime.ucMonth;
//                JSSJTime.byte[3]=gs_DateTime.ucYear;
//                Eny_EnergyActiveSave();
//                WriteHisEP();
//                SaveJSTime(JSSJTime.lword);
//            }
//            break;                                  //同一个时刻不可能转存好几次           
//        }
//    }
}
/*=========================================================================================\n
* @function_name: SaveJSTime
* @function_file: Energy.c
* @描述: 保存结算时间
* 
* 
* @参数: 
* @param:time  
* @返回: 
* @作者:   xuqf (2013-1-5)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void SaveJSTime(uint32 time)
{
    DataProcWriteRound2(R2_MOVE,JSSJJLID,(uint8*)&time);
}
/*=========================================================================================\n
* @function_name: Eny_SlpProc
* @function_file: Energy.c
* @描述:休眠电量处理
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-04-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Eny_SlpEnergyProc(void)
{
    //读脉冲计数器累加电量，记2个出一次脉冲
    uint32  ul_Dat = EnyB_ReadMeterParaACK(PPCFCNT); 
    
    if(ul_Dat >= gul_DatCFcnt)    //保护，寄存器溢出
    {
        guc_DatCFrmd += (ul_Dat-gul_DatCFcnt);
    }
    else    
    {
        guc_DatCFrmd += ((~gul_DatCFcnt+1)+ul_Dat);
    }
    gul_DatCFcnt = ul_Dat;
    
    gs_PowerCf.uc_Pz += (guc_DatCFrmd/2);
    guc_DatCFrmd %= 2;
    
    RamData.ImpBfr+=gs_PowerCf.uc_Pz ;
    if ( RamData.ImpBfr )   
    {
    Do_Use();
    RamData.OldImpBfr = RamData.ImpBfr-1;
    Pwr_E2Save();         //每次都保留CF尾数
    }
    return;
    
    if(gs_PowerCf.uc_Pz >= guc_GateCF)                                     //判别是否需要走字
    {
        uint8 cnt;
        cnt = gs_PowerCf.uc_Pz / guc_GateCF;
        gs_PowerCf.uc_Pz -= guc_GateCF*cnt;                                //对CF脉冲进行分频，将分频结果进行能量累加
        gs_Energy.ucPz   += guc_UnitCF*cnt;
         /*  px opt        
        gs_EnergyData.uiEPZ += gs_Energy.ucPz;
        gs_Energy.ucPz = 0;

        //gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);  // 电量增量CRC校验
        //MemCpy((void*)&gs_EnergyData_bak, (void*)&gs_EnergyData, sizeof(ENERGYDATA));
        Dif((gs_EnergyData.uiEPZ > SAVEVALUE)||(gs_EnergyData.uiENZ > SAVEVALUE)) // 判别是否需要写入
        {
          Eny_EnergyActiveSave(); 
        }
//        Pwr_E2Save();         //放在这里，在休眠计量下，正常上电和电池没电都会丢掉CF尾数，为降功耗，先这样
        */
    }
    
}

