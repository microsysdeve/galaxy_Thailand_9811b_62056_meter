
#ifndef __LCDSHOW_H__
#define __LCDSHOW_H__

#ifndef LCDSHOWEXT
    #define LCDSHOWEXT extern
#else
    #define LCDSHOWSELF
#endif



#define Const_MaxDispTabNum (sizeof(gCs_DispTab)/sizeof(S_DISPCONT))


LCDSHOWEXT uint8 guc_ShowStCom;
LCDSHOWEXT uint8 guc_ShowEnergyFlag;

////////////////////////////////////////////////////////////
LCDSHOWEXT uint32   gul_ShowState;      // ��ʾϵͳ״̬

#define flgShowSt_M         0x0001     // 
#define flgShowSt_I         0x0002     // 
#define flgShowSt_D         0x0004     // 
#define flgShowSt_T         0x0008     // 
#define flgShowSt_S5        0x0010     // 
#define flgShowSt_S6        0x0020     // 
#define flgShowSt_S7        0x0040     // 
#define flgShowSt_S8        0x0080     // 
#define flgShowSt_S9        0x0100     // 
#define flgShowSt_S10       0x0200     // 
#define flgShowSt_S11       0x0400     //
#define flgShowSt_Bat       0x0800     // 
#define flgShowSt_Total     0x1000     // 

//////////////////////////////////////////////////////////


enum
{
    Const_NoNeedRefresh,    //����Ҫ��������ˢ��
    Const_NeedRefresh,      //��Ҫ��������ˢ��
};

enum
{
    Const_DispMode_LX=0,        //����
    Const_DispMode_JX,          //����
    Const_DispMode_TX,          //ͣ��
    Const_DispMode_Full,        //ȫ����ʾ
    Const_DispMode_IRDA,        //����ͨѶ��ʾ
    Const_DispMode_LXGB,        //�Զ�����һ�ֽ�����ر���ʾ״̬
    Const_DispMode_TXGB,        //ͣ��һ�ֽ�����ر���ʾ״̬
    Const_DispMode_PwOff,       //ͣ��N���Ժ��״̬
    Const_DispModeOff,          //�賿x�㵽�ڶ���y��ر�lcd��ʾ��״̬
    Const_DispMode_AdvSysClr,
    Const_DispMode_AC,          //�Զ�У��������ʾ
    Const_DispMode_RMTLX,       //ң�������Լ���������������ʾ
    Const_DispMode_Err,         //������ʾģʽ
};

enum
{
    Const_Disp_RAM = 0,
    Const_Disp_E2,
};

/*ucSpecialMode�Ķ���*/
#define Const_AdvSysClr     0x80    //
#define Const_AdvAC         0x40    //�Զ�У��

#define Cosnt_RefreshTime   0x01    //ͣ����ʾʱ����ʾ������Ҫ������Ҫˢ��,�����Ϊʱ��
#define Const_RefreshAll    0x02    //ͣ��ʱ������ʾ������

typedef struct s_DispStt
{
    uint8   ucMode;         //��ʾģʽ,����,����,ͣ�Ե�
    uint8   ucTmr;          //��ʾ�Ķ�ʱʱ�䣬��ر���ʾʱ��
    uint8   ucPwrOffRefresh;//ͣ��ʱ��ʾ�Ƿ���Ҫˢ��
    uint16  uiIndex;        //��ǰ��ʾ��ı��е����,���������Ի��Ǽ��Ե�
    uint32  ulPwrOffTmr;    //ͣ������ʾ�Ķ�ʱʱ��
}S_DISPSTT;

#define ConstDayMin (1*24*60) //1day=24hour=1*24*60min

/*
*�������������ڵ���������������������,�Ժ������򲻻�仯,ʱ��ĵ�λ����,������Ҫ
*��ʱ��E2�и�������
*/
typedef struct 
{
    uint8 ucLxCnt;          //ѭ������
    uint8 ucLxTm;           //������ʾʱ��
    uint8 ucEnyDoc;         //��ʾ����С��λ��
    uint8 ucPowDoc;         //��ʾ����(���������ʾλ��)
    uint8 ucJxCnt;          //����ѭ����ʾ����
    uint8 uc_ShowErrPst;    //ERR��������ʾλ��
    uint8 ucJxTm;           //�е��¼�����ʾʱ��(����)
    uint8 ucJxPowOffTm;     //ͣ���¼�����ʾʱ��(����)
    uint16 ulPowOffShowTm ; //ͣ����ʾʱ��(����)
    uint8  ucFullShowTm;    //�ϵ�ȫ��ʱ�䣨������
    uint8  ucPowUpBgTm;     //�ϵ米����ʱ��(����)
    uint8  ucIrBgTm;        //���ⴥ��������ʱ��(����)
    uint8  ucKeyBgTm;       //��������������ʱ��(����)
    uint8  ucEsamBgTm;      //ESAM���󱳹���ʱ��(����)
    uint8  ucPowUpLedTm;    //LED�Լ�ʱ��(����)
    uint16 ul_CRC;          //CRC����
}S_DISPCONTENT;

