#define LCDSHOWEXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: ShowSysStart
* @function_file: Lcdshow.c
* @����: ��ʾ�ϵ��ʼ��
*
* @����:
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowSysStart(void)
{
    ShowInitial();                  //��ʾ������ʼ��
#ifdef _DEL
    guc_DyBgLed = gs_DispCont.ucFullShowTm;         //�ϵ米��ʱ���ȫ��ʱ��һ��
    gul_ShowState= 0x00;
    gs_DispStt.uiIndex = 0;         //ȫ����ʾ
    gs_DispStt.ucMode = Const_DispMode_Full;
    gs_DispStt.ucTmr = gs_DispCont.ucFullShowTm;    //����ʱ��5s
#endif
}
/*=========================================================================================\n
* @function_name: ShowInitial
* @function_file: Lcdshow.c
* @����: ��ʾ��ʼ��
*
* @����:
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowInitial(void)
{
//    SysE2ReadData(EEP_MAX_LX_NUM,&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);   //��ȡ��ʾ��
//    gs_DispCont.ul_CRC=do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);       //������ʾ���crc
    gs_DispCont.ucLxCnt = 4;       //��������
    gs_DispCont.ucJxCnt = 4;        //��������
    gs_DispCont.ucLxTm = 5;        //ÿ����ʾʱ��
    gs_DispCont.ucJxTm = 5;         //����ʱ��
    gs_DispCont.ucJxPowOffTm = 5;    //ͣ�����ʱ��
    gs_DispCont.ucFullShowTm = 5; //ȫ����ʾʱ��
//    
//    gs_DispCont.ucPowUpBgTm = InitPara3[44]; //�ϵ米����ʱ��
//    gs_DispCont.ucIrBgTm = InitPara3[45];  //���ⴥ��������ʱ��
//    gs_DispCont.ucKeyBgTm = InitPara3[46]; //��������������ʱ��
}
/*=========================================================================================\n
* @function_name: ShowKeyManage
* @function_file: Lcdshow.c
* @����: ����������ʾ����
* 
* 
* @����: 
* @param:ucType  ��ʾ���, Const_Disp_KeyUp-�Ϸ�, Const_Disp_KeyDn-�·�
* @����: 
* @����:   lwb (2012-05-15)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ShowKeyManage(void)
{
    //�����ͣ���£��Ͳ���Ҫ��ʾ������
    if(!_SYS_IS_PWR_OFF)                            //�е��½��д�������ʾ
    {
        gs_DispStt.ucTmr = gs_DispCont.ucJxTm;
    }else
    {
        gs_DispStt.ucTmr = gs_DispCont.ucJxPowOffTm;
    }
    
    if(gs_DispCont.ucJxCnt == 0)
    {                                       //���Ա�Ϊ0
        gs_DispCont.ucJxCnt = 1;
    }

    if(gs_DispStt.ucMode != Const_DispMode_JX)
    {                                       //�ɷǼ���״̬�������״̬
        gs_DispStt.ucMode = Const_DispMode_JX;
        gs_DispStt.uiIndex = 0;
    }
    else
    {                                                               //�������ڼ���״̬
        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucJxCnt)
        {
            gs_DispStt.uiIndex = 0;
        }
    }

    gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
    ShowRefresh();                                  //����ˢ��
}
/*=========================================================================================\n
* @function_name: ShowSecondProc
* @function_file: Lcdshow.c
* @����: һ���ӵ���һ��,��ϵͳ����N���Ժ�ϵͳ����N��֮�ڡ�ϵͳ�е������������,����֮���
*       ��ϵ�ǻ���������״̬�л�����һ������,���ǵ����賿xʱ��yʱ֮����������Ļ�,������
*       �˳�ʱ,����뵽����״̬��ͣ��״̬,��������1min�ͻ��ֽ���ر���ʾ״̬.
* @����:
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowSecondProc(void)
{

    gui_SystemEvent |= flgEtGlb_RefreshLcd;             //����LCDˢ��

    
//    guc_PrOutTm++;
//    if(guc_PrOutTm>=60)
//    {
//        guc_PrOutTm=0;
//        KeyPgm_DyOut();                                 //��̰������˳�
//        PwBs_DyOut();
//    }
    
    
    if(guc_ShowStCom>0)      //��ʾͨ�ŷ���
    {
        guc_ShowStCom--;
        if(guc_ShowStCom==0)
        {
//          gul_ShowState &= ~flgShowSt_Phone;
        }
    }
    
    if(gs_DispStt.ucTmr != 0)
    {
        gs_DispStt.ucTmr--;
        if(gs_DispStt.ucTmr>0)                          //�жϸ���ʾ״̬��ʱ�Ƿ�,��Ҫ����״̬�л�
        {
            return; 
        }
    }

    switch(gs_DispStt.ucMode)
    {
    case Const_DispMode_LX:       //����
//        if(guc_PllSta == PLL_800K)
//        {
////            gs_DispStt.ucTmr = gs_DispCont.ucLxTm/2;
//        }
//        else
//        {
            gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
//        }

        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucLxCnt)
        {
            gs_DispStt.uiIndex = 0;                     //���Ÿ��鵽��һ��
        }
        break;
    case Const_DispMode_JX:       //����  
        gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
        gs_DispStt.ucMode = Const_DispMode_LX;
        gs_DispStt.uiIndex = 0;
        break;
    case Const_DispMode_TX:        //ͣ��
      break;
    case Const_DispMode_Full:      //ȫ��
//      if(gs_DispStt.ucTmr != 0)
//        break;
//      AlarmLedLow();
    default:
                                                        //��λ������״̬
        gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
        gs_DispStt.ucMode = Const_DispMode_LX;
        gs_DispStt.uiIndex = 0;
        break;
    }
    return;
}
 
/*=========================================================================================\n
* @function_name: ShowStateManage
* @function_file: Lcdshow.c
* @����: ����״̬λ����ʾ׼��
*
* @����:
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowStateManage(void)
{
//  static uint8 flg = 0;

    if(!_SYS_IS_PWR_OFF)
    {
//        if(((guc_CoverStatus&0x0f) == CoverOpen)&&(gul_ShowId != 0x03300E01)&&(gul_ShowId != 0x03300E02))//�������ʾ ��β��һ������ʾ
//        {
//            gul_ShowState|=flgShowSt_Pane1;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Pane1;
//          
//        }
//        if(((guc_CoverWStatus&0x0f) == CoverOpen)&&(gul_ShowId != 0x03300D01)&&(gul_ShowId != 0x03300D02))//����β����ʾ ���һ������ʾ
//        {
//            gul_ShowState|=flgShowSt_Pane2;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Pane2;
//        }
    
//        if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir)  //���ʷ�����ʾ
//        {
//            gul_ShowState|=flgShowSt_Lift;
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Lift;
//        }

        if(gut_SysWarn.SysWarn.BatLow==true)   //��ر���
        {
            gul_ShowState|=flgShowSt_Bat;
        }else
        {
            gul_ShowState&=~flgShowSt_Bat;
        }
//        
//        if(guc_FactoryType == FactorMd)   //���ڷ���
//        {
//            gul_ShowState|=flgShowSt_Switch;
//        }else
//        {
//          if(gui_SystemState & flgStSys_Program)   // �Ƿ���״̬
//          {
//            if(flg)                   // �����˸��ʾ
//            {
//              flg = 0;
//              gul_ShowState|=flgShowSt_Switch;
//            }else
//            {
//              flg = 1;
//              gul_ShowState &= ~flgShowSt_Switch;
//            }
//          }else                                  
//          {
//            gul_ShowState &= ~flgShowSt_Switch;      
//          }
//        }
//        
//         if(ge_Channel == SETA)   //ͨ������
//        {
////            gul_ShowState|=flgShowSt_L;
//            gul_ShowState&=~flgShowSt_N;
//        }else
//        {
//            gul_ShowState|=flgShowSt_N;
//            gul_ShowState&=~flgShowSt_L;
//        }
//        if(gs_MeterState.ui_MeterState7.RunCode7Word.IImbalance)   //������ƽ�����
//        {
//          gul_ShowState|=flgShowSt_Scale;
//          AlarmLedHigh();  //��������
//        }
//        else
//        {
//          gul_ShowState&=~flgShowSt_Scale;
//          AlarmLedLow();
//        }
           
    }else
    {
        gul_ShowState=0;                    //ͣ���²���ʾ״̬
    }
}
/*=========================================================================================\n
* @function_name: ShowNumManage
* @function_file: Lcdshow.c
* @����:
*
*
* @����:
* @param:ulID  ���ݱ�ʶ
* @����:
* @����:   zb (2015-12-2)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
/*
void ShowNumManage(uint32 ulID,uint8 ucSubNo)
{
    uint32  ulNum;
    uint32  ulMsk = 0;
    uint8   i,nobuf[6],dotbuf,j;
    Word32  timebuf,databuf;
    uint32  buf;
    
    CLRWDT();  
    switch(ulID)
    {
    case 0x00000000:                    //�ܵ���
//      BE_ReadP(EEP_EDEC, (uint8*)&dotbuf,1);
      dotbuf = 2;
      switch(dotbuf)
      {
        case 0: //û��С����
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/1000);
          ulNum&=~0xff800000;     //����799999,��0��ʼ
          j = 7;//����7λ
          break;
        case 2: //2��С����
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/10);
          ulNum&=~0x80000000;     //����799999.99,��0��ʼ
          j = 5;//����5λ
          break;
        default://û��С����
          ulNum = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/1000);
          ulNum&=~0xff800000;     //����799999,��0��ʼ
          j = 7;//����7λ
      }
      for( i=0; i<j; i++)   //��������
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }     
      break;
    case 0x02010100:       //��ѹ
      ulNum = CalRMS(RMSU);
//      ulNum = Hex2BCD(ulNum/1000);
//      ulNum&=~0xff800000;     //����799999.99,��0��ʼ
      j = 6;//����6λ
      for( i=0; i<j; i++)   //��������
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x02020100:      //����
      ulNum = CalRMS(RMSI1);
      j = 4;//����4λ
//      ulNum = Hex2BCD(ulNum/1000);
//      ulNum&=~0xff800000;     //����799999.99,��0��ʼ
      for( i=0; i<j; i++)   //��������
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x02800001:      //���ߵ���
//      databuf.lword = 0;
//      BE_ReadP(EEP_KBGETNO, (uint8*)databuf.byte,3);
//      BE_ReadP(EEP_FXQDETNO, (uint8*)databuf.byte,3);
      
      ulNum = CalRMS(RMSI2);
      j = 4;//����4λ
      for( i=0; i<j; i++)   //��������
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(j== i)
      {
        ulMsk = ulMsk<<4;
      }
      break;
    case 0x03300E00:      //��β�Ǵ���
      databuf.lword = 0;
//      BE_ReadP(EEP_KBWGETNO, (uint8*)databuf.byte,3);

      ulNum = Hex2BCD(databuf.lword);
      for( i=0; i<7; i++)   //��������
      {
        if((ulNum<<(i*4))&0xF0000000L)
        {
          ulMsk = ulMsk<<4;
          break;
        }
        else
        {
          ulMsk|=0xA0000000L;
          ulMsk = ulMsk>>4;
        }
      }
      if(7 == i)
      {
        ulMsk = ulMsk<<4;
      }
      break;      
    case 0x04000101:      //����
      ulNum = 0;
      GetSysClock( timebuf.byte, Const_YYMMDD);
      for(i=0; i <3; i++)
      {
        buf = 0;
        buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
        ulNum |= buf;
      }
      ulMsk = 0xAA000000;
      break;
    case 0x04000102:      //ʱ��
      ulNum = 0;
      GetSysClock( timebuf.byte, Const_hhmmss);
      for(i=3; i>0; i--)
      {
        buf = 0;
        buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
        ulNum |= buf;
      }
      ulMsk = 0xAA000000;
      break;
    case 0x04000402:      //���
      SysE2ReadData(EEP_METERNO, (uint8*)nobuf,6);
//      BE_ReadP(EEP_METERNO +EEP_BAK_LEN, (uint8*)nobuf,6);//������
//      BE_ReadP(EEP_METERNO, (uint8*)nobuf,6);//������
      ulNum = 0;
//      if(ucSubNo)  //��ŵ�8λ
//      {
        for(i=4; i>0; i--)
        {
          ulNum = ulNum << 8;
          ulNum |= nobuf[i-1];
        }
//      }
//      else        //��Ÿ�4λ
//      {
//        for(i=5; i>=4; i--)
//        {
//          ulNum = ulNum << 8;
//          ulNum |= nobuf[i];
//        }
//        for( i=0; i<4; i++)   //��������
//        {
//          if((ulNum<<(i*4))&0xF0000000L)
//          {
//            ulMsk = ulMsk<<4;
//            break;
//          }
//          else
//          {
//            ulMsk|=0xA0000000L;
//            ulMsk = ulMsk>>4;
//          }
//        }
//        if(4 == i)
//        {
//          ulMsk = ulMsk<<4;
//        }        
//      }
      break; 
    case 0x03300D01:      //���һ�ο������ʼʱ�� ����
        ulNum = 0;
        DataProcRead2Slice(KBGJLID,0,3,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_YYMMDD);
        for(i=0; i <3; i++)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
        break;
     case 0x03300D02:      //���һ�ο������ʼʱ��  ʱ�� 
        ulNum = 0;
        DataProcRead2Slice(KBGJLID,0,0,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_hhmmss);
        for(i=3; i>0; i--)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;
    case 0x03300E01:      //���һ�ο�β�Ǵ�����ʼʱ��  ����
        ulNum = 0;
//        DataProcRead2Slice(KBWGJLID,0,3,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_YYMMDD);
        for(i=0; i <3; i++)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i])<<((2-i)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;
    case 0x03300E02:      //���һ�ο�β�Ǵ�����ʼʱ��  ʱ��

        ulNum = 0;
//        DataProcRead2Slice(KBWGJLID,0,0,3,timebuf.byte);
//        GetSysClock( timebuf.byte, Const_hhmmss);
        for(i=3; i>0; i--)
        {
          buf = 0;
          buf = (buf|(uint32)timebuf.byte[i-1])<<((i-1)*8);
          ulNum |= buf;
        }
        ulMsk = 0xAA000000;
      break;      
    default:
      ulNum = 0x00000000;
      ulMsk = 0x72310000;
    }
    gs_LcdDisp.ulNum1 = ulNum;
    gs_LcdDisp.ulNum1Msk = ulMsk;
    CLRWDT();  
}
*/
/*=========================================================================================\n
* @function_name: SearchDispNO
* @function_file: Lcdshow.c
* @����: ͨ�����ݱ�ʶ��������
*
*
* @����:
* @param:ulID
*
* @����:
* @return: uint16
* @����:   lwb (2012-03-19)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 SearchDispNO(Word32 ulID)
{
    if(ulID.byte[3]==0x00)                                  //������
    {
        for(uint8 i=0;i<guc_LenOfTabConvent;i++)
        {
            if(gCs_TabConvent[i].ulInID==ulID.lword)
            {
                return gCs_TabConvent[i].uiNumb;
            }
        }
    }else if(ulID.byte[3]==0x02)
    {
        for(uint8 i=0;i<guc_LenOfTabConvBL;i++)
        {
            if(gCs_TabConvBL[i].ulInID==ulID.lword)
            {
                return gCs_TabConvBL[i].uiNumb;
            }
        }
    }else if(ulID.byte[3]==0x03)
    {
        for(uint8 i=0;i<guc_LenOfTabAdd;i++)
        {
            if(gCs_TabAdd[i].ulInID==ulID.lword)
            {
                return gCs_TabAdd[i].uiNumb;
            }
        }

    }else if(ulID.byte[3]==0x04)
    {
        for(uint8 i=0;i<guc_LenOfTabConvCS;i++)
        {
            if(gCs_TabConvCS[i].ulInID==ulID.lword)
            {
                return gCs_TabConvCS[i].uiNumb;
            }
        }
    }
    return 0xff;    //��Ч��
}

/*=========================================================================================\n
* @function_name: ShowDataProc
* @function_file: Lcdshow.c
* @����: ��ʾ���ݵĴ���
*
* @����:
*
* @����:
* @return: 
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
/*
void ShowDataProc(void)
{
    uint16  uiAddr;                  //E2�и�����ʾ��ر�ĵ�ַ
    Word32  wdInID;                 //���ݱ�ʶ
      
    uint8   ucDispNo;              //����
    uint8   ucDispSubNo;            //��2����Ϣ
//    uint8   dotbuf;

    CLRWDT();  
    uiAddr = gs_DispStt.uiIndex *5;                         //������Ż�ȡ���ŵ�ַ

    if((gs_DispStt.ucMode==Const_DispMode_LX)||(gs_DispStt.ucMode==Const_DispMode_TX))
    {
        FCpyTMem(XDATA_RAMZONE, InitPara2 + uiAddr, 5);
        gul_ShowId=Uint8_To_Uint32(XDATA_RAMZONE);
//        uiAddr += EEP_LXTABLE;
//        BE_ReadP(uiAddr, XDATA_RAMZONE,5);   //��eeprom�л�����ݱ�ʶ
        
    }
    else if(gs_DispStt.ucMode==Const_DispMode_JX)
    {
      FCpyTMem(XDATA_RAMZONE, InitPara2 + uiAddr, 5);
      gul_ShowId=Uint8_To_Uint32(XDATA_RAMZONE);
//        uiAddr += EEP_JXTABLE;
//        BE_ReadP(uiAddr, XDATA_RAMZONE,5);   //��eeprom�л�����ݱ�ʶ

    }
    else if(gs_DispStt.ucMode==Const_DispMode_Full)
    {
        Disp_Full();
//        AlarmLedHigh();  //��������
        return;
    }
    else if(gs_DispStt.ucMode==Const_DispMode_AdvSysClr)
    {
              
    }    
    wdInID.lword = Uint8_To_Uint32(XDATA_RAMZONE);
    ucDispSubNo = XDATA_RAMZONE[4];
    
    ucDispNo = SearchDispNO(wdInID);   //�����ݱ�ʶ�л������

    
    gs_LcdDisp.uiUnitPt1 = gCs_DispTab[ucDispNo].uiUnitPoint;   //�õ���ʾ��λ��С����
    gul_ShowState |= gCs_DispTab[ucDispNo].ulShowState;  //�õ�����״̬
                                    
//    if((gul_ShowId==0x00000000)||(gul_ShowId==0x00000001)||(gul_ShowId==0x00000002))//����С���㵥������
//    {
//      BE_ReadP(EEP_EDEC, (uint8*)&dotbuf,1);
//      switch(dotbuf)
//      {
//        case 0: //û��С����
//          break;
//        case 2: //2��С����
//          gs_LcdDisp.uiUnitPt1 |= 0x30;
//          break;
//        default://û��С����
//          break;
//      }
//    }
    
    CLRWDT();  
    
    ShowNumManage(wdInID.lword, ucDispSubNo);


}
*/
/*=========================================================================================\n
* @function_name: ShowRefreshTime
* @function_file: Lcdshow.c
* @����: ͣ���������ʾʱ��ʱ��ֱ�Ӹ���,���ﲻȥ���ݴ���õ�ʱ���ǳ���ͣ��ʱ���Ŀ���
*
* @����:
* @����:
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowRefreshTime(void)
{
    GetSysClock((uint8*)&gs_LcdDisp.ulNum1, Const_hhmmss);
    return;
}

/*=========================================================================================\n
* @function_name: ShowRefresh
* @function_file: Lcdshow.c
* @����: ��ʾˢ��
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowRefresh(void)
{
    uint8 ucType = Const_NeedRefresh;

    
    ShowStateManage();
    
    ShowDataProc();
    if(gs_DispStt.ucMode==Const_DispMode_Full)
    {
      return;
    }
    if(ucType == Const_NeedRefresh)
    {
        Disp_State(gul_ShowState);
        Disp_Numb(gs_LcdDisp.ulNum1, gs_LcdDisp.ulNum1Msk);
        Disp_UnitPoint(gs_LcdDisp.uiUnitPt1);
//        guc_LCDRAM[7] = 0x9f;  //������С����ͷ���
//        guc_LCDRAM[6] &= 0x0f;
//        guc_LCDRAM[6] |= 0x40;
//        guc_LCDRAM[5] &= 0x7f;
//        guc_LCDRAM[4] &= 0x7f;
//        guc_LCDRAM[3] &= 0x7f;
//        guc_LCDRAM[2] &= 0x7f;
//        guc_LCDRAM[1] &= 0x7f;
//        guc_LCDRAM[0] = 0x00;
        
        LCD_RAMUpdata();
        gul_ShowState = 0;   //״̬���
    }
}


extern const uint8 code NUMTABLE_1L[];
extern const uint8 code NUMTABLE_1H[];
extern const uint8 code NumAddr[12];
/*=========================================================================================\n
* @function_name: PowOffShowRefresh
* @function_file: Lcdshow.c
* @����: ͣ������ʾˢ��
*
* @����:
* @����:
* @����:   lwb (2012-03-07)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void PowOffShowRefresh(void)
{   
    
//    gs_LcdDisp.ulNum1 = Hex2BCD((gs_EnergyA.lCP[0]+Eny_GetEp1( 0, 0))/10);
//    gs_LcdDisp.ulNum1&=~0x80000000;     //����799999.99,��0��ʼ
    
    gs_LcdDisp.ulNum1 = gul_Test;  //������
    gs_LcdDisp.ulNum1Msk =0xAA000000;
    
    Disp_Numb(gs_LcdDisp.ulNum1, gs_LcdDisp.ulNum1Msk);
    
//    guc_LCDRAM[7] = 0x9f;  //������С����ͷ���
//    guc_LCDRAM[6] &= 0x0f;
//    guc_LCDRAM[6] |= 0x40;
//    guc_LCDRAM[5] &= 0x7f;
//    guc_LCDRAM[4] &= 0x7f;
//    guc_LCDRAM[3] &= 0x7f;
//    guc_LCDRAM[2] &= 0x7f;
//    guc_LCDRAM[1] &= 0x7f;
//    guc_LCDRAM[0] = 0x00;
        
    LCD_RAMUpdata();
}
/*=========================================================================================\n
* @function_name: SleepDispInit
* @function_file: Lcdshow.c
* @����: ˯��ǰ��ʼ����ʾ
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-03)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void SleepDispInit(void)
{
    gs_DispStt.uiIndex = 0;         //��ʾ���л�����һ��
    guc_PowOffRuning=false;         //����״̬�л���˯��
}

/*=========================================================================================\n
* @function_name: SleepDisp
* @function_file: Lcdshow.c
* @����: ������ʾ
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
uint8 SleepDisp(void)
{

    if(gs_DispStt.ucTmr!=0)          //������ʾ
    {
        gs_DispStt.ucTmr--;
    }

    if(gs_DispStt.ucTmr>0)
    {
        //�����ʱ��������Ҫ��ȡʱ��
        if(gul_ShowId == 0x04000102) 
        {
            SleepTimeProc();
            gs_DispStt.ucPwrOffRefresh|= Cosnt_RefreshTime;
            ShowRefresh();
        }
        return true;
    }

//  if(gs_DispStt.ulPwrOffTmr!=0)   //ͣ��ʱ�䵽
//  {
//      if(((gs_FunCfg.uc_PWOFFSHOWMDCfg&0x99)==0x09))  //ͣ�糣��
//      {
//          gs_DispStt.uiIndex = 0;                     //���Ÿ��鵽0
//          gs_DispStt.ucTmr = 1;                       //ʱ������60s
//          gs_DispStt.ucMode = Const_DispMode_TX;
//          gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
//          ShowRefresh();
//          return false;
//      }
//  }


    if(gs_DispStt.ucTmr==0)
    {
        if(gs_DispStt.ucMode == Const_DispMode_LX)
        {
            SleepTimeProc();
            gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
            gs_DispStt.uiIndex++;
            gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
            if(gs_DispStt.uiIndex >= gs_DispCont.ucLxCnt)
            {
                gs_DispStt.uiIndex = 0;                     //���Ÿ��鵽0
                return false;
            }
        }else 
        {
            return false;
        }
        ShowRefresh();
    }
    return true;
}