#define CM_PRCFRM_EXT
#include "Include.h"
uint8 Judge62056Frm(S_COM* psCom) ;
uint8 DoNothing(S_FRAMEINFO *s_FrmInfo)
{
    return s_FrmInfo->ucAtb;
}
/*==============================================================================
命令与对应的函数处理
命令字， 属性， 处理函数(在另外一个文件中定义的)
==============================================================================*/
/*const S_CMDPROC code gs_CmdProc[] =
{
   //============ {0x11,RWData},                  //读数据
//  {0x13,ReadMeterAddr},           //读通讯地址
  //====================================  {0x01,FactoryRD},               //厂内读
//opt     {0x02,FactoryWR},               //厂内写
 {0x11,NULL}, 
};
*/

const ComFPro code gs_ComProc[]=
{
    JbComHd,            //帧头
    JbMode,             //判断模式，读，编程，厂家信息
    ContinueRead,       //继续读取
    PrRdWr,             //编程读写模式
};

const uint8 code ComProc_Len=dim(gs_ComProc);	
/*=========================================================================================\n
* @function_name: BD_ProcFrame
* @function_file: Prcfrm.c
* @描述:
*
*
* @参数:
* @param:ComProcCtr
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
extern const ComFPro code gs_ComProc[];
 volatile uint8 iResult;;
uint8 BD_ProcFrame(S_COM *ComProcCtr)
{
   
//    S_FRAMEINFO s_FrmInfo;                              //开辟临时缓存来处理信息
    //判断是1107规约的还是645规约的
//    s_FrmInfo.ucPort=ComProcCtr->ucPort;

//    if(Judge645Frm(ComProcCtr, &s_FrmInfo) == Ret_Err)  //判断645帧是否是合法帧
    {
        //判断是否是62056-21规约
        //首先把数据区中最高位的校验位去掉
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
          //这里增加帧判断，
 
            if(Judge62056Frm(ComProcCtr) == Ret_Err)  //判断62056帧是否是合法帧
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
                guc_ShowStCom = 4;           //显示3s
                OpenGJLed();
            }
        }
        //初始化成7位数据位1位校验位
//      guc_PrtlTpye=Prtl_1107;
        if(ComProcCtr->ucPort==ComIndex_Uart4)
        {
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart4(_bps300_);//, 0);        // 初始化模拟串口
            }
            else
            {
                Init_Uart4(_bps300_);// Init_Uart4(_bps2400_);//,  0);        // 初始化模拟串口
            }
        }
        else
        {
            if((gs_PtlCrt.uc_ComStep==Com_HD&&guc_BodeDely==0)
               ||(gs_PtlCrt.uc_ComStep==Com_BpsCk))
            {
                Init_Uart2(_bps300_);//, ,0);        //初始化红外
            }
            else
            {
                Init_Uart2(_bps300_);//,, 0);        //初始化红外
            }
        }

        ComBom_StartSend(ComProcCtr->ucPort);
        return Ret_OK;                              //非法帧
    }
//  else
//  {
//      if(Decode645Frame(&s_FrmInfo) == Ret_Err)       //解析645帧
//      {
//          return Ret_Err;
//      }
//
//      if(s_FrmInfo.ucErr == 0)
//      {
//          for(i = 0; i < sizeof(gs_CmdProc) / sizeof(S_CMDPROC); i++)
//          {
//              if(gs_CmdProc[i].ucCmd == s_FrmInfo.ucCmd)                  //查找规约命令字
//              {                                                           //执行相应函数
//                  if(Ret_Err == gs_CmdProc[i].ProcFun(&s_FrmInfo))
//                  {
//                      return Ret_Err;
//                  }
//                  break;
//              }
//          }
//          if(i >= sizeof(gs_CmdProc) / sizeof(S_CMDPROC))
//          {
//              return Ret_Err;                                     //找不到命令字就直接返回错误
//          }
//      }
//
//      if(s_FrmInfo.ucReply != 0)                                  //如果需要回复
//      {
//          if(Encode645Frame(ComProcCtr, &s_FrmInfo) == Ret_OK)    //帧的打包
//          {
//              guc_PrtlTpye=Prtl_645;
//              //初始化成8位数据位1位校验位
//
//              if(ComProcCtr->ucPort==ComIndex_Uart1)
//              {
//                  Init_Uart4(0,1);        //初始化485
//              }
//              else
//              {
//                  Init_Uart2(0,1);        //初始化红外
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
* @描述: 移除62056-21的校验位
* 
* @param: ComProcCtr 
* @作者: lwb (2014/3/18)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
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
* @描述: 判断645帧是否是合法的帧
*
*
* @参数:
* @param:psCom  通讯串口
* @param:sFrm
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 Judge645Frm(S_COM* psCom, S_FRAMEINFO* sFrm)
{
    for(uint8 i = 0; i < LeadCharNum; i++)
    {
        if(psCom->ucLen < (MinFrmLen + i))          //收到的数据至少需要满足最小帧长度
        {
            return Ret_Err;
        }
                                                    //判断是否是有效帧
        else if(Ret_OK == IsValidFrame(psCom->ucBuf+i,psCom->ucLen - i))
        {                                           //拷贝数据到临时缓存

            //判断是否数据长度正确
            //MemCpy(sFrm->ucbuf, psCom->ucBuf + i, psCom->ucLen - i);
            sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK;                          //返回有效帧
        }
    }
    return Ret_Err;                                     //非有效帧
}
/*=========================================================================================\n
* @function_name: Judge62056Frm
* @function_file: Prcfrm.c
* @描述: 判断是否是62056规约
* 
* @param: psCom 
* @param: sFrm 
* 
* @return: uint8 
* @作者: lwb (2014/3/26)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 Judge62056Frm(S_COM* psCom)
{
    for(uint8 i = 0; i < LeadCharNum; i++)
    {
        if(psCom->ucLen < (Min62056FrmLen + i))          //收到的数据至少需要满足最小帧长度
        {
         	debug_break(_debug_errno_62056_frame_CrcFAIL1_);
            return Ret_Err;
        }
                                                    //判断是否是有效帧
        else if(Ret_OK == IsValid62056Frame(psCom->ucBuf+i,psCom->ucLen - i))
        {                                           //拷贝数据到临时缓存

            //判断是否数据长度正确
            MemCpy(psCom->ucBuf, psCom->ucBuf + i, psCom->ucLen - i);
//          sFrm->ucbuf=(psCom->ucBuf + i);
            return Ret_OK;                          //返回有效帧
        }
    }
   	debug_break( _debug_errno_62056_frame_CrcFAIL2_);
    return Ret_Err;                                     //非有效帧
}

/*=========================================================================================\n
* @function_name: IsValidFrame
* @function_file: Prcfrm.c
* @描述: 合法帧判断
*
*
* @参数:
* @param:pucBuf
* @param:ucFrmLen
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
uint8 IsValidFrame(uint8* pucBuf, uint8 ucFrmLen)
{
    uint8 ucSum;

    if((pucBuf[0]!= 0x68) || (pucBuf[7] != 0x68))   //帧头0x68判断
    {
        return Ret_Err;
    }

    uint8 ucLen = pucBuf[PosDataLen];
    if(ucFrmLen < (MinFrmLen + ucLen))              //收到的完整帧与实际长度比较
    {
        return Ret_Err;
    }

    ucSum = DoSum(pucBuf, ucLen + MinFrmLen - 2);   //计算校验和
    if(pucBuf[ucLen + MinFrmLen - 2] != ucSum)
    {                                               //校验和不对
        return Ret_Err;
    }

    if(pucBuf[ucLen + MinFrmLen - 1] != 0x16)       //判断帧尾是否为0x16
    {
        return Ret_Err;
    }

    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: IsValid62056Frame
* @function_file: Prcfrm.c
* @描述: 判断是否是62056有效帧头
* 
* @param: pucBuf 
* @param: ucFrmLen 
* 
* @return: uint8 
* @作者: lwb (2014/3/26)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
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
* @描述: 计算校验和
*
*
* @参数:
* @param:pucBuf
* @param:ucLen
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
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
* @描述: 解析645帧
*
*
* @参数:
* @param:sFrm
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
#ifdef _del
uint8 Decode645Frame(S_FRAMEINFO* sFrm)
{
    sFrm->ucReply = 1;                              //默认是需要回复的
    sFrm->ucErr = 0;                                //默认没有错误
    sFrm->uiID.lword = 0xFFFFFFFF;                  //假设默认的ID为全F

    if(sFrm->ucbuf[9] > Max645FrmLen)               //防止下面减0x33过程中将非缓存中数据改写
    {
        sFrm->ucReply = 0;                          //不需要回复
        return Ret_Err;
    }

    if(Judge645Addr(sFrm) == Ret_Err)
    {
        sFrm->ucAtb = Const_Addr_Err;               //表地址错误
        sFrm->ucReply = 0;                          //不需要回复
        return Ret_Err;
    }

    UnDo33(sFrm->ucbuf + 10, sFrm->ucbuf[9]);       //数据区减0x33

    sFrm->ucCmd = sFrm->ucbuf[8];                   //控制字
    sFrm->ucLen = sFrm->ucbuf[9];                   //数据区长度长度

    if((sFrm->ucCmd == 0x11)||(sFrm->ucCmd == 0x14))
    {                                               //如果为读写的话
        sFrm->uiID.byte[0] = sFrm->ucbuf[10];       //数据标识
        sFrm->uiID.byte[1] = sFrm->ucbuf[11];
        sFrm->uiID.byte[2] = sFrm->ucbuf[12];
        sFrm->uiID.byte[3] = sFrm->ucbuf[13];
        if(sFrm->ucCmd == 0x14)                     //如果是写数据的话
        {
//          if(sFrm->ucAtb!=Const_Addr_Normal)      //如果设置不是普通地址，则返回错误
//          {
//              sFrm->ucErr = ComErrBit_Other;
//              sFrm->ucLen = 1;
//              return Ret_OK;
//          }
//
//
//          if(sFrm->ucLen < 12)                    //如果长度没有12的话，就是错误的帧
//          {
//              return Ret_Err;
//          }
//                                                  //操作者代码
//          sFrm->uiUserCode.byte[3] = sFrm->ucbuf[18];
//          sFrm->uiUserCode.byte[2] = sFrm->ucbuf[19];
//          sFrm->uiUserCode.byte[1] = sFrm->ucbuf[20];
//          sFrm->uiUserCode.byte[0] = sFrm->ucbuf[21];
//
//          if(guc_FactoryType == 0)                            //厂内状态没开的话需要判断密码
//          {
//              sFrm->ucLevel = JudgePassword(sFrm->ucbuf + 14);
//              if(sFrm->ucLevel == 0xFF)                       //判断权限
//              {
                    sFrm->ucAtb = Const_Atb_Pswd_Err;
                    sFrm->ucErr = ComErrBit_ErrPw;              //密码错误
                    sFrm->ucLen = 1;
                    return Ret_OK;
//              }
//          }
//          else
//          {
//                                                              //厂内状态,数据指针指向未处理数据
//              sFrm->ucbuf+=22;                                //数据指针指向未处理数据
//              return Ret_OK;
//          }
//                                                              //如果权限小于4且不在厂内状态,需要判断编程键
//          if(((sFrm->ucLevel <= 4) && (gui_SystemState & flgStSys_Program))
//             || (sFrm->ucLevel == 0x98)                       //98级,99级另外处理
//             || (sFrm->ucLevel == 0x99))
//          {                                       //拷贝真正有用的数据
//              //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 22, sFrm->ucLen - 12);
//              sFrm->ucbuf+=22;                    //数据指针指向未处理数据
//          }
//          else                                    //编程键没有按下
//          {
//              sFrm->ucAtb = Const_Atb_Pswd_Err;   //密码错误
//              sFrm->ucErr = ComErrBit_ErrPw;
//              sFrm->ucLen = 1;
//              return Ret_OK;
//          }
        }
        else                                        //否则为读数据
        {
            if(sFrm->ucLen < 4)                     //如果长度没有4的话，就是错误的帧
            {
                sFrm->ucErr = ComErrBit_Other;
                return Ret_Err;
            }
                                                    //拷贝数据
            //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 14, sFrm->ucLen - 4);
            sFrm->ucbuf+=14;                        //数据指针指向未处理数据
        }
    }
    else                                            //既不是读也不是写
    {                                               //拷贝数据
        //MemCpy(sFrm->ucbuf, sFrm->ucbuf + 10, sFrm->ucLen);
        sFrm->ucbuf+=10;                            //CMD命令字不是0X11和0X14,后续处理
    }

    return Ret_OK;                                  //返回解析正确
}
#endif
/*=========================================================================================\n
* @function_name: JudgePassword
* @function_file: Prcfrm.c
* @描述: 判断密码是否正确
*
*
* @参数:
* @param:buff
*
* @返回:
* @return: uint8 密码等级，返回0xFF代表密码错误
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
//uint8 JudgePassword(uint8* buff)
//{
//    uint8 PassWord[3];
//    if((buff[0] == 0x98) || (buff[0] == 0x99))      //如果是98、99级，那么不需要判断密码直接返回权限
//    {
//        return buff[0];
//    }
//
//    if((buff[0] != 0x02) && (buff[0] != 0x04))      //如果密码等级不等于02或者04则错误
//    {
//        return 0xFF;
//    }
                                                    //读取相应等级的密码
//    if(BE_ReadP(buff[0] * 3 + EEP_645PASSWD1, PassWord,3))
//    {
//        return 0xFF;
//    }

//   if((PassWord[0] == buff[1]) && (PassWord[1] == buff[2]) && (PassWord[2] == buff[3]))
//  {
       /*if((gs_PsLock.PsLockMask & 0x03) == 0)      //如果没有密码锁
       {
            if(buff[0] == 0x02)
            {
                gs_PsLock.PassW02 = 0;              //错误计时清零
                gs_PsLock.cnt &= ~0x0F;             //错误次数清零
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
                gs_PsLock.PassW02 = 0;              //错误计时清零
                gs_PsLock.cnt &= ~0x0F;             //错误次数清零
            }
            else
            {
                gs_PsLock.PassW04 = 0;
                gs_PsLock.cnt &= ~0xF0;
            }
            return buff[0];
        }*/
