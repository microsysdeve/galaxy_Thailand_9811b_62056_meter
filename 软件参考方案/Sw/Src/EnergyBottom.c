#define  ENERGYBOTTOMEXT
#include "Include.h"


/*=========================================================================================\n
* @function_name: EnyB_InitAnalog
* @function_file: EnergyBottom.c
* @����: ��û���õ����ļĴ���λ����
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_InitAnalog(void)
{
//  unsigned char xdata *point;
//  point = 0x285d;
//  *point = 0;
//  point++;
//  point++;
// *point = 0;
//  point = 0x2868;
//  *point = 0;
    CtrlSHORT=0;
    CtrlBAT=0;
    CtrlPLL=0;

}

/*=========================================================================================\n
* @function_name: EnyB_InitMeter
* @function_file: EnergyBottom.c
* @����: һ������ϵ�ִ�У����������м����Ĵ���������������ֵ
*
* @����:
* @����:
* @����:   lwb (2012-03-02)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_InitMeter(void)
{
    uint8 i;
    volatile uint8x *p;

    p = (volatile uint8x *)0x2878;
   *p = 0x80;
    p  = (volatile uint8x *)0x10e8;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p++;
    *p = 0;
    for( i = 0x00; i <= 0xe3; i++)
    {
        p  =(volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    for( i = 0xf0; i <= 0xfd; i++)
    {
        p  = (volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    p = (volatile uint8x *)0x10e8;
    *p = 0xbc;
    p++;
    *p = 0x74;
    p++;
    *p = 0x93;
    p++;
    *p = 0x88;
    p++;
    *p = 0;
    for( i = 0xe4; i <= 0xe6; i++)
    {
        p  = (volatile uint8x *)(0x1000+i);
        *p = 0;
        nop();nop();nop();
    }

    p  = (volatile uint8x *)0x10e8;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0xcc;
    p++;
    *p = 0x8c;
    p++;
    *p = 0x01;
    p  = (volatile uint8x *)0x10f4;
    *p = 0;
    nop();nop();nop();
    p  = (volatile uint8x *)0x10fa;
    *p = 0;
    nop();nop();nop();
    p  = (volatile uint8x *)0x10e8;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0xff;
    p++;
    *p = 0x00;
    p  = (volatile uint8x *)0x10f5;
    *p = 0;
    nop();nop();nop();
    p  =(volatile uint8x *) 0x10fb;
    *p = 0;
    nop();nop();nop();
    p =(volatile uint8x *) 0x2878;
    *p = 0x00;
}
/*=========================================================================================\n
* @function_name: EnyB_SetMeterCfg
* @function_file: EnergyBottom.c
* @����:  ���ü�����·�������
*
*
* @����:
* @param:addr  �����Ĵ�����ַ
* @����:
* @����:   lwb (2012-03-02)
* @��ע:    ����������ȫ�ֱ���u32PMdatal��8PMdatah
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_SetMeterCfg(uint16 addr)
{
    volatile uint8x   *p;

    p  = (volatile uint8x *)0x10e8;
    *p = (uint8)(u32PMdatal);
    p++;
    *p = (uint8)(u32PMdatal>>8);
    p++;
    *p = (uint8)(u32PMdatal>>16);
    p++;
    *p = (uint8)(u32PMdatal>>24);
    p++;
    *p = (uint8)(u8PMdatah);
    p  = (volatile uint8x *)addr;
    *p = 0;
    nop();nop();nop();
}
/*=========================================================================================\n
* @function_name: ReadMeterPara
* @function_file: EnergyBottom.c
* @����: ��ȡ������·�������
*
*
* @����:
* @param:addr  �����Ĵ�����ַ
* @����:
* @����:   lwb (2012-03-08)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint32 ReadMeterPara(uint16 addr)
{
    volatile uint8 xdata *u8Point;
    volatile uint32 xdata *u32Point;
    volatile uint8 i;


    u8Point = (volatile uint8x *)addr;
    i  = *u8Point;
    nop();nop();nop();

    u8Point = (volatile uint8x *)0x10ec;
    u8PMdatah = *u8Point;
    u32Point = (volatile uint32x *)0x10e8;
    return *u32Point;                       //���￴һ���Ƿ���ȷ��
}
/*=========================================================================================\n
* @function_name: EnyB_SetADC
* @function_file: EnergyBottom.c
* @����: ���õ�������ѹͨ��
*
*
* @����:
* @param:val_channel  ADC ѡ��ͨ��
*                    SETADC_IA ----����A ͨ��;
*                    SETADC_IB ----����B ͨ��;
*                    SETADC_U ----��ѹͨ��
* @param:val_para  ADC ����ѡ��
*                   SETADC_IT1 ��ӦIA��IBͨ��1������;
*                   SETADC_IT4 ��ӦIA��IBͨ��4������;
*                   SETADC_IT8 ��ӦIA��IBͨ��8������;
*                   SETADC_IT16 ��ӦIA��IBͨ��16������;
*                   SETADC_UT1 ��ӦUͨ��1������;
*                   SETADC_CLOSE �ر���Ӧͨ��
*
* @����:
* @����:   lwb (2012-03-02)
* @��ע: ��ѹADCֻ��1�����棨�����棩������ADCֻ��1��4��8��16��������
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_SetADC(uint8 val_channel,uint8 val_para)
{
    uint8  tmp;
    val_channel &= 0x03;
    tmp = CtrlADC;

    if(val_para&0x80)
    {
        CtrlADC =tmp&(~(0x01<<val_channel));
        return;
    }

    val_para = val_para&0x0f;
    tmp |=(0x01<< val_channel);

    CtrlADC = tmp;

    XBYTE[0x2858+val_channel] = val_para;
}

/*=========================================================================================\n
* @function_name: EnyB_SetMChannel
* @function_file: EnergyBottom.c
* @����: ����Mͨ��
*
*
* @����:
* @param:val_channel  M ͨ���Ĳ���ͨ��ѡ��
*                   0x00: measure the ground;
*                   0x01: measure temperature
*                   0x22: measure battery SETM_VBAT1// ��ѹ��
*                   0x23: measure battery SETM_VBAT2// ��ѹ��
*                   0x03: measure external input VM // ����ѹ
*                   0x04: measure SEG33             // ����ѹ
*                   0x05: measure SEG34             // ����ѹ
*                   0x06: measure SEG35             // ����ѹ
*                   0x07: measure SEG36             // ����ѹ
*                   0x24: measure SEG33             // ��ѹ��
*                   0x25: measure SEG34             // ��ѹ��
*                   0x26: measure SEG35             // ��ѹ��
*                   0x27: measure SEG36             // ��ѹ��
* @param:val_para     M ͨ������ѡ��
*                     SETM_T1 ��Ӧ1������
*                     SETM_T2 ��Ӧ2������
*                     SETM_CLOSE ��ʾ�ر�Mͨ��
*
* @����:
* @����:   lwb (2012-03-02)
* @��ע: M ͨ������ѡ��0x00,0x01,0x11,0x31 �ֱ��Ӧ1,2,4,8 ������,0x80��ʾ�ر�Mͨ��
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_SetMChannel(uint8 val_channel,uint8 val_para)
{
    if(val_para&0x80)
    {
        CtrlADC &= ~0x08;   //��Mͨ��
        CtrlMEAS = 0;
        return;
    }

    CtrlADC |= 0x08;        //��mͨ��
    CtrlGM = val_para&0x01;
    CtrlMEAS &= 0x80;
    CtrlMEAS |= val_channel;
}
/*=========================================================================================\n
* @function_name: EnyB_SetAnlog
* @function_file: initial.c
* @����: ��ʼģ���·
*
* @������
* @���أ�
* @���ߣ�
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:  Lwb (2011-6-27)
* @�޸�����:
===========================================================================================*/
void EnyB_SetAnlog(void)
{
    PMCtrl1 |= 0x50;                        //ʹ�ܽǲ�У����ʹ�ܼ���������I1,I2ͨ��
    PMCtrl2 = 0;
    PMCtrl3 = 0x20;                         //ʹ�ܴ�г�����ƹ���

    EnyB_SetADC(SETADC_U ,SETADC_UT1);      //���õ�ѹͨ������Ϊ1��
    EnyB_SetADC(SETADC_IA ,SETADC_IT16);    //����IAͨ������Ϊ16��
    EnyB_SetADC(SETADC_IB ,SETADC_IT4);     //����IBͨ������Ϊ4��

    PMCtrl1 |= 0x0F;                        //�򿪵�ѹͨ�� IAͨ�� IBͨ��
    PMCtrl4 &= ~BIT0;                       //�й��ۼ�
    CFCtrl = 0;                             //�������Լ���������֮��Ϊ���ݲ���CF
}
/*=========================================================================================\n
* @function_name: EnyB_CalRMS
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
uint32 EnyB_CalRMS(uint16 addr)
{
  Word32 TempValue,TempValue2;
  uint32 TempValue1;
  TempValue.lword=ReadMeterPara(addr);

  switch (addr)
  {
    case DATAP:
        if(TempValue.byte[3]>0x7f)          //����Ǹ����������ȱ������
        {
            TempValue.lword=~TempValue.lword+1;
        }
       
        if(gs_JbPm.ul_PG==0)
        {    
            return 0;
        }
        else
        {     
             TempValue.lword=(TempValue.lword*100/gs_JbPm.ul_PG);
        }

//        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))      //С������������һ�룬ֱ������
//        {
//            return 0;
//        }
//        else
        {
             TempValue1=Hex2BCD(TempValue.lword);                                   

//             if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
//             {
//                 TempValue1|=0x800000;
//             }
        }
        break;
      case RMSU:
//    case RMSIU:
         if(gs_JbPm.ul_URmG==0)
         {    
            return 0;
         }
         else
         {    
             TempValue.lword=TempValue.lword/gs_JbPm.ul_URmG;
         }

//         if(TempValue.lword<(gs_JbPm.ui_Un/100))        //С��10%�ĵ�ѹ������
//         {    
//             return 0;
//         }else
         {
             TempValue1=Hex2BCD(TempValue.lword);
         }
         break;
    case RMSI1:
        //�����ļ���
        if(gs_JbPm.ul_I1RmG==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/gs_JbPm.ul_I1RmG;
        }
        
//        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2))   //С������������1�룬����
//        {    
//            return 0;
//        }
//        else
        {    

            TempValue1=Hex2BCD(TempValue.lword);
            //���ʵļ���
            TempValue2.lword=ReadMeterPara(DATAP);
            if(TempValue2.byte[3]>0x7f)                         //����Ǹ����������ȱ������
            {
                TempValue2.lword=~TempValue2.lword+1;
            }


            if(gs_JbPm.ul_PG==0)
            {    
                TempValue2.lword=0;
            }
            else
            {     
                TempValue2.lword=TempValue2.lword/gs_JbPm.ul_PG;
            }

            if(TempValue2.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100))
            {
                //�������С���������ʣ����ǵ���С��0.2A,��������
                if(TempValue1<0x200)
                {
                    return 0;
                }
            }

//            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
//            {
//                TempValue1|=0x800000;
//            }
        }
        break;
    case RMSI2:
        if(gs_JbPm.ul_I2RmG==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/gs_JbPm.ul_I2RmG;
        }

//        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2))   //С������������1�룬����
//        {    
//            return 0;
//        }
//        else 
        {    
            TempValue1=Hex2BCD(TempValue.lword);
            
//            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
//            {
//                TempValue1|=0x800000;
//            }
        }
        break;
//    case DATAFREQ:
//        TempValue.lword=ADCFRE*100/TempValue.lword;
//        if(TempValue.lword>4950&&TempValue.lword<5050)
//        {
//            TempValue.lword=5000;
//        }else if(TempValue.lword<4500)
//        {
//            TempValue.lword=4500;
//        }else if(TempValue.lword>5500)
//        {
//            TempValue.lword=5500;
//        }
//        TempValue1=Hex2BCD(TempValue.lword);
//       break;
    default:
        TempValue1=0;
        break;
  }

  return TempValue1;
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
    if(guc_OpenCfTmCnt<3)
    {
        guc_OpenCfTmCnt++;
    }
    
    if ((!guc_CfOpenFlg)&&(guc_OpenCfTmCnt>=2))
    {
        guc_CfOpenFlg=true;

        u8PMdatah   =0;
        u32PMdatal = (gs_JbPm.ul_Gatecp<<1);
        EnyB_SetMeterCfg(GATECP);           //��һ������Ǳ�������ƿ��2��
        EnyB_SetMeterCfg(GATECQ);
        EnyB_InitCFInt();                   //����CF�����ж�
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
    PMCtrl4 |= (BIT4+BIT3);         //����CF
    EIE|=0x01;
    ExInt2IE|=BIT7;                 // ����CF�ж�
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
void EnyB_SetMeterRule(void)
{
    EnyB_InitAnalog();      //��ʼ��ģʽ����
    EnyB_InitMeter();       //��ʼ�������Ĵ���
    EnyB_SetAnlog();        //��ʼ��ģ��ͨ��
    EnyB_PurInit();         //����ģ���ϵ��ʼ��
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
    Eny_RefVar();                           //��������ˢ��

    PMCtrl4 |= BIT5;                        // ����Ǳ������
    PMCtrl1 &= ~BIT5;                       //ѡ��I1����
    u32PMdatal = 1;
    EnyB_SetMeterCfg(GATECP);               //����CF֮ǰһֱ������Ͱ����
    EnyB_SetMeterCfg(GATECQ);

    //��һ�����壬����������2��

    u32PMdatal=(gs_JbPm.ul_GatepL<<1);      //��һ�����壬����������2��
    if(gs_JbPm.ul_GatepL>=0x80000000)
    {
        u8PMdatah=(gs_JbPm.uc_GatepH<<1)+1;
    }else
    {
        u8PMdatah=(gs_JbPm.uc_GatepH<<1);
    }
            

    EnyB_SetMeterCfg(GATEP);               //����CF֮ǰһֱ������Ͱ����
    EnyB_SetMeterCfg(GATEQ);
    guc_OpenCfTmCnt=0;                     //��ʱ2s����CF
    Eny_PurCheckRAMEny();                  //���RAM����
}
extern const uint8 code InitPara3[sizeof(S_JBPM)-2];
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

    FCpyTMem((uint8*)&gs_JbPm.ui_MeterC,InitPara3,sizeof(S_JBPM)-2);    //����Flash���ݵ�RAM��
    gs_JbPm.ui_JbCRC=do_CRC((uint8*)&gs_JbPm,sizeof(S_JBPM)-2);         // У�������CRC���
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
void EnyB_IntCF(void)
{
//  if(gs_PDirCnt.PDir==true)                           //�ж��Ƿ��Ƿ���
//  {
//      gs_PowerCf.uc_N ++;                             // ���������ۼ�
//      if(gs_PowerCf.uc_N>=guc_GateCF)                 // �б��Ƿ���Ҫ����
//      {
//          gs_PowerCf.uc_N -=guc_GateCF;               // ��CF������з�Ƶ������Ƶ������������ۼ�
//          gs_Energy.ucN +=guc_UnitCF;
//          gui_SystemEvent|=flgEtGlb_EnergyCalc;       //�������������¼�
//      }
//  }
//  else
    {
        gs_PowerCf.uc_P ++;                             // ���������ۼ�
        if(gs_PowerCf.uc_P>=guc_GateCF)                 // �б��Ƿ���Ҫ����
        {
            gs_PowerCf.uc_P -=guc_GateCF;               // ��CF������з�Ƶ������Ƶ������������ۼ�
            gs_Energy.ucP +=guc_UnitCF;
            gui_SystemEvent|=flgEtGlb_EnergyCalc;       //�������������¼�
        }
    }
}
/*=========================================================================================\n
* @function_name: EnyB_Check_PowRev
* @function_file: EnergyBottom.c
* @����: ��⹦���Ƿ���
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_Check_PowRev(void)
{
    int32 l_pa;
    uint32 TempPara;
    uint32 ulPower;

    l_pa = ReadMeterPara(DATAP);
    if(l_pa<0)
    {                                       //���ʷ���
        l_pa=-l_pa;
        TempPara=gs_JbPm.ul_PG>>8;          //��ȡ����ϵ��
        if(TempPara==0)
        {                                   //У��������ʼ���ֵΪ0�Ļ���ֱ���жϹ���ԭʼֵ
            if(l_pa>0x2000)
            {
                gs_PDirCnt.ucRevDirCnt++;
                gs_PDirCnt.ucDirCnt=0;
                if(gs_PDirCnt.ucRevDirCnt>=3)
                {
                    gs_PDirCnt.PDir=true;
                }
            }
            else
            {
                gs_PDirCnt.ucRevDirCnt=0;
                gs_PDirCnt.ucDirCnt++;
                if(gs_PDirCnt.ucDirCnt>3)
                {
                    gs_PDirCnt.PDir=false;
                }
            }
        }
        else
        {   
            ulPower=(l_pa*100/gs_JbPm.ul_PG);
            if(ulPower>110)
            {
                gs_PDirCnt.ucRevDirCnt++;
                gs_PDirCnt.ucDirCnt=0;
                if(gs_PDirCnt.ucRevDirCnt>=3)
                {
                   gs_PDirCnt.PDir=true;
                }
            }
            else
            {
                gs_PDirCnt.ucRevDirCnt=0;
                gs_PDirCnt.ucDirCnt++;
                if(gs_PDirCnt.ucDirCnt>=3)
                {
                    gs_PDirCnt.PDir=false;
                }
            }
        }
    }
    else
    {
        gs_PDirCnt.ucRevDirCnt=0;
        gs_PDirCnt.ucDirCnt++;
        if(gs_PDirCnt.ucDirCnt>=3)
        {
            gs_PDirCnt.PDir=false;
        }
    }
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
    if(guc_ResetFlg)                            //û�г�����Ļ�
    {
        u32PMdatal=(gs_JbPm.ul_GatepL<<1);      //��һ�����壬����������2��
        if(gs_JbPm.ul_GatepL>=0x80000000)
        {
            u8PMdatah=(gs_JbPm.uc_GatepH<<1)+1;
        }else
        {
            u8PMdatah=(gs_JbPm.uc_GatepH<<1);
        }

    }else
    {
        u8PMdatah =gs_JbPm.uc_GatepH;     //�����Ƹ�λ
        u32PMdatal=gs_JbPm.ul_GatepL;
    }
    EnyB_SetMeterCfg(GATEP);            //����I1ͨ������������
    EnyB_SetMeterCfg(GATEQ);            //����I2ͨ������������

    u8PMdatah = 0;
    if(guc_ResetFlg)
    {
        u32PMdatal=(gs_JbPm.ul_Gatecp<<1); //Ǳ��������
    }else
    {
        u32PMdatal=gs_JbPm.ul_Gatecp;   //Ǳ��������
    }

    EnyB_SetMeterCfg(GATECP);           //����I1ͨ������������
    EnyB_SetMeterCfg(GATECQ);           //����I2ͨ������������

    p=&gs_JbPm.ul_SCP;
    for(uint8 i=0;i<7;i++)              //���ù��ʣ���ѹ�������Ȳ�ֵ
    {
        u32PMdatal=*(p+i);
        EnyB_SetMeterCfg(SCP+i);
    }

    PHCCtrl1=gs_JbPm.uc_PhcCtrl1;       //����I1�ǲ�ֵ
    PHCCtrl2=gs_JbPm.uc_PhcCtrl2;       //����I2�ǲ�ֵ
    
    CtrlGA=(gs_JbPm.uc_ADCGain&0x03);
    CtrlGB=((gs_JbPm.uc_ADCGain>>2)&0x03);
    CtrlGU=((gs_JbPm.uc_ADCGain>>4)&0x03);

}
/*=========================================================================================\n
* @function_name: EnyB_FstPluseProc
* @function_file: EnergyBottom.c
* @����: ��һ�����崦��
*
* @����:
* @����:
* @����:   lwb (2012-03-09)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_FstPluseProc(void)
{

    u8PMdatah   =gs_JbPm.uc_GatepH;     //�����Ƹ�λ
    u32PMdatal=gs_JbPm.ul_GatepL;
    EnyB_SetMeterCfg(GATEP);            //����I1ͨ������������
    EnyB_SetMeterCfg(GATEQ);            //����I2ͨ������������

    u8PMdatah = 0;
    u32PMdatal=gs_JbPm.ul_Gatecp;       //Ǳ��������
    EnyB_SetMeterCfg(GATECP);           //����I1ͨ������������
    EnyB_SetMeterCfg(GATECQ);           //����I2ͨ������������
}

/*=============================================================================================\n
Function���Զ�У���㷨
 ================================================================================================*/

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
* @����: ����ǲ�
* 
* @param: CurValue 
* @param: TarValue 
* 
* @return: uint8 
* @����: lwb (2014/3/19)
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
//void EnyB_AutoChkPW(uint8 *buf)
//{
//    uint8 ucData[4];                        //�����׼����ֵ
//    uint32 ul_Scp;                          //ԭʼ�Ȳ�����
//    int32 l_SdPower;                        //��׼����ֵ
//    int32 pa;
//
//    MemCpy((uint8*)ucData,buf,4);           //��ȡ��׼����ֵ
//    l_SdPower = Uint8_To_Uint32(ucData)/10; //��ñ�׼����ֵ
//    ul_Scp = ReadMeterPara(SCP);            //��ȡ�Ȳ�ֵ
//
//
//    pa =EnyB_CalRMS(DATAP);
//
//    gs_JbPm.ul_SCP = CalculateSC(pa, l_SdPower, ul_Scp);   //����Ȳ�ֵ
//    u32PMdatal = gs_JbPm.ul_SCP;
//    EnyB_SetMeterCfg(SCP);                                 //�����±Ȳ�ֵ
//}

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
//void EnyB_AutoChkIrms(uint8 *buf)
//{
//    uint8 ucData[2];
//    uint32  ul_SdCurrent;
//    uint32  ul_Irmg;
//    int32  l_IARms;
//
//
//    MemCpy((uint8*)ucData,buf,2);           //��ȡ��׼����ֵ
//    ul_SdCurrent=Uint8_To_Uint16(ucData);
//
//    ul_Irmg = ReadMeterPara(SCI1);  //��ȡ�Ȳ�ֵ
//
//    l_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));
//
//    gs_JbPm.ul_SCI1 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ
//
//    u32PMdatal = gs_JbPm.ul_SCI1;
//    EnyB_SetMeterCfg(SCI1);             //�����±Ȳ�ֵ
//}


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
//void EnyB_AutoChkUrms(uint8 *buf)
//{
//    uint8 ucData[2];
//    uint32  ul_SdVoltage;
//    uint32  ul_Urmg;
//    int32  l_URms;
//
//    MemCpy((uint8*)ucData,buf,2);           //��ȡ��׼����ֵ
//    ul_SdVoltage=Uint8_To_Uint16(ucData);   //��ñ�׼��ѹֵ
//    ul_Urmg = ReadMeterPara(SCU);           //��ȡ�Ȳ�ֵ
//
//    l_URms= BCD2Hex(EnyB_CalRMS(RMSU))*10;
//
//    gs_JbPm.ul_SCU = CalculateSC(l_URms, ul_SdVoltage, ul_Urmg);   //����Ȳ�ֵ
//
//    u32PMdatal = gs_JbPm.ul_SCU;
//    EnyB_SetMeterCfg(SCU);                  //�����±Ȳ�ֵ
//}
/*=========================================================================================\n
* @function_name: EnyB_AutoCheck
* @function_file: EnergyBottom.c
* @����: �Զ�У��
*
* @����:
* @����:
* @����:   lwb (2012-03-08)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void EnyB_AutoCheck(uint8* buf)
{
    Word32 WdData;
    uint32 ul_Scp,ul_Irmg,ul_Urmg;                  //ԭʼ�Ȳ�����
    uint32 ul_SdPower,ul_SdCurrent,ul_SdVoltage;    //��׼ֵ
    uint32 ul_IARms,ul_URms,ul_PaRms;               //��ǰ��Чֵ

    MemCpy((uint8*)WdData.byte,buf,4);              //��ȡ��׼����ֵ
    ul_SdPower = WdData.lword/10;                   //��ñ�׼����ֵ
    ul_Scp = ReadMeterPara(SCP);                    //��ȡ�Ȳ�ֵ

    ul_PaRms =BCD2Hex(EnyB_CalRMS(DATAP));

    gs_JbPm.ul_SCP = CalculateSC(ul_PaRms, ul_SdPower, ul_Scp);   //����Ȳ�ֵ


    MemCpy((uint8*)WdData.byte,buf+12,2);   //��ȡ��׼����ֵ
    ul_SdCurrent=WdData.word[0];

    ul_Irmg = ReadMeterPara(SCI1);          //��ȡ�Ȳ�ֵ

    ul_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));

    gs_JbPm.ul_SCI1 = CalculateSC(ul_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ

    MemCpy((uint8*)WdData.byte,buf+18,2);   //��ȡ��׼����ֵ
    ul_SdVoltage=WdData.word[0];            //��ñ�׼��ѹֵ
    ul_Urmg = ReadMeterPara(SCU);           //��ȡ�Ȳ�ֵ

    ul_URms= BCD2Hex(EnyB_CalRMS(RMSU))*10;

    gs_JbPm.ul_SCU = CalculateSC(ul_URms, ul_SdVoltage, ul_Urmg);   //����Ȳ�ֵ


    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();                                             //����У�����������оƬ
}
/*=========================================================================================\n
* @function_name: EnyB_IBAutoCheck
* @function_file: EnergyBottom.c
* @����: IB�Զ�У��
* 
* @����: lwb (2014/4/4)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void EnyB_IBAutoCheck(void)
{
                         
    uint32 ul_Scp,ul_Irmg,ul_Urmg;                  //ԭʼ�Ȳ�����
    uint32 ul_IARms,ul_URms,ul_PaRms;               //��ǰ��Чֵ

    ul_Scp = ReadMeterPara(SCP);                    //��ȡ�Ȳ�ֵ

    ul_PaRms =BCD2Hex(EnyB_CalRMS(DATAP));

    gs_JbPm.ul_SCP = CalculateSC(ul_PaRms, 11000, ul_Scp);   //����Ȳ�ֵ
            

    ul_Irmg = ReadMeterPara(SCI1);                              //��ȡ�Ȳ�ֵ

    ul_IARms= BCD2Hex(EnyB_CalRMS(RMSI1));

    gs_JbPm.ul_SCI1 = CalculateSC(ul_IARms, 5000, ul_Irmg);      //����Ȳ�ֵ


    ul_Urmg = ReadMeterPara(SCU);                               //��ȡ�Ȳ�ֵ

    ul_URms= BCD2Hex(EnyB_CalRMS(RMSU)); 

    gs_JbPm.ul_SCU = CalculateSC(ul_URms, 2200, ul_Urmg);       //����Ȳ�ֵ

    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
    EnyB_JbPm_Updata();    
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkAngle
* @function_file: EnergyBottom.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_AutoChkAngle(void)
{
                 
    int32 pa;
    PHCCtrl1=0;   //�ǲ�ֵд0
    //��Ҫ��ʱ�ȴ����ʷŵ�ͨ��д��E2ǰ
    DelayXms(10);
    pa=EnyB_CalRMS(DATAP);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

    gs_JbPm.uc_PhcCtrl1 = CalculateAC(pa, 5482);   //����ǲ�ֵ
    PHCCtrl1=gs_JbPm.uc_PhcCtrl1;       //����I1�ǲ�ֵ
    PHCCtrl2=gs_JbPm.uc_PhcCtrl2;       //����I2�ǲ�ֵ
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
}
