
#ifndef __LCDSHOW_H__
#define __LCDSHOW_H__

#ifndef LCDSHOWEXT
    #define LCDSHOWEXT extern
#else
    #define LCDSHOWSELF
#endif



#define Const_MaxDispTabNum (sizeof(gCs_DispTab)/sizeof(S_DISPCONT))


#define DEFAULT_CLOCK_NO    68          //默认的时间显示在显示表中的位置
#define DEFAULT_ENERGY_NO   1           //默认的当前电量在显示表中的位置

#define Const_Disp_Neg      0x00        //负数
#define Const_Disp_Pos      0x01        //正数
LCDSHOWEXT uint8 guc_ShowStCom;
LCDSHOWEXT uint8 guc_ShowEnergyFlag;

LCDSHOWEXT uint32   gul_ShowState;      // 显示系统状态
#define flgShowSt_Fuh       0x0800   // 负号
#define flgShowSt_TJ        0x0000   // 囤积
//#define flgShowSt_TZ        0x2000000   // 透支
//#define flgShowSt_LZ        0x1000000   // 拉闸
//#define flgShowSt_QGD       0x800000    // 请购电
//#define flgShowSt_SB        0x400000    // 失败
//#define flgShowSt_CG        0x200000    // 成功
//#define flgShowSt_Zhong     0x100000    // 中
//#define flgShowSt_DK        0x80000     // 读卡
//#define flgShowSt_SJ2       0x20000     // 三角2
//#define flgShowSt_SJ1       0x10000     // 三角1
//#define flgShowSt_Fk4       0x8000      // 方块4
//#define flgShowSt_Fk3       0x4000      // 方块3
//#define flgShowSt_Fk2       0x2000      // 方块2
//#define flgShowSt_Fk1       0x1000      // 方块1
#define flgShowSt_Lock      0x0400      // 密码错误锁
#define flgShowSt_PRvs      0x0200      // 功率反向
#define flgShowSt_Bat       0x0100      // 电池指示
#define flgShowSt_Pgm       0x0080      // 编程键
//#define flgShowSt_ZB        0x0080      // 载波
#define flgShowSt_Com       0x0040      // 通讯指示
#define flgShowSt_YQ2       0x0020      // 圆圈2
#define flgShowSt_YQ1       0x0010      // 圆圈1
#define flgShowSt_Fee4      0x0008      // 第四费率
#define flgShowSt_Fee3      0x0004      // 第三费率
#define flgShowSt_Fee2      0x0002      // 第二费率
#define flgShowSt_Fee1      0x0001      // 第一费率

//LCDSHOWEXT  uint32 gul_ShowId;

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
LCDSHOWEXT uint8 guc_IrShowLcdId[5];
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


/*S_DISPCONT显示表成员结构体的定义
*uiInID为核心表内部ID,用uiInID可以查核心表
*ucStr用于lcd驱动中查中文字符串表
*ucAtb为属性,其中:
    bit7: 0不消隐/1消隐
    bit6: 0无/1有 符号数
    bit5: 0不要/1要 Hex2BCD
    bit4-bit0:用于查单位小数点格式表
*/
#define Const_DispNeedMsk   0x80                        //需要消隐
#define Const_DispSigned    0x40                        //有符号数显示
#define Const_DisppHEX2BCD  0x20                        //需要HEX转BCD显示
#define Const_DispUnitPt    (0x10+0x08+0x04+0x02+0x01)  //用于查小数点和单位符号表

typedef struct s_dispcont
{
//  uint32  ulInID;         //内部ID,当为0xFFFF表示无效屏,0xFFFE表示全屏
    uint16  uiStr;          //用于lcd驱动中查中文字符串表
    uint8   ucAtb;          //属性
//  uint8   ucExt;          //扩展
//  uint8   ucOffset;       //用于扩展规约的项
//  uint8   reserved;       //保留
}S_DISPCONT;

typedef struct s_idtab
{
    uint32 ulInID;
    uint8 uiNumb;
}S_IDTAB;

