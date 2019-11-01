
#ifndef _REPORT_H_
#define _REPORT_H_

#ifndef RPT_EXT
    #define RPT_EXT extern
#endif

/*******************************************************************************
**主动上报模式字
*******************************************************************************/

//上报模式字1
typedef struct  
{
       uint16    LoopErrRpt:1;      //控制回路错误
       uint16    EasmErrRpt:1;      //EASM错误
       uint16    undefine2:1;       //内卡初始化错误
       uint16    RtcBatRpt:1;       //时钟电池电压低
       uint16    FlashErrRpt:1;     //内部程序错误
       uint16    EepErrRpt:1;       //存储器故障或损坏
       uint16    undefine6:1;       //保留
       uint16    RtcErrRpt:1;       //时钟故障
       uint16    CutBatRpt:1;      //停电抄表电池欠压
       uint16    undefine9:1;       //透支状态
       uint16    CoverRpt:1;        //开表盖
       uint16    undefine11:1;       //开端钮盖
       uint16    undefine12:1;       //恒定磁场干扰
       uint16    PowErrRpt:1;       //电源异常
       uint16    SwitchOff:1;       //跳闸成功
       uint16    SwitchOn:1;       //合闸成功
}GS_REPORTWORD1;

typedef union
{
    Word16 Word;
    GS_REPORTWORD1 ReportWord1;
}GT_REPORTWORD1;

//上报模式字2
typedef struct  
{
       uint16    undefine0:1;       //失压
       uint16    undefine1:1;       //欠压
       uint16    undefine2:1;       //过压
       uint16    undefine3:1;       //失流
       uint16    OverCurrent:1;     //过流
       uint16    undefine5:1;       //过载
       uint16    PDirRpt:1;         //功率反向
       uint16    undefine7:1;       //断相
       uint16    undefine8:1;       //断流
       uint16    undefine9:1;       //保留
       uint16    undefine10:1;       //保留
       uint16    undefine11:1;       //保留
       uint16    undefine12:1;       //保留
       uint16    undefine13:1;       //保留
       uint16    undefine14:1;       //保留
       uint16    undefine15:1;       //保留
}GS_REPORTWORD2;

typedef union
{
    Word16 Word;
    GS_REPORTWORD2 ReportWord2;
}GT_REPORTWORD2;

//上报模式字3
typedef struct  
{
       uint16    undefine0:1;       //电压逆相序
       uint16    undefine1:1;       //电流逆相序
       uint16    undefine2:1;       //电压不平衡
       uint16    undefine3:1;       //电流不平衡
       uint16    undefine4:1;       //辅助电源失电
       uint16    PowOffRpt:1;       //掉电
       uint16    undefine6:1;       //需量超限
       uint16    undefine7:1;       //总功率因数超下限
       uint16    undefine8:1;       //电流严重不平衡
       uint16    PDirRpt:1;         //潮流反向（双向计量除外）
       uint16    undefine10:1;       //全失压
       uint16    undefine11:1;       //保留
       uint16    undefine12:1;       //保留
       uint16    undefine13:1;       //保留
       uint16    undefine14:1;       //保留
       uint16    undefine15:1;       //保留
}GS_REPORTWORD3;

typedef union
{
    Word16 Word;
    GS_REPORTWORD3 ReportWord3;
}GT_REPORTWORD3;

//上报模式字4
typedef struct  
{
       uint16    PgRpt:1;       //编程
       uint16    MeterClr:1;       //电表清零
       uint16    undefine2:1;       //需量清零
       uint16    EventClr:1;       //事件清零
       uint16    Timing:1;       //校时
       uint16    SdtPg:1;       //时段表编程
       uint16    SqtPg:1;       //时区表编程
       uint16    ZxrPg:1;       //周休日编程
       uint16    JjrPg:1;       //节假日编程
       uint16    EPCalcPg:1;         //有功组合方式编程
       uint16    undefine10:1;       //无功组合方式1编程
       uint16    undefine11:1;       //无功组合方式2编程
       uint16    JsrPg:1;       //结算日编程
       uint16    FeePg:1;       //费率参数表编程
       uint16    undefine14:1;       //阶梯表编程
       uint16    MYupdate:1;       //密钥更新
}GS_REPORTWORD4;

