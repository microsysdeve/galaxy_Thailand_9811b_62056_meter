
#ifndef _REPORT_H_
#define _REPORT_H_

#ifndef RPT_EXT
    #define RPT_EXT extern
#endif

/*******************************************************************************
**�����ϱ�ģʽ��
*******************************************************************************/

//�ϱ�ģʽ��1
typedef struct  
{
       uint16    LoopErrRpt:1;      //���ƻ�·����
       uint16    EasmErrRpt:1;      //EASM����
       uint16    undefine2:1;       //�ڿ���ʼ������
       uint16    RtcBatRpt:1;       //ʱ�ӵ�ص�ѹ��
       uint16    FlashErrRpt:1;     //�ڲ��������
       uint16    EepErrRpt:1;       //�洢�����ϻ���
       uint16    undefine6:1;       //����
       uint16    RtcErrRpt:1;       //ʱ�ӹ���
       uint16    CutBatRpt:1;      //ͣ�糭����Ƿѹ
       uint16    undefine9:1;       //͸֧״̬
       uint16    CoverRpt:1;        //�����
       uint16    undefine11:1;       //����ť��
       uint16    undefine12:1;       //�㶨�ų�����
       uint16    PowErrRpt:1;       //��Դ�쳣
       uint16    SwitchOff:1;       //��բ�ɹ�
       uint16    SwitchOn:1;       //��բ�ɹ�
}GS_REPORTWORD1;

typedef union
{
    Word16 Word;
    GS_REPORTWORD1 ReportWord1;
}GT_REPORTWORD1;

//�ϱ�ģʽ��2
typedef struct  
{
       uint16    undefine0:1;       //ʧѹ
       uint16    undefine1:1;       //Ƿѹ
       uint16    undefine2:1;       //��ѹ
       uint16    undefine3:1;       //ʧ��
       uint16    OverCurrent:1;     //����
       uint16    undefine5:1;       //����
       uint16    PDirRpt:1;         //���ʷ���
       uint16    undefine7:1;       //����
       uint16    undefine8:1;       //����
       uint16    undefine9:1;       //����
       uint16    undefine10:1;       //����
       uint16    undefine11:1;       //����
       uint16    undefine12:1;       //����
       uint16    undefine13:1;       //����
       uint16    undefine14:1;       //����
       uint16    undefine15:1;       //����
}GS_REPORTWORD2;

typedef union
{
    Word16 Word;
    GS_REPORTWORD2 ReportWord2;
}GT_REPORTWORD2;

//�ϱ�ģʽ��3
typedef struct  
{
       uint16    undefine0:1;       //��ѹ������
       uint16    undefine1:1;       //����������
       uint16    undefine2:1;       //��ѹ��ƽ��
       uint16    undefine3:1;       //������ƽ��
       uint16    undefine4:1;       //������Դʧ��
       uint16    PowOffRpt:1;       //����
       uint16    undefine6:1;       //��������
       uint16    undefine7:1;       //�ܹ�������������
       uint16    undefine8:1;       //�������ز�ƽ��
       uint16    PDirRpt:1;         //��������˫��������⣩
       uint16    undefine10:1;       //ȫʧѹ
       uint16    undefine11:1;       //����
       uint16    undefine12:1;       //����
       uint16    undefine13:1;       //����
       uint16    undefine14:1;       //����
       uint16    undefine15:1;       //����
}GS_REPORTWORD3;

typedef union
{
    Word16 Word;
    GS_REPORTWORD3 ReportWord3;
}GT_REPORTWORD3;

//�ϱ�ģʽ��4
typedef struct  
{
       uint16    PgRpt:1;       //���
       uint16    MeterClr:1;       //�������
       uint16    undefine2:1;       //��������
       uint16    EventClr:1;       //�¼�����
       uint16    Timing:1;       //Уʱ
       uint16    SdtPg:1;       //ʱ�α���
       uint16    SqtPg:1;       //ʱ������
       uint16    ZxrPg:1;       //�����ձ��
       uint16    JjrPg:1;       //�ڼ��ձ��
       uint16    EPCalcPg:1;         //�й���Ϸ�ʽ���
       uint16    undefine10:1;       //�޹���Ϸ�ʽ1���
       uint16    undefine11:1;       //�޹���Ϸ�ʽ2���
       uint16    JsrPg:1;       //�����ձ��
       uint16    FeePg:1;       //���ʲ�������
       uint16    undefine14:1;       //���ݱ���
       uint16    MYupdate:1;       //��Կ����
}GS_REPORTWORD4;

typedef union
{
    Word16 Word;
    GS_REPORTWORD4 ReportWord4;
}GT_REPORTWORD4;

/*******************************************************************************
**�����ϱ�ģʽ��
*******************************************************************************/
typedef struct 
{
    GT_REPORTWORD1 ui_ReportWord1;                  //�����ϱ�ģʽ��1
    GT_REPORTWORD2 ui_ReportWord2;                  //�����ϱ�ģʽ��2
    GT_REPORTWORD3 ui_ReportWord3;                  //�����ϱ�ģʽ��3
    GT_REPORTWORD4 ui_ReportWord4;                  //�����ϱ�ģʽ��4 0411����
}REPORTWORD;