//[显示表]
/*
*这里的屏号是从0开始分别为1,2,3,...,屏号0无效
*在code区显示此值时需要在g_sDispStt.uiIndex的基础上加一才可以看到实际的屏号
*设置在E2中的屏号为大于0的整数
*注意:
    1.此表中内部核心ID不需要排序,而由屏号隐含顺序排列
    2.其中这个表里面的核心ID中,0xFFFF为无效屏号,仍然去数据处理中作用,0xFFFE为全屏显示
*/

#ifdef LCDSHOWSELF

const S_IDTAB code gCs_TabConvent[]=
{   
    {0x00000000, 0x01}, //2,  当前组合有功电量总            (N)
    {0x00000100, 0x02}, //3,  当前组合有功电量尖            (N)
    {0x00000200, 0x03}, //4,  当前组合有功电量峰            (N)
    {0x00000300, 0x04}, //5,  当前组合有功电量平            (N)
    {0x00000400, 0x05}, //6,  当前组合有功电量谷            (N)

    {0x00010000, 0x01}, //2,  当前正有功电量总              (N)
    {0x00010100, 0x02}, //3,  当前正有功电量尖              (N)
    {0x00010200, 0x03}, //4,  当前正有功电量峰              (N)
    {0x00010300, 0x04}, //5,  当前正有功电量平              (N)
    {0x00010400, 0x05}, //6,  当前正有功电量谷              (N)

    {0x00020000, 0x01}, //2,  当前反有功电量总              (N)
    {0x00020100, 0x02}, //3,  当前反有功电量尖              (N)
    {0x00020200, 0x03}, //4,  当前反有功电量峰              (N)
    {0x00020300, 0x04}, //5,  当前反有功电量平              (N)
    {0x00020400, 0x05}, //6,  当前反有功电量谷              (N)

    {0x00000001, 0x06}, //7,  上1月组合有功电量总           (N)
    {0x00000101, 0x07}, //8,  上1月组合有功电量尖           (N)
    {0x00000201, 0x08}, //9,  上1月组合有功电量峰           (N)
    {0x00000301, 0x09}, //10, 上1月组合有功电量平           (N)
    {0x00000401, 0x0a}, //11, 上1月组合有功电量谷           (N)

    {0x00010001, 0x06}, //7,  上1月正有功电量总             (N)
    {0x00010101, 0x07}, //8,  上1月正有功电量尖             (N)
    {0x00010201, 0x08}, //9,  上1月正有功电量峰             (N)
    {0x00010301, 0x09}, //10, 上1月正有功电量平             (N)
    {0x00010401, 0x0a}, //11, 上1月正有功电量谷             (N)

    {0x00020001, 0x06}, //7,  上1月反有功电量总             (N)
    {0x00020101, 0x07}, //8,  上1月反有功电量尖             (N)
    {0x00020201, 0x08}, //9,  上1月反有功电量峰             (N)
    {0x00020301, 0x09}, //10, 上1月反有功电量平             (N)
    {0x00020401, 0x0a}, //11, 上1月反有功电量谷             (N)

    {0x00000002, 0x0b}, //12, 上2月组合有功电量总           (N)
    {0x00000102, 0x0c}, //13, 上2月组合有功电量尖           (N)
    {0x00000202, 0x0d}, //14, 上2月组合有功电量峰           (N)
    {0x00000302, 0x0e}, //15, 上2月组合有功电量平           (N)
    {0x00000402, 0x0f}, //16, 上2月组合有功电量谷           (N)

    {0x00010002, 0x0b}, //12, 上2月正有功电量总             (N)
    {0x00010102, 0x0c}, //13, 上2月正有功电量尖             (N)
    {0x00010202, 0x0d}, //14, 上2月正有功电量峰             (N)
    {0x00010302, 0x0e}, //15, 上2月正有功电量平             (N)
    {0x00010402, 0x0f}, //16, 上2月正有功电量谷             (N)


    {0x00020002, 0x0b}, //12, 上2月反有功电量总             (N)
    {0x00020102, 0x0c}, //13, 上2月反有功电量尖             (N)
    {0x00020202, 0x0d}, //14, 上2月反有功电量峰             (N)
    {0x00020302, 0x0e}, //15, 上2月反有功电量平             (N)
    {0x00020402, 0x0f}, //16, 上2月反有功电量谷             (N)

    {0x00000003, 0x10}, //17, 上3月组合有功电量总           (N)
    {0x00000103, 0x11}, //18, 上3月组合有功电量尖           (N)
    {0x00000203, 0x12}, //19, 上3月组合有功电量峰           (N)
    {0x00000303, 0x13}, //20, 上3月组合有功电量平           (N)
    {0x00000403, 0x14}, //21, 上3月组合有功电量谷           (N)

    {0x00010003, 0x10}, //17, 上3月正有功电量总             (N)
    {0x00010103, 0x11}, //18, 上3月正有功电量尖             (N)
    {0x00010203, 0x12}, //19, 上3月正有功电量峰             (N)
    {0x00010303, 0x13}, //20, 上3月正有功电量平             (N)
    {0x00010403, 0x14}, //21, 上3月正有功电量谷             (N)

    {0x00020003, 0x10}, //17, 上3月反有功电量总             (N)
    {0x00020103, 0x11}, //18, 上3月反有功电量尖             (N)
    {0x00020203, 0x12}, //19, 上3月反有功电量峰             (N)
    {0x00020303, 0x13}, //20, 上3月反有功电量平             (N)
    {0x00020403, 0x14}, //21, 上3月反有功电量谷             (N)

//  {0x000B0000, 0x3D}, //20, 当前周期电量                  (N)
//  {0x000B0001, 0x3E}, //21, 上1周期电量                   (N)

};
const   uint8 code guc_LenOfTabConvent = sizeof(gCs_TabConvent) / sizeof(S_IDTAB);



