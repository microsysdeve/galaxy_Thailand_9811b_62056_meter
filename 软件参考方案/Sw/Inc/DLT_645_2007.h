
#ifndef _DLT_2007_645_H_
#define _DLT_2007_645_H_

#ifndef DLT_2007_645_EXT
    #define DLT_2007_645_EXT extern
#endif



#define USERIDNUM  0x0400040E

enum
{
    InValid=0,  //��Ч
    QhTmFm,     //ʱ����ʱ���л�ʱ��
    QhCnFm,     //��ʱ����p��14,
    SdBCnFm,    //��ʱ�α���q��8
    FeeCnFm,    //������k��63 ʵ��<=4
    HldCnFm,    //����������n��254
    AtSwCnFm,   //�Զ�ѭ����ʾ����
    AtSwTmFm,   //ÿ����ʾʱ��
    EngDocFm,   //��ʾ����С��λ��
    PowDocFm,   //��ʾ����(�������)С��λ��
    KeySwCnFm,  //����ѭ����ʾ����
    MeterIdFm,  //���
    EPCalcFm,   //�й������
    IrBdFm,     //�����ͺ�����ͨ������������
    ZxrWdFm,    //������������
    ZxrSdFm,    //�����ղ��õ���ʱ�α��
    JsrFm,      //ÿ�µ�1������
    SqDtFm,     //ʱ������
    SdDtFm,     //ʱ������
    ZdDjTmFm,   //���㶳��ʱ����
    RDjTmFm,    //�ն���ʱ��
    RS485Fm,    //485�����ʸ�ʽ
    TzTmFm,     //��բ��ʱʱ���ʽ
    GgJRFm,     //�������ո�ʽ
    DjMdFm,     //�����ʽ�����㶳����
    ZdDjMdFm,   //���㶳���ʽ
    ZdDjStTmFm, //���㶳����ʼʱ��
    SqCntFm,    //��ʱ����(ÿ���л���) m��14
    MeterAdsFm, //ͨ�ŵ�ַ
    MeterRptFm, //�������������+�����ϱ�ģʽ��
    PowerFullTm,//ȫ����ʾʱ��
    LoadCurveFm,//���ɼ�¼ģʽ��+���ɼ�¼��ʼʱ��+ʱ������
    PdirFm,     //���ʷ����¼�
    MeterModeFm,//�������������
};

typedef struct
{
    uint32 ulId;        //���ݱ�ʶ
    uint16 E2Addr;      //E2��ַ
    uint8  ucLen;       //���ݳ���
}Gs_E2RWCtr;


DLT_2007_645_EXT Word32 guw_UseCode;

/*******************************************************************************
**�����Ǻ�������
*******************************************************************************/
uint8 RWData(S_FRAMEINFO *s_FrmInfo);
//uint8 ReadMeterAddr(S_FRAMEINFO *s_FrmInfo);
uint8 WriteMeterAddr(S_FRAMEINFO *s_FrmInfo);
uint8 ChangePassWord(S_FRAMEINFO *s_FrmInfo);
uint8 ChangeBode(S_FRAMEINFO *s_FrmInfo);
uint8 ClearMaxXL(S_FRAMEINFO *s_FrmInfo);
uint8 ClearMeter(S_FRAMEINFO *s_FrmInfo);
uint8 ClearEvent(S_FRAMEINFO *s_FrmInfo);
uint8 BroadcastTime(S_FRAMEINFO *s_FrmInfo);
uint8 Freeze(S_FRAMEINFO *s_FrmInfo);
uint8 SecPulsCtrl(S_FRAMEINFO *s_FrmInfo);
uint8 MidFindID(Word32 id, S_CORETAB code* tab, uint8 num);
uint8 ReadAccuEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadZHLYEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
//uint8 ReadCurEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
//uint8 ReadHisEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 FunToBeDef(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 FactoryRD(S_FRAMEINFO *s_FrmInfo);
uint8 FactoryWR(S_FRAMEINFO *s_FrmInfo);
uint8 ComRWE2Para(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadVar(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable);

//uint8 CmpCode(S_FRAMEINFO *s_FrmInfo);

uint8 ComReadRunCode(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadJL(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwDjData(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwSqSd(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwLcdData(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwSysTime(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwRamE2(S_FRAMEINFO *s_FrmInfo, S_CORETAB code*  CTable);
uint8 SwitchSuperAdmin(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ComMeterConst(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ComRdEvCnt(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 RwGGJR(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 IrShowLcd(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadSwVersion(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadEnyD0Block(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 WrPassWord(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadHisJSTime(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 Report(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadCurveJl(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
 
#endif
