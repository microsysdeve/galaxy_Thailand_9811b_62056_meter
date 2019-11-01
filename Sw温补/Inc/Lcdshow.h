
#ifndef __LCDSHOW_H__
#define __LCDSHOW_H__

#ifndef LCDSHOWEXT
    #define LCDSHOWEXT extern
#else
    #define LCDSHOWSELF
#endif



#define Const_MaxDispTabNum (sizeof(gCs_DispTab)/sizeof(S_DISPCONT))


#define DEFAULT_CLOCK_NO    68          //Ĭ�ϵ�ʱ����ʾ����ʾ���е�λ��
#define DEFAULT_ENERGY_NO   1           //Ĭ�ϵĵ�ǰ��������ʾ���е�λ��

#define Const_Disp_Neg      0x00        //����
#define Const_Disp_Pos      0x01        //����
LCDSHOWEXT uint8 guc_ShowStCom;
LCDSHOWEXT uint8 guc_ShowEnergyFlag;

LCDSHOWEXT uint32   gul_ShowState;      // ��ʾϵͳ״̬
#define flgShowSt_Fuh       0x0800   // ����
#define flgShowSt_TJ        0x0000   // �ڻ�
//#define flgShowSt_TZ        0x2000000   // ͸֧
//#define flgShowSt_LZ        0x1000000   // ��բ
//#define flgShowSt_QGD       0x800000    // �빺��
//#define flgShowSt_SB        0x400000    // ʧ��
//#define flgShowSt_CG        0x200000    // �ɹ�
//#define flgShowSt_Zhong     0x100000    // ��
//#define flgShowSt_DK        0x80000     // ����
//#define flgShowSt_SJ2       0x20000     // ����2
//#define flgShowSt_SJ1       0x10000     // ����1
//#define flgShowSt_Fk4       0x8000      // ����4
//#define flgShowSt_Fk3       0x4000      // ����3
//#define flgShowSt_Fk2       0x2000      // ����2
//#define flgShowSt_Fk1       0x1000      // ����1
#define flgShowSt_Lock      0x0400      // ���������
#define flgShowSt_PRvs      0x0200      // ���ʷ���
#define flgShowSt_Bat       0x0100      // ���ָʾ
#define flgShowSt_Pgm       0x0080      // ��̼�
//#define flgShowSt_ZB        0x0080      // �ز�
#define flgShowSt_Com       0x0040      // ͨѶָʾ
#define flgShowSt_YQ2       0x0020      // ԲȦ2
#define flgShowSt_YQ1       0x0010      // ԲȦ1
#define flgShowSt_Fee4      0x0008      // ���ķ���
#define flgShowSt_Fee3      0x0004      // ��������
#define flgShowSt_Fee2      0x0002      // �ڶ�����
#define flgShowSt_Fee1      0x0001      // ��һ����

//LCDSHOWEXT  uint32 gul_ShowId;

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
LCDSHOWEXT uint8 guc_IrShowLcdId[5];
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


/*S_DISPCONT��ʾ���Ա�ṹ��Ķ���
*uiInIDΪ���ı��ڲ�ID,��uiInID���Բ���ı�
*ucStr����lcd�����в������ַ�����
*ucAtbΪ����,����:
    bit7: 0������/1����
    bit6: 0��/1�� ������
    bit5: 0��Ҫ/1Ҫ Hex2BCD
    bit4-bit0:���ڲ鵥λС�����ʽ��
*/
#define Const_DispNeedMsk   0x80                        //��Ҫ����
#define Const_DispSigned    0x40                        //�з�������ʾ
#define Const_DisppHEX2BCD  0x20                        //��ҪHEXתBCD��ʾ
#define Const_DispUnitPt    (0x10+0x08+0x04+0x02+0x01)  //���ڲ�С����͵�λ���ű�

typedef struct s_dispcont
{
//  uint32  ulInID;         //�ڲ�ID,��Ϊ0xFFFF��ʾ��Ч��,0xFFFE��ʾȫ��
    uint16  uiStr;          //����lcd�����в������ַ�����
    uint8   ucAtb;          //����
//  uint8   ucExt;          //��չ
//  uint8   ucOffset;       //������չ��Լ����
//  uint8   reserved;       //����
}S_DISPCONT;

