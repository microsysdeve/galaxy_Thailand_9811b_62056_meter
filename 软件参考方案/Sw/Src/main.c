
#define __MAIN__
#define VAREXT

#include "Include.h"

__root const unsigned char __code codepsword[4]@0x400=
{0xff,0xff,0xff,0xff};

/*=========================================================================================\n
* @function_name: Init_Var
* @function_file: main.c
* @����: ��ʼ������
* 
* @����: lwb (2014/3/14)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void Init_Var(void)
{
    guc_ResetFlg = true;
    guc_CfOpenFlg=false;
    gs_PtlCrt.uc_ComStep=0;
    gs_PtlCrt.uc_CompLevel=0;
    guc_SecCnt=0;
    guc_500msCnt=0;
    gul_E2ParaStt = 0x0FFFFFFF;         //��λ��Ĭ�ϲ�������E2��Ч
    gui_SystemSleepState=0;
    MemSet((uint8*)&gs_PDirCnt,0,sizeof(gs_PDirCnt));
    gui_SystemState = 0;
    gui_RefreshEvent=0;
    guc_KeyEvent=0;
    guc_TimeEvent=0;
    gui_SystemEvent=0;
    guc_ShowStCom=0;
    gui_DyPgmOut=0;
    gs_DispStt.ucIndex=0;
    guc_MeterSysSta=0;
    guc_DeamandTimer=0;
}
/*=========================================================================================\n
* @function_name: RTCWakeUPFunc
* @function_file: main.c
* @����: RTC����
* 
* 
* @return: uint8 
* @����: lwb (2014/3/24)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 RTCWakeUPFunc(void)
{
    CLRWDT();
    SetPLL(SETPLL_800K);

    if(gs_DispStt.ucTmr>0)
    {
        gs_DispStt.ucTmr--;
        if(gs_DispStt.ucTmr==0)
        {
            gs_DispStt.ucIndex=0;
            //����
            LCD_Off();
            Init_RTC(RTC_DAY);                      //��ʼ��ΪDAY RTC����
        }else
        {
            Init_RTC(RTC_SEC);                      //��ʼ��Ϊ1S RTC����
            ShowRefresh();
        }
    }
    else
    {
        gs_DispStt.ucIndex=0;
        Init_RTC(RTC_DAY);                      //��ʼ��ΪDAY RTC����
        //����
        LCD_Off();
    }

    Sleep();
    return false;
}
/*=========================================================================================\n
* @function_name: IOWakeUPFunc
* @function_file: main.c
* @����: IO�ڻ���
* 
* 
* @return: uint8 
* @����: lwb (2014/3/24)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 IOWakeUPFunc(void)
{
    CLRWDT();                           //ι��

    SetPLL(SETPLL_800K);
    if(KeyStUp())
    {
        InitLCD();                      //��ʼ��LCD��ʾ
        ShowKeyProc();
    }
    Init_RTC(RTC_SEC);                  //��ʼ��Ϊ1S RTC����
//  CoverScanSleep();                   //���Ǽ��
    Sleep();
    return false;
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
        PowerDnPro();                  //���紦��
        gui_SystemEvent &=~ flgEtGlb_PowDown;
        gui_SystemSleepState=0x55aa;
        //while(1);                                       //˯�߲��ɹ����ȴ����Ź���λ
    }
    else if(gui_SystemEvent & flgEtGlb_EnergyCalc)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        Eny_EnergyProc();                               // �����¼�
        gui_SystemEvent &=~ flgEtGlb_EnergyCalc;
    }
    else if(gui_SystemEvent&flgEtGlb_DemadProc)
    {
        DemandProc();
        gui_SystemEvent &=~flgEtGlb_DemadProc;
    }
    else if(gui_SystemEvent & flgEtGlb_RefreshLcd)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        ShowRefresh();                                  // ��ʾˢ��
        gui_SystemEvent &=~ flgEtGlb_RefreshLcd;
    }
    else if(gui_SystemEvent & flgEtGlb_NeedPrtclChk)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        ComApp_Proc();                                  // ͨѶ�¼�
        gui_SystemEvent &=~flgEtGlb_NeedPrtclChk;
    }
    else if(gui_SystemEvent&flgEtGlb_ClearMeter)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        Data_ClearMeter();
        gui_SystemEvent&=~flgEtGlb_ClearMeter;
    }
    else if(gui_SystemEvent&flgEtGlb_FirstPulse)
    {
        if(!(Systate&BIT0))                         //
        {
            return;
        }
        EnyB_FstPluseProc();
        gui_SystemEvent&=~flgEtGlb_FirstPulse;
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
        TimerProc();                                    // ��ͣ����е��¾�����
        EnyB_Open_Cf();
        ShowSecondProc();
        EnyB_Check_PowRev();                           //���ʷ����ж�
        Demand_1s();
        guc_TimeEvent &= ~flgEtTim_Second;              //
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
    }
    else                                                //
    {                                                   //
        guc_TimeEvent = 0;                              //
    }
}
/*=========================================================================================\n
* @function_name: RefreshPara
* @function_file: DataProtect.c
* @����: ����ˢ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void RefreshPara(void)
{
    if(gui_RefreshEvent & flgEtPara_EnyBottom)
    {
        Eny_RefVar();
        gui_RefreshEvent &= ~flgEtPara_EnyBottom;
    }
    else if(gui_RefreshEvent&flgEtPara_Fee)
    {
        getFee();
        gui_RefreshEvent&=~flgEtPara_Fee;
    }
    else if(gui_RefreshEvent&flgEtPara_Bode)
    {
        Init_Uart2(0, 0);        // ��ʼ��ģ�⴮��
        Init_Uart4(0, 0);        // ��ʼ��ģ�⴮��
        gui_RefreshEvent&=~flgEtPara_Bode;
    } 
    else if(gui_RefreshEvent & flgEtPara_Init) 
    {
        if(CheckCRCWord(guc_InitWd))
        {
            InitE2Data();
        }
        gui_RefreshEvent&=~flgEtPara_Init;
    }
    else
    {
        gui_RefreshEvent =0;
    }
}
/*=========================================================================================\n
* @function_name: ShowKeyProc
* @function_file: main.c
* @����: 
* 
* @����: lwb (2014/3/25)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void ShowKeyProc(void)
{
    gs_DispStt.ucIndex++;
    if(gs_DispStt.ucIndex>=9)
    {
        gs_DispStt.ucIndex=0;
    }
    gs_DispStt.ucTmr=15;
    ShowRefresh(); 
}

/*=========================================================================================\n
* @function_name: main
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
void main(void)
{
MAINSTART:
    SPC_FNC = 0x01;
    FlashPw = 0x86;
    SPC_FNC = 0;
    XRAMPWD=0x33;   //�������
    //�ж��Ƿ����
    if(!(Systate&BIT0))         // �ж��Ƿ��ѹ��
    {

        gui_SystemState |= flgStSys_PowOff;
        //�ж��Ƿ���IO�ڻ��ѣ�IO���Ѻ���ԡ�
        if(Systate&BIT2)
        {
            if(!RTCWakeUPFunc())
            {
                goto MAINSTART;
            }
        }

        //IO�ڴ���
        if(Systate&BIT3)        //IO����
        {
            if(!IOWakeUPFunc())
            {
                goto MAINSTART;
            }
        }

        SetPLL(SETPLL_800K);
        Eny_PurCheckRAMEny();
        InitLCD();              //LCD��ʼ��
        PowerDnPro();
    }

    CtrlMEAS &=~ BIT7;          //1:LDO33����
    SetPLL(SETPLL_3_2M);
    
//�ȴ���Դ�ȶ�
    SetLDOVolt(SETLDO_24V); 
    CPUInit();              //ϵͳ��ʼ��
//    Disp_Full();
    SleepTimeProc();
    Init_Var();             //��ʼ������
    InitDemand();
    EnyB_SetMeterRule();    //������ʼ��
    RecoverEnegyData();     //�ָ���������
    getFee(); 
    EA=1;                   //���ж�
    while (1)
    {
        CLRWDT();               //ι��
        Check_Sfr();            //���sfr
        if(0x00 != gui_SystemEvent)                     //
        {                                               //
            SysEventProc();                             // ϵͳ�¼�
        }
        else if(0x00!= guc_TimeEvent)                   //
        {
            if(!(Systate&BIT0))                         //
            {
                continue;
            }
            TimeEventProc();                            // ʱ�䴦������
        }                                               //
        else if(0x00 != gui_RefreshEvent)               //
        {   
            if(!(Systate&BIT0))                         //
            {
                continue;
            }                                            //
            RefreshPara();                              // ����ˢ��
        }                                               //
        else if(0x00 != guc_KeyEvent)                   //
        {     
            if(!(Systate&BIT0))                         //
            {
                continue;
            }                                          //
            KeyProc();                                  // ��������
        }

        if(gui_SystemSleepState==0x55aa)
        {
            goto MAINSTART;
        }
    }
    
    
}


