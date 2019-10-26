#define MCUDRIVEEXT
#define RTCCPTEXT
#include "Include.h"
#include "powerevent.h"
#define V98x1A1
#include "Timer0Capture.h"
/*=========================================================================================\n
* @function_name: IO_Init
* @function_file: main.c
* @����: 
* 
* @����: 
* @����: 
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-7-26)
* @�޸�����:  
===========================================================================================*/
void IO_Init(void)
{
    //PxOE 1��ֹ��� 0�������
    //PxIE 1�������� 0��ֹ����
  	/*  IO      �ܽ�       ����     LED��I2C��������
		P0.0	/TDO       ���0    FX    ����LED
		P0.1    /TDI       ���0    DLZS  ����ָʾ
		P0.2    /TMS       ���0    SDA    
		P0.3	/TCK       ���0    SCL
		P0.4	/NO USE
		P0.5	/NO USE
		P0.6	/NO USE
		P0.7	/NO USE
	*/
    P0OE = 0; 
    P0IE = 0;
    P0OD = 0;
	/*  IO      �ܽ�       ����
		P1.0   /NO USE		 
		P1.1   /RXD1/T1/INT2                       
		P1.2   /TXD1/T2EX/INT3/MEACLK                   
		P1.3   /RXD5/INT0/CFx/SP/PLLDIV/WAKEUP	 
		P1.4   /TXD5/INT1/PLLDIV/WAKEUP1 	     
		P1.5   /NO USE			
		P1.6   /NO USE	
		P1.7   /NO USE	
	*/
    P1OE  = 0;	
    P1IE  = 0;
    P1OD  = 0;
    P11FS = 0;
    P12FS = 0;
    P13FS = 0;
    P14FS = 0;  
	/*  IO      �ܽ�       ����
		P2.0	/T2/RXD4/OSC     TXD4  
		P2.1    /T0/TXD4/PLL     RXD4        
		P2.2    /NO USE       
		P2.3	/NO USE       
		P2.4	/RXD2       JD   LED earth       
		P2.5	/TXD2       BG	 ����          
		P2.6	/NO USE        
		P2.7	/NO USE          
	*/
    P2OE = 0xff;    //LED��UART��������
    P2IE = 0;
	/*  IO      �ܽ�       ����
		P3.0	/COM0      ���0       
		P3.1    /COM1      ���0        
		P3.2    /COM2      ���0       
		P3.3	/COM3      ���0       
		P3.4	/NO USE          
		P3.5	/NO USE  
		P3.6	/NO USE               
		P3.7	/NO USE 
	*/	
    P3OE = (BIT0+BIT1+BIT2+BIT3);
    P3IE = 0;
	/*  IO      �ܽ�       ����
		P4.0	/COM4/SEG0 ���0       
		P4.1    /COM5/SEG1 ���0        
		P4.2    /NO USE        
		P4.3	/NO USE        
		P4.4	/NO USE          
		P4.5	/NO USE  
		P4.6	/NO USE               
		P4.7	/NO USE 
	*/			
    P4OE = 0xff;
    P4IE = 0;
    //P4OD &= ~(BIT0+BIT1);
	/*  IO      �ܽ�       ����
		P5.0	/SEG1      ���0
		P5.1    /SEG2      ���0
		P5.2    /SEG3      ���0
		P5.3	/SEG4      ���0
		P5.4	/SEG5      ���0
		P5.5	/SEG6      ���0
		P5.6	/SEG7      ���0
		P5.7	/SEG8      ���0
	*/
	P5OE = 0xff;   //�������
    P5IE = 0;   //��ֹ����
	/*  IO      �ܽ�       ����
		P6.0	/NO USE
		P6.1    /NO USE
		P6.2    /SEG9      ���0
		P6.3	/SEG10     ���0
		P6.4	/SEG11     ���0
		P6.5	/SEG12     ���0
		P6.6	/SEG13     ���0
		P6.7	/SEG14     ���0
	*/
	P6OE = 0xff;   //�������
    P6IE = 0;   //��ֹ����
    //P6OD = 0;   //���0
	/*  IO      �ܽ�       ����
		P7.0	/NO USE
		P7.1    /NO USE
		P7.2    /NO USE
		P7.3	/NO USE
		P7.4	/NO USE
		P7.5	/NO USE
		P7.6	/SEG15     ���0
		P7.7	/SEG16     ���0
	*/  
	P7OE = 0xFf;   //�������
    P7IE = 0x00;   //��ֹ����
    //P7OD = 0;   //���0
	/*  IO      �ܽ�       ����
		P8.0	/SEG17     
		P8.1    /SEG18     
		P8.2    /SEG19     
		P8.3	/NO USE
		P8.4	/NO USE     
		P8.5	/NO USE
		P8.6	/NO USE      
		P8.7	/NO USE
	*/
    P8OE = 0;   //�������
    P8IE = 0;   //��ֹ����
    //P8OD=0;   //���0
    /*  IO      �ܽ�       ����
		P9.0	/SEG20     
		P9.1    /TA1/SDSP  
		P9.2    /TA2       
		P9.3	/PLLDIV    
		P9.4	/NO USE         
		P9.5	/CF2       
		P9.6	/CF1       CF1      
		P9.7	/NO USE
	*/	
    P9OE = 0xf3;   //�������
    P9IE = 0x09;   //��ֹ����
    P9OD = 0;   //���0
//    P9FS = BIT6;
     _multiOut_Nor();
    CloseFD();
}
/*=========================================================================================\n
* @function_name: Init_Timer0
* @function_file: main.c
* @����: ��ʼ����ʱ��0
* 
* @����: 
* @����: 
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-8-8)
* @�޸�����:  
===========================================================================================*/
void Init_Timer0(void)
{
    //CKCON &= ~BIT3;         //1/12clk
    CKCON |= BIT3;          //1clk
    TMOD  &= 0xf0;
    TMOD  |= 0x01;          //��ʱ��Ϊģʽ1    
    TH0    = 0xEF;          //��ʱ5ms
    TL0    = 0xFF;          //������һ�ν��жϵ�ʱ���趨
    TR0    = 1;             //����ʱ��0
    IE    |= BIT1;
}
/*=========================================================================================\n
* @function_name: Init_Timer1
* @function_file: main.c
* @����: ��ʱ��1��ʱΪ10ms
* 
* @����: 
* @����: 
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-8-9)
* @�޸�����:  
===========================================================================================*/
void Init_Timer1(uint16 tm)
{
    uint16 tmp;
    TR1 = 0;                // ��ʱ������ʱ��1 
    CKCON &= ~BIT4;         // 1/12clk
    TMOD &=~ BIT3;          // ��ʱ��Ϊ��ʽ1 16λ������
    TMOD |= BIT4;           // ��ʱ��Ϊ��ʽ1 16λ������
//#if (MEA_SLP_FMCU == 1)
//    tmp = 65535 - tm*68*4;//mcu 3.2M
//#else  
    tmp = 65535 - tm*68;//mcu 800k
//#endif
    TH1 = tmp>>8;           // ��ʱ400ms
    TL1 = tmp;              // ������һ�ν��жϵ�ʱ���趨    
    IE |= BIT3;             // TIME1 interrupt       
}
/*=========================================================================================\n
* @function_name: Init_Timer2
* @function_file: main.c
* @����: ��ʱ��2��ʱΪ10ms
* 
* @����: 
* @����: 
* @����:
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  xuqf (2013-1-15)
* @�޸�����:  
===========================================================================================*/
void Init_Timer2(void)
{
    CKCON &= ~BIT5;         // 1/12clk
    T2CON &= ~BIT1;         // ����ʱ����
    TH2    = 0xF5;          // ��ʱ10ms
    TL2    = 0x54;          // ������һ�ν��жϵ�ʱ���趨
    TR2    = 1;             // ������ʱ��2
    IE    |= BIT5;          // TIME2 interrupt
}
/*=========================================================================================\n
* @function_name: Delay1OSC
* @function_file: McuDrive.c
* @����: ��ʱ1OSC ��13Mpll ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Delay1OSC(void)
{
    for(uint8 i=0;i<20;i++)
    {
    
    }
} 
/*=========================================================================================\n
* @function_name: DelayOSC
* @function_file: McuDrive.c
* @����: ��13M��Ƶ����ʱnum��OSC
* 
* 
* @����: 
* @param:num  ����
* @����: 
* @����:   lwb (2012-03-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DelayOSC(uint8 num)
{
    for(uint8 i=0;i<num;i++)
    {
        Delay1OSC();
    }
}
/*=========================================================================================\n
* @function_name: RTCWakeUpTm
* @function_file: McuDrive.c
* @����: RTC����ʱ��
* 
* 
* @����: 
* @param:Tm  1s-00��1min-01   1hour-02  62.5ms,1~62S-07
* @����: 
* @����:   lwb (2012-10-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void RTCWakeUpTm(uint8 Tm, uint8 Sec)
{

    RTCPEN=0x96;            
    RTCPWD=0x57;
    DelayOSC(5);
    INTRTC=Tm;
    if(Tm == RTC_SETSEC)
    {
        SECINT = (BIT6|Sec);
    }
    DelayOSC(5);
    RTCPEN=0x96;
    RTCPWD=0x56;
    DelayOSC(5);
}
/*=========================================================================================\n
* @function_name: EnableRTCInt
* @function_file: McuDrive.c
* @����: ����RTC�ж�
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-28)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnableRTCInt(void)
{
    EIE|=BIT1;              //���ж�
    ExInt3IE|=BIT6;
}
/*=========================================================================================\n
* @function_name: DisableRTCInt
* @function_file: McuDrive.c
* @����: �ر�RTC�ж�
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-28)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DisableRTCInt(void)
{
    ExInt3IE&=~BIT6;    //���ж�
}
/*=========================================================================================\n
* @function_name: RTCInitForSleep
* @function_file: Timeproc.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
/*void RTCInitForSleep(void)
{
    RTCPEN=0x96;        //1S����
    RTCPWD=0x57;
    DelayOSC(5);
    INTRTC=0x00;
    DelayOSC(5);
    RTCPEN=0x96;
    RTCPWD=0x56;
    DelayOSC(5);
}*/
/*=========================================================================================\n
* @function_name: Mcu_Init
* @function_file: Init.c
* @����: ��ʼ��MCU��LCD ��TIMER0�� 
* 
* @����: 
* @����: 
* @����:   lim (2011-12-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Mcu_I1nit(void)
{
    PRCtrl0 = CONFIG_PRCTRL0;
    PRCtrl1 = CONFIG_PRCTRL1;  
    IO_Init();              //IO��ʼ��                
    InitLCD();             //LCD��ʼ��
//    OpenBeiGuang();
 //    Disp_Full();            //��ʾȫ��
    Init_Uart();            //Uart��ʼ��
    Init_Timer0();          //ע����ms
    Init_Timer2();          //��ʼ����ʱ��2
   // Key_Init();              //������ʼ��
    KeyPortIn();
    OpenPortIn();
    RTCWakeUpTm(RTC_DAY, 0);   //RTC��ʼ�� 1HOUR
    EnableRTCInt();         //����RTC���ж�
}
/*=========================================================================================\n
* @function_name: SetPLL13M
* @function_file: McuDrive.c
* @����: PLL�л���13M
* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 SetPLL13M(uint8 MEA)
{
    uint8 i=0;
    CtrlCLK=0xEb;               //ADC 800K  dsp 3.2M MCU 13M;
    CtrlPLL=BIT6;               //13M
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //��һ��ʱ����û������
        }
    }
    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //��һ��ʱ����û������
        }
    }
    if(MEA == MEA_ON)
    {
        MEAFRQ=1;
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
                return false;       //��һ��ʱ����û������
            }
        }
    }
    CtrlCry0 = 0x00;                //����������
    CtrlCry1 = 0x03;
    CtrlCry2 = BIT5;
    CtrlBGP  = 0x04;//0x34;//0x32;//0x3A;//0x30;
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //��СLDO25���-δȷ�ϣ��رյ�ط���
     CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    CtrlM    = BIT0;
    guc_PllSta = PLL_13M;
      
    return true;
} 
/*=========================================================================================\n
* @function_name: SetPLL3DOT2M
* @function_file: McuDrive.c
* @����: PLL�л���3.2M
* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 SetPLL3DOT2M(uint8 MEA)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;

    CtrlCLK=0xEA;               //MCU3.2M MEA3.2M ADC809.6K
    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //��һ��ʱ����û������
        }
    }

    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //��һ��ʱ����û������
        }
    }
    
    if(MEA)
    {
        MEAFRQ=1;                 
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
                return false;       //��һ��ʱ����û������
            }
        }
    }
    CtrlCry0 = 0x00;        //����������
    CtrlCry1 = 0x03;        //��ͣ����
    CtrlCry2 = BIT5;        //�����·��λʹ��
    CtrlBGP  = 0x04;//0x34;//0x32;//0x3A;//0x30;        //Ĭ��+20ppm�����Ƹߵ������
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //��СLDO25���-δȷ�ϣ��رյ�ط���
    CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    guc_PllSta = PLL_3D2M;
    
     TimerA_Capture_App_Init();
    return true;
}

/*=========================================================================================\n
* @function_name: PowOffSetPLL
* @function_file: McuDrive.c
* @����: ���߻���ʱPLL�л�
* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 PowOffSetFmcu(uint8 SetFmcu)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;
if(SetFmcu == PLL_3D2M)
    CtrlCLK = (CtrlCLK & 0xFC)| 0x02;      //MCU 3.2M 
else
    CtrlCLK = (CtrlCLK & 0xFC);            //MCU 800K

    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
            return false;       //��һ��ʱ����û������
        }
    }

    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            return false;       //��һ��ʱ����û������
        }
    }
if(SetFmcu == PLL_3D2M)    
    guc_PllSta = PLL_3D2M;
else
    guc_PllSta = PLL_3D2M;
    return true;
}
/*=========================================================================================\n
* @function_name: SetPLL800K
* @function_file: McuDrive.c
* @����: 800k
* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-09-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 SetPLL800K(uint8 MEA)
{
    uint8 i;
    i=0;
    FWC=0;
    FSC=0;
  
    CtrlCLK=0xC0;               //MCU 800K  MEA 800K  ADC 200K
    CtrlPLL=0;                  //
    while(!(PLLLCK&BIT0))
    {
        i++;
        if(i>50)
        {
         debug_break( _debug_errno_SetPLL800K_FAIL1_) ;   return false;       //��һ��ʱ����û������
        }
    }
    
    MCUFRQ=1;
    i=0;
    while(!(MCUFRQ))
    {
        i++;
        if(i>20)
        {
            debug_break( _debug_errno_SetPLL800K_FAIL2_) ;   return false;       //��һ��ʱ����û������
        }
    }
    
    if(MEA == MEA_ON)
    {
        MEAFRQ=1;                 
        i=0;
        while(!(MEAFRQ))
        {
            i++;
            if(i>20)
            {
               debug_break( _debug_errno_SetPLL800K_FAIL3_) ;    return false;       //��һ��ʱ����û������
            }
        }
    }
    
    CtrlCry0 = 0x00;        //����������
    CtrlCry1 = 0x03;        //��ͣ����
    CtrlCry2 = BIT5;        //�����·��λʹ��
    CtrlBGP  = 0xC4;//0xF4;//0xF2;//0xFA;//0xF0;        //Ĭ��+20ppm�����Ƹߵ�������Сƫ�õ������͹���
#if (CONFIG_VCC == 0)
    CtrlLDO  = 0x80;        //��СLDO25���-δȷ�ϣ��رյ�ط���
    CtrlLDO = 0x00 | ( _LcdVolMod_Null_ )<<3;
#else
    CtrlLDO = 0x00;
#endif
    guc_PllSta = PLL_800K;
    
    return true;
}
/*=========================================================================================\n
* @function_name: MChannelCal
* @function_file: McuDrive.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-30)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
 

void MChannelCal(void)
{
 
    if((gs_DateTime.ucSecond==0x05))
    {
        //GetBat();                                                   //��ȡ��ص�ѹ
       
      
    }else  if((gs_DateTime.ucSecond==0x07)||(gs_DateTime.ucSecond==0x08))
    {
        if(CtrlADC5!=0x81)
        {
            CtrlADC5=0x81;
        }
    }
//    else if(gs_DateTime.ucSecond==0x15 && guc_FrsCalRTCDelay == 0)  //ÿ���ӵ�10s
//    {
//        CalRTC();
//    }
}

 
/*=========================================================================================\n
* @function_name: GetBat
* @function_file: McuDrive.c
* @����: �����ص�ѹ
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-30)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/

 
void GetBat(void)
{
    volatile Word32 tempvalue;
//    {
        CtrlADC5=0x97;                              //M2ͨ��������ز�������

        DelayXms(30);                               //��ʱ30ms
        tempvalue.lword=EnyB_ReadMeterParaACK(DATAOM);

        if(tempvalue.byte[3]>0x80)                  //������յ�ʱ���ȡ�����Ǹ�ֵ
        {
            tempvalue.lword=(~tempvalue.lword)+1;
        }
        tempvalue.lword = tempvalue.lword >> 16;
        tempvalue.lword = ((tempvalue.lword*100+5069)/5959);
//        tempvalue.lword=(tempvalue.lword+BATOFFSET)/BATDIV;     //�����ص�ѹ

        gul_CellVoltage=tempvalue.lword;

        if(tempvalue.lword<=BATLEVEL)                       //��ص�ѹ����������,��ظ澯
        {
            gui_BatLowFlg = 0x5A5A;
//            gul_ShowState|=flgShowSt_Bat;
            gut_SysWarn.SysWarn.BatLow=true;
//            gs_MeterState.ui_MeterState1.RunCode1Word.MeterCell=true;
//            gs_MeterState.ui_MeterState1.RunCode1Word.RTCCell=true;
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt == false      //ʱ�ӵ�ص� ״̬��־δ��
//               && gs_ReportWord.ui_ReportWord1.ReportWord1.RtcBatRpt == 1)           //ʱ�ӵ�ص� ��Ҫ�����ϱ�
//            {
//                gs_ReportState.ui_ReportState1.ReportWord1.RtcBatRpt = true;         //ʱ�ӵ�ص� ״̬��λ
//            }
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt == false      //ʱ�ӵ�ص� ״̬��־δ��
//               && gs_ReportWord.ui_ReportWord1.ReportWord1.CutBatRpt == 1)           //ʱ�ӵ�ص� ��Ҫ�����ϱ�
//            {
//                gs_ReportState.ui_ReportState1.ReportWord1.CutBatRpt = true;         //ʱ�ӵ�ص� ״̬��λ
//            }
        }
        else
        {
            gui_BatLowFlg = 0;
//            gul_ShowState&=~flgShowSt_Bat;
            gut_SysWarn.SysWarn.BatLow=false;
//            gs_MeterState.ui_MeterState1.RunCode1Word.MeterCell=false;
//            gs_MeterState.ui_MeterState1.RunCode1Word.RTCCell=false;
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt == true)     //ʱ�ӵ�ص� �ж�״̬��־
//            {
//                gs_ReportStateFlg.ui_ReportState1.ReportWord1.RtcBatRpt = false;
//            }
//            if(gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt == true)     //ʱ�ӵ�ص� �ж�״̬��־
//            {
//                gs_ReportStateFlg.ui_ReportState1.ReportWord1.CutBatRpt = false;
//            }
        }

//        guc_CheckBatFlg=false;
        CtrlADC5=0x81;      //�л����¶Ȳ���
//    }
}
/*=========================================================================================\n
* @function_name: ChangeBodeProc
* @function_file: McuDrive.c
* @����: �޸Ĳ����ʴ���
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-31)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Init_Uart(void)
{
 
#ifndef  _ComUSE645_    
    guc_485Bode=_bps300_;
    
    Init_Uart2(guc_485Bode);
    ComBom_Init(ComIndex_Uart2);    //��uart2 �˿ڶ�Ӧ�� COM��ʼ��
    Init_Uart4(_bps300_);//guc_485Bode);
    ComBom_Init(ComIndex_Uart4);    //��uart4 �˿ڶ�Ӧ�� COM��ʼ��
#endif
}
/*=========================================================================================\n
* @function_name: IOOFF
* @function_file: McuDrive.c
* @����: ���紦��IO��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void IOOFF(void)
{
    CloseBeiGuang();  //�رձ���
    P1OE |= BIT4; 
    P1IE &=~ BIT4;
    LCD_Off();
    
    //IR 485
    P20FS=0;
    P21FS=0;
    P24FS=0;
    P25FS=0;
    P2OE|=(BIT0+BIT1+BIT4+BIT5);   //��ֹ���
    P2IE&=~(BIT0+BIT1+BIT4+BIT5);
    
    KeyPrDisable();//��̼�
    
    P0OE |= BIT1;    //����  ����   
    P0IE &= ~BIT1;        
    P0OD &= ~BIT1;
    
    P0OE |= BIT2;    //TMS ����
    P0IE &= ~BIT2;   
    P0OE |= BIT3;    //TCK  ����
    P0IE &= ~BIT3;  
    
    P9OE |= BIT0;    //pwrdet  ����
    P9IE &= ~BIT0;   
    P1OE |= BIT4;    //DDjc  ����
    P1IE &= ~BIT4;     
    
#if (MEA_SLP_CF == 0)    
    P1OE|= BIT3;        //CF IO����
    P1IE &= ~BIT3;
    P13FS = 0x0;
#else
    P1OE &= ~BIT3;
    P1IE &= ~BIT3;
    P13FS = 0x04;
#endif
    
#if(CONFIG_PT == 1)
    DetEnable();  
#endif
}
/*=========================================================================================\n
* @function_name: PowUpLedCtl
* @function_file: McuDrive.c
* @����: �ϵ米�⣬LED����
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void PowUpLedCtl(void)
{
    if(gs_DispCont.ucPowUpBgTm!=0)
    {
//        OpenBeiGuang();         //�ϵ翪���⣬����ʱ������ʾ��ʼ������
    }
}
/*=========================================================================================\n
* @function_name: IntOFF
* @function_file: McuDrive.c
* @����: �ر��ж�
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void IntOFF(void)
{
  debug_break(_debug_fun_IntOFF_);
    IE=0;
    EIE=0;
    EXIF=0;
}
/*=========================================================================================\n
* @function_name: UARTOFF
* @function_file: McuDrive.c
* @����: �ر�UART
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void UARTOFF(void)
{
    TCON2=0;
    TCON3=0;
    TCON4=0;
    CFGA=0;
}
/*=========================================================================================\n
* @function_name: MCUForPowerOff
* @function_file: McuDrive.c
* @����: ���紦��
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void MCUForPowerOff(void)
{
    uint8 i;
    CtrlADC6 = 0;                         //��ADͨ��
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);   //��CF
    EnyB_SetMeterCfgACK(0x00,PMCtrl1);   //ֹͣ���㣬�����ź�

    for(i=0;i<20;i++);

    PMG=1;                              //�رռ���ʱ��
}

/*=========================================================================================\n
* @function_name: SwichPluseOutType
* @function_file: McuDrive.c
* @����: �л����ӹ���
* 
* 
* @����: 
* @param:type  0-RTC  2-ʱ��Ͷ��
* @����: 
* @����:   lwb (2012-06-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
/*
void SwichPluseOutType(uint8 type)
{
    if(type==0)
    {
        P9FS|=BIT3;                                                     //���RTC
        P9OE&=(~BIT3);
    }
    if(type==2)
    {
        P9FS&=(~BIT3);
        P9OE&=(~BIT3);
    }
}
*/