typedef struct 
{
    uint16  uiStr1;         //������ʾ��str������
    uint16  uiUnitPt1;      //��λ��С���������ʾ����
    uint32  ulNum1;         //��ʾnum��������
    uint32  ulNum1Msk;      //num����ʾʱ,�����������ַ���ʾ��Ϣ
}S_LCDDISP;

typedef struct 
{
    uint8   ucPort;                 //Ϊ�˼���ͨѶ
    uint8   ucCmd;                  //��Լ������
    uint8   ucLen;                  //�շ����ݵĳ���
    uint8   ucLevel;                //Ȩ�޵ȼ�
    uint8   ucReply;                //�Ƿ���Ҫ�ظ�
    Word16  ucErr;                  //����״̬��
    uint8   ucAtb;                  //��������,������ַ��Ϣ,֡�б�״̬
    Word32  uiID;                   //����ID
    Word32  uiUserCode;             //�����ߴ���
    uint8   *ucbuf;                 //���յ��������׵�ַָ��
}S_LCDDATEINFO;

LCDSHOWEXT  S_DISPCONTENT gs_DispCont;
LCDSHOWEXT S_DISPSTT   gs_DispStt ;        //״̬ת�����õ��Ľṹ
LCDSHOWEXT S_LCDDISP   gs_LcdDisp ;
//LCDSHOWEXT uint8 guc_IrShowLcdId[5];
//LCDSHOWEXT uint8 guc_ErrEsamMacSwTm;
//LCDSHOWEXT uint8 guc_ErrEsamKetSwTm;
//LCDSHOWEXT uint8 guc_ErrRevPowerSwTm;
//LCDSHOWEXT uint8 guc_ErrRevPowerStatus;
//LCDSHOWEXT uint8 guc_SwErrCode[8];
//LCDSHOWEXT uint8 guc_ErrCodeCnt;
//LCDSHOWEXT uint8 guc_ErrBtnFlag;
//LCDSHOWEXT uint8 guc_ShowErrEndFlag;

LCDSHOWEXT uint32 gul_ShowId;
//LCDSHOWEXT uint8 guc_ErrSwPt;       //������ʾָ��
LCDSHOWEXT uint8 guc_BgCtrl;


#define Const_DispNeedMsk   0x80                        //��Ҫ����
#define Const_DispSigned    0x40                        //�з�������ʾ
#define Const_DisppHEX2BCD  0x20                        //��ҪHEXתBCD��ʾ
#define Const_DispUnitPt    (0x10+0x08+0x04+0x02+0x01)  //���ڲ�С����͵�λ���ű�

typedef struct s_dispcont
{
    uint32  ulShowState;    //ÿ����״̬
    uint8   uiUnitPoint;    //ÿ����С����ͷ���
}S_DISPCONT;

typedef struct s_idtab
{
    uint32 ulInID;
    uint8 uiNumb;
}S_IDTAB;



#ifdef LCDSHOWSELF

const S_IDTAB code gCs_TabConvent[]=
{   
    {0x00000000, 0x01}, //��ǰ����й�������            (N)
    {0x00010000, 0x01}, //��ǰ���й�������              (N)
    {0x00020000, 0x01}, //��ǰ���й�������              (N)

    {0x00000001, 0x02}, //��1������й�������           (N)
    {0x00010001, 0x02}, //��1�����й�������             (N)
    {0x00020001, 0x02}, //��1�·��й�������             (N)

    {0x00000002, 0x03}, //��2������й�������           (N)
    {0x00010002, 0x03}, //��2�����й�������             (N)
    {0x00020002, 0x03}, //��2�·��й�������             (N)
};
const   uint8 code guc_LenOfTabConvent = sizeof(gCs_TabConvent) / sizeof(S_IDTAB);

