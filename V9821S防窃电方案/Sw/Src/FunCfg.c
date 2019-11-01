#define FUNCFGEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: RecoverCfg
* @function_file: FunCfg.c
* @����: �ָ�������
* 
* @����: 
* @����: 
* @����:   lwb (2013-01-23)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void RecoverCfg(void)
{
    FCpyTMem(&gs_FunCfg.uc_CfSaveCfg, InitPara1+23, sizeof(GSFUNCFG)-2); 
    //SysE2ReadData(EEP_CFSAVECFG,&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2);   //��ȡ������
    if((gs_FunCfg.uc_PWOFFSHOWMDCfg!=0x09)
       &&(gs_FunCfg.uc_PWOFFSHOWMDCfg!=0x90))
    {
        gs_FunCfg.uc_PWOFFSHOWMDCfg=0;
    }    
    gs_FunCfg.ul_CRC=do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2);       //�����������crc
    //SysE2ReadData(EEP_DBYXTZZ,(uint8*)&gs_MeterMode,1);                        //ˢ�µ������������1
}
/*=========================================================================================\n
* @function_name: Up_FunCfg
* @function_file: FunCfg.c
* @����: �������üĴ���
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Up_FunCfg(void)
{
//    uint8 i;
    RecoverCfg();                                   //�ָ�����
    
    //��ȡ���㷽ʽ��
//    if((gs_FunCfg.uc_CfSaveCfg&0xf0)==0x50)         //��Ҫ���¼���
//    {
//        BE_ReadB(EEP_YGCALC,&guc_EPCalcType);       //ˢ�¼�����ʽ��   
//        //���¼�����ϵ���
//        //������������
//        for(i=0;i<5;i++)
//        {
//            gs_EnergyA.lCP[i]=0;
//            if(guc_EPCalcType&BIT0)
//            {
//                gs_EnergyA.lCP[i]+=gs_EnergyA.ulP[i];
//            }
//            else if(guc_EPCalcType&BIT1)
//            {
//                gs_EnergyA.lCP[i]-=gs_EnergyA.ulP[i];
//            }
//
//
//            //������������
//            if(guc_EPCalcType&BIT2)
//            {
//                gs_EnergyA.lCP[i] +=gs_EnergyA.ulN[i];
//            }
//            else if(guc_EPCalcType&BIT3)
//            {
//                gs_EnergyA.lCP[i] -=gs_EnergyA.ulN[i];
//            } 
//        }
//
//        gs_EnergyA.uiCRC = do_CRC((uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE) - 2);
//        if(Eny_CheckEnergyActiveRAM() == ENERGY_ERR_NONE)
//        {
//            BE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA,sizeof(ENERGYACTIVE));
//        }
//        //����жϼ���,����������������ж�����Ϊ������
//
//        if(Eny_CheckEnergyActiveRAM() == ENERGY_ERR_NONE)
//        {
//        #if (_SW_SE_Type > 0)
//            SE_WriteP(EEP_EPS,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
//        #else
//            BE_WriteP(EEP_EPS+EEP_BAK_LEN,(uint8*)&gs_EnergyA, sizeof(ENERGYACTIVE));
//        #endif
//        }
//
//    }//��Ȼ �Ͷ�ԭ���ĵ�������Ҫ����
    //BE_ReadB(EEP_YGCALC,&guc_EPCalcType);               //ˢ�¼�����ʽ��  
    guc_EPCalcType=0x05;
    Eny_EnergyActiveSave();
 
}
/*=========================================================================================\n
* @function_name: CfgCheck
* @function_file: FunCfg.c
* @����: ��ʱ����������Ƿ���ȷ
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-28)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void CfgCheck(void)
{
    if(gs_FunCfg.ul_CRC!=do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2))       //������CRC����ȷ�������������
    {
        Up_FunCfg();   //���������� 
    }

    if(gs_DispCont.ul_CRC!=do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2))
    {
        ShowInitial();
    }
}
