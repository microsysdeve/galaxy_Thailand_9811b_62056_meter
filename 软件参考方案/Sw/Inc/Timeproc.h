#ifndef __TIMEPROC_H__
#define __TIMEPROC_H__

#ifndef TIMEPROC_EXT
    #define TIMEPROC_EXT extern
#else
    #define TIMEPROC_SELF 
#endif

#define _SW_EXT_RTC
#define CLOCKERR  0x55

#define Const_ClkBAK_RAM BIT0                               //ramʱ�ӱ���,һ��ÿ�뱸��һ��
#define Const_ClkBAK_E2  BIT1                               //E2��ʱ�ӱ���,һ���Сʱ����һ��
#define Const_ClkBAK (Const_ClkBAK_RAM + Const_ClkBAK_E2)   //����ʱ�Ӷ�����һ��
#define CLOCK_LEN   (sizeof(S_TIMEDATA))

#define DayMinCount     (1440)                              //ÿ��ķ�����
#define HourSecCount    (3600)                              //ÿСʱ������
#define QuartYearDay    (1461)                              //4����������
#define DaySecCount     (86400)                             //1�����������

#define MAX_CLOCK_BAK_GAP (300)                               //������Ӳʱ���ܸ�������������� 300s

enum
{
    SOFT_RTC_MAIN,                                          //��ʱ��ram����������һ����ȷ
    SOFT_RTC_E2,                                            //��ʱ�ӿ�E2���ֵ���������
    SOFT_RTC_ERR,                                           //��ʱ�Ӳ�����E2���ݶ���Ч��
};

enum EXT_RTC_WORK_TYPE
{                                                           //��ʵ�ʴ���ʱ,�ⲿʱ�ӵĹ���״̬
    EXT_RTC_NO_WORK,
    EXT_RTC_WORK,
    EXT_RTC_VALID,
    EXT_RTC_INVALID,
};

enum CLOCKTYPE
{//����ı��YYΪ��,MMΪ��,DDΪ��,WWΪ����,hhΪСʱ,mmΪ��,ssΪ��,���ݴ��ҵ����Ӧ�����ֽڴӵ͵���
    Const_YYMMDDWW,         //���ݴӵ��ֽڿ�ʼ�������д���Ϊ����,��,��,��
    Const_YYMMDD,           //��,��,��
    Const_hhmmss,           //��,��,ʱ
    Const_YYMMDDhhmmss,     //��,��,��,��,��,ʱ,
    Const_YYMMDDhhmm,       //��,ʱ,��,��,��
    Const_hhmmssYYMMDDWW,   //����,��,��,��,��,��,ʱ,
    Const_WW,               //����
};

typedef struct strTimeData
{

    uint8   ucSecond;       //��
    uint8   ucMinute;       //��
    uint8   ucHour;         //ʱ
    uint8   ucDay;          //��
    uint8   ucMonth;        //��
    uint8   ucYear;         //��
    uint8   ucWeek;         //��

    uint16  uiCRC;          // CRCУ��
} S_TIMEDATA;
TIMEPROC_EXT S_TIMEDATA gs_DateTime;        //��ǰʱ������
TIMEPROC_EXT S_TIMEDATA gs_LastDateTime;    //��һ��ʱ������
TIMEPROC_EXT S_TIMEDATA gs_ClkTmp;          //ʱ��������ʱ����
TIMEPROC_EXT  uint8 guc_ExtRtcErrCnt;       //Ӳʱ�Ӵ������
TIMEPROC_EXT  uint8 guc_ClockErr;

typedef struct 
{
    uint8   ucMinute;       //��
    uint8   ucHour;         //ʱ
    uint8   ucDay;          //��
    uint8   ucMonth;        //��
    uint8   ucYear;         //��
} S_CURTIME;
TIMEPROC_EXT S_CURTIME gs_CurDateTime;        //��ǰʱ������
TIMEPROC_EXT S_CURTIME gs_StartLoadCurve;     //���ɼ�¼��ʼʱ��
TIMEPROC_EXT uint32 gul_LoadCurveMin;         //��ǰ������
TIMEPROC_EXT uint8 guc_LCTimeFlag;                  //��ʼʱ�����ñ�־


#ifdef TIMEPROC_SELF
const S_DATACHK code gCs_ClkChkTab[] =
{

    {0, 0x59,},  //0x00, ucSecond
    {0, 0x59,},  //0x01, ucMinute
    {0, 0x23,},  //0x02, ucHour
    {1, 0x31,},  //0x03, ucDay
    {1, 0x12,},  //0x04, ucMonth
    {0, 0x99,},  //0x05, ucYear
    {0, 0x06,},  //0x06, week,����Ƚ�����
};

const uint8 code Tab_Week_2K[] =
//0,    1,  2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12     �·�,Ϊ�˲����,��һ��Ϊ��Чֵ
{0x00,0x06,0x02,0x03,0x06,0x01,0x04,0x06,0x02,0x05,0x00,0x03,0x05};  //2000��ÿ���µĵ�һ�������ڼ����Ų���

const uint8 code MonthDays[] =
{
    0,                                          // 0x00 (��Ч)
    31, 28, 31, 30, 31, 30, 31, 31, 30,         // 0x01 - 0x09
    0, 0, 0, 0, 0, 0,                           // 0x0A - 0x0F (��Ч)
    31, 30, 31,                                 // 0x10 - 0x12
};

// ÿ����ʼ���������
const uint16 code gui_MonthBeginDay[12] = 
{0, 31, 59, 90,120, 151, 181, 212, 243, 273, 304, 334};
#else
extern const uint8 code MonthDays[];
extern const S_DATACHK code gCs_ClkChkTab[];
#endif


void TimerProc(void);                           //��ʱ����ʱ������ÿ�����
void GetSysClock(uint8* pucBuf, uint8 ucType);  //��ȡϵͳʱ��
void SetSysClock(uint8* pucBuf, uint8 ucType);  //����ϵͳʱ��
void ClockBAK_RAM(void);                        //����RAMʱ��
//void ClockBAK_E2(void);                         //����E2ʱ��
void ClockBAK_All(void);                        //����RAM��E2ʱ��
void GetYYMMDDhhmm(uint8* pucBuf);              //��ȡYMDHM����

uint8 CalcWeek(uint8 year, uint8 month, uint8 day);               //����ʱ��ʱ����������ʱ����
uint8 YearMonthDayCheck(uint8 ucYear, uint8 ucMonth, uint8 ucDay);//����ʱ��ʱ��������õ�ʱ���Ƿ���ϸ�ʽ

uint8 RTCCheck(uint8* pucClk);
//uint8 CheckTime(void);
//uint32 CalcAbsSecond(S_TIMEDATA* psTm);
//uint32 CalcAbsTime(S_TIMEDATA* psTm);
//uint16 CalcAbsDay(S_TIMEDATA* psTm);
//uint32 CalcTimeGap(S_TIMEDATA* psTm1, S_TIMEDATA* psTm2);
//uint8 ValidTime(uint8* time, uint8 type);
void SleepTimeProc(void);
uint8 SoftClockCheck(void);
#endif  


