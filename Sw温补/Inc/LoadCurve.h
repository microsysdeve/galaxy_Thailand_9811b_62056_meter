#ifndef __LOADCURVE_H__
#define __LOADCURVE_H__

#ifndef LOADCURVEEXT
    #define LOADCURVEEXT extern
#endif

#define LOADCURVE
#define LDC_TYPENEW       //0411后读取负荷记录方式

#define Err_LG 0xF000     //大于最新时标
#define Err_LT 0xF800     //小于最早时标
#define Err_MD 0xF400     //中间时标
#define Err_NO 0xF200     //无数据

#define CurveTotalCnt     288
   

#define CurveOneType     0x01
#define CurveTwoType     0x02
#define CurveThreeType   0x04
#define CurveFourType    0x08

typedef struct 
{
    uint8    ucReadFlg;     //
    uint8    ucIsFake;      //是否补点
    uint16   uiCurPt;       //当前最新位置
    uint16   uiLastPt;      //当前最早位置
    uint16   uiFindPt;      //查询位置
         
}S_LDCPT;

LOADCURVEEXT S_LDCPT gs_LdcPos;

typedef struct 
{
    uint8   ucMinute;       //分
    uint8   ucHour;         //时
    uint8   ucDay;          //日
    uint8   ucMonth;        //月
    uint8   ucYear;         //年
}S_CURVETM;

#ifdef LDC_TYPENEW
typedef struct
{
    uint8 ucType;
    uint8 CurCnt;
    uint8 TotalCnt;
    uint8 SeqFrameEnd;
    S_CURVETM tmOG;
    S_CURVETM tmBG;
    S_CURVETM tmED;
    uint16 uiGap;
    uint32 ulLastMin;
    uint32 ulLastData;    
}S_LDCFRAME;
//typedef struct
//{
//    uint8 CurCnt;
//    uint8 TotalCnt;
//    uint8 SeqFrameEnd;
//    uint16 LastPt;
//    uint32 LastData; 
//}S_LDCFRAME;
LOADCURVEEXT S_LDCFRAME gs_LdcFrame;

#else
typedef struct
{
    uint8 CurCnt;
    uint8 TotalCnt;
    uint8 SeqFrameEnd;
    uint16 LastCurvePt;
    
}S_CURVEFOLLOWFRAME;
LOADCURVEEXT S_CURVEFOLLOWFRAME gs_CurveFollowFrame;
#endif
typedef struct
{
    uint32 ulTotalCnt;
    uint32 ulOneCnt;
    uint32 ulTwoCnt;
    uint32 ulThreeCnt;
    uint32 ulFourCnt;
}S_CURVECNT;




typedef struct
{
    S_CURVETM  STm;
    uint8  ucType;
    uint8  ucOnePt;
    uint8  ucTwoPt;
    uint8  ucThreePt;
    uint8  ucFourPt;
    uint8  ucHighBit;
}S_CURVETOTAL1;

typedef struct
{
    S_CURVETM  STm;
    uint8  ucType;
    uint16 uiOnePt;
    uint16 uiTwoPt;
    uint16 uiThreePt;
    uint16 uiFourPt;
}S_CURVETOTAL;


//LOADCURVEEXT uint8 guc_LoadCurveMode;  //负荷记录模式字

typedef struct
{
    uint8  ucLdcMode;   //负荷记录模式字
    uint16 uiFH1;       //第1类负荷记录间隔时间
    uint16 uiFH2;       //第2类负荷记录间隔时间
    uint16 uiFH3;       //第3类负荷记录间隔时间
    uint16 uiFH4;       //第4类负荷记录间隔时间
}S_LDCPARA;
 
LOADCURVEEXT S_LDCPARA gs_LdcSet; //负荷记录间隔

typedef struct
{
    uint16 uiCntAddr;
    uint16 uiPtAddr;
    uint16 uiBaseAddr;
    uint8  ucLen;
}S_CURVESTORE;

extern const S_CURVESTORE code gs_CurveStoreTab[5];
LOADCURVEEXT uint8 guc_Timechange;  //时间是否改变

LOADCURVEEXT void LoadCurveCheck(void);
void Ldc_DataProc(void);
void Ldc_Recover(void);
uint16 Ldc_ZoneChk(uint8 const *tmBG, uint8 const *tmED, uint8 ucType);
uint8 Ldc_Get1stRecord(uint8 ucType, uint8 *Tm, uint8 *buff);
//uint8 Ldc_Get1stRecord(uint8 ucType, uint8 *TmBG, uint8 *TmED, uint8 *buff);
uint8 Ldc_GetSeqRecord(uint8 ucType,uint8 *buff);
//uint8 Ldc_GetSeqRecord(uint8 ucType, uint8 *Tm, uint8 *buff);
uint32 Ldc_TmMinCal(uint8 *Tm);
uint8 Ldc_TimeCal(uint8 *TmNew, uint8 *TmOld, uint16 Gap);
void Ldc_TimeAdd(uint8 *Tm, uint32 ulLen);
uint8 CmpTm(uint8 const *T1, uint8  const *T2, uint8 n ); 
uint8 BuildOneCurveFrame(uint8 ucType,uint8*DesBuff,uint8*SrcBuff);
uint8 BuildTotalCurveFrame(S_CURVETOTAL *s_TotalCurve,uint8 *buff);
 
uint8 GetOneOldestRecord( uint8 ucType, uint8 ucCnt,uint8 *buff);
uint8 GetTotalOldestRecord(uint8 ucCnt,uint8 *buff);

uint8 GetOneTmRecord(uint8 ucType,uint8 *Tm,uint8 *buff);
uint8 GetOneTmSeqRecord( uint8 ucType, uint8 ucCnt,uint8 *buff);

uint8 GetTotalTmRecord(uint8 *Tm,uint8 *buff);
uint8 GetTotalTmSeqRecord(uint8 ucCnt,uint8 *buff);

uint8 GetOneItemRecord( uint8 ucType, uint8 *buff);
uint8 GetTotalItemRecord(uint8 *buff);

void Ldc_TimeSub(uint8 *Tm, uint16 uiLen);




#endif 

