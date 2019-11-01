#define RPT_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: Rpt_Clr
* @function_file: Report.c
* @描述: 清零主动上报内容
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_Clr(uint8 ucType)
{    
    guc_RptClrCnt = 0;    //不需自动清零
    MemSet((uint8*)&gs_RptStaB, 0x00, RPTSTALEN);                   //主动上报状态备份清零
    switch(ucType)
    {
    default:
    case Const_All:
    case Const_Meter:
        MemSet((uint8*)&gs_ReportStateFlg, 0x00, RPTSTALEN);                //主动上报状态标志清零   
        MemSet((uint8*)&gs_ReportState, 0x00, RPTSTALEN);                   //主动上报状态清零        
        MemSet((uint8*)&gs_RptCnt,      0x00, RPTCNTLEN);                   //主动上报事件次数全清
    case Const_Event:
        gs_RptStaB.ui_RptSta4.ReportWord4.MeterClr 
            = gs_ReportState.ui_RptSta4.ReportWord4.MeterClr;
        gs_RptStaB.ui_RptSta4.ReportWord4.EventClr 
            = gs_ReportState.ui_RptSta4.ReportWord4.EventClr; 
        if(gs_ReportStateFlg.ui_RptSta4.ReportWord4.MeterClr == false)
        {
            MemSet((uint8*)&gs_ReportStateFlg, 0x00, RPTSTALEN);    
        }
        else
        {
            MemSet((uint8*)&gs_ReportStateFlg, 0x00, RPTSTALEN);
            gs_ReportStateFlg.ui_RptSta4.ReportWord4.MeterClr = true;
        }  
        MemCpy((uint8*)&gs_ReportState, (uint8*)&gs_RptStaB, RPTSTALEN);    //
        uint8 temp[2];
        MemCpy(temp, (uint8*)&gs_RptCnt.MeterClr, 2);
        MemSet((uint8*)&gs_RptCnt,      0x00, RPTCNTLEN);                   //
        MemCpy((uint8*)&gs_RptCnt.MeterClr, temp, 2);
        break;        
    }    
}
/*=========================================================================================\n
* @function_name: Rpt_UpdateClr
* @function_file: Report.c
* @描述: 主动上报状态字自动清零
* 
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_UpdateClr(void)
{
    if(guc_RptClrCnt != 0)
    {
        guc_RptClrCnt--;
        if(guc_RptClrCnt == 0)
        {           
            Rpt_UpdateSta((uint16 *)&gs_RptStaB);  
            //Rpt_Clr(Const_Update);      
        }
    }
}
//对应主动上报BIT位,与REPORTCNT结构体对应
const uint8 code RptBIT[]=
{
    0,  1,  2,  3,  5,  7,  8, 10, 13, 14, 15, 20,
   22, 37, 48, 49, 51, 52, 53, 54, 55, 57, 60, 63,
};
/*=========================================================================================\n
* @function_name: Rpt_StaSet
* @function_file: Report.c
* @描述: 设置主动上报状态
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_StaSet(uint8 ucNum)
{   /**/    
    uint16 *pMode, *pFlg, *pRpt, *pRptB;
    uint8 *pCnt;
    uint16 uiMsk;
    uint8 ucCnt;
    uint8 i,flag;
    
    flag = 0;
    if(ucNum&BIT7)
    {
        ucNum &= ~BIT7;
        flag = 1;
    }
    ucCnt = ucNum/16;   //对应word   
    pMode = (uint16 *)&gs_ReportWord+ucCnt;   
    if(ucCnt > 1)
    {
        ucCnt += 2;
    }
    pFlg = (uint16 *)&gs_ReportStateFlg+ucCnt;
    pRpt = (uint16 *)&gs_ReportState+ucCnt;
    pRptB = (uint16 *)&gs_RptStaB+ucCnt;
      
    uiMsk = ucNum%16;   //对应bit
    uiMsk = (uint16)BIT32MAP[uiMsk];
    
    if(((*pMode) & uiMsk) != 0x0000)  //对应主动上报模式字开
    {
        if(((*pFlg) & uiMsk) == 0)    //对应状态标志未置位
        {
            *pRpt |= uiMsk;           //对应状态置位
            *pRptB |= uiMsk;           //对应状态备份置位
            *pFlg |= uiMsk;           //对应状态标志置位
            pCnt = (uint8 *)&gs_RptCnt;
            for(i=0; i<RPTCNTLEN; i++)
            {
                if(ucNum == RptBIT[i])
                {
                    if(flag == 1)
                    {
                        pCnt[i] = 0xff;    //没有对应次数，始终FF    
                    }
                    else if(pCnt[i] != 0xff)    //次数未满FF
                    {
                        pCnt[i]++;    
                    }
                    break;    //单个位处理
                }
            }            
        }
    }
}
/*=========================================================================================\n
* @function_name: Rpt_StaBitClr
* @function_file: Report.c
* @描述: 设置主动上报状态
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-06-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_StaBitClr(uint8 ucNum)
{   /**/    
    uint16 *pFlg, *pRpt, *pRptB;
    uint8 *pCnt;
    uint16 uiMsk;
    uint8 ucCnt;
    uint8 i;

    if(ucNum&BIT7)      
    {
        ucNum &= ~BIT7;
    }
    ucCnt = ucNum/16;   //对应word     
    if(ucCnt > 1)
    {
        ucCnt += 2;
    }
    pFlg  = (uint16 *)&gs_ReportStateFlg+ucCnt;
    pRpt  = (uint16 *)&gs_ReportState+ucCnt;
    pRptB = (uint16 *)&gs_RptStaB+ucCnt;
      
    uiMsk = ucNum%16;   //对应bit
    uiMsk = (uint16)BIT32MAP[uiMsk];
    
    *pRpt  &= ~uiMsk;           //对应状态位清零
    *pRptB &= ~uiMsk;           //对应状态位备份清零
    *pFlg  &= ~uiMsk;           //对应状态标志位清零
    
    pCnt = (uint8 *)&gs_RptCnt;
    for(i=0; i<RPTCNTLEN; i++)
    {
        if(ucNum == RptBIT[i])
        {
            pCnt[i] = 0x00;    //对应次数清零
            break;    
        }
    }    
}
/*=========================================================================================\n
* @function_name: Rpt_StaFlgClr
* @function_file: Report.c
* @描述: 清主动上报状态标志
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_StaFlgClr(uint8 ucNum)
{
    uint16 *pFlg;
    uint16 uiMsk;
    uint8  ucCnt;
    
    if(ucNum&BIT7)
    {
        ucNum &= ~BIT7;
    }
    ucCnt = ucNum/16;   //对应uint16      
    if(ucCnt > 1)
    {
        ucCnt += 2;
    }
    pFlg = (uint16 *)&gs_ReportStateFlg+ucCnt;
         
    uiMsk = ucNum%16;   //对应bit
    uiMsk = (uint16)BIT32MAP[uiMsk];
    if(((*pFlg) & uiMsk) != 0)
    {
        *pFlg &= ~uiMsk;        //清状态标志
    }
}
/*=========================================================================================\n
* @function_name: Rpt_UpdateSta
* @function_file: Report.c
* @描述: 更新主动上报状态字状态
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_UpdateSta(uint16 *pRe)
{
//    s_RptReset.ui_RptSta1.ReportWord1.LoopErrRpt
    uint16 *pRpt;
    uint8 *pCnt;
    uint8 i;
    uint8 ucCnt;
    uint16 uiMsk;
    
    pRpt = (uint16 *)&gs_ReportState;
    pCnt = (uint8 *)&gs_RptCnt;
    
    for(uint8 i=0; i<6; i++)
    {
        pRpt[i] &= pRe[i]; //根据主动上报复位字更新状态字
    }
    
    for(i=0; i<RPTCNTLEN; i++,pCnt++)
    {
        ucCnt = RptBIT[i]/16;       
        if(ucCnt > 1)
        {
            ucCnt += 2;
        }
        pRpt = (uint16 *)&gs_ReportState+ucCnt;  //对应uint16 
        uiMsk = (uint16)BIT32MAP[RptBIT[i]%16];  //对应bit 
        if(((*pRpt) & uiMsk) == 0x0000)
        {
            *pCnt = 0;    
        }
    }
    guc_RptClrCnt = 0;    //不需自动清零
}
/*=========================================================================================\n
* @function_name: Rpt_Chk
* @function_file: Report.c
* @描述: 更新主动上报状态字状态
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_Recover(void)
{
    SysE2ReadData(EEP_ZDSBMSZ,(uint8*)&gs_ReportWord,   RPTWORDLEN);      //刷新主动上报模式字
    MemCpy(XDATA_RAMZONE,    (uint8*)&gs_ReportState,    RPTSTALEN);      //主动上报状态字
    MemCpy(XDATA_RAMZONE+12, (uint8*)&gs_ReportStateFlg, RPTSTALEN);      //主动上报标志
    MemCpy(XDATA_RAMZONE+24, (uint8*)&gs_RptStaB,        RPTSTALEN);      //主动上报状态字清零备份
    MemCpy(XDATA_RAMZONE+36, (uint8*)&guc_RptClrCnt,             1);      //主动上报清零时间
    MemCpy(XDATA_RAMZONE+37, (uint8*)&gs_RptCnt,         RPTCNTLEN);      //主动上报次数
    if(gui_ReportCRC != do_CRC(XDATA_RAMZONE, RPTDATLEN))
    {
        if(gut_SysWarn.SysWarn.BatLow)
        {
            Rpt_Clr(Const_All);
            Rpt_StaSet(RPT_RTCBAT);
            //Rpt_StaSet(RPT_CUTBAT);
        }
        else
        {
            BE_ReadP(EEP_RPTDATA,  (uint8 *)XDATA_RAMZONE,       RPTDATLEN);  //从E2恢复
            MemCpy((uint8*)&gs_ReportState,    XDATA_RAMZONE,    RPTSTALEN);  //主动上报状态字
            MemCpy((uint8*)&gs_ReportStateFlg, XDATA_RAMZONE+12, RPTSTALEN);  //主动上报标志
            MemCpy((uint8*)&gs_RptStaB,        XDATA_RAMZONE+24, RPTSTALEN);  //主动上报状态字清零备份
            MemCpy((uint8*)&guc_RptClrCnt,     XDATA_RAMZONE+36,         1);  //主动上报清零时间
            MemCpy((uint8*)&gs_RptCnt,         XDATA_RAMZONE+37, RPTCNTLEN);  //主动上报次数
        }
    }
    gui_ReportCRC = 0;
}
/*=========================================================================================\n
* @function_name: Rpt_Crc
* @function_file: Report.c
* @描述: 更新主动上报状态字状态
* 
* 
* @参数: 
* @param:    
* 
* @返回: 
* @return: 
* @作者:   lm (2014-05-06)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Rpt_Crc(void)
{
    //if(!gut_SysWarn.SysWarn.BatLow) //电池尚未欠压
    {
        MemCpy(XDATA_RAMZONE,    (uint8*)&gs_ReportState,    RPTSTALEN);   //主动上报状态字       
        MemCpy(XDATA_RAMZONE+12, (uint8*)&gs_ReportStateFlg, RPTSTALEN);   //主动上报状态发生标志
        MemCpy(XDATA_RAMZONE+24, (uint8*)&gs_RptStaB,        RPTSTALEN);   //主动上报状态字清零备份
        MemCpy(XDATA_RAMZONE+36, (uint8*)&guc_RptClrCnt,             1);   //主动上报清零时间
        MemCpy(XDATA_RAMZONE+37, (uint8*)&gs_RptCnt,         RPTCNTLEN);   //主动上报次数
        
        gui_ReportCRC = do_CRC(XDATA_RAMZONE, RPTDATLEN);
        BE_WriteP(EEP_RPTDATA,  XDATA_RAMZONE,  RPTDATLEN+2);  
    }
}