//  }
//    else                                            //如果密码错误
//  {
//      if(!(gui_SystemState & flgStSys_Program))   //编程键没有按就直接返回
//      {
//          return 0xFF;
//      }
//
//      if(buff[0] == 0x02)
//      {
//          gs_PsLock.cnt = 0xF0 | (0x0F & (gs_PsLock.cnt + 1));
//          if((gs_PsLock.cnt & 0x0F) >= 3)
//          {
//              gul_ShowState |= flgShowSt_Lock;    //显示密码锁
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
//              gul_ShowState |= flgShowSt_Lock;    //显示密码锁
//              gs_PsLock.PassW04 = TIME_PSLOCK;
//              gs_PsLock.cnt &= ~0xF0;
//              gs_PsLock.cnt |= 0x30;
//              gs_PsLock.PsLockMask |= 0x02;
//          }
//      }
//      return 0xFF;                                //返回密码不正确
//    }
//}
/*=========================================================================================\n
* @function_name: Judge645Addr
* @function_file: Prcfrm.c
* @描述: 判断645地址是否正确
*
*
* @参数:
* @param:sFrm
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
#ifdef DEL
uint8 Judge645Addr(S_FRAMEINFO* sFrm)
{
    uint8 i;
    BE_ReadP(EEP_COMADD,guc_MeteAddr, 6);           //读取表地址,就算这里不判断,回复的时候也需要
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
            sFrm->ucAtb = Const_Addr_Any;               //万能地址
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
            sFrm->ucAtb = Const_Addr_Any;               //万能地址
            sFrm->ucReply = 0;                          //不需要回复
            return Ret_OK;
        }

        for(i = 1; i <= 6; i++)
        {
            if(sFrm->ucbuf[i] != guc_MeteAddr[i - 1])
            {
                sFrm->ucAtb = Const_Addr_Err;           //运行到这里，说明表地址错误
                return Ret_Err;
            }
        }
    }
    else
    {
        sFrm->ucAtb = Const_Addr_Normal;                //正常地址
    }
    return Ret_OK;
}
#endif
/*=========================================================================================\n
* @function_name: Encode645Frame
* @function_file: Prcfrm.c
* @描述: 645帧打包
*
*
* @参数:
* @param:psCom
* @param:sFrm
*
* @返回:
* @return: uint8
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
#ifdef DEL
uint8 Encode645Frame(S_COM* psCom, S_FRAMEINFO* sFrm)
{
    psCom->ucBuf[0] = 0x68;                                         //填写帧头
    psCom->ucBuf[7] = 0x68;                                         //填写帧头

    MemCpy(psCom->ucBuf + 1,guc_MeteAddr,6);                        //填写地址到帧里面去

    if(sFrm->ucErr == 0)                                            //正常应答
    {
        psCom->ucBuf[9] = sFrm->ucLen;                              //填写数据域长度
        if(sFrm->ucCmd == 0x11 || sFrm->ucCmd == 0x03
#ifdef SQSDPRLOG
           ||sFrm->ucCmd == 0x31
           ||sFrm->ucCmd == 0x32
           ||sFrm->ucCmd == 0x12
#endif
           )                                     //如果是读数据的话
        {
            psCom->ucBuf[9] += 4;                                   //加上数据标识的长度
            MemCpy(psCom->ucBuf+10,sFrm->uiID.byte,4);              //数据标识
            MemCpy(psCom->ucBuf + 14, (uint8*)sFrm->ucbuf, sFrm->ucLen);    //拷贝数据区
        }
        else
        {                                                           //拷贝数据区
            MemCpy(psCom->ucBuf + 10, (uint8*)sFrm->ucbuf, sFrm->ucLen);
        }

        sFrm->ucCmd |= 0x80;                                        //控制字加0x80
        psCom->ucBuf[8] = sFrm->ucCmd;                              //填写控制码

        Do33(psCom->ucBuf + 10, psCom->ucBuf[9]);                   //数据区加0x33操作
        psCom->ucLen = MinFrmLen + psCom->ucBuf[9];                 //数据帧的长度
                                                                    //计算校验和
        psCom->ucBuf[psCom->ucLen - 2] = DoSum(psCom->ucBuf, psCom->ucLen - 2);
        psCom->ucBuf[psCom->ucLen - 1] = 0x16;                      //填写帧尾
    }
    else
    {

        sFrm->ucCmd += 0xC0;                        //控制字加0xC0
        psCom->ucBuf[8] = sFrm->ucCmd;              //填写控制码
        psCom->ucBuf[9] = 0x01;                     //填写数据域长度
        psCom->ucBuf[10] = sFrm->ucErr + 0x33;      //填写错误码 + 0x33
        psCom->ucBuf[11] = DoSum(psCom->ucBuf, 11); //计算校验和
        psCom->ucBuf[12] = 0x16;                    //填写帧尾
        psCom->ucLen = 13;                          //总共要发送的字节数

    }
    
    return Ret_OK;
}

#endif
/*=========================================================================================\n
* @function_name: UnDo33
* @function_file: Prcfrm.c
* @描述: 数据区减0x33的操作
*
*
* @参数:
* @param:pucBuf
* @param:ucLen
* @返回:
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
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
* @描述: 数据区加0x33的操作
*
*
* @参数:
* @param:pucBuf
* @param:ucLen
* @返回:
* @作者:   lwb (2012-02-28)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void Do33(uint8* pucBuf, uint8 ucLen)
{
    for(uint8 i = 0; i < ucLen; i++)
    {
        pucBuf[i] += 0x33;
    }
}

