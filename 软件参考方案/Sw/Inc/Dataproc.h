 
#ifndef _AP_DATAPROC_H_
#define _AP_DATAPROC_H_

#ifndef AP_DATAPROC_EXT
    #define AP_DATAPROC_EXT extern
#else 
    #define AP_DATASLEF
#endif 

enum
{
    LSDLID=0,       //��ʷ����      0x00
    LSXLID,         //��ʷ����      0x01
    DDJLID,         //�����¼      0x02
    KBGJLID,        //����Ǽ�¼    0x03
    KXGJLID,        //���߸Ǽ�¼    0x04
};

enum
{//���Ʊ�2��ָ����д����ʱ,��Ҫ�����ƶ��ķ�ʽ
    R2_NO_MOVE=0,     //����Ҫ�ƶ�
    R2_MOVE,        //��Ҫ�����ƶ�һ��
};


typedef struct s_evcntadd
{
    uint8   ucLen;      //E2�����ݱ�����ֽ���,���ֵ���Ӧ�ó���4,��Ӧһ��unsigned long
    uint16  uiAddr;     //E2�д�ŵĵ�ַ
}S_EVCNTADD;



typedef struct s_round2
{//����������������2
    uint8   ucLen;      //�������
    uint16  ucMod;      //���ݿ�����,������ģ
    uint16  uiPtAddr;   //ָ���ַ,����ָ��ǰ���ݿ�
    uint16  uiDataAddr; //��������������ʼ��ַ
}S_ROUND2;

typedef struct 
{
    uint16 uiE2Addr;
    uint8  ucPageCnt;
}S_E2CLRCTR;

enum 
{
    ClrTypeNum = 6,     //����������
#ifdef SQSDPRLOG
    ClrType_RSDBCNum,   //����ʱ��������
    ClrType_SQBCNum,    //��ʱ��������
#endif

#ifdef ZXRPRLOG
    ClrType_ZXRBCNum,   //��������������
#endif

#ifdef YGZHZPRLOG
    ClrType_YGZHBCNum, //���й���Ϸ�ʽ������
#endif

#ifdef JSRPRLOG
    ClrType_JSRBCNum, //�������������
#endif
    ClrType_JSSJNum,  //����ʱ������
    ClrType_AllNum,   //�����м�¼
};

enum 
{
  DjClrType_BaseNum=5,
#ifdef LOADCURVE
  CurveClr_Num,
#endif
  DjClrType_AllNum, 
};

#ifdef AP_DATASLEF
const S_ROUND2 code gCs_Round2Tab[] =
{//�����ݿ鲻����HEX��BCD֮���ת����С����λ����ת��,����ر�֤���ݿ���ֱ�Ӷ�ȡ�Ϳ���ʹ��

    {20,    12, EEP_EPHIS_PT,           EEP_EPHIS       },  //��ʷ����      0x00
    {8,     13, EEP_XULIANGHIS_PT,      EEP_XULIANGHIS  },  //��ʷ����      0x01
    {10,    10, EEP_DDET_PT,            EEP_DDET        },  //�����¼      0x02
    {5,     13, EEP_BGEVENT_PT,         EEP_BGEVENT     },  //����Ǽ�¼    0x03
    {6,     13, EEP_XGEVENT_PT,         EEP_XGEVENT     },  //���߸Ǽ�¼    0x04
};
#else
extern const S_ROUND2 code gCs_Round2Tab[];
#endif

AP_DATAPROC_EXT uint8  XDATA_RAMZONE[64];
AP_DATAPROC_EXT uint8  guc_InitWd[10];   //��ʼ��״̬��
//AP_DATAPROC_EXT uint8  guc_ClearWd[10];  //�������״̬��
AP_DATAPROC_EXT uint32 gul_PowerTm;      //ͣ��ʱ��
 
void Data_ClearMeter(void);
void Data_HourProc(void);
void Data_MinProc(void);
//void Data_DayProc(void);
void DataProcWriteRound2(uint8 ucRound, uint8 ucPos, uint8* pucBuf);
void DataProcRead2Slice(uint8 ucR2Pos, uint8 ucCnt, uint8 ucOffset, uint8 ucLen, uint8* pucBuf);
//void DataProcEvCountAdd(uint8 ucNo);
//uint32 RdEvCount(uint8 ucNo);
void SetCRCWord(uint8 *WrodSt);
void ClRCRCWord(uint8 *WrodSt);
uint8 CheckCRCWord(uint8 *WrodSt);
//void CalPowDwTm(void);
//void RecoverJSRData(void);
//void RecoverDayDjData(void);
void RecoverEnegyData(void);
//void StructFreezeDate(void);
//void RecoverZDFrez(void);
//void YearJSProc(void);
//void WriLastDJTime(S_CURTIME *LastCbrTm,uint8* time,uint8* pucBuf);
//void CalDayBack(S_CURTIME *CurTime,uint8 offset);
//uint8 JudgeJSR(uint8* CurTime,uint8* JSRTime,uint8 flg);
//uint8 JudgeCurTime(uint8* CurTime,uint8* RdjTime);


#endif
