
#ifndef _DLT_2007_645_H_
#define _DLT_2007_645_H_

#ifndef DLT_2007_645_EXT
    #define DLT_2007_645_EXT extern
#endif



#define USERIDNUM  0x0400040E

enum
{
    InValid=0,  //0 无效
    QhTmFm,     //1 时区、时段切换时间
    QhCnFm,     //2 年时区数p≤14,
    SdBCnFm,    //3 日时段表数q≤8
    SqCntFm,    //4 日时段数(每日切换数) m≤14
    FeeCnFm,    //5 费率数k≤63 实际<=4
    HldCnFm,    //6 公共假日数n≤254
    AtSwCnFm,   //7 自动循环显示屏数
    AtSwTmFm,   //8 每屏显示时间
    EngDocFm,   //9 显示电能小数位数
    PowDocFm,   //10 显示功率(最大需量)小数位数
    KeySwCnFm,  //11 按键循环显示屏数
    MeterIdFm,  //12 表号
    EPCalcFm,   //13 有功组合字
    IrBdFm,     //14 调制型红外光口通信速率特征字
    RS485Fm,    //15 485波特率格式
    ZxrWdFm,    //16 周休日特征字
    ZxrSdFm,    //17 周休日采用的日时段表号
    JsrFm,      //18 每月第1结算日
    ZdDjTmFm,   //19 整点冻结时间间隔
    RDjTmFm,    //20 日冻结时间
    TzTmFm,     //21 跳闸延时时间格式
    GgJRFm,     //22 公共假日格式
    DjMdFm,     //23 冻结格式除整点冻结外
    ZdDjMdFm,   //24 整点冻结格式
    ZdDjStTmFm, //25 整点冻结起始时间
    MeterAdsFm, //26 通信地址
    MeterRptFm, //27 电表运行特征字+主动上报模式字
    PowerFullTm,//28 全屏显示时间
    LoadCurveFm,//29 负荷记录模式字+负荷记录起始时间+时间间隔？
    PdirFm,     //30 功率反向事件
    MeterModeFm,//31 电表运行特征字
    EsamStaFm,  //32 密钥总条数 34
    OCFm,       //33 过流判断下限与延时
    SqDtFm,     //34 时区数据
    SdDtFm,     //35 时段数据
};

typedef struct
{
    uint32 ulId;        //数据标识
    uint16 E2Addr;      //E2地址
    uint8  ucLen;       //数据长度
}Gs_E2RWCtr;


DLT_2007_645_EXT Word32 guw_UseCode;

/*******************************************************************************
**下面是函数申明
*******************************************************************************/
uint8 RWData(S_FRAMEINFO *s_FrmInfo);
uint8 ReadMeterAddr(S_FRAMEINFO *s_FrmInfo);
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
uint8 ReadCurEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadHisEgy(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 FunToBeDef(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 FactoryRD(S_FRAMEINFO *s_FrmInfo);
uint8 FactoryWR(S_FRAMEINFO *s_FrmInfo);
uint8 ComRWE2Para(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
uint8 ReadVar(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable);

uint8 CmpCode(S_FRAMEINFO *s_FrmInfo);
/*
uint8 AutoCheckMeter(S_FRAMEINFO *s_FrmInfo, S_CORETAB* CTable);
*/
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

uint8 RwTestTime(S_FRAMEINFO *s_FrmInfo, S_CORETAB code* CTable);
void RecoverTestTime(void);

#endif
