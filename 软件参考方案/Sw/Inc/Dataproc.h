 
#ifndef _AP_DATAPROC_H_
#define _AP_DATAPROC_H_

#ifndef AP_DATAPROC_EXT
    #define AP_DATAPROC_EXT extern
#else 
    #define AP_DATASLEF
#endif 

enum
{
    LSDLID=0,       //历史电量      0x00
    LSXLID,         //历史需量      0x01
    DDJLID,         //掉电记录      0x02
    KBGJLID,        //开表盖记录    0x03
    KXGJLID,        //开线盖记录    0x04
};

enum
{//卷绕表2的指针在写数据时,需要卷绕移动的方式
    R2_NO_MOVE=0,     //不需要移动
    R2_MOVE,        //需要卷绕移动一格
};


typedef struct s_evcntadd
{
    uint8   ucLen;      //E2中数据保存的字节数,这个值最大不应该超过4,对应一个unsigned long
    uint16  uiAddr;     //E2中存放的地址
}S_EVCNTADD;



typedef struct s_round2
{//卷绕数据内容类型2
    uint8   ucLen;      //数据项长度
    uint16  ucMod;      //数据块总数,用于求模
    uint16  uiPtAddr;   //指针地址,用于指向当前数据块
    uint16  uiDataAddr; //所有数据内容起始地址
}S_ROUND2;

typedef struct 
{
    uint16 uiE2Addr;
    uint8  ucPageCnt;
}S_E2CLRCTR;

enum 
{
    ClrTypeNum = 6,     //基本清零数
#ifdef SQSDPRLOG
    ClrType_RSDBCNum,   //清日时段清零数
    ClrType_SQBCNum,    //清时区清零数
#endif

#ifdef ZXRPRLOG
    ClrType_ZXRBCNum,   //清周休日清零数
#endif

#ifdef YGZHZPRLOG
    ClrType_YGZHBCNum, //清有功组合方式清零数
#endif

#ifdef JSRPRLOG
    ClrType_JSRBCNum, //清结算日清零数
#endif
    ClrType_JSSJNum,  //结算时间清零
    ClrType_AllNum,   //清所有记录
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
{//本数据块不关心HEX和BCD之间的转换和小数点位数的转换,请务必保证数据可以直接读取就可以使用

    {20,    12, EEP_EPHIS_PT,           EEP_EPHIS       },  //历史电量      0x00
    {8,     13, EEP_XULIANGHIS_PT,      EEP_XULIANGHIS  },  //历史需量      0x01
    {10,    10, EEP_DDET_PT,            EEP_DDET        },  //掉电记录      0x02
    {5,     13, EEP_BGEVENT_PT,         EEP_BGEVENT     },  //开表盖记录    0x03
    {6,     13, EEP_XGEVENT_PT,         EEP_XGEVENT     },  //开线盖记录    0x04
};
#else
extern const S_ROUND2 code gCs_Round2Tab[];
#endif

AP_DATAPROC_EXT uint8  XDATA_RAMZONE[64];
AP_DATAPROC_EXT uint8  guc_InitWd[10];   //初始化状态字
//AP_DATAPROC_EXT uint8  guc_ClearWd[10];  //电表清零状态字
AP_DATAPROC_EXT uint32 gul_PowerTm;      //停电时间
 
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
