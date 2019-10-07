#define POWMANGE_EXT

#include "Include.h"

uint8 guc_ChkPowDn;                 // �µ���Ĵ���
/*=========================================================================================\n
* @function_name: Pwr_DownChk
* @function_file: Powmanger.c
* @����:
*
* @����:
* @����:
* @����:   lwb (2012-03-23)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Pwr_DownChk(void)
{
    guc_ChkPowDn <<= 1;
#if (CONFIG_PT == 0)
    if(!_IsUpIo())      // �ж��Ƿ��ѹ��
#else
    if(!_IsUpIo() && PwrDetLow())      // �ж��Ƿ��ѹ��
#endif
//    if(!_IsUpIo() && PwrDetLow())      // �ж��Ƿ��ѹ��
    {
        guc_ChkPowDn |=0x1;                 // �ѵ�ǰ��ѹ״̬����Ĵ�����ֻ�������е͵�ƽ�ſ����ж����µ�
    }

    if(0x03 == (guc_ChkPowDn&0x03))                // ��������8�Σ�Ҳ����8ms�͵�ƽ�������µ��¼�
    {
        guc_ChkPowDn =0x0;
        gui_SystemEvent |= flgEtGlb_PowDown;// �����µ��¼����
        Pwr_DownProc();                  //���紦��       
    }
}
extern void Init_CfG(void);
/*=========================================================================================\n
* @function_name: LCDForPowerOff
* @function_file: System.c
* @����: ���紦����
*
* @����:
* @����:
* @����:   lwb (2012-01-31)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Pwr_LcdSet(void)
{         
//  Ҫ����ʾ    
    LCDInitSleep();                     //��ʼ��LCD��ʾ
    gs_DispStt.ucMode = Const_DispMode_TX;
    gs_DispStt.uiIndex = 0;
    gs_DispStt.ucTmr=gs_DispCont.ucLxTm;
    if(guc_PowOffRuning)
    {
        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
        ShowRefresh();                  //����ˢ��
    }
    else
    {   //��Ҫ����ʾ     
        LCD_Off();
        CtrlLCDV=0x00;
    }
}
/*=========================================================================================\n
* @function_name: Pwr_E2Save
* @function_file: System.c
* @����: ���紦����
*
* @����:
* @����:
* @����:   lwb (2012-01-31)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/

/*
void Pwr_E2Save(void)
{
    uint16 CRC;
    MemCpy(XDATA_RAMZONE,   (uint8*)&gs_EnergyData.uiEPZ,   6);        //��ǰ��������
    MemCpy(XDATA_RAMZONE+6,  (uint8*)&gs_PowerCf.uc_Pz,  2);            //��ǰCF��
    MemCpy(XDATA_RAMZONE+8,  (uint8*)&gs_Energy.ucPz,  2);              //��ǰCF��Ӧ������    
//    MemCpy(XDATA_RAMZONE+4,  (uint8*)&gs_PowerCf.guc_EepromCFcntP,  1);
    CRC=do_CRC(XDATA_RAMZONE, 10);
    MemCpy(XDATA_RAMZONE+10,(uint8*)&CRC,2);
    BE_WriteP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,12);
}
*/
/*=========================================================================================\n
* @function_name: Pwr_DownProc
* @function_file: System.c
* @����: ���紦����
*
* @����:
* @����:
* @����:   lwb (2012-01-31)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 Pwr_DownProc(void)
{ 
    EA=0;
    IOOFF();                                              //�ر����ж����IO
    IntOFF();                                             //�ر��жϣ�����жϱ��
    UARTOFF();                                            //�ر�����UART       

    Tamp_Sleep();    

    Pwr_E2Save();   
    gui_SystemState |= flgStSys_PowOff;    //�õ���״̬
//    guc_PowOffRuning = true; 
//    Pwr_LcdSet();
    //RTCWakeUpTm(RTC_SETSEC, 6);
    gs_WakeUp.ucType = RTC_SETSEC;
    gs_WakeUp.ucTmDly = 6;
    gs_WakeUp.ucSlpCnt = 0;
    gs_WakeUp.ucIncntA = 0;
    gs_WakeUp.ucIncntB = 0;
    if( gui_BatLowFlg == 0x5A5A) //��ص�ѹ�Ͳ�ȥ����
    {
        CtrlADC6=0;      //�ر����е�ADC
        PMG=1;           //�رռ���ʱ��
        MEAFRQ=0; 
        while(MEAFRQ);
        
        RTCWakeUpTm(RTC_HOUR, 0); //Сʱ����
    }else
    {
        RTCWakeUpTm(gs_WakeUp.ucType, gs_WakeUp.ucTmDly);
    }
    //������дE2�������ڴ���E2�˿�
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();                     //I2C�����
    
    OpenFD();
//#if (CONFIG_PT == 1)
//    OpenFD();
//#endif
//    OpenCurrentLed();
//    DelayXms(200);
    if(!POWERUP())
    {
        if(Sleep())
        {
        }
        else
        {
            return false;
        }
    }                                                               
    return false;
}
/*=========================================================================================\n
* @function_name: Pwr_WakeupProc
* @function_file: Powmanger.c
* @����: ���߻��Ѵ���
* 
* 
* @����: 
* @����:  
* @����:   lm (2014-04-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
/*
void Pwr_WakeupProc(void)
{ 
    SLPWDT();     
    CloseFD();
    guc_SleepCnt = 0;    
    //�����Ĵ��������������
    gul_DataCP = gul_DataCP*24/103;                           //����800kʱ��������ֵ(���ź����)
    EnyB_SetMeterL2H(gul_DataCP,  DATACP);		              //д�볣�����ʼĴ�����MEA��800k
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp, GATECP);           //д��800KǱ������
    EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);                 //800K�˲�������    
    EnyB_SetMeterCfgACK(0x00, PMCtrl3);                       //�����˲���
    EnyB_SetMeterCfgACK(0x16, PMCtrl1);                       //����˫ͨ��
    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800, SCI1);           //д800k�����Ȳ�
    EnyB_SetMeterCfgACK(0x10,CRPST);
    EnyB_SetMeterCfgACK(0xFA,PMCtrl4);                        //�򿪼���,����Ǳ������
    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800, SCI2);
    CtrlADC0 = gs_JbPm.uc_AnaG;                               //Aͨ��ADC 16������ Bͨ��4��
    CtrlADC6 = 0x03;	                                      //����ģ��A,Bͨ��ADC      
    Init_Timer1(600);                                            //���ö�ʱ��1, 400ms    
    SLPWDT();
    Eny_SlpEnergyProc();              
    SLPWDT();  
    TR1 = 1;
    EA = 1;
    PCON = 1;                                                 //MCU����ȴ�400ms
    EA = 0;
    SLPWDT();
    uint32 ul_PDRMI1 = EnyB_ReadMeterParaACK(RMSII1);         //��ȡ˫ͨ������
    uint32 ul_PDRMI2 = EnyB_ReadMeterParaACK(RMSII2)/BMUL;       
    CtrlADC6 = 0;                                             //��ADͨ��   
    EnyB_SetMeterCfgACK(0, PMCtrl1);                          //ֹͣ���㣬�����ź�
    //gul_DataCP = ul_PDRMI1;
    gul_DataCP = (ul_PDRMI1>ul_PDRMI2?ul_PDRMI1:ul_PDRMI2);   //�õ���ֵ 
    //gul_DataCP=0x6E5D5F; //DEBUG
    if(guc_PowOffRuning)
    {
        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
        ShowRefresh();                  //����ˢ��
    }
    EnyB_SetMeterH2L(gul_DataCP, DATACP);                //��������ֵ
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp/4, GATECP);           //д��32KǱ������
    RTCWakeUpTm(RTC_SETSEC, 6); 
    OpenFD();
    SleepRTC();
}*/
void Pwr_WakeupProc(void)
{    
#if (MEA_SLP_PLL == 1)    
    CtrlBGP  &= 0x3f;                               //�������� ADCȫ�ֵ���ƫ�� �������
    CtrlCLK = (CtrlCLK & 0xC3)| 0x28;               //MEA 3.2M  ADC 800K
#endif 
    gul_DataCP = gul_DataCP/MEA_AMUL;               //����800kʱ��������ֵ(���ź����)
    EnyB_SetMeterL2H(gul_DataCP,  DATACP);          //д�볣�����ʼĴ�����MEA-32K��3.2M
#if (MEA_SLP_PLL == 0)
    EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);       //800K�˲�������
