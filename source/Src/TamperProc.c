#define TAMPEREXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: Tamp_Init
* @function_file: TamperProc.c
* @����: ������ʼ�� 
* @����:  
* @����:   
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Tamp_Init(void)
{
    guc_WorkMd  = TamperMode;
    guc_PendSta = 0;    //PendReady
    guc_PendCnt = 0;   
    gul_I1rms800k = 0;
    gul_I2rms800k = 0;
}
/*=========================================================================================\n
* @function_name: Tamp_ChkPLL
* @function_file: TamperProc.c
* @����: ����ģʽ�ж� 
* @����: 
* @����: 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Tamp_ChkPLL(void)
{ 
    uint8 ucLastMd;   
    ucLastMd = guc_WorkMd;
    
    if(false == Tamp_ChkUrms())
        return;

//    if(gul_Urms800k < Voltage_100V)//���������
//    {
//        guc_WorkMd = TamperMode;
//    }
//    else
//    {
        guc_WorkMd = NormalMode;      
//    }
    
    if(ucLastMd != guc_WorkMd)
    {
        SwitchMode(ucLastMd); 
        //��ʾ����
        if(ucLastMd == TamperMode)
        {
            guc_PendSta = 0;    //PendReady
            guc_PendCnt = 0;  
            gs_DispStt.ucMode = Const_DispMode_LX;
            gs_DispStt.uiIndex = 0;                     //���Ÿ��鵽������
            gs_DispStt.ucTmr = gs_DispCont.ucLxTm-1;
        }
    }
}
/*=========================================================================================\n
* @function_name: MeterADSel
* @function_file: TamperProc.c
* @����: ��ADͨ������ 
* @����: 
* @����: 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void MeterADSel(uint8 ABit, uint8 DBit)
{
    ADCOPEN(ABit);         
    EnyB_SetMeterCfgACK(0x10|DBit, PMCtrl1);
}
/*=========================================================================================\n
* @function_name: MeterADClose
* @function_file: TamperProc.c
* @����: ��ADͨ������ 
* @����: 
* @����: 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void MeterADClose(uint8 ABit)
{
    ADCCLOSE(ABit);         
    EnyB_SetMeterCfgACK(0, PMCtrl1);
}
/*=========================================================================================\n
* @function_name: Tamp_ChkUrms
* @function_file: TamperProc.c
* @����: �ڲ�ͬ����״̬�»�ȡ��ѹ��Чֵ
* @����: 
* @����: true-�ѵõ���false-δ�õ�
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
bool Tamp_ChkUrms(void)
{
#if (CONFIG_PT != 0)
    if(!POWERUP())
    {
        gul_Urms800k = 0;
        return true;
    }
#endif    
    if(guc_PllSta == PLL_800K)
    {
        if(guc_PendSta == PendReady)        //�ȴ���ͨ��
        {
            MeterADSel(ADCUPDN, ONU);
            guc_PendSta = PendUGO;
            return false;
        }
        else if((guc_PendSta&0x0F) == 0x0A)
        {
            return true;
        }
    }
    else
    {
        gul_Urms800k = EnyB_ReadMeterParaACK(RMSIU);
        return true;
    }
    
    return false;
}
/*=========================================================================================\n
* @function_name: Tamp_ChkIrms
* @function_file: TamperProc.c
* @����: �ڲ�ͬ����״̬�»�ȡ������Чֵ
* @����: 
* @����: true-�ѵõ���false-δ�õ�
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
bool Tamp_ChkIrms(void)
{
    if((guc_PendSta&0x0F) != 0x0A)        //
        return false;
    else
    {
        if(guc_PendSta == PendUEND)        //
        {
            MeterADSel(ADCAPDN, ONI1);
            guc_PendSta = PendI1GO;
            return false;
        }
#if (CONFIG_CH == 1)
        else if(guc_PendSta != PendI1END)
        {
            return true;
        }
#else
        else if(guc_PendSta == PendI1END)
        {       
            MeterADSel(ADCBPDN, ONI2);
            guc_PendSta = PendI2GO;
            return true;
        }
        else if(guc_PendSta != PendI2END)
        {
            gul_I2rms800k = gul_I2rms800k/MEA_BMUL;
            return true;
        }
#endif
    }    
    return false;
}
/*=========================================================================================\n
* @function_name: Tamp_IntProc
* @function_file: TamperProc.c
* @����: �жϴ���10MS����һ��
* 
* @����: 
* 
* @����: 
* @return: int16 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//#pragma inline = forced
__near_func void Tamp_IntProc(void)
{
    if((guc_PendSta&0x05) == 0x05)      //sta go
    {
        guc_PendCnt++;
        if(guc_PendCnt>55)
        {
            guc_PendCnt = 0;
            if(guc_PendSta == PendUGO)
            {                    
                gul_Urms800k = EnyB_ReadMeterParaACK(RMSIU);
                MeterADClose(ADCUPDN);
                guc_PendSta = PendUEND;
            }
            else if(guc_PendSta == PendI1GO)
            {
                gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);
                gul_I1DCval = EnyB_ReadMeterParaACK(DATAIDI1);       
                MeterADClose(ADCAPDN);
                guc_PendSta = PendI1END;
            }
#if (CONFIG_CH == 2)
            else
            {
                gul_I2rms800k = EnyB_ReadMeterParaACK(RMSII2);
                gul_I2DCval = EnyB_ReadMeterParaACK(DATAIDI2);
                MeterADClose(ADCBPDN);
                guc_PendSta = PendI2END;
            }
#endif
        }
    }
}
/*=========================================================================================\n
* @function_name: SwitchMode
* @function_file: TamperProc.c
* @����: ����ģʽ�л�
* @����: 
* @����:  
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void SwitchMode(uint8 ucLastMd)
{  
    CLRWDT();
    EA = 0;
    if((guc_WorkMd&0xF0) != 0x00)
    {
        SetPLL3DOT2M(MEA_ON);       
    }
    else
    {
        SetPLL800K(MEA_ON);
    }
    EnyB_SetMeterRule((guc_WorkMd&0x0F));
    if((ucLastMd&0xF0)!=(guc_WorkMd&0xF0))
    {
        Mcu_RTCNormal(guc_PllSta);
    }
    EA = 1;
    CLRWDT();
}
/*=========================================================================================\n
* @function_name: Tamp_DspProc
* @function_file: TamperProc.c
* @����: �Ե�������� 
* @����:  
* @����: 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Tamp_DspProc(void)
{   
    if(guc_CfOpenFlg)
    {
        gul_I1rms800k = 0;
        gul_I2rms800k = 0;
        gul_DataCP    = 0;
//        gul_I1DCval  = 0; //�ڲ�ƽ������µ��磬��ֹ����ĵ�1��2�����ٵ�������������
//        gul_I2DCval  = 0; 
        return;
    }
    
    if(guc_WorkMd == TamperMode)
    {        
        if(false == Tamp_ChkIrms())
            return;       
        gul_DataCP = (gul_I1rms800k>gul_I2rms800k?gul_I1rms800k:gul_I2rms800k);   //�õ���ֵ
        EnyB_SetMeterCfgACK(gul_DataCP, DATACP);
        guc_PendSta = PendReady;
    }
    else
    {
        gul_I1DCval = EnyB_ReadMeterParaACK(DATAIDI1);
        gul_I2DCval = EnyB_ReadMeterParaACK(DATAIDI2);
    }
    if(gul_I1DCval & _NegLogo_ )//0x80000000)   //��ֵ
    {
        gul_I1DCval = ~gul_I1DCval + 1;
    }
    if(gul_I2DCval & _NegLogo_ )//0x80000000)   //��ֵ
    {
        gul_I2DCval = ~gul_I2DCval + 1;
    }
}
/*=========================================================================================\n
* @function_name: CalImbRate
* @function_file: EnergyBottom.c
* @����: �жϵ�����ƽ��
* @����:  Big-��ֵ
*         Small-Сֵ
*         Dnmtr-��ĸ
*         Risk-������յȼ�
* @����:   uldiff
* @����:   liming (2016-03-21)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint32 CalImbRate(uint32 Big, uint32 Small, uint32 Dnmtr, uint8 Risk)
{
    uint32 ul_diff;
    if(Dnmtr == 0)
        return 100;
    if (Risk == 0x55)       //���10��
    {
        ul_diff = ((Big - Small)*10/Dnmtr)*10;
    }
    else if (Risk == 0xAA)       //����ٱ�
    {
        ul_diff = ((Big - Small)/Dnmtr)*100;
    }
    else
    {
        ul_diff = (Big - Small)*100/Dnmtr;
    }
    
    if(ul_diff>100)
    {
        ul_diff = 100;
    }
    
    return ul_diff;
}
/*=========================================================================================\n
* @function_name: Tamp_ChkBlance
* @function_file: EnergyBottom.c
* @����: �жϵ�����ƽ��
* @����:  ulgate-ͨ��������ƽ���жϷ�ֵ����λ%
*         ulstart-�μӵ�����ƽ����С�ж�ֵ���Ĵ���ԭʼֵ
* @����:   true-��ƽ�⣬false-ƽ�� 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
bool Tamp_ChkBlance(uint32 ulgate)
{
    uint32 ul_Value1,ul_Value2;
    uint32 ul_diff;
    uint8  ucRisk;
    
    if(guc_WorkMd == NormalMode)
    {
        ul_Value1 = EnyB_ReadMeterParaACK(RMSI1);
        ul_Value2 = EnyB_ReadMeterParaACK(RMSI2)/MEA_BMUL;
    }
    else
    {
        ul_Value1 = gul_I1rms800k;
        ul_Value2 = gul_I2rms800k;
    }
    ucRisk = 0;
    if(ul_Value1 >= 0x28F5C28 || ul_Value2 >= 0x28F5C28)
    {//�����������,0xFFFFFFFF/100 = 0x28F5C28
        ucRisk = 0x55;
        if(ul_Value1 >= 0x19999999 || ul_Value2 >= 0x19999999)
        {
            ucRisk = 0xAA;
        }
    }
//    if(ul_Value1 < Current_STARTA && ul_Value2 < Current_STARTB)
//    {
//        gs_SysRunSt.Imbalance = false;
//        //return false;
//    }
    if(ul_Value1 > ul_Value2)
    {
#if (imBlance_Cmp == 0)        //��ĸ��ǰͨ��
        if(gs_Channel.ucSta == SETA)
        {
            ul_diff = CalImbRate(ul_Value1, ul_Value2, ul_Value1, ucRisk);
        }
        else
        {
            ul_diff = CalImbRate(ul_Value1, ul_Value2, ul_Value2, ucRisk);
        }
#elif (imBlance_Cmp == 1)       //��ĸ��ֵ
        ul_diff = CalImbRate(ul_Value1, ul_Value2, ul_Value1, ucRisk);
#else                           //��ĸСֵ
        ul_diff = CalImbRate(ul_Value1, ul_Value2, ul_Value2, ucRisk);
#endif
        if(ul_diff >= ulgate)
        {
            gs_SysRunSt.Imbalance = true;
            if(ul_Value1 < Current_STARTA && ul_Value2 < Current_STARTB)
            {
                gs_SysRunSt.Imbalance = false;
                //return false;
            }
            if(gs_Channel.ucSta == SETB)
            {
                gs_Channel.ucACnt++;
                gs_Channel.ucBCnt = 0;
                if(gs_Channel.ucACnt > gs_Channel.ucGate)
                {
                    return true;
                }                                   
            }
            return false;
        }
        else
        {
            gs_SysRunSt.Imbalance = false;
            return false;
        }
    }
    else
    {
#if (imBlance_Cmp == 0)        //��ĸ��ǰͨ��
        if(gs_Channel.ucSta == SETA)
        {
            ul_diff = CalImbRate(ul_Value2, ul_Value1, ul_Value1, ucRisk);
        }
        else
        {
            ul_diff = CalImbRate(ul_Value2, ul_Value1, ul_Value2, ucRisk);
        }
#elif (imBlance_Cmp == 1)       //��ĸ��ֵ
        ul_diff = CalImbRate(ul_Value2, ul_Value1, ul_Value1, ucRisk);
#else                           //��ĸСֵ
        ul_diff = CalImbRate(ul_Value2, ul_Value1, ul_Value2, ucRisk);
#endif
        if(ul_diff >= ulgate)
        {
            gs_SysRunSt.Imbalance = true;
            if(ul_Value1 < Current_STARTA && ul_Value2 < Current_STARTB)
            {
                gs_SysRunSt.Imbalance = false;
                //return false;
            }
            if(gs_Channel.ucSta == SETA)
            {
                gs_Channel.ucBCnt++;
                gs_Channel.ucACnt = 0;
                if(gs_Channel.ucBCnt > gs_Channel.ucGate)
                {
                    return true;
                }                                   
            }
            return false;
        }
        else
        {
            gs_SysRunSt.Imbalance = false;
            return false;
        }
    }         
}
/*=========================================================================================\n
* @function_name: Tamp_BlanceProc
* @function_file: Tamper.c
* @����: �жϵ�����ƽ��
* @����: 
* @����:   true-��ƽ�⣬false-ƽ�� 
* @����:   liming (2016-01-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Tamp_BlanceProc(void)
{
    if(Tamp_ChkBlance(imBlance_Rate))      //������ƽ��
    {
        gs_Channel.ucACnt = gs_Channel.ucBCnt = 0;
        if(guc_WorkMd == NormalMode)
        {
            guc_CfOpenFlg = true;
            guc_CfOpenCnt = 0;
            //�����ж�
        }
        if(gs_Channel.ucSta == SETA)
        {               
            gs_Channel.ucSta = SETB;
        }
        else
        {
            gs_Channel.ucSta = SETA;
        }       
    }
}
/*=========================================================================================\n
* @function_name: Tamp_Sleep
* @function_file: Tamper.c
* @����: ���Ե粿�ֵĵ��紦��
* @����: 
* @����:   
* @����:   liming (2016-01-20)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Tamp_Sleep(void)
{   //

    if(guc_WorkMd == NormalMode)
    {
#if (CONFIG_CH == 1)
        gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);             //��ȡ����ֵ
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);            //д800k�����Ȳ�
        gul_DataCP = gul_I1rms800k/4;
#else
        if(gs_Channel.ucSta == SETA)
        {
            gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);         //��ȡ����ֵ
            //EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);        //д800k�����Ȳ�
            gul_DataCP = gul_I1rms800k/4;
        }
        else
        {
            gul_I2rms800k = EnyB_ReadMeterParaACK(RMSII2)/MEA_BMUL;//��ȡ����ֵ
            //EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800, SCI1);        //д800k�����Ȳ�
            gul_DataCP = gul_I2rms800k/4;
        }
#endif        
        CtrlADC5 = 0;
        CtrlADC6 = 0;                                             //��ADͨ��   
        EnyB_SetMeterCfgACK(0, PMCtrl1);                          //ֹͣ���㣬�����ź�  
//        EnyB_SetMeterH2L(gul_DataCP, DATACP);                  //��������ֵ 
//        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp/4, GATECP);           //д��32KǱ������

        EnyB_SetMeterCfgACK(0x10, CRPST);                          //�ؼ���ģʽ
        EnyB_SetMeterCfgACK(0, PMCtrl4);                          //�ؼ���ģʽ  
        EnyB_SetMeterCfgACK(0x05,CFCtrl);       //ֻ������CF
        
    }
//    else
//    {
//      gul_I1DCval = 0xE86451;
//      gul_I2DCval = 0x1191D34;

#if (CONFIG_CH == 1)
      EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);     //д800k�����Ȳ�
      EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����B·ֱ��ƫ��
      EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����B·�����жϷ�ֵ 
#else
        if(gs_Channel.ucSta == SETA)
        {
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);     //д800k�����Ȳ�
            EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����A·�����жϷ�ֵ            
        }
        else
        {
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800, SCI1);        //д800k�����Ȳ�
            EnyB_SetMeterCfgACK(gul_I2DCval,0x1001);            //����B·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTB, IDETTH);           //����B·�����жϷ�ֵ            
        }
#endif
//    }
    EnyB_SetMeterCfgACK(0, PPCFCNT);                          //�������  
    EnyB_SetMeterCfgACK(0x5A, PMCtrl4);                    //��������ģʽ, MEAתOSCʱ��
    
    EnyB_SetMeterCfgACK(gs_JbPm.ul_GateOSC, GATEP);           //���ó�����������
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp/4, GATECP);           //д��32KǱ������
    EnyB_SetMeterH2L(gul_DataCP, DATACP);                  //��������ֵ
    
    gul_DatCFcnt = 0;
    guc_DatCFrmd = 0;
}