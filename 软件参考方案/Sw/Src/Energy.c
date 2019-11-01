#define AP_ENERGYEXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: Eny_JbPm_GetE2
* @function_file: EnergyBottom.c
* @����: ��ȡE2�е����ݣ�ͬʱ������صĴ���
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
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
            if(gs_JbPm.ui_JbCRC == do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2))  //RAM�е������Ƿ�����
            {                                           //��Ϊ���²���Ҫ�����������ṹ������
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
* @����: У������ĸ��£���E2�и���
*
*
* @����:
* @param:pjb
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
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
* @����: ��E2�ж���У�������ͬʱ����������У�飬�����ȷ�������ˢ�£�����ȷ���ó�ʼ������
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_RefVar(void)
{
    uint16 uitmp;
    BE_ReadW(EEP_JBTOTAL+sizeof(S_JBPM)-2, &uitmp);                             //��E2�е�CRCУ��ֵ

    if(uitmp == gs_JbPm.ui_JbCRC)                                               //�ж�����E2�е������Ƿ���RAM�е����
    {                                                                           //RAM�е�������E2�е���һ����
        if(gs_JbPm.ui_JbCRC == do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2))      //RAM�е������Ƿ�����
        {                                                                       //��Ϊ���²���Ҫ�����������ṹ������
            EnyB_JbPm_Updata();
        }
        else
        {
            Eny_JbPm_GetE2();                                                  // RAM�е�����Ҫ��ͨ����CRCУ�飬Ҫ����E2��CRC�Բ�����
        }
    }
    else
    {
        Eny_JbPm_GetE2();                                                      //RAM�е�����Ҫ��ͨ����CRCУ�飬Ҫ����E2��CRC�Բ�����
    }
    Eny_JbPm_MeterConst();                                                     //��������ĸ���
}
/*=========================================================================================\n
* @function_name: Eny_RefCalcType
* @function_file: Energy.c
* @����: ˢ�¼�����ʽ��
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_RefCalcType(void)
{
    guc_EPCalcType=0x55;                            //Ĭ�����ӷ�
    //BE_ReadB(EEP_YGCALC,&guc_EPCalcType);               //ˢ�¼�����ʽ��
}
/*=========================================================================================\n
* @function_name: Eny_JbPm_MeterConst
* @function_file: EnergyBottom.c
* @����: ���峣��
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_JbPm_MeterConst(void)
{
    uint8 i;
    for(i=0;i<MeterConstLen;i++)                                // ��������ų���ʵ�����ֿ���
    {                                                           // ���ݱ�����ȷ��CF�����Ƶϵ���͵�λ������С
        if(gs_MeterConstT[i].ui_MC==gs_JbPm.ui_MeterC)
        {                                                       // �������峣����ȷ��CF��Ƶϵ���͵�λ������С
            guc_GateCF = gs_MeterConstT[i].uc_CFGate;           // �����������
            guc_UnitCF = gs_MeterConstT[i].uc_CFUinit;          // ��λ��С
            break;
        }
    }

    if(i>=MeterConstLen)                                        // ���ұ���У�����û�ж�Ӧ�ĳ����Ĵ���
    {                                                           // ��������û�ж�Ӧ�������״̬������
        guc_GateCF = 10;                                        // ��һ���Ƚϴ�����ݣ����׿���
        guc_UnitCF = 1;
    }
}

/*=========================================================================================\n
* @function_name: Eny_EnergyClrCur
* @function_file: Energy.c
* @����: �����ǰ�����й�����
*        ���RAM�е����ݣ����ǽṹ���е����ݣ������2kWh
*        ���E2�е����ݣ��ǵ�ǰ�����й��ܵ�������
* @����:
* @param:ucType
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
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
* @����: �ϵ���RAM�����Ƿ���ȷ
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_PurCheckRAMEny(void)
{
    ENERGYACTIVE sEA;
    if(ENERGY_ERR_RAM==Eny_CheckEnergyActiveRAM())
    {                                                                       //RAM��������ȷ
        BE_ReadP(EEP_EPS,(uint8*)&sEA,sizeof(ENERGYACTIVE));                //��ȡE2�еĵ���
        if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE)- 2) != sEA.uiCRC)      //���E2�е���CRC�Ƿ���ȷ
        {                                                                   //��E2��������ȷ
        #if (_SW_SE_Type > 0)
            SE_ReadP(EEP_EPS+EEP_BAK_LEN,(uint8*)&sEA,sizeof(ENERGYACTIVE));
        #else
            BE_ReadP(EEP_EPS+EEP_BAK_LEN,(uint8*)&sEA,sizeof(ENERGYACTIVE)); //��ȡE2�еĵ���
        #endif
            if(do_CRC((uint8*)&sEA, sizeof(ENERGYACTIVE) - 2) == sEA.uiCRC)
            {                                                               //����E2������ȷ
                MemCpy((uint8*)&gs_EnergyA, (uint8*)&sEA, sizeof(ENERGYACTIVE));            //����E2���ݵ�����RAM��
            }else
            {                                                               //����E2��������ȷ
                Eny_EnergyClrCur(ENERGY_CLR_E2);                                //����RAM������E2�е���
            }
        }
        else
        {
            MemCpy((uint8*)&gs_EnergyA, (uint8*)&sEA, sizeof(ENERGYACTIVE));                //������E2������RAM��
        }
    }
}

/*=========================================================================================\n
* @function_name: Eny_CheckEnergy
* @function_file: Energy.c
* @����: ���ṹ���е������Ƿ���ȷ
*       ��������crcУ�����������,0�ض���У����ȷ,1��У�������ݶ�,2����
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_CheckEnergy(void)
{
    uint8   ucErr = 0;
    uint16  uiCRC;

    uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);          // ��������CRCУ��
    if (uiCRC != gs_EnergyData.uiCRC)
    {
        ucErr++;
        uiCRC = do_CRC((uint8 *)&gs_EnergyData_bak, sizeof(ENERGYDATA)-2);  // ���ݵ�������CRCУ��
        if (uiCRC != gs_EnergyData_bak.uiCRC)
        {
            ucErr++;
        }
    }

    if (ucErr & 1)
    {                                                                       // ��һ�����
        MemCpy((uint8*)&gs_EnergyData, (uint8*)&gs_EnergyData_bak, sizeof(ENERGYDATA));     // ��������
    }
    else if(ucErr >= 2)                                                     // ������ͱ������򶼳���
    {                                                                       // ������
        Eny_EnergyClrCur(ENERGY_CLR_RAM);                                       // ����
    }
}

/*=========================================================================================\n
* @function_name: Eny_CheckEnergyActiveRAM
* @function_file: Energy.c
* @����: ���RAM�����Ƿ���ȷ
*
* @����:
*
* @����:
* @return: uint8
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 Eny_CheckEnergyActiveRAM(void)
{
    //��֤����CRCУ��
    if(do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE)- 2) != gs_EnergyA.uiCRC)
    {
        return ENERGY_ERR_RAM;
    }

    return ENERGY_ERR_NONE;
}

/*=========================================================================================\n
* @function_name: Eny_GetEp1
* @function_file: Energy.c
* @����: ���㵱ǰ�������й��ܵ����������ַ���)
*
*
* @����:
* @param:index  0-��ϣ�����״̬�־�����1-ԭ��, , 2-��
* @param:fee   �Ʒѵķ���
*
* @����:
* @return: int16
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
int16 Eny_GetEp1(uint8 index, uint8 fee)
{
    int16 iRet=0;
#ifdef MultariffMeter
    if((fee != 0) && ((fee - 1) != gs_FeeData.uc_FeeNo))    //�������ķ��ʲ��������ڵ�ǰ���ʻ��߲������ܵ����Ļ�����0
    {
        return 0;
    }
#endif

    Eny_CheckEnergy();                                      //������������Ч�ԣ��Ƿ�ͨ�Ĺ�CRCУ��

    if(index==0)
    {                                                       //�����������й����ռ�����ʽ��������
        iRet = gs_EnergyData.uiEP;
//      iRet += gs_EnergyData.uiEN;
    }
//  else if(index==1)
//  {
//      iRet = gs_EnergyData.uiEP;                          //���������������
//  }else if(index==2)
//  {
//      iRet =gs_EnergyData.uiEN;                           //���ط����������
//
//  }
    return iRet;
}

/*=========================================================================================\n
* @function_name: Eny_EnergyActiveSave
* @function_file: Energy.c
* @����: ��ǰ����д��E2��
*           ���ﻹ����һ������,�������ݷַ��ʺ����ܵ�������ȵĻ�,������д���ݵ�E2��
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_EnergyActiveSave(void)
{
    uint8 ucFlg = 0;
    int16 iDelta;
    ENERGYACTIVE sEA;
    //����֤E2����CRC�Ƿ���ȷ,�����һ����ȷ,����Ϊ�ⲿ��������Ч
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

    //���E2����CRC��Ч,����E2���ݸ���RAM����,��E2����CRC����ȷʱ,RAM����CRC��ȷ,��ô����RAM����
    //���������ȷ,����������E2�����ݸ���RAM����
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


//  //�����й�
//  iDelta = Eny_GetEp1(1, 0);
//  gs_EnergyA.ulP[0] += iDelta;
//  #ifdef MultariffMeter
//  gs_EnergyA.ulP[gs_FeeData.uc_FeeNo+1] += iDelta;
//  #endif
    //����й�
    iDelta = Eny_GetEp1(0, 0);
    gs_EnergyA.lCP[0] += iDelta;

    #ifdef MultariffMeter
    gs_EnergyA.lCP[gs_FeeData.uc_FeeNo+1] += iDelta;
    #endif 
//  //�����й�
//  iDelta = Eny_GetEp1(2, 0);
//  gs_EnergyA.ulN[0] += iDelta;
//
//  #ifdef MultariffMeter
//  gs_EnergyA.ulN[gs_FeeData.uc_FeeNo+1] += iDelta;
//  #endif
    //����CRC
    gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
    //��ҪRAM�����Ϸ�����дE2
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

    //����жϼ���,����������������ж�����Ϊ������
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
* @����: �����������յ��ײ��������ݺ�ת����RAM��ͬʱ����CRCУ��
*           ͬʱ�б��Ƿ���Ҫ��RAM�еĵ���ת����E2��
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Eny_EnergyProc(void)
{
//    uint8   i;
    uint8   ucDelta;
    uint8*  p;                                          // �����й�������ָ��
    uint16*  p1;
    uint8 ucSaveflg;

    ucSaveflg=0;
    Eny_CheckEnergy();                                  // ��������Ч��

    p = (uint8*)&gs_Energy;                             // ��������;

    p1 = (uint16*)&gs_EnergyData;
//  for (i=0; i<1; i++,p++,p1++)
    {                                                   // ����й������־�������ﵽMAX_E����EEPROM��дһ�Σ�
        if ( *p > 0)
        {                                               // �е�������
            __disable_interrupt();                      // ���ݱ���
            ucDelta = *p;                               // ���ж��в����������ƶ���RAM�����Ĵ�����
            *p = 0;
            __enable_interrupt();
            *p1 += ucDelta;                             // ���жϲ��������������ۼӵ�RAM��
        }

        if (*p1 > MAX_E)                                // RAM�е���������Ϊ��Ч����
        {
            Eny_CheckEnergy();
        }

        if (*p1 > SAVEVALUE)                            // �б��Ƿ���Ҫд��
        { 
            ucSaveflg=0x55;                                              
        }  
    }

    gs_EnergyData.uiCRC = do_CRC((uint8 *)&gs_EnergyData, sizeof(ENERGYDATA)-2);  // ��������CRCУ��
    MemCpy((void*)&gs_EnergyData_bak, (void*)&gs_EnergyData, sizeof(ENERGYDATA));

    if(ucSaveflg==0x55)
    {
        Eny_EnergyActiveSave();
    }
}
/*=========================================================================================\n
* @function_name: WriteHisEP
* @function_file: Energy.c
* @����: д����ʷ����
*
* @����:
* @����:
* @����:   lwb (2012-03-25)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
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
    DataProcWriteRound2(R2_MOVE,LSDLID,(uint8*)&gs_EnergyA);    //д����ʷ����
}
/*=========================================================================================\n
* @function_name: EnergyCBRManage
* @function_file: Energy.c
* @����: �����մ���,һСʱ���ñ������жϳ�����ʱ��һ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-22)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnergyCBRManage(void)
{
    uint8 i,j;
    Word16 W16_JSR[3];

    BE_ReadP(EEP_CBR1, W16_JSR[0].byte,6);              // �õ������յ����ں�Сʱ
                                                    
    for(i=0;i<2;i++)                                    //ȥ����ͬ�ĳ�����
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

        //��Ҫ��Ҫ���������Ƿ�Ϸ�
        if(W16_JSR[i].byte[0] == gs_DateTime.ucHour && W16_JSR[i].byte[1]  == gs_DateTime.ucDay)
        {
            Eny_EnergyActiveSave();
            WriteHisEP();
            MemSet(XDATA_RAMZONE,0x00,8);
            DataProcWriteRound2(R2_MOVE,LSXLID,XDATA_RAMZONE);  // д������������ݼ�ʱ��
            InitDemand();
//            DemandClrCur();                                     // ���㵱ǰ����
            break;                                              //ͬһ��ʱ�̲�����ת��ü���           
        }
    }
}
