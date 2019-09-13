#define ADK_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: ADK_CalFun
* @function_file: DLT_645_2007.c
* @����: ���Ͽ�У�����ʼ��
* 
* 
* @����: 
* @param:s_FrmInfo  
* @����: 
* @����:   lm (2013-07-31)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
#ifdef _DEL 
uint8 ADK_CalFun(S_FRAMEINFO *s_FrmInfo)
{
    //���ڣ�����<1kwh
    if(s_FrmInfo->ucCmd != 0x11 || (guc_FactoryType!=FactorMd) || ((*(gs_EnergyA.lCP)+ Eny_GetEp1(0,0))>1000))
    {
        s_FrmInfo->ucErr.word = ComErrBit_Other;
        s_FrmInfo->ucLen = 1;
    }
    else if(guc_ADKcal == ADK_Init)
    {
        Word16 CRC;
        CLRWDT();               //ι��
        FCpyTMem(XDATA_RAMZONE,InitPara0,sizeof(S_JBPM)-2);                     //����Flash���ݵ�RAM��
        CRC.word=do_CRC(XDATA_RAMZONE,sizeof(S_JBPM)-2);
        XDATA_RAMZONE[sizeof(S_JBPM)-2]=CRC.byte[0];
        XDATA_RAMZONE[sizeof(S_JBPM)-1]=CRC.byte[1];                            //����CRC��RAM��
        SysE2ParaSetManage(EEP_JBTOTAL,XDATA_RAMZONE,sizeof(S_JBPM));//д�뵽E2�� 
//        BE_WriteP(EEP_JBTOTAL, (uint8*)&gs_JbPm, sizeof(S_JBPM));
//        BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN, (uint8*)&gs_JbPm, sizeof(S_JBPM));
        Eny_JbPm_GetE2();                                     //����У�����������оƬ
        s_FrmInfo->ucReply = 0;
    }
    else if(guc_ADKcal == ADK_Cal)
    {
        s_FrmInfo->ucReply = 0;
        if(s_FrmInfo->ucbuf[1]==0x11)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_11;
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else if(s_FrmInfo->ucbuf[1]==0x15)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_15;
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else if(s_FrmInfo->ucbuf[1]==0x31)
        {
            gui_RefreshEvent |= flgEtPara_ADKCal_31;                        
            BE_WriteP(EEP_AUTOCAL, s_FrmInfo->ucbuf + 2, 16);
        }
        else
        {
            s_FrmInfo->ucReply = 1;
            s_FrmInfo->ucErr.word = ComErrBit_Other;
            s_FrmInfo->ucLen = 1;
        }
    }             
    return Ret_OK;
}