#define RPTWORDLEN   sizeof(REPORTWORD)

RPT_EXT REPORTWORD gs_ReportWord;

/*******************************************************************************
**�����ϱ�״̬��
*******************************************************************************/
typedef struct 
{
    GT_REPORTWORD1 ui_RptSta1;                  //�����ϱ�ģʽ��1
    GT_REPORTWORD2 ui_RptSta2A;                 //�����ϱ�ģʽ��2
    GT_REPORTWORD2 ui_RptSta2B;                 //�����ϱ�ģʽ��2
    GT_REPORTWORD2 ui_RptSta2C;                 //�����ϱ�ģʽ��2
    GT_REPORTWORD3 ui_RptSta3;                  //�����ϱ�ģʽ��3
    GT_REPORTWORD4 ui_RptSta4;                  //�����ϱ�ģʽ��4 0411����
}REPORTSTATE;

#define RPTSTALEN   sizeof(REPORTSTATE)

RPT_EXT REPORTSTATE gs_ReportState;    //�����ϱ�״̬��  1: ���� 0: �·���λ�����ϱ�״̬��ָ��
RPT_EXT REPORTSTATE gs_RptStaB;        //1:��λ  0:��λ
RPT_EXT REPORTSTATE gs_ReportStateFlg; //1:�¼�����  0:�¼�����

//�����¼�,��BIT7�޴�����¼
#define RPT_LOOP    0
#define RPT_ESAM    1+BIT7
#define RPT_EEPINIT 2+BIT7
#define RPT_RTCBAT  3+BIT7
#define RPT_EEP     5+BIT7
#define RPT_RTCERR  7+BIT7
#define RPT_CUTBAT  8+BIT7
#define RPT_COVER   10
#define RPT_POWERR  13
#define RPT_SWHOFF  14
#define RPT_SWHON   15
#define RPT_OVERC   20
#define RPT_PDIR    22+BIT7
#define RPT_POWOFF  37
#define RPT_PROG    48
#define RPT_MECLR   49
#define RPT_EVCLR   51
#define RPT_TIME    52
#define RPT_SDPG    53
#define RPT_SQPG    54
#define RPT_ZXRPG   55
#define RPT_EPCPG   57
#define RPT_JSRPG   60
#define RPT_MYGX    63
#define RPT_NONE    0xFF

typedef struct
{   
       uint8    LoopErr;      //���ƻ�·����
       uint8    EasmErr;      //EASM����
       uint8    EepInit;      //�ڿ���ʼ������
       uint8    RtcBat;       //ʱ�ӵ�ص�ѹ��
       uint8    EepErr;       //�洢�����ϻ���
       uint8    RtcErr;       //ʱ�ӹ���
       uint8    CutBat;       //ͣ�糭����Ƿѹ
       uint8    Cover;        //�����
       uint8    PowErr;       //��Դ�쳣       
       uint8    SwitchOn;     //��բ�ɹ�
       uint8    SwitchOff;    //��բ�ɹ�
       uint8    OverC;        //����
       uint8    PDir;         //���ʷ���
       uint8    PowOff;       //����
       uint8    Pg;           //���
       uint8    MeterClr;       //�������
       uint8    EventClr;       //�¼�����
       uint8    Timing;       //Уʱ
       uint8    SdtPg;       //ʱ�α���
       uint8    SqtPg;       //ʱ������
       uint8    ZxrPg;       //�����ձ��
//       uint8    JjrPg;       //�ڼ��ձ��
       uint8    EPCalcPg;         //�й���Ϸ�ʽ���
       uint8    JsrPg;       //�����ձ��
//       uint8    FeePg;       //���ʲ�������
       uint8    MYupdate;       //��Կ����
}REPORTCNT; //Ŀǰ�������ܱ�֧��

#define RPTCNTLEN   sizeof(REPORTCNT)
RPT_EXT REPORTCNT gs_RptCnt;

RPT_EXT uint8  guc_RptClrCnt;    //�����ϱ��Զ�����ʱ��

RPT_EXT uint16 gui_ReportCRC;

#define RPTDATLEN (RPTSTALEN*3+RPTCNTLEN+1)

enum CLRTYPE
{
    Const_All = 0,         //
    Const_Meter,
    Const_Event,
};
//�����ϱ��ж�����
#define RptRet() (((gs_ReportState.ui_RptSta1.Word.word&0x25AC) != 0) \
                  || ((gs_ReportState.ui_RptSta2A.Word.word&0x0040) != 0) \
                  || (gs_ReportState.ui_RptSta3.ReportWord3.PowOffRpt != 0) \
                  || ((gs_ReportState.ui_RptSta4.Word.word&0x127B) != 0))

void Rpt_Clr(uint8);
void Rpt_UpdateClr(void);
void Rpt_UpdateSta(uint16 *);
void Rpt_Recover(void);
void Rpt_StaSet(uint8);
void Rpt_StaBitClr(uint8);
void Rpt_StaFlgClr(uint8);
void Rpt_Crc(void);

#endif