typedef union
{
    Word16 Word;
    GS_REPORTWORD4 ReportWord4;
}GT_REPORTWORD4;

/*******************************************************************************
**主动上报模式字
*******************************************************************************/
typedef struct 
{
    GT_REPORTWORD1 ui_ReportWord1;                  //主动上报模式字1
    GT_REPORTWORD2 ui_ReportWord2;                  //主动上报模式字2
    GT_REPORTWORD3 ui_ReportWord3;                  //主动上报模式字3
    GT_REPORTWORD4 ui_ReportWord4;                  //主动上报模式字4 0411新增
}REPORTWORD;

#define RPTWORDLEN   sizeof(REPORTWORD)

RPT_EXT REPORTWORD gs_ReportWord;

/*******************************************************************************
**主动上报状态字
*******************************************************************************/
typedef struct 
{
    GT_REPORTWORD1 ui_RptSta1;                  //主动上报模式字1
    GT_REPORTWORD2 ui_RptSta2A;                 //主动上报模式字2
    GT_REPORTWORD2 ui_RptSta2B;                 //主动上报模式字2
    GT_REPORTWORD2 ui_RptSta2C;                 //主动上报模式字2
    GT_REPORTWORD3 ui_RptSta3;                  //主动上报模式字3
    GT_REPORTWORD4 ui_RptSta4;                  //主动上报模式字4 0411新增
}REPORTSTATE;

#define RPTSTALEN   sizeof(REPORTSTATE)

RPT_EXT REPORTSTATE gs_ReportState;    //主动上报状态字  1: 发生 0: 下发复位主动上报状态字指令
RPT_EXT REPORTSTATE gs_RptStaB;        //1:暗位  0:明位
RPT_EXT REPORTSTATE gs_ReportStateFlg; //1:事件发生  0:事件结束

//以下事件,带BIT7无次数记录
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
       uint8    LoopErr;      //控制回路错误
       uint8    EasmErr;      //EASM错误
       uint8    EepInit;      //内卡初始化错误
       uint8    RtcBat;       //时钟电池电压低
       uint8    EepErr;       //存储器故障或损坏
       uint8    RtcErr;       //时钟故障
       uint8    CutBat;       //停电抄表电池欠压
       uint8    Cover;        //开表盖
       uint8    PowErr;       //电源异常       
       uint8    SwitchOn;     //跳闸成功
       uint8    SwitchOff;    //合闸成功
       uint8    OverC;        //过流
       uint8    PDir;         //功率反向
       uint8    PowOff;       //掉电
       uint8    Pg;           //编程
       uint8    MeterClr;       //电表清零
       uint8    EventClr;       //事件清零
       uint8    Timing;       //校时
       uint8    SdtPg;       //时段表编程
       uint8    SqtPg;       //时区表编程
       uint8    ZxrPg;       //周休日编程
//       uint8    JjrPg;       //节假日编程
       uint8    EPCalcPg;         //有功组合方式编程
       uint8    JsrPg;       //结算日编程
//       uint8    FeePg;       //费率参数表编程
       uint8    MYupdate;       //密钥更新
}REPORTCNT; //目前单相智能表支持

#define RPTCNTLEN   sizeof(REPORTCNT)
RPT_EXT REPORTCNT gs_RptCnt;

RPT_EXT uint8  guc_RptClrCnt;    //主动上报自动清零时间

RPT_EXT uint16 gui_ReportCRC;

#define RPTDATLEN (RPTSTALEN*3+RPTCNTLEN+1)

enum CLRTYPE
{
    Const_All = 0,         //
    Const_Meter,
    Const_Event,
};
//主动上报判断条件
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