/*=========================================================================================\n
* @function_name: ParaInit
* @function_file: DLT_645_2007.c
* @����: ������ʼ��
* 
* 
* @����: 
* @param:s_FrmInfo  
* @����: 
* @����:   lm (2013-08-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 ParaInit(S_FRAMEINFO *s_FrmInfo)
{
    MemCpy(s_FrmInfo->uiID.byte,s_FrmInfo->ucbuf,4);   //���ݱ�ʶ
    
    if(s_FrmInfo->uiID.lword != 0x80541413)
 //      || !(gui_SystemState & flgStSys_Program))
    {
        s_FrmInfo->ucErr.word = ComErrBit_Other;
        s_FrmInfo->ucLen = 1;
        return Ret_OK;
    }  
    
    SetCRCWord(guc_InitWd);
 //   guc_RTCSave = 0xAA;
 //   guc_RTCSave = 0x55;
    gui_RefreshEvent|=flgEtPara_Init;
    s_FrmInfo->ucLen = 0;
    
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: ADK_ReadVar
* @function_file: DLT_645_2007.c
* @����: ������ʼ��
* 
* 
* @����: 
* @param:s_FrmInfo  
* @����: 
* @����:   lm (2013-08-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/

uint8 ADK_ReadVar(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    int16 Eadd;
    uint32 *pEnyData;
    int32  data1; 
    uint32 ulVarValue;
    uint16 uiCosVal;
    
    pEnyData=(uint32*)gs_EnergyA.lCP;                    //��ȡ�������ݽṹ�׵�ַ
    data1=*(pEnyData);
    Eadd = Eny_GetEp1(0,0);
    data1 += Eadd;                                                     //�й�������
   /* if(data1>0x80000000)
    {
        guc_ShowEnergyFlag=0x55;
        data1=-data1;
        flag=1;
    }*/
    data1/=10;
    if(data1 > 80000000)
    {
        data1 = data1 % 80000000;
    }
    data1= Hex2BCD(data1);                              //ת��ΪBCD��
   /* if(flag)
    {
        data1|=0x80000000;
    }*/
    data1 &=~0x80000000;
    MemCpy(s_FrmInfo->ucbuf,(uint8*)&data1,4);      //�й�

    MemSet(s_FrmInfo->ucbuf+4,0x00,4);     //�޹�

    ulVarValue=CalRMS(RMSU);        
    MemCpy(s_FrmInfo->ucbuf+8,(uint8*)&ulVarValue,2);   //��ѹ

    if(SETA == gs_Channel.ucSta)
    {
        ulVarValue=CalRMS(RMSI1);       
        MemCpy(s_FrmInfo->ucbuf+10,(uint8*)&ulVarValue,3);    //����
        ulVarValue=CalRMS(DATAP);       
        MemCpy(s_FrmInfo->ucbuf+13,(uint8*)&ulVarValue,3);   //A�й�����
    }else if(SETB == gs_Channel.ucSta)
    {
        ulVarValue=CalRMS(RMSI2);       
        MemCpy(s_FrmInfo->ucbuf+10,(uint8*)&ulVarValue,3);    //���ߵ���
        ulVarValue=CalRMS(DATAQ);       
        MemCpy(s_FrmInfo->ucbuf+13,(uint8*)&ulVarValue,3);   //B�й�����
    }
    MemSet(s_FrmInfo->ucbuf+16,0x00,3);   //�޹�����      
    uiCosVal=CalCos();                                      
    MemCpy(s_FrmInfo->ucbuf+19,(uint8*)&uiCosVal,2);      //��������
     
    s_FrmInfo->ucLen = 21;
    return Ret_OK;
}