#else
    EnyB_SetMeterCfgACK(0x889374bc, PARABPF);       //3.2M�˲�������
#endif
    EnyB_SetMeterCfgACK(0x00, IDET);                //���������빦����Чֵ����
#if (MEA_SLP_CF == 1)    
    EnyB_SetMeterCfgACK(0x1A, PMCtrl4);             //����������ʹ�������ۼӣ�CF���
    EnyB_SetMeterCfgACK(0x10,CRPST);                //����40ms
#else
    EnyB_SetMeterCfgACK(0x0A, PMCtrl4);             //����������ʹ�������ۼ�
#endif    
    EnyB_SetMeterCfgACK(0x00, PMCtrl3);             //��ֹ��ͨ�˲���
    CtrlADC0 = gs_JbPm.uc_AnaG;                         //����ADC����
#if (MEA_SLP_FMCU == 1)     
    PowOffSetFmcu(PLL_800K);         //MCUƵ��3.2M����800K
#endif      
    /*�ȿ�ģ�⣬�ٿ�����,��Ҫ�ȴ�ʱ���ٿ�IDET*/    
#if (CONFIG_CH == 1)  
    CtrlADC6 = 0x01;	                            //����ģ��ͨ��ADC_A,ֻ��A·�����ٵ������
    EnyB_SetMeterCfgACK(0x12, PMCtrl1);             //����ͨ��A,�ź�����ͨ��1