const   S_IDTAB code gCs_TabConvCS[]=
{
    {0x04000101, 0x15}, //日期星期
    {0x04000102, 0x16}, //时间
    {0x04000401, 0x17}, //通讯地址 占用2屏
    {0x04000402, 0x19}, //表号 占用2屏
    {0x0400040E, 0x1b}, //客户编号 占用2屏
    {0x04000409, 0x1d}, //常数
    {0x04000B01, 0x1e}, //结算日1
    {0x04000B02, 0x1f}, //结算日2
    {0x04000B03, 0x20}, //结算日3

};
const   uint8 code guc_LenOfTabConvCS = sizeof(gCs_TabConvCS) / sizeof(S_IDTAB);
const   S_IDTAB code gCs_TabConvBL[]=
{
    {0x02010100, 0x21}, // 电压
    {0x02020100, 0x22}, // 电流
    {0x02030000, 0x23}, // 总功率
    {0x02030100, 0x23}, // 总功率
    {0x02060000, 0x24}, // 功率因素
    {0x02060100, 0x24}, // 功率因素
    {0x02800001, 0x25}, // 零线电流
    {0x02800008, 0x26}, // 电池电压
};
const   uint8 code guc_LenOfTabConvBL = sizeof(gCs_TabConvBL) / sizeof(S_IDTAB);
const S_DISPCONT code gCs_DispTab[]=
{
    { 0x0000,  0x00,},   //0,  全屏显示

    { 0x0001, 0x43,}, //1,  当前电量总                (N)
    { 0x0002, 0x43,}, //2,  当前电量尖                (N)
    { 0x0003, 0x43,}, //3,  当前电量峰                (N)
    { 0x0004, 0x43,}, //4,  当前电量平                (N)
    { 0x0005, 0x43,}, //5,  当前电量谷                (N)

//  { 0x0006, 0x43,}, //6,  当前正有功电量总                (N)
//  { 0x0007, 0x43,}, //7,  当前正有功电量尖                (N)
//  { 0x0008, 0x43,}, //8,  当前正有功电量峰                (N)
//  { 0x0009, 0x43,}, //9,  当前正有功电量平                (N)
//  { 0x000a, 0x43,}, //10, 当前正有功电量谷                (N)
//
//  { 0x0006, 0x43,}, //11,  当前反有功电量总                (N)
//  { 0x0007, 0x43,}, //12,  当前反有功电量尖                (N)
//  { 0x0008, 0x43,}, //13,  当前反有功电量峰                (N)
//  { 0x0009, 0x43,}, //14,  当前反有功电量平                (N)
//  { 0x000a, 0x43,}, //15,  当前反有功电量谷                (N)

    { 0x0106, 0x43,}, //6,  上1月电量总               (N)
    { 0x0107, 0x43,}, //7,  上1月电量尖               (N)
    { 0x0108, 0x43,}, //8,  上1月电量峰               (N)
    { 0x0109, 0x43,}, //9,  上1月电量平               (N)
    { 0x010a, 0x43,}, //10,  上1月电量谷               (N)

//  { 0x0110, 0x43,}, //21,  上1月正有功电量总               (N)
//  { 0x0111, 0x43,}, //22,  上1月正有功电量尖               (N)
//  { 0x0112, 0x43,}, //23,  上1月正有功电量峰               (N)
//  { 0x0113, 0x43,}, //24, 上1月正有功电量平               (N)
//  { 0x0114, 0x43,}, //25, 上1月正有功电量谷               (N)
//
//  { 0x0110, 0x43,}, //26,  上1月反有功电量总               (N)
//  { 0x0111, 0x43,}, //27,  上1月反有功电量尖               (N)
//  { 0x0112, 0x43,}, //28,  上1月反有功电量峰               (N)
//  { 0x0113, 0x43,}, //29, 上1月反有功电量平               (N)
//  { 0x0114, 0x43,}, //30, 上1月反有功电量谷               (N)

    { 0x0206, 0x43,}, //11, 上2月组合有功电量总               (N)
    { 0x0207, 0x43,}, //12, 上2月组合有功电量尖               (N)
    { 0x0208, 0x43,}, //13, 上2月组合有功电量峰               (N)
    { 0x0209, 0x43,}, //14, 上2月组合有功电量平               (N)
    { 0x020a, 0x43,}, //15, 上2月组合有功电量谷               (N)

//  { 0x0210, 0x43,}, //36, 上2月正有功电量总               (N)
//  { 0x0211, 0x43,}, //37, 上2月正有功电量尖               (N)
//  { 0x0212, 0x43,}, //38, 上2月正有功电量峰               (N)
//  { 0x0213, 0x43,}, //39, 上2月正有功电量平               (N)
//  { 0x0214, 0x43,}, //40, 上2月正有功电量谷               (N)
//
//  { 0x0210, 0x43,}, //41, 上2月反有功电量总               (N)
//  { 0x0211, 0x43,}, //42, 上2月反有功电量尖               (N)
//  { 0x0212, 0x43,}, //43, 上2月反有功电量峰               (N)
//  { 0x0213, 0x43,}, //44, 上2月反有功电量平               (N)
//  { 0x0214, 0x43,}, //45, 上2月反有功电量谷               (N)

    { 0x0306, 0x43,}, //16, 上3月组合有功电量总               (N)
    { 0x0307, 0x43,}, //17, 上3月组合有功电量尖               (N)
    { 0x0308, 0x43,}, //18, 上3月组合有功电量峰               (N)
    { 0x0309, 0x43,}, //19, 上3月组合有功电量平               (N)
    { 0x030a, 0x43,}, //20, 上3月组合有功电量谷               (N)

//  { 0x0310, 0x43,}, //51, 上3月正有功电量总               (N)
//  { 0x0311, 0x43,}, //52, 上3月正有功电量尖               (N)
//  { 0x0312, 0x43,}, //53, 上3月正有功电量峰               (N)
//  { 0x0313, 0x43,}, //54, 上3月正有功电量平               (N)
//  { 0x0314, 0x43,}, //55, 上3月正有功电量谷               (N)
//
//  { 0x0310, 0x43,}, //56, 上3月反有功电量总               (N)
//  { 0x0311, 0x43,}, //57, 上3月反有功电量尖               (N)
//  { 0x0312, 0x43,}, //58, 上3月反有功电量峰               (N)
//  { 0x0313, 0x43,}, //59, 上3月反有功电量平               (N)
//  { 0x0314, 0x43,}, //60, 上3月反有功电量谷               (N)

//  { 0x0001, 0x43,}, //21当前周期电量               (N)
//  { 0x010b, 0x43,}, //22上月周期电量            (N)
    
    { 0x0000, 0x01,}, //21, 日期及星期
    { 0x0000, 0x02,}, //22, 时间

    { 0x0000, 0x13,}, //23, 通讯地址高4位
    { 0x0000, 0x00,}, //24, 通讯地址低8位

    { 0x001c, 0x13,}, //25, 表号高4位
    { 0x001c, 0x00,}, //26, 表号低8位


    { 0x001d, 0x13,}, //27, 客户编号高4位
    { 0x001d, 0x00,}, //28, 客户编号低8位


    {0x001b, 0x80},   //29常数
    {0x0000, 0x0b},   //30结算日1
    {0x0000, 0x0b},   //31结算日2
    {0x0000, 0x0b},   //32结算日3

    { 0x001e, 0x84,}, //33, 电压
    { 0x001f, 0x85,}, //34, 电流
    { 0x0021, 0x86,}, //35, 总功率
    { 0x0000, 0x87,}, //36, 功率因素
    { 0x0020, 0x85,}, //37, 零线电流
    { 0x0000, 0x88,}, //38, 电池电压
    
    { 0x0000, 0x12,}, //39, 编程日期
    { 0x0000, 0x02,}, //40, 编程时间
    { 0x0000, 0x12,}, //41, 校表日期
    { 0x0000, 0x11,}, //42, 校表时间
};