typedef struct s_idtab
{
    uint32 ulInID;
    uint8 uiNumb;
}S_IDTAB;

//[��ʾ��]
/*
*����������Ǵ�0��ʼ�ֱ�Ϊ1,2,3,...,����0��Ч
*��code����ʾ��ֵʱ��Ҫ��g_sDispStt.uiIndex�Ļ����ϼ�һ�ſ��Կ���ʵ�ʵ�����
*������E2�е�����Ϊ����0������
*ע��:
    1.�˱����ڲ�����ID����Ҫ����,������������˳������
    2.�������������ĺ���ID��,0xFFFFΪ��Ч����,��Ȼȥ���ݴ���������,0xFFFEΪȫ����ʾ
*/

#ifdef LCDSHOWSELF

const S_IDTAB code gCs_TabConvent[]=
{   
    {0x00000000, 0x01}, //2,  ��ǰ����й�������            (N)
    {0x00000100, 0x02}, //3,  ��ǰ����й�������            (N)
    {0x00000200, 0x03}, //4,  ��ǰ����й�������            (N)
    {0x00000300, 0x04}, //5,  ��ǰ����й�����ƽ            (N)
    {0x00000400, 0x05}, //6,  ��ǰ����й�������            (N)

    {0x00010000, 0x01}, //2,  ��ǰ���й�������              (N)
    {0x00010100, 0x02}, //3,  ��ǰ���й�������              (N)
    {0x00010200, 0x03}, //4,  ��ǰ���й�������              (N)
    {0x00010300, 0x04}, //5,  ��ǰ���й�����ƽ              (N)
    {0x00010400, 0x05}, //6,  ��ǰ���й�������              (N)

    {0x00020000, 0x01}, //2,  ��ǰ���й�������              (N)
    {0x00020100, 0x02}, //3,  ��ǰ���й�������              (N)
    {0x00020200, 0x03}, //4,  ��ǰ���й�������              (N)
    {0x00020300, 0x04}, //5,  ��ǰ���й�����ƽ              (N)
    {0x00020400, 0x05}, //6,  ��ǰ���й�������              (N)

    {0x00000001, 0x06}, //7,  ��1������й�������           (N)
    {0x00000101, 0x07}, //8,  ��1������й�������           (N)
    {0x00000201, 0x08}, //9,  ��1������й�������           (N)
    {0x00000301, 0x09}, //10, ��1������й�����ƽ           (N)
    {0x00000401, 0x0a}, //11, ��1������й�������           (N)

    {0x00010001, 0x06}, //7,  ��1�����й�������             (N)
    {0x00010101, 0x07}, //8,  ��1�����й�������             (N)
    {0x00010201, 0x08}, //9,  ��1�����й�������             (N)
    {0x00010301, 0x09}, //10, ��1�����й�����ƽ             (N)
    {0x00010401, 0x0a}, //11, ��1�����й�������             (N)

    {0x00020001, 0x06}, //7,  ��1�·��й�������             (N)
    {0x00020101, 0x07}, //8,  ��1�·��й�������             (N)
    {0x00020201, 0x08}, //9,  ��1�·��й�������             (N)
    {0x00020301, 0x09}, //10, ��1�·��й�����ƽ             (N)
    {0x00020401, 0x0a}, //11, ��1�·��й�������             (N)

    {0x00000002, 0x0b}, //12, ��2������й�������           (N)
    {0x00000102, 0x0c}, //13, ��2������й�������           (N)
    {0x00000202, 0x0d}, //14, ��2������й�������           (N)
    {0x00000302, 0x0e}, //15, ��2������й�����ƽ           (N)
    {0x00000402, 0x0f}, //16, ��2������й�������           (N)

    {0x00010002, 0x0b}, //12, ��2�����й�������             (N)
    {0x00010102, 0x0c}, //13, ��2�����й�������             (N)
    {0x00010202, 0x0d}, //14, ��2�����й�������             (N)
    {0x00010302, 0x0e}, //15, ��2�����й�����ƽ             (N)
    {0x00010402, 0x0f}, //16, ��2�����й�������             (N)


    {0x00020002, 0x0b}, //12, ��2�·��й�������             (N)
    {0x00020102, 0x0c}, //13, ��2�·��й�������             (N)
    {0x00020202, 0x0d}, //14, ��2�·��й�������             (N)
    {0x00020302, 0x0e}, //15, ��2�·��й�����ƽ             (N)
    {0x00020402, 0x0f}, //16, ��2�·��й�������             (N)

    {0x00000003, 0x10}, //17, ��3������й�������           (N)
    {0x00000103, 0x11}, //18, ��3������й�������           (N)
    {0x00000203, 0x12}, //19, ��3������й�������           (N)
    {0x00000303, 0x13}, //20, ��3������й�����ƽ           (N)
    {0x00000403, 0x14}, //21, ��3������й�������           (N)

    {0x00010003, 0x10}, //17, ��3�����й�������             (N)
    {0x00010103, 0x11}, //18, ��3�����й�������             (N)
    {0x00010203, 0x12}, //19, ��3�����й�������             (N)
    {0x00010303, 0x13}, //20, ��3�����й�����ƽ             (N)
    {0x00010403, 0x14}, //21, ��3�����й�������             (N)

    {0x00020003, 0x10}, //17, ��3�·��й�������             (N)
    {0x00020103, 0x11}, //18, ��3�·��й�������             (N)
    {0x00020203, 0x12}, //19, ��3�·��й�������             (N)
    {0x00020303, 0x13}, //20, ��3�·��й�����ƽ             (N)
    {0x00020403, 0x14}, //21, ��3�·��й�������             (N)

//  {0x000B0000, 0x3D}, //20, ��ǰ���ڵ���                  (N)
//  {0x000B0001, 0x3E}, //21, ��1���ڵ���                   (N)

};
const   uint8 code guc_LenOfTabConvent = sizeof(gCs_TabConvent) / sizeof(S_IDTAB);



