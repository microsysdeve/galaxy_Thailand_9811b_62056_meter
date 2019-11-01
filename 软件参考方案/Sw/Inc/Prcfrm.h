#ifndef _CM_PRCFRM_H_
#define _CM_PRCFRM_H_

#ifndef CM_PRCFRM_EXT
#define CM_PRCFRM_EXT extern
#endif

#define FactorMd            0x55

#define Ret_OK              0x00        //��ȷ
#define Ret_Err             0xff        //����

#define LeadCharNum         0x10        //ǰ��������
#define FrmHeadLen          0x08        //֡ͷ����
#define MinFrmLen           0x0C        //��С֡����
#define PosDataLen          0x09        //������������֡����λ��
#define Max645FrmLen        0x70        //645֡��󳤶�
#define LeadChar62056Num    0x30        //ǰ��������
#define Min62056FrmLen      0x05        //��С֡����

#define  Prtl_645           0xAA
#define  Prtl_1107          0x00


enum
{//���ַ����
    Const_Addr_Broadcast = 0,       //�㲥��ַ
    Const_Addr_Any,                 //���ܱ��ַ
    Const_Addr_Normal,              //��ͨƥ����ַ
    Const_Addr_Err                  //������ַ
};

/*******************************************************************************
**����������״̬�ֵ�λ����,S_FRAMEINFO��
*******************************************************************************/
#define Const_Atb_Addr (0x01+0x02)  //��ַ��Ϣ,��Ӧ�����enum������
#define Const_Atb_Cmd_Err   0x04    //�����ִ���
#define Const_Atb_Data_Err  0x08    //����������
#define Const_Atb_ID_Err    0x10    //���ݱ�ʶ����
#define Const_Atb_Pswd_Err  0x20    //�������
#define Const_Atb_DataJC    0x40    //�Ƿ������ݼ���
#define Const_Atb_ShowData  0x80    //�Ƿ�����ʾ����


/*******************************************************************************
**�����Ǵ�����Ϣ�ֵ�λ����,S_FRAMEINFO��
*******************************************************************************/
#define ComErrBit_Other     BIT0    //��������
#define ComErrBit_Nodata    BIT1    //����������
#define ComErrBit_ErrPw     BIT2    //�����δ��Ȩ
#define ComErrBit_ChBod     BIT3    //ͨѶ���ʲ��ܸ���
#define ComErrBit_YearQ     BIT4    //��ʱ������
#define ComErrBit_TimeD     BIT5    //��ʱ������
#define ComErrBit_Fee       BIT6    //��������

typedef struct s_frameinfo
{
    uint8   ucPort;                 //ͨѶ��
    uint8   ucCmd;                  //��Լ������
    uint8   ucLen;                  //�շ����ݵĳ���
    uint8   ucLevel;                //Ȩ�޵ȼ�
    uint8   ucReply;                //�Ƿ���Ҫ�ظ�
    uint8  ucErr;                  //����״̬��
    uint8   ucAtb;                  //��������,������ַ��Ϣ,֡�б�״̬
    Word32  uiID;                   //����ID
    Word32  uiUserCode;             //�����ߴ���
    uint8   *ucbuf;                 //���յ��������׵�ַָ��
    void*   pvExt;                  //��չ��,�������κ�����,�����ṹ��,�ɳ�Ա����ucPrtcl����
}S_FRAMEINFO;

typedef struct s_cmdproc
{
    uint8   ucCmd;                  //��Լ������
    uint8   (*ProcFun)(S_FRAMEINFO*);//������
}S_CMDPROC;

extern const S_CMDPROC code gs_CmdProc[];//�����봦��

CM_PRCFRM_EXT uint8 guc_MeteAddr[6];
//CM_PRCFRM_EXT uint8  guc_PrtlTpye;
CM_PRCFRM_EXT uint8 guc_FactoryType;
CM_PRCFRM_EXT uint8 guc_DyProDmOut;
/*******************************************************************************
**�����Ǻ�������
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


