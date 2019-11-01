#define DATAPROTECTEXT
#include "Include.h"

const S_E2PARACHK code gCs_E2ParaChkTab[] =
{//ע��:������Ҫ�ο�E2�����Ų���Ӧ���ĵ�,�����������Ӧ�������ڲο�

    {E2_PROTECT_LEN,    0*E2_PROTECT_LEN},  //0x00
    {JBLEN,             1*E2_PROTECT_LEN},  //0x01 У�����
    {JBLEN,             1*E2_PROTECT_LEN},  //0x02 У�����
    {TIME_LEN,          3*E2_PROTECT_LEN},  //0x03 ʱ������
};
 
/*=========================================================================================\n
* @function_name: GetE2Type
* @function_file: DataProtect.c
* @����: ���ݵ�ַ��ȡҳ��ַ
* 
* 
* @����: 
* @param:uiAddr  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-05-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetE2Type(uint16 uiAddr)
{//����0xFF�ͱ�ʾһ����д��E2
    if(uiAddr >= dim(gCs_E2ParaChkTab)*E2_PROTECT_LEN)
    {
        return 0xFF;
    }
    return  (uint8)(uiAddr>>5);
}
/*=========================================================================================\n
* @function_name: DataSecurityInit
* @function_file: DataProtect.c
* @����: �������ݰ�ȫ����صı�����ʼ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DataSecurityInit(void)
{//�������ݰ�ȫ����صı�����ʼ��
    gul_E2ParaStt = 0x0FFFFFFF;         //��λ��Ĭ�ϲ�������E2��Ч
    gui_RefreshEvent|=(flgEtPara_PowDir);
}
/*=========================================================================================\n
* @function_name: E2ParaCheck
* @function_file: DataProtect.c
* @����: ÿ�����һ��,ʵ��E2��ҪУ��������Ƿּ�,������ÿ��У��,����������ֻ��Ϊ�˽���������У���ڲ�ͬʱ���ɢ
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void E2ParaCheck(void)
//{//��ָ��no�ŵ�E2�����������crcУ���ж�
//    uint8   i = 0;
//    uint8   ucLen;
//    uint8   ucNo;
//    uint16  uiAddr;
//    uint8   ucszChk1[64];
//    uint8   ucszChk2[64];
//
//    if(gs_DateTime.ucMinute>=0x03)      //�ӵ�3���ӿ�ʼ���E2
//    {
//       ucNo=APIByteBCD2HEX(gs_DateTime.ucMinute)-0x03;
//    }else
//    {
//        return;//ǰ������ϵͳ����̫�󲻴���
//    }
//
//    if(ucNo >= dim(gCs_E2ParaChkTab))                                   //�������ʱ��δ��
//    {
//        return;
//    }
//
//    ucLen = gCs_E2ParaChkTab[ucNo].ucLen;
//    uiAddr = gCs_E2ParaChkTab[ucNo].uiAddr;
//
//    BE_ReadP(uiAddr, ucszChk1, ucLen);                          //��ȡ��E2����
//
//#if (_SW_SE_Type > 0)
//    SE_ReadP(uiAddr, ucszChk2, ucLen);                          //��ȡСE2����
//#else
//    BE_ReadP(uiAddr+EEP_BAK_LEN, ucszChk2, ucLen);
//#endif
//
//    if(do_CRC(ucszChk1, ucLen - 2) != Uint8_To_Uint16(ucszChk1 + ucLen - 2))                //�жϴ�E2�Ƿ���ȷ
//    {
//        i = 1;                                                                              //��E2����ȷ
//    }
//
//    if(do_CRC(ucszChk2, ucLen - 2) != Uint8_To_Uint16(ucszChk2 + ucLen - 2))                //�ж�СE2�Ƿ���ȷ
//    {
//        i += 2;                                                                             //СE2����ȷ
//    }
//
//    if(i == 0)                                                                              //�жϴ�СE2�Ƿ���ȷ
//    {                                                                                       //��СE2CRC����ȷ�Ļ�
//        if(Uint8_To_Uint16(ucszChk1 + ucLen - 2) != Uint8_To_Uint16(ucszChk2 + ucLen - 2))  //�жϴ�СE2CRC�Ƿ����
//        {
//            i = 2;                                                                          //���ȣ���ΪСE2���ݲ���ȷ
//        }
//    }
//
//    gul_E2ParaStt |= BIT32MAP[ucNo];
//
//    if(i == 1)
//    {                                                                               //��E2���ݲ���ȷ������СE2���ݸ���
//        gul_E2ParaStt &= ~BIT32MAP[ucNo];
//        BE_WriteP(uiAddr, ucszChk2, ucLen);
//    }
//    else if(i == 2)
//    {                                                                               //СE2���ݲ���ȷ�����ô�E2���ݸ���
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
* @����: E2�������ݴ���,�ڲ������õ�ʱ����д�˴�E2,
*        �ٶԶ�Ӧ��ҳ����crcУ��,ͬʱ����ҳ�����ݱ������Ӧ��СE2
* 
* @����: 
* @param:ucLen  
* @param:uiAddr  
* @param:pucBuf  
* @����: 
* @����:   lwb (2012-05-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
        //������������ò�����ʱ��,
        //�����õĲ���������ڿ�ҳ�����,
        //���ʱ��ᵼ�²�gCs_E2ParaChkTab�����������,
        //��ʵ�ʻ�ֻ�õ�һ��.
        //�����Ҫ������E2������ʱ��ע��,
        //����һ����ʵ�����,û��һ�������ܳ���ҳ���������,Ŀǰ�������
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
* @����: ��ȡE2����
* 
* 
* @����: 
* @param:ucLen  
* @param:uiAddr  
* @param:pucBuf  
* @����: 
* @����:   lwb (2012-05-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
//            SE_ReadP(uiAddr, pucBuf, ucLen);                //��ǰСE2������Ч
//        #else
//            BE_ReadP(uiAddr+EEP_BAK_LEN,pucBuf, ucLen);
//        #endif
//        }
//        else
//        {
//            BE_ReadP(uiAddr, pucBuf, ucLen);                //��ǰ��E2��Ч
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
* @����: ��������Ƿ�Ϸ������Ϸ�ʹ��Ĭ������
* 
* 
* @����: 
* @param:ucNum  
* @param:p  
* @param:psDC  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-05-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 DataCheck(uint8 ucNum, uint8* p, S_DATACHK code* psDC)
{//�����ж����ݵĺϷ���,���ж������Ƿ��ڱ���趨�������޷�Χ֮��,�������Ҫ��Ĭ�ϲ�����������Ļ�,����Ĭ�ϲ�������
    uint8 i;

    for(i=0; i<ucNum; i++,p++,psDC++)
    {//ע��ucMin������0,������*p����uint8�͵�
        if((*p < psDC->ucMin) || (*p > psDC->ucMax))
        {
            //��ʹ��Ĭ��ֵ�Ļ�����Ϊ���������ǰ����ֻ�������ж����ݺϷ��Ե�
            return Const_Data_Err;

        }
    }

    return Const_Data_OK;
}
 
