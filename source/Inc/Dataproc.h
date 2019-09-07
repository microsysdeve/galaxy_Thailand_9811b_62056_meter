 
#ifndef _AP_DATAPROC_H_
#define _AP_DATAPROC_H_

#ifndef AP_DATAPROC_EXT
    #define AP_DATAPROC_EXT extern
#else 
    #define AP_DATASLEF
#endif

typedef struct 
{
    uint8 PluseType:1;      //0 RTC 1 Rate Switch pluse
    uint8 STAFLAG:1;
    uint8 Imbalance:1;
    uint8 Pdir:1;
    uint8 Prog:1;
    uint8 undefine5:1;
    uint8 undefine6:1;
    uint8 Current:1;
}GS_SYSRUNST;


AP_DATAPROC_EXT GS_SYSRUNST gs_SysRunSt;


//AP_DATAPROC_EXT union FREventOutUnion gs_FREventOut;

typedef struct 
{
    uint16 LoopError:1;      //��·���� ERR-01
    uint16 EsamError:1;      //ESAM������Ҫָ��λ���ɹ� ERR-02
    uint16 BatLow:1;         //��ص�ѹ��
    uint16 EEPROMERROR:1;    //EEPROM ���� ָʱ�����У��Ͳ��ٴ��� ERR-06
    uint16 TimeError:1;      //TIMER ERROR
    uint16 MACError:1;       //MAC ERROR ERR-10
    uint16 EsamKeyError:1;   //�ܳ׸��´���
    uint16 EsamJMError:1;    //���Ľ������
    uint16 REVPOWER:1;       //���ʷ���
}GS_SYSWARTN;
 
typedef union 
{
    GS_SYSWARTN SysWarn;
    uint16 byte;
}GT_SYSWARUN;

AP_DATAPROC_EXT GT_SYSWARUN  gut_SysWarn;
AP_DATAPROC_EXT uint8x XDATA_RAMZONE[16];  //pxdebug  //AP_DATAPROC_EXT uint8x XDATA_RAMZONE[128];
AP_DATAPROC_EXT uint8x XDATA_RAMZONE1[11];   //pxdebug //AP_DATAPROC_EXT uint8x XDATA_RAMZONE1[256];

/*******************************************************************************
**�������������1
*******************************************************************************/
typedef struct  
{
       uint8    undefine0:1;       //���ÿ��ؿ��Ʒ�ʽ:0��ƽ/1����
       uint8    LcdshowMode:1;     //Һ��Ȧ1Ȧ2��������:0��ʾ1��2��ʱ��/1��ʾ1��2�׷���
       uint8    ReportMode:1;      //�����ϱ�ģʽ:0�����ú�����־/1���ú�����־
       uint8    undefine3:1;       //����
       uint8    undefine4:1;       //����
       uint8    undefine5:1;       //����
       uint8    undefine6:1;       //����
       uint8    undefine7:1;       //����
}GS_RUNMODE;

AP_DATAPROC_EXT GS_RUNMODE gs_MeterMode;

enum
{
    LSDLID=0,     //��ʷ����      0x00
    DSDJID,       //��ʱ����      0x01
    SSDJID,       //˲ʱ����      0x02
    SQQHDJID,     //ʱ���л�����  0x03
    RSDQHDJID,    //ʱ���л�����  0x04
    RDJID,        //�ն���        0x05    
    ZDDJID,       //���㶳��      0x06
    DBQLJLID,     //��������¼  0x07
    SJQLJLID,     //�¼������¼  0x08
    JSJLID,       //Уʱ��¼      0x09
    BCJLID,       //��̼�¼      0x0a
    DDJLID,       //�����¼      0x0b
    KBGJLID,      //����Ǽ�¼    0x0c
    DYGZJLID,     //��Դ���ϼ�¼  0x0d
    JSSJJLID,     //����ʱ���¼  0x0e
    ZFHJLID,       //�ܸ��ɼ�¼����    0x0f
    FH1JLID,       //��1�ฺ�ɼ�¼���� 0x10
    FH2JLID,       //��2�ฺ�ɼ�¼���� 0x11
    FH3JLID,       //��3�ฺ�ɼ�¼���� 0x12
    FH4JLID,       //��4�ฺ�ɼ�¼���� 0x13
#ifdef ZXRPRLOG
    ZXRJLID,      //�����ռ�¼    0x14
#endif

#ifdef YGZHZPRLOG
    YGZHJLID,     //�й���ϼ�¼  0x15
#endif

#ifdef JSRPRLOG
    JSRJLID,      //�����ռ�¼    0x16
#endif
   
};