const   S_IDTAB code gCs_TabConvCS[]=
{
    {0x04000101, 0x15}, //��������
    {0x04000102, 0x16}, //ʱ��
    {0x04000401, 0x17}, //ͨѶ��ַ ռ��2��
    {0x04000402, 0x19}, //��� ռ��2��
    {0x0400040E, 0x1b}, //�ͻ���� ռ��2��
    {0x04000409, 0x1d}, //����
    {0x04000B01, 0x1e}, //������1
    {0x04000B02, 0x1f}, //������2
    {0x04000B03, 0x20}, //������3

};
const   uint8 code guc_LenOfTabConvCS = sizeof(gCs_TabConvCS) / sizeof(S_IDTAB);
const   S_IDTAB code gCs_TabConvBL[]=
{
    {0x02010100, 0x21}, // ��ѹ
    {0x02020100, 0x22}, // ����
    {0x02030000, 0x23}, // �ܹ���
    {0x02030100, 0x23}, // �ܹ���
    {0x02060000, 0x24}, // ��������
    {0x02060100, 0x24}, // ��������
    {0x02800001, 0x25}, // ���ߵ���
    {0x02800008, 0x26}, // ��ص�ѹ
};
const   uint8 code guc_LenOfTabConvBL = sizeof(gCs_TabConvBL) / sizeof(S_IDTAB);
const S_DISPCONT code gCs_DispTab[]=
{
    { 0x0000,  0x00,},   //0,  ȫ����ʾ

    { 0x0001, 0x43,}, //1,  ��ǰ������                (N)
    { 0x0002, 0x43,}, //2,  ��ǰ������                (N)
    { 0x0003, 0x43,}, //3,  ��ǰ������                (N)
    { 0x0004, 0x43,}, //4,  ��ǰ����ƽ                (N)
    { 0x0005, 0x43,}, //5,  ��ǰ������                (N)

//  { 0x0006, 0x43,}, //6,  ��ǰ���й�������                (N)
//  { 0x0007, 0x43,}, //7,  ��ǰ���й�������                (N)
//  { 0x0008, 0x43,}, //8,  ��ǰ���й�������                (N)
//  { 0x0009, 0x43,}, //9,  ��ǰ���й�����ƽ                (N)
//  { 0x000a, 0x43,}, //10, ��ǰ���й�������                (N)
//
//  { 0x0006, 0x43,}, //11,  ��ǰ���й�������                (N)
//  { 0x0007, 0x43,}, //12,  ��ǰ���й�������                (N)
//  { 0x0008, 0x43,}, //13,  ��ǰ���й�������                (N)
//  { 0x0009, 0x43,}, //14,  ��ǰ���й�����ƽ                (N)
//  { 0x000a, 0x43,}, //15,  ��ǰ���й�������                (N)

    { 0x0106, 0x43,}, //6,  ��1�µ�����               (N)
    { 0x0107, 0x43,}, //7,  ��1�µ�����               (N)
    { 0x0108, 0x43,}, //8,  ��1�µ�����               (N)
    { 0x0109, 0x43,}, //9,  ��1�µ���ƽ               (N)
    { 0x010a, 0x43,}, //10,  ��1�µ�����               (N)

//  { 0x0110, 0x43,}, //21,  ��1�����й�������               (N)
//  { 0x0111, 0x43,}, //22,  ��1�����й�������               (N)
//  { 0x0112, 0x43,}, //23,  ��1�����й�������               (N)
//  { 0x0113, 0x43,}, //24, ��1�����й�����ƽ               (N)
//  { 0x0114, 0x43,}, //25, ��1�����й�������               (N)
//
//  { 0x0110, 0x43,}, //26,  ��1�·��й�������               (N)
//  { 0x0111, 0x43,}, //27,  ��1�·��й�������               (N)
//  { 0x0112, 0x43,}, //28,  ��1�·��й�������               (N)
//  { 0x0113, 0x43,}, //29, ��1�·��й�����ƽ               (N)
//  { 0x0114, 0x43,}, //30, ��1�·��й�������               (N)

    { 0x0206, 0x43,}, //11, ��2������й�������               (N)
    { 0x0207, 0x43,}, //12, ��2������й�������               (N)
    { 0x0208, 0x43,}, //13, ��2������й�������               (N)
    { 0x0209, 0x43,}, //14, ��2������й�����ƽ               (N)
    { 0x020a, 0x43,}, //15, ��2������й�������               (N)

//  { 0x0210, 0x43,}, //36, ��2�����й�������               (N)
//  { 0x0211, 0x43,}, //37, ��2�����й�������               (N)
//  { 0x0212, 0x43,}, //38, ��2�����й�������               (N)
//  { 0x0213, 0x43,}, //39, ��2�����й�����ƽ               (N)
//  { 0x0214, 0x43,}, //40, ��2�����й�������               (N)
//
//  { 0x0210, 0x43,}, //41, ��2�·��й�������               (N)
//  { 0x0211, 0x43,}, //42, ��2�·��й�������               (N)
//  { 0x0212, 0x43,}, //43, ��2�·��й�������               (N)
//  { 0x0213, 0x43,}, //44, ��2�·��й�����ƽ               (N)
//  { 0x0214, 0x43,}, //45, ��2�·��й�������               (N)

    { 0x0306, 0x43,}, //16, ��3������й�������               (N)
    { 0x0307, 0x43,}, //17, ��3������й�������               (N)
    { 0x0308, 0x43,}, //18, ��3������й�������               (N)
    { 0x0309, 0x43,}, //19, ��3������й�����ƽ               (N)
    { 0x030a, 0x43,}, //20, ��3������й�������               (N)

//  { 0x0310, 0x43,}, //51, ��3�����й�������               (N)
//  { 0x0311, 0x43,}, //52, ��3�����й�������               (N)
//  { 0x0312, 0x43,}, //53, ��3�����й�������               (N)
//  { 0x0313, 0x43,}, //54, ��3�����й�����ƽ               (N)
//  { 0x0314, 0x43,}, //55, ��3�����й�������               (N)
//
//  { 0x0310, 0x43,}, //56, ��3�·��й�������               (N)
//  { 0x0311, 0x43,}, //57, ��3�·��й�������               (N)
//  { 0x0312, 0x43,}, //58, ��3�·��й�������               (N)
//  { 0x0313, 0x43,}, //59, ��3�·��й�����ƽ               (N)
//  { 0x0314, 0x43,}, //60, ��3�·��й�������               (N)

//  { 0x0001, 0x43,}, //21��ǰ���ڵ���               (N)
//  { 0x010b, 0x43,}, //22�������ڵ���            (N)
    
    { 0x0000, 0x01,}, //21, ���ڼ�����
    { 0x0000, 0x02,}, //22, ʱ��

    { 0x0000, 0x13,}, //23, ͨѶ��ַ��4λ
    { 0x0000, 0x00,}, //24, ͨѶ��ַ��8λ

    { 0x001c, 0x13,}, //25, ��Ÿ�4λ
    { 0x001c, 0x00,}, //26, ��ŵ�8λ


    { 0x001d, 0x13,}, //27, �ͻ���Ÿ�4λ
    { 0x001d, 0x00,}, //28, �ͻ���ŵ�8λ


    {0x001b, 0x80},   //29����
    {0x0000, 0x0b},   //30������1
    {0x0000, 0x0b},   //31������2
    {0x0000, 0x0b},   //32������3

    { 0x001e, 0x84,}, //33, ��ѹ
    { 0x001f, 0x85,}, //34, ����
    { 0x0021, 0x86,}, //35, �ܹ���
    { 0x0000, 0x87,}, //36, ��������
    { 0x0020, 0x85,}, //37, ���ߵ���
    { 0x0000, 0x88,}, //38, ��ص�ѹ
    
    { 0x0000, 0x12,}, //39, �������
    { 0x0000, 0x02,}, //40, ���ʱ��
    { 0x0000, 0x12,}, //41, У������
    { 0x0000, 0x11,}, //42, У��ʱ��
};