#else    
    if(gs_Channel.ucSta == SETA)                           
    {
        CtrlADC6 = 0x01;
        EnyB_SetMeterCfgACK(0x12, PMCtrl1);         //����ͨ��A,�ź�����ͨ��1
    }
    else
    {
        CtrlADC6 = 0x02;
        EnyB_SetMeterCfgACK(0x32, PMCtrl1);         //����ͨ��B,�ź�����ͨ��1
    }    
#endif
    EnyB_SetMeterCfgACK(0x05,CFCtrl);               //������������Ͱ�ۼ�    
#if (MEA_SLP_PLL == 0)                              //����800K:��Ҫ�ȴ�ʱ���ڿ��� 3.2M:����ȴ�
    Init_Timer1(5);   //MCU����ȴ�5ms 
    TR1 = 1;
    EA = 1;
    PCON = 1;   //MCU����ȴ�Xms  
    EA = 0;                    
    EnyB_SetMeterCfgACK(0x13, IDET);                //MEA-800K �����жϵ���4 ��ʼ�ж�
#else
    EnyB_SetMeterCfgACK(0x1F, IDET);                //MEA-3.2M �����жϵ���16,��ʼ�ж�
#endif  
    
//#if (MEA_SLP_FMCU == 1)   //MCU 3.2M 
//    Init_Timer1(15);                                //MCU����ȴ�15ms
//#else
    Init_Timer1(15);                                //MCU����ȴ�15ms
//#endif    
    TR1 = 1;
    EA = 1;
    PCON = 1;    //MCU����ȴ�Xms  
    EA = 0;
    
    uint8 ucIdet = EnyB_ReadMeterParaACK(IDET);     //��ȡ�жϽ��
    EnyB_SetMeterCfgACK(0x00, IDET);                //�رտ��ٵ������
        
    if(ucIdet & 0x40)   //�ж��е���
    {
#if (MEA_SLP_PLL == 0)
        Init_Timer1(400);                        //���ö�ʱ��1, 400ms  ��ʱ����ʱ�䲻��,ֻ�ܹ�����MCU 800K
#else
        Init_Timer1(125);                        //���ö�ʱ��1, 125ms  
#endif
        SLPWDT(); 
        TR1 = 1;
        EA = 1;
        PCON = 1;                                   //MCU����ȴ�Xms
        EA = 0;
        SLPWDT();
#if (MEA_SLP_FMCU == 1) 
        PowOffSetFmcu(PLL_3D2M);   //MCU��3.2M 
#endif         
#if (CONFIG_CH == 1) 
        gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);      //��ȡA·��Чֵ
        gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����A·ֱ��ֵ
