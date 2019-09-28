 
#define AP_DATAPROC_EXT
#include "Include.h"

void RecoverRunPara(void)
{
    //�ָ����״̬
    //�̵���״̬
    //����״̬
}

/*=========================================================================================\n
* @function_name: Data_RecPara
* @function_file: Dataproc.c
* @����: �ָ�����
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-30)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Data_RecPara(void)
{        
//  CLRWDT();               //ι��
    RecoverCfg();           //�ָ�������
//#ifdef LOADCURVE
//    RecoverLoadCurve();     //�ָ�������������
//#endif

//  CLRWDT();               //ι��
    RecoverEnergyData();     //�ָ���������

//  CLRWDT();               //ι��
//    RecoverRtcPara();       //�ָ�RTC����

//  CLRWDT();               //ι��
//    RecoverRunPara();       //�ָ�����״̬��

//  CLRWDT();               //ι��    
//    if(guc_ClockErr!=CLOCKERR)
//    {
//        RecoverJSRData();   //�ϵ粹������
////        CLRWDT();           //ι��
//        RecoverDayDjData(); //�ϵ粹�ն���
//    }
//    guc_ClockErr=0;
//  CLRWDT();
}
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
    uint8 i;
    for(i=0;i<10;i++)
    {
        WrodSt[i]=55;
    }
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
#ifdef _DEL
//    uint8 i,j;
    if(CheckCRCWord(guc_ClearWd))
    {
        ClRCRCWord(guc_ClearWd);
//        Disp_SysClr();
        gs_DispStt.ucMode = Const_DispMode_AdvSysClr;
        gs_DispStt.ucTmr = 3;
        MemSet(XDATA_RAMZONE,0x00,64);          //�������ⲿRAM 
            //����������������
            gut_SysWarn.byte=0;                                                 //�澯������

            //MemSet((uint8*)&gs_MeterState.ui_MeterState1.Word,0x00,sizeof(METERSTATE));
//            if(gui_SystemState&flgStSys_Program)
//            {
//                gs_SysRunSt.Prog = true;
//            }

//            if(gs_FeeData.uc_FeeRSDN==0x02)
//            {
//                gs_MeterState.ui_MeterState3.RunCode3Word.RateTable=true;       //�޸ĵ��״̬�֣�ʹ�õڶ���ʱ��
//            }
//            if(gs_FeeData.uc_FeeSQN==0x02)
//            {
//                gs_MeterState.ui_MeterState3.RunCode3Word.TimeZoneTable=true;  //�޸ĵ��״̬�֣�ʹ�õ�һ��ʱ��  
//            }
//
//            gui_RefreshEvent|=flgEtPara_Fee;
//        }
        guc_CoverStatus=0;
//        guc_PoweroffCoverJl=0x55;
        guc_PrKeyNewDown=0x55;
        //gs_FREventOut.byte=0;

//      EVENTOUTLOW();       
        Eny_EnergyClrCur(ENERGY_CLR);                               //�����ǰ����
        MemSet((uint8*)&gs_PowerCf,0,sizeof(S_POWERCF));            //������
        MemSet((uint8*)&gs_Energy,0,sizeof(S_ENERGY));              //��������
        Demand_Init();
        BE_WriteP(EEP_MAXDEMAND , (uint8 *)&gl_XPm, 3);
        SleepTimeProc();                                            //��RTC��ȡʱ�ӵ�RAM��
//    }
        E2DataChk();
  }
#endif
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
    //EnergyCBRManage();
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
//    getTimeZone();                                      //�����л�
    CLRWDT();
    Eny_RefVar();
    CLRWDT();
    CfgCheck();     //��������
    CLRWDT();
    //E2ParaCheck();  //E2���
    CLRWDT();
    //���ö������־λ
    //guc_DjCheckFlg|=flgDsDjCheck+flgZdDjCheck+flgDayDjCheck;    
}
/*=========================================================================================\n
* @function_name: Data_SecProc
* @function_file: Dataproc.c
* @����: ���ݴ�����봦��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Data_SecProc(void)
{
   TimerProc();                                //���е��¾�����
    CLRWDT();
    EnyB_Open_Cf();
    CLRWDT();
    Tamp_ChkPLL();                              //�������е�ѹ 
    CLRWDT();
    Tamp_DspProc();
    if(guc_CfOpenFlg == false   //��״̬�ȶ������������ж�
       && guc_WorkMd == NormalMode)      
    {
#if (CONFIG_CH == 2)
        CLRWDT();
        Tamp_BlanceProc();        
#endif
        CLRWDT();
        if(EnyB_ChkPowRev((uint8*)&gs_Channel.ucSta, CONFIG_JUNC)) //���ʷ����ж�
        {
//            OpenReverseLed();
        }
        else
        {
//            CloseReverseLed();
        }
//        CLRWDT(); 
//        Demand_1s();
    }
    else if(guc_WorkMd == TamperMode)
    {
//        CloseEarthLed();
//        CloseReverseLed();
//        CloseCurrentLed();        
    }
    CLRWDT();    
    //ShowSecondProc();
    CLRWDT();
}
/*=========================================================================================\n
* @function_name: DjProc
* @function_file: Dataproc.c
* @����: ���ᴦ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-30)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DjProc(void)
{
//    if(guc_DjCheckFlg&flgDsDjCheck)             //��ʱ���ᴦ��
//    {
//        DSFrez();
//        guc_DjCheckFlg&=~flgDsDjCheck;
//    }else if(guc_DjCheckFlg&flgZdDjCheck)       //���㶳���ж�
//    {
//        ZDFrez();
//        guc_DjCheckFlg&=~flgZdDjCheck;  
//
//    }else if(guc_DjCheckFlg&flgDayDjCheck)      //�ն����ж�
//    {
//        DayFrez();
//        guc_DjCheckFlg&=~flgDayDjCheck;
//    }
//    else if(guc_DjCheckFlg&flgInsDjEvent)  //˲ʱ����
//    {
//        HurryFrez();                                                            
//        guc_DjCheckFlg&=~flgInsDjEvent;
//    }
//    else 
//    {
//        guc_DjCheckFlg=0;
//    }
 
}
/*=========================================================================================\n
* @function_name: DataProcEvCountAdd
* @function_file: Dataproc.c
* @����: �¼��ۼƴ�������
* 
* 
* @����: 
* @param:ucNo  
* @����: 
* @����:   lwb (2012-05-22)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DataProcEvCountAdd(uint8 ucNo)
{//�¼��ۼƴ����ӵĶ������ݽӿ�,�ṩ����������ģ��,ʹģ�鲻ֱ�Ӵ����ⲿ������,���ǽ������ݴ������
//    uint8   ucLen;
//    uint16  uiAddr;
//    S_EVCNTADD code* pECA;
//    uint32  ulCnt;
//
//    if(ucNo < sizeof(gCs_EvCntAddTab)/sizeof(S_EVCNTADD))
//    {//�����Ϸ����ж�
//        pECA = (S_EVCNTADD code*)&gCs_EvCntAddTab + ucNo;
//        ulCnt = 0;
//        ucLen = pECA->ucLen;
//        uiAddr = pECA->uiAddr;
//        BE_ReadP(uiAddr, (uint8*)&ulCnt, ucLen);    //�ۼ�ֵ��ȡ
//        ulCnt++;                                    //�ۼ�ֵ��1
//        BE_WriteP(uiAddr, (uint8*)&ulCnt, ucLen);   //�ۼ�ֵ��1���д
//    }
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
//    uint16  uiPt;                       //ָ��
//    uint16  uiAddr;                     //E2��ַ
//    S_ROUND2 code* psR2;                     //ָ����Ʊ�1ĳһ����Ԫ��ָ��
//       
//    if(ucPos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
//    {
//        return;
//    }
//    uiPt=0;
//    
//    psR2 = (S_ROUND2 code*)&gCs_Round2Tab +ucPos;
//    if(ucPos>=ZFHJLID && ucPos<=FH4JLID)
//    {        
//        BE_ReadP(psR2->uiPtAddr, (uint8*)&uiPt, 2);                //��ȡƫ��ָ��
//    }
//    else
//    {
//        BE_ReadB(psR2->uiPtAddr, (uint8*)&uiPt);    //ָ��
//    }
//
//    if(ucRound != R2_NO_MOVE)
//    {//��Ҫ����ƶ�һλ
//        if(uiPt == 0)
//        {
//            uiPt = psR2->ucMod - 1;
//        }
//        else
//        {
//            uiPt--;
//        }
//    }
//    uiPt %= psR2->ucMod;                //�õ���Ҫ���ҵ��¼�ָ��,ʵ��Ϊ���ݱ���
//
//    uiAddr = psR2->uiDataAddr + uiPt * psR2->ucLen;
//
//    BE_WriteP(uiAddr, pucBuf, psR2->ucLen);
//    if(ucRound != R2_NO_MOVE)
//    {
//        if(ucPos>=ZFHJLID && ucPos<=FH4JLID)
//        {
//            BE_WriteP(psR2->uiPtAddr, (uint8*)&uiPt,2);//д��ָ������            
//        }
//        else
//        {
//            BE_WriteP(psR2->uiPtAddr, (uint8*)&uiPt,1);//д��ָ������
//        }
//    }
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
//    uint16  uiPt;                       //ָ��
//    uint16  uiAddr;                     //E2��ַ
//    S_ROUND2 code* psR2;                     //ָ����Ʊ�1ĳһ����Ԫ��ָ��
//
//    if(ucR2Pos >= sizeof(gCs_Round2Tab)/sizeof(S_ROUND2))
//    {
//        return;
//    }
//    
//    uiPt=0;
//    
//    psR2 = (S_ROUND2 code*)&gCs_Round2Tab + ucR2Pos;
//    if(ucR2Pos>=ZFHJLID && ucR2Pos<=FH4JLID)
//    {
//        BE_ReadP( psR2->uiPtAddr, (uint8*)&uiPt,2);//��ȡָ��        
//    }
//    else
//    {
//        BE_ReadP( psR2->uiPtAddr, (uint8*)&uiPt,1);//��ȡָ��
//    }
//    uiPt += ucCnt;
//    uiPt %= psR2->ucMod;                //�õ���Ҫ���ҵ��¼�ָ��,ʵ��Ϊ���ݱ���
//
//    uiAddr = psR2->uiDataAddr + uiPt * psR2->ucLen + ucOffset;
//
//    BE_ReadP(uiAddr, pucBuf, ucLen);
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
void Data_DayProc(void)
{
    gui_SystemState &= ~flgStSys_IsTodayJS;         //ȥ���Ѿ����й��㲥Уʱ���
}
/*=========================================================================================\n
* @function_name: Data_YearProc
* @function_file: Dataproc.c
* @����: �촦��
* 
* @����: 
* @����: 
* @����:   liming (2015-05-26)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Data_YearProc(void)
{
    uint32 ul_temp;
    Demand_Init();
    ul_temp=0;
    BE_WriteP(EEP_MAXDEMAND , (uint8*)&ul_temp, 3);
}
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
void CalPowDwTm(void)
{
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
}

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
void RecoverJSRData(void)
{
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
//    MemSet(&LastCbrTm.ucSecond, 0x00, 6);
//
//    DataProcRead2Slice(JSSJJLID,0,0,4,XDATA_RAMZONE);    //�����һ�ν���ʱ��
//    if( ApiBufCmp(&LastCbrTm.ucHour, XDATA_RAMZONE, 4) == CMP_EQU ) //
//    {
//        DataProcRead2Slice(DDJLID,0,0,6,&LastCbrTm.ucSecond);
//        if(ApiBufCmp(&LastCbrTm.ucMinute, XDATA_RAMZONE, 5) == CMP_EQU) //ȫ�㣬δ������
//        {
//            return;
//        }
//    }
//    else
//    {
//        MemCpy(&LastCbrTm.ucHour, XDATA_RAMZONE, 5);
//    }
//    
//    //DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);    //��ȡ���һ�ε����¼
//    
//    //MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);        //��ȡ����ʱ��
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
}
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
void RecoverDayDjData(void)
{
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
////    DataProcRead2Slice(DDJLID,0,0,12,XDATA_RAMZONE);                //��ȡ���һ�ε����¼
////
////    MemCpy(&LastCbrTm.ucSecond,XDATA_RAMZONE,6);            //��ȡ����ʱ��
//    
//    MemSet(&LastCbrTm.ucSecond, 0x00, 6);
//
//    DataProcRead2Slice(RDJID,0,0,5,XDATA_RAMZONE);            //��ȡ���һ���ն���ʱ��
//    if( ApiBufCmp(&LastCbrTm.ucMinute, XDATA_RAMZONE, 5) == CMP_EQU ) //
//    {
//        DataProcRead2Slice(DDJLID,0,0,6,&LastCbrTm.ucSecond);
//        if(ApiBufCmp(&LastCbrTm.ucMinute, XDATA_RAMZONE, 5) == CMP_EQU) //ȫ�㣬δ������
//        {
//            return;
//        }
//    }
//    else
//    {
//        MemCpy(&LastCbrTm.ucMinute, XDATA_RAMZONE, 5);
//    }
//    BE_ReadP(EEP_RFREEZTM,RdjTm.byte,2);                    //��ȡ�ն���ʱ��
//    
//    ucHour=RdjTm.byte[1];
//    ucMin=RdjTm.byte[0];
//    CurTime.ucDay=gs_DateTime.ucDay;
//    CurTime.ucMonth=gs_DateTime.ucMonth;
//    CurTime.ucYear=gs_DateTime.ucYear;
//    
//    //�жϹ�ȥ�����ն���
//    CbrCnt=CalRDJCount(&LastCbrTm.ucMinute,&gs_DateTime.ucMinute,ucHour,ucMin);
//    CalDayBack(&CurTime,JudgeCurTime(&gs_DateTime.ucMinute,RdjTm.byte));
//    
//    if( CbrCnt )  //��Ҫ����
//    {
//        for(i=0; i<CbrCnt; i++)
//        {
//            WriLastDJTime(&CurTime,RdjTm.byte,XDATA_RAMZONE1+i*5);
//            CalDayBack(&CurTime,1);
//        }
//
//
//        Eadd = Eny_GetEp1(1, 0);                            //ȡ��ĳ�����ʵĵ�������
//        data1.lword= gs_EnergyA.ulP+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+5+i*4,(void*)data1.byte,4);    //���� �ܼ��ƽ�ȵ���
//
//        Eadd = Eny_GetEp1(2, 0);                            //ȡ��ĳ�����ʵĵ�������
//        data1.lword= gs_EnergyA.ulN+Eadd;
//        data1.lword/=10;
//        data1.lword=Hex2BCD(data1.lword);
//        MemCpy(XDATA_RAMZONE+25+i*4,(void*)data1.byte,4);   //���� �ܼ��ƽ�ȵ���
//
////        for(i = 0; i <= 4; i++)
////        {
////            Eadd = Eny_GetEp1(1, i);                            //ȡ��ĳ�����ʵĵ�������
////            data1.lword= gs_EnergyA.ulP[i]+Eadd;
////            data1.lword/=10;
////            data1.lword=Hex2BCD(data1.lword);
////            MemCpy(XDATA_RAMZONE+5+i*4,(void*)data1.byte,4);    //���� �ܼ��ƽ�ȵ���
////        }
////    
////        for(i = 0; i <= 4; i++)
////        {
////            Eadd = Eny_GetEp1(2, i);                            //ȡ��ĳ�����ʵĵ�������
////            data1.lword= gs_EnergyA.ulN[i]+Eadd;
////            data1.lword/=10;
////            data1.lword=Hex2BCD(data1.lword);
////            MemCpy(XDATA_RAMZONE+25+i*4,(void*)data1.byte,4);   //���� �ܼ��ƽ�ȵ���
////        }
//       
//        MemSet(XDATA_RAMZONE+45,0,4);                           //����
//        
//        //ת����ٴι��ն�������
//        while(CbrCnt)
//        {
//            CbrCnt--;
//            DataProcEvCountAdd(RDJNUMID);                       //�����ն������
//    //      StructFreezeDate();
//            MemCpy(XDATA_RAMZONE,(XDATA_RAMZONE1+CbrCnt*5),5);
//            DataProcWriteRound2(R2_MOVE,RDJID,XDATA_RAMZONE);   //д������  
//        }
//    }
}
/*=========================================================================================\n
* @function_name: RecoverEnergyData
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
void Data_RecEnergy(void)
{
    Eny_SlpEnergyProc();    //�ָ���������
//    if(guc_DatCFrmd != 0)
//    {
//        gs_PowerCf.uc_Pz += 8;  //����1600���峣���ó�����������ܶ��������    
//    }
    gul_DatCFcnt = 0;
    guc_DatCFrmd = 0;   //
//    gui_SystemState &= ~flgStSys_PowOff;
}
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
void RecoverEnergyData(void)
{
  return;  
  /*
  BE_ReadP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,12)
    uint16 CRC=Uint8_To_Uint16(XDATA_RAMZONE+10);
    if(CRC==do_CRC(XDATA_RAMZONE, 10))      //���籣��������ȷ
    {
        MemCpy((uint8*)&gs_EnergyData.uiEPZ,  XDATA_RAMZONE ,   6);        //��ǰ��������
        MemCpy((uint8*)&gs_PowerCf.uc_Pz,XDATA_RAMZONE+6, 2);      //��ǰCF��
        MemCpy((uint8*)&gs_Energy.ucPz, XDATA_RAMZONE+8, 2);      //��ǰCF��Ӧ������ 
        if(POWERUP())
        {
            Eny_EnergyActiveSave();
        }
    }
    else
    {
        //MemSet((uint8*)&gs_EnergyData.uiEPZ,  0,   6);   
        MemSet((uint8*)&gs_PowerCf.uc_Pz,0,2);        //��ǰCF��
        MemSet((uint8*)&gs_Energy.ucPz, 0, 2);      //��ǰCF���ڵ�����
    }
    
    if(POWERUP())
    {
        CRC=0;
        BE_WriteP(EEP_POWDWENERGY+10,(uint8*)&CRC,2);               //ʹ����������Ч
    }
    
    gui_SystemState &= ~flgStSys_PowOff;
  */
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
uint8 JudgeCurTime(uint8* CurTime,uint8* RdjTime)
{
    if(*(CurTime+1) < *(RdjTime+1))             //�ж�ʱ�������ǰhourС���ն���hour
    {
        return true;
    }else                                       
    {
        if(*(CurTime+1) == *(RdjTime+1))        //��hour���
        {
            if(*CurTime < *RdjTime)             //�ж�Minute
            {
                return true;
            }
        }
        return 0;
    }
}
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
void WriLastDJTime(S_CURTIME *CurTime,uint8* time,uint8* pucBuf)
{
    CurTime->ucMinute = *time;                    //�ն���ķ�
    CurTime->ucHour = *(time+1);                  //�ն����ʱ
    MemCpy(pucBuf,&CurTime->ucMinute,5);
}
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
void CalDayBack(S_CURTIME *CurTime,uint8 offset)
{
    uint8 ucData;
    if(offset)                                //��������Ч����Ҫ��1��
    {
        if(CurTime->ucDay>0x01)                  //�ж�day�ǲ��Ǵ���1�ա�����ǣ���1��
        {
            ucData=APIByteBCD2HEX(CurTime->ucDay);
            ucData--;                                                            //����1��
            CurTime->ucDay = APIByteHEX2BCD(ucData);
        }else                                 //�������
        {
            if(CurTime->ucMonth > 0x01)          //�ж��·��ǲ���1�¡��������
            {
                ucData=APIByteBCD2HEX(CurTime->ucMonth);
                ucData--;                                                            //����1��
                CurTime->ucMonth = APIByteHEX2BCD(ucData);

                if(((APIByteBCD2HEX(CurTime->ucYear) & 0x03) == 0)&& CurTime->ucMonth == 0x02)  
                {//�жϵ�ǰ���ǲ��������2�·�
                    CurTime->ucDay = MonthDays[CurTime->ucMonth] + 1; //�����1��
                }else
                {
                    CurTime->ucDay = MonthDays[CurTime->ucMonth];
                }
                CurTime->ucDay=APIByteHEX2BCD(CurTime->ucDay);
            }else                             //�����1�£���1��1�գ�
            {

                ucData=APIByteBCD2HEX(CurTime->ucYear);
                ucData--;                                                            //����1��
                CurTime->ucYear = APIByteHEX2BCD(ucData);
                CurTime->ucMonth = 0x12;
                CurTime->ucDay = 0x31;
            }
        }
    }
}
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
uint8 JudgeJSR(uint8* CurTime,uint8* JSRTime,uint8 flg)
{
    uint8 i;
    for(i=0;i<flg;i++)
    {
        if(*(CurTime+1) < *(JSRTime+1+i*2))         //�ж���
        {
            return i;                               
        }else                                       
        {
            if(*(CurTime+1) == *(JSRTime+1+i*2))    //��Day���
            {
                if(*CurTime < *(JSRTime+i*2))       //�ж�Hour
                {
                    return i;                       //
                }
            }
        }
    }

    return flg;
}