const S_IDTAB code gCs_TabAdd[]=
{
    {0x03300001, 0x27}, //编程时间 占用2屏
    {0x03300401, 0x29}, //校时时间 占用2屏
};
const uint8 code guc_LenOfTabAdd = sizeof(gCs_TabAdd) / sizeof(S_IDTAB);

#else
extern const   S_IDTAB code gCs_TabConvent[];
extern const   uint8 code guc_LenOfTabConvent;
extern const   S_IDTAB code gCs_TabConvBL[];
extern const   uint8 code guc_LenOfTabConvBL;
extern const   S_IDTAB code gCs_TabConvCS[];
extern const   uint8 code guc_LenOfTabConvCS;
#endif


// 单位小数点表
/*
*低半字节的：显示符号（等于某个值即显示对应的符号）
*其余几位的显示情况：显示小数点（对应位等于1：显示，否则不显示）
*/
enum
{//单位表
    UNIT_NONE,          //0x00
    UNIT_KWH,           //0x01
    UNIT_KW,            //0x02
//    UNIT_CS,            //0x06
//    UNIT_Yuan,          //0x03
//  UNIT_Jine,          //0x04
//  UNIT_BH,            //0x05
//  UNIT_TIME,          //0x07
//  UNIT_SD,            //0x08
//  UNIT_SQ,            //0x09
//  UNIT_SY,            //0x0a
//  UNIT_JT,            //0x0b
//  UNIT_V,             //0x0c
//  UNIT_A,             //0x0d
//  UNIT_PF,            //0x0e
};

