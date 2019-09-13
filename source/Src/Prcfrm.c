#define CM_PRCFRM_EXT
#include "Include.h"

uint8 DoNothing(S_FRAMEINFO *s_FrmInfo)
{
    return s_FrmInfo->ucAtb;
}
/*==============================================================================
�������Ӧ�ĺ�������
�����֣� ���ԣ� ������(������һ���ļ��ж����)
==============================================================================*/
const S_CMDPROC code gs_CmdProc[] =
{
    {0x11,RWData},                      //������
  //  {0x12,FactoryWR},                      //���������� RWData
    {0x14,RWData},                      //д����
    {0x13,ReadMeterAddr},               //��ͨѶ��ַ
    {0x15,WriteMeterAddr},              //дͨѶ��ַ
   // {0x08,BroadcastTime},               //�㲥Уʱ
   // {0x16,Freeze},                      //��������
    //{0x17,ChangeBode},                  //����ͨѶ����
    {0x18,ChangePassWord},              //��������
   // {0x1A,ClearMeter},                  //�������
   //{0x1C,SwitchCtrl},
   // {0x1B,ClearEvent},                  //�¼�����
   // {0x1D,SecPulsCtrl},                 //�๦�ܶ�������źſ���
    {0x1F,ParaInit},                    //������ʼ��
    {0x01,FactoryRD},                   //���ڶ�
 //   {0x02,FactoryWR},                   //����д
  //  {0x04,FactoryWR},                   //����д
   // {0x0f,FactoryWR},                   //����д
    //{0x03,CmpCode},                     //���ݱȶ�
};

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
uint8 BD_ProcFrame(S_COM *ComProcCtr)
{
    uint32 ulDey;
    uint8 i;
    S_FRAMEINFO s_FrmInfo;                              //������ʱ������������Ϣ
    s_FrmInfo.ucPort=ComProcCtr->ucPort;
    ulDey=0xffff;
    if(Judge645Frm(ComProcCtr, &s_FrmInfo) == Ret_Err)  //�ж�645֡�Ƿ��ǺϷ�֡
    {
        return Ret_Err;                                 //�Ƿ�֡
    }

    if(Decode645Frame(&s_FrmInfo) == Ret_Err)           //����645֡
    {
        return Ret_Err;
    }

//    gul_ShowState |= flgShowSt_Com;                     //ͨѶ��ʾ�绰������
    guc_ShowStCom = 3;                                  //��ʾ3s

    if(guc_ADKcal != ADK_None)                          //���Ͽ�
    {
        if(Ret_Err == ADK_CalFun(&s_FrmInfo))
        {
            return Ret_Err;
        }
    }    
    else if(s_FrmInfo.ucErr.word == 0)
    {
        for(i = 0; i < sizeof(gs_CmdProc) / sizeof(S_CMDPROC); i++)
        {
            if(gs_CmdProc[i].ucCmd == s_FrmInfo.ucCmd)                  //���ҹ�Լ������
            {                                                           //ִ����Ӧ����
                if(Ret_Err == gs_CmdProc[i].ProcFun(&s_FrmInfo))
                {
                    return Ret_Err;
                }
                break;
            }
        }
        if(i >= sizeof(gs_CmdProc) / sizeof(S_CMDPROC))
        {
            return Ret_Err;                                     //�Ҳ��������־�ֱ�ӷ��ش���
        }
    }

    if(s_FrmInfo.ucReply != 0)                                  //�����Ҫ�ظ�
    {
        if(Encode645Frame(ComProcCtr, &s_FrmInfo) == Ret_OK)    //֡�Ĵ��
        {
            while(guc_ComSendDy)
            {
                if(ulDey!=0)
                {
                    ulDey--;
                }else
                {
                    break;
                }
            }

            ComBom_StartSend(ComProcCtr->ucPort);
            return Ret_OK;
         }
        return Ret_Err;
    }else
    {
        return Ret_Err;
    }
    //return Ret_OK;
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
        else if(ApiCodeBufCmp(psCom->ucBuf+8+i,guc_ADKcmd,4)==CMP_EQU)   //���Ͽ˳�ʼ��
        {
            guc_ADKcal = ADK_Init;
            sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK; 
        }
        else if(psCom->ucLen == 0x1D + i 
                && psCom->ucBuf[8+i] == 0x11 
                && psCom->ucBuf[9+i] == 0x11)           //���Ͽ�У��
        {
            guc_ADKcal = ADK_Cal;
            sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK;                          //������Ч֡
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
    guc_ADKcal = ADK_None;
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
uint8 Decode645Frame(S_FRAMEINFO* sFrm)
{
    sFrm->ucReply = 1;                              //Ĭ������Ҫ�ظ���
    sFrm->ucErr.word = 0;                                //Ĭ��û�д���
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

    if(guc_ADKcal != ADK_None)
    {
        sFrm->ucbuf+=9;
        return Ret_OK;                                  //���ؽ�����ȷ
    }
    else if((sFrm->ucCmd == 0x11)||(sFrm->ucCmd == 0x14)
#ifdef SQSDPRLOG
       ||(sFrm->ucCmd == 0x12)
#endif
      )
    {                                               //���Ϊ��д�Ļ�
        MemCpy(sFrm->uiID.byte,sFrm->ucbuf+10,4);   //���ݱ�ʶ

        if(sFrm->ucCmd == 0x14)                     //�����д���ݵĻ�
        {
            if(sFrm->ucAtb!=Const_Addr_Normal)      //������ò�����ͨ��ַ���򷵻ش���
            {
                sFrm->ucReply = 0;                                  //����Ҫ�ظ���
                return Ret_Err;
            }
            if(sFrm->ucLen <= 12)                                    //�������û��12�Ļ������Ǵ����֡
            {
                return Ret_Err;
            }

            MemCpy(sFrm->uiUserCode.byte,sFrm->ucbuf+18,4);//�����ߴ���
           // if(guc_FactoryType != FactorMd)                         //����״̬û���Ļ���Ҫ�ж�����
            {
                sFrm->ucLevel = JudgePassword(sFrm->ucbuf + 14);
                if(sFrm->ucLevel == 0xFF)                           //�ж�Ȩ��
                {
                    sFrm->ucAtb = Const_Atb_Pswd_Err;
                    sFrm->ucErr.word = ComErrBit_ErrPw;             //�������
                    sFrm->ucLen = 1;
                    return Ret_OK;
                }
            }
            //else
            {
//              sFrm->ucLevel=sFrm->ucbuf[14];
                                                                    //����״̬,����ָ��ָ��δ��������
                sFrm->ucbuf+=22;                                    //����ָ��ָ��δ��������
                return Ret_OK;
            }
                                                                //���Ȩ��С��4�Ҳ��ڳ���״̬,��Ҫ�жϱ�̼�
//            if( (sFrm->ucLevel <= 4) 
//               || (sFrm->ucLevel == 0x98)                       //98��,99�����⴦��
//               || (sFrm->ucLevel == 0x99) ) 
//            {                                       //�����������õ�����
//                sFrm->ucbuf+=22;                    //����ָ��ָ��δ��������
//            }
//            else                                    //��̼�û�а���
//            {
//                sFrm->ucAtb = Const_Atb_Pswd_Err;   //�������
//                sFrm->ucErr.word = ComErrBit_ErrPw;
//                sFrm->ucLen = 1;
//                return Ret_OK;
//            }
        }
        else                                            //����Ϊ������
        {
            if(sFrm->ucCmd == 0x11)
            {
                if(
                   (sFrm->uiID.lword!=0x04040300)       //������Ȳ�����4�Ļ����Ҳ���Һ���鿴������Ǵ����֡��
                   &&(sFrm->uiID.byte[3]!=0x06)         //���ɼ�¼��ȡ�����ݳ��ȴ���4
                   &&(sFrm->uiID.byte[3]!=0x4F)         //����֡
                   &&(sFrm->ucLen != 4)
                   )
                   
                {
                    sFrm->ucErr.word= ComErrBit_Other;  //û���ҵ����ݱ�ʶ
                    sFrm->ucLen = 1;
                    return Ret_OK;
                }
            }
            else if(sFrm->ucCmd == 0x12)                //CMD=12,����Һ���鿴����
            {
                if(
                   (sFrm->uiID.lword!=0x04040300)       //������Ȳ�����5�Ļ����Ҳ���Һ���鿴������Ǵ����֡��
                    &&(sFrm->ucLen != 5)
                   )
                {
                    sFrm->ucErr.word = ComErrBit_Other; //û���ҵ����ݱ�ʶ
                    sFrm->ucLen = 1;
                    return Ret_OK;
                }
            }
            sFrm->ucbuf+=14;                        //����ָ��ָ��δ��������
        }
    }
    else                                            //�Ȳ��Ƕ�Ҳ����д
    {                                               //��������
        sFrm->ucbuf+=10;                            //CMD�����ֲ���0X11��0X14,��������
    }

    return Ret_OK;                                  //���ؽ�����ȷ
}
/*=========================================================================================\n
* @function_name: PwBs_DyOut
* @function_file: Prcfrm.c
* @����: ��������ж�
* 
* @����: 
* @����: 
* @����:   lwb (2012-06-07)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void PwBs_DyOut(void)
{
//    //�����ж��Ƿ����
//    if(gs_PassWordCtr.ucSt02==BSST)
//    {
//        if(gs_PassWordCtr.uiDyPW2Out>0)
//        {
//            gs_PassWordCtr.uiDyPW2Out--;
//            if(gs_PassWordCtr.uiDyPW2Out==0)
//            {
//                gs_PassWordCtr.ucSt02=0;
//                gs_PassWordCtr.ucPW2ErrCnt=0;
//                //����ʱ��
//                BE_WriteP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x02);    //д�����ʣ��ʱ��
//            }
//        }
// 
//    }
//
//    if(gs_PassWordCtr.ucSt04==BSST)
//    {
//        if(gs_PassWordCtr.uiDyPW4Out>0)
//        {
//            gs_PassWordCtr.uiDyPW4Out--;
//            if(gs_PassWordCtr.uiDyPW4Out==0)
//            {
//                gs_PassWordCtr.ucSt04=0;
//                gs_PassWordCtr.ucPW4ErrCnt=0;
//                //����ʱ��
//                BE_WriteP(EEP_PW4BSTM,(uint8*)&gs_PassWordCtr.uiDyPW4Out,0x02);    //д�����ʣ��ʱ��
//            }
//        }
//    }
}
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
uint8 JudgePassword(uint8* buff)
{
    uint8 PassWord[3];
//    uint8 ucBsCnt;
//  if((buff[0] == 0x98) || (buff[0] == 0x99))      //�����98��99������ô����Ҫ�ж�����ֱ�ӷ���Ȩ��
//  {
//      return buff[0];
//  }

    if((buff[0] != 0x02) && (buff[0] != 0x04))      //�������ȼ�������02����04�����
    {
        return 0xFF;
    }

                                                    //��ȡ��Ӧ�ȼ�������
    BE_ReadP(buff[0] * 3 + EEP_645PASSWD1, PassWord,3);
//    PassWord[0] = 0x00;
//    PassWord[1] = 0x00;
//    PassWord[2] = 0x00;
    if(ApiBufCmp(PassWord,buff+1,3)==CMP_EQU)
    {
        //�����ж���û�б���,
        if(buff[0]==0x02)               //02���������
        {

            if(gs_PassWordCtr.ucSt02==BSST) //02����������жϣ�����ֱ�ӷ��ش���
            {
                return 0xFF;
            }else           //��Ȼ�����ܼ�,��������������
            {
                gs_PassWordCtr.ucPW2ErrCnt=0;
                gs_PassWordCtr.uiDyPW2Out=0;
                return 0x02;
            }

        }else if(buff[0]==0x04)         //04���������
        {
            if(gs_PassWordCtr.ucSt04==BSST) //04����������жϣ�����ֱ�ӷ��ش���
            {
                return 0xFF;
            }else           //��Ȼ�����ܼ�,��������������
            {
                gs_PassWordCtr.ucPW4ErrCnt=0;
                gs_PassWordCtr.uiDyPW4Out=0;
                return 0x04;
            }
        }
    }
    else                                            //����������
    {
       // if(!(gui_SystemState & flgStSys_Program))   //��̼�û�а���ֱ�ӷ���
       // {
       //     return 0xFF;
       // }
        //���ȶ�ȡ��������

//        BE_ReadP(EEP_BSCOUNT,&ucBsCnt,1);               //��������
//        if(buff[0] == 0x02)                         //02���������
//        {
//            if(gs_PassWordCtr.ucSt02!=BSST)
//            {
//                gs_PassWordCtr.ucPW2ErrCnt++;                   //�����������
//                if(gs_PassWordCtr.ucPW2ErrCnt>=ucBsCnt)         //�жϵ��˱�������
//                {
//                    gs_PassWordCtr.ucSt02=BSST;                 //����
//                    BE_ReadP(EEP_BSTIME,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x02);   //д�����ʱ��
//                    //д�����ʱ��    
//                    BE_WriteP(EEP_PW2BSTM,(uint8*)&gs_PassWordCtr.uiDyPW2Out,0x02);
//                }
//            }
//        }
//        else if(buff[0] == 0x04)
//        {
//            if(gs_PassWordCtr.ucSt04!=BSST)
//            {
//                gs_PassWordCtr.ucPW4ErrCnt++;                   //�����������
//                if(gs_PassWordCtr.ucPW4ErrCnt>=ucBsCnt)         //�жϵ��˱�������
//                {
//                    gs_PassWordCtr.ucSt04=BSST;                 //����
//                    BE_ReadP(EEP_BSTIME,(uint8*)&gs_PassWordCtr.uiDyPW4Out,0x02);   //д�����ʱ��
//                    //д�����ʱ��    
//                    BE_WriteP(EEP_PW4BSTM,(uint8*)&gs_PassWordCtr.uiDyPW4Out,0x02);
//                }
//            }
//        }
        return 0xFF;                                //�������벻��ȷ
    }
    return 0xFF;
}
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
uint8 Judge645Addr(S_FRAMEINFO* sFrm)
{
    uint8 i;
    uint8 flag;
    flag=0;
    BE_ReadP(EEP_COMADD,guc_MeteAddr, 6);           //��ȡ���ַ,�������ﲻ�ж�,�ظ���ʱ��Ҳ��Ҫ
    if(ApiBufCmp(sFrm->ucbuf+1, guc_MeteAddr, 6) != CMP_EQU)
    {
        //������ͨ��ַ���ж��Ƿ���ȫ99
        for(i = 1; i <= 6; i++)
        {
            if(sFrm->ucbuf[i] != 0x99)
            {
                break;
            }
        }

        if(i>=6)
        {
            sFrm->ucAtb = Const_Addr_Broadcast;         //�㲥��ַ
            sFrm->ucReply = 0;                          //����Ҫ�ظ�
            return Ret_OK;
        }

        //�ж��Ƿ���λ��ַ
        for(i = 12; i >0 ; i --)
        {//�ж��Ƿ�Ϊ���ܱ��ַ������λ���
            if(flag==1)     //�Ѿ�
            {
                if((i - 1)& 0x01)
                {
                    if((sFrm->ucbuf[(i+1)>>1] & 0xF0) != (guc_MeteAddr[(i - 1)>>1] & 0xF0))
                    {
                        break;
                    }
                }else
                {
                    if((sFrm->ucbuf[(i+1)>>1 ] & 0x0F) != (guc_MeteAddr[(i - 1)>>1] & 0x0F))
                    {
                        break;
                    }
                }
            }else
            {
                if((i - 1)& 0x01)
                {
                    if((sFrm->ucbuf[(i+1)>>1] & 0xF0) != 0xA0)
                    {
                        if((sFrm->ucbuf[(i+1)>>1] & 0xF0) == (guc_MeteAddr[(i - 1)>>1] & 0xF0))
                        {
                            flag=1;
                        }else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if((sFrm->ucbuf[(i+1)>>1 ] & 0x0F) != 0x0A)
                    {
                       if((sFrm->ucbuf[(i+1)>>1 ] & 0x0F) == (guc_MeteAddr[(i - 1)>>1] & 0x0F))
                       {
                           flag=1;
                       }else
                       {
                           break;
                       }
                    }
                }
            }
        }

        if(i > 0)
        {//û���ж����˳�����Ϊ�Ǵ���ı��
            sFrm->ucAtb = Const_Addr_Err;           //���е����˵�����ַ����
            return Ret_Err;
        }else
        {//������Ϊ����λ��Ż������ܱ��
            sFrm->ucAtb = Const_Addr_Any;               //���ܵ�ַ
        }
    }else
    {
        sFrm->ucAtb = Const_Addr_Normal;                //������ַ
    }
    return Ret_OK;
}
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
uint8 Encode645Frame(S_COM* psCom, S_FRAMEINFO* sFrm)
{
        psCom->ucBuf[0] = 0x68;                                         //��д֡ͷ
        psCom->ucBuf[7] = 0x68;                                         //��д֡ͷ
    
        //BE_ReadP(EEP_COMADD,psCom->ucBuf + 1, 6);           //��ȡ���ַ
    
        MemCpy(psCom->ucBuf + 1,guc_MeteAddr,6);                        //��д��ַ��֡����ȥ
    
        if(sFrm->ucErr.word == 0)                                            //����Ӧ��
        {
            psCom->ucBuf[9] = sFrm->ucLen;                              //��д�����򳤶�
            if(guc_DLT1997 == 0x55)
              {
                  if(sFrm->ucCmd == 0x01)    //97��Լ��
                  { 
                      psCom->ucBuf[9] += 2;                                   //�������ݱ�ʶ�ĳ���
                      MemCpy(XDATA_RAMZONE, (uint8*)sFrm->ucbuf, sFrm->ucLen);    //����������
                      MemCpy(psCom->ucBuf+10,sFrm->uiID.byte,2);              //���ݱ�ʶ
                      MemCpy(psCom->ucBuf + 12, XDATA_RAMZONE, sFrm->ucLen);    //����������                
                  }
                  else if(sFrm->ucCmd == 0x04)    //97��Լд
                  { 
                      MemCpy(psCom->ucBuf + 8, (uint8*)sFrm->ucbuf, sFrm->ucLen);    //����������
                  }
                  guc_DLT1997 = 0x00;
              }
    
            else
            {
                if(sFrm->ucCmd == 0x11)                                     //����Ƕ����ݵĻ�
                {
                    psCom->ucBuf[9] += 4;                                   //�������ݱ�ʶ�ĳ���
                    MemCpy(psCom->ucBuf+10,sFrm->uiID.byte,4);              //���ݱ�ʶ
                    MemCpy(psCom->ucBuf + 14, (uint8*)sFrm->ucbuf, sFrm->ucLen);    //����������
                }
                else
                {                                                           //����������
                    MemCpy(psCom->ucBuf + 10, (uint8*)sFrm->ucbuf, sFrm->ucLen);
                }
            }
            sFrm->ucCmd += 0x80;                                        //�����ּ�0x80
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
            /*if(sFrm->ucCmd==0xC3)                       //Esam ����
            {
                psCom->ucBuf[8] = sFrm->ucCmd;              //��д������
                psCom->ucBuf[9] = 0x02;                     //��д�����򳤶�
    
                psCom->ucBuf[10] = sFrm->ucErr.byte[0] + 0x33;      //��д������ + 0x33
                psCom->ucBuf[11] = sFrm->ucErr.byte[1] + 0x33;      //��д������ + 0x33
    
                psCom->ucBuf[12] = DoSum(psCom->ucBuf, 12); //����У���
                psCom->ucBuf[13] = 0x16;                    //��д֡β
                psCom->ucLen = 14;                          //�ܹ�Ҫ���͵��ֽ���                        
            }else*/
            {
                psCom->ucBuf[8] = sFrm->ucCmd;              //��д������
                psCom->ucBuf[9] = 0x01;                     //��д�����򳤶�
                psCom->ucBuf[10] = sFrm->ucErr.byte[0] + 0x33;      //��д������ + 0x33
                psCom->ucBuf[11] = DoSum(psCom->ucBuf, 11); //����У���
                psCom->ucBuf[12] = 0x16;                    //��д֡β
                psCom->ucLen = 13;                          //�ܹ�Ҫ���͵��ֽ���
            }
        }
        return Ret_OK;

}
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


