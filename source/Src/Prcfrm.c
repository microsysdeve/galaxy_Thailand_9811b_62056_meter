#define CM_PRCFRM_EXT
#include "Include.h"
uint8 Judge62056Frm(S_COM* psCom) ;
uint8 DoNothing(S_FRAMEINFO *s_FrmInfo)
{
    return s_FrmInfo->ucAtb;
}
/*==============================================================================
�������Ӧ�ĺ�������
�����֣� ���ԣ� ������(������һ���ļ��ж����)
==============================================================================*/
/*const S_CMDPROC code gs_CmdProc[] =
{
   //============ {0x11,RWData},                  //������
//  {0x13,ReadMeterAddr},           //��ͨѶ��ַ
  //====================================  {0x01,FactoryRD},               //���ڶ�
//opt     {0x02,FactoryWR},               //����д
 {0x11,NULL}, 
};
*/

const ComFPro code gs_ComProc[]=
{
    JbComHd,            //֡ͷ
    JbMode,             //�ж�ģʽ��������̣�������Ϣ
    ContinueRead,       //������ȡ
    PrRdWr,             //��̶�дģʽ
};

const uint8 code ComProc_Len=dim(gs_ComProc);	
/*=========================================================================================\n
* @function_name: BD_ProcFrame
* @function_file: Prcfrm.c
* @����:
*
*
* @����:
* @param:ComProcCtr
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
extern const ComFPro code gs_ComProc[];
 volatile uint8 iResult;;
uint8 BD_ProcFrame(S_COM *ComProcCtr)
{
   
//    S_FRAMEINFO s_FrmInfo;                              //������ʱ������������Ϣ
    //�ж���1107��Լ�Ļ���645��Լ��
//    s_FrmInfo.ucPort=ComProcCtr->ucPort;

//    if(Judge645Frm(ComProcCtr, &s_FrmInfo) == Ret_Err)  //�ж�645֡�Ƿ��ǺϷ�֡
    {
        //�ж��Ƿ���62056-21��Լ
        //���Ȱ������������λ��У��λȥ��
//        for(uint8 i=0;i<ComProcCtr->ucLen;i++)
//        {
//            ComProcCtr->ucBuf[i]&=0x7F;
//        }


        extern const uint8 ComProc_Len;
        if(gs_PtlCrt.uc_ComStep>ComProc_Len)
        {
            ReturnErr();
        }else
        {
          //��������֡�жϣ�
 
            if(Judge62056Frm(ComProcCtr) == Ret_Err)  //�ж�62056֡�Ƿ��ǺϷ�֡
            {
              debug_break( _debug_errno_62056_frame_CrcFAIL_ );
                return Ret_Err;
            }
            iResult = gs_ComProc[gs_PtlCrt.uc_ComStep](ComProcCtr); 
            if ( iResult ) //if(gs_ComProc[gs_PtlCrt.uc_ComStep](ComProcCtr))
            {
             debug_break( _debug_errno_62056_frame_FunFAIL_ );
                return Ret_Err;
            }
            else
            {
                guc_ShowStCom = 4;           //��ʾ3s
                OpenGJLed();
            }
        }
        //��ʼ����7λ����λ1λУ��λ
//      guc_PrtlTpye=Prtl_1107;
        if(ComProcCtr->ucPort==ComIndex_Uart4)
        {
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart4(_bps300_);//, 0);        // ��ʼ��ģ�⴮��
            }
            else
            {
                Init_Uart4(_bps300_);// Init_Uart4(_bps2400_);//,  0);        // ��ʼ��ģ�⴮��
            }
        }
        else
        {
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart2(_bps300_);//, ,0);        //��ʼ������
            }
            else
            {
                Init_Uart2(_bps300_);//,, 0);        //��ʼ������
            }
        }

        ComBom_StartSend(ComProcCtr->ucPort);
        return Ret_OK;                              //�Ƿ�֡
    }
//  else
//  {
//      if(Decode645Frame(&s_FrmInfo) == Ret_Err)       //����645֡
//      {
//          return Ret_Err;
//      }
//
//      if(s_FrmInfo.ucErr == 0)
//      {
//          for(i = 0; i < sizeof(gs_CmdProc) / sizeof(S_CMDPROC); i++)
//          {
//              if(gs_CmdProc[i].ucCmd == s_FrmInfo.ucCmd)                  //���ҹ�Լ������
//              {                                                           //ִ����Ӧ����
//                  if(Ret_Err == gs_CmdProc[i].ProcFun(&s_FrmInfo))
//                  {
//                      return Ret_Err;
//                  }
//                  break;
//              }
//          }
//          if(i >= sizeof(gs_CmdProc) / sizeof(S_CMDPROC))
//          {
//              return Ret_Err;                                     //�Ҳ��������־�ֱ�ӷ��ش���
//          }
//      }
//
//      if(s_FrmInfo.ucReply != 0)                                  //�����Ҫ�ظ�
//      {
//          if(Encode645Frame(ComProcCtr, &s_FrmInfo) == Ret_OK)    //֡�Ĵ��
//          {
//              guc_PrtlTpye=Prtl_645;
//              //��ʼ����8λ����λ1λУ��λ
//
//              if(ComProcCtr->ucPort==ComIndex_Uart1)
//              {
//                  Init_Uart4(0,1);        //��ʼ��485
//              }
//              else
//              {
//                  Init_Uart2(0,1);        //��ʼ������
//              }
//
//              ComBom_StartSend(ComProcCtr->ucPort);
//              return Ret_OK;
//          }
//          else
//          {
//              return Ret_Err;
//          }
//      }else
//      {
//          return Ret_Err;
//      }
//  }
}
/*=========================================================================================\n
* @function_name: RemoveVerifyBit
* @function_file: Prcfrm.c
* @����: �Ƴ�62056-21��У��λ
* 
* @param: ComProcCtr 
* @����: lwb (2014/3/18)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void RemoveVerifyBit(S_COM *ComProcCtr)
{

    for(uint8 i=0;i<ComProcCtr->ucLen;i++)
    {
        ComProcCtr->ucBuf[i]&=0x7F;
    }
}
/*=========================================================================================\n
* @function_name: Judge645Frm
* @function_file: Prcfrm.c
* @����: �ж�645֡�Ƿ��ǺϷ���֡
*
*
* @����:
* @param:psCom  ͨѶ����
* @param:sFrm
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 Judge645Frm(S_COM* psCom, S_FRAMEINFO* sFrm)
{
    for(uint8 i = 0; i < LeadCharNum; i++)
    {
        if(psCom->ucLen < (MinFrmLen + i))          //�յ�������������Ҫ������С֡����
        {
            return Ret_Err;
        }
                                                    //�ж��Ƿ�����Ч֡
        else if(Ret_OK == IsValidFrame(psCom->ucBuf+i,psCom->ucLen - i))
        {                                           //�������ݵ���ʱ����

            //�ж��Ƿ����ݳ�����ȷ
            //MemCpy(sFrm->ucbuf, psCom->ucBuf + i, psCom->ucLen - i);
            sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK;                          //������Ч֡
        }
    }
    return Ret_Err;                                     //����Ч֡
}
/*=========================================================================================\n
* @function_name: Judge62056Frm
* @function_file: Prcfrm.c
* @����: �ж��Ƿ���62056��Լ
* 
* @param: psCom 
* @param: sFrm 
* 
* @return: uint8 
* @����: lwb (2014/3/26)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 Judge62056Frm(S_COM* psCom)
{
    for(uint8 i = 0; i < LeadCharNum; i++)
    {
        if(psCom->ucLen < (Min62056FrmLen + i))          //�յ�������������Ҫ������С֡����
        {
         	debug_break(_debug_errno_62056_frame_CrcFAIL1_);
            return Ret_Err;
        }
                                                    //�ж��Ƿ�����Ч֡
        else if(Ret_OK == IsValid62056Frame(psCom->ucBuf+i,psCom->ucLen - i))
        {                                           //�������ݵ���ʱ����

            //�ж��Ƿ����ݳ�����ȷ
            MemCpy(psCom->ucBuf, psCom->ucBuf + i, psCom->ucLen - i);
//          sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK;                          //������Ч֡
        }
    }
   	debug_break( _debug_errno_62056_frame_CrcFAIL2_);
    return Ret_Err;                                     //����Ч֡
}

/*=========================================================================================\n
* @function_name: IsValidFrame
* @function_file: Prcfrm.c
* @����: �Ϸ�֡�ж�
*
*
* @����:
* @param:pucBuf
* @param:ucFrmLen
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 IsValidFrame(uint8* pucBuf, uint8 ucFrmLen)
{
    uint8 ucSum;

    if((pucBuf[0]!= 0x68) || (pucBuf[7] != 0x68))   //֡ͷ0x68�ж�
    {
        return Ret_Err;
    }

    uint8 ucLen = pucBuf[PosDataLen];
    if(ucFrmLen < (MinFrmLen + ucLen))              //�յ�������֡��ʵ�ʳ��ȱȽ�
    {
        return Ret_Err;
    }

    ucSum = DoSum(pucBuf, ucLen + MinFrmLen - 2);   //����У���
    if(pucBuf[ucLen + MinFrmLen - 2] != ucSum)
    {                                               //У��Ͳ���
        return Ret_Err;
    }

    if(pucBuf[ucLen + MinFrmLen - 1] != 0x16)       //�ж�֡β�Ƿ�Ϊ0x16
    {
        return Ret_Err;
    }

    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: IsValid62056Frame
* @function_file: Prcfrm.c
* @����: �ж��Ƿ���62056��Ч֡ͷ
* 
* @param: pucBuf 
* @param: ucFrmLen 
* 
* @return: uint8 
* @����: lwb (2014/3/26)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 IsValid62056Frame(uint8* pucBuf, uint8 ucFrmLen)
{
    if(      (pucBuf[0]== '/') 
          || (pucBuf[0]== AS_SOH)
//        || (pucBuf[0]== AS_ACK)
          || ((pucBuf[0]== AS_ACK)&&(pucBuf[1]!= AS_SOH))
       )    
    {
        return Ret_OK;
    }
    else
    {
        return Ret_Err;
    }

}
/*=========================================================================================\n
* @function_name: DoSum
* @function_file: Prcfrm.c
* @����: ����У���
*
*
* @����:
* @param:pucBuf
* @param:ucLen
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
uint8 DoSum(uint8* pucBuf, uint8 ucLen)
{
    uint8 ucSum = 0;
    for(uint8 i = 0; i < ucLen; i ++)
    {
        ucSum += pucBuf[i];
    }
    return ucSum;
}
/*=========================================================================================\n
* @function_name: Decode645Frame
* @function_file: Prcfrm.c
* @����: ����645֡
*
*
* @����:
* @param:sFrm
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#ifdef _del
uint8 Decode645Frame(S_FRAMEINFO* sFrm)
{
    sFrm->ucReply = 1;                              //Ĭ������Ҫ�ظ���
    sFrm->ucErr = 0;                                //Ĭ��û�д���
    sFrm->uiID.lword = 0xFFFFFFFF;                  //����Ĭ�ϵ�IDΪȫF

    if(sFrm->ucbuf[9] > Max645FrmLen)               //��ֹ�����0x33�����н��ǻ��������ݸ�д
    {
        sFrm->ucReply = 0;                          //����Ҫ�ظ�
        return Ret_Err;
    }

    if(Judge645Addr(sFrm) == Ret_Err)
    {
        sFrm->ucAtb = Const_Addr_Err;               //���ַ����
        sFrm->ucReply = 0;                          //����Ҫ�ظ�
        return Ret_Err;
    }

    UnDo33(sFrm->ucbuf + 10, sFrm->ucbuf[9]);       //��������0x33

    sFrm->ucCmd = sFrm->ucbuf[8];                   //������
    sFrm->ucLen = sFrm->ucbuf[9];                   //���������ȳ���

    if((sFrm->ucCmd == 0x11)||(sFrm->ucCmd == 0x14))
    {                                               //���Ϊ��д�Ļ�
        sFrm->uiID.byte[0] = sFrm->ucbuf[10];       //���ݱ�ʶ
        sFrm->uiID.byte[1] = sFrm->ucbuf[11];
        sFrm->uiID.byte[2] = sFrm->ucbuf[12];
        sFrm->uiID.byte[3] = sFrm->ucbuf[13];
        if(sFrm->ucCmd == 0x14)                     //�����д���ݵĻ�
        {
//          if(sFrm->ucAtb!=Const_Addr_Normal)      //������ò�����ͨ��ַ���򷵻ش���
//          {
//              sFrm->ucErr = ComErrBit_Other;
//              sFrm->ucLen = 1;
//              return Ret_OK;
//          }
//
//
//          if(sFrm->ucLen < 12)                    //�������û��12�Ļ������Ǵ����֡
//          {
//              return Ret_Err;
//          }
//                                                  //�����ߴ���
//          sFrm->uiUserCode.byte[3] = sFrm->ucbuf[18];
//          sFrm->uiUserCode.byte[2] = sFrm->ucbuf[19];
//          sFrm->uiUserCode.byte[1] = sFrm->ucbuf[20];
//          sFrm->uiUserCode.byte[0] = sFrm->ucbuf[21];
//
//          if(guc_FactoryType == 0)                            //����״̬û���Ļ���Ҫ�ж�����
//          {
//              sFrm->ucLevel = JudgePassword(sFrm->ucbuf + 14);
//              if(sFrm->ucLevel == 0xFF)                       //�ж�Ȩ��
//              {
                    sFrm->ucAtb = Const_Atb_Pswd_Err;
                    sFrm->ucErr = ComErrBit_ErrPw;              //�������
                    sFrm->ucLen = 1;
                    return Ret_OK;
//              }
//          }
//          else
//          {
//                                                              //����״̬,����ָ��ָ��δ��������
//              sFrm->ucbuf+=22;                                //����ָ��ָ��δ��������
//              return Ret_OK;
//          }
//                                                              //���Ȩ��С��4�Ҳ��ڳ���״̬,��Ҫ�жϱ�̼�
//          if(((sFrm->ucLevel <= 4) && (gui_SystemState & flgStSys_Program))
//             || (sFrm->ucLevel == 0x98)                       //98��,99�����⴦��
//             || (sFrm->ucLevel == 0x99))
//          {                                       //�����������õ�����
//              //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 22, sFrm->ucLen - 12);
//              sFrm->ucbuf+=22;                    //����ָ��ָ��δ��������
//          }
//          else                                    //��̼�û�а���
//          {
//              sFrm->ucAtb = Const_Atb_Pswd_Err;   //�������
//              sFrm->ucErr = ComErrBit_ErrPw;
//              sFrm->ucLen = 1;
//              return Ret_OK;
//          }
        }
        else                                        //����Ϊ������
        {
            if(sFrm->ucLen < 4)                     //�������û��4�Ļ������Ǵ����֡
            {
                sFrm->ucErr = ComErrBit_Other;
                return Ret_Err;
            }
                                                    //��������
            //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 14, sFrm->ucLen - 4);
            sFrm->ucbuf+=14;                        //����ָ��ָ��δ��������
        }
    }
    else                                            //�Ȳ��Ƕ�Ҳ����д
    {                                               //��������
        //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 10, sFrm->ucLen);
        sFrm->ucbuf+=10;                            //CMD�����ֲ���0X11��0X14,��������
    }

    return Ret_OK;                                  //���ؽ�����ȷ
}
#endif
/*=========================================================================================\n
* @function_name: JudgePassword
* @function_file: Prcfrm.c
* @����: �ж������Ƿ���ȷ
*
*
* @����:
* @param:buff
*
* @����:
* @return: uint8 ����ȼ�������0xFF�����������
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
//uint8 JudgePassword(uint8* buff)
//{
//    uint8 PassWord[3];
//    if((buff[0] == 0x98) || (buff[0] == 0x99))      //�����98��99������ô����Ҫ�ж�����ֱ�ӷ���Ȩ��
//    {
//        return buff[0];
//    }
//
//    if((buff[0] != 0x02) && (buff[0] != 0x04))      //�������ȼ�������02����04�����
//    {
//        return 0xFF;
//    }
                                                    //��ȡ��Ӧ�ȼ�������
//    if(BE_ReadP(buff[0] * 3 + EEP_645PASSWD1, PassWord,3))
//    {
//        return 0xFF;
//    }

//   if((PassWord[0] == buff[1]) && (PassWord[1] == buff[2]) && (PassWord[2] == buff[3]))
//  {
       /*if((gs_PsLock.PsLockMask & 0x03) == 0)      //���û��������
       {
            if(buff[0] == 0x02)
            {
                gs_PsLock.PassW02 = 0;              //�����ʱ����
                gs_PsLock.cnt &= ~0x0F;             //�����������
            }
            else
            {
                gs_PsLock.PassW04 = 0;
                gs_PsLock.cnt &= ~0xF0;
            }
            return buff[0];
        }

        if((gs_PsLock.PsLockMask & 0x01) && (buff[0] == 0x02))
        {
            return 0xFF;
        }
        else if((gs_PsLock.PsLockMask & 0x02) && (buff[0] == 0x04))
        {
            return 0xFF;
        }
        else
        {
            if(buff[0] == 0x02)
            {
                gs_PsLock.PassW02 = 0;              //�����ʱ����
                gs_PsLock.cnt &= ~0x0F;             //�����������
            }
            else
            {
                gs_PsLock.PassW04 = 0;
                gs_PsLock.cnt &= ~0xF0;
            }
            return buff[0];
        }*/