const   S_IDTAB code gCs_TabConvBL[]=
{
    {0x02010100, 0x0F}, // ��ѹ
    {0x02020100, 0x10}, // ����
    {0x02030000, 0x0}, // �ܹ���
    {0x02030100, 0x0}, // �ܹ���
    {0x02060000, 0x0}, // ��������
    {0x02060100, 0x0}, // ��������
    {0x02800001, 0x10}, // ���ߵ���
    {0x02800008, 0x0}, // ��ص�ѹ
};
const   uint8 code guc_LenOfTabConvBL = sizeof(gCs_TabConvBL) / sizeof(S_IDTAB);

const S_IDTAB code gCs_TabAdd[]=
{
//    {0x03300001, 0x0}, //���ʱ�� ռ��2��
//    {0x03300401, 0x0}, //Уʱʱ�� ռ��2��
    {0x03300D00, 0x09}, //����Ǵ���
    {0x03300E00, 0x0A}, //��β�Ǵ���
    {0x03300D01, 0x0B}, //���һ�ο������ʼʱ�� ����
    {0x03300D02, 0x0C}, //���һ�ο������ʼʱ�� ʱ��
    {0x03300E01, 0x0D}, //���һ�ο���β����ʼʱ�� ����
    {0x03300E02, 0x0E}, //���һ�ο���β����ʼʱ�� ʱ��
};
const uint8 code guc_LenOfTabAdd = sizeof(gCs_TabAdd) / sizeof(S_IDTAB);

const   S_IDTAB code gCs_TabConvCS[]=
{
    {0x04000101, 0x04}, //����
    {0x04000102, 0x05}, //ʱ��
    {0x04000402, 0x06}, //��� ռ��2��
};
const   uint8 code guc_LenOfTabConvCS = sizeof(gCs_TabConvCS) / sizeof(S_IDTAB);
/////////////////////////////////////////////
//����ṹ��������ṹ�����
const S_DISPCONT code gCs_DispTab[]=
{
    { 0x00000000,  0x00,},   //0, ����ʾ

    { 0x00001000,  0x31,}, //1,  ��ǰ����й������� 
    { 0x00000018,  0x01,}, //2,  ��1������й�������
    { 0x00000000,  0x01,}, //3,  ��2������й�������
    { 0x00000020,  0x40,}, //4,  ����
    { 0x00000020,  0x50,}, //5,  ʱ��

    { 0x00000040,  0x00,}, //6, ���
    { 0x00000000,  0x00,}, //7, ����ʾ
    { 0x00000000,  0x00,},   //8, ����ʾ
    { 0x00000100,  0x00,},   //9, ����Ǵ���
    { 0x00000200,  0x00,},   //A, ��β�Ǵ���
    { 0x00000120,  0x40,},   //B, ���һ�ο������ʼʱ�� ����
    { 0x00000120,  0x50,},   //C, ���һ�ο������ʼʱ�� ʱ��
    { 0x00000220,  0x40,},   //D, ���һ�ο���β����ʼʱ�� ����
    { 0x00000220,  0x50,},   //E, ���һ�ο���β����ʼʱ�� ʱ��
    { 0x00000000,  0x43,},   //F, ��ѹ
    { 0x00000000,  0x24,},   //0x10, ����
//    { 0x00000001,  0x22,},   //E, �й�����
//    { 0x00000000,  0x30,},   //F, ��������
//    
//    { 0x00000000,  0x22,},   //0x10, ����
};

#else
extern const   S_IDTAB code gCs_TabConvent[];
extern const   uint8 code guc_LenOfTabConvent;
extern const   S_IDTAB code gCs_TabConvBL[];
extern const   uint8 code guc_LenOfTabConvBL;
extern const   S_IDTAB code gCs_TabConvCS[];
extern const   uint8 code guc_LenOfTabConvCS;
#endif

enum
{
    Const_Ret_OK = 0,
    Const_Ret_Err,
    Const_Ret_Disp_Off,             //�ر���ʾ
    Const_Ret_DispFull,             //ȫ����ʾ
    Const_Ret_DispMode_Err,         //���󱨾�
};

void ShowSysStart(void);
void ShowInitial(void);
void ShowSecondProc(void);
//void ShowDataProc(void);
#define  ShowDataProc()  {}
void ShowNumManage(uint32 ulID, uint8 ucSubNo);
void ShowRefresh(void);
void PowOffShowRefresh(void);
uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);

void ShowKeyManage(void);
void SleepDispInit(void);

uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);

uint8 SleepDisp(void);

#endif