const S_IDTAB code gCs_TabAdd[]=
{
    {0x03300001, 0x27}, //���ʱ�� ռ��2��
    {0x03300401, 0x29}, //Уʱʱ�� ռ��2��
};
const uint8 code guc_LenOfTabAdd = sizeof(gCs_TabAdd) / sizeof(S_IDTAB);

#else
extern const   S_IDTAB code gCs_TabConvent[];
extern const   uint8 code guc_LenOfTabConvent;
extern const   S_IDTAB code gCs_TabConvBL[];
extern const   uint8 code guc_LenOfTabConvBL;
extern const   S_IDTAB code gCs_TabConvCS[];
extern const   uint8 code guc_LenOfTabConvCS;
#endif


// ��λС�����
/*
*�Ͱ��ֽڵģ���ʾ���ţ�����ĳ��ֵ����ʾ��Ӧ�ķ��ţ�
*���༸λ����ʾ�������ʾС���㣨��Ӧλ����1����ʾ��������ʾ��
*/
enum
{//��λ��
    UNIT_NONE,          //0x00
    UNIT_KWH,           //0x01
    UNIT_KW,            //0x02
//    UNIT_CS,            //0x06
//    UNIT_Yuan,          //0x03
//  UNIT_Jine,          //0x04
//  UNIT_BH,            //0x05
//  UNIT_TIME,          //0x07
//  UNIT_SD,            //0x08
//  UNIT_SQ,            //0x09
//  UNIT_SY,            //0x0a
//  UNIT_JT,            //0x0b
//  UNIT_V,             //0x0c
//  UNIT_A,             //0x0d
//  UNIT_PF,            //0x0e
};

