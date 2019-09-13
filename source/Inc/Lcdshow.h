
#ifndef __LCDSHOW_H__
#define __LCDSHOW_H__

#ifndef LCDSHOWEXT
    #define LCDSHOWEXT extern
#else
    #define LCDSHOWSELF
#endif



#define Const_MaxDispTabNum (sizeof(gCs_DispTab)/sizeof(S_DISPCONT))


LCDSHOWEXT uint8 guc_ShowStCom;
LCDSHOWEXT uint8 guc_ShowEnergyFlag;

////////////////////////////////////////////////////////////
LCDSHOWEXT uint32   gul_ShowState;      // 显示系统状态

#define flgShowSt_M         0x0001     // 
#define flgShowSt_I         0x0002     // 
#define flgShowSt_D         0x0004     // 
#define flgShowSt_T         0x0008     // 
#define flgShowSt_S5        0x0010     // 
#define flgShowSt_S6        0x0020     // 
#define flgShowSt_S7        0x0040     // 
#define flgShowSt_S8        0x0080     // 
#define flgShowSt_S9        0x0100     // 
#define flgShowSt_S10       0x0200     // 
#define flgShowSt_S11       0x0400     //
#define flgShowSt_Bat       0x0800     // 
#define flgShowSt_Total     0x1000     // 

//////////////////////////////////////////////////////////


enum
{
    Const_NoNeedRefresh,    //不需要调用驱动刷新
    Const_NeedRefresh,      //需要调用驱动刷新
};

enum
{
    Const_DispMode_LX=0,        //轮显
    Const_DispMode_JX,          //键显
    Const_DispMode_TX,          //停显
    Const_DispMode_Full,        //全屏显示
    Const_DispMode_IRDA,        //红外通讯显示
    Const_DispMode_LXGB,        //自动轮显一轮结束后关闭显示状态
    Const_DispMode_TXGB,        //停显一轮结束后关闭显示状态
    Const_DispMode_PwOff,       //停电N天以后的状态
    Const_DispModeOff,          //凌晨x点到第二天y点关闭lcd显示的状态
    Const_DispMode_AdvSysClr,
    Const_DispMode_AC,          //自动校表特殊显示
    Const_DispMode_RMTLX,       //遥控器轮显键加速轮显内容显示
    Const_DispMode_Err,         //错误显示模式
};

enum
{
    Const_Disp_RAM = 0,
    Const_Disp_E2,
};

/*ucSpecialMode的定义*/
#define Const_AdvSysClr     0x80    //
#define Const_AdvAC         0x40    //自动校表

#define Cosnt_RefreshTime   0x01    //停电显示时仅显示数据需要更新需要刷新,本表仅为时间
#define Const_RefreshAll    0x02    //停电时所有显示都更新

typedef struct s_DispStt
{
    uint8   ucMode;         //显示模式,轮显,键显,停显等
    uint8   ucTmr;          //显示的定时时间，或关闭显示时间
    uint8   ucPwrOffRefresh;//停电时显示是否需要刷新
    uint16  uiIndex;        //当前显示查的表中的序号,不管是轮显或是键显等
    uint32  ulPwrOffTmr;    //停电下显示的定时时间
}S_DISPSTT;

#define ConstDayMin (1*24*60) //1day=24hour=1*24*60min

/*
*定义的这个变量内的数据是上面设置下来的,以后不设置则不会变化,时间的单位是秒,或许需要
*定时从E2中更新数据
*/
typedef struct 
{
    uint8 ucLxCnt;          //循显屏数
    uint8 ucLxTm;           //轮显显示时间
    uint8 ucEnyDoc;         //显示电能小数位数
    uint8 ucPowDoc;         //显示功率(最大需量显示位数)
    uint8 ucJxCnt;          //按键循环显示屏数
    uint8 uc_ShowErrPst;    //ERR错误字显示位置
    uint8 ucJxTm;           //有电下键显显示时间(自扩)
    uint8 ucJxPowOffTm;     //停电下键显显示时间(自扩)
    uint16 ulPowOffShowTm ; //停电显示时间(自扩)
    uint8  ucFullShowTm;    //上电全屏时间（自扩）
    uint8  ucPowUpBgTm;     //上电背光亮时间(自扩)
    uint8  ucIrBgTm;        //红外触发背光亮时间(自扩)
    uint8  ucKeyBgTm;       //按键触发背光亮时间(自扩)
    uint8  ucEsamBgTm;      //ESAM错误背光亮时间(自扩)
    uint8  ucPowUpLedTm;    //LED自检时间(自扩)
    uint16 ul_CRC;          //CRC保护
}S_DISPCONTENT;