//        gul_I1DCval = 0xFA7600;
        EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
        CtrlADC6 = 0;                                       //��ADͨ�� 
        EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
        EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����B·�����жϷ�ֵ
        gul_DataCP = gul_I1rms800k;
        gs_WakeUp.ucIncntA = 0;  //���A·û�������� 
#else        
        if(gs_Channel.ucSta == SETA)
        {
            gul_Test = 1;  //������
            gul_I1rms800k = EnyB_ReadMeterParaACK(RMSII1);      //��ȡA·��Чֵ
            gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����A·ֱ��ֵ
//            gul_I1DCval = 0xFA7600;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
            CtrlADC6 = 0;                                       //��ADͨ�� 
            EnyB_SetMeterCfgACK(gul_I2DCval,0x1001);            //����B·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTB, IDETTH);           //����B·�����жϷ�ֵ            
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800,SCI1);
            gs_Channel.ucSta = SETB;
            gs_WakeUp.ucIncntA = 0;  //���A·û�������� 
        }
        else
        {
          gul_Test = 2;  //������                                                       
            gul_I2rms800k = EnyB_ReadMeterParaACK(RMSII1)/MEA_BMUL; //��ȡB·��Чֵ   
            gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����B·ֱ��ֵ
//            gul_I2DCval = 0xF41500;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
            CtrlADC6 = 0;                                       //��ADͨ�� 
            EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����A·�����жϷ�ֵ
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
            gs_Channel.ucSta = SETA;
            gs_WakeUp.ucIncntB = 0;  //���B·û�������� 
        }
        //�õ���ֵ
        gul_DataCP = (gul_I1rms800k>gul_I2rms800k?gul_I1rms800k:gul_I2rms800k);
#endif   
        if(gul_DataCP > RMSII1_TH) //��ֹС����������ʱ���ٵ�����������
          EnyB_SetMeterH2L(gul_DataCP, DATACP);       //��������ֵ
        else
        {
          gul_DataCP = 0x00;//������
          EnyB_SetMeterH2L(0x00, DATACP);       //��������ֵ
        }
    }
    else
    {   
      SLPWDT();
      if(gs_Channel.ucSta == SETA) //A��B·û�������� 
      {
        gs_WakeUp.ucIncntA++;
      }else
      {
        gs_WakeUp.ucIncntB++;
      }
      if((gs_WakeUp.ucIncntA>10)||(gs_WakeUp.ucIncntB>10))
      {                   
#if (MEA_SLP_PLL == 0)
        Init_Timer1(400);                        //���ö�ʱ��1, 400ms  ��ʱ����ʱ�䲻��,ֻ�ܹ�����MCU 800K  
#else
        Init_Timer1(125);                        //���ö�ʱ��1, 125ms  
#endif
        SLPWDT(); 
        TR1 = 1;
        EA = 1;
        PCON = 1;                                   //MCU����ȴ�Xms
        EA = 0;
        SLPWDT();
      }
#if (MEA_SLP_FMCU == 1) 
      PowOffSetFmcu(PLL_3D2M);   //MCU��3.2M 
#endif 
#if (CONFIG_CH == 1) 
        gul_I1rms800k = 0;
        if(gs_WakeUp.ucIncntA>10)   //û��������10�λ��Ѽ��
        {
          gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����A·ֱ��ֵ
          gs_WakeUp.ucIncntA = 0;  //��ռ��� 
        }
//        gul_I1DCval = 0xFA7600;
        EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
        CtrlADC6 = 0;                                       //��ADͨ�� 
        EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
        gul_DataCP = 0;
#else
        if(gs_Channel.ucSta == SETA)
        {
          gul_Test = 3;  //������
            gul_I1rms800k = 0;
            if(gs_WakeUp.ucIncntA>10)  //û��������10�λ��Ѽ��
            {
              gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����B·ֱ��ֵ
              gs_WakeUp.ucIncntA = 0;  //��ռ��� 
            }
//            gul_I1DCval = 0xFA7600;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
            CtrlADC6 = 0;                                       //��ADͨ�� 
            EnyB_SetMeterCfgACK(gul_I2DCval,0x1001);            //����B·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTB, IDETTH);           //����B·�����жϷ�ֵ
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2_800,SCI1);
            gs_Channel.ucSta = SETB;
        }
        else
        {
          gul_Test = 4;  //������
            gul_I2rms800k = 0;
            if(gs_WakeUp.ucIncntB>10)  //û��������10�λ��Ѽ��
            {  
              gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����A·ֱ��ֵ
              gs_WakeUp.ucIncntB = 0;  //��ռ��� 
            }
//            gul_I2DCval = 0xF41500;
            EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
            CtrlADC6 = 0;                                       //��ADͨ�� 
            EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
            EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����A·�����жϷ�ֵ
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1_800,SCI1);
            gs_Channel.ucSta = SETA;
        }
        gul_DataCP = (gul_I1rms800k>gul_I2rms800k?gul_I1rms800k:gul_I2rms800k);
