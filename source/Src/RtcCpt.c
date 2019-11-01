#define RTCCPTEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: RtcParaFsToE2
* @function_file: RtcCpt.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-07-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:   
* @�޸�����: 
===========================================================================================*/
void RtcParaFsToE2(uint8* ucData)
{
    uint8 i;
    uint8 code* p;
    uint8 CalSum;
    //CalCRC;
    uint8 Sum;
    int16 tempoffset;
    char XDATA_RAMZONE[8];
goto a1;
    //��ȡ����Ļ�,��FLASH�ж�ȡ����
    //�ж�FLASH�Ƿ�����ȷ��,��ȷ�Ļ���д��E2��
    p=(uint8 code*)0x480;
    for(i=0;i<3;i++)                        //��ȡ�¶�ƫ����
    {
        FCpyTMem(XDATA_RAMZONE,p+i*4,4);
        CalSum=DoSum(XDATA_RAMZONE,2)+0x33;
        Sum=XDATA_RAMZONE[2];
        if(CalSum==Sum)             //Crc��ȷ
        {
            //tempoffset=*((int16*)(XDATA_RAMZONE));
            MemInvertCpy((uint8*)&tempoffset,XDATA_RAMZONE,2);
    
            if(tempoffset<0)
            {
                tempoffset-=5;
                tempoffset/=10;
            }else
            {
                tempoffset+=5;       //��������
                tempoffset/=10;
            }
            ucData[0]=(uint8)tempoffset;
            //1���ֽڣ�����������
            break;
        }
    }
    
     //��ȡ���峣��ƫ����
a1: 
    p=(uint8 code*)0x48c;
    
    for(i=0;i<3;i++)
    {
    
        XDATA_RAMZONE[0]= p[i*4];
        XDATA_RAMZONE[1]= p[i*4+1];
        XDATA_RAMZONE[2]= p[i*4+2];
        XDATA_RAMZONE[3]= p[i*4+3];
        
        //FCpyTMem(XDATA_RAMZONE,p+i*4,4);
        CalSum=DoSum(XDATA_RAMZONE,2)+0x33;
        Sum=XDATA_RAMZONE[2];
    
        //�ж�FLASH�Ƿ�����ȷ��,��ȷ�Ļ���д��E2��
        if(CalSum==Sum)             //Crc��ȷ
        {   //4���ֽ�
            XDATA_RAMZONE[3]=XDATA_RAMZONE[1];
            XDATA_RAMZONE[2]=XDATA_RAMZONE[0];
            if(XDATA_RAMZONE[2]>=0x80)
            {
                XDATA_RAMZONE[0]=0xff;
                XDATA_RAMZONE[1]=0xff;
            }else
            {
                XDATA_RAMZONE[0]=0x00;
                XDATA_RAMZONE[1]=0x00;
            }
    
            MemCpy(ucData+1,XDATA_RAMZONE,4);
            break;
        }
    }
    //���¼���CRC,д��E2��
    //CalCRC=do_CRC(ucData,sizeof(ucData)-2);
    //Uint16_To_Uint8(CalCRC,ucData+sizeof(ucData)-2);
    //BE_WriteP(EEP_RTCTEMPOFFSET,(uint8*)ucData,28);     //  ��ȡRTC����
    // ------------SysE2ParaSetManage(EEP_RTCTEMPOFFSET, (uint8*)ucData,5);//д�볣��ƫ�ƺ�RTC����ƫ��
    Copy_FlashInfo( (char *)&FlashInfo.lRtcJZPara,(uint8*)(ucData+1),4);

}
/*=========================================================================================\n
* @function_name: RecoverRtcParaFrmFalsh
* @function_file: RtcCpt.c
* @����: �ָ�RTC������FLASH��
* 
* @����: 
* @����: 
* @����:   lwb (2012-07-16)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
#ifdef _DEL
void RecoverRtcParaFrmFalsh(void)
{
    //���ȶ�ȡRTC����,����CRC�Ƿ���ȷ
    uint8 ucData[28];
    BE_ReadP(EEP_RTCTEMPOFFSET,(uint8*)ucData,28);     //  ��ȡRTC����
    RtcParaFsToE2(ucData);
}

/*=========================================================================================\n
* @function_name: RecoverRtcPara
* @function_file: RtcCpt.c
* @����: �ָ�RTC����
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-30)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/

void RecoverRtcPara(void)
{

    //���ȶ�ȡRTC����,����CRC�Ƿ���ȷ
    uint8 ucData[28];
//  uint8 i;
//  uint8 code* p;
//  uint16 CalSum;
//  //CalCRC;
//  uint16 Sum;
//  int16 tempoffset;


    BE_ReadP(EEP_RTCTEMPOFFSET,(uint8*)ucData,28);     //  ��ȡRTC����

    if(Uint8_To_Uint16(ucData+sizeof(ucData)-2)!=do_CRC(ucData,sizeof(ucData)-2))
    {
        RtcParaFsToE2(ucData);

//      //��ȡ����Ļ�,��FLASH�ж�ȡ����
//      //�ж�FLASH�Ƿ�����ȷ��,��ȷ�Ļ���д��E2��
//      p=(uint8 code*)0x480;
//      for(i=0;i<3;i++)                        //��ȡ�¶�ƫ����
//      {
//          FCpyTMem(XDATA_RAMZONE,p+i*4,4);
//          CalSum=DoSum(XDATA_RAMZONE,2)+0x33;
//          Sum=XDATA_RAMZONE[2];
//          if(CalSum==Sum)             //Crc��ȷ
//          {
//              //tempoffset=*((int16*)(XDATA_RAMZONE));
//              MemInvertCpy((uint8*)&tempoffset,XDATA_RAMZONE,2);
//
//              if(tempoffset<0)
//              {
//                  tempoffset-=5;
//                  tempoffset/=10;
//              }else
//              {
//                  tempoffset+=5;       //��������
//                  tempoffset/=10;
//              }
//              ucData[0]=(uint8)tempoffset;
//              //1���ֽڣ�����������
//              break;
//          }
//      }
//
//       //��ȡ���峣��ƫ����
//
//      p=(uint8 code*)0x48c;
//
//      for(i=0;i<3;i++)
//      {
//
//          FCpyTMem(XDATA_RAMZONE,p+i*4,4);
//          CalSum=DoSum(XDATA_RAMZONE,2)+0x33;
//          Sum=XDATA_RAMZONE[2];
//
//          //�ж�FLASH�Ƿ�����ȷ��,��ȷ�Ļ���д��E2��
//          if(CalSum==Sum)             //Crc��ȷ
//          {   //4���ֽ�
//              XDATA_RAMZONE[3]=XDATA_RAMZONE[1];
//              XDATA_RAMZONE[2]=XDATA_RAMZONE[0];
//              if(XDATA_RAMZONE[2]>=0x80)
//              {
//                  XDATA_RAMZONE[0]=0xff;
//                  XDATA_RAMZONE[1]=0xff;
//              }else
//              {
//                  XDATA_RAMZONE[0]=0x00;
//                  XDATA_RAMZONE[1]=0x00;
//              }
//
//              MemCpy(ucData+1,XDATA_RAMZONE,4);
//              break;
//          }
//      }
//      //���¼���CRC,д��E2��
//      //CalCRC=do_CRC(ucData,sizeof(ucData)-2);
//      //Uint16_To_Uint8(CalCRC,ucData+sizeof(ucData)-2);
//      //BE_WriteP(EEP_RTCTEMPOFFSET,(uint8*)ucData,28);     //  ��ȡRTC����
//      SysE2ParaSetManage(EEP_RTCTEMPOFFSET, (uint8*)ucData,5);//д�볣��ƫ�ƺ�RTC����ƫ��
    }
}
#endif
/*=========================================================================================\n
* @function_name: Correct_Rtc
* @function_file: RtcCpt.c
* @����: У��RTC
*
*
* @����:
* @param:Hvalue
* @param:Lvalue
* @����:
* @����:   lwb (2012-03-24)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void SetRTCNormal(int16 offset)
{
    Word32 temp1,temp2;
    int16 temp3;
    temp2.lword=0;
    temp1.lword=(uint16)offset;
    if((temp1.byte[1]>0x80))
    { 
        temp1.word[0]=(~temp1.word[0]);
        temp1.word[0]&=0x1fff;
        temp1.lword=temp1.lword*5/30;                      //����ƫ�ƾ���Ϊ0.1ppm
        temp2.lword=6553600/4-1;
        temp2.lword=temp2.lword+temp1.lword;
    }
    else
    {
        temp1.lword=(temp1.lword)*5/30;
        temp2.lword=6553600/4;
        temp2.lword=temp2.lword-temp1.lword;
    }
    temp3=offset/10;
    temp1.lword=(uint16)temp3;
    RTCPEN=0x96;                        //1S����
    RTCPWD=0x57;
    DelayOSC(5);
    RTCCH=temp1.byte[1];
    RTCCL=temp1.byte[0];
    DIVTHH=temp2.byte[2];
    DIVTHM=temp2.byte[1];
    DIVTHL=temp2.byte[0];
    DelayOSC(5);
    RTCPEN=0x96;
    RTCPWD=0x56;
}
//extern const uint8 code InitParaRTC[];
/*=========================================================================================\n
* @function_name: CalRTC
* @function_file: RtcCpt.h
* @����: ����RTCƫ��ppm
*
* @����:
* @����:
* @����:   lwb (2012-03-22)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void CalRTC(void)
{
    uint8 ucdata[4];
    Word32 temp1;
    int32 delta;
    float temperature; //��ǰ�¶�
    int8  tempoffset;
    int16  OSC;
    uint32 BparaTemp[5];
    int32 Bpara;
    uint32  MAdcValue;
    uint8 Ti;
    uint32  temp;
    S_TEMPPARA s_TempPara;
    uint8 code *p;
    uint8 TempParaSum;
   
    
#ifdef _DEL

    p=(uint8 code*)0x420;
    for(uint8 i=0;i<3;i++)
    {
        FCpyTMem((uint8*)&s_TempPara.ul_TempParaA,p+i*24,sizeof(S_TEMPPARA));
        TempParaSum=DoSum((uint8*)&s_TempPara.ul_TempParaA,sizeof(S_TEMPPARA)-2)+0x33;
        if(TempParaSum==s_TempPara.uc_Add33)
        {
            break;
        }
    }


//    if(_SYS_IS_PWR_OFF)
//    {    
//        MAdcValue=EnyB_ReadMeterParaACK(DATAOM);//��Mͨ��ԭʼֵ
//    }
//    else
    {    
        MAdcValue=EnyB_ReadMeterParaACK(DATAOM);//��Mͨ��ԭʼֵ
    }

    temp=MAdcValue>>16;
    FCpyTMem((uint8 *)&gui_Kpara, (uint8 code*)&InitParaRTC[(CtrlBGP&0x3e)], 0x02);
    temp=(temp*gui_Kpara)/1000;
    
    if(TempParaSum!=s_TempPara.uc_Add33)
    {        
        s_TempPara.ul_TempParaA = 18018;
        s_TempPara.ul_TempParaB = 1;
        s_TempPara.ul_TempParaC = 224019254;
        s_TempPara.ul_TempParaD = 7092;
        s_TempPara.ul_TempParaE = 10;
    }
    temperature=(s_TempPara.ul_TempParaB*sqrt(s_TempPara.ul_TempParaC+s_TempPara.ul_TempParaD*temp)-s_TempPara.ul_TempParaA)/s_TempPara.ul_TempParaE;
    //temperature=(-58.25+sqrt(3396.5584-0.096*(18001.2-(float)temp)))/0.0495;//(sqrt(3396.5584-0.096*(18001.2-(float)temp))/0.048)-58.28;

    BE_ReadP(EEP_RTCTEMPOFFSET,(uint8*)&tempoffset,1);     //  �¶ȳ���ƫ��

    temperature+=tempoffset;
#ifndef V9811S
    if(_SYS_IS_PWR_OFF)
    {
        temperature-=6;
    }
#endif
    if(temperature>90)
    {   
        temperature=90;
    }else if(temperature<(-43))
    {   
        temperature=-43;
    }

    //�����¶ȵ�ȫ�ֱ�����
       gi_Temprature=(uint16)(temperature*10);
    //��ȡRTCBֵ
    BE_ReadP(EEP_RTCBVAL, (uint8*)BparaTemp,20);           //RTCBֵ

    if(temperature>=50)
    {
        Bpara=BparaTemp[4];
    }
    else if((temperature<50)&&(temperature>=40))
    {
        Bpara=BparaTemp[3];
    }
    else if((temperature<40)&&(temperature>=0))
    {
        Bpara=BparaTemp[2];
    }
    else if((temperature<0)&&(temperature>=-20))
    {
        Bpara=BparaTemp[1];
    }
    else if(temperature<-20)
    {
        Bpara=BparaTemp[0];
    }

    //��ȡ�����¶�
    BE_ReadP(EEP_RTCDDTEMP, (uint8*)&Ti,1);  //�����¶�

    //��ȡ���峣��ƫ��
    BE_ReadP(EEP_RTCFRQOFFSET, (uint8*)ucdata,4);           // RTC����ƫ��
#endif
    
    CopyRam ( ucdata, (char *)&(FlashInfo.lRtcJZPara),sizeof(FlashInfo.lRtcJZPara));
    MemInvertCpy(temp1.byte,ucdata,4);

    delta=(int32)temp1.lword;

    OSC=(int16)((((float)Bpara)*(temperature-((float)Ti))*(temperature-((float)Ti)))/1000000+delta);
OSC=delta;
    SetRTCNormal(OSC);
}
 