typedef struct 
{
    uint16  uiStr1;         //用于显示的str区内容
    uint16  uiUnitPt1;      //单位和小数点符号显示内容
    uint32  ulNum1;         //显示num区的内容
    uint32  ulNum1Msk;      //num区显示时,消隐或特殊字符显示信息
}S_LCDDISP;

typedef struct 
{
    uint8   ucPort;                 //为了兼容通讯
    uint8   ucCmd;                  //规约命令字
    uint8   ucLen;                  //收发数据的长度
    uint8   ucLevel;                //权限等级
    uint8   ucReply;                //是否需要回复
    Word16  ucErr;                  //错误状态字
    uint8   ucAtb;                  //数据属性,包括地址信息,帧判别状态
    Word32  uiID;                   //数据ID
    Word32  uiUserCode;             //操作者代码
    uint8   *ucbuf;                 //接收的数据区首地址指针
}S_LCDDATEINFO;

LCDSHOWEXT  S_DISPCONTENT gs_DispCont;
LCDSHOWEXT S_DISPSTT   gs_DispStt ;        //状态转换中用到的结构
LCDSHOWEXT S_LCDDISP   gs_LcdDisp ;
//LCDSHOWEXT uint8 guc_IrShowLcdId[5];
//LCDSHOWEXT uint8 guc_ErrEsamMacSwTm;
//LCDSHOWEXT uint8 guc_ErrEsamKetSwTm;
//LCDSHOWEXT uint8 guc_ErrRevPowerSwTm;
//LCDSHOWEXT uint8 guc_ErrRevPowerStatus;
//LCDSHOWEXT uint8 guc_SwErrCode[8];
//LCDSHOWEXT uint8 guc_ErrCodeCnt;
//LCDSHOWEXT uint8 guc_ErrBtnFlag;
//LCDSHOWEXT uint8 guc_ShowErrEndFlag;

LCDSHOWEXT uint32 gul_ShowId;
//LCDSHOWEXT uint8 guc_ErrSwPt;       //错误显示指针
LCDSHOWEXT uint8 guc_BgCtrl;


#define Const_DispNeedMsk   0x80                        //需要消隐
#define Const_DispSigned    0x40                        //有符号数显示
#define Const_DisppHEX2BCD  0x20                        //需要HEX转BCD显示
#define Const_DispUnitPt    (0x10+0x08+0x04+0x02+0x01)  //用于查小数点和单位符号表

typedef struct s_dispcont
{
    uint32  ulShowState;    //每屏的状态
    uint8   uiUnitPoint;    //每屏的小数点和符号
}S_DISPCONT;

typedef struct s_idtab
{
    uint32 ulInID;
    uint8 uiNumb;
}S_IDTAB;



#ifdef LCDSHOWSELF

const S_IDTAB code gCs_TabConvent[]=
{   
    {0x00000000, 0x01}, //当前组合有功电量总            (N)
    {0x00010000, 0x01}, //当前正有功电量总              (N)
    {0x00020000, 0x01}, //当前反有功电量总              (N)

    {0x00000001, 0x02}, //上1月组合有功电量总           (N)
    {0x00010001, 0x02}, //上1月正有功电量总             (N)
    {0x00020001, 0x02}, //上1月反有功电量总             (N)

    {0x00000002, 0x03}, //上2月组合有功电量总           (N)
    {0x00010002, 0x03}, //上2月正有功电量总             (N)
    {0x00020002, 0x03}, //上2月反有功电量总             (N)
};
const   uint8 code guc_LenOfTabConvent = sizeof(gCs_TabConvent) / sizeof(S_IDTAB);