/*=========================================================================================\n
* @function_name: SleepRTC
* @function_file: McuDriver.c
* @����: ��LDO33;
*        ��AD;
*        ��ֹ������·����˫��ram;
*        �ر����м���ͨ��;
*        ��PMʱ��;
*        ��ϵͳ�е���Ƶ����;
*        ��PLL;
*        ��ϵͳ���ٽ���ǳ˯�ߡ� 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lim (2011-12-11)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 SleepRTC(void)
{
    uint8 i;

   // gs_KeyCtr[UpKey].Status=KeyRls;             //��������Ϊ�ͷ�
      GPIO_Init_OffLine1();
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();                     //I2C�����
//    FWC=0;
//    FSC=0;
//    if((Systate&BIT0)==0x01)
//    {   
//        return false;
//    }
//    CtrlADC6=0;                 //�ر����е�ADC
//
//    for(i=0;i<20;i++);          //�ȴ�

//    PMG=1; //�رռ���ʱ��
    if (_IsUpIo()) //  if((Systate&BIT0)==0x01)
    {   
        return false;
    }

    MCUFRQ=0;
    while(MCUFRQ);
    
//    MEAFRQ=0; 
//    while(MEAFRQ);

    if (  _IsUpIo()) //  if((Systate&BIT0)==BIT0)
    {   
        return false; 
    }

    for(i=0;i<3;i++);           //�ȴ�

    CtrlCLK=0x00;
    while(CtrlCLK); 
     
    SLEEP0=1;

    return false;               //˯�߲��ɹ����ش���
}

/*=========================================================================================\n
* @function_name: Sleep
* @function_file: McuDrive.c
* @����: ��LDO33;
*        ��AD;
*       ��ֹ������·����˫��ram;
*       �ر����м���ͨ��;
*       ��PMʱ��;
*       ��ϵͳ�е���Ƶ����;
*       ��PLL;
*       ��ϵͳ���ٽ���ǳ˯��;* 
* @����: 
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 Sleep(void)
{
    uint8 i;
    FWC=0;
    FSC=0;

    // RTCWakeUpTm(RTC_SEC);
    //gui_SystemState |= flgStSys_PowOff;    //�õ���״̬

    if((Systate&BIT0)==0x01)    //�е�
    {   
        return false;
    }

    //CtrlADC6=0;             //�ر����е�ADC
    //LCDCtrl=0;
    //LCDG=1;
    //CtrlLDO|=BIT5;
    

//    for(i=0;i<20;i++);      //�ȴ�
//
//    PMG=1;                  //�رռ���ʱ��

    if((Systate&BIT0)==0x01)
    {   
        return false;
    }

    MCUFRQ=0;
    while(MCUFRQ);

//    MEAFRQ=0;
//    while(MEAFRQ);

    if((Systate&BIT0)==0x01)
    {   
        return false; 
    }

    for(i=0;i<3;i++);       //�ȴ�

    CtrlCLK=0x00;
    while(CtrlCLK);

    SLEEP0 = 1;
    DelayOSC(5);
    return false;           //˯�߲��ɹ�������FLASE
}
/*=========================================================================================\n
* @function_name: BgCtrFun
* @function_file: McuDrive.c
* @����: �������
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void BgCtrFun(void)
{
    if(guc_WorkMd != NormalMode)
    {
//        CloseBeiGuang();//�رձ���
    }
    else
    {
//        OpenBeiGuang();       
    }
}
#ifdef _SW_EXT_RTC
/*=========================================================================================\n
* @function_name: GetExtRTC
* @function_file: McuDrive.c
* @����: ��ȡӲ��ʱ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-02-29)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void GetExtRTC(void)
{
    volatile uint8 RTCFLAG ;
    RTCFLAG = RDRTC;
    DelayOSC(5);
    gs_ClkTmp.ucSecond  = RTCSC;
    gs_ClkTmp.ucMinute  = RTCMiC;
    gs_ClkTmp.ucHour    = RTCHC;
    gs_ClkTmp.ucWeek    = RTCWC;
    gs_ClkTmp.ucDay     = RTCDC;
    gs_ClkTmp.ucMonth   = RTCMoC;
    gs_ClkTmp.ucYear    = RTCYC;
}
 
void SetExtRTC(void)
{
    //RTC����д 
    RTCPEN = 0x96;      //password 1
    RTCPWD = 0x57;      //password 2
    DelayOSC(5);
    //дRTCʱ��
    RTCYC   = gs_DateTime.ucYear;
    RTCMoC  = gs_DateTime.ucMonth;
    RTCDC   = gs_DateTime.ucDay;
    RTCHC   = gs_DateTime.ucHour;
    RTCMiC  = gs_DateTime.ucMinute;
    RTCSC   = gs_DateTime.ucSecond;
    RTCWC   = gs_DateTime.ucWeek;
    DelayOSC(5);
    //RTC��ֹд  
    RTCPEN = 0x96;
    RTCPWD = 0x56;
    DelayOSC(5);
}
#endif

/*=========================================================================================\n
* @function_name: Check_Sfr
* @function_file: McuDrive.c
* @����: �������⹦�ܼĴ���
* 
* @����: 
* @����: 
* @����:   lwb (2012-07-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Mcu_ChkSfr(void)
{
//    if(!OSCSTATE())
//    {
//    }
    
    if(EIE!=0xE3)
    {
        EIE=0xE3;
    }
    if(IE!=0xA2)
    {
        IE=0xA2;
    }

    if(guc_CfOpenFlg==false)
    {
       if((ExInt2IE&0x8C)!=0x8C)
       {
           ExInt2IE|=0x8C;
       }
    }else
    {
        if((ExInt2IE&0x0C)!=0x0C)
        {
           ExInt2IE|=0x0C;
        }
    }

//  if(ExInt3IE!=0x40)
//  {
//      ExInt3IE=0x40;
//  }
    if( P20FS!=0x02
        ||P21FS!=0x02)
//        ||P24FS!=0x02
//        ||P25FS!=0x02)
    {
        P20FS=0x02;
        P21FS=0x02;
//        P24FS=0x02;
//        P25FS=0x02;
    }   
}
/*=========================================================================================\n
* @function_name: Mcu_RTCNormal
* @function_file: McuDrive.c
* @����: ��ʹ��RTC���ܱ�Ĭ������
*
*
* @����:
* @����:
* @����:   lm (2014-07-09)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Mcu_RTCNormal(uint8 Pll)
{
    uint32 ul_div;

    //FCpyTMem((uint8 *)&gs_DateTime, (uint8 code*)&InitTM, 7);      
    RTCPEN = 0x96;
    RTCPWD = 0x57;
    DelayOSC(2);
    RTCCH  = 0;
    RTCCL  = 0;
  //  ul_div = Pll * 4096UL *100 - 1;
   // DIVTHH = ul_div>>16;
   // DIVTHM = ul_div>>8;
  //  DIVTHL = ul_div;
    
    RTC_Format (FlashInfo.lRtcJZPara);
    DelayOSC(2);
    RTCPEN = 0x96;
    RTCPWD = 0x56;
#if (CONFIG_RTC==0)
    FCpyTMem((uint8 *)&gs_DateTime, (uint8 code*)&InitTM, 7);
    SetExtRTC();   
#endif
}
/*=========================================================================================\n
* @function_name: Mcu_PendTm
* @function_file: McuDrive.c
* @����: Mcu����
*
*
* @����:
* @����:
* @����:   lm (2014-04-22)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 Mcu_PendTm(uint8 Xms)
{	
    uint8 tmp;
	Debug_Break(	_debugh_fun_Mcu_PendTm_);
    tmp = EA;
//	if((CtrlCLK&0x03) == 0x02)
    if(guc_PllSta != PLL_800K)
    {       
        DelayXms(Xms);
        return 1;
    }
    else
    {
        Init_Timer1(Xms);          //���ö�ʱ��1
        EA = 1;
        TR1 = 1;
        guc_PendSlpSta = 0x01;
        while(guc_PendSlpSta)    
            PCON = 1;              //MCU����ȴ�xms
        EA = tmp;
        return 0;
    }
}