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
    guc_DyBgLed = gs_DispCont.ucFullShowTm;         //�ϵ米��ʱ���ȫ��ʱ��һ��
    gul_ShowState= 0x00;
    gs_DispStt.uiIndex = 1;         //ȫ����ʾ
    gs_DispStt.ucMode = Const_DispMode_Full;
    gs_DispStt.ucTmr = gs_DispCont.ucFullShowTm;    //����ʱ��5s
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
    SysE2ReadData(EEP_MAX_LX_NUM,&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);   //��ȡ��ʾ��
    gs_DispCont.ul_CRC=do_CRC(&gs_DispCont.ucLxCnt,sizeof(S_DISPCONTENT)-2);       //������ʾ���crc
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
void ShowKeyManage(uint8 ucType)
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
//      if(guc_ShowErrEndFlag!=true)
//      {
//          gs_DispStt.uiIndex = 0;
//
//          if(gut_SysWarn.byte)                                //����澯�ֲ�Ϊ0�Ļ�
//          {
//              if(gs_DispStt.uiIndex == gs_DispCont.uc_ShowErrPst)
//              {
//                  gs_DispStt.ucMode=Const_DispMode_Err;
//                  guc_ErrSwPt=0;
//                  guc_ErrBtnFlag=true;
//
//              }
//          }
//      }
    }
    else
    {                                                               //�������ڼ���״̬
        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucJxCnt)
        {
//          if(gs_DispCont.uc_ShowErrPst>=gs_DispCont.ucJxCnt
//             || gs_DispCont.uc_ShowErrPst==0)
//          {
//              if(gut_SysWarn.byte)                               //����澯�ֲ�Ϊ0�Ļ�
//              {
//                  gs_DispStt.ucMode=Const_DispMode_Err;
//                  guc_ErrSwPt=0;
//                  guc_ErrBtnFlag=true;
//              }
//          }
            gs_DispStt.uiIndex = 0;
//          guc_ShowErrEndFlag=false;
        }