#endif  
        if(gul_DataCP > RMSII1_TH)  //��ֹС����������ʱ���ٵ�����������
          EnyB_SetMeterH2L(gul_DataCP, DATACP);       //��������ֵ
        else
        {
          gul_DataCP = 0x00;//������
          EnyB_SetMeterH2L(0x00, DATACP);       //��������ֵ
        }
    }    
    
#if (POW_OFF_ENYPROC == 1) 
    DelayXms(1);   //�����Ӹ�Ƶ�е�32Kʱ ��MCU 3.2M�������Ĵ���ʱ��Ҫ�ȴ�
    Eny_SlpEnergyProc(); //��������
#endif    
    
#if (POW_OFF_DISP == 1) 
    LCDInitSleep();    //��ʼ��LCD��ʾ
//    if(gs_Channel.ucSta == SETB)
//    {
//      gul_Test = (gul_I1DCval>>8)|(uint32)gul_Test<<20;
//    }else
//    {
//      gul_Test = (gul_I2DCval>>8)|(uint32)gul_Test<<20;
//    }
//    gul_Test = gul_DatCFcnt;
    gul_Test = ((uint16)(gul_DataCP>>8))|(gul_Test<<16)|(((uint32)gs_PowerCf.uc_Pz)<<20);
    PowOffShowRefresh();                  //����ˢ��
#endif    
     