const   S_IDTAB code gCs_TabConvBL[]=
{
    {0x02010100, 0x0F}, // 电压
    {0x02020100, 0x10}, // 电流
    {0x02030000, 0x0}, // 总功率
    {0x02030100, 0x0}, // 总功率
    {0x02060000, 0x0}, // 功率因素
    {0x02060100, 0x0}, // 功率因素
    {0x02800001, 0x10}, // 零线电流
    {0x02800008, 0x0}, // 电池电压
};
const   uint8 code guc_LenOfTabConvBL = sizeof(gCs_TabConvBL) / sizeof(S_IDTAB);

const S_IDTAB code gCs_TabAdd[]=
{
//    {0x03300001, 0x0}, //编程时间 占用2屏
//    {0x03300401, 0x0}, //校时时间 占用2屏
    {0x03300D00, 0x09}, //开表盖次数
    {0x03300E00, 0x0A}, //开尾盖次数
    {0x03300D01, 0x0B}, //最近一次开表盖起始时间 日期
    {0x03300D02, 0x0C}, //最近一次开表盖起始时间 时间
    {0x03300E01, 0x0D}, //最近一次开表尾盖起始时间 日期
    {0x03300E02, 0x0E}, //最近一次开表尾盖起始时间 时间
};
const uint8 code guc_LenOfTabAdd = sizeof(gCs_TabAdd) / sizeof(S_IDTAB);

const   S_IDTAB code gCs_TabConvCS[]=
{
    {0x04000101, 0x04}, //日期
    {0x04000102, 0x05}, //时间
    {0x04000402, 0x06}, //表号 占用2屏
};
const   uint8 code guc_LenOfTabConvCS = sizeof(gCs_TabConvCS) / sizeof(S_IDTAB);
/////////////////////////////////////////////
//下面结构体由上面结构体查找
const S_DISPCONT code gCs_DispTab[]=
{
    { 0x00000000,  0x00,},   //0, 无显示

    { 0x00001000,  0x31,}, //1,  当前组合有功电量总 
    { 0x00000018,  0x01,}, //2,  上1月组合有功电量总
    { 0x00000000,  0x01,}, //3,  上2月组合有功电量总
    { 0x00000020,  0x40,}, //4,  日期
    { 0x00000020,  0x50,}, //5,  时间

    { 0x00000040,  0x00,}, //6, 表号
    { 0x00000000,  0x00,}, //7, 无显示
    { 0x00000000,  0x00,},   //8, 无显示
    { 0x00000100,  0x00,},   //9, 开表盖次数
    { 0x00000200,  0x00,},   //A, 开尾盖次数
    { 0x00000120,  0x40,},   //B, 最近一次开表盖起始时间 日期
    { 0x00000120,  0x50,},   //C, 最近一次开表盖起始时间 时间
    { 0x00000220,  0x40,},   //D, 最近一次开表尾盖起始时间 日期
    { 0x00000220,  0x50,},   //E, 最近一次开表尾盖起始时间 时间
    { 0x00000000,  0x43,},   //F, 电压
    { 0x00000000,  0x24,},   //0x10, 电流
//    { 0x00000001,  0x22,},   //E, 有功功率
//    { 0x00000000,  0x30,},   //F, 功率因素
//    
//    { 0x00000000,  0x22,},   //0x10, 需量
};

#else
extern const   S_IDTAB code gCs_TabConvent[];
extern const   uint8 code guc_LenOfTabConvent;
extern const   S_IDTAB code gCs_TabConvBL[];
extern const   uint8 code guc_LenOfTabConvBL;
extern const   S_IDTAB code gCs_TabConvCS[];
extern const   uint8 code guc_LenOfTabConvCS;
#endif

enum
{
    Const_Ret_OK = 0,
    Const_Ret_Err,
    Const_Ret_Disp_Off,             //关闭显示
    Const_Ret_DispFull,             //全屏显示
    Const_Ret_DispMode_Err,         //错误报警
};

void ShowSysStart(void);
void ShowInitial(void);
void ShowSecondProc(void);
//void ShowDataProc(void);
#define  ShowDataProc()  {}
void ShowNumManage(uint32 ulID, uint8 ucSubNo);
void ShowRefresh(void);
void PowOffShowRefresh(void);
uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);

void ShowKeyManage(void);
void SleepDispInit(void);

uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);

uint8 SleepDisp(void);

#endif