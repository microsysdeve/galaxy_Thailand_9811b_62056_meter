#define  ENERGYBOTTOMEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: EnyB_Init
* @function_file: EnergyBottom.c
* @����: �ײ��ʼ��
* 
* 
* @����: 
* @����: 
* @return:  
* @����:   liming (2016-01-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
//uint8  guc_FactoryType;

void EnyB_Init(void)
{
    gs_PDirCnt.ucDirCnt = 0;
    gs_PDirCnt.ucRevDirCnt = 0;
    gs_PDirCtr.ucDelayTm = CONFIG_POW_DLY;
    gs_PDirCtr.ulPDirGate = ((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/1000;
    
    gs_Channel.ucSta = 0;
    gs_Channel.ucACnt = 0;
    gs_Channel.ucBCnt = 0;
    gs_Channel.ucGate = CONFIG_CH_DLY;
}
/*=========================================================================================\n
* @function_name: WaitACK
* @function_file: EnergyBottom.c
* @����: �ȴ���ʱ��������ACK��0-1-0��
* 
* 
* @����: 
* @����: 
* @return:  
* @����:   hexz (2015-02-11)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void WaitACK(void)
{
    uint16 i;

    if (MEAFRQ)                 //PMʱ��ΪPLL
    {
        for (i = 0; i < 9; i++)
        {
            _nop();
        }
        for (i = 0; i < 76; i++)
        {
            if (!XBYTE[ACK])
                break;
        }
    }else                       //PMʱ��ΪOSC
    {
        if (MCUFRQ)                     //MCUʱ��ΪPLL
        {
            for (i = 0; i < 240; i++)
            {
                _nop();
            }
            for (i = 0; i < 1920; i++)
            {
                if (!XBYTE[ACK])
                break;
            }
        }else                           //MCUʱ��ΪOSC
        {
            for (i = 0; i < 1; i++)
            {
                _nop();
            }
            for (i = 0; i < 2; i++)
            {
                if (!XBYTE[ACK])
                break;
            }
        }
        return;
    }
    return;
}
/*=========================================================================================\n
* @function_name: EnyB_ReadMeterParaACK
* @function_file: EnergyBottom.c
* @����: ˫��ram���ã�ʹ��ACK�ź�
* 
* 
* @����: 
* @param:addr  ���ݵ�������ַ
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint32 EnyB_ReadMeterParaACK1(uint16 addr)
{
//    udata8 index;
    uint32  u32PMdatal;
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    u32PMdatal=XBYTE[addr];                          //��ȡ��ʵ��ַ���������ݵ�����
    WaitACK();
    if (XBYTE[ACK])
    {
      debug_break(_debug_errno_EnyB_ReadMeterParaACK_);
      return false;
    }
//    u32PMdatal=(uint32)XBYTE[BUFF0];
//    temp=(uint32)XBYTE[BUFF1]<<8;
//    u32PMdatal+= temp;
//    temp=(uint32)XBYTE[BUFF2];
//    temp=temp<<16;
//    u32PMdatal+=temp;
//    temp=(uint32)XBYTE[BUFF3];
//    temp=temp<<24;
//    u32PMdatal+=temp;
    u32PMdatal  = 0;
    u32PMdatal |= XBYTE[BUFF3];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF2];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF1];
    u32PMdatal<<= 8;
    u32PMdatal |= XBYTE[BUFF0];
    
    return u32PMdatal;
     
}

uint32 EnyB_ReadMeterParaACK (uint16 addr)
{
      uint32  u32PMdatal ;
      _Interrupt_AppDisable() ;
      u32PMdatal =EnyB_ReadMeterParaACK1( addr) ;
      _Interrupt_AppEnable();   
      return u32PMdatal;
}

/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @����: ˫��ram���ã�ʹ��ACK�ź�
* 
* 
* @����: 
* @param:u32PMdatal  ����
* @param:addr        ��ַ
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 EnyB_SetMeterL2H(uint32 u32PMdatal ,uint16 addr)
{
    uint8 i,index;
    volatile uint32 temp;
    index=0;
    
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }
    
    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    XBYTE[addr]=0;
    MEAFRQ = 1;                               //�����иߵ�Ƶ
    while(!MEAFRQ)
    {
        i++;
        if(i>30)
        {
            break ; //��һ��ʱ����û������
        }
    }    
                                  //�������ĵ�ַд��0�������������뵽�����ĵ�ַ
    	

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }

    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @����: ˫��ram���ã�ʹ��ACK�ź�
* 
* 
* @����: 
* @param:u32PMdatal  ����
* @param:addr        ��ַ
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
volatile unsigned long kiki;
uint8 EnyB_SetMeterH2L(uint32 u32PMdatal ,uint16 addr)
{
    uint8 i,index;
    volatile uint32 temp;
    index=0;
      kiki  =u32PMdatal ;
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }

    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    
    MEAFRQ = 0;                               //�����иߵ�Ƶ
    while(MEAFRQ)
    {
        i++;
        if(i>30)
        {
            break ; //��һ��ʱ����û������
        }
    }    
    
    XBYTE[addr]=0;                              //�������ĵ�ַд��0�������������뵽�����ĵ�ַ	

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }

    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfgACK
* @function_file: EnergyBottom.c
* @����: ˫��ram���ã�ʹ��ACK�ź�
* 
* 
* @����: 
* @param:u32PMdatal  ����
* @param:addr        ��ַ
* 
* @����: 
* @return: uint8 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 EnyB_SetMeterCfgACK1(uint32 u32PMdatal ,uint16 addr)
{
    uint8 index;
    volatile uint32 temp;
    index=0;
    
    void            Value_put ( unsigned long lData, unsigned short iAddr ) ;
    extern unsigned  long  iReg[];
    
     Value_put ( u32PMdatal, addr );
    
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }

    XBYTE[BUFF0]=(uint8)(u32PMdatal&0xff);
    XBYTE[BUFF1]=(uint8)((u32PMdatal>>8)&(0xff));
    XBYTE[BUFF2]=(uint8)((u32PMdatal>>16)&(0xff));
    XBYTE[BUFF3]=(uint8)((u32PMdatal>>24)&(0xff));
    XBYTE[addr]=0;                              //�������ĵ�ַд��0�������������뵽�����ĵ�ַ

//  for(index=0;index<CFGDELAY;index++)
    {   
        nop();
    }


    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {   
            return false;
        }
    }
    
    return true;
}
uint8 EnyB_SetMeterCfgACK(uint32 u32PMdatal ,uint16 addr)
{
  uint8  cresult;
    _Interrupt_AppDisable();
      cresult = EnyB_SetMeterCfgACK1(u32PMdatal,  addr);
  _Interrupt_AppEnable();
  return cresult;
}


/*=========================================================================================\n
* @function_name: InitADC
* @function_file: EnergyBottom.c
* @����: ��ʼ����ʼ��ADC�����������ͨ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void InitADC(uint8 MeaClk)
{
    CtrlADC0 = 0x00;   //ͨ��ģ����������, У���������
    CtrlADC1 = 0x00;   //ADCն����ƫ�õ������ã�Ĭ��Ϊ0
    CtrlADC2 = 0x00;   //ADCն����ƫ�õ������ã�ͨ����λ��Ĭ��Ϊ0
    CtrlADC3 = 0x00;   //ADCʱ����ͨ����·���ã�Ĭ��Ϊ0
    CtrlBAT  = 0x00;   //��طŵ���ƣ�Ĭ��Ϊ0
    CtrlADC4 = 0x00;   //ADC������ƫ�õ�ѹ���ã�Ĭ��Ϊ0
    CtrlADC5 = 0x00;   //Mͨ������
    CtrlM    = BIT0;   //���Ʋ�����������
    if(MeaClk)
    {
        CtrlADC6 = 0;   //ģ��ͨ������
    }
    else
    {
        CtrlADC6 = ADCAPDN+ADCBPDN+ADCUPDN+ADCMPDN;   //ģ��ͨ������
    }   
}
/*=========================================================================================\n
* @function_name: InitMeaClk
* @function_file: EnergyBottom.c
* @����: ����ʱ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void InitMeaClk(void)
{
    uint8 i;
    
    MEAFRQ=1;                 
    i=0;
    while(!(MEAFRQ))
    {
        i++;
        if(i>20)
        {
            return;       //��һ��ʱ����û������
        }
    }
}
/*=========================================================================================\n
* @function_name: InitPMDSP
* @function_file: EnergyBottom.c
* @����: �����Ĵ�����ʼ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-12)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void InitPMDSP(uint8 MeaClk)
{
    uint8 i;
    
    PMG = 0;
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl1);   
    EnyB_SetMeterCfgACK(INITGATEP,GATEP);        //���ü�����ʼֵ
    EnyB_SetMeterCfgACK(INITGATEQ,GATEQ);
    if(MeaClk)
    {
        EnyB_SetMeterCfgACK(0x911d3c9c, PARABPF);      //800k�˲�������  
    }
    else
    {
        EnyB_SetMeterCfgACK(0x889374bc, PARABPF);      //3.2M�˲�������
    }
    
    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
    EnyB_SetMeterCfgACK(0xC8,PMCtrl4);
    EnyB_SetMeterCfgACK(0x08,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
    
    EnyB_SetMeterCfgACK(0x01,GATECP);       //Ǳ��1   
    EnyB_SetMeterCfgACK(0x01,GATECQ);       //Ǳ��2
    if(MeaClk)
    {
        EnyB_SetMeterCfgACK(0x13,PMCtrl1);      //������ͨ��
        EnyB_SetMeterCfgACK(0x05,CFCtrl);       //������ֵ��CF
    }
    else
    {
        EnyB_SetMeterCfgACK(0x5F,PMCtrl1);      //��������ͨ��
        EnyB_SetMeterCfgACK(0x00,CFCtrl);       //��+������ֵ��CF
    }
    EnyB_SetMeterCfgACK(0x00,PMCtrl2);      //
    EnyB_SetMeterCfgACK(0x70,PMCtrl3);      //������·�й�����г������
    EnyB_SetMeterCfgACK(0xc0,PMCtrl4);      //�ȴ��˲����ȶ�����
//    if(MeaClk)    //800K��������
//    {
//        EnyB_SetMeterCfgACK(0x10,CRPST);        //�ȴ��˲����ȶ�����
//        EnyB_SetMeterCfgACK(0xfA,PMCtrl4);      //�ȴ��˲����ȶ�����
//    }
//    else
//    {
//        EnyB_SetMeterCfgACK(0x00,CRPST);        //�ȴ��˲����ȶ�����
//        EnyB_SetMeterCfgACK(0xf8,PMCtrl4);      //�ȴ��˲����ȶ�����
//    }
    EnyB_SetMeterCfgACK(0, PHCCtrl1);       //��0
    EnyB_SetMeterCfgACK(0, PHCCtrl2);
    guc_CfOpenFlg     = true;
    guc_CfOpenCnt     = 0;      //��CF����
}
/*=========================================================================================\n
* @function_name: EnyB_Open_Cf
* @function_file: EnergyBottom.c
* @����: ����CF����
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_Open_Cf(void)
{   
//    if(guc_RtcConflict==0x55)
//    {
//        gui_RefreshEvent|=flgEtPara_RTC;    
//        guc_RtcConflict=0x00;
//    }

    if(guc_CfOpenCnt<1)
    {
        guc_CfOpenCnt++;
    }else
    {
        if(guc_CfOpenFlg&&(guc_CfOpenCnt>=1))
        {   
            if(guc_WorkMd != NormalMode)
            {
                EnyB_SetMeterCfgACK(0x10,CRPST);
                EnyB_SetMeterCfgACK(0xFA,PMCtrl4);  //�򿪼���,����Ǳ������
            } 
            else
            {
                EnyB_SetMeterCfgACK(0x00,CRPST);
                if(gs_Channel.ucSta == SETB)                    //Bͨ��                                        
                {
                    EnyB_SetMeterCfgACK(0xFC,PMCtrl4);  //�򿪼���,����Ǳ������
                }
                else
                {
                    EnyB_SetMeterCfgACK(0xF8,PMCtrl4);  //�򿪼���,����Ǳ������
                }
            }                         
            EnyB_InitCFInt();                   //����CF�����ж�
            guc_CfOpenFlg=false;
        }
    }
}
/*========================================================
* @function_name: EnyB_InitCFInt
* @function_file: EnergyBottom.c
* @����: ��ʼ��CF�ж�
* 
* @����: lwb (2012/3/3)
* @��ע: 
*----------------------------------------------------------
* @�޸���: 
* @�޸�����:  
============================================================*/
void EnyB_InitCFInt(void)
{
    EIE|=BIT0;
    ExInt2IE|=BIT7;
//    P9OE&=(~BIT6);                          //��CF IO���
//    P9FS|=(BIT6);
    _CfPluse_E1Out();  
    //P1OE&=(~BIT3);
    //P1IE&=(~BIT3);
    //P13FS = 0x04;  //CFx CF1���
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterRule
* @function_file: EnergyBottom.c
* @����: ���ü���ģ������
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void Mea_Init(void)
{
    InitADC(MEA3D2M);     //��ʼ��ADC�����������ͨ��
    InitMeaClk();         //�м���ʱ�Ӻ󣬲��ܶ�ȡ����
    SLPWDT();
    //Data_RecEnergy();     //�ָ���������    
    //SLPWDT();
    InitPMDSP(MEA3D2M);   //PM DSP init�����ü���ֵ����ֹ�ҳ�����
    SLPWDT();
    EnyB_PurInit();       //����ģ���ϵ��ʼ��
    _CfPluse_OutEnable() ;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterRule
* @function_file: EnergyBottom.c
* @����: ���ü���ģ������
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_SetMeterRule(uint8 MeaClk)
{
    InitADC(MeaClk);       //��ʼ��ADC�����������ͨ��
    CLRWDT();
    InitPMDSP(MeaClk);     //PM DSP init�����ü���ֵ����ֹ�ҳ�����
    CLRWDT();
    Eny_RefVar();                                       //��������ˢ��
//    EnyB_PurInit();         //����ģ���ϵ��ʼ��
}
/*=========================================================================================\n
* @function_name: EnyB_PurInit
* @function_file: EnergyBottom.c
* @����: �ϵ��ʼ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_PurInit(void)                                 
{
    Eny_RefVar();                                       //��������ˢ��
    Eny_RefCalcType();                                  //������ʽ��ˢ��
    Eny_PurCheckRAMEny();                               //���RAM����
}
//extern const uint8 code InitPara0[sizeof(S_JBPM)-2];
/*=========================================================================================\n
* @function_name: EnyB_JbPm_Init
* @function_file: EnergyBottom.c
* @����: У������ĳ�ʼ��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_JbPm_Init(void)                                
{                                                        
    FCpyTMem((uint8*)&gs_JbPm.ui_MeterC, InitPara0, sizeof(S_JBPM)-2);              //����Flash���ݵ�RAM��
    gs_JbPm.ui_JbCRC=do_CRC((uint8*)&gs_JbPm,sizeof(S_JBPM)-2);     // У�������CRC���
}

/*=========================================================================================\n
* @function_name: EnyB_IntCF
* @function_file: EnergyBottom.c
* @����: �����ж�
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
#ifdef _DEL
void EnyB_IntCF(void)                       
{
    uint8 *pCfZ;
    uint8 *pEyZ;

//    uint8 *pCf;
//    uint8 *pEy;


    //if(gs_SysRunSt.Pdir)      //�ж��Ƿ��Ƿ���
//    {
//        pEyZ=&gs_Energy.ucNz;
//        pCfZ=&gs_PowerCf.uc_Nz;
//    }
//    else
//    {
        pEyZ=&gs_Energy.ucPz;                                   //��������
        pCfZ=&gs_PowerCf.uc_Pz;                                 //����������
//    }
    RamData.CF_Buf

    (*pCfZ)++;                                                  //�������ۼ�
    if(*pCfZ >= guc_GateCF)                                     //�б��Ƿ���Ҫ����
    {
        *pCfZ -=guc_GateCF;                                     //��CF������з�Ƶ������Ƶ������������ۼ�
        *pEyZ +=guc_UnitCF; 
        gui_SystemEvent |= flgEtGlb_EnergyCalc;                 //�������������¼�
    }
 
//    if((gs_FunCfg.uc_CfSaveCfg&0x0F)==0x05)                     //CF����ַ��ʼ���
//    {
//        if(gs_MeterState.ui_MeterState2.RunCode2Word.PADIR)     //�ж��Ƿ��Ƿ���
//        {
//            pEy=(&gs_Energy.ucN1+gs_FeeData.uc_FeeNo);          //���������
//            pCf=(&gs_PowerCf.uc_N1+gs_FeeData.uc_FeeNo);        //�����������
//
//        }else                                                   //����
//        {
//            pEy=(&gs_Energy.ucP1+gs_FeeData.uc_FeeNo);          //������������
//            pCf=(&gs_PowerCf.uc_P1+gs_FeeData.uc_FeeNo);        //��������������
//        }
//
//        (*pCf)++;                                              //����ַ��������ۼ�
//        if(*pCf>=guc_GateCF)                                   // �б��Ƿ���Ҫ����
//        {
//            *pCf -=guc_GateCF;                                 // ��CF������з�Ƶ������Ƶ������������ۼ�
//            *pEy +=guc_UnitCF; 
//            gui_SystemEvent |= flgEtGlb_EnergyCalc;             //�������������¼�
//        }
//    }
}
#endif
/*=========================================================================================\n
* @function_name: CalRMS
* @function_file: EnergyBottom.c
* @����: ����˲ʱ��
* 
* 
* @����: 
* @param:addr  �Ĵ�����ַ
* 
* @����: 
* @return: uint32 ������Чֵ
* @����:   lwb (2012-05-22)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint32 CalRMS(uint16 addr)
{
  Word32 TempValue,TempValue2;
  uint32 TempPara,TempValue1;
  //TempValue.lword=0;
  if(addr == DATAP && gs_Channel.ucSta == SETB)
  {
      addr = DATAQ;
  }
  TempValue.lword=EnyB_ReadMeterParaACK(addr);

  switch (addr)
  {
    case DATAP:
        if(TempValue.byte[3]>0x7f)          //����Ǹ����������ȱ������
        {
            TempValue.lword=~TempValue.lword+1;
        }

        TempPara=gs_JbPm.ul_PG/256;        //��ȡ����ϵ��
       
        if(TempPara==0)
        {    
            TempValue1=0;
        }
         else
        {     
             TempValue.lword=((TempValue.lword*32)/TempPara)*8;
        }
        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
        {
             TempValue1=0;
        }
        else
        {
           //  TempValue1=Hex2BCD(TempValue.lword);
              TempValue1= TempValue.lword;
             if(gs_SysRunSt.Pdir==true)   //������Ӹ���
             {
                 TempValue1 =-TempValue1 ;//_NegLogeo_Set(TempValue1);//=0x800000;
             }
        }
        break;
    case DATAQ:
        if(TempValue.byte[3]>0x7f)          //����Ǹ����������ȱ������
        {
            TempValue.lword=~TempValue.lword+1;
        }

        TempPara=gs_JbPm.ul_PG/256;        //��ȡ����ϵ��
       
        if(TempPara==0)
        {    
            TempValue1=0;
        }
         else
        {     
             TempValue.lword=((TempValue.lword*32)/TempPara)*8;
        }
        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
        {
             TempValue1=0;
        }
        else
        {
             //  TempValue1=Hex2BCD(TempValue.lword);
              TempValue1= TempValue.lword;
             if(gs_SysRunSt.Pdir==true)   //������Ӹ���
             {
                 TempValue1 =-TempValue1 ;//_NegLogeo_Set(TempValue1);//=0x800000;
             }
        }
        break;
    case RMSU:
         if(guc_PllSta == PLL_800K)
         {
             TempValue.lword=gul_Urms800k;   
         }
         TempPara=gs_JbPm.ul_URmG/65536;   //ReadRMSPara(1);
         if(TempPara==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/TempPara;
         }

         if(TempValue.lword<ULEVEL && guc_FactoryType != FactorMd)
         {    
             return 0;
         }else
         {
             TempValue1=Hex2BCD(TempValue.lword);
         }
         break;
    case RMSI1:
        //�����ļ���
        if(guc_PllSta == PLL_800K)
        {
           TempValue.lword=gul_I1rms800k;    
        }

        TempPara=gs_JbPm.ul_I1RmG/65536;    //ReadRMSPara(2);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }
        
        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2) 
           && guc_FactoryType != FactorMd)
        {    
            return 0;
        }else
        {        
            TempValue1=Hex2BCD(TempValue.lword);

            //���ʵļ���
            TempValue2.lword=EnyB_ReadMeterParaACK(DATAP);
            if(TempValue2.byte[3]>0x7f)                         //����Ǹ����������ȱ������
            {
                TempValue2.lword=~TempValue2.lword+1;
            }

            TempPara=gs_JbPm.ul_PG/256;        //��ȡ����ϵ��

            if(TempPara==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=((TempValue2.lword*32)/TempPara)*8;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)
               && guc_FactoryType != FactorMd)
            {
                //�������С���������ʣ����ǵ���С��0.2A,��������
                if(TempValue1<0x200)
                {
                    TempValue1=0;
                }
            }           
            
            if(gs_SysRunSt.Pdir==true)   //������Ӹ���
            {
               _NegLogeo_Set(TempValue1);//|=0x800000;
            }
        }
        break;
    case RMSI2:
       if(guc_PllSta == PLL_800K)
        {
           TempValue.lword=gul_I2rms800k;    
        }

        TempPara=gs_JbPm.ul_I2RmG/65536;    //ReadRMSPara(3);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }

        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2)
           && guc_FactoryType != FactorMd)
        {    
            return 0;
        }else 
        {    
            TempValue1=Hex2BCD(TempValue.lword);

            //���ʵļ���
            TempValue2.lword=EnyB_ReadMeterParaACK(DATAQ);
            if(TempValue2.byte[3]>0x7f)                         //����Ǹ����������ȱ������
            {
                TempValue2.lword=~TempValue2.lword+1;
            }

            TempPara=gs_JbPm.ul_QG/256;        //��ȡ����ϵ��

            if(TempPara==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=((TempValue2.lword*32)/TempPara)*8;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)
               && guc_FactoryType != FactorMd)
            {
                //�������С���������ʣ����ǵ���С��0.2A,��������
                if(TempValue1<0x200)
                {
                    TempValue1=0;
                }
            }           
            
            if(gs_SysRunSt.Pdir==true)   //������Ӹ���
            {
                _NegLogeo_Set(TempValue1);//|=0x800000;
            }
        }
        break;
      case DATAFREQ:
          TempValue.lword=ADCFRE*100/TempValue.lword;
          if(TempValue.lword>4950&&TempValue.lword<5050)
          {
              TempValue.lword=5000;
          }else if(TempValue.lword<4500)
          {    
              TempValue.lword=4500;
          }else if(TempValue.lword>5500)
          {    
              TempValue.lword=5500;
          }
          TempValue1=Hex2BCD(TempValue.lword);
         break;
    case RMSIU:
         if(guc_PllSta == PLL_800K)
         {
             TempValue.lword=gul_Urms800k;   
         }
         TempPara=gs_JbPm.ul_URmG/65536;   //ReadRMSPara(1);
         if(TempPara==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/TempPara;
         }

         if(TempValue.lword<ULEVEL)
         {    
             return 0;
         }else
         {
             TempValue1=TempValue.lword;
         }
         break;
    default:
        TempValue1=0;
        break;
  }

  return TempValue1;
}
/*=========================================================================================\n
* @function_name: CalCos
* @function_file: EnergyBottom.c
* @����: ���㹦������
* 
* @����: 
* 
* @����: 
* @return: uint16 
* @����:   lwb (2012-06-01)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint16 CalCos(void)
{
    uint8 flag;
    uint32 temp_p,temp_i,temp_u;
    Word32 temp_res,temp_ui;
    temp_p = CalRMS(DATAP);
    flag=0;
    if(temp_p&_NegLogo_)   //0x800000)     //������
    {
        temp_p&=~_NegLogo_ ;//0x800000;  //����ȡ��
        flag=1;
    }
    temp_p = BCD2Hex(temp_p);
    //temp_p = BCD2Hex(CalRMS(DATAP));
    //temp_q = BCD2Hex(CalRMS(DATAQ));
    temp_i = BCD2Hex(0x7fffff&CalRMS(RMSI1));
    temp_u = BCD2Hex(CalRMS(RMSU));
 
    
    temp_res.lword = temp_p*1000;
    temp_ui.lword = temp_u*temp_i/1000;
    temp_res.lword = temp_res.lword/temp_ui.lword;
    
    temp_res.lword = Hex2BCD(temp_res.lword);
    //������������
    if(temp_res.lword>=0x990)              //����0.99�Ļ�ֱ����ʾ1.0
    {    
        temp_res.lword=0x1000;
    }else if((temp_res.lword>=0x490)&&(temp_res.lword<=0x510))        //��0.49��0.51֮��ֱ����ʾ0.5
    {    
        temp_res.lword=0x500;
    }else if((temp_res.lword>=0x790)&&(temp_res.lword<=0x810))        //��0.79��0.81֮��ֱ����ʾ0.8
    {    
        temp_res.lword=0x800;
    }else if(temp_res.lword<=0x100)                                //С��0.1�����,�����й������������ʾ
    {
        if(temp_i>0x050)                           //�е��� 
        {    
            if(temp_p<0x500)                       //��û���й����ʣ���ʾ0.0 
            {
                temp_res.lword=0x0000;
            }
        }
        else
        {                                           //û��������ʾ1.0
            temp_res.lword=0x1000; 
        }
    }
                                                  //������ݼ�����ʾ
    if(flag==1&&temp_res.lword!=0)
    {
        temp_res.word[0]|=0x8000;
    }
    return (uint16)temp_res.word[0];                           
}
/*=========================================================================================\n
* @function_name: EnyB_Check_PowRev
* @function_file: EnergyBottom.c
* @����: ��⹦���Ƿ���
* 
* @����: *channel-ͨ�� junc-���߷�ʽ
* @����: true-���� false-����
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint8 EnyB_ChkPowRev(uint8 *channel, uint8 junc)
{
    int32 l_pa,l_pb,ltempa,ltempb;
    uint32 TempPara;
  volatile  uint32 ulPower;
    uint8 flag;
    
      
    if((*channel == SETA) ||(1))
    {
        l_pa = EnyB_ReadMeterParaACK(DATAP);       
        TempPara=gs_JbPm.ul_PG>>8;          //��ȡ����ϵ��
    }
    //else
    {
        l_pb = EnyB_ReadMeterParaACK(DATAQ);
        TempPara=gs_JbPm.ul_QG>>8;          //��ȡ����ϵ��
    }
    ltempa = (labs(l_pa) >labs(l_pb))?l_pa:l_pb;
    l_pa = ltempa;
    
    
    if(TempPara==0)
    {   //У��������ʼ���ֵΪ0�Ļ���ֱ�ӷ���
        return false;
    }
    //Ĭ�Ϸ���
    if(l_pa<0)
    {                                       
        l_pa = -l_pa;
        if(junc == 0)
        {
            flag = false;       //��������
        }
        else
        {
            flag = true;        //���ʷ���
        }
    }
    else
    {
        if(junc == 0)
        {
            flag = true;        //���ʷ���
        }
        else
        {
            flag = false;       //��������
        }
    }
  
    ulPower=((l_pa*32)/TempPara)*8;
    if(ulPower > gs_PDirCtr.ulPDirGate)
    {
        if(flag == false)
        {
            gs_PDirCnt.ucRevDirCnt=0;
            gs_PDirCnt.ucDirCnt++;
            if(gs_PDirCnt.ucDirCnt>=gs_PDirCtr.ucDelayTm)
            {
               gs_SysRunSt.Pdir=false;
            }
        }
        else
        {
            gs_PDirCnt.ucRevDirCnt++;
            gs_PDirCnt.ucDirCnt=0;
            if(gs_PDirCnt.ucRevDirCnt>=gs_PDirCtr.ucDelayTm)
            {
               gs_SysRunSt.Pdir=true;
            }
        }
    }
    
    return gs_SysRunSt.Pdir;
}
/*=========================================================================================\n
* @function_name: EnyB_Cal_Cos
* @function_file: EnergyBottom.c
* @����: ���㹦������
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
//int16 EnyB_Cal_Cos(void)
//{
//    uint32 ul_PS;
//    int16 CosA = 0;
//    if(gs_EnyInsData.ul_IARms < 40)
//    {
//        return 1000;
//    }
//    ul_PS = gs_EnyInsData.ul_URms*gs_EnyInsData.ul_IARms;
//    ul_PS /= 10000;
//    CosA = (gs_EnyInsData.l_PowerPA * 1000)/ (int32)ul_PS;
//    return CosA;
//}
 
/*=========================================================================================\n
* @function_name: EnyB_JbPm_Updata
* @function_file: EnergyBottom.c
* @����: ˢ��У�������SFR��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-02)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_JbPm_Updata(void)
{//��RAM�е�У��������µ�SFR��
    uint32 *p;
   
    if(guc_PllSta == PLL_800K)
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gateq,GATEP); 
    }
    else
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEP);        //����I1ͨ������������

    }
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEQ);        //����I2ͨ������������ 
    
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECP);      //����I1ͨ������������
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECQ);      //����I2ͨ������������  

    //EnyB_Check_RMSI();
    p=&gs_JbPm.ul_SCP;
    for(uint8 i=0;i<7;i++)                              //���ù��ʣ���ѹ�������Ȳ�ֵ
    {
        EnyB_SetMeterCfgACK(*(p+i),SCP+i);           
    }
    
    if(guc_PllSta == PLL_800K)
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_Gateq,GATEP); 
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1,SCI1);
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2,SCI2);
    }
    
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1,PHCCtrl1);  //����I1�ǲ�ֵ
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2,PHCCtrl2);  //����I2�ǲ�ֵ
    
    CtrlADC0 = gs_JbPm.uc_AnaG;                         //����ADC����
    // if((gs_JbPm.uc_AnaG&0x07)==0x07)                    //IA����40���Ļ�������IA ƫ�õ���
    // {
        // CtrlADC4|=BIT4;             //����ƫ�õ���
    // }else
    // {
        // CtrlADC4&=~BIT4;            //����ƫ�õ���
    // }
}

void Enyb_Reg_ModData(uint16 iAddr ,uint32 lValue, char bitoper)
{
      uint32  lData  ;   
    lData = EnyB_ReadMeterParaACK(iAddr); 
    if ( _Bit_Res_ == bitoper)
    lData &= (lValue);
      else if (_Bit_Set_ == bitoper)
    lData |= lValue;
  EnyB_SetMeterCfgACK(lData  ,iAddr);  
}


void   Enyb_Reg_ModBif( uint16 iAddr ,  char bitnum, char bitoper)
{
  uint32  lData ;
  volatile unsigned long lValue = (( uint32 )1)<<bitnum;
  
  if ( _Bit_Res_ == bitoper)
    lData = (~lValue);
  else if (_Bit_Set_ == bitoper)
    lData = lValue;  
  Enyb_Reg_ModData( iAddr  ,lData,   bitoper);  
}


const struct      STS_JBPMFORMAT  st_jbpmformat[ ]=
{   
    {(int)&(((S_JBPM *)0)->ui_MeterC), sizeof(((S_JBPM *)0)->ui_MeterC)},		  // ����
    {(int)&(((S_JBPM *)0)->ui_Un),sizeof(((S_JBPM *)0)->ui_Un)},		      // ��Ƶ�ѹ
    {(int)&(((S_JBPM *)0)->ui_Ib),sizeof(((S_JBPM *)0)->ui_Ib)},		      // ��Ƶ���
    {(int)&(((S_JBPM *)0)->ul_Gatep),sizeof(((S_JBPM *)0)->ul_Gatep)},		   //�й�������������ֵ32λ
    {(int)&(((S_JBPM *)0)->ul_Gateq),sizeof(((S_JBPM *)0)->ul_Gateq)},		   //�й�������������ֵ32λ
    {(int)&(((S_JBPM *)0)->ul_Gatecp), sizeof(((S_JBPM *)0)->ul_Gatecp)},		  //�й�����Ǳ������ֵ32
    {(int)&(((S_JBPM *)0)->ul_GateOSC), sizeof(((S_JBPM *)0)->ul_GateOSC)},		 //
    {(int)&(((S_JBPM *)0)->ul_SCP),sizeof(((S_JBPM *)0)->ul_SCP)},		     //�й��Ȳ�ֵ 
    {(int)&(((S_JBPM *)0)->ul_SCQ),sizeof(((S_JBPM *)0)->ul_SCQ)},		     //�޹����ʱȲ�
    {(int)&(((S_JBPM *)0)->ul_SCU),sizeof(((S_JBPM *)0)->ul_SCU)},		     //��ѹ��Чֵ�Ȳ�
    {(int)&(((S_JBPM *)0)->ul_SCI1),sizeof(((S_JBPM *)0)->ul_SCI1)},		    //ͨ��I1������Чֵ�Ȳ�
    {(int)&(((S_JBPM *)0)->ul_SCI2),sizeof(((S_JBPM *)0)->ul_SCI2)},		    //ͨ��I2������Чֵ�Ȳ� 
    {(int)&(((S_JBPM *)0)->ul_PARAPC),sizeof(((S_JBPM *)0)->ul_PARAPC)},		  //�й����ʶ��β���
    {(int)&(((S_JBPM *)0)->ul_PARAQC),sizeof(((S_JBPM *)0)->ul_PARAQC)},//�޹����ʶ��β���
    {(int)&(((S_JBPM *)0)->uc_PhcCtrl1), sizeof(((S_JBPM *)0)->uc_PhcCtrl1)},		 //I1ͨ���ǲ�
    {(int)&(((S_JBPM *)0)->uc_PhcCtrl2), sizeof(((S_JBPM *)0)->uc_PhcCtrl2)},		 //I2ͨ���ǲ�
    {(int)&(((S_JBPM *)0)->ul_PG),sizeof(((S_JBPM *)0)->ul_PG)},		      //���ʱ���ϵ��
    {(int)&(((S_JBPM *)0)->ul_QG),sizeof(((S_JBPM *)0)->ul_QG)},		      //���ʱ���ϵ��
    {(int)&(((S_JBPM *)0)->ul_URmG), sizeof(((S_JBPM *)0)->ul_URmG)},		    //��ѹͨ������ϵ��
    {(int)&(((S_JBPM *)0)->ul_I1RmG), sizeof(((S_JBPM *)0)->ul_I1RmG)},		   //����ͨ��1����ϵ��
    {(int)&(((S_JBPM *)0)->ul_I2RmG), sizeof(((S_JBPM *)0)->ul_I2RmG)},		   //����ͨ��2����ϵ��
    {(int)&(((S_JBPM *)0)->ul_SCI1_800), sizeof(((S_JBPM *)0)->ul_SCI1_800)},		//ͨ��I1������Чֵ�Ȳ�
    {(int)&(((S_JBPM *)0)->ul_SCI2_800), sizeof(((S_JBPM *)0)->ul_SCI2_800)},		//ͨ��I2������Чֵ�Ȳ�
    {(int)&(((S_JBPM *)0)->uc_AnaG), sizeof(((S_JBPM *)0)->uc_AnaG)},		 //ģ������(����I2 bit[12:9]��I1 bit[7:4]��U bit[3:0])
    {(int)&(((S_JBPM *)0)->ui_JbCRC), sizeof(((S_JBPM *)0)->ui_JbCRC)},		   // У�������CRC��� 
};

const unsigned char     st_jbpmformatlen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
 
char            st_jbMod(struct      STS_JBPMFORMAT code *sttext , char  *sin)
{
    unsigned char       clen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
    
   // struct      STS_JBPMFORMAT code *sttext = (struct      STS_JBPMFORMAT code *)&(st_jbpmformat[stp->cNo]);
    
    //if ( stp->cNo >=clen)
      //  return 1;
    
      Copy_FlashInfo(((char *)&gs_JbPm) + sttext->cOffset , (char *)sin  ,sttext->cLen);
      EnyB_JbPm_Updata();
    return 0;
}

 struct      STS_JBPMFORMAT code  *     st_jbread( char  *sin)
{
    unsigned char       clen = (sizeof(st_jbpmformat)/sizeof(st_jbpmformat[0]));
    struct          STJBMOD  *stp = (struct          STJBMOD *)sin;
    struct      STS_JBPMFORMAT code *sttext = (struct      STS_JBPMFORMAT code *)&(st_jbpmformat[stp->cNo]);
    
    if ( stp->cNo >=clen)
        return NULL;
    return  sttext;    
}