/*=========================================================================================\n
* @function_name: ADK_ReadVar
* @function_file: DLT_645_2007.c
* @����: ������ʼ��
* 
* 
* @����: 
* @param:s_FrmInfo  
* @����: 
* @����:   lm (2013-08-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 ADK_Backup(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    Eny_EnergyClrCur(ENERGY_CLR);                               //�����ǰ����
    MemSet((uint8*)&gs_PowerCf,0,sizeof(S_POWERCF));            //������
    MemSet((uint8*)&gs_Energy,0,sizeof(S_ENERGY));              //��������
    
    uint32 tmp;
    tmp = Uint8_To_Uint32(s_FrmInfo->ucbuf+12);
    gs_EnergyA.lCP[0] = gs_EnergyA.ulP = BCD2Hex(tmp)*10;  
    gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
    BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA,sizeof(ENERGYACTIVE));
    BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));

    s_FrmInfo->ucLen = 0;

    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: ADK_ReadFlash
* @function_file: ADKfunc.c
* @����: ���Ͽ˲���ֻ������֧��
* 
* 
* @����: 
* @param:s_FrmInfo  
* @����: 
* @����:   lm (2013-08-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 ADK_ReadFlash(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable)
{
    if(s_FrmInfo->uiID.lword == 0x04000404)       //���ѹ
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+27, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000405)      //�����
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+33, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000406)      //������
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+39, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000409)      //����й�����
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitADK+45, CTable->ucLen); 
    }
    else if(s_FrmInfo->uiID.lword == 0x04000501)      //�������״̬�ְ��Ͽ˸�
    {
        gt_RunCode.ucSta = 0x42;   //Ĭ�����ã�����·��������������
        if(gs_Channel.ucSta == SETB)
        {
            gt_RunCode.sSta.bChannel = 0;
        }
        if(gs_SysRunSt.Pdir)
        {
            gt_RunCode.sSta.bPdir = true;
        }
        s_FrmInfo->ucbuf[0] = gt_RunCode.ucSta;
    }
    else if(s_FrmInfo->uiID.lword == 0x04800001)      //��������汾��
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitFwVer, CTable->ucLen);
    }
    else if(s_FrmInfo->uiID.lword == 0x04800002)      //����Ӳ���汾��
    {
        FCpyTMem(s_FrmInfo->ucbuf, InitHwVer, CTable->ucLen);
    }
    else
    {
        s_FrmInfo->ucErr.word = ComErrBit_Nodata;
        s_FrmInfo->ucLen = 1;
        return Ret_OK;
    }
    s_FrmInfo->ucLen = CTable->ucLen;
    return Ret_OK;
}
#endif
//����У����
/*=========================================================================================\n
* @function_name: CalculateSC
* @function_file: EnergyBottom.c
* @����: ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue  
* @param:TarValue  
* @param:LastSC  
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint32 CalculateSC(int32 CurValue,int32 TarValue,int32 LastSC)
{
    //���㹫ʽ����,���ı�2011��7��14��
    int16 Error;                    
    uint16 Stemp0remd,Stemp2remd;  
    int32 Stemp0,Stemp1,Stemp2,Stemp3;//
    uint32 Result;

    //��ʽ˵�� ������ʽ S=2^31(1/(1+e)-1)+S1(1/(1+e)),���e����1000����
    //���⹫ʽ��:  S=  2^31(-e/(1000+e))+S1(1000/(1000+e)=S1(1000/(1000+e)-2^31(e/(1000+e))
    //�������  2^31(e/(1000+e))
    Error=(CurValue-TarValue)*1000/TarValue;            //�������ֵ��������1000
    Stemp0=0x80000000/(1000+Error);                     //�ȱ����������� 2^31/(1000+e)=0x80000000/(1000+e)
    Stemp0remd=0x80000000%(1000+Error);                 //��������
    Stemp0remd=Stemp0remd*1000/(1000+Error);            //����С�����֣�С����������1000
    Stemp1=Stemp0*Error+(Stemp0remd*Error)/1000;        //�Ѽ����������С�����ֶ�����ERROR����2^31(e/(1000+e))

    //�������S1*(1000/(1000+e)
    Stemp2=LastSC/(1000+Error);                         //������������
    Stemp2remd=LastSC%(1000+Error);                     //������������
    Stemp2remd=Stemp2remd*1000/(1000+Error);            //С������
    Stemp3=Stemp2*1000+Stemp2remd;                      //�������ּ�С������  

    Result=Stemp3-Stemp1;                               //S=S1(1000/(1000+e)-2^31(e/(1000+e))
    return Result;
 
}
/*=========================================================================================\n
* @function_name: CalculateAC
* @function_file: EnergyBottom.c
* @����: ���㹫ʽ
* 
* 
* @����: 
* @param:CurValue  
* @param:TarValue  
* @param:LastSC  
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 CalculateAC(int32 CurValue,int32 TarValue)
{
    //���㹫ʽ����,���ı�2011��7��14��
    int16 Error;                    
    uint8 Result;

    Error=(CurValue-TarValue)*1000/TarValue;            //�������ֵ��������1000
    Result = (int32)3011*Error/2000;

    return Result; 
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkPW
* @function_file: EnergyBottom.c
* @����: У�����ʺ����
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChkPW(uint8 ucSta)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint32 ul_Scp;                          //ԭʼ�Ȳ�����
    int32 l_SdPower;                        //��׼����ֵ
    //int32  err;
    //int32  errPgain;
    int32 pa;
    uint16 tmpGa, tmpPW;
    
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //��ȡ��׼����ֵ  
    
    if(ucSta == SETA)
    {
        tmpGa = SCP;
        tmpPW = DATAP;
    }
    else
    {
        tmpGa = SCQ;
        tmpPW = DATAQ;
    }   
    ul_Scp = EnyB_ReadMeterParaACK(tmpGa);      //��ȡ�Ȳ�ֵ
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);//BCD2Hex(Uint8_To_Uint32(ucData))/100;   //��ñ�׼����ֵ

    pa=CalRMS(tmpPW);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
    } 

    pa =BCD2Hex(pa);
    
    if(ucSta == SETA)
    {
        gs_JbPm.ul_SCP = CalculateSC(pa, l_SdPower, ul_Scp);   //����Ȳ�ֵ
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);             //�����±Ȳ�ֵ
    }
    else
    {
        gs_JbPm.ul_SCQ = CalculateSC(pa, l_SdPower, ul_Scp);   //����Ȳ�ֵ
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCQ, SCQ);             //�����±Ȳ�ֵ
    }
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkTinyPW
* @function_file: EnergyBottom.c
* @����: У�����ʶ��β��������
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChkTinyPW(uint8 ucSta)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint8 i;
    int32 l_SdPower;                        //��׼����ֵ   
    Word32 TempValue;
    uint32 TempSum;
    uint32 pa_sum,TempPara;
    uint16 tmpPw;
    
    pa_sum = 0;
    TempSum = 0;
 
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //��ȡ��׼����ֵ 
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>4);   //��ñ�׼����ֵ
    
    if(ucSta == SETA)
    {
        tmpPw = DATAIP;
        TempPara = gs_JbPm.ul_PG/256;        //��ȡ����ϵ��
    }
    else
    {
        tmpPw = DATAIQ;
        TempPara = gs_JbPm.ul_QG/256;        
    }
    for(i=0; i<16; i++)
    {
        TempValue.lword=EnyB_ReadMeterParaACK(tmpPw); 
        DelayXms(20);
        CLRWDT();                           //ι��
        if(TempValue.byte[3]>0x7f)          //����Ǹ����������ȱ������
        {
            TempValue.lword=~TempValue.lword+1;
        }
        TempSum += TempValue.lword;
    }   
    
    TempSum = TempSum>>4;              //��ȡ���ʼĴ���ֵ
    
    pa_sum = (TempSum*2560)/TempPara;  //����ֵ
      
    //TempValue.lword = l_SdPower*TempPara/2560;    //���ۼĴ���ֵ
    
    if(l_SdPower > pa_sum)
      TempSum = (TempValue.lword*(l_SdPower-pa_sum)/l_SdPower);    //������β���ֵ
    else
      TempSum = -(TempValue.lword*(pa_sum-l_SdPower)/l_SdPower);   //������β���ֵ
    
    if(ucSta == SETA)
    {
        gs_JbPm.ul_PARAPC = TempSum;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_PARAPC, PARAPC);                          //�����±Ȳ�ֵ 
    }
    else
    {
        gs_JbPm.ul_PARAQC = TempSum;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_PARAQC, PARAQC);                          //�����±Ȳ�ֵ
    }
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));  
    EnyB_JbPm_Updata(); 
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkIrms
* @function_file: EnergyBottom.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChkIrms(uint8 ucSta)
{
    uint8 ucData[3];
    uint32  ul_SdCurrent;
    uint32  ul_Irmg;
    int32  l_IARms;
    uint16 tmpGa,tmpRMS;
    
    BE_ReadP(EEP_AUTOCAL+5,ucData,3);      //��ȡ��׼����ֵ
    ul_SdCurrent=BCD2Hex(Uint8_To_Uint24(ucData));    //��ñ�׼����ֵ
    
    if(ucSta == SETA)
    {
        tmpGa = SCI1;
        tmpRMS = RMSI1;
    }
    else
    {
        tmpGa = SCI2;
        tmpRMS = RMSI2;
    }
    ul_Irmg = EnyB_ReadMeterParaACK(tmpGa);                    //��ȡ�Ȳ�ֵ

    l_IARms= BCD2Hex(CalRMS(tmpRMS)&0x7FFFFF);
        
    if(ucSta == SETA)
    {
        gs_JbPm.ul_SCI1 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ
        gs_JbPm.ul_SCI1_800 = gs_JbPm.ul_SCI1;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1, SCI1);
    }
    else
    {
        gs_JbPm.ul_SCI2 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ
        gs_JbPm.ul_SCI2_800 = gs_JbPm.ul_SCI2;
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2, SCI2);
    } 
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkUrms
* @function_file: EnergyBottom.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChkUrms(void)
{
    uint8 ucData[3];
    uint32  ul_SdVoltage;
    uint32  ul_Urmg;
    int32  l_URms;

    BE_ReadP(EEP_AUTOCAL+1,ucData,3);      //��ȡ��׼��ѹֵ
    ul_SdVoltage=BCD2Hex(Uint8_To_Uint24(ucData))/10;    //��ñ�׼��ѹֵ
    ul_Urmg = EnyB_ReadMeterParaACK(SCU);                    //��ȡ�Ȳ�ֵ

    l_URms= BCD2Hex(CalRMS(RMSU))*10;//gs_EnyInsData.ul_URms;

    gs_JbPm.ul_SCU = CalculateSC(l_URms, ul_SdVoltage, ul_Urmg);   //����Ȳ�ֵ

    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCU, SCU);                                 //�����±Ȳ�ֵ
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkAngle
* @function_file: EnergyBottom.c
* @����: �ǲ�У��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChkAngle(uint8 ucSta)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint32 l_SdPower;                        //��׼����ֵ
    uint32 pa;
    uint16 tmpGa,tmpPw;
    
    if(ucSta == SETA)
    {
        tmpGa = PHCCtrl1;
        tmpPw = DATAP;
    }
    else
    {
        tmpGa = PHCCtrl2;
        tmpPw = DATAQ;
    }
    EnyB_SetMeterCfgACK(0, tmpGa);       //�ǲ�ֵд0
    //��Ҫ��ʱ�ȴ����ʷŵ�ͨ��д��E2ǰ
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //��ȡ��׼����ֵ  
   
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);///10;   //��ñ�׼����ֵ

    pa=CalRMS(tmpPw);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

 //   l_SdPower=3000;
    if(ucSta == SETA)
    {
        gs_JbPm.uc_PhcCtrl1 = CalculateAC(pa, l_SdPower);   //����ǲ�ֵ
        EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1, PHCCtrl1);  //���ýǲ�ֵ 
    }
    else
    {       
        gs_JbPm.uc_PhcCtrl2 = CalculateAC(pa, l_SdPower);   //����ǲ�ֵ
        EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2, PHCCtrl2);  //���ýǲ�ֵ    
    }         
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();                                       //����У�����������оƬ
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChknAngle
* @function_file: EnergyBottom.c
* @����: ���߽ǲ�У��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ADK_AutoChknAngle(void)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint32 l_SdPower;                        //��׼����ֵ
    uint32 pa;
    
    EnyB_SetMeterCfgACK(0, PHCCtrl2);       //�ǲ�ֵд0
    //��Ҫ��ʱ�ȴ����ʷŵ�ͨ��д��E2ǰ
    BE_ReadP(EEP_AUTOCAL+8,ucData,4);         //��ȡ��׼����ֵ  
   
    l_SdPower = BCD2Hex(Uint8_To_Uint32(ucData)>>8);///10;   //��ñ�׼����ֵ
//  pa = EnyB_ReadMeterParaACK(DATAP);        //��ȡ����ֵ�������ж�
//
//  if(pa>0)           //���Ȱѱ�ƶ�ȡ�Ĺ���ֵת����ֵ
//  {
//     pa= -BCD2Hex(CalRMS(DATAP));//gs_EnyInsData.l_PowerPA;
//  }else
//  {
//     pa= BCD2Hex(CalRMS(DATAP));//-gs_EnyInsData.l_PowerPA;
//  }
    pa=CalRMS(DATAQ);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

    l_SdPower=3000;
    gs_JbPm.uc_PhcCtrl2 = CalculateAC(pa, l_SdPower);   //����ǲ�ֵ
 
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2, PHCCtrl2);  //���ýǲ�ֵ
    
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ

    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));

    EnyB_JbPm_Updata();                                       //����У�����������оƬ
}
