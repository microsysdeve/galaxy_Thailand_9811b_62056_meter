#define LOADCURVEEXT
#include "Include.h"

#ifdef LOADCURVE

const S_CURVESTORE code gs_CurveStoreTab[5]=
{
    {   EEP_ZFHETNO,    EEP_ZFHET_PT,   EEP_ZFHET,  11},
    {   EEP_FHET1NO,    EEP_FHET1_PT,   EEP_FHET1,  12},
    {   EEP_FHET2NO,    EEP_FHET2_PT,   EEP_FHET2,  8},
    {   EEP_FHET3NO,    EEP_FHET3_PT,   EEP_FHET3,  7},
    {   EEP_FHET4NO,    EEP_FHET4_PT,   EEP_FHET4,  13},
};
/*=========================================================================================\n
* @function_name: ReCoverPoint
* @function_file: LoadCurve.c
* @����: �ָ�ָ��
* 
* 
* @����: 
* @param:Curve_DesPt  
* @param:Curve_SrcPt  
* @����: 
* @����:   lwb (2013-02-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ReCoverPoint(S_CURVETOTAL *Curve_DesPt,S_CURVETOTAL1 *Curve_SrcPt)
{
    uint8  *SrcPt;
    uint16 *DesPt;
    uint16 uiHighBit;
    uint8 i;

    MemCpy((uint8*)Curve_DesPt,(uint8*)Curve_SrcPt,6);           //����ʱ��,��ģʽ��

    SrcPt=&Curve_SrcPt->ucOnePt;
    DesPt=&Curve_DesPt->uiOnePt;
    uiHighBit=Curve_SrcPt->ucHighBit;
    for (i=0;i<4;i++)
    {
        DesPt[i]=SrcPt[i];
        uiHighBit<<=2;
        DesPt[i]|=(uiHighBit&0x0300);
    }
}
/*=========================================================================================\n
* @function_name: CmpTm
* @function_file: LoadCurve.c
* @����: �Ƚ�2��ʱ��Ĵ�С
* 
* 
* @����: 
* @param:T1  
* @param:T2  
* @param:n  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
* @function_name: SearchEqualItem
* @function_file: LoadCurve.c
* @����: ����ָ��ʱ�������������ַ�����
* 
* 
* @����: 
* @param:tm     ָ��ʱ��
* @param:type  ��������
* @param:ucEqual  �Ƿ�ֻ������Ƚ����trueֻ������ȣ�false ������ӽ�  
*
* @����: 
* @return: uint16  ����λ�ã�0xffff,��Чλ��
* @����:   lwb (2013-02-15)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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

    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr,(uint8*)&ulCurveCnt,3);         //��ȡ��4�ฺ���ܴ���
    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,(uint8*)&CurPt,2);               //����ָ��
    BE_ReadP(uiBaseAddr+CurPt*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);  //��ȡ��ǰָ���ʱ�䣬�������ʱ��

    ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );                                       //�Ƚ����¼�¼ʱ��,����򷵻�0
    if ( ucResut ==  CMP_EQU )
    {
        return CurPt;
    }
    else if (ucResut == CMP_LG )
    {
        if(ucEqual == true)
        {
            return 0xffff;
        }
        else
        {
            return 0xff00;                                                          //���ز��Ҳ���
        }
    }


    if(ulCurveCnt > CurveTotalCnt)
    {
        ulCurveCnt = CurveTotalCnt;
    }
    LastPt = (CurPt + ulCurveCnt - 1)%CurveTotalCnt;
//    if (ulCurveCnt>CurveTotalCnt)                                               //��������ָ��
//    {
//        if (CurPt>0)
//        {
//            LastPt=CurPt-1;
//        }
//        else
//        {
//            LastPt=CurveTotalCnt-1;
//        }
//    }
//    else
//    {
//        LastPt=CurveTotalCnt-1;
//    }

    BE_ReadP(uiBaseAddr+LastPt*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);     //��ȡ����ָ���ʱ��
    ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );                                           //�Ƚ������¼ʱ��
    if ( ucResut ==  CMP_EQU )                                                      //���������¼�򷵻������¼ƫ��
    {
        return LastPt;
    }
    else if (ucResut == CMP_LT )
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

    //�������ж��ǲ��Ҵ洢���Ƕ�λ��
    if (CurPt>LastPt)                                                               //�ж��Ƿ�ع���
    {
        BE_ReadP(uiBaseAddr+(CurveTotalCnt-1)*gs_CurveStoreTab[ucType].ucLen,
                 XDATA_RAMZONE,5);                                                  //��ȡ�洢λ�����ָ���ʱ��

        ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );                                       //�ȶ�ʱ��

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

    //���ַ�����ָ��ʱ��
    while (1)
    {
        if(low == high)   //��ֹ������ѭ��
        {
            return low;
        }
        mid = (low + high) / 2; 
        BE_ReadP(uiBaseAddr+mid*gs_CurveStoreTab[ucType].ucLen,XDATA_RAMZONE,5);   //��ȡ����ָ���ʱ��
        ucResut=CmpTm(tm, XDATA_RAMZONE, 5 );
        if (ucResut==  CMP_LT )
        {
            if (low + 1 == high)
            {
//              if(ucEqual == true)
//              {
//                  return 0xffff;
//              }
//              else
                {
                    return low;
                }
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
//              if(ucEqual == true)
//              {
//                  return 0xffff;
//              }
//              else
                {
                    return low;
                }
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
* @function_name: BuildOneCurveFrame
* @function_file: LoadCurve.c
* @����: �����������ɼ�¼����֡
* 
* 
* @����: 
* @param:uclen  
* @param:ucType  
* @param:DesBuff  
* @param:SrcBuff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8  BuildOneCurveFrame(uint8 ucType,uint8*DesBuff,uint8*SrcBuff)
{
    uint8 i;
    uint8 ucOffset;
    DesBuff[0] = 0xA0;
    DesBuff[1] = 0xA0;

    ucOffset=8;
    MemCpy(DesBuff+3, SrcBuff, 5);              //��¼ʱ��

    for (i=0; i<ucType-1; i++)
    {
        DesBuff[ucOffset++] = 0xAA;
    }

    if (ucType==0x01)                           //��һ�ฺ��
    {
        MemCpy(DesBuff+8,SrcBuff+5,2);          //A���ѹ
        MemSet(DesBuff+10,0xFF,4);              //B,C���ѹ
        MemCpy(DesBuff+14,SrcBuff+7,3);         //A�����
        MemSet(DesBuff+17,0xFF,6);              //B,C�����
        MemCpy(DesBuff+23,SrcBuff+10,2);        //Ƶ��
        ucOffset+=17;
    }
    else if (ucType==0x02)                      //�ڶ��ฺ��
    {
        //MemSet(DesBuff+7+ucType,0xFF,3);      //�����
        MemCpy(DesBuff+7+ucType,SrcBuff+5,3);   //�����
//      MemCpy(DesBuff+10+ucType,SrcBuff+5,3);  //A���
//      MemSet(DesBuff+13+ucType,0xFF,18);      //B,C��ʣ���ABC�޹�����
        MemSet(DesBuff+10+ucType,0xFF,21);      //B,C��ʣ���ABC�޹�����
        ucOffset+=24;
    }
    else if (ucType==0x03)                      //�����ฺ��
    {
//      MemSet(DesBuff+7+ucType,0xFF,2);        //���������
        MemCpy(DesBuff+7+ucType,SrcBuff+5,2);   //���������
//      MemCpy(DesBuff+9+ucType,SrcBuff+5,2);   //A�������
//      MemSet(DesBuff+11+ucType,0xFF,4);       //B,C�������
        MemSet(DesBuff+9+ucType,0xFF,6);        //A,B,C�������
        ucOffset+=8;
    }
    else if (ucType==0x04)                      //�����ฺ��
    {
        MemCpy(DesBuff+7+ucType,SrcBuff+5,8);   //�й����������
        MemSet(DesBuff+15+ucType,0xFF,8);       //�޹����������
        ucOffset+=16;
    }

    for (i=0; i<7-ucType; i++)
    {
        DesBuff[ucOffset++] = 0xAA;
    }

    DesBuff[2] = ucOffset-3;

    DesBuff[ucOffset++] = DoSum( DesBuff, DesBuff[2]+3 );
    DesBuff[ucOffset] = 0xE5;

    return DesBuff[2] + 5;
}
/*=========================================================================================\n
* @function_name: BuildTotalCurveFrame
* @function_file: LoadCurve.c
* @����: �����ܵĸ��ɼ�¼����֡
* 
* 
* @����: 
* @param:ucTotalType  
* @param:s_TotalCurve  
* @param:Desbuff  
* @param:SrcBuff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 BuildTotalCurveFrame(S_CURVETOTAL *s_TotalCurve,uint8 *buff)
{
    uint8 ucTypeLen;
    uint8 ucTotalType;
    uint8 *p;
    uint16 *uiPt;
    uint8 i;
    uint8 ucOffset,ucOffset1;

    ucTotalType=(s_TotalCurve->ucType&guc_LoadCurveMode);
    if(ucTotalType == 0)
    {
        return 0;
    }
    p=XDATA_RAMZONE;
    //���ݵ�ǰ����ģʽ�ֺʹ洢ʱģʽ�֣������������ָ�������
    ucTypeLen=0;
    uiPt=(uint16*)&s_TotalCurve->uiOnePt;
    for (i=0;i<4;i++)
    {
        if (ucTotalType&BIT8MAP[i])
        {
            ucTypeLen+=(gs_CurveStoreTab[i+1].ucLen-5);
            BE_ReadP(gs_CurveStoreTab[i+1].uiBaseAddr+(*uiPt)*gs_CurveStoreTab[i+1].ucLen+5,
                     p,
                     gs_CurveStoreTab[i+1].ucLen-5);

            p+=(gs_CurveStoreTab[i+1].ucLen-5);
        }
        uiPt++;
    }

    //���ݸ����ָ������ݣ���֡�ɺϵ�����
    buff[0] = 0xA0;
    buff[1] = 0xA0;

    MemCpy(buff+3, (uint8*)&s_TotalCurve->STm.ucMinute, 5);     //��¼ʱ��

    ucOffset=8;
    ucOffset1=0;

    if (ucTotalType&BIT0)                                       //��һ�ฺ��
    {
        MemCpy(buff+8,XDATA_RAMZONE,2);                         //A���ѹ
        MemSet(buff+10,0xFF,4);                                 //B,C���ѹ
        MemCpy(buff+14,XDATA_RAMZONE+2,3);                      //A�����
        MemSet(buff+17,0xFF,6);                                 //B,C�����
        MemCpy(buff+23,XDATA_RAMZONE+5,2);                      //Ƶ��
        ucOffset=25;
        ucOffset1=7;
    }

    buff[ucOffset++]=0xAA;

    if (ucTotalType&BIT1)                                       //�ڶ��ฺ��
    {
        //MemSet(buff+ucOffset,0xFF,3);                         //�����
        MemCpy(buff+ucOffset,XDATA_RAMZONE+ucOffset1,3);        //�����
//      MemCpy(buff+ucOffset+3,XDATA_RAMZONE+ucOffset1,3);      //A���
//      MemSet(buff+ucOffset+6,0xFF,18);                        //B,C��ʣ���ABC�޹�����
        MemSet(buff+ucOffset+3,0xFF,21);                        //A,B,C��ʣ���ABC�޹�����
        ucOffset+=24;
        ucOffset1+=3;
    }

    buff[ucOffset++]=0xAA;

    if (ucTotalType&BIT2)                                       //�����ฺ��
    {
        //MemSet(buff+ucOffset,0xFF,2);                         //���������
        MemCpy(buff+ucOffset,XDATA_RAMZONE+ucOffset1,2);        //���������
//      MemCpy(buff+ucOffset+2,XDATA_RAMZONE+ucOffset1,2);      //A�������
//      MemSet(buff+ucOffset+4,0xFF,4);                         //B,C�������
        MemSet(buff+ucOffset+2,0xFF,6);                         //A,B,C�������
        ucOffset+=8;
        ucOffset1+=2;
    }

    buff[ucOffset++]=0xAA;

    if (ucTotalType&BIT3)                                       //�����ฺ��
    {
        MemCpy(buff+ucOffset,XDATA_RAMZONE+ucOffset1,8);        //�й����������
        MemSet(buff+ucOffset+8,0xFF,8);                         //�޹����������
        ucOffset+=16;
    }

    for (i=0;i<3;i++)
    {
        buff[ucOffset++]=0xAA;
    }

    buff[2] = ucOffset-3;

    buff[ucOffset++] = DoSum( buff, buff[2]+3 );
    buff[ucOffset] = 0xE5;

    return buff[2] + 5;

}
/*=========================================================================================\n
* @function_name: GetOneOldestRecord
* @function_file: LoadCurve.c
* @����: ��ȡ�ָ����������ݿ�
* 
* 
* @����: 
* @param:ucType  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetOneOldestRecord( uint8 ucType, uint8 ucCnt,uint8 *buff)
{
    uint16 CurPt,OldPt;
    uint32 ulCurveCnt;
    uint16 uiBaseAddr;
    uint8  ucLen;

    ulCurveCnt=0;


    uiBaseAddr=gs_CurveStoreTab[ucType].uiBaseAddr;
    ucLen=gs_CurveStoreTab[ucType].ucLen;

    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,(uint8*)&CurPt,2);               //��ȡ����ָ��
    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr,(uint8*)&ulCurveCnt,3);         //��ȡ�����ܴ���
    
    if(ulCurveCnt > CurveTotalCnt)
    {
        ulCurveCnt = CurveTotalCnt;
    }

    if(ucCnt>=ulCurveCnt)                                   //��ȡ��ƫ����������Ч��¼���� ����0
    {
        return 0;
    }
    
    OldPt = (CurPt + ulCurveCnt - 1)%CurveTotalCnt;

    if(CurPt>OldPt)
    {
      if (ucCnt<=OldPt)
        {
            BE_ReadP(uiBaseAddr+(OldPt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);
        }
        else
        {
            BE_ReadP(uiBaseAddr+(OldPt+CurveTotalCnt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);
        }
    }else
    {
        if (ucCnt<=(OldPt-CurPt))
        {
            BE_ReadP(uiBaseAddr+(OldPt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);
        }
    }
    return BuildOneCurveFrame(ucType,buff,XDATA_RAMZONE);
}

/*=========================================================================================\n
* @function_name: GetTotalOldestRecord
* @function_file: LoadCurve.c
* @����: ��ȡ�ܸ����������ݿ�
* 
* 
* @����: 
* @param:ucCnt  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetTotalOldestRecord(uint8 ucCnt,uint8 *buff)
{
    S_CURVETOTAL s_TotalCurve;
    S_CURVETOTAL1 s_SrcTotalCurve;
    uint16 uiTotalPt;
    uint32 ulCurveCnt;
    uint16 OldPt;
    ulCurveCnt=0;


    BE_ReadP(EEP_ZFHET_PT,(uint8*)&uiTotalPt,2);            //��ȡ�ܸ��ɼ�¼��ǰָ��         
    BE_ReadP(EEP_ZFHETNO,(uint8*)&ulCurveCnt,3);            //��ȡ�ܸ����ܴ���
    
    if(ulCurveCnt > CurveTotalCnt)
    {
        ulCurveCnt = CurveTotalCnt;
    }

    if(ucCnt>=ulCurveCnt)                                   //��ȡ��ƫ����������Ч��¼���� ����0
    {
        return 0;
    }
    
    OldPt = (uiTotalPt + ulCurveCnt - 1)%CurveTotalCnt;

    if(uiTotalPt>OldPt)
    {
      if (ucCnt<=OldPt)
        {
            BE_ReadP(EEP_ZFHET+(OldPt-ucCnt)*11,(uint8*)&s_SrcTotalCurve.STm.ucMinute,11);
        }
        else
        {
            BE_ReadP(EEP_ZFHET+(OldPt+CurveTotalCnt-ucCnt)*11,(uint8*)&s_SrcTotalCurve.STm.ucMinute,11);
        }
    }else
    {
        if (ucCnt<=(OldPt-uiTotalPt))
        {
            BE_ReadP(EEP_ZFHET+(OldPt-ucCnt)*11,(uint8*)&s_SrcTotalCurve.STm.ucMinute,11);
        }
    }

    ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);   //�ָ�ָ��

    return BuildTotalCurveFrame(&s_TotalCurve,buff);
}
/*=========================================================================================\n
* @function_name: GetOneTmRecord
* @function_file: LoadCurve.c
* @����: ���������ʱ�为�ɼ�¼��
* 
* 
* @����: 
* @param:ucType 
* @param:Tm  
* @param:ucCnt  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetOneTmRecord(uint8 ucType,uint8 *Tm,uint8 *buff)
{
    uint16 uiPosition;
    uint16 CurPt;

    uiPosition=SearchEqualItem((uint8 const *)Tm, ucType, true);

    if (uiPosition==0xffff)      //�Ҳ���������
    {
        return 0;
    }
    else
    {
        gs_CurveFollowFrame.LastCurvePt=uiPosition;
    }

    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,(uint8*)&CurPt,2);                    //��ȡ����ָ��

    if (uiPosition==CurPt)                                      //���ָ��ʱ�������һ�εĻ���û�к���֡
    {
        gs_CurveFollowFrame.SeqFrameEnd=true;
    }



    BE_ReadP(gs_CurveStoreTab[ucType].uiBaseAddr+uiPosition*gs_CurveStoreTab[ucType].ucLen,
             XDATA_RAMZONE,
             gs_CurveStoreTab[ucType].ucLen);
    return BuildOneCurveFrame(ucType,buff,XDATA_RAMZONE);
}
/*=========================================================================================\n
* @function_name: GetOneTmSeqRecord
* @function_file: LoadCurve.c
* @����: ��ȡ����ʱ��ָ��ɺ���֡���ݿ�
* 
* 
* @����: 
* @param:ucType  
* @param:ucCnt  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetOneTmSeqRecord( uint8 ucType, uint8 ucCnt,uint8 *buff)
{
    uint16 CurPt;
    uint16 uiBaseAddr;
    uint8  ucLen;

    uiBaseAddr=gs_CurveStoreTab[ucType].uiBaseAddr;
    ucLen=gs_CurveStoreTab[ucType].ucLen;

    BE_ReadP(gs_CurveStoreTab[ucType].uiPtAddr,(uint8*)&CurPt,2);               //��ȡ����ָ��

    if (gs_CurveFollowFrame.LastCurvePt>CurPt)                                  //����ϴζ�ȡ��ָ����ڵ�ǰָ��Ļ�
    {
        //ֻҪ�ϴζ�ȡ��ָ��Ӷ�ȡ��ƫ���������ڵ�ǰָ�����Ч
        if (gs_CurveFollowFrame.LastCurvePt>=CurPt+ucCnt)
        {
            BE_ReadP(uiBaseAddr+(gs_CurveFollowFrame.LastCurvePt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);

            if (gs_CurveFollowFrame.LastCurvePt<CurPt+ucCnt+1)
            {
                //��һ֡ û�к���֡
                gs_CurveFollowFrame.SeqFrameEnd=true;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {//�ϴζ�ȡ��ָ��С�ڵ�ǰָ�뻰
        if (gs_CurveFollowFrame.LastCurvePt>=ucCnt)
        {
            BE_ReadP(uiBaseAddr+(gs_CurveFollowFrame.LastCurvePt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);
        }
        else
        {
            if ((gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt)>=CurPt+ucCnt)
            {
                BE_ReadP(uiBaseAddr+(gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt-ucCnt)*ucLen,XDATA_RAMZONE,ucLen);

                if ((gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt)<CurPt+ucCnt+1)
                {
                    //��һ֡ û�к���֡
                    gs_CurveFollowFrame.SeqFrameEnd=true;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    return BuildOneCurveFrame(ucType,buff,XDATA_RAMZONE);
}

/*=========================================================================================\n
* @function_name: GetTotalTmRecord
* @function_file: LoadCurve.c
* @����: ��ȡ�ܸ��ɸ���ʱ�����ݿ�
* 
* 
* @����: 
* @param:Tm  
* @param:ucCnt  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetTotalTmRecord(uint8 *Tm,uint8 *buff)
{

    S_CURVETOTAL s_TotalCurve;
    S_CURVETOTAL1 s_SrcTotalCurve;
    uint16 uiPosition;
    uint16 CurPt;

    uiPosition=SearchEqualItem((uint8 const *)Tm, 0, true);

    if (uiPosition==0xffff)                         //�Ҳ���������
    {
        return 0;
    }
    else
    {
        gs_CurveFollowFrame.LastCurvePt=uiPosition;
    }

    BE_ReadP(EEP_ZFHET_PT,(uint8*)&CurPt,2);                    //��ȡ����ָ��

    if (uiPosition==CurPt)                                      //���ָ��ʱ�������һ�εĻ���û�к���֡
    {
        gs_CurveFollowFrame.SeqFrameEnd=true;
    }

    BE_ReadP(EEP_ZFHET+uiPosition*11,(uint8*)&s_SrcTotalCurve.STm.ucMinute,11);
    ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);
    return BuildTotalCurveFrame(&s_TotalCurve,buff);
}
/*=========================================================================================\n
* @function_name: GetTotalTmSeqRecord
* @function_file: LoadCurve.c
* @����: ��ȡָ��ʱ�����֡
* 
* 
* @����: 
* @param:ucCnt  
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetTotalTmSeqRecord(uint8 ucCnt,uint8 *buff)
{
    S_CURVETOTAL s_TotalCurve;
    S_CURVETOTAL1 s_SrcTotalCurve;
    uint16 uiTotalPt;

    BE_ReadP(EEP_ZFHET_PT,(uint8*)&uiTotalPt,2);            //��ȡ�ܸ��ɼ�¼��ǰָ��         

    if (gs_CurveFollowFrame.LastCurvePt>uiTotalPt)
    {
        if (gs_CurveFollowFrame.LastCurvePt>=uiTotalPt+ucCnt)
        {
            BE_ReadP(EEP_ZFHET+(gs_CurveFollowFrame.LastCurvePt-ucCnt)*11,
                     (uint8*)&s_SrcTotalCurve.STm.ucMinute,
                     11);

            //ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);

            if ((gs_CurveFollowFrame.LastCurvePt)<uiTotalPt+ucCnt+1)
            {
                //��һ֡ û�к���֡
                gs_CurveFollowFrame.SeqFrameEnd=true;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (gs_CurveFollowFrame.LastCurvePt>=ucCnt)
        {
            BE_ReadP(EEP_ZFHET+(gs_CurveFollowFrame.LastCurvePt-ucCnt)*11,
                     (uint8*)&s_SrcTotalCurve.STm.ucMinute,
                     11);
            //ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);
        }
        else
        {
            if ((gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt)>=uiTotalPt+ucCnt)
            {
                BE_ReadP(EEP_ZFHET+(gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt-ucCnt)*11,
                         (uint8*)&s_SrcTotalCurve.STm.ucMinute,
                         11);

                //ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);

                if ((gs_CurveFollowFrame.LastCurvePt+CurveTotalCnt)<uiTotalPt+ucCnt+1)
                {
                    //��һ֡ û�к���֡
                    gs_CurveFollowFrame.SeqFrameEnd=true;
                }
            }
            else
            {
                return 0;
            }
        }
    }

    ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);
    return BuildTotalCurveFrame(&s_TotalCurve,buff);
}

/*=========================================================================================\n
* @function_name: GetOneItemRecord
* @function_file: LoadCurve.c
* @����: ��ȡ���1�����ɼ�¼
* 
* 
* @����: 
* @param:ucType   ��������
* @param:buff   
* 
* @����: 
* @return: 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetOneItemRecord( uint8 ucType, uint8 *buff)
{

    uint32 ulCurveCnt;
    //��ȡ�������ʹ������������1�βż���
    ulCurveCnt=0;
    BE_ReadP(gs_CurveStoreTab[ucType].uiCntAddr,(uint8*)&ulCurveCnt,3);
    if (ulCurveCnt>0)
    {
        DataProcRead2Slice(ZFHJLID+ucType,0,0,14,XDATA_RAMZONE);
        return BuildOneCurveFrame(ucType,buff,XDATA_RAMZONE);
    }
    else
    {
        return 0;
    }
}
/*=========================================================================================\n
* @function_name: GetTotalItemRecord
* @function_file: LoadCurve.c
* @����: ��ȡ�ܸ��ɵ����һ�θ��ɼ�¼
* 
* 
* @����: 
* @param:buff  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 GetTotalItemRecord(uint8 *buff)
{
    S_CURVETOTAL s_TotalCurve;
    S_CURVETOTAL1 s_SrcTotalCurve;
    uint8 i;
    uint16 *Pt;

    DataProcRead2Slice(ZFHJLID,0,0,11,(uint8*)&s_SrcTotalCurve);               //��ȡ��ǰָ��������

    ReCoverPoint(&s_TotalCurve,&s_SrcTotalCurve);

    Pt=(uint16*)&s_TotalCurve.uiOnePt;
    for (i=0;i<4;i++)
    {
        Pt[i]%=CurveTotalCnt;
    }
    return BuildTotalCurveFrame(&s_TotalCurve,buff);

}


/*=========================================================================================\n
* @function_name: LoadCurveCheck
* @function_file: LoadCurve.c
* @����: 
* 
* 
* @����: 
* @param:Tm  
* @param:buff  
* @����: 
* @����:   lm (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void LoadCurveCheck(void)
{
    uint8 i,j;
    uint16 uiPosition;
    uint32 ulCurveCnt;
    uint16 uiTotalPt;
    uint8 buff[20];
     
    MemCpy(XDATA_RAMZONE1,&gs_DateTime.ucMinute,5);    //д��ʱ��
    if(guc_Timechange == 0x55)    //����ʱ��ı�
    {          
        for(i=0;i<5;i++)
        {                
            uiPosition=SearchEqualItem((uint8 const *)XDATA_RAMZONE1, i, false);
            if(uiPosition == 0xffff)                                                //�ı�ʱ��С������ʱ��
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
                    BE_WriteP(gs_CurveStoreTab[0].uiBaseAddr, buff, gs_CurveStoreTab[0].ucLen);    //�帺�ɼ�¼
                    break;
                }
                ulCurveCnt=0;
                uiTotalPt=0;
                BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);   //
                BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);     //                  
            }
            else if(uiPosition != 0xff00)                                           //��ǰ�޸ĵ�ʱ��,�ڸ��ɼ�¼�д����м䡣
            {
                ulCurveCnt = 0;
                BE_ReadP(gs_CurveStoreTab[i].uiCntAddr,(uint8*)&ulCurveCnt,3);      //��ȡ�����ܴ���
                BE_ReadP(gs_CurveStoreTab[i].uiPtAddr,(uint8*)&uiTotalPt,2);        //��ȡ���ɼ�¼��ǰָ��

                if(ulCurveCnt>CurveTotalCnt)                                        //����¼�ĸ��ɴ�������E2�洢�ĸ�����Ч����
                {
                    ulCurveCnt=CurveTotalCnt;                                       //���ɼ�¼�����޸ĳ�E2�洢����Ч���ɴ���
                }
                
               /*if(uiPosition==uiTotalPt)
                {
                
                
                    continue;
                }
                else */if(uiPosition>=uiTotalPt)                                            //��ǰʱ��λ�ô��ڵ�ǰ���ɼ�¼ָ��      
                {
                    ulCurveCnt=ulCurveCnt-1-(uiPosition-uiTotalPt);                 //������Ч��������
                }
                else if(uiPosition<uiTotalPt)
                {                                      
                    ulCurveCnt=ulCurveCnt-1-(CurveTotalCnt+uiPosition-uiTotalPt);
                }
               

                BE_ReadP(gs_CurveStoreTab[i].uiBaseAddr+uiPosition*gs_CurveStoreTab[i].ucLen,XDATA_RAMZONE,5);

                if(CMP_EQU==CmpTm(XDATA_RAMZONE1, XDATA_RAMZONE, 5 ))               //����ʱ����λ��ʱ�����
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
            
        }
        guc_Timechange = 0;
    }
}
/*=========================================================================================\n
* @function_name: LoadCurveSave
* @function_file: LoadCurve.c
* @����: 
* 
* 
* @����: 
* @param:Tm  
* @param:buff  
* @����: 
* @����:   lm (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void LoadCurveSave(void)
{
    S_CURVETOTAL Curve_Pt;
    S_CURVETOTAL1 Curve_SrcPt;
    uint32 temp_value;
    uint8 uc_SaveType;
    uint32 ul_Min;
    uint8 i;
    uint16 *pTime;
    uint16 uiHighBit;
//    uint16 uiPosition;
//    uint32 ulCurveCnt;
//    uint16 uiTotalPt;
    uint8 *SrcPt;
    uint16 *DesPt;
    
   
    uc_SaveType = 0;
    ul_Min=(uint32)CalcAbsDay((S_TIMEDATA*)&gs_DateTime)*((uint32)1440)
           + ((uint16)APIByteBCD2HEX(gs_DateTime.ucHour)*((uint16)60))
           + APIByteBCD2HEX(gs_DateTime.ucMinute)
           - gul_LoadCurveMin;
//  if(ul_Min == 0)
//  {
//      return;
//  }
//    ul_Min = APIByteBCD2HEX(gs_DateTime.ucMinute);
    pTime=(uint16*)&gs_LoadCurveTime.uiFH1;

    if(guc_LoadCurveMode)
    {
        for (i=0;i<4;i++)
        {
            if ( (ul_Min%pTime[i]== 0) 
                 && (guc_LoadCurveMode&BIT8MAP[i]))
            {
                uc_SaveType |= BIT8MAP[i];
            }
//            guc_LoadCurveCnt[i]++;
//            if((guc_LoadCurveCnt[i] >= pTime[i]) 
//               && (guc_LoadCurveMode&BIT8MAP[i]))
//            {
//                uc_SaveType |= BIT8MAP[i];
//                guc_LoadCurveCnt[i] = 0;
//            }            
        }
    }

    if(POWERSTATE())            //ϵͳͣ�磬ֱ�ӷ��أ������и��ɼ�¼
    {
        return;
    }

    if (uc_SaveType)
    {
//        MemCpy(XDATA_RAMZONE1,&gs_DateTime.ucMinute,5);    //д��ʱ��
        //���Ӹ���ʱ���ж�
        LoadCurveCheck();
//        if(guc_Timechange == 0x55)    //����ʱ��ı�
//        {          
//            for(i=0;i<5;i++)
//            {                
//                uiPosition=SearchEqualItem((uint8 const *)XDATA_RAMZONE1, i, false);
//                if(uiPosition == 0xffff)                                                //�ı�ʱ��С������ʱ��
//                {
//                    ulCurveCnt=0;
//                    uiTotalPt=0;
//                    BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);   //
//                    BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);     //
//                }
//                else if(uiPosition != 0xff00)                                           //��ǰ�޸ĵ�ʱ��,�ڸ��ɼ�¼�д����м䡣
//                {
//                    ulCurveCnt = 0;
//                    BE_ReadP(gs_CurveStoreTab[i].uiCntAddr,(uint8*)&ulCurveCnt,3);      //��ȡ�����ܴ���
//                    BE_ReadP(gs_CurveStoreTab[i].uiPtAddr,(uint8*)&uiTotalPt,2);        //��ȡ���ɼ�¼��ǰָ��
//
//                    if(ulCurveCnt>CurveTotalCnt)                                        //����¼�ĸ��ɴ�������E2�洢�ĸ�����Ч����
//                    {
//                        ulCurveCnt=CurveTotalCnt;                                       //���ɼ�¼�����޸ĳ�E2�洢����Ч���ɴ���
//                    }
//
//                    if(uiPosition>=uiTotalPt)                                            //��ǰʱ��λ�ô��ڵ�ǰ���ɼ�¼ָ��      
//                    {
//                        ulCurveCnt=ulCurveCnt-1-(uiPosition-uiTotalPt);                 //������Ч��������
//                    }
//                    else if(uiPosition<uiTotalPt)
//                    {                                      
//                        ulCurveCnt=ulCurveCnt-1-(CurveTotalCnt+uiPosition-uiTotalPt);
//                    }
//                    
//                    uiTotalPt=(uiPosition+1)%CurveTotalCnt; 
//                    
//                    BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&uiTotalPt, 2);             //
//                    BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulCurveCnt, 3);           //
//                }
//                
//            }
//            guc_Timechange = 0;
//        }
//        DataProcRead2Slice(ZFHJLID,0,0,11,(uint8*)&Curve_SrcPt);
//        
//        
//        //�ָ�ָ��
//        //MemCpy(&Curve_Pt,&Curve_SrcPt,6);           //����ʱ��,��ģʽ��
//        SrcPt=&Curve_SrcPt.ucOnePt;
//        DesPt=&Curve_Pt.uiOnePt;
//        uiHighBit=Curve_SrcPt.ucHighBit;
//        for (i=0;i<4;i++)
//        {
//            DesPt[i]=SrcPt[i];
//            uiHighBit<<=2;
//            DesPt[i]|=(uiHighBit&0x0300);
//        }

        MemCpy(XDATA_RAMZONE,&gs_DateTime.ucMinute,5);    //д��ʱ��

        if (uc_SaveType&CurveOneType)
        {
            
//            if (Curve_Pt.uiOnePt == 0)
//            {
//                Curve_Pt.uiOnePt = CurveTotalCnt-1;
//            }
//            else
//            {
//                Curve_Pt.uiOnePt--;
//            }
            temp_value = CalRMS(RMSU);
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,2);
            temp_value = CalRMS(RMSI1);
            MemCpy(XDATA_RAMZONE+7,(uint8*)&temp_value,3);
            temp_value = CalRMS(DATAFREQ);
            MemCpy(XDATA_RAMZONE+10,(uint8*)&temp_value,2); 
            DataProcWriteRound2(R2_MOVE,FH1JLID,XDATA_RAMZONE); 
            DataProcEvCountAdd(FH1NUMID);                   //���Ӹ���1��¼            
        }
        if (uc_SaveType&CurveTwoType)
        {
            
//            if (Curve_Pt.uiTwoPt == 0)
//            {
//                Curve_Pt.uiTwoPt = CurveTotalCnt-1;
//            }
//            else
//            {
//                Curve_Pt.uiTwoPt--;
//            }
            temp_value = CalRMS(DATAP);
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,3);

            DataProcWriteRound2(R2_MOVE,FH2JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH2NUMID);                   //���Ӹ���2��¼
        }
        if (uc_SaveType&CurveThreeType)
        {           
//            if (Curve_Pt.uiThreePt == 0)
//            {
//                Curve_Pt.uiThreePt = CurveTotalCnt-1;
//            }
//            else
//            {
//                Curve_Pt.uiThreePt--;
//            }
            temp_value = CalCos();
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,2);

            DataProcWriteRound2(R2_MOVE,FH3JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH3NUMID);                   //���Ӹ���3��¼
        }
        if (uc_SaveType&CurveFourType)
        {
            
//            if (Curve_Pt.uiFourPt == 0)
//            {
//                Curve_Pt.uiFourPt = CurveTotalCnt-1;
//            }
//            else
//            {
//                Curve_Pt.uiFourPt--;
//            }

            temp_value = gs_EnergyA.ulP[0];
            temp_value += Eny_GetEp1(1, 0);
            temp_value/=10;
            temp_value = Hex2BCD(temp_value);             //ת��ΪBCD��
            MemCpy(XDATA_RAMZONE+5,(uint8*)&temp_value,4);

            temp_value = gs_EnergyA.ulN[0];
            temp_value += Eny_GetEp1(2, 0);
            temp_value/=10;
            temp_value = Hex2BCD(temp_value);             //ת��ΪBCD��
            MemCpy(XDATA_RAMZONE+9,(uint8*)&temp_value,4);

            DataProcWriteRound2(R2_MOVE,FH4JLID,XDATA_RAMZONE);
            DataProcEvCountAdd(FH4NUMID);                   //���Ӹ���1��¼
        }

        MemCpy((uint8*)&Curve_SrcPt,XDATA_RAMZONE,5);    //д��ʱ��
        Curve_SrcPt.ucType = uc_SaveType;
        
        for(i=1;i<5;i++)
        {   
            BE_ReadP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&Curve_Pt.uiOnePt+(i-1)*2, 2);     // 
        }        

        //����ָ��
        SrcPt=&Curve_SrcPt.ucOnePt;
        DesPt=&Curve_Pt.uiOnePt;
        uiHighBit=0;
        for (i=0;i<4;i++)
        {
            uiHighBit<<=2;
            SrcPt[i]=DesPt[i];
            DesPt[i]>>=8;
            uiHighBit |= (DesPt[i]&0x03);

        }
        Curve_SrcPt.ucHighBit=uiHighBit;
        DataProcWriteRound2(R2_MOVE,ZFHJLID,(uint8*)&Curve_SrcPt);
        DataProcEvCountAdd(ZFHNUMID);                //�����ܸ��ɼ�¼
    }
}

/*=========================================================================================\n
* @function_name: RecoverLoadCurve
* @function_file: LoadCurve.c
* @����: 
* 
* 
* @����: 
* @param:Tm  
* @param:buff  
* @����: 
* @����:   lm (2013-02-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void RecoverLoadCurve(void)
{
    uint8 uc_LoadCurveMode;
    
    uc_LoadCurveMode = guc_LoadCurveMode;
    
    SysE2ReadData(EEP_FHJLMSZ,(uint8*)&guc_LoadCurveMode,1);       //ˢ�¸�������ģʽ��
    SysE2ReadData(EEP_FHJL1JG,(uint8*)&gs_LoadCurveTime,8);        //ˢ�¸��ɼ�¼����1���    
    SysE2ReadData(EEP_FHJLTIME,(uint8*)&gs_StartLoadCurve,5);      //ˢ�¸��ɼ�¼��ʼʱ��
    
    if(guc_LCTimeFlag == 0xAA && uc_LoadCurveMode != guc_LoadCurveMode)
    {        
        uint8 i;
        uint32 ulPt=0;
        
        for(i=0;i<5;i++)
        {     
            BE_WriteP(gs_CurveStoreTab[i].uiCntAddr, (uint8*)&ulPt, 3);   //�帺�ɼ�¼
            BE_WriteP(gs_CurveStoreTab[i].uiPtAddr, (uint8*)&ulPt, 2);    //�帺�ɼ�¼
        }
        //gui_RefreshEvent |= flgEtPara_Fee;
        //guc_LCTimeFlag = 0;
    }
    
    if(guc_LCTimeFlag == 0x55)
    {
        S_TIMEDATA s_Datatime;
        MemSet((uint8*)&s_Datatime,0x00,9);
        MemCpy((uint8*)&s_Datatime.ucMinute,(uint8*)&gs_StartLoadCurve.ucMinute,5);
        gul_LoadCurveMin=(uint32)CalcAbsDay((S_TIMEDATA*)&s_Datatime)*((uint32)1440)
         + ((uint16)APIByteBCD2HEX(gs_StartLoadCurve.ucHour)*((uint16)60))
         + APIByteBCD2HEX(gs_StartLoadCurve.ucMinute);
    }
    guc_LCTimeFlag = 0;    
}
#endif