//      else if(gs_DispStt.uiIndex == gs_DispCont.uc_ShowErrPst)
//      {
//          if(gut_SysWarn.byte)                                //����澯�ֲ�Ϊ0�Ļ�
//          {
//              gs_DispStt.ucMode=Const_DispMode_Err;
//              guc_ErrSwPt=0;
//              guc_ErrBtnFlag=true;
//          }
//      }
    }

    gs_DispStt.ucPwrOffRefresh |= Const_RefreshAll;
    ShowRefresh();                                  //����ˢ��
}
/*=========================================================================================\n
* @function_name: CheckErrorCode
* @function_file: Lcdshow.c
* @����: ��⵱ǰ�Ƿ���Ҫ��ʾ������
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-19)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void CheckErrorCode(void)
{
//    if(gut_SysWarn.byte==0)                            //����澯��Ϊ0�Ļ�,ֱ�ӷ���
//    {
//        return;
//    } 
//
////  if(gut_SysWarn.SysWarn.REVPOWER)
////  {
////      guc_ErrRevPowerSwTm++;
////      if(guc_ErrRevPowerSwTm>9)
////      {
////          gut_SysWarn.SysWarn.REVPOWER=false;
////          guc_ErrRevPowerSwTm=0;
////          gs_DispStt.ucTmr=1;             //�����л�������
////      }
////  }
//
//    guc_ErrCodeCnt=0;
// 
//    if(gut_SysWarn.SysWarn.BatLow)
//    {
//        guc_SwErrCode[guc_ErrCodeCnt]=0x04;
//        guc_ErrCodeCnt++;
//    }
//    if(gut_SysWarn.SysWarn.EEPROMERROR)
//    {
//        guc_SwErrCode[guc_ErrCodeCnt]=0x06;
//        guc_ErrCodeCnt++;
//    }
// 
//    if(gut_SysWarn.SysWarn.TimeError)
//    {
//        guc_SwErrCode[guc_ErrCodeCnt]=0x08;
//        guc_ErrCodeCnt++;
//    }
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

    guc_PrOutTm++;
    if(guc_PrOutTm>=60)
    {
        guc_PrOutTm=0;
        KeyPgm_DyOut();                                 //��̰������˳�
        PwBs_DyOut();
    }
    
        
//  CheckErrorCode();
    ShowStateFlashManage();

    if(guc_ShowStCom>0)
    {
        guc_ShowStCom--;
        if(guc_ShowStCom==0)
        {
          gul_ShowState &= ~flgShowSt_Com;
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

//  if(gut_SysWarn.byte)                            //����澯�ֲ�Ϊ0�Ļ�,��ʾ������
//  {
//      if(gs_DispStt.ucMode!=Const_DispMode_Err)   //������ڴ���ģʽ�Ļ����л�������ģʽ
//      {
//          gs_DispStt.ucMode=Const_DispMode_Err;
//          guc_ErrSwPt=0;                          //��ʾ��һ��������
//      }else
//      {
//          guc_ErrSwPt++;                          //�Ѿ��ڴ���ģʽ�Ļ�����ʾ��һ��������
//          if(guc_ErrSwPt>=guc_ErrCodeCnt)
//          {
//              guc_ErrSwPt=0;
//          }
//      }
//
//      gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
//      return;
//  }
                                             //ϵͳ�е�״̬�¹���
    switch(gs_DispStt.ucMode)
    {
    case Const_DispMode_LX:
        gs_DispStt.ucTmr = gs_DispCont.ucLxTm;
        gs_DispStt.uiIndex++;
        if(gs_DispStt.uiIndex >= gs_DispCont.ucLxCnt)
        {
            gs_DispStt.uiIndex = 0;                     //���Ÿ��鵽0
        }
        break;
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

    if(!_SYS_IS_PWR_OFF)
    {
        gul_ShowState &= ~(flgShowSt_TJ+flgShowSt_Fee1      //�������ǰ״̬��ͣ����Ҳ����ʾ
                       +flgShowSt_Fee2+flgShowSt_Fee3
                       +flgShowSt_Fee4+flgShowSt_YQ1
                       +flgShowSt_YQ2+flgShowSt_PRvs
                       +flgShowSt_Fuh);

        gul_ShowState |=BIT8MAP[gs_FeeData.uc_FeeNo];       //������ʾ
        if(gs_FeeData.uc_FeeRSDN == 2)                      //ʱ�α���ʾ
        {
            gul_ShowState |= flgShowSt_YQ2;
        }else
        {
            gul_ShowState |= flgShowSt_YQ1;
        }
    
        /*if(guc_CoverStatus==1)                              //�������ʾ
        {
            gul_ShowState|=flgShowSt_TJ;
        }*/
    
        if(guc_FactoryType == FactorMd)                     // �Ƿ�����ģʽ
        {
            gul_ShowState ^= flgShowSt_Pgm;                 // ����ģʽ�б����ʾȡ��
        }else if(gui_SystemState & flgStSys_Program)        // �Ƿ���״̬
        {
            gul_ShowState |= flgShowSt_Pgm;                 // �����ʾ
        }
        else                                                // ���Ǳ��״̬
        {
            gul_ShowState &= ~flgShowSt_Pgm;                // ȡ�������ʾ
        }
    
        if(gs_MeterState.ui_MeterState1.RunCode1Word.PDir)  //���ʷ�����ʾ
        {
            gul_ShowState|=flgShowSt_PRvs;
        }

        if(gut_SysWarn.SysWarn.BatLow==true)   //��ر���
        {
            gul_ShowState|=flgShowSt_Bat;
        }else
        {
            gul_ShowState&=~flgShowSt_Bat;
        }
    }else
    {
        gul_ShowState=0;                    //ͣ���²���ʾ״̬
    }
}
/*=========================================================================================\n
* @function_name: ShowStateFlashManage
* @function_file: Lcdshow.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-22)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void ShowStateFlashManage(void)
{
    if(gs_PassWordCtr.ucSt02==BSST||gs_PassWordCtr.ucSt04==BSST) //02����������жϣ�����ֱ�ӷ��ش���
    {
        gul_ShowState|=flgShowSt_Lock;
    }else
    {
        gul_ShowState&=~flgShowSt_Lock;
    }
 }
/*=========================================================================================\n
* @function_name: ShowNumManage
* @function_file: Lcdshow.c
* @����:
*
*
* @����:
* @param:ucAtb  �൱����ʾ���й������������з���,BCD2HEX,�������ֵ�����,��״̬λ���������״̬�Ķ���λһ��
* @param:ucType  �൱�ڵ�λС�����ʽ���λ��,ĳ�����͵ı�������ʾ��ʽ�ض���������е�ĳһ����Ա��Ӧ
* @param:pucData  Ϊ��ʾ������,��Ч������ȫ�ֱ���ucLenָ��
* @param:ucLen
* @����:
* @����:   lwb (2012-03-19)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void ShowNumManage(uint8 ucAtb, uint8 ucType, uint8* pucData)
{
    uint32  ulNum;
    uint32  ulMsk;
    uint8 * pucNum;
    uint8 * pucMsk;
    uint8 ucMskLen;
    uint8 i;
    uint8 ucDocNum;

    ulNum = Uint8_To_Uint32(pucData);
    if(ucAtb & Const_DisppHEX2BCD)
    {
        ulNum = Hex2BCD(ulNum);
    }

    ulMsk=0;
    if(ucType==0x01)      //ʱ��
    {
        ulNum>>=8;
        ulMsk = 0xAA000000L;
    }else if(ucType==0x02 || ucType==0x12 || ucType==0x11)//����
    {
        ulMsk = 0xAA000000L;
    }
    else if(ucType==0x03)
    {
        //��ȡС����λ��
        if(guc_ShowEnergyFlag==0x55)
        {
            if(ulNum&0x80000000)        //������
            {
                ulNum&=~0x80000000;
            }
            gul_ShowState|=flgShowSt_Fuh;
        }

        BE_ReadP(EEP_EDEC,&ucDocNum,1);
        if(ucDocNum==0)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=8;
            }else
            {
                ulMsk=0x000000AAL;
            }    
        }
        else if(ucDocNum==1)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=4;
                gs_LcdDisp.uiUnitPt1 |= Point_D1;
            }else
            {
                gs_LcdDisp.uiUnitPt1 |= Point_D2;
                ulMsk=0x0000000AL;
            }
        }else
        {
            gs_LcdDisp.uiUnitPt1 |= Point_D2;
        }

        if(gs_FunCfg.uc_ENSHOWCfg&BIT2)                 //������λ��Ҫ����
        {
            ucAtb &=~ Const_DispNeedMsk;                //����Ҫ����
        }else
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)             //1λС��ʱ��Ҫ����
            {
                if(ucDocNum==0)                         //0λС����ʱ������7λ
                {
                    ucMskLen=7;
                }else
                if(ucDocNum==1)                         //1λС����ʱ������6λ
                {
                    ucMskLen=6;
                }else
                {
                    ucMskLen=5;
                }
            }else
            {
                ucMskLen=5;
            }
            ucAtb |= Const_DispNeedMsk;     //��Ҫ����
       }
    }else if(ucType==0x13||ucType==0x0b)
    {
        ulMsk = 0xAAAA0000L;
    }else if(ucType==0x04)                  //��ѹ��6
    {
        ucMskLen=6;
    }else if(ucType==0x05)                  //���������ߵ���
    {
        if(ulNum&0x800000)                  //������
        {
            ulNum&=~0x800000;
            gul_ShowState|=flgShowSt_Fuh;
        }        
        ucMskLen=4;
    }else if(ucType==0x06)                  //����
    {
        if(ulNum&0x800000)                  //������
        {
            ulNum&=~0x800000;
            gul_ShowState|=flgShowSt_Fuh;
        }
        
        BE_ReadP(EEP_PDEC,&ucDocNum,1);
        if(ucDocNum==0)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=16;
            }else
            {
                ulMsk=0x0000AAAAL;
            }    
        }
        else if(ucDocNum==1)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=12;
                gs_LcdDisp.uiUnitPt1 |= Point_D1;
            }else
            {
                gs_LcdDisp.uiUnitPt1 |= Point_D4;
                ulMsk=0x00000AAAL;
            }
        }else if(ucDocNum==2)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=8;
                gs_LcdDisp.uiUnitPt1 |= Point_D2;
            }else
            {
                gs_LcdDisp.uiUnitPt1 |= Point_D4;
                ulMsk=0x000000AAL;
            }
        }else if(ucDocNum==3)
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)
            {
                ulNum>>=4;
                gs_LcdDisp.uiUnitPt1 |= Point_D3;
            }else
            {
                gs_LcdDisp.uiUnitPt1 |= Point_D4;
                ulMsk=0x0000000AL;
            }
        }
        else
        {
            gs_LcdDisp.uiUnitPt1 |= Point_D4; 
        }

        if(gs_FunCfg.uc_ENSHOWCfg&BIT2)                 //������λ��Ҫ����
        {
            ucAtb &=~ Const_DispNeedMsk;                //����Ҫ����
        }else
        {
            if(gs_FunCfg.uc_ENSHOWCfg&BIT1)             //1λС��ʱ��Ҫ����
            {
                if(ucDocNum==0)                         //0λС����ʱ������7λ
                {
                    ucMskLen=7;
                }else
                if(ucDocNum==1)                         //1λС����ʱ������6λ
                {
                    ucMskLen=6;
                }else
                if(ucDocNum==2)                         //2λС����ʱ������6λ
                {
                    ucMskLen=5;
                }else
                if(ucDocNum==3)                         //3λС����ʱ������6λ
                {
                    ucMskLen=4;
                }
                else
                {
                    ucMskLen=3;
                }
            }else
            {
                ucMskLen=3;
            }
            ucAtb |= Const_DispNeedMsk;     //��Ҫ����
       }
    }else if(ucType==0x07)                  //��������
    {
        if(ulNum&0x8000)                  //������
        {
            ulNum&=~0x8000;
            gul_ShowState|=flgShowSt_Fuh;
        }
        ucMskLen=4;
    }

    if (ucAtb & Const_DispNeedMsk)
    {

        pucNum = ((uint8*)&ulNum)+3;
        pucMsk = ((uint8*)&ulMsk)+3;
        for(i=0; i<ucMskLen; i++)
        {//���жϸ�λ�ַ�,���жϵ�λ�ַ�
            if(i & 1)
            {//����,��Ӧ�ַ����ֽ��е�λ��Ϊ��λ
                if(*pucNum & 0x0F)
                {//��Ϊ��,���˳�
                    break;
                }
                else
                {//Ϊ0,����������
                    *pucMsk |= 0x0A;
                }
                pucNum--;           //����һ���ֽ�
                pucMsk--;
            }
                else
                {//ż��,��Ӧ�ַ����ֽڵĸ�λ
                    if(*pucNum & 0xF0)
                    {//��Ϊ��,���˳�
                        break;
                    }
                    else
                    {//Ϊ0,����������
                        *pucMsk |= 0xA0;
                    }
                }
        }
    }
    gs_LcdDisp.ulNum1 = ulNum;
    gs_LcdDisp.ulNum1Msk = ulMsk;
}
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
* @return: uint8 ����Const_Ret_OK / Const_Ret_Err / Const_Ret_Disp_Off / Const_Ret_DispFull
* @����:   lwb (2012-03-15)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 ShowDataProc(void)
{
    uint8   ucRet = Const_Ret_OK;
    uint8   ucUnitPtPos;
    uint8   ucAtb;
    uint16  uiAddr;                                         //E2�и�����ʾ��ر�ĵ�ַ
    uint8   ucDispNo;                                       //����
    uint8   ucShowIdPos;
    S_LCDDATEINFO psRet;                                    //���ڽ������ݴ����ؽ��

    MemSet((uint8*)&psRet, 0, sizeof(S_LCDDATEINFO));
    uiAddr = gs_DispStt.uiIndex *5;                         //������Ż�ȡ���ŵ�ַ

    if(gs_DispStt.ucMode==Const_DispMode_LX
       ||gs_DispStt.ucMode==Const_DispMode_TX)
    {
        uiAddr += EEP_LXTABLE;
        BE_ReadP(uiAddr, XDATA_RAMZONE,5);
    }else if(gs_DispStt.ucMode==Const_DispMode_JX)
    {
        uiAddr += EEP_JXTABLE;
        BE_ReadP(uiAddr, XDATA_RAMZONE,5);
        
    }else if(gs_DispStt.ucMode==Const_DispMode_Full)
    {
        return Const_Ret_DispFull;
    }
    else if(gs_DispStt.ucMode==Const_DispMode_IRDA)
    {
        MemCpy(XDATA_RAMZONE,guc_IrShowLcdId,5);       //��������
        //ͨѶID����
    }else if(gs_DispStt.ucMode==Const_DispMode_Err)
    {
        ucRet = Const_Ret_DispMode_Err;
    }else
    {
        ucRet = Const_Ret_Err;      //����״̬���ý�����ʾ����,��ʱӦ������ʾ���ر�״̬
    }

    if(ucRet != Const_Ret_OK)
    {                               //�����������������֯,ֱ�ӽ���߼���ʾ��������ʾ��ʽ
        return ucRet;
    }

    psRet.uiID.lword=Uint8_To_Uint32(XDATA_RAMZONE);
    gul_ShowId=psRet.uiID.lword;            //ͣ����ʾ��
    ucDispNo=SearchDispNO(psRet.uiID);
    ucShowIdPos=XDATA_RAMZONE[4];
    if(ucShowIdPos==0x01)
    {
        ucDispNo++;
    }

    if((ucDispNo == 0) || (ucDispNo > Const_MaxDispTabNum))
    {   //���ų�����ʾ�������,��ʾ�����й���
        ucDispNo = DEFAULT_ENERGY_NO;
        psRet.uiID.lword=0;
        
    }

    gs_LcdDisp.uiStr1 = gCs_DispTab[ucDispNo].uiStr;
                                    //�õ���ʾ�������ַ�����Ϣ,������������
    ucUnitPtPos = gCs_DispTab[ucDispNo].ucAtb & Const_DispUnitPt;
                                    //���ڲ鵥λ��С�����
    gs_LcdDisp.uiUnitPt1 = gCui_UnitPointTab[ucUnitPtPos];
                                    //�õ���ʾ��λ��С����

    ucAtb = gCs_DispTab[ucDispNo].ucAtb & (Const_DispNeedMsk + Const_DispSigned + Const_DisppHEX2BCD);
    psRet.ucCmd = 0x11;
    psRet.ucAtb |= Const_Atb_ShowData;
    psRet.ucbuf=XDATA_RAMZONE;
    MemSet(XDATA_RAMZONE,0x00,14);
    guc_ShowEnergyFlag=0;
    RWData((S_FRAMEINFO*)&psRet);
                                    //�õ���ʾ����ͬʱ�õ����ݳ���,�ñ���psRet->ucLen����
    if(psRet.ucErr.word != Const_Data_OK)
    {
        ucRet = Const_Ret_Err;
        return ucRet;
    }
    if(ucUnitPtPos==0x11)           //У������
    {
        psRet.ucbuf+=4;
    }else if(ucUnitPtPos==0x13)           //��ţ�ͨѶ��ַ���ͻ����
    {
        psRet.ucbuf+=4;
    }else if(ucUnitPtPos==0x12)           //������ڣ�У������
    {
        if(ucDispNo == 0x29)
        {
            psRet.ucbuf+=7;
        }
        else
        {
            psRet.ucbuf+=3;
        }
    }
    
    ShowNumManage(ucAtb, ucUnitPtPos, psRet.ucbuf);
    return ucRet;
}

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
    uint8 ucRet = Const_Ret_OK;
    uint8 ucType = Const_NeedRefresh;

    ShowStateManage();
    if(_SYS_IS_PWR_OFF)
    {                                           //ϵͳ����
        if(gs_DispStt.ucPwrOffRefresh & Const_RefreshAll)
        {                                       //����������Ҫ����
            ucRet = ShowDataProc();
        }
        else if(gs_DispStt.ucPwrOffRefresh & Cosnt_RefreshTime)
        {                                       //ʱ����Ҫˢ��
            ShowRefreshTime();
        }else
        {
            ucType = Const_NoNeedRefresh;       //���л���������ʾʱ��Ļ�������Ҫˢ��
        }
    }
    else
    {                                           //�е�
        ucRet = ShowDataProc();
    }

    switch(ucRet)
    {
    case Const_Ret_OK:                          //������淵�����ֵ,����ʾ�����Ѿ���֯��
        break;
    case Const_Ret_Err:                         //display error,��ʾ"------"
        gs_LcdDisp.ulNum1Msk = 0x11111111L;
        break;
    case Const_Ret_DispFull:                    //ȫ����ʾ
        Disp_Full();
        ucType = Const_NoNeedRefresh;
        break;
//    case Const_Ret_DispMode_Err:
////      if(gut_SysWarn.SysWarn.REVPOWER)//���ʷ���
////      {
////          gs_LcdDisp.ulNum1=0x56;
////      }
////      else
//        {
//            gs_LcdDisp.ulNum1=guc_SwErrCode[guc_ErrSwPt];
//        }
//        gs_LcdDisp.ulNum1|=0x00E00000;
//        gs_LcdDisp.ulNum1Msk=0xAA033100;
//        gul_ShowState=0;
//        gs_LcdDisp.uiStr1=0;
//        gs_LcdDisp.uiUnitPt1=0;
//        break;
    default:
        break;
    }
    
    if(ucType == Const_NeedRefresh)
    {
        Disp_State(gul_ShowState);
        Disp_Numb(gs_LcdDisp.ulNum1, gs_LcdDisp.ulNum1Msk);
        Disp_String(gs_LcdDisp.uiStr1);
        Disp_UnitPoint(gs_LcdDisp.uiUnitPt1);
        LCD_RAMUpdata();
    }
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
