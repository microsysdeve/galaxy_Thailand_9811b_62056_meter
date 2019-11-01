#define  ENERGYBOTTOMEXT
#include "Include.h"
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
uint32 EnyB_ReadMeterParaACK(uint16 addr)
{
    udata8 index;
    uint32  u32PMdatal,temp;
    XBYTE[INVD]=0XCC;
    XBYTE[INVD]=0x00;
    index=0;
    while(XBYTE[ACK])
    {
        index++;
        if(index>CFGDELAY)
        {
            return false;
        }
    }

    index=XBYTE[addr];                          //��ȡ��ʵ��ַ���������ݵ�����
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

    u32PMdatal=(uint32)XBYTE[BUFF0];
    temp=(uint32)XBYTE[BUFF1]<<8;
    u32PMdatal+= temp;
    temp=(uint32)XBYTE[BUFF2];
    temp=temp<<16;
    u32PMdatal+=temp;
    temp=(uint32)XBYTE[BUFF3];
    temp=temp<<24;
    u32PMdatal+=temp;
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
uint8 EnyB_SetMeterCfgACK(uint32 u32PMdatal ,uint16 addr)
{
    uint8 index;
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
    
//  temp=EnyB_ReadMeterParaACK(addr);
//  if(temp==u32PMdatal)
//  {
//      return true;
//  }
//  else
//  {
//      return false;
//  }
    return true;
}
/*=========================================================================================\n
* @function_name: ADCInit
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
void ADCInit(void)
{
    CtrlADC5=0x81;                              //Ĭ���ǲ����¶�
    CtrlADC6=0;
    ADCOPEN(ADCAPDN+ADCUPDN+ADCMPDN);   //OPEN ADC U A B M
//  CtrlADC0=(ADCA16X+ADCB1X+ADCU1X);           //ADC A 32X GAIN  ADC B 1x GAIN ADC U 1X GAIN
}
/*=========================================================================================\n
* @function_name: PMDspInit
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
void PMDspInit(void)
{
    uint8 i;
    PMG=0;
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl1);
    EnyB_SetMeterCfgACK(INITGATEP,GATEP);        //���ü�����ʼֵ
    EnyB_SetMeterCfgACK(INITGATEQ,GATEQ);
    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }
//  EnyB_SetMeterCfgACK(0,0x10f0);
//  EnyB_SetMeterCfgACK(0,0x10f1);
//  EnyB_SetMeterCfgACK(0,0x10f2);
//  EnyB_SetMeterCfgACK(0,0x10f3);

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
//  EnyB_SetMeterCfgACK(0,0x10f6);
//  EnyB_SetMeterCfgACK(0,0x10f7);
//  EnyB_SetMeterCfgACK(0,0x10f8);
//  EnyB_SetMeterCfgACK(0,0x10f9);
    EnyB_SetMeterCfgACK(0xC8,PMCtrl4);
    EnyB_SetMeterCfgACK(0x08,PMCtrl4);
    EnyB_SetMeterCfgACK(0x00,PMCtrl4);

//  EnyB_SetMeterCfgACK(0,0x10f0);
//  EnyB_SetMeterCfgACK(0,0x10f1);
//  EnyB_SetMeterCfgACK(0,0x10f2);
//  EnyB_SetMeterCfgACK(0,0x10f3);

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f0+i);
    }

//  EnyB_SetMeterCfgACK(0,0x10f6);
//  EnyB_SetMeterCfgACK(0,0x10f7);
//  EnyB_SetMeterCfgACK(0,0x10f8);
//  EnyB_SetMeterCfgACK(0,0x10f9);

    for(i=0;i<4;i++)
    {
        EnyB_SetMeterCfgACK(0,0x10f6+i);
    }
    EnyB_SetMeterCfgACK(0x01,GATECP);       //Ǳ��1
    
    EnyB_SetMeterCfgACK(0x01,GATECQ);       //Ǳ��2
    EnyB_SetMeterCfgACK(0x5b,PMCtrl1);      //��������ͨ��
    EnyB_SetMeterCfgACK(0x00,PMCtrl2);      //
    EnyB_SetMeterCfgACK(0x70,PMCtrl3);      //������·�й�����г������
    EnyB_SetMeterCfgACK(0xc0,PMCtrl4);      //�ȴ��˲����ȶ�����
    EnyB_SetMeterCfgACK(0,PHCCtrl1);        //��0
    EnyB_SetMeterCfgACK(0,PHCCtrl2);
    guc_CfOpenFlg=true;
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
    if(guc_RtcConflict==0x55)
    {
        gui_RefreshEvent|=flgEtPara_RTC;    
        guc_RtcConflict=0x00;
    }

    if(guc_OpenCfTmCnt<1)
    {
        guc_OpenCfTmCnt++;
    }else
    {
        if(guc_CfOpenFlg&&(guc_OpenCfTmCnt>=1))
        {   
            EnyB_SetMeterCfgACK(0xd8,PMCtrl4);  //�򿪼���,����Ǳ������
            EnyB_InitCFInt();                   //����CF�����ж�
            guc_CfOpenFlg=false;
        }
    }

    if(guc_FrsCalRTCDelay>0)                    //��ʱ5s
    {
        guc_FrsCalRTCDelay--;
        if(guc_FrsCalRTCDelay==0)
        {
            CalRTC();                           //�ϵ��һ��У��RTC��Ҫ��AD�ȶ�
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
    P9OE&=(~BIT6);                          //��CF IO���
    P9FC|=(BIT6);
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
    ADCInit();              //��ʼ��ADC�����������ͨ��
    PMDspInit();            //PM DSP init�����ü���ֵ����ֹ�ҳ�����
    EnyB_PurInit();         //����ģ���ϵ��ʼ��
    DelayOSC(200);
    DelayOSC(200);
    DelayOSC(200);
    CtrlADC5=0x92;          //������ز�������
    guc_CheckBatFlg=true;  //�����¶�
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
extern const uint8 code InitPara5[sizeof(S_JBPM)-2];
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
    FCpyTMem((uint8*)&gs_JbPm.ui_MeterC,InitPara5,sizeof(S_JBPM)-2);                     //����Flash���ݵ�RAM��
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
void EnyB_IntCF(void)                       
{
    uint8 *pCfZ;
    uint8 *pEyZ;

    uint8 *pCf;
    uint8 *pEy;


    if(gs_MeterState.ui_MeterState2.RunCode2Word.PADIR)      //�ж��Ƿ��Ƿ���
    {
        pEyZ=&gs_Energy.ucNz;
        pCfZ=&gs_PowerCf.uc_Nz;
    }else
    {
        pEyZ=&gs_Energy.ucPz;                                   //��������
        pCfZ=&gs_PowerCf.uc_Pz;                                 //����������
    }


    (*pCfZ)++;                                                  //�������ۼ�
    if(*pCfZ>=guc_GateCF)                                       //�б��Ƿ���Ҫ����
    {
        *pCfZ -=guc_GateCF;                                     //��CF������з�Ƶ������Ƶ������������ۼ�
        *pEyZ +=guc_UnitCF; 
        gui_SystemEvent |= flgEtGlb_EnergyCalc;                 //�������������¼�
    }
 
    if((gs_FunCfg.uc_CfSaveCfg&0x0F)==0x05)                     //CF����ַ��ʼ���
    {
        if(gs_MeterState.ui_MeterState2.RunCode2Word.PADIR)     //�ж��Ƿ��Ƿ���
        {
            pEy=(&gs_Energy.ucN1+gs_FeeData.uc_FeeNo);          //���������
            pCf=(&gs_PowerCf.uc_N1+gs_FeeData.uc_FeeNo);        //�����������

        }else                                                   //����
        {
            pEy=(&gs_Energy.ucP1+gs_FeeData.uc_FeeNo);          //������������
            pCf=(&gs_PowerCf.uc_P1+gs_FeeData.uc_FeeNo);        //��������������
        }

        (*pCf)++;                                              //����ַ��������ۼ�
        if(*pCf>=guc_GateCF)                                   // �б��Ƿ���Ҫ����
        {
            *pCf -=guc_GateCF;                                 // ��CF������з�Ƶ������Ƶ������������ۼ�
            *pEy +=guc_UnitCF; 
            gui_SystemEvent |= flgEtGlb_EnergyCalc;             //�������������¼�
        }
    }

}
/*=========================================================================================\n
* @function_name: ReadRMSPara
* @function_file: EnergyBottom.c
* @����: ��ȡ��ʾ����ϵ��k
* 
* 
* @����: 
* @param:ucpos  
* 
* @����: 
* @return: uint32 
* @����:   lwb (2012-05-29)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
uint32 ReadRMSPara(uint8 ucpos)
{
    uint32 TempValue;
    TempValue=0x1000;

    BE_ReadP(EEP_JBTOTAL+sizeof(S_JBPM)-19+ucpos*4,(uint8*)&TempValue,4);
    TempValue/=65536;
    return TempValue;
}
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
        if(TempValue.lword<(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)
           && guc_FactoryType != FactorMd)
        {
             TempValue1=0;
        }
        else
        {
             TempValue1=Hex2BCD(TempValue.lword);

             if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
             {
                 TempValue1|=0x800000;
             }
        }
        break;
    case RMSU:
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
        TempPara=gs_JbPm.ul_I1RmG/65536;    //ReadRMSPara(2);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }
        
        if(TempValue.lword<((gs_JbPm.ui_Ib/1000)*2) && guc_FactoryType != FactorMd)
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
            
            
            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
            {
                TempValue1|=0x800000;
            }
        }
        break;
    case RMSI2:
        TempPara=gs_JbPm.ul_I2RmG/65536;    //ReadRMSPara(3);
        if(TempPara==0)
        {    
            return 0;
        }
        else
        {    
            TempValue.lword=TempValue.lword/TempPara;
        }

        if(TempValue.lword<IBLEVEL && guc_FactoryType != FactorMd)
        {    
            return 0;
        }else 
        {    
            TempValue1=Hex2BCD(TempValue.lword);
            
            if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir==true)   //������Ӹ���
            {
                TempValue1|=0x800000;
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
    if(temp_p&0x800000)     //������
    {
        temp_p&=~0x800000;  //����ȡ��
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
/* 
    temp1.lword=EnyB_ReadMeterParaACK(DATAAP1);     //���ڹ���
    temp2.lword=EnyB_ReadMeterParaACK(DATAP);       //�й�����
    if(temp2.byte[3]>0x7f)
    {    
        temp2.lword=(~temp2.lword)+1;
    }

    temp2.lword=temp2.lword*100;
    temp3.lword=temp2.lword/temp1.lword;
    temp3.lword*=gs_JbPm.ul_SCU;
    temp3.lword/=gs_JbPm.ul_SCP;
    temp3.lword*=gs_JbPm.ul_SCI1;

    temp3.lword=Hex2BCD(temp3.lword*10);
*/
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

    l_pa = EnyB_ReadMeterParaACK(DATAP);
    if(l_pa>0)
    {                                       //���ʷ���
        TempPara=gs_JbPm.ul_PG>>8;          //��ȡ����ϵ��
        if(TempPara==0)
        {                                   //У��������ʼ���ֵΪ0�Ļ���ֱ���жϹ���ԭʼֵ
            if(l_pa>0x2000)
            {
                gs_PDirCnt.ucRevDirCnt++;
                gs_PDirCnt.ucDirCnt=0;
                if(gs_PDirCnt.ucRevDirCnt>=gs_PDirCtr.ucDelayTm)
                {
                    gs_MeterState.ui_MeterState1.RunCode1Word.PDir=true;
                }
            }
            else
            {
                gs_PDirCnt.ucRevDirCnt=0;
                gs_PDirCnt.ucDirCnt++;
                if(gs_PDirCnt.ucDirCnt>=gs_PDirCtr.ucDelayTm)
                {
                    gs_MeterState.ui_MeterState1.RunCode1Word.PDir=false;
                }
            }
        }else
        {   
             ulPower=((l_pa*32)/TempPara)*8;
             if(ulPower>gs_PDirCtr.ul_PDirGate
                /*(((gs_JbPm.ui_Ib/1000)*(gs_JbPm.ui_Un/100))*2/100)*/)
             {
                 gs_PDirCnt.ucRevDirCnt++;
                 gs_PDirCnt.ucDirCnt=0;
                 if(gs_PDirCnt.ucRevDirCnt>=gs_PDirCtr.ucDelayTm)
                 {
                     gs_MeterState.ui_MeterState1.RunCode1Word.PDir=true;
                 }
             }else
             {
                 gs_PDirCnt.ucRevDirCnt=0;
                 gs_PDirCnt.ucDirCnt++;
                 if(gs_PDirCnt.ucDirCnt>=gs_PDirCtr.ucDelayTm)
                 {
                     gs_MeterState.ui_MeterState1.RunCode1Word.PDir=false;
                 }
             }
        }
    }else
    {
        gs_PDirCnt.ucRevDirCnt=0;
        gs_PDirCnt.ucDirCnt++;
        if(gs_PDirCnt.ucDirCnt>=gs_PDirCtr.ucDelayTm)
        {
            gs_MeterState.ui_MeterState1.RunCode1Word.PDir=false;
        }
    }
    
    if(gs_PDirCtr.ul_PDirGate == 0)
    {
        gs_MeterState.ui_MeterState1.RunCode1Word.PDir=false;
    }
    
    if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir)
    {
        gs_MeterState.ui_MeterState2.RunCode2Word.PADIR = true;
        Rpt_StaSet(RPT_PDIR);
//     gut_SysWarn.SysWarn.REVPOWER=true;
        if(gs_SysRunSt.PDirFR==false
//        &&(gs_DispStt.ucMode!=Const_DispMode_Full)
           )
        {
          
//         gs_DispStt.ucMode=Const_DispMode_Err;
//         gui_SystemEvent |= flgEtGlb_RefreshLcd;

//         #ifdef FRCom
//              EVENTOUTHIGH();
//              gs_FREventOut.FREventOutStruct.PDirFR=true;
//         #endif
            gs_SysRunSt.PDirFR=true;
        }
    }
    else
    {
//     gut_SysWarn.SysWarn.REVPOWER=false;
//     gs_MeterState.ui_MeterState1.RunCode1Word.PDir = false;      //�幦�ʷ����־
       gs_MeterState.ui_MeterState2.RunCode2Word.PADIR= false;
       gs_SysRunSt.PDirFR=false;
       Rpt_StaFlgClr(RPT_PDIR);
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

    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEP);        //����I1ͨ������������
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatep,GATEQ);        //����I2ͨ������������  
 

    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECP);      //����I1ͨ������������
    EnyB_SetMeterCfgACK(gs_JbPm.ul_Gatecp,GATECQ);      //����I2ͨ������������  