/*
1.XSBP8258屏
                          DP10            DP9             DP8
             ____    ____    ____    ____    ____    ____    ____    ____
            |    |  |    | .|    |  |    | .|    |  |    | .|    |  |    |
            |____|  |____|  |____|  |____|  |____|  |____|  |____|  |____|
            |    |  |    | .|    |  |    | .|    |  |    | .|    |  |    |
            |____|. |____|. |____|. |____| .|____|. |____| .|____| .|____|
                DP1      DP2      DP3     DP4     DP5     DP6     DP7
*/

//定义实际使用到的小数点,用于建立小数点和单位符号表
#define _P1     0x0010
#define _P2     0x0020
#define _P3     0x0040
#define _P4     0x0080
#define _P5     0x0100
#define _P6     0x0200
#define _P7     0x0400
#define _P8     0x0800
#define _P9     0x1000
#define _P10    0x2000
#define _PFu    0x4000


//程序处理用小数点宏定义
#define Point_D1 _P7                //对应第2位数后面的小数点,后面跟1位小数
#define Point_D2 _P6                //对应第3位数后面的小数点,后面跟2位小数
#define Point_D3 _P5                //对应第3位数后面的小数点,后面跟3位小数
#define Point_D4 _P4                //对应第5位数后面的小数点,后面跟4位小数
#define Point_D6 _P2                //对应第7位数后面的小数点,后面跟6位小数
#define Point_Fu _PFu                //数字前面的负号

