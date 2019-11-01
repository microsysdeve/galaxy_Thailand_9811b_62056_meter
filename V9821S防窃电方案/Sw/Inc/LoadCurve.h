#ifndef __LOADCURVE_H__
#define __LOADCURVE_H__

#ifndef LOADCURVEEXT
    #define LOADCURVEEXT extern
#endif

#define LOADCURVE

#define CurveTotalCnt     288
   

#define CurveOneType     0x01
#define CurveTwoType     0x02
#define CurveThreeType   0x04
#define CurveFourType    0x08


typedef struct
{
    uint8 CurCnt;
    uint8 TotalCnt;
    uint8 SeqFrameEnd;
    uint16 LastCurvePt;
    
}S_CURVEFOLLOWFRAME;
LOADCURVEEXT S_CURVEFOLLOWFRAME gs_CurveFollowFrame;

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
    uint8   ucMinute;       //��
    uint8   ucHour;         //ʱ
    uint8   ucDay;          //��
    uint8   ucMonth;        //��
    uint8   ucYear;         //��
}S_CURVETM;

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


LOADCURVEEXT uint8 guc_LoadCurveMode;  //���ɼ�¼ģʽ��

typedef struct
{
    uint16 uiFH1;       //��1�ฺ�ɼ�¼���ʱ��
    uint16 uiFH2;       //��2�ฺ�ɼ�¼���ʱ��
    uint16 uiFH3;       //��3�ฺ�ɼ�¼���ʱ��
    uint16 uiFH4;       //��4�ฺ�ɼ�¼���ʱ��
}S_FHTIME;
 
LOADCURVEEXT S_FHTIME gs_LoadCurveTime; //���ɼ�¼���

typedef struct
{
    uint16 uiCntAddr;
    uint16 uiPtAddr;
    uint16 uiBaseAddr;
    uint8  ucLen;
}S_CURVESTORE;

extern const S_CURVESTORE code gs_CurveStoreTab[5];
LOADCURVEEXT uint8 guc_Timechange;  //ʱ���Ƿ�ı�

LOADCURVEEXT void LoadCurveCheck(void);
void LoadCurveSave(void);
void RecoverLoadCurve(void);

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






#endif 