//    EnyB_Check_RMSI();
    p=&gs_JbPm.ul_SCP;
    for(uint8 i=0;i<7;i++)                              //���ù��ʣ���ѹ�������Ȳ�ֵ
    {
        EnyB_SetMeterCfgACK(*(p+i),SCP+i);           
    }
    
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1,PHCCtrl1);  //����I1�ǲ�ֵ
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl2,PHCCtrl2);  //����I2�ǲ�ֵ
    
    CtrlADC0 = gs_JbPm.uc_AnaG;                         //����ADC����
    if((gs_JbPm.uc_AnaG&0x07)==0x07)                    //IA����40���Ļ�������IA ƫ�õ���
    {
        CtrlADC4|=BIT4;             //����ƫ�õ���
    }else
    {
        CtrlADC4&=~BIT4;            //����ƫ�õ���
    }
}

/*=========================================================================================\n
* @function_name: RecoverPowDirConfig
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
void RecoverPowDirConfig(void)
{
    gs_PDirCnt.ucDirCnt=0;
    gs_PDirCnt.ucRevDirCnt=0;
    SysE2ReadData(EEP_PDIRTIME,(uint8*)&gs_PDirCtr.ucDelayTm,4);    //���·������ж���ʱ�ͷ�ֵ 
    gs_PDirCtr.ucDelayTm=BCD2Hex(gs_PDirCtr.ucDelayTm);
    gs_PDirCtr.ul_PDirGate=BCD2Hex(gs_PDirCtr.ul_PDirGate&0x00ffffff);   
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
void EnyB_AutoChkPW(void)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint32 ul_Scp;                          //ԭʼ�Ȳ�����
    int32 l_SdPower;                        //��׼����ֵ
    //int32  err;
    //int32  errPgain;
    int32 pa;

    BE_ReadP(EEP_AUTOCAL,ucData,4);         //��ȡ��׼����ֵ  
    
    ul_Scp = EnyB_ReadMeterParaACK(SCP);      //��ȡ�Ȳ�ֵ
    l_SdPower = Uint8_To_Uint32(ucData)/10;   //��ñ�׼����ֵ
//  pa = EnyB_ReadMeterParaACK(DATAP);        //��ȡ����ֵ�������ж�
//
//  if(pa>0)           //���Ȱѱ�ƶ�ȡ�Ĺ���ֵת����ֵ
//  {
//     pa= -BCD2Hex(CalRMS(DATAP));//gs_EnyInsData.l_PowerPA;
//  }else
//  {
//     pa= BCD2Hex(CalRMS(DATAP));//-gs_EnyInsData.l_PowerPA;
//  }

    pa=CalRMS(DATAP);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
    } 

    pa =BCD2Hex(pa);
    gs_JbPm.ul_SCP = CalculateSC(pa, l_SdPower, ul_Scp);   //����Ȳ�ֵ
 
    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);                                 //�����±Ȳ�ֵ
}

/*=========================================================================================\n
* @function_name: EnyB_AutoChkPW2
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
void EnyB_AutoChkPW2(void)
{
    uint8 ucData[4];                        //�����׼����ֵ
    uint8 i;
    int32 l_SdPower;                        //��׼����ֵ   
    Word32 TempValue;
    uint32 TempSum;
    uint32 pa_sum,TempPara;
    
    pa_sum = 0;
    TempSum = 0;
    BE_ReadP(EEP_AUTOCAL,ucData,4);         //��ȡ��׼����ֵ  

    l_SdPower = Uint8_To_Uint32(ucData);   //��ñ�׼����ֵ

    for(i=0;i<16;i++)
    {
        TempValue.lword=EnyB_ReadMeterParaACK(DATAIP); 
        DelayXms(20);
        CLRWDT();                           //ι��
        //DelayXms(255);
        if(TempValue.byte[3]>0x7f)          //����Ǹ����������ȱ������
        {
            TempValue.lword=~TempValue.lword+1;
        }
        TempSum += TempValue.lword;
    }   
    
    TempSum = TempSum>>4;              //��ȡ���ʼĴ���ֵ
    TempPara = gs_JbPm.ul_PG/256;        //��ȡ����ϵ��
    pa_sum = (TempSum*2560)/TempPara;  //����ֵ
      
    TempValue.lword = l_SdPower*TempPara/2560;    //���ۼĴ���ֵ
    
    if(l_SdPower > pa_sum)
      gs_JbPm.ul_PARAPC = (TempValue.lword*(l_SdPower-pa_sum)/l_SdPower);       //������β���ֵ
    else
      gs_JbPm.ul_PARAPC = -(TempValue.lword*(pa_sum-l_SdPower)/l_SdPower);   //������β���ֵ
    EnyB_SetMeterCfgACK(gs_JbPm.ul_PARAPC, PARAPC);                                 //�����±Ȳ�ֵ
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
void EnyB_AutoChkIrms(void)
{
    uint8 ucData[2];
    uint32  ul_SdCurrent;
    uint32  ul_Irmg;
    int32  l_IARms;

    BE_ReadP(EEP_AUTOCAL+12,ucData,2);      //��ȡ��׼����ֵ
    ul_SdCurrent=Uint8_To_Uint16(ucData);    //��ñ�׼����ֵ
    ul_Irmg = EnyB_ReadMeterParaACK(SCI1);                    //��ȡ�Ȳ�ֵ

    l_IARms= BCD2Hex(CalRMS(RMSI1));//gs_EnyInsData.ul_IARms;

    gs_JbPm.ul_SCI1 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ

    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI1, SCI1);                                 //�����±Ȳ�ֵ
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
void EnyB_AutoChkUrms(void)
{
    uint8 ucData[2];
    uint32  ul_SdVoltage;
    uint32  ul_Urmg;
    int32  l_URms;

    BE_ReadP(EEP_AUTOCAL+18,ucData,2);      //��ȡ��׼��ѹֵ
    ul_SdVoltage=Uint8_To_Uint16(ucData);    //��ñ�׼��ѹֵ
    ul_Urmg = EnyB_ReadMeterParaACK(SCU);                    //��ȡ�Ȳ�ֵ

    l_URms= BCD2Hex(CalRMS(RMSU))*10;//gs_EnyInsData.ul_URms;

    gs_JbPm.ul_SCU = CalculateSC(l_URms, ul_SdVoltage, ul_Urmg);   //����Ȳ�ֵ

    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCU, SCU);                                 //�����±Ȳ�ֵ
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
    uint8 ucData[4];                        //�����׼����ֵ
    int32 l_SdPower;                        //��׼����ֵ
    int32 pa;
    
    //EnyB_SetMeterCfgACK(0, PHCCtrl1);       //�ǲ�ֵд0
    //��Ҫ��ʱ�ȴ����ʷŵ�ͨ��д��E2ǰ
    BE_ReadP(EEP_AUTOCAL,ucData,4);         //��ȡ��׼����ֵ  
   
    l_SdPower = Uint8_To_Uint32(ucData)/10;   //��ñ�׼����ֵ
//  pa = EnyB_ReadMeterParaACK(DATAP);        //��ȡ����ֵ�������ж�
//
//  if(pa>0)           //���Ȱѱ�ƶ�ȡ�Ĺ���ֵת����ֵ
//  {
//     pa= -BCD2Hex(CalRMS(DATAP));//gs_EnyInsData.l_PowerPA;
//  }else
//  {
//     pa= BCD2Hex(CalRMS(DATAP));//-gs_EnyInsData.l_PowerPA;
//  }

    pa=CalRMS(DATAP);               //��ȡ����
    if(pa&0x800000)                 //�жϷ���
    {
        pa&=~0x800000;               
        pa =BCD2Hex(pa);
    }else
    {
        pa =BCD2Hex(pa);
    }

    gs_JbPm.uc_PhcCtrl1 = CalculateAC(pa, l_SdPower);   //����ǲ�ֵ
 
    EnyB_SetMeterCfgACK(gs_JbPm.uc_PhcCtrl1, PHCCtrl1);  //���ýǲ�ֵ
    
    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ

    SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));

    EnyB_JbPm_Updata();                                       //����У�����������оƬ
}
/*=========================================================================================\n
* @function_name: EnyB_AutoChkInrms
* @function_file: EnergyBottom.c
* @����: У�����ߵ���
* 
* 
* @����: 
* @param:ui_SdCurrent  
* @����: 
* @����:   lwb (2012-10-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_AutoChkInrms(uint16 ui_SdCurrent)
{
    uint32  ul_Irmg;
    int32   l_IARms;
    int32   ul_SdCurrent;
    
    ul_SdCurrent=ui_SdCurrent;

    ul_Irmg = EnyB_ReadMeterParaACK(SCI2);                    //��ȡ�Ȳ�ֵ

    l_IARms= BCD2Hex(CalRMS(RMSI2));//gs_EnyInsData.ul_IARms;

    gs_JbPm.ul_SCI2 = CalculateSC(l_IARms, ul_SdCurrent, ul_Irmg);   //����Ȳ�ֵ

    EnyB_SetMeterCfgACK(gs_JbPm.ul_SCI2, SCI2);                     //�����±Ȳ�ֵ


    gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
    BE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));        //д��У�����
        
    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));    
    #else
        BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN,(uint8*)&gs_JbPm, sizeof(S_JBPM));
    #endif     

} 
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
void EnyB_AutoCheck(void)
{
    EnyB_AutoChkPW();                                                   // У�����ʺ����
    EnyB_AutoChkIrms();                                                 // У��������Чֵ
    EnyB_AutoChkUrms();                                                 // У����ѹ��Чֵ
    //if((0x00 == gs_JbPm.uc_JbOkFlag)&&(guc_FactoryType))                    // û�н�ֹд���־��ͬʱ��������ģʽ������дУ�����
    //{//д������
        gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ

        SysE2ParaSetManage(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));            //д��У�����

//      BE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));            //д��У�����
//
//  #if (_SW_SE_Type > 0)
//      SE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
//  #else
//      BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN,(uint8*)&gs_JbPm, sizeof(S_JBPM));
//  #endif
             
        EnyB_JbPm_Updata();                                       //����У�����������оƬ
    //}
}
 
/*=========================================================================================\n
* @function_name: EnyB_CloseAutoCheck
* @function_file: EnergyBottom.c
* @����: �ر��Զ�У��һ��У����ɺ���Ҫ�ر�
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_CloseAutoCheck(void)
{
    //��Ҫ�ӱ������ƣ�Ҫ��������ģʽ
    if(guc_FactoryType==FactorMd)                                                    // ֻ��������ģʽ�£�������д������
    {
        gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);      //����CRCУ��ֵ
        BE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));
        
    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));    
    #else
        BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN,(uint8*)&gs_JbPm, sizeof(S_JBPM));
    #endif 
    }
}
 
/*=========================================================================================\n
* @function_name: EnyB_OpenAutoCheck
* @function_file: EnergyBottom.c
* @����: ���Զ�У��
* 
* @����: 
* @����: 
* @����:   lwb (2012-03-08)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_OpenAutoCheck(void)
{
    if(guc_FactoryType==FactorMd)// ֻ��������ģʽ�£�������д������
    {
        
        gs_JbPm.ui_JbCRC = do_CRC((uint8 *)&gs_JbPm,sizeof(S_JBPM)-2);  //����CRCУ��ֵ
        BE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));        //д������
        
    #if (_SW_SE_Type > 0)
        SE_WriteP(EEP_JBTOTAL,(uint8 *)&gs_JbPm,sizeof(S_JBPM));    
    #else
        BE_WriteP(EEP_JBTOTAL+EEP_BAK_LEN,(uint8*)&gs_JbPm, sizeof(S_JBPM));
    #endif 
    }
}
/*=========================================================================================\n
* @function_name: EnyB_Check_RMSI
* @function_file: EnergyBottom.c
* @����: ����Ƿ�����
* 
* @����: 
* @����: 
* @����:   lm (2013-03-21)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_Check_OC(void)
{
    uint32 ul_rms;
    if(guc_PowerOffTmCnt<1)
    {
        guc_PowerOffTmCnt++;
    }else
    {
        ul_rms = CalRMS(RMSU);                                  //��ȡ��ѹ��Чֵ
        if(ul_rms < gs_PowDn.uiGate)   //<60%�αȵ�ѹ
        {
            gs_PowDn.ucDly++;
            if(gs_PowDn.ucDly >= gs_PowDn.ucTime && gs_PowDn.ucFlg != 0x55)
            {
                PowerJL(1, &gs_DateTime.ucSecond);              //ͣ���¼
                gs_PowDn.ucFlg = 0x55;
                gui_SystemState |= flgStSys_PowOffing;
            }
        }
        else
        {
            if(gs_PowDn.ucFlg == 0x55)
            {
                PowerJL(2, &gs_DateTime.ucSecond);              //ͣ���¼
                gs_PowDn.ucFlg = 0xAA;
                gui_SystemState &= ~flgStSys_PowOffing;
            }
            gs_PowDn.ucDly = 0;
        }
    }
}
/*=========================================================================================\n
* @function_name: EnyB_Check_RMSI
* @function_file: EnergyBottom.c
* @����: ����Ƿ�����
* 
* @����: 
* @����: 
* @����:   lm (2013-03-21)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void EnyB_Check_RMSI(void)
{
    uint32 ul_rmsi;

    if(gs_GiantSCP.ui_CRC == do_CRC((uint8*)&gs_GiantSCP.ul_Adjust,4)                  
       && gs_GiantSCP.ul_Adjust != 0)                                        //������в���ֵ��Ҫ����
    {
        ul_rmsi = CalRMS(RMSI1)&0x7fffffff;                                  //��ȡ������Чֵ
        
        if((ul_rmsi >= 0x048000 && guc_GiantSCPflag==0x55)                    //����48A & 
           || ul_rmsi >= 0x052000)                                           //����52A 
        {
            if(guc_GiantSCPcnt>3)
            {
                if(gs_GiantSCP.ul_Adjust<0x014AFD6A && gs_GiantSCP.ul_Adjust>-0x014AFD6A) //����
                {
                    ul_rmsi = gs_JbPm.ul_SCP + gs_GiantSCP.ul_Adjust;
                }
                else
                {
                    ul_rmsi = gs_JbPm.ul_SCP;
                }
                EnyB_SetMeterCfgACK(ul_rmsi, SCP);
                guc_GiantSCPflag = 0x55;
                guc_GiantSCPcnt = 3;
            }
            else
            {
                EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);
                guc_GiantSCPflag = 0xAA;
            }
            guc_GiantSCPcnt++;
        }
        else
        {
            EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);
            guc_GiantSCPflag = 0xAA;
            guc_GiantSCPcnt = 0;
        }
    }
    else
    {
        EnyB_SetMeterCfgACK(gs_JbPm.ul_SCP, SCP);
        guc_GiantSCPflag = 0x00;
    }
}