//  }
//    else                                            //����������
//  {
//      if(!(gui_SystemState & flgStSys_Program))   //��̼�û�а���ֱ�ӷ���
//      {
//          return 0xFF;
//      }
//
//      if(buff[0] == 0x02)
//      {
//          gs_PsLock.cnt = 0xF0 | (0x0F & (gs_PsLock.cnt + 1));
//          if((gs_PsLock.cnt & 0x0F) >= 3)
//          {
//              gul_ShowState |= flgShowSt_Lock;    //��ʾ������
//              gs_PsLock.PassW02 = TIME_PSLOCK;
//              gs_PsLock.cnt &= ~0x0F;
//              gs_PsLock.cnt |= 0x03;
//              gs_PsLock.PsLockMask |= 0x01;
//          }
//      }
//      else if(buff[0] == 0x04)
//      {
//          gs_PsLock.cnt = 0x0F | (0xF0 & (gs_PsLock.cnt + 0x10));
//          if((gs_PsLock.cnt & 0xF0) >= 0x30)
//          {
//              gul_ShowState |= flgShowSt_Lock;    //��ʾ������
//              gs_PsLock.PassW04 = TIME_PSLOCK;
//              gs_PsLock.cnt &= ~0xF0;
//              gs_PsLock.cnt |= 0x30;
//              gs_PsLock.PsLockMask |= 0x02;
//          }
//      }
//      return 0xFF;                                //�������벻��ȷ
//    }
//}
/*=========================================================================================\n
* @function_name: Judge645Addr
* @function_file: Prcfrm.c
* @����: �ж�645��ַ�Ƿ���ȷ
*
*
* @����:
* @param:sFrm
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#ifdef DEL
uint8 Judge645Addr(S_FRAMEINFO* sFrm)
{
    uint8 i;
    BE_ReadP(EEP_COMADD,guc_MeteAddr, 6);           //��ȡ���ַ,�������ﲻ�ж�,�ظ���ʱ��Ҳ��Ҫ
    if(ApiBufCmp(sFrm->ucbuf+1, guc_MeteAddr, 6) != CMP_EQU)
    {
        for(i = 1; i <= 6; i++)
        {
            if(sFrm->ucbuf[i] != 0xAA)
            {
                break;
            }
        }

        if(i>=6)
        {
            sFrm->ucAtb = Const_Addr_Any;               //���ܵ�ַ
            return Ret_OK;
        }

        for(i = 1; i <= 6; i++)
        {
            if(sFrm->ucbuf[i] != 0x99)
            {
                break;
            }
        }

        if(i>=6)
        {
            sFrm->ucAtb = Const_Addr_Any;               //���ܵ�ַ
            sFrm->ucReply = 0;                          //����Ҫ�ظ�
            return Ret_OK;
        }

        for(i = 1; i <= 6; i++)
        {
            if(sFrm->ucbuf[i] != guc_MeteAddr[i - 1])
            {
                sFrm->ucAtb = Const_Addr_Err;           //���е����˵�����ַ����
                return Ret_Err;
            }
        }
    }
    else
    {
        sFrm->ucAtb = Const_Addr_Normal;                //������ַ
    }
    return Ret_OK;
}
#endif
/*=========================================================================================\n
* @function_name: Encode645Frame
* @function_file: Prcfrm.c
* @����: 645֡���
*
*
* @����:
* @param:psCom
* @param:sFrm
*
* @����:
* @return: uint8
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
#ifdef DEL
uint8 Encode645Frame(S_COM* psCom, S_FRAMEINFO* sFrm)
{
    psCom->ucBuf[0] = 0x68;                                         //��д֡ͷ
    psCom->ucBuf[7] = 0x68;                                         //��д֡ͷ

    MemCpy(psCom->ucBuf + 1,guc_MeteAddr,6);                        //��д��ַ��֡����ȥ

    if(sFrm->ucErr == 0)                                            //����Ӧ��
    {
        psCom->ucBuf[9] = sFrm->ucLen;                              //��д�����򳤶�
        if(sFrm->ucCmd == 0x11 || sFrm->ucCmd == 0x03
#ifdef SQSDPRLOG
           ||sFrm->ucCmd == 0x31
           ||sFrm->ucCmd == 0x32
           ||sFrm->ucCmd == 0x12
#endif
           )                                     //����Ƕ����ݵĻ�
        {
            psCom->ucBuf[9] += 4;                                   //�������ݱ�ʶ�ĳ���
            MemCpy(psCom->ucBuf+10,sFrm->uiID.byte,4);              //���ݱ�ʶ
            MemCpy(psCom->ucBuf + 14, (uint8*)sFrm->ucbuf, sFrm->ucLen);    //����������
        }
        else
        {                                                           //����������
            MemCpy(psCom->ucBuf + 10, (uint8*)sFrm->ucbuf, sFrm->ucLen);
        }

        sFrm->ucCmd |= 0x80;                                        //�����ּ�0x80
        psCom->ucBuf[8] = sFrm->ucCmd;                              //��д������

        Do33(psCom->ucBuf + 10, psCom->ucBuf[9]);                   //��������0x33����
        psCom->ucLen = MinFrmLen + psCom->ucBuf[9];                 //����֡�ĳ���
                                                                    //����У���
        psCom->ucBuf[psCom->ucLen - 2] = DoSum(psCom->ucBuf, psCom->ucLen - 2);
        psCom->ucBuf[psCom->ucLen - 1] = 0x16;                      //��д֡β
    }
    else
    {

        sFrm->ucCmd += 0xC0;                        //�����ּ�0xC0
        psCom->ucBuf[8] = sFrm->ucCmd;              //��д������
        psCom->ucBuf[9] = 0x01;                     //��д�����򳤶�
        psCom->ucBuf[10] = sFrm->ucErr + 0x33;      //��д������ + 0x33
        psCom->ucBuf[11] = DoSum(psCom->ucBuf, 11); //����У���
        psCom->ucBuf[12] = 0x16;                    //��д֡β
        psCom->ucLen = 13;                          //�ܹ�Ҫ���͵��ֽ���

    }
    
    return Ret_OK;
}

#endif
/*=========================================================================================\n
* @function_name: UnDo33
* @function_file: Prcfrm.c
* @����: ��������0x33�Ĳ���
*
*
* @����:
* @param:pucBuf
* @param:ucLen
* @����:
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void UnDo33(uint8* pucBuf, uint8 ucLen)
{
    for(uint8 i = 0; i < ucLen; i++)
    {
        pucBuf[i] -= 0x33;
    }
}
/*=========================================================================================\n
* @function_name: Do33
* @function_file: Prcfrm.c
* @����: ��������0x33�Ĳ���
*
*
* @����:
* @param:pucBuf
* @param:ucLen
* @����:
* @����:   lwb (2012-02-28)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:
===========================================================================================*/
void Do33(uint8* pucBuf, uint8 ucLen)
{
    for(uint8 i = 0; i < ucLen; i++)
    {
        pucBuf[i] += 0x33;
    }
}

