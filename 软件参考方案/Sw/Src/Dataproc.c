 
#define AP_DATAPROC_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: CheckCRCWord
* @function_file: Dataproc.c
* @����: �������״̬���Ƿ���ȷ
* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-06-06)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
* @����: ����������״̬��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-06)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
* @����: ���õ������״̬��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-06)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
* @����: ����
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Data_ClearMeter(void)
{
    uint8 i;
    if(CheckCRCWord(guc_InitWd))
    {
        ClRCRCWord(guc_InitWd);
 
        MemSet(XDATA_RAMZONE,0x00,64);          //�������ⲿRAM
        //����
        for(i=0;i<12;i++)                                       //����ʷ�������¼�
        {
            CLRWDT();               //ι��
            BE_WriteP(EEP_EPHIS_PT+64*i,XDATA_RAMZONE,64);     
        }

 
        Eny_EnergyClrCur(ENERGY_CLR);                               //�����ǰ����
        MemSet((uint8*)&gs_PowerCf,0,sizeof(S_POWERCF));            //������
        MemSet((uint8*)&gs_Energy,0,sizeof(S_ENERGY));              //��������
//        DemandClrCur();
        InitDemand();
        SleepTimeProc();                                            //��RTC��ȡʱ�ӵ�RAM��
    }
}
/*=========================================================================================\n
* @function_name: Data_HourProc
* @function_file: Dataproc.c
* @����: Сʱ����
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Data_HourProc(void)
{
    //�������մ���
    EnergyCBRManage();
    //������������
}
/*=========================================================================================\n
* @function_name: Data_MinProc
* @function_file: Dataproc.c
* @����: ���ݴ���ķ��Ӵ���
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
    getFee();       //ÿ����ˢ�·���
//  E2ParaCheck();  //E2���
}
/*=========================================================================================\n
* @function_name: DataProcWriteRound2
* @function_file: Dataproc.c
* @����:
*
*
* @����:
* @param:ucRound    0��ʾָ�벻��Ҫ�ƶ�,�����ʾָ����Ҫ�����ƶ�
* @param:ucPos      ��������,���Ʊ�2�е�λ��,��Ӧһ����������
* @param:pucBuf     ���ݻ���,����Ч���ݳ����ɾ��Ʊ�2�е��������ָ��,�������Ʊ�ʱȷ������ȷ
* @����:
* @����:   lwb (2012-04-06)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void DataProcWriteRound2(uint8 ucRound, uint8 ucPos, uint8* pucBuf)
{
    uint8   ucPt;                       //ָ��
    uint16  uiAddr;                     //E2��ַ
    S_ROUND2 code* psR2;                     //ָ����Ʊ�1ĳһ����Ԫ��ָ��
       
    if(ucPos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
    {
        return;
    }
    ucPt=0;
    
    psR2 = (S_ROUND2 code*)&gCs_Round2Tab +ucPos;

    BE_ReadB(psR2->uiPtAddr, (uint8*)&ucPt);    //ָ��


    if(ucRound != R2_NO_MOVE)
    {//��Ҫ����ƶ�һλ
        if(ucPt == 0)
        {
            ucPt = psR2->ucMod - 1;
        }
        else
        {
            ucPt--;
        }
    }
    ucPt %= psR2->ucMod;                //�õ���Ҫ���ҵ��¼�ָ��,ʵ��Ϊ���ݱ���

    uiAddr = psR2->uiDataAddr + ucPt * psR2->ucLen;

    BE_WriteP(uiAddr, pucBuf, psR2->ucLen);
    if(ucRound != R2_NO_MOVE)
    {
        BE_WriteP(psR2->uiPtAddr, (uint8*)&ucPt,1);//д��ָ������
    }
}
/*=========================================================================================\n
* @function_name: DataProcRead2Slice
* @function_file: Dataproc.c
* @����:
*
*
* @����:
* @param:ucR2Pos  ��������,���Ʊ�2�е�λ��,��Ӧһ����������
* @param:ucCnt    ǰ�ڼ�������  0���һ��/1���ϴ�/...
* @param:ucOffset  �ڶ�Ӧ���ݿ��е�ƫ��,��λ���ֽ�
* @param:ucLen      ��Ҫ��ȡ�����ݳ���
* @param:pucBuf  ���ݻ���,����Ч���ݳ����ɾ��Ʊ�2�е��������ָ��,�������Ʊ�ʱȷ������ȷ
* @����:
* @����:   lwb (2012-04-06)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void DataProcRead2Slice(uint8 ucR2Pos, uint8 ucCnt, uint8 ucOffset, uint8 ucLen, uint8* pucBuf)
{
    uint8   ucPt;                       //ָ��
    uint16  uiAddr;                     //E2��ַ
    S_ROUND2 code* psR2;                     //ָ����Ʊ�1ĳһ����Ԫ��ָ��

    if(ucR2Pos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
    {
        return;
    }
    
    ucPt=0;
    
    psR2 = (S_ROUND2 code*)&gCs_Round2Tab + ucR2Pos;
 
    BE_ReadP( psR2->uiPtAddr, (uint8*)&ucPt,1);//��ȡָ��
 
    ucPt += ucCnt;
    ucPt %= psR2->ucMod;                //�õ���Ҫ���ҵ��¼�ָ��,ʵ��Ϊ���ݱ���

    uiAddr = psR2->uiDataAddr + ucPt * psR2->ucLen + ucOffset;

    BE_ReadP(uiAddr, pucBuf, ucLen);
}

/*=========================================================================================\n
* @function_name: Data_DayProc
* @function_file: Dataproc.c
* @����: �촦��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void Data_DayProc(void)
//{
//    gui_SystemState &= ~flgStSys_IsTodayJS;         //ȥ���Ѿ����й��㲥Уʱ���
//}
/*=========================================================================================\n
* @function_name: CalPowDwTm
* @function_file: Dataproc.c
* @����: �������ʱ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void CalPowDwTm(void)
//{
//    uint32 ul_SecTm;
//    uint32 ul_MinTm;
//    InitCLRWDT();               //ι��
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);                //��ȡ���һ�ε����¼
//    BE_ReadP(EEP_PRODUCELEFTTM,(uint8*)&gui_DyProDmOut,0x02);       //����ʣ��ʱ��
//    BE_ReadP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);             //��ȡ���ʣ��ʱ��
//    BE_ReadP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x04);  //��ȡ����ʱ��
//    BE_ReadP(EEP_POWERDWTM,(uint8*)&gul_PowerTm,4);                 //ͣ��ʱ��
//    if(XDATA_RAMZONE[3+6]!=XDATA_RAMZONE[3])                         //�ж��Ƿ����
//    {
//        gui_SystemState &= ~flgStSys_IsTodayJS;                     //ȥ���Ѿ����й��㲥Уʱ���
//    }
//
//    ul_SecTm=CalcTimeGap((S_TIMEDATA*)(XDATA_RAMZONE+6),(S_TIMEDATA*)XDATA_RAMZONE);
//    ul_MinTm=ul_SecTm/60;
//    gul_PowerTm+=ul_MinTm;
//    if(ul_MinTm==0)                                                 //������µ�С�ڷ��ӣ��ж�ʵ����ʱ�Ƿ���֣��������1��
//    {
//        if(XDATA_RAMZONE[7]!=XDATA_RAMZONE[1])
//        {
//            ul_MinTm=1;
//        }
//    }
//
//    if(ul_MinTm>=gui_DyPgmOut)                                      //���ʱ��
//    {
//        gui_DyPgmOut=0;
//        gui_SystemState &= ~flgStSys_Program;                       // ���ñ��״̬��־
//        gs_MeterState.ui_MeterState3.RunCode3Word.Program=false;
//
//    }else
//    {
//        gui_SystemState|=flgStSys_Program;
//        gs_MeterState.ui_MeterState3.RunCode3Word.Program=true;
//        gui_DyPgmOut-=ul_MinTm;
//    }
//
//    BE_WriteP(EEP_PRGLEFTTM,(uint8*)&gui_DyPgmOut,0x02);    //д����ʣ��ʱ��
//
//    BE_ReadP(EEP_PRODUCE,(uint8*)&guc_FactoryType,1);        //��ȡ�볧��״̬
//    if(guc_FactoryType==FactorMd)                           //��ȡ����״̬
//    {
//        if(ul_MinTm>=gui_DyProDmOut)                        //����ʱ��
//        {
//            gui_DyProDmOut=0;
//            guc_FactoryType=0;                              // �˳�����״̬
//        }else
//        {
//            guc_FactoryType=FactorMd;
//            gui_DyProDmOut-=ul_MinTm;
//        }
//        BE_WriteP(EEP_PRODUCELEFTTM,(uint8*)&gui_DyProDmOut,0x02);  //����ʣ��ʱ��
//        SysE2ParaSetManage(EEP_PRODUCE,(uint8*)&guc_FactoryType,1);  //д�볧��״̬
//    }
//
//    if(gs_PassWordCtr.ucSt02==BSST && ul_MinTm>=gs_PassWordCtr.uiDyPW2Out)
//    {
//        gs_PassWordCtr.uiDyPW2Out=0;            //����ʱ������
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
//        gs_PassWordCtr.uiDyPW4Out=0;            //����ʱ������
//        gs_PassWordCtr.ucSt04=0;
//        gs_PassWordCtr.ucPW4ErrCnt=0;
//
//    }else
//    {
//        gs_PassWordCtr.uiDyPW4Out-=ul_MinTm;
//    }
//    //����ʱ��
//    BE_WriteP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x04);    //д�����ʣ��ʱ��
//}

/*=========================================================================================\n
* @function_name: RecoverJSRData
* @function_file: Dataproc.c
* @����: �ϵ粹������
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);    //��ȡ���һ�ε����¼
//
//    MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);        //��ȡ����ʱ��
//
//    BE_ReadP(EEP_CBR1,W16_JSR[0].byte, 6);              //��ȡ3��������
//                                                        //ȥ����ͬ�ĳ�����
//    for(i=0;i<2;i++)
//    {
//        for(j=i+1;j<3;j++)
//        {
//            if(W16_JSR[i].word==W16_JSR[j].word)
//            {
//                W16_JSR[j].word=0x9999;
//            }else                                       //�Ƚϴ�С��С������ǰ
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
//    for(i=0;i<3;i++)                          //�ж���Ч�����ո���
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
//    //��ȡ������
//    for(i=0;i<JSRflg;i++)
//    {
//       if(W16_JSR[i].word==0x9999)
//       {
//           continue;
//       }
//
//       ucDay=W16_JSR[i].byte[1];
//       ucHour=W16_JSR[i].byte[0];
//       //�жϹ�ȥ����������
//       CbrCnt+=CalCBRCount(&LastCbrTm.ucMinute,&gs_DateTime.ucMinute,ucDay,ucHour);
//       if(i==0)             //��һ�������ղ�������
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
//    MemCpy((uint8*)CurTime.byte,(uint8*)&gs_DateTime.ucHour,4); //������ǰʱ��
//
//    CurJSRcnt=JudgeJSR(CurTime.byte,W16_JSR[0].byte,JSRflg);       //�ж���Ҫ���ĸ������տ�ʼ
//
//    for(i=0;i<CbrCnt;i++)
//    {
//      if(CurJSRcnt == 0)
//      {                                                       //�������1����
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
//        MemCpy(XDATA_RAMZONE+i*4,CurTime.byte,4);         //�������ʱ��
//        CurJSRcnt--;
//    }
//
//
//    //ת����ٴι�����������
//    while(CbrCnt)
//    {
//        CbrCnt--;
//        WriteHisEP();
//        DataProcWriteRound2(R2_MOVE,JSSJJLID,XDATA_RAMZONE+CbrCnt*4);   //д�����ݣ�����
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
* @����: �ϵ粹�ն���
* 
* @����: 
* @����: 
* @����:   lm (2012-12-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
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
//    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);                //��ȡ���һ�ε����¼
//
//    MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);            //��ȡ����ʱ��
//
//    BE_ReadP(EEP_RFREEZTM,RdjTm.byte,2);                    //��ȡ�ն���ʱ��
//
//    ucHour=RdjTm.byte[1];
//    ucMin=RdjTm.byte[0];
//    CurTime.ucDay=gs_DateTime.ucDay;
//    CurTime.ucMonth=gs_DateTime.ucMonth;
//    CurTime.ucYear=gs_DateTime.ucYear;
//
//           //�жϹ�ȥ�����ն���
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
//        Eadd = Eny_GetEp1(1, i);                            //ȡ��ĳ�����ʵĵ�������
//        data1.lword= gs_EnergyA.ulP[i]+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+5+i*4,(void*)data1.byte,4);    //���� �ܼ��ƽ�ȵ���
//    }
//
//    for(i = 0; i <= 4; i++)
//    {
//        Eadd = Eny_GetEp1(2, i);                            //ȡ��ĳ�����ʵĵ�������
//        data1.lword= gs_EnergyA.ulN[i]+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+25+i*4,(void*)data1.byte,4);   //���� �ܼ��ƽ�ȵ���
//    }
//
//    MemSet(XDATA_RAMZONE+45,0,4);                           //����
//
//    //ת����ٴι��ն�������
//    while(CbrCnt)
//    {
//        CbrCnt--;
//        DataProcEvCountAdd(RDJNUMID);                       //�����ն������
////      StructFreezeDate();
//        MemCpy(XDATA_RAMZONE,(XDATA_RAMZONE1+CbrCnt*5),5);
//        DataProcWriteRound2(R2_MOVE,RDJID,XDATA_RAMZONE);   //д������
//    }
//}
/*=========================================================================================\n
* @function_name: RecoverEnegyData
* @function_file: Dataproc.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-09-27)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void RecoverEnegyData(void)
{
    uint16 CRC;
    BE_ReadP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,9);
    CRC=Uint8_To_Uint16(XDATA_RAMZONE+7);
    if(CRC==do_CRC(XDATA_RAMZONE, 7))                          //���籣��������ȷ
    {
        MemCpy((uint8*)&gs_EnergyData.uiEP,XDATA_RAMZONE,4);    //�ָ���������

        MemCpy((uint8*)&gs_FeeData.uc_FeeNo,XDATA_RAMZONE+6, 1);//��ǰ����
 
        Eny_EnergyActiveSave();                                 //�������

        MemCpy((uint8*)&gs_PowerCf.uc_P,XDATA_RAMZONE+4,1);     //��ǰCF��
        MemCpy((uint8*)&gs_Energy.ucP, XDATA_RAMZONE+5, 1);     //��ǰCF���ڵ�����

        CRC=0;
        BE_WriteP(EEP_POWDWENERGY+7,(uint8*)&CRC,2);           //ʹ����������Ч
    }
    else
    {
        MemSet((uint8*)&gs_PowerCf.uc_P,0,1);                   //��ǰCF��
        MemSet((uint8*)&gs_Energy.ucP, 0, 1);                   //��ǰCF���ڵ�����
    }

//  Eny_EnergyActiveSave();                                 //�������

    gui_SystemState &= ~flgStSys_PowOff;
}
/*=========================================================================================\n
* @function_name: JudgeCurTime
* @function_file: Dataproc.c
* @����: �жϵ�ǰʱ�����޹��ն���ʱ�䡣��û������ʱ�䣬����true��
* 
* 
* @����: 
* @param:CurTime  
* @param:RdjTime  
* 
* @����: 
* @return: uint8 
* @����:   xuqf (2013-3-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//uint8 JudgeCurTime(uint8* CurTime,uint8* RdjTime)
//{
//    if(*(CurTime+1) < *(RdjTime+1))             //�ж�ʱ�������ǰhourС���ն���hour
//    {
//        return true;
//    }else
//    {
//        if(*(CurTime+1) == *(RdjTime+1))        //��hour���
//        {
//            if(*CurTime < *RdjTime)             //�ж�Minute
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
* @����: д������
* 
* 
* @����: 
* @param:CurTime  
* @param:time  
* @param:pucBuf  
* @����: 
* @����:   xuqf (2013-3-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void WriLastDJTime(S_CURTIME *CurTime,uint8* time,uint8* pucBuf)
//{
//    CurTime->ucMinute = *time;                    //�ն���ķ�
//    CurTime->ucHour = *(time+1);                  //�ն����ʱ
//    MemCpy(pucBuf,&CurTime->ucMinute,5);
//}
/*=========================================================================================\n
* @function_name: CalDayBack
* @function_file: Dataproc.c
* @����: ��ǰ��һ���жϣ��������꣬����
* 
* 
* @����: 
* @param:CurTime  
* @param:offset  
* @����: 
* @����:   xuqf (2013-3-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void CalDayBack(S_CURTIME *CurTime,uint8 offset)
//{
//    uint8 ucData;
//    if(offset)                                //��������Ч����Ҫ��1��
//    {
//        if(CurTime->ucDay>0x01)                  //�ж�day�ǲ��Ǵ���1�ա�����ǣ���1��
//        {
//            ucData=APIByteBCD2HEX(CurTime->ucDay);
//            ucData--;                                                            //����1��
//            CurTime->ucDay = APIByteHEX2BCD(ucData);
//        }else                                 //�������
//        {
//            if(CurTime->ucMonth > 0x01)          //�ж��·��ǲ���1�¡��������
//            {
//                ucData=APIByteBCD2HEX(CurTime->ucMonth);
//                ucData--;                                                            //����1��
//                CurTime->ucMonth = APIByteHEX2BCD(ucData);
//
//                if(((APIByteBCD2HEX(CurTime->ucYear) & 0x03) == 0)&& CurTime->ucMonth == 0x02)
//                {//�жϵ�ǰ���ǲ��������2�·�
//                    CurTime->ucDay = MonthDays[CurTime->ucMonth] + 1; //�����1��
//                }else
//                {
//                    CurTime->ucDay = MonthDays[CurTime->ucMonth];
//                }
//                CurTime->ucDay=APIByteHEX2BCD(CurTime->ucDay);
//            }else                             //�����1�£���1��1�գ�
//            {
//
//                ucData=APIByteBCD2HEX(CurTime->ucYear);
//                ucData--;                                                            //����1��
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
* @����: �жϵ�ǰʱ��������ձȽ�
* 
* 
* @����: 
* @param:CurTime  
* @param:JSRTime  
* @param:flg  
* 
* @����: 
* @return: uint8 
* @����:   lwb (2013-03-06)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//uint8 JudgeJSR(uint8* CurTime,uint8* JSRTime,uint8 flg)
//{
//    uint8 i;
//    for(i=0;i<flg;i++)
//    {
//        if(*(CurTime+1) < *(JSRTime+1+i*2))         //�ж���
//        {
//            return i;
//        }else
//        {
//            if(*(CurTime+1) == *(JSRTime+1+i*2))    //��Day���
//            {
//                if(*CurTime < *(JSRTime+i*2))       //�ж�Hour
//                {
//                    return i;                       //
//                }
//            }
//        }
//    }
//
//    return flg;
//}