enum
{
    DBQLNUMID=0,    //����������      0x00
    SJQLNUMID,      //�¼��������      0x01
    JSNUMID,        //Уʱ����          0x02
    BCNUMID,        //��̴���          0x03
    DDNUMID,        //�������          0x04
    DSDJNUMID,      //��ʱ�������      0x05
    SSDJNUMID,      //˲ʱ�������      0x06
    SQQHDJNUMID,    //ʱ���л��������  0x07
    RSDQHDJNUMID,   //ʱ���л����� ���� 0x08
    RDJNUMID,       //�ն������        0x09    
    ZDDJNUMID,      //���㶳�����      0x0a
    KBGNUMID,       //����Ǵ���        0x0b
    DYGZNUMID,      //��Դ���ϴ���      0x0c
    ZFHNUMID,       //�ܸ��ɼ�¼����    0x0d
    FH1NUMID,       //��1�ฺ�ɼ�¼���� 0x0e
    FH2NUMID,       //��2�ฺ�ɼ�¼���� 0x0f
    FH3NUMID,       //��3�ฺ�ɼ�¼���� 0x10
    FH4NUMID,       //��4�ฺ�ɼ�¼���� 0x11
#ifdef SQSDPRLOG
    RSDNUMID,       //��ʱ�α��̴���  0x12
    SQNUMID,        //ʱ�����̴���    0x13
#endif

#ifdef ZXRPRLOG
    ZXRNUMID,       //�����ձ�̴���    0x14
#endif

#ifdef YGZHZPRLOG
    YGZHNUMID,      //�й���Ϸ�ʽ��̴��� 0x15
#endif

#ifdef JSRPRLOG
    JSRNUMID,       //�����ձ�̴���    0x16
#endif
    PRNUMCNT,
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

//#ifdef AP_DATASLEF
//const S_ROUND2 code gCs_Round2Tab[] =
//{//�����ݿ鲻����HEX��BCD֮���ת����С����λ����ת��,����ر�֤���ݿ���ֱ�Ӷ�ȡ�Ϳ���ʹ��
//
//    {60,    12, EEP_EPHIS_PT,   EEP_EPHIS   },  //��ʷ����      0x00
//    {49,    60, EEP_DSDJHIS_PT, EEP_DSDJLHIS},  //��ʱ����      0x01
//    {49,    3,  EEP_SSDJHIS_PT, EEP_SSDJLHIS},  //˲ʱ����      0x02
//    {49,    2,  EEP_SQDJHIS_PT, EEP_SQDJLHIS},  //ʱ���л�����  0x03
//    {49,    2,  EEP_RSDJHIS_PT, EEP_RSDJLHIS},  //ʱ���л�����  0x04
//    {49,    62, EEP_RDJHIS_PT,  EEP_RDJLHIS },  //�ն���        0x05    
//    {13,    254,EEP_ZDDJHIS_PT, EEP_ZDDJLHIS},  //���㶳��      0x06
//    {18,    10, EEP_DBQLET_PT,  EEP_DBQLET  },  //��������¼  0x07
//    {14,    10, EEP_SJQLET_PT,  EEP_SJQLET  },  //�¼������¼  0x08
//    {16,    10, EEP_JSET_PT,    EEP_JSET    },  //Уʱ��¼      0x09
//    {50,    10, EEP_BCET_PT,    EEP_BCET    },  //��̼�¼      0x0a
//    {12,    10, EEP_DDET_PT,    EEP_DDET    },  //�����¼      0x0b
//    {28,    10, EEP_KBGET_PT,   EEP_KBGET   },  //����Ǽ�¼    0x0c
//    {20,    10, EEP_DYYC_PT,    EEP_DYYC    },  //��Դ���ϼ�¼  0x0d
//    {4,     12, EEP_JSTIME_PT,  EEP_JSTIME  },  //����ʱ���¼  0x0e
//#ifdef LOADCURVE 
//    {11,    CurveTotalCnt,EEP_ZFHET_PT,   EEP_ZFHET   },  //�ܸ��ɼ�¼    0x0f
//    {12,    CurveTotalCnt,EEP_FHET1_PT,   EEP_FHET1   },  //��1�ฺ�ɼ�¼ 0x10
//    {8,     CurveTotalCnt,EEP_FHET2_PT,   EEP_FHET2   },  //��2�ฺ�ɼ�¼ 0x11
//    {7,     CurveTotalCnt,EEP_FHET3_PT,   EEP_FHET3   },  //��3�ฺ�ɼ�¼ 0x12
//    {13,    CurveTotalCnt,EEP_FHET4_PT,   EEP_FHET4   },  //��4�ฺ�ɼ�¼ 0x13
//#endif
//#ifdef ZXRPRLOG
//    {11,    10, EEP_ZXRXGJL_PT, EEP_ZXRXGJL },  //�����ռǱ�̼�¼    0x14
//#endif
//
//#ifdef YGZHZPRLOG
//    {11,    10, EEP_YGZHET_PT,  EEP_YGZHET  },  //�й���ϱ�̼�¼  0x15
//#endif
//
//#ifdef JSRPRLOG
//    {16,    10, EEP_JSRET_PT,   EEP_JSRET   },  //�����ձ�̼�¼    0x16
//#endif
//   
//};
//
//const  S_EVCNTADD code gCs_EvCntAddTab[] =
//{
//     {3,    EEP_DBQLETNO    },  //����������      0x00
//     {3,    EEP_SJQLETNO    },  //�¼��������      0x01
//     {3,    EEP_JSETNO      },  //Уʱ��¼          0x02
//     {3,    EEP_BCETNO      },  //��̼�¼          0x03
//
//     {3,    EEP_DDETNO      },  //�����¼          0x04
//     {3,    EEP_DSDJHISNO   },  //��ʱ�������      0x05
//     {3,    EEP_SSDJHISNO   },  //˲ʱ�������      0x06
//     {3,    EEP_SQDJHISNO   },  //ʱ���л��������  0x07
//     {3,    EEP_RSDJHISNO   },  //ʱ���л����� ���� 0x08
//     {3,    EEP_RDJHISNO    },  //�ն������        0x09    
//     {3,    EEP_ZDDJHISNO   },  //���㶳�����      0x0a
//
//     {3,    EEP_KBGETNO     },  //����Ǽ�¼        0x0b
//
//     {3,    EEP_DYYCNO      },  //��Դ���ϼ�¼      0x0c
//#ifdef LOADCURVE    
//     {3,    EEP_ZFHETNO     },  //�ܸ��ɼ�¼        0x0d
//     {3,    EEP_FHET1NO     },  //��1�ฺ�ɼ�¼     0x0e
//     {3,    EEP_FHET2NO     },  //��2�ฺ�ɼ�¼     0x0f
//     {3,    EEP_FHET3NO     },  //��3�ฺ�ɼ�¼     0x10
//     {3,    EEP_FHET4NO     },  //��4�ฺ�ɼ�¼     0x11
//#endif     
//#ifdef SQSDPRLOG
//     {3,    EEP_RSDXGNO     },  //��ʱ�α��̴���  0x12
//     {3,    EEP_SQXGNO      },  //ʱ�����̴���    0x13
//#endif
//
//#ifdef ZXRPRLOG
//     {3,    EEP_ZXRXGNO     },  //�����ձ�̴���    0x14
//#endif
//
//#ifdef YGZHZPRLOG
//     {3,    EEP_YGZHETNO    },  //�й���Ϸ�ʽ��̴��� 0x15
//#endif
//
//#ifdef JSRPRLOG
//     {3,    EEP_JSRETNO     },  //�����ձ�̴���    0x16      
//#endif
//};
//
//
//const  S_E2CLRCTR code gCs_MeterClearAddrTab[ClrType_AllNum]=
//{
//    {EEP_DBQLETNO,  3,},    //�������
//    {EEP_SJQLETNO,  3,},    //�¼�����
//    {EEP_JSTIME_PT, 1,},    //����ʱ���¼����
//
//    {EEP_JSETNO,    3,},    //Уʱ����
//    {EEP_BCETNO,    8,},    //�������
//    {EEP_DDETNO,    2,},    //��������
//    {EEP_KBGETNO,   5,},    //���������
//    {EEP_DYYCNO,    4,},    //��Դ��������
//
//#ifdef SQSDPRLOG    
//    {EEP_RSDXGNO,   9,},    //��ʱ�α�����
//    {EEP_SQXGNO,    9,},    //ʱ��������
//#endif
//
//#ifdef ZXRPRLOG
//    {EEP_ZXRXGNO,   2,},    //����������
//#endif
//
//#ifdef YGZHZPRLOG
//    {EEP_YGZHETNO,  2,},    //�й���Ϸ�ʽ����
//#endif
//#ifdef JSRPRLOG
//    {EEP_JSRETNO,   3,},    //����������
//#endif
//
//};
//
//
//const  S_E2CLRCTR code gCs_DJClearAddrTab[DjClrType_AllNum]=
//{
//    {EEP_SSDJHIS_PT,  3,},    //˲ʱ��������
//    {EEP_SQDJHIS_PT,  2,},    //ʱ����������
//    {EEP_RSDJHIS_PT,  2,},    //ʱ�α�������
//    {EEP_RDJHIS_PT,  48,},    //�ն�������
//    {EEP_ZDDJHIS_PT, 52,},    //���㶳������
//    {EEP_DSDJHIS_PT, 46,},    //��ʱ��������
//#ifdef LOADCURVE     
//    {EEP_ZFHETNO,   233,},    //������������
//#endif
//};
//
//#else
//extern const S_ROUND2 code gCs_Round2Tab[];
//extern const S_EVCNTADD code gCs_EvCntAddTab[];
//extern const S_E2CLRCTR code gCs_MeterClearAddrTab[ClrType_AllNum];
//extern const  S_E2CLRCTR code gCs_DJClearAddrTab[DjClrType_AllNum];
//#endif

#define MAX_DayDJ  7                     //����ϵ粹�ն������

AP_DATAPROC_EXT uint8  guc_InitWd[10];   //��ʼ��״̬��
AP_DATAPROC_EXT uint8  guc_ClearWd[10];  //�������״̬��
AP_DATAPROC_EXT uint8  guc_CalWd[10];    //У��״̬��
AP_DATAPROC_EXT uint32 gul_PowerTm;      //ͣ��ʱ��
 
void Data_ClearMeter(void);
void Data_HourProc(void);
void Data_MinProc(void);
void Data_DayProc(void);
void Data_SecProc(void);
void DataProcWriteRound2(uint8 ucRound, uint8 ucPos, uint8* pucBuf);
void DataProcRead2Slice(uint8 ucR2Pos, uint8 ucCnt, uint8 ucOffset, uint8 ucLen, uint8* pucBuf);
void DataProcEvCountAdd(uint8 ucNo);
uint32 RdEvCount(uint8 ucNo);
void Data_RecPara(void);
void DjProc(void);
void SetCRCWord(uint8 *WrodSt);
void ClRCRCWord(uint8 *WrodSt);
uint8 CheckCRCWord(uint8 *WrodSt);
void CalPowDwTm(void);
void RecoverJSRData(void);
void RecoverDayDjData(void);
void Data_RecEnergy(void);
void StructFreezeDate(void);
void RecoverZDFrez(void);
void YearJSProc(void);
void WriLastDJTime(S_CURTIME *LastCbrTm,uint8* time,uint8* pucBuf);
void CalDayBack(S_CURTIME *CurTime,uint8 offset);
uint8 JudgeJSR(uint8* CurTime,uint8* JSRTime,uint8 flg);
uint8 JudgeCurTime(uint8* CurTime,uint8* RdjTime);
void RecoverEnergyData(void);
void Data_YearProc(void);

#endif