/*
1.XSBP8258��
                          DP10            DP9             DP8
             ____    ____    ____    ____    ____    ____    ____    ____
            |    |  |    | .|    |  |    | .|    |  |    | .|    |  |    |
            |____|  |____|  |____|  |____|  |____|  |____|  |____|  |____|
            |    |  |    | .|    |  |    | .|    |  |    | .|    |  |    |
            |____|. |____|. |____|. |____| .|____|. |____| .|____| .|____|
                DP1      DP2      DP3     DP4     DP5     DP6     DP7
*/

//����ʵ��ʹ�õ���С����,���ڽ���С����͵�λ���ű�
#define _P1     0x0010
#define _P2     0x0020
#define _P3     0x0040
#define _P4     0x0080
#define _P5     0x0100
#define _P6     0x0200
#define _P7     0x0400
#define _P8     0x0800
#define _P9     0x1000
#define _P10    0x2000
#define _PFu    0x4000


//��������С����궨��
#define Point_D1 _P7                //��Ӧ��2λ�������С����,�����1λС��
#define Point_D2 _P6                //��Ӧ��3λ�������С����,�����2λС��
#define Point_D3 _P5                //��Ӧ��3λ�������С����,�����3λС��
#define Point_D4 _P4                //��Ӧ��5λ�������С����,�����4λС��
#define Point_D6 _P2                //��Ӧ��7λ�������С����,�����6λС��
#define Point_Fu _PFu                //����ǰ��ĸ���

