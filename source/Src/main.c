#define __MAIN__
#define VAREXT

#include "Include.h"
#include "PubSet.h"
__root const unsigned char __code codepsword[512]@0x400=
{ 
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

/*=========================================================================================\n
* @function_name: Init_Var
* @function_file: main.c
* @����: ��ʼ��ϵͳȫ�ֱ����Ͳ���
*
* @����:
* @����:
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-8-9)
* @�޸�����:
===========================================================================================*/
void Var_Init(void)
{
    gui_SystemState   = 0;  
    gui_SystemEvent   = 0;      //ϵͳ�¼�
    guc_TimeEvent     = 0;      //ʱ���¼�
    gui_RefreshEvent  = 0;      //ˢ���¼�
    guc_KeyEvent      = 0;      //�����¼�
    gui_SysSleepSta   = 0;      //���������߱�־
    
    guc_BodeDely      = 0;
//    guc_CfOpenFlg     = true;
//    guc_CfOpenCnt     = 0;      //��CF����

    guc_ShowStCom     = 0;      //ͨ����ʾ����
    
//    guc_ErrSwPt=0;
//    guc_ErrCodeCnt=0;
    gs_SysRunSt.Pdir=0;
    gut_SysWarn.byte=0;
    
    guc_ComSendDy     = 0;      //645������ʱ

    gs_Channel.ucSta = SETA;         //����ͨ��ѡ��
    guc_SleepCnt = 0;           //���߼���
   
    guc_FactoryType = 0;        //����״̬��־
    gs_PtlCrt.uc_ComStep=0;
    gs_PtlCrt.uc_CompLevel=0;
    
}

/*=========================================================================================\n
* @function_name: SysEventProc
* @function_file: main.c
* @����: ϵͳ�¼���������
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void SysEventProc(void)
{
  
    if(gui_SystemEvent & flgEtGlb_PowDown)              
    {                                                   
        Pwr_DownProc();                  //���紦��
        gui_SystemEvent &=~ flgEtGlb_PowDown;           
        gui_SysSleepSta = 0x55aa;
        //while(1);                                       //˯�߲��ɹ����ȴ����Ź���λ
    }                                                   
    else if(gui_SystemEvent & flgEtGlb_EnergyCalc)      
    {                                                   
        Eny_EnergyProc();                               // �����¼�
        gui_SystemEvent &=~ flgEtGlb_EnergyCalc;        
    }
    else if(gui_SystemEvent & flgEtGlb_DemadProc)
    {
        Demand_Proc();
        gui_SystemEvent &=~flgEtGlb_DemadProc;
    }
    else if(gui_SystemEvent & flgEtGlb_RefreshLcd)      
    {                                                   
        ShowRefresh();                                  // ��ʾˢ��
        gui_SystemEvent &=~ flgEtGlb_RefreshLcd;        
    }                                                   
    else if(gui_SystemEvent & flgEtGlb_NeedPrtclChk)    
    {                                                   
        ComApp_Proc();                                  // ͨѶ�¼�
        gui_SystemEvent &=~flgEtGlb_NeedPrtclChk;       
    }
//    else if( gui_SystemEvent&flgEtGlb_ClearEv)         //�����¼��¼�
//    {
//        Data_ClearEvent();
//        gui_SystemEvent&=~flgEtGlb_ClearEv;
//    }
    else if(gui_SystemEvent&flgEtGlb_AutoCal)
    {
        //EnyB_AutoChkSP();
        gui_SystemEvent&=~flgEtGlb_AutoCal; 
    }
    else if(gui_SystemEvent&flgEtGlb_ClearMeter)
    {
        Data_ClearMeter();
        gui_SystemEvent&=~flgEtGlb_ClearMeter;
    }
    else
    {
        gui_SystemEvent = 0;                            //��ֹ����ʱ,����ѭ������Ĵ�����Զ������
    }
}
/*=========================================================================================\n
* @function_name: TimeEventProc
* @function_file: main.c
* @����: ϵͳʱ���¼�����
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-09)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void TimeEventProc(void)
{
    if(guc_TimeEvent & flgEtTim_Second)                 // �봦��
    {       
        Data_SecProc();
        guc_TimeEvent |= flgEtTim_SecSoft;
        guc_TimeEvent &= ~flgEtTim_Second;              
    }
    else if(guc_TimeEvent&flgEtTim_Minute)
    {
        Data_MinProc();
        guc_TimeEvent&=~flgEtTim_Minute;
    }                                                   //
    else if(guc_TimeEvent & flgEtTim_Hour)              // Сʱ�¼�
    {                                                   //
        Data_HourProc();
        guc_TimeEvent &= ~flgEtTim_Hour;                //
    }else if(guc_TimeEvent & flgEtTim_Day)
    {
        Data_DayProc();
        guc_TimeEvent &=~flgEtTim_Day;
    }
    else if(guc_TimeEvent & flgEtTim_Year)
    {
        Data_YearProc();
        guc_TimeEvent &=~flgEtTim_Year;
    }
    else if(guc_TimeEvent & flgEtTim_SecSoft)
    {
        if(guc_CfOpenFlg == false)
        {
            BgCtrFun();
        }
        MChannelCal();                                  // ����M
//        KeyScan();
        guc_TimeEvent &= ~flgEtTim_SecSoft;
    }
    else                                                //
    {                                                   //
        guc_TimeEvent = 0;                              //  
    }
}
/*=========================================================================================\n
* @function_name: Init_CfG
* @function_file: main.c
* @����: ��ʼ������
* 
* @����: 
* @����: 
* @����:   lwb (2012-11-05)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Init_CfG(void)
{
    if(gs_FunCfg.ul_CRC != do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2))
    {
        MemSet(&gs_FunCfg.uc_CbrCfg,0,sizeof(GSFUNCFG)-3);//����������
        gs_FunCfg.uc_CfSaveCfg = 0x50;
        gs_FunCfg.uc_ENSHOWCfg = 0x02;
        gs_FunCfg.ul_CRC=do_CRC(&gs_FunCfg.uc_CfSaveCfg,sizeof(GSFUNCFG)-2);       //�����������crc
    }
}
/*=========================================================================================\n
* @function_name: App_Init
* @function_file: main.c
* @����: ��ʼ������
* 
* @����: 
* @����: 
* @����:   lwb (2012-11-05)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void App_Init(void)
{
    Demand_Init();          //��ʼ����������
    DataSecurityInit();
    //ShowSysStart();         //��ʾ�ϵ��ʼ��
    Mcu_RTCNormal(guc_PllSta);         //RTCĬ�ϳ�ʼ��
    Tamp_Init();
    EnyB_Init();
}
/*=========================================================================================\n
* @function_name: Mea_Consumption_Dly
* @function_file: main.c
* @����:
* 
* @����: 
* @����: 
* @����:   lwb (2012-11-05)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
bool Mea_Consumption_Dly(void)
{
    OpenFD();
    for(uint8 i=0; i<5; i++)
    {
      SLPWDT();               //800kι��
      DelayOSC(20);
    }
    if(!(Systate&BIT0))      // �ж��Ƿ��ѹ��
    {
      RTCWakeUpTm(RTC_SETSEC, 6);
      
      SLEEP0=1;
      return false;               //˯�߲��ɹ����ش���
    }else
    {
      CloseFD();
      return true;
    }
}
/*=========================================================================================\n
* @function_name                    : main
* @function_file: main.c
* @����: ���������
*
* @����:
* @����:
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-7-20)
* @�޸�����:
===========================================================================================*/

__near_func void m1ain(void)
{
  
  debug_init();
  
MAINSTART:
    if(!(Systate&BIT0))      // �ж��Ƿ�VDCIN��
    {  
        if(SetPLL800K(MEA_OFF) == 0)   //MCU��800K
        {
            goto MAINSTART;
        }
        SLPWDT();                      //ι��   
        if(false == Pwr_ChkProc())     //ϵͳ�ϵ��ж�
        {
            goto MAINSTART;
        }
    }
    SLPWDT();
    if(false == Mea_Consumption_Dly()) //�ŵ���ʱ�жϹ����Ƿ��ȶ�
    {
        goto MAINSTART;
    }
    if(SetPLL800K(MEA_OFF) == 0)   //VDCIN��ʱ��MCU��800K
    {
      goto MAINSTART;
    }
    SLPWDT();               //800kι��
    Mcu_Init();             //ϵͳ�ײ��ʼ��
    SLPWDT();               //800kι��
    App_Init();             //ϵͳӦ�ò��ʼ��
    SLPWDT();               //800kι��
    // Mea_Init();             //������ʼ��           
    SLPWDT();               //800kι��   
    Var_Init();             //ϵͳ������ʼ��-Ӧ���ܷŵ�appinit��
    SLPWDT();               //800kι��
    Data_RecPara();         //ϵͳ���ݻָ�
    SLPWDT();               //800kι��
    GetBat();               //�õ���ص�ѹ
    SLPWDT();               //800kι��
    EA = 1;                 //�����ж�
    //InitE2Data();
    while (1)
    {
        CLRWDT();               //ι��
        Mcu_ChkSfr();           //���sfr
#if (CONFIG_PT == 0)
        if(!POWERUP())
#else
        if(!POWERUP() && PwrDetLow())
#endif       
        {
            gui_SystemEvent |= flgEtGlb_PowDown;
        }
        if(0x00 != gui_SystemEvent)                     //
        {                                               //
            SysEventProc();                             // ϵͳ�¼�
        }   
        else if(0x00 != guc_TimeEvent)                  //
        {                                               //
            TimeEventProc();                            // ʱ�䴦������
        }                                               //
        else if(0x00 != gui_RefreshEvent)               // 
        {                                               //
            RefreshPara();                              // ����ˢ��
        }                                               //
        else if(0x00 != guc_KeyEvent)                   //
        {                                               //
            KeyProc();                                  // ��������
        }

        if(gui_SysSleepSta == 0x55aa)
        {
            goto MAINSTART;
        }
    }
}