#ifdef LCDSHOWSELF
const   uint16 code gCui_UnitPointTab[]=
{
    0x0000,                 //0x00.不显示,如显示表号等无单位小数点的信息时使用
    _P4+_P6,                //0x01.日期(XX.XX.XX  X)
    _P4+_P6+_P8+_P9,        //0x02.时间(XX:XX:XX)
    UNIT_KWH,               //0x03.正向电量类,默认不显示小数点,由E2中读取的小数点位数决定,在显示处理函数中组织完成
    _P7,                    //0x04.电压(X.X  V)
    _P5,                    //0x05.电流(X.XXX A)
    UNIT_KW,            //0x06.有功功率或需量(X.XXXXX kW)
    _P5,//    _P5+UNIT_CS,            //0x07.功率因素(X.XXX,cos￠)
    _P6,                    //0x08.二位小数(XX.XX)
    _P4+_P6,                //0x09.XX.XX.XX 年月日 或 日月时
    _P4,                    //0x0A.XXXX.XXXX
    _P6,                    //0x0b 结算日 XX.XX
    0x0000,                 //0x0c
    0x0000,                 //0x0d
    0x0000,                 //0x0e
    0x0000,                 //0x0f
    0x0000,                 //0x10
    _P4+_P6+_P8+_P9,        //0x11
    _P4+_P6,                //0x12
    0x0000,                 //0x13
};
#endif

#define MacIsDispEnerg ((ucType == 0x16) || (ucType == 0x03))
#define _SW_ISNEEDNEGDISP   0       //是否需要负号显示功能

typedef struct s_ptmsk
{
    uint16  uiPtMsk;    //对应小数点的屏蔽位
    uint8   ucNum;      //小数点对应第几个位置
    uint8   reserved;   //保留
}S_PTMSK;

#ifdef LCDSHOWSELF
const S_PTMSK code gCs_szPtMskTab[] =
{
    {Point_D6, 6, 0x00},
    {Point_D4, 4, 0x00},
    {Point_D3, 3, 0x00},
    {Point_D2, 2, 0x00},
    {Point_D1, 1, 0x00},
};

#endif

typedef struct s_dispsttbit
{
    uint8*  pucDst;     //目的状态字
    uint8*  pucSrc;     //源状态字
    uint8   ucDstMsk;   //目的状态字的位,其值大小为BIT0 - BIT7
    uint8   ucSrcMsk;   //源状态字的位定义,其值大小为BIT0 - BIT7
    uint8   ucAtb;      //属性
    uint8   ucOffset;   //偏移,用于查子表时的偏移指针
}S_DISPSTTBIT;


#define __SW_BLINK_DISP__  1            //闪烁位控制

enum
{
    Const_Disp_KeyUp = 0,
    Const_Disp_KeyDn,
    Const_Disp_RmtUp,       //遥显上翻屏
    Const_Disp_RmtDn,       //遥显下翻屏
};

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
void ShowKeyManage(uint8 ucType);
void ShowSecondProc(void);
uint8 ShowDataProc(void);
void ShowRefresh(void);
void SleepDispInit(void);
uint8 SleepDisp(void);
uint8 SearchDispNO(Word32 ulID);
void ShowStateManage(void);
void ShowStateFlashManage(void);

#endif