//    if(gul_DataCP >= RMSII1_TH)  //1A����ʱ�Ĵ���RMSII1��ֵ(�����Ȳ����֮���ֵ)
//    {
//        gs_WakeUp.ucSlpCnt = 0;
//        gs_WakeUp.ucTmDly = 6;
//        gs_WakeUp.ucType = RTC_SETSEC;
//    }
//    else
//    {
//        gs_WakeUp.ucSlpCnt++;
//        if(gs_WakeUp.ucType == RTC_SETSEC && gs_WakeUp.ucSlpCnt>10)
//        {           
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly  = 0;
//            gs_WakeUp.ucType   = RTC_MIN;
//        }
//        else if(gs_WakeUp.ucType == RTC_MIN && gs_WakeUp.ucSlpCnt>59)
//        {
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly = 0;
//            gs_WakeUp.ucType = RTC_HOUR;
//        }
//        else if(gs_WakeUp.ucType == RTC_HOUR && gs_WakeUp.ucSlpCnt>23)
//        {
//            gs_WakeUp.ucSlpCnt = 0;
//            gs_WakeUp.ucTmDly = 0;
//            gs_WakeUp.ucType = RTC_DAY;
//        }
//    }
//    RTCWakeUpTm(gs_WakeUp.ucType, gs_WakeUp.ucTmDly);  
    RTCWakeUpTm(RTC_SETSEC, 6);
    SleepRTC();
}
/*=========================================================================================\n
* @function_name: Pwr_WakeupProc
* @function_file: Powmanger.c
* @����: ���߻��Ѵ���
* 
* 
* @����: 
* @����:  
* @����:   lm (2014-04-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//void Pwr_SleepProc(void)
//{
//    SLPWDT();     
//    CloseFD();
//    if(guc_PowOffRuning)
//    {
//        gs_DispStt.ucPwrOffRefresh|=Const_RefreshAll;
//        ShowRefresh();                  //����ˢ��
//    }
//    guc_SleepCnt++;
//    if(guc_SleepCnt>=3)
//    {
//        guc_SleepCnt = 3;
//        Data_RecEnergy();
//        MCUForPowerOff();
//        RTCWakeUpTm(RTC_HOUR,   0);
//    }
//    else
//    {
//        RTCWakeUpTm(RTC_SETSEC, 3);
//    }
//    SleepRTC();    
//}
/*=========================================================================================\n
* @function_name: Pwr_SlpReset
* @function_file: Powmanger.c
* @����: ���߻��Ѵ���
* 
* 
* @����: 
* @����:  
* @����:   lm (2015-03-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Pwr_SlpReset(void)
{
//#if (CONFIG_PT != 0)
//    OpenFD();    
//    DetEnable();    
//#endif
//    P9OE = 0xbf;   //�������
    P1OE &= ~BIT3;
    P1IE &= ~BIT3;
//    P9FS |= BIT6;  //CF��� 
    P13FS = 0x04;
    
    CtrlBGP  &= 0x3f;                           //�������� ADCȫ�ֵ���ƫ�� �������
    CtrlCLK = (CtrlCLK & 0xC3)| 0x28;           //MEA 3.2M  ADC 800K

    Mea_Init();    //������ʼ��
    CtrlADC0 = gs_JbPm.uc_AnaG;                 //����ADC����
    CtrlADC6 = 0x03;                            //IA,IB
    EnyB_SetMeterCfgACK(0x16, PMCtrl1);         //����ͨ��A,�ź�����ͨ��1  I1��I2��������ʹ��
    EnyB_SetMeterCfgACK(0x889374bc, PARABPF);   //3.2M�˲�������
    
    EnyB_SetMeterCfgACK(gs_JbPm.ul_GateOSC, GATEP);   //���ó�����������    
    EnyB_SetMeterCfgACK(0x00, DATACP);       //��������ֵ
    gul_I1rms800k = 0;
    gul_I2rms800k = 0;
    gs_WakeUp.ucIncntA = 10;   //ֱ�Ӹ���ֱ��ֵ
    gs_WakeUp.ucIncntB = 10;
    gs_Channel.ucSta = SETA;

#if (MEA_SLP_FMCU == 1)     
    PowOffSetFmcu(PLL_800K);         //MCUƵ��3.2M����800K
#endif    
    Init_Timer1(80);                //���ö�ʱ��1, MEA 3.2M,ֱ��ֵ������ʱ�� 70ms  
    SLPWDT(); 
    TR1 = 1;
    EA = 1;
    PCON = 1;                                   //MCU����ȴ�Xms
    EA = 0;
    SLPWDT();
#if (MEA_SLP_FMCU == 1)      
    PowOffSetFmcu(PLL_3D2M);       //MCU��3.2M
#endif    
    gul_I1DCval   = EnyB_ReadMeterParaACK(DATAIDI1);    //����A·ֱ��ֵ
    gul_I2DCval   = EnyB_ReadMeterParaACK(DATAIDI2);    //����B·ֱ��ֵ
    
    EnyB_SetMeterCfgACK(0, PMCtrl1);                    //ֹͣ���㣬�����ź� 
    CtrlADC6 = 0;
    EnyB_SetMeterCfgACK(gul_I1DCval,0x1001);            //����A·ֱ��ƫ��
    EnyB_SetMeterCfgACK(IDET_STARTA, IDETTH);           //����A·�����жϷ�ֵ
    EnyB_SetMeterH2L(gs_JbPm.ul_SCI1_800,SCI1);         //д��Ȳ�ֵ��ͬʱ����Ƶ���л��� ��Ƶ
    
    CtrlBGP  |= 0xC0;
    CtrlCLK = (CtrlCLK & 0xC3);           //MEA 800K  ADC 200K    
    
    SLPWDT();
    guc_CfOpenFlg = false;
    gul_DataCP = 0;
    guc_SleepCnt = 0;
    gul_DatCFcnt = 0;
    guc_DatCFrmd = 0;
    gui_DatCFdec = 0;
    RecoverEnergyData();
    gui_SystemState = flgStSys_PowOff;    //�õ���״̬ 
    Init_CfG();
}
/*=========================================================================================\n
* @function_name: Pwr_ChkProc
* @function_file: Powmanger.c
* @����: �ϵ��жϴ���
* 
* 
* @����: 
* @����:  
* @����:   lm (2015-03-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
bool Pwr_ChkProc(void)
{
    uint8 i;
    //�ϵ��ȶ�ʱ��
    
    for(i=0; i<CONFIG_DELAY; i++)
    {
        if(POWERUP())
        {
            break;
        }
//        SLPWDT();               //800kι��
//        DelayOSC(15); 
    }
    SLPWDT();               //800kι��
    if(i >= CONFIG_DELAY && !POWERUP())        //û��
    {  
#if (MEA_SLP_FMCU == 1)      
       if(PowOffSetFmcu(PLL_3D2M) == 0)   //MCU��3.2M
        {
          return false;
        }
#endif 
 //////////////////////////////////////////////////////
//        Init_Timer1(100);         //������
//        SLPWDT(); 
//        TR1 = 1;
//        EA = 1;
//        PCON = 1;                          
//        EA = 0;
//        SLPWDT();
//        RTCWakeUpTm(RTC_SETSEC, 6);
//        SleepRTC();
 //////////////////////////////////////////////////////       
        if((gs_FunCfg.ul_CRC != do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2)) || PORRESET())  //û��ص���ram��
        {
            Pwr_SlpReset();         
        }
        SLPWDT();
//#if (POW_OFF_DISP == 1)        
//        guc_PowOffRuning = true;
//        Pwr_LcdSet();
//#endif        
//#if (CONFIG_PT != 0)        //��PT
//        if(!PwrDetLow())   //�е���        
//        {
//            Pwr_WakeupProc();       //���Ѵ���
//        }
//        else              
//        {
//            Pwr_SleepProc();
//        }
//#else                   //����PT
        if( gui_BatLowFlg == 0x5A5A) //��ص�ѹ�Ͳ�ȥ����
        {
          CtrlADC6=0;      //�ر����е�ADC
          PMG=1;           //�رռ���ʱ��
          MEAFRQ=0; 
          while(MEAFRQ);
          
          RTCWakeUpTm(RTC_HOUR, 0); //Сʱ����
          SleepRTC();
        }else
        {
          Pwr_WakeupProc();       //���Ѵ���
        }
//#endif
        return false;         //����ʧ��
    }
    
    for(i=0; i<20; i++)      //��������400ms
    {
        SLPWDT();               //800kι��
        DelayOSC(15);           //
        if(!POWERUP())          //POWERDN���Բ�����
        {
            IOOFF();                            //�ر����ж����IO
            MCUForPowerOff();
            IntOFF();                           //�ر��жϣ�����жϱ��
            UARTOFF();                          //�ر�����UART
            gs_FunCfg.ul_CRC = do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2) +1;//ʹCRC���󣬻ָ�����
            RTCWakeUpTm(RTC_SETSEC, 6);
//            RTCWakeUpTm(RTC_DAY,0x00);         //1hour����
            Sleep();
            return false;
        }        
    }

    return true;
}
/*=========================================================================================\n
* @function_name: Pwr_ChkProc
* @function_file: Powmanger.c
* @����: �ϵ��жϴ���
* 
* 
* @����: 
* @����:  
* @����:   lm (2015-03-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Pwr_UpProc(void)
{
    
}
