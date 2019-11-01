#define DATAPROTECTEXT
#include "Include.h"

const S_E2PARACHK code gCs_E2ParaChkTab[] =
{//注意:建表需要参考E2参数排布对应的文档,下面两个秒对应量仅用于参考

    {E2_PROTECT_LEN,    0*E2_PROTECT_LEN},  //0x00
    {JBLEN,             1*E2_PROTECT_LEN},  //0x01 校表参数
    {JBLEN,             1*E2_PROTECT_LEN},  //0x02 校表参数
    {TIME_LEN,          3*E2_PROTECT_LEN},  //0x03 时钟数据
};
 
/*=========================================================================================\n
* @function_name: GetE2Type
* @function_file: DataProtect.c
* @描述: 根据地址获取页地址
* 
* 
* @参数: 
* @param:uiAddr  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-05-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 GetE2Type(uint16 uiAddr)
{//返回0xFF就表示一定读写大E2
    if(uiAddr >= dim(gCs_E2ParaChkTab)*E2_PROTECT_LEN)
    {
        return 0xFF;
    }
    return  (uint8)(uiAddr>>5);
}
/*=========================================================================================\n
* @function_name: DataSecurityInit
* @function_file: DataProtect.c
* @描述: 部分数据安全性相关的变量初始化
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void DataSecurityInit(void)
{//部分数据安全性相关的变量初始化
    gul_E2ParaStt = 0x0FFFFFFF;         //复位后默认参数区大E2有效
    gui_RefreshEvent|=(flgEtPara_PowDir);
}
/*=========================================================================================\n
* @function_name: E2ParaCheck
* @function_file: DataProtect.c
* @描述: 每秒调用一次,实际E2需要校验的周期是分级,而不是每秒校验,这里这样做只是为了将各个区的校验在不同时间打散
* 
* @参数: 
* @返回: 
* @作者:   lwb (2012-05-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void E2ParaCheck(void)
//{//对指定no号的E2参数区间进行crc校验判断
//    uint8   i = 0;
//    uint8   ucLen;
//    uint8   ucNo;
//    uint16  uiAddr;
//    uint8   ucszChk1[64];
//    uint8   ucszChk2[64];
//
//    if(gs_DateTime.ucMinute>=0x03)      //从第3分钟开始检测E2
//    {
//       ucNo=APIByteBCD2HEX(gs_DateTime.ucMinute)-0x03;
//    }else
//    {
//        return;//前几分钟系统负荷太大不处理
//    }
//
//    if(ucNo >= dim(gCs_E2ParaChkTab))                                   //正常检测时间未到
//    {
//        return;
//    }
//
//    ucLen = gCs_E2ParaChkTab[ucNo].ucLen;
//    uiAddr = gCs_E2ParaChkTab[ucNo].uiAddr;
//
//    BE_ReadP(uiAddr, ucszChk1, ucLen);                          //读取大E2参数
//
//#if (_SW_SE_Type > 0)
//    SE_ReadP(uiAddr, ucszChk2, ucLen);                          //读取小E2参数
//#else
//    BE_ReadP(uiAddr+EEP_BAK_LEN, ucszChk2, ucLen);
//#endif
//
//    if(do_CRC(ucszChk1, ucLen - 2) != Uint8_To_Uint16(ucszChk1 + ucLen - 2))                //判断大E2是否正确
//    {
//        i = 1;                                                                              //大E2不正确
//    }
//
//    if(do_CRC(ucszChk2, ucLen - 2) != Uint8_To_Uint16(ucszChk2 + ucLen - 2))                //判断小E2是否正确
//    {
//        i += 2;                                                                             //小E2不正确
//    }
//
//    if(i == 0)                                                                              //判断大小E2是否都正确
//    {                                                                                       //大小E2CRC都正确的话
//        if(Uint8_To_Uint16(ucszChk1 + ucLen - 2) != Uint8_To_Uint16(ucszChk2 + ucLen - 2))  //判断大小E2CRC是否相等
//        {
//            i = 2;                                                                          //不等，认为小E2数据不正确
//        }
//    }
//
//    gul_E2ParaStt |= BIT32MAP[ucNo];
//
//    if(i == 1)
//    {                                                                               //大E2数据不正确，则用小E2数据覆盖
//        gul_E2ParaStt &= ~BIT32MAP[ucNo];
//        BE_WriteP(uiAddr, ucszChk2, ucLen);
//    }
//    else if(i == 2)
//    {                                                                               //小E2数据不正确，则用大E2数据覆盖
//    #if (_SW_SE_Type > 0)
//        SE_WriteP(uiAddr, ucszChk1, ucLen);
//    #else
//        BE_WriteP(uiAddr+EEP_BAK_LEN, ucszChk1, ucLen);
//    #endif
//    }
//}
 
/*=========================================================================================\n
* @function_name: SysE2ParaSetManage
* @function_file: DataProtect.c
* @描述: E2参数备份处理,在参数设置的时候先写了大E2,
*        再对对应的页进行crc校验,同时将这页的数据备份入对应的小E2
* 
* @参数: 
* @param:ucLen  
* @param:uiAddr  
* @param:pucBuf  
* @返回: 
* @作者:   lwb (2012-05-10)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void SysE2ParaSetManage(uint16 uiAddr, uint8* pucBuf,uint8 ucLen)
{
    uint8   ucNo; 
    uint8   ucBlkLen;
    uint16  uiE2Addr;
    uint8   ucszChk1[64];
    uint8   ucszChk2[64];
    uint8*  p = ucszChk1;

    ucNo = GetE2Type(uiAddr);

    if(ucLen == 0)
    {    
        return;
    }
    
    if(ucNo < dim(gCs_E2ParaChkTab))
    {
        //这里假设在设置参数的时候,
        //所设置的参数不会存在跨页的情况,
        //这个时候会导致查gCs_E2ParaChkTab有两个项存在,
        //但实际会只用第一个.
        //这个需要在配置E2参数的时候注意,
        //另外一个是实际情况,没有一个参数能超过页的情况存在,目前至少如此
        ucBlkLen = gCs_E2ParaChkTab[ucNo].ucLen;
        uiE2Addr = gCs_E2ParaChkTab[ucNo].uiAddr;
        BE_ReadP(uiE2Addr, ucszChk1, ucBlkLen);

        if(do_CRC(ucszChk1, ucBlkLen - 2) != Uint8_To_Uint16(ucszChk1 + ucBlkLen - 2))
        {
        #if (_SW_SE_Type > 0)
            SE_ReadP(uiE2Addr, ucszChk2, ucBlkLen);
        #else
            BE_ReadP(uiE2Addr+EEP_BAK_LEN,ucszChk2, ucBlkLen);
        #endif             
            if(do_CRC(ucszChk2, ucBlkLen - 2) == Uint8_To_Uint16(ucszChk2 + ucBlkLen - 2))
            {
                p = ucszChk2;
            }
        }

        MemCpy((p+(uiAddr-uiE2Addr)), pucBuf, ucLen);

        Uint16_To_Uint8(do_CRC(p, ucBlkLen - 2), p + ucBlkLen - 2);
        BE_WriteP(uiE2Addr, p, ucBlkLen);
    #if (_SW_SE_Type > 0)
        SE_WriteP(uiE2Addr, p, ucBlkLen);
    #else 
        BE_WriteP(uiE2Addr+EEP_BAK_LEN, p, ucBlkLen);
    #endif
    }
    else
    {
        BE_WriteP(uiAddr, pucBuf, ucLen);
    }
}
/*=========================================================================================\n
* @function_name: SysE2ReadData
* @function_file: DataProtect.c
* @描述: 读取E2数据
* 
* 
* @参数: 
* @param:ucLen  
* @param:uiAddr  
* @param:pucBuf  
* @返回: 
* @作者:   lwb (2012-05-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
//void SysE2ReadData(uint16 uiAddr, uint8* pucBuf,uint8 ucLen)
//{
//    uint8 ucNo = GetE2Type(uiAddr);
//
//    if(ucNo < dim(gCs_E2ParaChkTab))
//    {
//        if(!(gul_E2ParaStt & BIT32MAP[ucNo]))
//        {
//        #if (_SW_SE_Type > 0)
//            SE_ReadP(uiAddr, pucBuf, ucLen);                //当前小E2数据有效
//        #else
//            BE_ReadP(uiAddr+EEP_BAK_LEN,pucBuf, ucLen);
//        #endif
//        }
//        else
//        {
//            BE_ReadP(uiAddr, pucBuf, ucLen);                //当前大E2有效
//        }
//    }
//    else
//    {
//        BE_ReadP(uiAddr, pucBuf, ucLen);
//    }
//}
/*=========================================================================================\n
* @function_name: DataCheck
* @function_file: DataProtect.c
* @描述: 检查数据是否合法，不合法使用默认数据
* 
* 
* @参数: 
* @param:ucNum  
* @param:p  
* @param:psDC  
* 
* @返回: 
* @return: uint8 
* @作者:   lwb (2012-05-18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
uint8 DataCheck(uint8 ucNum, uint8* p, S_DATACHK code* psDC)
{//用以判断数据的合法性,即判断数据是否在表格设定的上下限范围之内,如果还需要用默认参数进行替代的话,则用默认参数更新
    uint8 i;

    for(i=0; i<ucNum; i++,p++,psDC++)
    {//注意ucMin可能是0,而这里*p又是uint8型的
        if((*p < psDC->ucMin) || (*p > psDC->ucMax))
        {
            //不使用默认值的话就认为这个函数当前功能只是用于判断数据合法性的
            return Const_Data_Err;

        }
    }

    return Const_Data_OK;
}
 
