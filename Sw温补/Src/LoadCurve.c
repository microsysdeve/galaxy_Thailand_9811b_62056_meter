#define LOADCURVEEXT
#include "Include.h"

#ifdef LOADCURVE

const S_CURVESTORE code gs_CurveStoreTab[5]=
{
    {   EEP_ZFHETNO,    EEP_ZFHET_PT,   EEP_ZFHET,  11},
    {   EEP_FHET1NO,    EEP_FHET1_PT,   EEP_FHET1,  10},
    {   EEP_FHET2NO,    EEP_FHET2_PT,   EEP_FHET2,  8},
    {   EEP_FHET3NO,    EEP_FHET3_PT,   EEP_FHET3,  7},
    {   EEP_FHET4NO,    EEP_FHET4_PT,   EEP_FHET4,  13},
};
/*=========================================================================================\n
* @function_name: CmpTm
* @function_file: LoadCurve.c
* @描述: 比较2个时间的大小
* 
* 
* @参数: 
* @param:T1  
* @param:T2  
* @param:n  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 CmpTm(uint8 const *T1, uint8  const *T2, uint8 n ) 
{
    uint8 i ;

    for (i=n; i>0; i--)
    {
        if ( *(T1+i-1) > *(T2+i-1) )
        {
            return CMP_LG;
        }
        else if ( *(T1+i-1) < *(T2+i-1) )
        {
            return CMP_LT;
        }
    }
    return CMP_EQU;
}
/*=========================================================================================\n
* @function_name: Ldc_ZoneChk
* @function_file: LoadCurve.c
* @描述: 根据读取时间
* 
* 
* @参数: 
* @param:tmBG   指定读取最早时标C
* @param:tmED   指定读取最新时标D
* @param:type   负荷类型
*
* @返回: 
* @return: uint16  返回位置
* @作者:   lwb (2013-02-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint16 Ldc_ZoneChk(uint8 const *tmBG, uint8 const *tmED, uint8 ucType)
{
    uint32 ulCurveCnt;
    uint8  ucZone;
    uint16 uiBaseAddr;

    uiBaseAddr = gs_CurveStoreTab[ucType].uiBaseAddr;
    ulCurveCnt = 0;
    ucZone     = 0;
    
    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr, (uint8*)&ulCurveCnt, 3);       //读取分类负荷总次数
    if(ulCurveCnt == 0)
    {
        return Err_NO;    //无存储数据
    }
    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,  (uint8*)&gs_LdcPos.uiCurPt, 2);//读取当前负荷指针
//    BE_ReadP(uiBaseAddr+gs_LdcPos.uiCurPt *gs_CurveStoreTab[ucType].ucLen,
//             XDATA_RAMZONE+5, 5);                                                //读取当前指向的时间，即最新时标B   
    if(ulCurveCnt > CurveTotalCnt)    //保护   
    {
        ulCurveCnt = CurveTotalCnt;
    }
    gs_LdcPos.uiLastPt = (gs_LdcPos.uiCurPt + ulCurveCnt - 1)%CurveTotalCnt;    //得到最早时标指针
    BE_ReadP(uiBaseAddr+gs_LdcPos.uiLastPt*gs_CurveStoreTab[ucType].ucLen,
             XDATA_RAMZONE, 5);                                                 //读取最早指向的时间，即最早时标A
    MemCpy(XDATA_RAMZONE+5, (uint8*)&gs_DateTime.ucMinute, 5);                  //读取电表最新时间，即最新时标B    
    if(CmpTm(tmED, XDATA_RAMZONE,  5) == CMP_LT)    //比较读取时标D与记录时标A
    {
        return Err_LT;    //D<A 顺序CDAB无交集，返回错误
    }      
    if(CmpTm(tmBG, XDATA_RAMZONE+5, 5) == CMP_LG)   //比较读取时标C与记录时标B
    {
        return Err_LG;    //C>B 顺序ABCD ，还需考虑电表时间
    }      
    if(CmpTm(tmBG, XDATA_RAMZONE,  5) == CMP_LT)    //比较读取时标C与记录时标A
    {
        MemCpy((uint8 *)tmBG, XDATA_RAMZONE, 5);    //CAXX 读取时标C改为A
        ucZone |= BIT0;
    }        
    if(CmpTm(tmED, XDATA_RAMZONE+5, 5) == CMP_LG)   //比较读取时标D与记录时标B
    {
        MemCpy((uint8 *)tmED, XDATA_RAMZONE+5, 5);  //XXBD 读取时标D改为B
        ucZone |= BIT1;
    }    
//    if((ucZone&0x03) == 0x01)         //A-D
//    {
//        gs_LdcFrame.TotalCnt
//    }
//    else if((ucZone&0x03) == 0x02)    //C-B
//    {
//        gs_LdcFrame.TotalCnt
//    }
//    else if((ucZone&0x03) == 0x03)    //A-B
      
    if((ucZone&0x03) != 0)  
    {
        uint32 tp1,tp2;
//        tp0=Ldc_TmMinCal((uint8 *)&gs_LdcFrame.tmOG);
        tp1=Ldc_TmMinCal((uint8 *)tmED);
        tp2=Ldc_TmMinCal((uint8 *)tmBG); 
        gs_LdcFrame.TotalCnt = 1+(tp1-tp2)/gs_LdcFrame.uiGap;
//        if((ucZone&0x02)==0x02)
//        {
//            gs_LdcFrame.TotalCnt = 1+(tp1-tp2)/gs_LdcFrame.uiGap;
//        }
//        else
//        {
//            gs_LdcFrame.TotalCnt = 1+((tp1-tp2)-(tp2-tp0))/gs_LdcFrame.uiGap;
//            if(CmpTm(tmED, tmBG, 5) == CMP_EQU)
//            {
//                return Err_NO;
//            }
//        }
    }
    //其他情况，读取点数不变    
    return 0;
}
/*=========================================================================================\n
* @function_name: Search1stEqualItem
* @function_file: LoadCurve.c
* @描述: 根据指定时间查找数据项，二分法查找
* 
* 
* @参数: 
* @param:tmBG   指定读取最早时标C
* @param:tmED   指定读取最新时标D
* @param:type   负荷类型
*
* @返回: 
* @return: uint16  返回位置
* @作者:   lwb (2013-02-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint16 Search1stEqualItem(uint8 const *tmBG, uint8 ucType)//, uint8 ucEqual)
{
    uint16 low, mid, high;
    //uint16 CurPt,LastPt;
    //uint32 ulCurveCnt;
    uint8  ucResult;
    uint16 uiBaseAddr;

    uiBaseAddr = gs_CurveStoreTab[ucType].uiBaseAddr;
    //ulCurveCnt = 0;

//    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr, (uint8*)&ulCurveCnt, 3);       //读取分类负荷总次数
//    if(ulCurveCnt == 0)
//    {
//        return Err_NO;    //无存储数据
//    }
//    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,  (uint8*)&gs_LdcPos.uiCurPt, 2);//读取当前负荷指针
//    BE_ReadP(uiBaseAddr+gs_LdcPos.uiCurPt*gs_CurveStoreTab[ucType].ucLen,
//             XDATA_RAMZONE, 5);                                                 //读取当前指向的时间，即最近时标
//    
//    if(ulCurveCnt > CurveTotalCnt)    //保护   
//    {
//        ulCurveCnt = CurveTotalCnt;
//    }
//    gs_LdcPos.uiLastPt = (gs_LdcPos.uiCurPt + ulCurveCnt - 1)%CurveTotalCnt;    //得到最早时标
//    
//    ucResult = CmpTm(tm, XDATA_RAMZONE, 5);                                     //比较查找时标与最近时标
//    if(ucResult == CMP_EQU)
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
//        return gs_LdcPos.uiCurPt;
//    }
//    else if (ucResult == CMP_LG)                                                //比最近时标大   
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
//        return Err_LG|gs_LdcPos.uiCurPt;  
//    }
//
//    BE_ReadP(uiBaseAddr+gs_LdcPos.uiLastPt*gs_CurveStoreTab[ucType].ucLen,
//             XDATA_RAMZONE, 5); //读取最早指向的时间
//    
//    ucResult = CmpTm(tm, XDATA_RAMZONE, 5);                                       //比较最早记录时标
//    if(ucResult == CMP_EQU)                                                     //等于最早记录则返回最早记录偏移
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
//        return gs_LdcPos.uiLastPt;
//    }
//    else if(ucResult == CMP_LT)                                                 //小于返回最早时间或错误
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
//        return Err_LT|gs_LdcPos.uiLastPt;
//    }
    //XDATA_RAMZONE是由zonechk传递而来
    ucResult = CmpTm(tmBG, XDATA_RAMZONE+5, 5);                                     //比较查找时标与最近时标
    if(ucResult == CMP_EQU)
    {
        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
        return gs_LdcPos.uiCurPt;
    }
//    else if (ucResult == CMP_LG)                                                   //比最近时标大   
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
//        return Err_LG|gs_LdcPos.uiCurPt;  
//    }   
    ucResult = CmpTm(tmBG, XDATA_RAMZONE, 5);                                       //比较最早记录时标
    if(ucResult == CMP_EQU)                                                     //等于最早记录则返回最早记录偏移
    {
        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
        return gs_LdcPos.uiLastPt;
    }
//    else if(ucResult == CMP_LT)                                                 //小于返回最早时间或错误
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
//        return Err_LT|gs_LdcPos.uiLastPt;
//    }
    //下面是判断是查找存储的那段位置
    if(gs_LdcPos.uiCurPt > gs_LdcPos.uiLastPt)                                  //判断是否回滚
    {   //回滚了回滚了回滚了
        BE_ReadP(uiBaseAddr+(CurveTotalCnt-1)*gs_CurveStoreTab[ucType].ucLen,
                 XDATA_RAMZONE, 5);                                             //读取存储位置最后指向的时间

        ucResult = CmpTm(tmBG, XDATA_RAMZONE, 5);                                 //比对时间
        if(ucResult == CMP_LT)        //小，上半区
        {
            low  = 0;
            high = gs_LdcPos.uiLastPt;
        }
        else if (ucResult == CMP_LG ) //大，下半区
        {
            low  = gs_LdcPos.uiCurPt;
            high = CurveTotalCnt-1;
        }
        else                          //相等，直接返回
        {
            gs_LdcPos.uiFindPt = CurveTotalCnt-1;
            return gs_LdcPos.uiFindPt;
        }
    }
    else                              //没有回滚
    {
        low  = gs_LdcPos.uiCurPt;
        high = gs_LdcPos.uiLastPt; 
        if(low == high)   //防止意外死循环
        {             
            return low;
        }
        //gs_LdcPos.ucIsFull = 0x00;
    }

    //二分法查找指定时间
    while (1)
    {
        if(low == high)   //防止意外死循环
        {             
            return Err_MD|low;
        }
        mid = (low + high) / 2; 
        BE_ReadP(uiBaseAddr+mid*gs_CurveStoreTab[ucType].ucLen, XDATA_RAMZONE, 5);  //读取中间时标
        ucResult = CmpTm(tmBG, XDATA_RAMZONE, 5);
        if(ucResult == CMP_LT)
        {
            if (low + 1 == high)
            {  
                return Err_MD|low;
            }
            else
            {
                low = mid ;
            }
        }
        else if ( ucResult == CMP_LG )
        {
            if ( low + 1 == high)
            {  
                return Err_MD|low;
            }
            else
            {
                high = mid ;
            }
        }
        else
        {
            return mid;
        }
    } 
}
//uint16 Search1stEqualItem(uint8 const *tm, uint8 ucType)//, uint8 ucEqual)
//{
//    uint16 low, mid, high;
//    //uint16 CurPt,LastPt;
//    uint32 ulCurveCnt;
//    uint8  ucResult;
//    uint16 uiBaseAddr;
//
//    uiBaseAddr = gs_CurveStoreTab[ucType].uiBaseAddr;
//    ulCurveCnt = 0;
//    
//    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr, (uint8*)&ulCurveCnt, 3);       //读取分类负荷总次数
//    if(ulCurveCnt == 0)
//    {
//        return Err_NO;    //无存储数据
//    }
//    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,  (uint8*)&gs_LdcPos.uiCurPt, 2);//读取当前负荷指针
//    BE_ReadP(uiBaseAddr+gs_LdcPos.uiCurPt*gs_CurveStoreTab[ucType].ucLen,
//             XDATA_RAMZONE, 5);                                                 //读取当前指向的时间，即最近时标
//    
//    if(ulCurveCnt > CurveTotalCnt)    //保护   
//    {
//        ulCurveCnt = CurveTotalCnt;
//    }
//    gs_LdcPos.uiLastPt = (gs_LdcPos.uiCurPt + ulCurveCnt - 1)%CurveTotalCnt;    //得到最早时标
//    
//    ucResult = CmpTm(tm, XDATA_RAMZONE, 5);                                     //比较查找时标与最近时标
//    if(ucResult == CMP_EQU)
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
//        return gs_LdcPos.uiCurPt;
//    }
//    else if (ucResult == CMP_LG)                                                //比最近时标大   
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiCurPt;
//        return Err_LG|gs_LdcPos.uiCurPt;  
//    }
//
//    BE_ReadP(uiBaseAddr+gs_LdcPos.uiLastPt*gs_CurveStoreTab[ucType].ucLen,
//             XDATA_RAMZONE, 5); //读取最早指向的时间
//    
//    ucResult = CmpTm(tm, XDATA_RAMZONE, 5);                                       //比较最早记录时标
//    if(ucResult == CMP_EQU)                                                     //等于最早记录则返回最早记录偏移
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
//        return gs_LdcPos.uiLastPt;
//    }
//    else if(ucResult == CMP_LT)                                                 //小于返回最早时间或错误
//    {
//        gs_LdcPos.uiFindPt = gs_LdcPos.uiLastPt;
//        return Err_LT|gs_LdcPos.uiLastPt;
//    }
//
//    //下面是判断是查找存储的那段位置
//    if(gs_LdcPos.uiCurPt > gs_LdcPos.uiLastPt)                                  //判断是否回滚
//    {   //回滚了回滚了回滚了
//        BE_ReadP(uiBaseAddr+(CurveTotalCnt-1)*gs_CurveStoreTab[ucType].ucLen,
//                 XDATA_RAMZONE, 5);                                             //读取存储位置最后指向的时间
//
//        ucResult = CmpTm(tm, XDATA_RAMZONE, 5);                                 //比对时间
//        if(ucResult == CMP_LT)        //小，上半区
//        {
//            low  = 0;
//            high = gs_LdcPos.uiLastPt;
//        }
//        else if (ucResult == CMP_LG ) //大，下半区
//        {
//            low  = gs_LdcPos.uiCurPt;
//            high = CurveTotalCnt-1;
//        }
//        else                          //相等，直接返回
//        {
//            gs_LdcPos.uiFindPt = CurveTotalCnt-1;
//            return gs_LdcPos.uiFindPt;
//        }
//    }
//    else                              //没有回滚
//    {
//        low  = gs_LdcPos.uiCurPt;
//        high = gs_LdcPos.uiLastPt; 
//        //gs_LdcPos.ucIsFull = 0x00;
//    }
//
//    //二分法查找指定时间
//    while (1)
//    {
//        if(low == high)   //防止意外死循环
//        {             
//            return Err_MD|low;
//        }
//        mid = (low + high) / 2; 
//        BE_ReadP(uiBaseAddr+mid*gs_CurveStoreTab[ucType].ucLen, XDATA_RAMZONE, 5);  //读取中间时标
//        ucResult = CmpTm(tm, XDATA_RAMZONE, 5);
//        if(ucResult == CMP_LT)
//        {
//            if (low + 1 == high)
//            {  
//                return Err_MD|low;
//            }
//            else
//            {
//                low = mid ;
//            }
//        }
//        else if ( ucResult == CMP_LG )
//        {
//            if ( low + 1 == high)
//            {  
//                return Err_MD|low;
//            }
//            else
//            {
//                high = mid ;
//            }
//        }
//        else
//        {
//            return mid;
//        }
//    } 
//}
/*=========================================================================================\n
* @function_name: SearchEqualItem
* @function_file: LoadCurve.c
* @描述: 根据指定时间查找数据项，二分法查找
* 
* 
* @参数: 
* @param:tm     指定时间
* @param:type  负荷类型
* @param:ucEqual  是否只返回相等结果，true只返回相等，false 返回最接近  
*
* @返回: 
* @return: uint16  返回位置，0xffff,无效位置
* @作者:   lwb (2013-02-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint16 SearchEqualItem(uint8 const *tm, uint8 ucType, uint8 ucEqual)
{
    uint16 low, mid, high;
    uint16 CurPt,LastPt;
    uint32 ulCurveCnt;
    uint8  ucResut;
    uint16 uiBaseAddr;

    uiBaseAddr=gs_CurveStoreTab[ucType].uiBaseAddr;
    ulCurveCnt=0;

    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr,(uint8*)&ulCurveCnt,3);         //读取分类负荷总次数
    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,(uint8*)&CurPt,2);               //负荷指针
    BE_ReadP(uiBaseAddr+CurPt*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);  //读取当前指向的时间，即最近的时间

    ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );     //比较最新记录时标,相等则返回0
    if ( ucResut ==  CMP_EQU )
    {
        return CurPt;
    }
    else if (ucResut == CMP_LG )              //大则返回查找不到    
    {
        if(ucEqual == true)
        {
            return 0xffff;
        }
        else
        {
           uint32 tp1,tp2,tpCnt;
           uint16 *uiGapPt;
           uiGapPt                 = (uint16 *)&gs_LdcSet.uiFH1;  //负荷记录间隔时间
           gs_LdcFrame.uiGap       = uiGapPt[ucType - 1];         //负荷间隔
        
           tp1=Ldc_TmMinCal((uint8 *) tm );
           tp2=Ldc_TmMinCal(XDATA_RAMZONE); 
           tpCnt = ((tp1-tp2)/gs_LdcFrame.uiGap) + ulCurveCnt;
           if( tpCnt > CurveTotalCnt) //时间超出总条数
           {
             return 0xfff0;
           }else
           {
             return 0xff00;                    //返回查找不到
           }
        }
    }

    if(ulCurveCnt > CurveTotalCnt)    //保护   
    {
        ulCurveCnt = CurveTotalCnt;
    }
    LastPt = (CurPt + ulCurveCnt - 1)%CurveTotalCnt;

    BE_ReadP(uiBaseAddr+LastPt*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);     //读取最早指向的时间
    ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );                                           //比较最早记录时标
    if ( ucResut ==  CMP_EQU )                                                      //等于最早记录则返回最早记录偏移
    {
        return LastPt;
    }
    else if (ucResut == CMP_LT )    //小于返回最早时间或错误
    {
        if(ucEqual == true)
        {
            return LastPt;
        }
        else
        {
            return 0xffff;
        }
    }

    //下面是判断是查找存储的那段位置
    if (CurPt>LastPt)                                                               //判断是否回滚了
    {
        BE_ReadP(uiBaseAddr+(CurveTotalCnt-1)*gs_CurveStoreTab[ucType].ucLen,
                 XDATA_RAMZONE,5);                                                  //读取存储位置最后指向的时间

        ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );                                       //比对时间

        if (ucResut==CMP_LT )
        {
            low=0;
            high=LastPt;
        }
        else if (ucResut==CMP_LG )
        {
            low=CurPt;
            high=CurveTotalCnt-1;
        }
        else
        {
            return CurveTotalCnt-1;
        }
    }
    else
    {
        low=CurPt;
        high=LastPt;        
    }

    //二分法查找指定时间
    while (1)
    {
        if(low == high)   //防止意外死循环
        {    
            return low;
        }
        mid = (low + high) / 2; 
        BE_ReadP(uiBaseAddr+mid*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);   //读取最早指向的时间
        ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );
        if (ucResut==  CMP_LT )
        {
            if (low + 1 == high)
            {     
                return low;
            }
            else
            {
                low = mid ;
            }
        }
        else if ( ucResut == CMP_LG )
        {
            if ( low + 1 == high)
            {
                return low;
            }
            else
            {
                high = mid ;
            }
        }
        else
        {
            return mid;
        }
    } 
}

/*=========================================================================================\n
* @function_name: Ldc_BuildFrame
* @function_file: LoadCurve.c
* @描述: 构建单条负荷记录数据帧
* 
* 
* @参数: 
* @param:uclen  
* @param:ucType  
* @param:DesBuff  
* @param:SrcBuff  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8  Ldc_BuildFrame(uint8 ucType, uint8*DesBuff, uint8*SrcBuff)
{
    uint8 ucLen;
    
    ucLen = 0;
    if((ucType&0x0f) == 0x01)
    {
        if((ucType&0xf0) == 0x10)   
        {
            ucLen = 2;
            MemCpy(DesBuff, SrcBuff+5, 2);              //记录电压
        }
        else                        
        {
            ucLen = 3;
            MemCpy(DesBuff, SrcBuff+7, 3);              //记录电流
        } 
    }
    else if((ucType&0x0f) == 0x02)
    {
        ucLen = 3;
        MemCpy(DesBuff, SrcBuff+5, 3);   //总有功功率   
    }
    else if((ucType&0x0f) == 0x03)
    {
        ucLen = 2;
        MemCpy(DesBuff, SrcBuff+5, 2);   //总功率因数   
    }
    else                                  //总有功电能
    {
        ucLen = 4;
        if((ucType&0xf0) == 0x10)         //正向
        {
            MemCpy(DesBuff, SrcBuff+5, 4);              
        }
        else                              //反向
        {
            MemCpy(DesBuff, SrcBuff+9, 4);              
        }              
    }
    MemCpy((uint8 *)&gs_LdcFrame.ulLastData, DesBuff, ucLen);
    
    return ucLen;
}
/*=========================================================================================\n
* @function_name: Ldc_BuildFakeFrm
* @function_file: LoadCurve.c
* @描述: 构建单条负荷记录数据帧
* 
* 
* @参数: 
* @param:uclen  
* @param:ucType  
* @param:DesBuff  
* @param:SrcBuff  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8  Ldc_BuildFakeFrm(uint8 ucType, uint8 *DesBuff)//, uint8 ucCnt)
{
    uint8 ucLen;
    
    ucLen = 0;
    if((ucType&0x0f) == 0x01)
    {
        if((ucType&0xf0) == 0x10)   
        {
            ucLen = 2;
            MemSet(DesBuff, 0xff, ucLen);              //记录电压
        }
        else                        
        {
            ucLen = 3;
            MemSet(DesBuff, 0xff, ucLen);              //记录电流
        } 
    }
    else if((ucType&0x0f) == 0x02)
    {
        ucLen = 3;
        MemSet(DesBuff, 0xff, ucLen);   //总有功功率   
    }
    else if((ucType&0x0f) == 0x03)
    {
        ucLen = 2;
        MemSet(DesBuff, 0xff, ucLen);   //总功率因数   
    }
    else                                  //总有功电能 正反
    {
        ucLen = 4;
        MemCpy(DesBuff, (uint8 *)&gs_LdcFrame.ulLastData, ucLen);
    }
    
    return ucLen;
}
/*=========================================================================================\n
* @function_name: GetOneTmRecord
* @function_file: LoadCurve.c
* @描述: 读单项给定时间负荷记录块
* 
* 
* @参数: 
* @param:ucType 
* @param:Tm  
* @param:ucCnt  
* @param:buff  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//uint8 Ldc_Get1stRecord(uint8 ucType, uint8 *TmBG, uint8 *TmED, uint8 *buff)
//{
//    uint16 uiPos;
//  //  uint16 CurPt;
//    uint16 State;
//    
//    gs_LdcPos.ucReadFlg = false;    //读数据标志
//    
//    uiPos = Search1stEqualItem((uint8 const *)TmBG, (uint8 const *)TmED, (ucType&0x0f));
//    
//    State = uiPos&0xFC00;
//    uiPos &= ~0xFC00;   //去除标志,定位相同或上一点数据
//    gs_LdcPos.uiFindPt = uiPos;     
//    
//    if(State != 0)      //有错误标志
//    {
//        if(State == Err_NO)   //无数据
//        {
//            return 0;
//        }
////        else                  //时标未找到相同数据
////        {        
////            if(State == Err_LG)             //查找时标>最新时标
////            {
////                gs_LdcPos.ucReadFlg = true;
////            }
////        }
//    }
//
//    if(gs_LdcPos.uiCurPt == gs_LdcPos.uiFindPt)   //当前时标==最新时标
//    {
//        gs_LdcPos.ucReadFlg = true;
//    }      
//    
//    if(State != 0 && State != Err_LT)            //时标未找到
//    {
//        uint32 temp;
//        
//        temp = gs_LdcFrame.ulLastMin%gs_LdcFrame.uiGap;   //距离下点时间
//        Ldc_TimeAdd((uint8*)&gs_LdcFrame.tmBG, temp);    //得到下点时标
//        if(CmpTm((uint8*)&gs_LdcFrame.tmBG, (uint8*)&gs_DateTime.ucMinute, 5) == CMP_LG) //超过当前时间
//        {
//            gs_LdcFrame.SeqFrameEnd = true;
//            return 0;
//        }
//        //读取查找得到数据（上1点的数据+下1点的时标）
//        BE_ReadP(gs_CurveStoreTab[ucType&0x0f].uiBaseAddr
//                 +gs_LdcPos.uiFindPt*gs_CurveStoreTab[ucType&0x0f].ucLen,
//                 XDATA_RAMZONE,
//                 gs_CurveStoreTab[ucType&0x0f].ucLen*2);
//        if(gs_LdcPos.uiFindPt == CurveTotalCnt - 1)
//        {
//            gs_LdcPos.uiFindPt = 0;
//        }
//        else
//        {
//            gs_LdcPos.uiFindPt++;   //指向上个数据
//        }
//        MemCpy(buff, (uint8*)&gs_LdcFrame.tmBG, 5);
//        MemCpy((uint8*)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5);
//        gs_LdcPos.ucIsFake = (Ldc_TmMinCal(XDATA_RAMZONE) - gs_LdcFrame.ulLastMin) 
//                              / gs_LdcFrame.uiGap;                        //得到补次数
//        if(gs_LdcPos.ucIsFake != 0)
//        {
//            gs_LdcPos.ucIsFake--;
//            if((ucType&0x0f) == 0x04)
//            {
//                MemCpy((uint8 *)&gs_LdcFrame.ulLastData, XDATA_RAMZONE+5, 4);
//            }
//            return 5+Ldc_BuildFakeFrm(ucType, buff+5);
//        }
//        else
//        {
//            return 5+Ldc_BuildFrame(ucType, buff+5, XDATA_RAMZONE+gs_CurveStoreTab[ucType&0x0f].ucLen);
//        }
//    }
//    else                                         //找到时标 or 小于最早时标
//    {
//        //读取查找得到数据
//        BE_ReadP(gs_CurveStoreTab[ucType&0x0f].uiBaseAddr+uiPos*gs_CurveStoreTab[ucType&0x0f].ucLen,
//             XDATA_RAMZONE,
//             gs_CurveStoreTab[ucType&0x0f].ucLen);
//        MemCpy(buff, XDATA_RAMZONE, 5);
//        MemCpy((uint8 *)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5);
//        return 5+Ldc_BuildFrame(ucType, buff+5, XDATA_RAMZONE);
//    }    
//}
uint8 Ldc_Get1stRecord(uint8 ucType, uint8 *Tm, uint8 *buff)
{
    uint16 uiPos;
  //  uint16 CurPt;
    uint16 State;
    
    gs_LdcPos.ucReadFlg = false;    //读数据标志
    uiPos = Search1stEqualItem((uint8 const *)Tm, (ucType&0x0f));
    
    State = uiPos&0xFC00;
    uiPos &= ~0xFC00;   //去除标志,定位相同或上一点数据
    gs_LdcPos.uiFindPt = uiPos;     
    
    if(State != 0)      //有错误标志
    {
        if(State == Err_NO)   //无数据
        {
            return 0;
        }
        else                  //时标未找到相同数据
        {        
            if(State == Err_LG)             //查找时标>最新时标
            {
                gs_LdcPos.ucReadFlg = true;
            }
        }
    }

//    if(gs_LdcPos.uiCurPt == gs_LdcPos.uiFindPt)   //当前时标==最新时标
//    {
//        gs_LdcPos.ucReadFlg = true;
//    }      
    
    if(State != 0 && State != Err_LT)            //时标未找到
    {
        uint32 temp;
        
        temp = gs_LdcFrame.uiGap-gs_LdcFrame.ulLastMin%gs_LdcFrame.uiGap;   //距离下点时间
        Ldc_TimeAdd((uint8*)&gs_LdcFrame.tmBG, temp);    //得到下点时标
        if(CmpTm((uint8*)&gs_LdcFrame.tmBG, (uint8*)&gs_LdcFrame.tmED, 5) == CMP_LG) //超过读取最后时间
        {
            gs_LdcFrame.SeqFrameEnd = true;
            return 0;
        }
        //读取查找得到数据（上1点的数据+下1点的时标）
        BE_ReadP(gs_CurveStoreTab[ucType&0x0f].uiBaseAddr
                 +gs_LdcPos.uiFindPt*gs_CurveStoreTab[ucType&0x0f].ucLen,
                 XDATA_RAMZONE,
                 gs_CurveStoreTab[ucType&0x0f].ucLen*2);
//        if(gs_LdcPos.uiFindPt == CurveTotalCnt - 1)
//        {
//            gs_LdcPos.uiFindPt = 0;
//        }
//        else
//        {
//            gs_LdcPos.uiFindPt++;   //指向上个数据
//        }
        MemCpy(buff, (uint8*)&gs_LdcFrame.tmBG, 5);
        MemCpy((uint8*)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5);
        gs_LdcPos.ucIsFake = (Ldc_TmMinCal(XDATA_RAMZONE) - gs_LdcFrame.ulLastMin) 
                              / gs_LdcFrame.uiGap;                        //得到补次数
        if(gs_LdcPos.ucIsFake != 0)
        {
            if(gs_LdcPos.uiFindPt == CurveTotalCnt - 1)
            {
                gs_LdcPos.uiFindPt = 0;
            }
            else
            {
                gs_LdcPos.uiFindPt++;   //指向上个数据
            }
            BE_ReadP(gs_CurveStoreTab[ucType&0x0f].uiBaseAddr
                 +gs_LdcPos.uiFindPt*gs_CurveStoreTab[ucType&0x0f].ucLen,
                 XDATA_RAMZONE,
                 gs_CurveStoreTab[ucType&0x0f].ucLen*2);
            gs_LdcPos.ucIsFake--;
            if((ucType&0x0f) == 0x04)
            {
                if((ucType&0x30) == 0x10)
                {
                    MemCpy((uint8 *)&gs_LdcFrame.ulLastData, XDATA_RAMZONE+5, 4);
                }
                else
                {
                    MemCpy((uint8 *)&gs_LdcFrame.ulLastData, XDATA_RAMZONE+9, 4);
                }
            }
            MemCpy(buff, (uint8*)&gs_LdcFrame.tmOG, 5);
            return 5+Ldc_BuildFakeFrm(ucType, buff+5);
        }
        else
        {
            return 5+Ldc_BuildFrame(ucType, buff+5, XDATA_RAMZONE);//+gs_CurveStoreTab[ucType&0x0f].ucLen);
        }
    }
    else                                         //找到时标 or 小于最早时标
    {
        //读取查找得到数据
        BE_ReadP(gs_CurveStoreTab[ucType&0x0f].uiBaseAddr+uiPos*gs_CurveStoreTab[ucType&0x0f].ucLen,
             XDATA_RAMZONE,
             gs_CurveStoreTab[ucType&0x0f].ucLen);
        
        if(CmpTm((uint8 *)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5) == CMP_LG)
        {
            if((ucType&0x0f) == 0x04)
            {
                if((ucType&0x30) == 0x10)
                {
                    MemCpy((uint8 *)&gs_LdcFrame.ulLastData, XDATA_RAMZONE+5, 4);
                }
                else
                {
                    MemCpy((uint8 *)&gs_LdcFrame.ulLastData, XDATA_RAMZONE+9, 4);
                }
            }
            MemCpy(buff, (uint8*)&gs_LdcFrame.tmOG, 5);
            return 5+Ldc_BuildFakeFrm(ucType, buff+5);
        }
        else
        {
            if(gs_LdcPos.uiCurPt == gs_LdcPos.uiFindPt)   //当前时标==最新时标
            {
                gs_LdcPos.ucReadFlg = true;
            } 
            MemCpy(buff, XDATA_RAMZONE, 5);
            MemCpy((uint8 *)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5);
            return 5+Ldc_BuildFrame(ucType, buff+5, XDATA_RAMZONE);
        }      
    }    
}
/*=========================================================================================\n
* @function_name: Ldc_TmMinCal
* @function_file: LoadCurve.c
* @描述: 
* 
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-06-05)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint32 Ldc_TmMinCal(uint8 *Tm)
{
    uint32 ulTm;
    //以2000年1月1日为基准到现在的所有天数,因此时间不能在2000年之前(其实2000年用00表示,百年以上都略去)    
    uint8 ucYear = APIByteBCD2HEX(Tm[4]);        //年转换成Hex
    uint8 ucMonth = APIByteBCD2HEX(Tm[3])-1;      //月转换成Hex
    uint8 ucDay = APIByteBCD2HEX(Tm[2]) - 1;      //日转换成Hex
    uint8 ucHour = APIByteBCD2HEX(Tm[1]);
    uint8 ucMin = APIByteBCD2HEX(Tm[0]);
    if((ucYear & 0x03) == 0)                            //判断是否过了闰年的2月
    {
        if(ucMonth >= 2)
            ucDay++;                                    //大于等于3月份，闰年应该加上2。29的一天
    }
    else
    {
        ucDay++;                                        //非闰年加上00年闰月多出来的一天
    }
    
    ulTm = (ucYear*365 + gui_MonthBeginDay[ucMonth] + (ucDay + (ucYear>>2)))*((uint32)1440)
           + ((uint16)ucHour*((uint16)60)) + ucMin;
    return ulTm;
}
/*=========================================================================================\n
* @function_name: Ldc_TimeCal
* @function_file: LoadCurve.c
* @描述: 
* 
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-05-20)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 Ldc_TimeCal(uint8 *TmNew, uint8 *TmOld, uint16 Gap)
{
    uint32 ulTmNew,ulTmOld,ulTmGap;
    
    ulTmNew = Ldc_TmMinCal(TmNew);
    ulTmOld = Ldc_TmMinCal(TmOld);
    ulTmGap = ulTmNew - ulTmOld;
    if(ulTmGap == (uint32)Gap || ulTmGap == 0)    //连续时间点 或 补到时间点
    {
        return 0x00;
    }
    else  
    {
        if(ulTmGap/Gap >= 97)
          return 96;
        else
          return (ulTmGap/Gap) - 1;        
    }
}
/*=========================================================================================\n
* @function_name: GetOneTmSeqRecord
* @function_file: LoadCurve.c
* @描述: 读取给定时间分负荷后续帧数据块
* 
* 
* @参数: 
* @param:ucType  
* @param:ucCnt  
* @param:buff  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-19)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 Ldc_GetSeqRecord(uint8 ucType, uint8 *buff)
{
    //uint16 CurPt;
    uint16 uiBaseAddr;
    uint8  ucLen;
    
    if(gs_LdcPos.ucIsFake != 0x00)
    {
        gs_LdcPos.ucIsFake--;
        return Ldc_BuildFakeFrm(ucType, buff);
    }
    else if(gs_LdcPos.ucReadFlg == true)     //已经是最新数据
    {
        Ldc_TimeAdd((uint8*)&gs_LdcFrame.tmBG, gs_LdcFrame.uiGap);    //得到下点时标
        if(CmpTm((uint8*)&gs_LdcFrame.tmBG, (uint8*)&gs_DateTime.ucMinute, 5) == CMP_LG) //超过当前时间
        {
            gs_LdcFrame.SeqFrameEnd = true;
            return 0;
        }
        return Ldc_BuildFakeFrm(ucType, buff);
    }
    
    uiBaseAddr = gs_CurveStoreTab[ucType&0x0f].uiBaseAddr;
    ucLen      = gs_CurveStoreTab[ucType&0x0f].ucLen;
    
    if(gs_LdcPos.uiFindPt == 0)
    {
        gs_LdcPos.uiFindPt = CurveTotalCnt - 1;
    }
    else
    {
        gs_LdcPos.uiFindPt--;   //指向下个数据
    }
    BE_ReadP(uiBaseAddr+gs_LdcPos.uiFindPt*ucLen, XDATA_RAMZONE, ucLen);
//    if(gs_LdcPos.uiFindPt == gs_LdcPos.uiCurPt)
//    {
//        gs_LdcPos.ucReadFlg = true;
//    }

    gs_LdcPos.ucIsFake = Ldc_TimeCal(XDATA_RAMZONE, (uint8*)&gs_LdcFrame.tmBG, gs_LdcFrame.uiGap);
    
    MemCpy((uint8 *)&gs_LdcFrame.tmBG, XDATA_RAMZONE, 5);
    if(gs_LdcPos.ucIsFake == 0x00)
    {    
        if(gs_LdcPos.uiFindPt == gs_LdcPos.uiCurPt)
        {
            gs_LdcPos.ucReadFlg = true;
        }        
        return Ldc_BuildFrame(ucType, buff, XDATA_RAMZONE);
    }
    else
    {
        if(gs_LdcPos.uiFindPt == CurveTotalCnt - 1)
        {
            gs_LdcPos.uiFindPt = 0;
        }
        else
        {
            gs_LdcPos.uiFindPt++;   //指向上个数据
        }
        gs_LdcPos.ucIsFake--;
        return Ldc_BuildFakeFrm(ucType, buff);
    }
}
/*=========================================================================================\n
* @function_name: LoadCurveCheck
* @function_file: LoadCurve.c
* @描述: 
* 
* 
* @参数: 
* @param:Tm  
* @param:buff  
* @返回: 
* @作者:   lm (2013-02-16)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void LoadCurveCheck(void)
{
    uint8 i,j;
    uint16 uiPosition;
    uint32 ulCurveCnt;
    uint16 uiTotalPt;
    uint8 buff[20];
     
    MemCpy(XDATA_RAMZONE1,&gs_DateTime.ucMinute,5);    //写入时间
    if(guc_Timechange == 0x55)    //发生时间改变
    {          
        for(i=1;i<5;i++)
        {                
            uiPosition=SearchEqualItem((uint8 const *)XDATA_RAMZONE1, i, false);
            if(uiPosition == 0xffff)                                                //改变时间小于最早时间
            {
                if(i==0)
                {
                    ulCurveCnt=0;
                    uiTotalPt=0;
                    for(j=0;j<5;j++)
                    {
                        BE_WriteP(gs_CurveStoreTab[j].uiPtAddr, (uint8*)&uiTotalPt, 2);             //
                        BE_WriteP(gs_CurveStoreTab[j].uiCntAddr, (uint8*)&ulCurveCnt, 3);           //
                    }
                    MemSet(buff,0x00,gs_CurveStoreTab[0].ucLen);
                    BE_WriteP(gs_CurveStoreTab[0].uiBaseAddr, buff, gs_CurveStoreTab[0].ucLen);    //清负荷记录
                    break;
                }
                ulCurveCnt=0;
                uiTotalPt=0;
                BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);   //
                BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);     //                  
            }
            else if((uiPosition != 0xff00) && (uiPosition != 0xfff0))                                           //当前修改的时间,在负荷记录中处于中间。
            {
                ulCurveCnt = 0;
                BE_ReadP(gs_CurveStoreTab[i].uiCntAddr,(uint8*)&ulCurveCnt,3);      //读取负荷总次数
                BE_ReadP(gs_CurveStoreTab[i].uiPtAddr,(uint8*)&uiTotalPt,2);        //读取负荷记录当前指针

                if(ulCurveCnt>CurveTotalCnt)                                        //当记录的负荷次数大于E2存储的负荷有效次数
                {
                    ulCurveCnt=CurveTotalCnt;                                       //负荷记录次数修改成E2存储的有效负荷次数
                }
                
               /*if(uiPosition==uiTotalPt)
                {
                
                
                    continue;
                }
                else */if(uiPosition>=uiTotalPt)                                            //当前时间位置大于当前负荷记录指针      
                {
                    ulCurveCnt=ulCurveCnt-1-(uiPosition-uiTotalPt);                 //负荷有效次数等于
                }
                else if(uiPosition<uiTotalPt)
                {                                      
                    ulCurveCnt=ulCurveCnt-1-(CurveTotalCnt+uiPosition-uiTotalPt);
                }
               

                BE_ReadP(gs_CurveStoreTab[i].uiBaseAddr+uiPosition*gs_CurveStoreTab[i].ucLen,XDATA_RAMZONE,5);

                if(CMP_EQU==CmpTm(XDATA_RAMZONE1, XDATA_RAMZONE, 5 ))               //现在时间与位置时间相等
                {
                     if(uiPosition == uiTotalPt)
                     {
                        continue;
                     }
                     ulCurveCnt++;  
                     uiTotalPt=uiPosition;
                }else
                {
//                    if(uiPosition == uiTotalPt)
//                    {
//                        ulCurveCnt--;  
//                        uiTotalPt=(uiPosition+1)%CurveTotalCnt;   
//                    }
//                    else
                    {
                        uiTotalPt=(uiPosition+1)%CurveTotalCnt; 
                    }
                }
                
                BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);             //
                BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);           //
            }
            else if(uiPosition == 0xfff0)
            {
              
                DataProcRead2Slice(FH1JLID+(i-1),0,0,gs_CurveStoreTab[i].ucLen,XDATA_RAMZONE);
                MemCpy(XDATA_RAMZONE,XDATA_RAMZONE1,5);                
                Ldc_TimeSub( XDATA_RAMZONE, (CurveTotalCnt-1) * gs_LdcFrame.uiGap);//计算之前时间点
                if( i != 4) //不是第四类负荷记录
                {
                  MemSet(XDATA_RAMZONE+5, 0xFF, gs_CurveStoreTab[i].ucLen-5);
                }
                uiTotalPt = CurveTotalCnt -1;
                ulCurveCnt = 1;
                BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);             //
                BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);
                BE_WriteP(gs_CurveStoreTab[i].uiBaseAddr+uiTotalPt*gs_CurveStoreTab[i].ucLen,XDATA_RAMZONE,gs_CurveStoreTab[i].ucLen);
            }
            
        }
        guc_Timechange = 0;
    }
}
/*=========================================================================================\n
* @function_name: Ldc_DataProc
* @function_file: LoadCurve.c
* @描述: 
* 
* 
* @参数:  
* @返回: 
* @作者:   lm (2014-05-20)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Ldc_DataProc(void)
{
    uint32 temp_value;
    uint8 uc_SaveType;
    uint32 ul_Min;
    uint8 i;
    uint16 *pTime;   
   
    uc_SaveType = 0;
    ul_Min=(uint32)CalcAbsDay((S_TIMEDATA*)&gs_DateTime)*((uint32)1440)
           + ((uint16)APIByteBCD2HEX(gs_DateTime.ucHour)*((uint16)60))
           + APIByteBCD2HEX(gs_DateTime.ucMinute);
           //- gul_LoadCurveMin;
    
    pTime=(uint16*)&gs_LdcSet.uiFH1;

    if(gs_LdcSet.ucLdcMode)
    {
        for (i=0; i<4; i++)
        {
            if ( (ul_Min%pTime[i]== 0)                    //间隔
                 && (gs_LdcSet.ucLdcMode&BIT8MAP[i]))       //模式字
            {
                uc_SaveType |= BIT8MAP[i];
            }          
        }
    }

    if(POWERSTATE())            //系统停电，直接返回，不进行负荷记录
    {
        return;
    }

    if (uc_SaveType)
    {
        //增加覆盖时间判断
        LoadCurveCheck();
        MemCpy(XDATA_RAMZONE,&gs_DateTime.ucMinute,5);    //写入时间

        if (uc_SaveType&CurveOneType)   //电压，电流，频率
        {
            temp_value = CalRMS(RMSU);
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,2);
            temp_value = CalRMS(RMSI1);
            MemCpy(XDATA_RAMZONE+7,(uint8*)&temp_value,3);
//            temp_value = CalRMS(DATAFREQ);
//            MemCpy(XDATA_RAMZONE+10,(uint8*)&temp_value,2); 
            DataProcWriteRound2(R2_MOVE,FH1JLID,XDATA_RAMZONE); 
            DataProcEvCountAdd(FH1NUMID);                   //增加负荷1记录            
        }
        if (uc_SaveType&CurveTwoType)   //功率
        {
            temp_value = CalRMS(DATAP);
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,3);

            DataProcWriteRound2(R2_MOVE,FH2JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH2NUMID);                   //增加负荷2记录
        }
        if (uc_SaveType&CurveThreeType) //功率因数
        {           
            temp_value = CalCos();
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,2);

            DataProcWriteRound2(R2_MOVE,FH3JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH3NUMID);                   //增加负荷3记录
        }
        if (uc_SaveType&CurveFourType)  //正反有功电能
        {
            temp_value = gs_EnergyA.ulP[0];
            temp_value += Eny_GetEp1(1, 0);
            temp_value/=10;
            temp_value = Hex2BCD(temp_value);             //转换为BCD码
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,4);

            temp_value = gs_EnergyA.ulN[0];
            temp_value += Eny_GetEp1(2, 0);
            temp_value/=10;
            temp_value = Hex2BCD(temp_value);             //转换为BCD码
            MemCpy(XDATA_RAMZONE+9,(uint8*)&temp_value,4);

            DataProcWriteRound2(R2_MOVE,FH4JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH4NUMID);                   //增加负荷1记录
        }
    }
}
/*=========================================================================================\n
* @function_name: Ldc_Recover
* @function_file: LoadCurve.c
* @描述: 
* 
* 
* @参数: 
* @返回: 
* @作者:   lm (2014-05-20)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Ldc_Recover(void)
{
    S_LDCPARA  s_LdcSet;

    MemCpy((uint8 *)&s_LdcSet, (uint8 *)&gs_LdcSet, 9);     //刷新前模式字与间隔   
    SysE2ReadData(EEP_FHJLMSZ, (uint8*)&gs_LdcSet, 9);      //刷新负荷记录模式字与间隔    
    if(ApiBufCmp((uint8 *)&s_LdcSet, (uint8 *)&gs_LdcSet, 9) != CMP_EQU)  
    {        
        uint8 i;
        MemSet(XDATA_RAMZONE, 0x00, 5);

        if(s_LdcSet.ucLdcMode != gs_LdcSet.ucLdcMode)
        {
            for(i=1; i<5; i++)
            {     
                BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, XDATA_RAMZONE, 5);   //次数+指针
            }  
        }
        else
        {
            uint16 *p1, *p2;
            p1 = &s_LdcSet.uiFH1;
            p2 = &gs_LdcSet.uiFH1;
            for(i=0; i<4; i++,p1++,p2++)
            {   
                if(*p1 != *p2)
                {
                    BE_WriteP(gs_CurveStoreTab[i+1].uiCntAddr, XDATA_RAMZONE, 5);   //清负荷记录
                }               
            } 
        }        
    }   
}
/*=========================================================================================\n
* @function_name: Ldc_TimeAdd
* @function_file: DLT_645_2007.c
* @描述: 上次时间+间隔
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @param:CTable  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Ldc_TimeAdd(uint8 *Tm, uint32 ulLen)
{
    uint32  ulHour;
    uint32  ulMin;
    
    ulMin = APIByteBCD2HEX(Tm[0]) + ulLen;     //uiMin实际限制60*96+59
    ulHour = APIByteBCD2HEX(Tm[1]) + ulMin/60;   
    ulMin = ulMin%60;
    Tm[0] = APIByteHEX2BCD((uint8)ulMin);      //保存更新后的分
    if(ulHour >= 24)
    {
        uint32 ulDay; 
        uint8 ucMaxDay;
        
        ulDay = APIByteBCD2HEX(Tm[2]) + ulHour/24;
        ulHour = ulHour%24;
        Tm[1] = APIByteHEX2BCD(ulHour);          //保存更新后的时
        do
        {
          ucMaxDay = MonthDays[Tm[3]];
          if(Tm[3] == 0x02)
          {
              if((APIByteBCD2HEX(Tm[4]) & 0x03) == 0)      // 闰年
              {
                  ucMaxDay++;                                        //闰年二月最大天数增加1
              }
          }
          
          if(ulDay > ucMaxDay)
          {
              uint8 ucMonth;
              
              ulDay -= ucMaxDay;
              //Tm[2] = APIByteHEX2BCD(ucDay);        //保存更新后的天
              ucMonth = APIByteBCD2HEX(Tm[3]);
              ucMonth++;                                              //增加1月,最大不会超过7天
              if(ucMonth > 12)
              {
                  uint8 ucYear;
                  
                  ucMonth = 1;
                  ucYear = APIByteBCD2HEX(Tm[4]);
                  ucYear++;
                  if(ucYear > 99)
                  {
                      ucYear = 0;
                  }
                  Tm[4] = APIByteHEX2BCD(ucYear);        //保存更新后的年
              }
              Tm[3] = APIByteHEX2BCD(ucMonth);          //保存更新后的月
          }
          CLRWDT();
        }while( ulDay > MonthDays[Tm[3]]);
        Tm[2] = APIByteHEX2BCD(ulDay);          //保存更新后的天
    }
    Tm[1] = APIByteHEX2BCD(ulHour);          //保存更新后的时
}

/*=========================================================================================\n
* @function_name: Ldc_TimeSub
* @function_file: DLT_645_2007.c
* @描述: 当前时间-间隔
* 
* 
* @参数: 
* @param:s_FrmInfo  
* @param:CTable  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2013-02-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void Ldc_TimeSub(uint8 *Tm, uint16 uiLen)
{    
    uint32 ulMin;
    uint8 time[5];
    
    ulMin=Ldc_TmMinCal( Tm );
    if( ulMin >= uiLen)
    {
      ulMin -= uiLen;
    }else
    {
      ulMin = 0;
    }
    time[0] = 0x00; //以2000年1月1日为基准
    time[1] = 0x00;
    time[2] = 0x01;
    time[3] = 0x01;
    time[4] = 0x00;
    Ldc_TimeAdd( time, ulMin);
    MemCpy( Tm, time, 5);
}
#endif