#ifdef LCDSHOWSELF
const   uint16 code gCui_UnitPointTab[]=
{
    0x0000,                 //0x00.����ʾ,����ʾ��ŵ��޵�λС�������Ϣʱʹ��
    _P4+_P6,                //0x01.����(XX.XX.XX  X)
    _P4+_P6+_P8+_P9,        //0x02.ʱ��(XX:XX:XX)
    UNIT_KWH,               //0x03.���������,Ĭ�ϲ���ʾС����,��E2�ж�ȡ��С����λ������,����ʾ����������֯���
    _P7,                    //0x04.��ѹ(X.X  V)
    _P5,                    //0x05.����(X.XXX A)
    UNIT_KW,            //0x06.�й����ʻ�����(X.XXXXX kW)
    _P5,//    _P5+UNIT_CS,            //0x07.��������(X.XXX,cos��)
    _P6,                    //0x08.��λС��(XX.XX)
    _P4+_P6,                //0x09.XX.XX.XX ������ �� ����ʱ
    _P4,                    //0x0A.XXXX.XXXX
    _P6,                    //0x0b ������ XX.XX
    0x0000,                 //0x0c
    0x0000,                 //0x0d
    0x0000,                 //0x0e
    0x0000,                 //0x0f
    0x0000,                 //0x10
    _P4+_P6+_P8+_P9,        //0x11
    _P4+_P6,                //0x12
    0x0000,                 //0x13
};
#endif

#define MacIsDispEnerg ((ucType == 0x16) || (ucType == 0x03))
#define _SW_ISNEEDNEGDISP   0       //�Ƿ���Ҫ������ʾ����

typedef struct s_ptmsk
{
    uint16  uiPtMsk;    //��ӦС���������λ
    uint8   ucNum;      //С�����Ӧ�ڼ���λ��
    uint8   reserved;   //����
}S_PTMSK;

#ifdef LCDSHOWSELF
const S_PTMSK code gCs_szPtMskTab[] =
{
    {Point_D6, 6, 0x00},
    {Point_D4, 4, 0x00},
    {Point_D3, 3, 0x00},
    {Point_D2, 2, 0x00},
    {Point_D1, 1, 0x00},
};

#endif

typedef struct s_dispsttbit
{
    uint8*  pucDst;     //Ŀ��״̬��
    uint8*  pucSrc;     //Դ״̬��
    uint8   ucDstMsk;   //Ŀ��״̬�ֵ�λ,��ֵ��СΪBIT0 - BIT7
    uint8   ucSrcMsk;   //Դ״̬�ֵ�λ����,��ֵ��СΪBIT0 - BIT7
    uint8   ucAtb;      //����
    uint8   ucOffset;   //ƫ��,���ڲ��ӱ�ʱ��ƫ��ָ��
}S_DISPSTTBIT;


#define __SW_BLINK_DISP__  1            //��˸λ����

enum
{
    Const_Disp_KeyUp = 0,
    Const_Disp_KeyDn,
    Const_Disp_RmtUp,       //ң���Ϸ���
    Const_Disp_RmtDn,       //ң���·���
};

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
void ShowKeyManage(uint8 ucType);
void ShowSecondProc(void);
uint8 ShowDataProc(void);
void ShowRefresh(void);
void SleepDispInit(void);
uint8 SleepDisp(void);
uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);
void ShowStateFlashManage(void);

#endif