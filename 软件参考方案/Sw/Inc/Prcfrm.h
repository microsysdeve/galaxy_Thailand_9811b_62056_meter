#ifndef _CM_PRCFRM_H_
#define _CM_PRCFRM_H_

#ifndef CM_PRCFRM_EXT
#define CM_PRCFRM_EXT extern
#endif

#define FactorMd            0x55

#define Ret_OK              0x00        //正确
#define Ret_Err             0xff        //错误

#define LeadCharNum         0x10        //前导符个数
#define FrmHeadLen          0x08        //帧头长度
#define MinFrmLen           0x0C        //最小帧长度
#define PosDataLen          0x09        //数据区长度在帧里面位置
#define Max645FrmLen        0x70        //645帧最大长度
#define LeadChar62056Num    0x30        //前导符个数
#define Min62056FrmLen      0x05        //最小帧长度

#define  Prtl_645           0xAA
#define  Prtl_1107          0x00


enum
{//表地址类型
    Const_Addr_Broadcast = 0,       //广播地址
    Const_Addr_Any,                 //万能表地址
    Const_Addr_Normal,              //普通匹配表地址
    Const_Addr_Err                  //错误表地址
};

/*******************************************************************************
**下面是属性状态字的位定义,S_FRAMEINFO中
*******************************************************************************/
#define Const_Atb_Addr (0x01+0x02)  //地址信息,对应上面的enum中类型
#define Const_Atb_Cmd_Err   0x04    //命令字错误
#define Const_Atb_Data_Err  0x08    //数据区错误
#define Const_Atb_ID_Err    0x10    //数据标识错误
#define Const_Atb_Pswd_Err  0x20    //密码错误
#define Const_Atb_DataJC    0x40    //是否是数据集抄
#define Const_Atb_ShowData  0x80    //是否是显示数据


/*******************************************************************************
**下面是错误信息字的位定义,S_FRAMEINFO中
*******************************************************************************/
#define ComErrBit_Other     BIT0    //其他错误
#define ComErrBit_Nodata    BIT1    //无请求数据
#define ComErrBit_ErrPw     BIT2    //密码错，未授权
#define ComErrBit_ChBod     BIT3    //通讯速率不能更改
#define ComErrBit_YearQ     BIT4    //年时区数超
#define ComErrBit_TimeD     BIT5    //日时段数超
#define ComErrBit_Fee       BIT6    //费率数超

typedef struct s_frameinfo
{
    uint8   ucPort;                 //通讯口
    uint8   ucCmd;                  //规约命令字
    uint8   ucLen;                  //收发数据的长度
    uint8   ucLevel;                //权限等级
    uint8   ucReply;                //是否需要回复
    uint8  ucErr;                  //错误状态字
    uint8   ucAtb;                  //数据属性,包括地址信息,帧判别状态
    Word32  uiID;                   //数据ID
    Word32  uiUserCode;             //操作者代码
    uint8   *ucbuf;                 //接收的数据区首地址指针
    void*   pvExt;                  //扩展用,可以是任何类型,包括结构体,由成员变量ucPrtcl决定
}S_FRAMEINFO;

typedef struct s_cmdproc
{
    uint8   ucCmd;                  //规约命令字
    uint8   (*ProcFun)(S_FRAMEINFO*);//处理函数
}S_CMDPROC;

extern const S_CMDPROC code gs_CmdProc[];//命令与处理

CM_PRCFRM_EXT uint8 guc_MeteAddr[6];
//CM_PRCFRM_EXT uint8  guc_PrtlTpye;
CM_PRCFRM_EXT uint8 guc_FactoryType;
CM_PRCFRM_EXT uint8 guc_DyProDmOut;
/*******************************************************************************
**下面是函数申明
*******************************************************************************/
uint8 DoNothing(S_FRAMEINFO *s_FrmInfo);
uint8 BD_ProcFrame(S_COM *ComProcCtr);
uint8 Judge645Frm(S_COM* psCom, S_FRAMEINFO* sFrm);
uint8 IsValidFrame(uint8* pucBuf, uint8 ucFrmLen);
uint8 IsValid62056Frame(uint8* pucBuf, uint8 ucFrmLen);
uint8 Judge62056Frm(S_COM* psCom);
uint8 DoSum(uint8* pucBuf, uint8 ucLen);
uint8 Decode645Frame(S_FRAMEINFO* sFrm);
uint8 Judge645Addr(S_FRAMEINFO* sFrm);
//uint8 JudgePassword(uint8* buff);
void UnDo33(uint8* pucBuf, uint8 ucLen);
void Do33(uint8* pucBuf, uint8 ucLen);
uint8 Encode645Frame(S_COM* psCom, S_FRAMEINFO* sFrm);


#endif


