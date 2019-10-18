#define	AP_1107_EXT
#include "Include.h"
struct            ST645CommTimeFormat
{
    unsigned char               cSec;
    unsigned char               cMin;
    unsigned char               cHour;
    unsigned char               cDay;
    unsigned char               cMonth;
    unsigned char               cYear;
};

const uint8 code guc_PcComEd[]=
{
    AS_SOH, 'B','0',AS_ETX,//0x71
};//SOH,B0,ETX,

const uint8 code guc_WROBS[]=
{
    AS_SOH,'W',0xaa,AS_STX
};//SOH W1 STX

const uint8 code guc_RdOBS[]=
{
    AS_SOH,'R','2',AS_STX
};//SOH R1 STX

const uint8 code guc_Frmhd[]=
{   
  '/','?','!','\r','\n'         //"/?!CRLF"
};

const uint8 code guc_FrmADrrhd[]=
{   
  '/','?',0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,'!','\r','\n'         //"/?xxxxxx!CRLF"
};
 #define                 _defbps_    _bps300_
//#define                 _defbps_    _bps2400_
const uint8 code guc_BpsCheck[]=
{
    '/','L','U','N',0x30+_defbps_,'<','1','>','L','U','N','1','0',//'0','0','0','\r','\n'
};//回复识别帧头，确定波特率

const uint8 code guc_ACKHd1[6]=
{
    AS_ACK,'0',0x30+_defbps_,0xAA,'\r','\n'
};//ACK 0 Z（3）2400BPS 

const uint8 code  guc_PgAck[]=
{
    AS_SOH,'P','0',AS_STX,'(',')',AS_ETX,0x60,
};//SOH P0 STX () ETX 

const uint8 code guc_PgPCAck[]=
{
    AS_SOH,'P',0xaa,AS_STX,'(',0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,')',AS_ETX
};//SOH PX STX(XXXXXX)ETX

//const string code guc_OwId[]=
//{
//    "VANGO",
//};

const uint8 code guc_InitCmd[]=
{
    AS_SOH,'V','G',AS_STX,'C','L','R','-','0','0',AS_ETX,0x60,
};

#define BE_ReadP(a,b,c)   {}  //gs_E2DataTable[index].uiE2Adrr,ASCII,8);
#define  EnyB_IBAutoCheck()   {}  //g
#define  EnyB_AutoChkAngle()   {}  //g
#define   _ReadBodyOpOrMdTrDate_time_           0xfe 
/*=========================================================================================\n
* @function_name: gs_OBSCom
* @function_file: Ptl_1107.c
* @描述: 通讯显示 标识核心表
* 
* @参数: 
* @返回: 
* @作者: Lwb (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
    
    
    
const char as[]="";
const GS_IECCOM    gs_OBSCom[]=
{   //obsi              uint             param     atb           pfindex  

    //当前电量 
    { "1.8.0",          "*kWh)\r\n",    _code645_00000000_,       IEC_RO,       _ReadCurEgy_},
    { "1.8.1",          "*kWh)\r\n",    _code645_00010000_-_code645_00000000_,       IEC_RO,     _ReadCurEgy_},
    { "1.8.2",          "*kWh)\r\n",    _code645_00020000_-_code645_00000000_,       IEC_RO,     _ReadCurEgy_},
    //{ "1.8.3",          "*kWh)\r\n",     _code645_00010000-_code645_00000000,      IEC_RO,     _ReadCurEgy_},
    //{ "1.8.4",          "*kWh)\r\n",     _code645_00020000-_code645_00000000,      IEC_RO,     _ReadCurEgy_},

 
    //上1月电量
    { "1.8.0*1",        "*kWh)\r\n",    _code645_00000001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*1",        "*kWh)\r\n",    _code645_00010001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*1",        "*kWh)\r\n",    _code645_00020001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*1",        "*kWh)\r\n",    0x03,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*1",        "*kWh)\r\n",    0x04,       IEC_RO,     _ReadHisEgy_},

    //上2月电量
    { "1.8.0*2",        "*kWh)\r\n",    _code645_00000002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*2",        "*kWh)\r\n",    _code645_00010002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*2",        "*kWh)\r\n",    _code645_00020002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
   // { "1.8.3*2",        "*kWh)\r\n",    0x13,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*2",        "*kWh)\r\n",    0x14,       IEC_RO,     _ReadHisEgy_},


    //上3月电量
    { "1.8.0*3",        "*kWh)\r\n",    _code645_00000003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*3",        "*kWh)\r\n",    _code645_00010003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*3",        "*kWh)\r\n",    _code645_00020003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*3",        "*kWh)\r\n",    0x23,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*3",        "*kWh)\r\n",    0x24,       IEC_RO,     _ReadHisEgy_},

    //上4月电量
    { "1.8.0*4",        "*kWh)\r\n",    _code645_00000004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*4",        "*kWh)\r\n",    _code645_00010004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*4",        "*kWh)\r\n",    _code645_00020004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*4",        "*kWh)\r\n",    0x33,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*4",        "*kWh)\r\n",    0x34,       IEC_RO,     _ReadHisEgy_},

    //上5月电量
    { "1.8.0*5",        "*kWh)\r\n",    _code645_00000005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*5",        "*kWh)\r\n",    _code645_00010005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_}, 
    { "1.8.2*5",        "*kWh)\r\n",    _code645_00020005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*5",        "*kWh)\r\n",    0x43,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*5",        "*kWh)\r\n",    0x44,       IEC_RO,     _ReadHisEgy_},

    //上6月电量
    { "1.8.0*6",        "*kWh)\r\n",    _code645_00000006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*6",        "*kWh)\r\n",    _code645_00010006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*6",        "*kWh)\r\n",    _code645_00020006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*6",        "*kWh)\r\n",    0x53,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*6",        "*kWh)\r\n",    0x54,       IEC_RO,     _ReadHisEgy_},

    //上7月电量
    { "1.8.0*7",        "*kWh)\r\n",    _code645_00000007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*7",        "*kWh)\r\n",    _code645_00010007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*7",        "*kWh)\r\n",    _code645_00020007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*7",        "*kWh)\r\n",    0x63,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*7",        "*kWh)\r\n",    0x64,       IEC_RO,     _ReadHisEgy_},

    //上8月电量
    { "1.8.0*8",        "*kWh)\r\n",    _code645_00000008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*8",        "*kWh)\r\n",    _code645_00010008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*8",        "*kWh)\r\n",    _code645_00020008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*8",        "*kWh)\r\n",    0x73,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*8",        "*kWh)\r\n",    0x74,       IEC_RO,     _ReadHisEgy_},

    //上9月电量
    { "1.8.0*9",        "*kWh)\r\n",    _code645_00000009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*9",        "*kWh)\r\n",    _code645_00010009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*9",        "*kWh)\r\n",    _code645_00020009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*9",        "*kWh)\r\n",    0x83,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*9",        "*kWh)\r\n",    0x84,       IEC_RO,     _ReadHisEgy_},

    //上10月电量
    { "1.8.0*10",       "*kWh)\r\n",    _code645_0000000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*10",       "*kWh)\r\n",    _code645_0001000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*10",       "*kWh)\r\n",    _code645_0002000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*10",       "*kWh)\r\n",    0x93,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*10",       "*kWh)\r\n",    0x94,       IEC_RO,     _ReadHisEgy_},

    //上11月电量
    { "1.8.0*11",       "*kWh)\r\n",    _code645_0000000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*11",       "*kWh)\r\n",    _code645_0001000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*11",       "*kWh)\r\n",    _code645_0002000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*11",       "*kWh)\r\n",    0xA3,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*11",       "*kWh)\r\n",    0xA4,       IEC_RO,     _ReadHisEgy_},

    //上12月电量
    { "1.8.0*12",       "*kWh)\r\n",    _code645_0000000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*12",       "*kWh)\r\n",    _code645_0001000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*12",       "*kWh)\r\n",    _code645_0002000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*12",       "*kWh)\r\n",    0xB3,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*12",       "*kWh)\r\n",    0xB4,       IEC_RO,     _ReadHisEgy_},


    {"1.6.0",           ")",            0x00,       IEC_RO,     0x02},    //当前最大需量及发生时间
    {"1.6.0*1",         ")",            0x10,       IEC_RO,     0x02},    //上1次最大需量及发生时间
    {"1.6.0*2",         ")",            0x20,       IEC_RO,     0x02},    //上2次最大需量及发生时间
    {"1.6.0*3",         ")",            0x30,       IEC_RO,     0x02},    //上3次最大需量及发生时间
    {"1.6.0*4",         ")",            0x40,       IEC_RO,     0x02},    //上4次最大需量及发生时间
    {"1.6.0*5",         ")",            0x50,       IEC_RO,     0x02},    //上5次最大需量及发生时间
    {"1.6.0*6",         ")",            0x60,       IEC_RO,     0x02},    //上6次最大需量及发生时间
    {"1.6.0*7",         ")",            0x70,       IEC_RO,     0x02},    //上7次最大需量及发生时间
    {"1.6.0*8",         ")",            0x80,       IEC_RO,     0x02},    //上8次最大需量及发生时间
    {"1.6.0*9",         ")",            0x90,       IEC_RO,     0x02},    //上9次最大需量及发生时间
    {"1.6.0*10",        ")",            0xA0,       IEC_RO,     0x02},    //上10次最大需量及发生时间
    {"1.6.0*11",        ")",            0xB0,       IEC_RO,     0x02},    //上11次最大需量及发生时间
    {"1.6.0*12",        ")",            0xC0,       IEC_RO,     0x02},    //上12次最大需量及发生时间


    //事件
    {"96.70",           ")",            _ReadBodyOpOrMdTrDate_time_,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //开表盖时间

    {"96.71",           ")",            0,         IEC_RO,     _ReadBodyOpOrMdTrDate_},    //开端钮盖时间及次数
    {"96.71*1",         ")",            0x1,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上1次开端钮盖时间及次数
    {"96.71*2",         ")",            0x2,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上2次开端钮盖时间及次数
    {"96.71*3",         ")",            0x3,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上3次开端钮盖时间及次数
    {"96.71*4",         ")",            0x4,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上4次开端钮盖时间及次数
    {"96.71*5",         ")",            0x5,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上5次开端钮盖时间及次数
    {"96.71*6",         ")",            0x6,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上6次开端钮盖时间及次数
    {"96.71*7",         ")",            0x7,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上7次开端钮盖时间及次数
    {"96.71*8",         ")",            0x8,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上8次开端钮盖时间及次数
    {"96.71*9",         ")",            0x9,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上9次开端钮盖时间及次数
    {"96.71*10",        ")",            0xa,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上10次开端钮盖时间及次数
    {"96.71*11",        ")",            0xb,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上11次开端钮盖时间及次数
    {"96.71*12",        ")",            0xc,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //上12次开端钮盖时间及次数

    {"96.7.1",          ")",      _code645_03110000_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //掉电总次数
    {"96.77.1*1",       ")",      _code645_03110001_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上1次掉电时间和结束时间
    {"96.77.1*2",       ")",      _code645_03110002_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上2次掉电时间和结束时间
    {"96.77.1*3",       ")",      _code645_03110003_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上3次掉电时间和结束时间
    {"96.77.1*4",       ")",      _code645_03110004_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上4次掉电时间和结束时间
    {"96.77.1*5",       ")",      _code645_03110005_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上5次掉电时间和结束时间
    {"96.77.1*6",       ")",      _code645_03110006_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上6次掉电时间和结束时间
    {"96.77.1*7",       ")",      _code645_03110007_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上7次掉电时间和结束时间
    {"96.77.1*8",       ")",      _code645_03110008_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上8次掉电时间和结束时间
    {"96.77.1*9",       ")",      _code645_03110009_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上9次掉电时间和结束时间
    {"96.77.1*10",      ")",      _code645_0311000A_- _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上10次掉电时间和结束时间
    //{"96.77.1*11",      ")",      _code645_03110000_ _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上11次掉电时间和结束时间
    //{"96.77.1*12",      ")",      _code645_03110000_ _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //上12次掉电时间和结束时间

    //表号
    {"0.0.0",           ")",            0x00,       IEC_RW,     _E2DataProc_},
    {"96.97.1",         ")",            0x01,       IEC_RW,     _E2DataProc_},    //写入结算日1
    {"96.97.2",         ")",            0x02,       IEC_RW,     _E2DataProc_},    //写入结算日2
    {"96.97.3",         ")",            0x03,       IEC_RW,     _E2DataProc_},    //写入结算日3
    {"0.8.0",           "*min)",        0x04,       IEC_RW,     _E2DataProc_},    //需量周期
    {"96.1.3",          ")",            0x05,       IEC_RO,     _E2DataProc_},    //生产日期
    {"96.2.5",          ")",            0x06,       IEC_RO,     _E2DataProc_},    //校表日期
    {"96.2.2",          ")",            0x07,       IEC_RO,     _E2DataProc_},    //费率修改日期
    {"96.8.0",          "*min)",        0x08,       IEC_RW,     _E2DataProc_},    //负荷记录周期

    {"96.96.1",         ")",            0x09,       IEC_WO,     _E2DataProc_},    //写入P1密码
    {"96.96.2",         ")",            0x0A,       IEC_WO,     _E2DataProc_},    //写入P2码

    {"96.6.1",          ")",            0x0b,       IEC_RO,     _E2DataProc_},    //电表状态字

    {"96.50",          ")",             0x0C,       IEC_RW,     _E2DataProc_},    //工作日费率时间
    {"96.51",          ")",             0x0D,       IEC_RW,     _E2DataProc_},    //工作日费率时间
    {"96.52",          ")",             0x0E,       IEC_RW,     _E2DataProc_},    //工作日费率时间


    {"96.60",          ")",             0x0F,       IEC_RW,     _E2DataProc_},    //工作日费率
    {"96.61",          ")",             0x10,       IEC_RW,     _E2DataProc_},    //工作日费率
    {"96.62",          ")",             0x11,       IEC_RW,     _E2DataProc_},    //工作日费率


    { "0.9.1",          ")",            0x01,       IEC_RW,     _DateAndTimeProc_},    //时间

    { "0.9.2",          ")",            0x00,       IEC_RW,     _DateAndTimeProc_},    //日期

    { "0.9.5",          ")",            0x02,       IEC_RW,     _DateAndTimeProc_},    //星期

    
    {"32.7.0",          "*V)",          0x01,       IEC_RO,     _ReadInsData_},    //电压
    {"31.7.0",          "*A)",          0x02,       IEC_RO,     _ReadInsData_},    //电流
    
    //清零命令
    {"FF.0.0",          ")",            0x00,       IEC_WO,     0x08},
    {"FF.0.1",          ")",            0x01,       IEC_WO,     0x09},
 
};

const uint8 code Cosnt_OBSLen=dim(gs_OBSCom);
/*=========================================================================================\n
* @function_name: gs_OBSFuction
* @function_file: Ptl_1107.c
* @描述: 通讯显示处理函数列表
* 
* @参数: 
* @返回: 
* @作者: Lwb (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
 const PFOBSProc code gs_OBSFuction[]=
{
    ReadCurEgy,                 //读取当前有功电量   0
    ReadHisEgy,                 //读取历史有功电量   1
    ReadHisDemad,               //读取历史需量      2
    ReadBodyOpOrMdTrDate,       //开表盖和线盖事件   3
    ReadPowDnJl,                //掉电记录         4
    E2DataProc,                 //读取E2数据       5
    DateAndTimeProc,            //读取日期和时间    6 
    ReadInsData,                //读取瞬时数据      7
    ClearMeterProc,             //清零电量处理      8
    AutoJB,                     //自动校表

};
 
const  uint8 code ConstOBSFunCnt=dim(gs_OBSFuction);  

/*=========================================================================================\n
* @function_name: CmpStr
* @function_file: Ptl_1107.c
* @描述: 比较字符串是否正确，如果被比较的位置不是0xaa
*        并且不相等的话，返回错误
* 
* 
* @参数： 
* @param:cmped  
* @param:cmp  
* @param:len  
* 
* @返回： 
* @return: uint8 
* @作者: Lwb (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
uint8 CmpStr(uint8* cmped,const uint8 code * cmp,uint16 len)
{
	uint8 i;
    for(i=0;i<len;i++)
    {
        if(cmped[i]!=cmp[i]
		&&((uint8)cmp[i]!=0xAA))	 //这里不强制转化,比较字符和uint8会不对 
        {
            return Ret_Err;
        }
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: FindObsiPoint
* @function_file: Ptl_1107.c
* @描述: 在通讯核心表中查找对应OBSI码的位置，有对应的OBSI 返回位置，否则返回0XFF
* 
* 
* @参数: 
* @param:Obsi  通讯或者显示表对应的OBSI
* @param:len   OBSI码对应的长度
* 
* @返回: 
* @return: uint8 返回OBSI码的位置
* @作者: Lwb (2011-8-29)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 FindObsiPoint(uint8* Obsi,uint8 len)
{
    uint8 i;
    for(i=0;i<Cosnt_OBSLen;i++)
    {
        if(ApiCodeBufCmp((uint8 code  *)gs_OBSCom[i].pOBS,(uint8   *)Obsi,len)==CMP_EQU)//比较字符串
        {
            return i;
        }
    }
    return 0xff;   
}
/*=========================================================================================\n
* @function_name: CalBCC
* @function_file: Ptl_1107.c
* @描述: 计算数据帧中的BCC
* 
* 
* @参数： 
* @param:OrgBCC  原始BCC
* @param:Data  输入计算的数据
* @param:len  输入计算的数据长度
* 
* @返回： 
* @return: uint8  返回的计算后的BCC
* @作者: Lwb (2011-9-5)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
uint8 CalBCC(uint8 OrgBCC, uint8 *Data,uint8 len)
{
	uint8 i;
    for(i=0;i<len;i++)
    {
        OrgBCC^=Data[i];
    }
    return OrgBCC;
}
/*=========================================================================================\n
* @function_name: DateFormat
* @function_file: Ptl_1107.c
* @描述: 日期、时间处理
* 
* 
* @参数： 
* @param:op     0-- 日期  1--时间
* @param:Ascii  输入的日期或者时间的ASC
* @返回： 
* @作者: Lwb (2011-9-5)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void DateFormat(uint8 op,uint8 *ASCII)
{

    ASCII[7]=ASCII[5];      //秒或者日
    ASCII[6]=ASCII[4];

    ASCII[4]=ASCII[3];      //分或者月
    ASCII[3]=ASCII[2];


    if(op==0)               //日期还是时间格式
    {
        ASCII[5]='-';
        ASCII[2]='-';
    }else 
    {
        ASCII[5]=':';
        ASCII[2]=':';
    }
}
/*=========================================================================================\n
* @function_name: DateAndTmFormat
* @function_file: Ptl_1107.c
* @描述: 日期和时间格式处理，年月日时分更改成 年-月-日,时:分
* 
* 
* @参数： 
* @param:ASCII  
* @返回: 
* @作者: Lwb  (2011-9-5)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
void DateAndTmFormat(uint8 *ASCII)
{
    ASCII[13]=ASCII[9];     //分
    ASCII[12]=ASCII[8];

    ASCII[10]=ASCII[7];     //时
    ASCII[9]=ASCII[6];

    ASCII[7]=ASCII[5];     //日
    ASCII[6]=ASCII[4];

    ASCII[4]=ASCII[3];      //月
    ASCII[3]=ASCII[2];

    //年位置正确
                            //日期还是时间格式
    ASCII[5]='-';
    ASCII[2]='-';
    ASCII[8]=',';
    ASCII[11]=':';
}
/*=========================================================================================\n
* @function_name: DataorTmCpy
* @function_file: Ptl_1107.c
* @描述: 处理日期时间，去掉日期和时间格式中的-或者:,例如11-09-12变成 110912
* 
* 
* @参数: 
* @param:Ascii     处理后的日期和时间的ascii码
* @param:OrgAscii  未处理的日期和时间格式
* @返回: 
* @作者:   Lwb (2011-9-15)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void DataorTmCpy(uint8 *Ascii,uint8* OrgAscii)
{
    Ascii[0]=OrgAscii[0];      //年   时

    Ascii[1]=OrgAscii[1];

    Ascii[2]=OrgAscii[3];     //月   分

    Ascii[3]=OrgAscii[4];
    
    Ascii[4]=OrgAscii[6];     //日  秒
    
    Ascii[5]=OrgAscii[7];
}
/*=========================================================================================\n
* @function_name: JudgeOBSPsw
* @function_file: Ptl_1107.c
* @描述: 判断密码是否正确
* 
* 
* @参数： 
* @param:buff  
* @param:type  
* 
* @返回： 
* @return: uint8 
* @作者: Lwb  (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
uint8 JudgeOBSPsw(uint8 *buff,uint8 ucLevel)
{
    uint32 E2Adrr;
	uint8 i;
    uint8 PassWord[8];
#ifdef PX_OPT
    if(ucLevel>0x02)
    {
        return Ret_Err;
    }
    E2Adrr=EEP_RDPASSWORD+(ucLevel-1)*8;
    BE_ReadP(E2Adrr,PassWord,8);

    for(i=0;i<8;i++)
    {
        if(buff[i]!=PassWord[i])
        {
            break;
        }
    }
    
    if(i>=8)
    {
         return Ret_OK;                         //返回密码正确
    }else
    {//如果密码错误
        return Ret_Err;                         //返回密码不正确
    }
#endif
   return Ret_OK;                         //返回密码正确
}
/*=========================================================================================\n
* @function_name: ReadCurEgy
* @function_file: Ptl_1107.c
* @描述: 读取有功电量
* 
* 
* @参数： 
* @param:index  0~4，总、费率1~4
* @param:cmd    Const_DataCom-通讯、Const_DataDisp—显示
* @param:pvoid  读取数据缓存
* 
* @返回： 
* @return: uint32 数据长度
* @作者: Lwb  (2011-9-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/

uint32 ReadCurEgy(uint8 index,uint8 cmd,void *pvoid)
{
    char        ctemp;
    Word32 Data;
    int16 Eadd;
    uint8 ASCII[9];
    strDispCode  pCode = { 0x0000000 ,0};
    //取得某个电量增量
    switch ( index)
    {
    case   _code645_00000000_ - _code645_00000000_ :
          pCode.Code = 0x0 ;
          break;
    case   _code645_00010000_- _code645_00000000_ :
          pCode.Code = 0x00010000;
          break;
    case     _code645_00020000_- _code645_00000000_ :
        pCode.Code =0x00020000;
        break;
        
    } 
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );    
    RamData.InDisp = ctemp;    
    
    //Eadd = Eny_GetEp1(0, index);    
    //Data.lword =  gs_EnergyA.lCP[index]; 
    //Data.lword += Eadd;
    //Data.lword =123456;
    Data.lword = *((uint32 *)ComData);
    if ( Data.lword & 0x80000000)
        Data.lword &=0x7fffffff;
    Data.lword= Hex2BCD(Data.lword);        //首先转化为BCD码
    BCD2ASCII(Data.byte,ASCII,4);
    MemCpy(pvoid,ASCII,5);
    ((uint8*)pvoid)[5]='.';
    MemCpy(((uint8*)pvoid)+6,ASCII+5,3);
    return 9;
}

/*=========================================================================================\n
* @function_name: ReadHisEgy
* @function_file: Ptl_1107.c
* @描述: 读取历史电量
* 
* 
* @参数： 
* @param:index  高4位是月份，低4位是费率号
* @param:cmd    Const_DataCom-通讯、Const_DataDisp—显示
* @param:pvoid  读取数据缓存
* 
* @返回： 
* @return: uint32 
* @作者: Lwb (2011-9-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/

uint32 ReadHisEgy(uint8 index,uint8 cmd,void *pvoid)
{
    char        ctemp,cMonth ,cType;
   // uint8 ucMonth=(0xf0&index)>>4;
    //uint8 offset=0x0f&index;
    Word32 Data;
    uint8 ASCII[9];
    //DataProcRead2Slice(LSDLID,ucMonth,offset*4,4,Data.byte);
     strDispCode  pCode = { 0x0000000 ,0};
    //取得某个电量增量
     cMonth = index /3;
     cType = index % 3;
     pCode.Code =  cType;
     pCode.Code <<=16;
       pCode.Code+= cMonth ;
     
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );
    RamData.InDisp = ctemp;    
    Data.lword = *((uint32 *)ComData);
     if ( Data.lword & 0x80000000)
        Data.lword &=0x7fffffff;
     
    Data.lword= Hex2BCD(Data.lword);    //首先转化为BCD码
    BCD2ASCII(Data.byte,ASCII,4);
    MemCpy(pvoid,ASCII,5);
    ((uint8*)pvoid)[5]='.';
    MemCpy(((uint8*)pvoid)+6,ASCII+5,3);
    return 9;
}
 
/*=========================================================================================\n
* @function_name: ReadHisDemad
* @function_file: Ptl_1107.c
* @描述: 读取历史需量
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @作者: lwb (2014/4/2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint32 ReadHisDemad(uint8 index,uint8 cmd,void *pvoid)
{
 
    uint8 ucMonth=(0xf0&index)>>4;
    uint8 offset=0x0f&index;
    Word32 Data;
    uint8 buff[8];
    uint8 ASCII[10];
  //opt   DataProcRead2Slice(LSXLID,ucMonth,offset*4,8,buff);
    Data.lword=0;
    MemCpy(Data.byte,buff,3);

    Data.lword= Hex2BCD(Data.lword);    //首先转化为BCD码
    BCD2ASCII(Data.byte,ASCII,3);

    MemCpy(pvoid,ASCII,3);
    ((uint8*)pvoid)[3]='.';
    MemCpy(((uint8*)pvoid)+4,ASCII+3,3);
    ((uint8*)pvoid)[7]='*';
    ((uint8*)pvoid)[8]='k';
    ((uint8*)pvoid)[9]='W';
    ((uint8*)pvoid)[10]=')';
    ((uint8*)pvoid)[11]='(';
    //(003.088*kW)(06-07-05,10:08)
    //日期

    BCD2ASCII(buff+3,ASCII,5);      //把日期转化成ASCii
    DateAndTmFormat(ASCII);         //转化日期和时间的格式
    MemCpy(((uint8*)pvoid)+12,ASCII,14);

    return 26;
}
/*=========================================================================================\n
* @function_name: DateAndTimeProc
* @function_file: Ptl_1107.c
* @描述: 读取日期和时间,星期
* 
* 
* @参数： 
* @param:index  
* @param:cmd    Const_DataCom-通讯、Const_DataDisp—显示
* @param:pvoid  读取数据缓存 
* 
* @返回： 
* @return: uint32 
* @作者: Lwb (2011-9-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:  
===========================================================================================*/
uint32 DateAndTimeProc(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucData[4];
    uint8 ASCII[8];
    uint8 len;
    uint8 DtorTm=0xff;
    if(Const_DataCOmWR!=cmd)
    {
        switch(index)
        {
        case 0x00:                                      //日期
        default:
            GetSysClock(ucData,Const_YYMMDD);
            DtorTm=0;
            len=3;
            break;
        case 0x01:                                      //时间
            GetSysClock(ucData,Const_hhmmss);
            DtorTm=1;
            len=3;
            break;
        case 0x02:                                      //星期
           ucData[0]=gs_DateTime.ucWeek+1;
           ucData[0]<<=4;
           len=1;
           break;
        }
    }
    else if(Const_DataCOmWR==cmd)                            //写
    {
        switch(index)
        {
        case 0x00:                                      //日期
        default:
            DataorTmCpy(ASCII,pvoid);
            ASCII2BCD(ucData,ASCII,6);
            SetSysClock(ucData,Const_YYMMDD);
            break;
        case 0x01:                                      //时间
            DataorTmCpy(ASCII,pvoid);
            ASCII2BCD(ucData,ASCII,6);
            SetSysClock(ucData,Const_hhmmss);
            break;
        case 0x02:                                      //星期
            ucData[0]=*(uint8*)pvoid-0x31;              //星期从1~7编程0~6
            SetSysClock(ucData,Const_WW);
            break;
        }
        gui_RefreshEvent|=flgEtPara_Fee;
        return 0;
    }

    BCD2ASCII(ucData,ASCII,len);
    len=1;
    if(DtorTm!=0xff)
    {
        DateFormat(DtorTm,ASCII);
        len=8;
    }
    MemCpy(pvoid,ASCII,len);
    return len;
}
/*=========================================================================================\n
* @function_name: ReadBodyOpOrMdTrDate
* @function_file: Ptl_1107.c
* @描述: 读取开表盖线盖事件
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @作者: lwb (2014/4/3)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/


uint32 ReadBodyOpOrMdTrDate(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 *ucbuf;//[10];
    uint8 ASCII[20];
    uint8 ucMonth=(0xf0&index)>>4;
    uint8 uctype=index;  //=0x0f&index;
   uint8 ctemp ;
   long  ltemp ;
    
    struct   ST645CommTimeFormat *stp =(struct   ST645CommTimeFormat *)ComData; 
    
    strDispCode  pCode = { 0x03300d01 ,0};
    
    if (   _ReadBodyOpOrMdTrDate_time_ != index ) 
             pCode.Code  += index ;
    
 tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );
    RamData.InDisp = ctemp;      
    if( _ReadBodyOpOrMdTrDate_time_ == uctype)                //读开表盖时间
    {
        ucbuf = &(stp->cMin); //opt      DataProcRead2Slice(KBGJLID, ucMonth, 0, 5, ucbuf); 
    }
    else                            //读开线盖时间和次数
    {
     //optv   DataProcRead2Slice(KXGJLID, ucMonth, 0, 6, ucbuf); 
      ucbuf = &(stp->cMin);    
    }      
 //   BCD2ASCII(&(stp->cMin),ASCII,5);               //把日期转化成ASCii
  //  DateAndTmFormat(ASCII);                 //转化日期和时间的格式
    //MemCpy(pvoid,ASCII,14);
    
    BCD2ASCII(&(stp->cMin),pvoid,5);               //把日期转化成ASCii
    DateAndTmFormat(pvoid);                 //转化日期和时间的格式
   // MemCpy(pvoid,ASCII,14);    
    if( _ReadBodyOpOrMdTrDate_time_ == uctype )                        //读开表盖时间
    {
        return 14;
    }
    else
    {
      ((uint8*)pvoid)[14]=')';
      ((uint8*)pvoid)[15]='(';        
      ltemp = GetFrozeCnt(_FROZE_EOPEN_1_) + (FlashInfo.FrozeCnt[_FROZE_EK_1_]&1)?1:0;      
      ltemp -= index ;
      ctemp = ( ltemp < 0) ? 0:ltemp;
      ctemp = BCD(ctemp) ;
      BCD2ASCII((char *)&ctemp,((uint8*)pvoid)+16,1); //    BCD2ASCII(ucbuf,ASCII+5,1);         //把日期转化成次数      
      return 18;
    }
 
}
/*=========================================================================================\n
* @function_name: DoNoting
* @function_file: Ptl_1107.c
* @描述: 保留，不做任何事情
* 
* 
* @参数： 
* @param:index  
* @param:cmd  
* @param:pvoid  
* 
* @返回： 
* @return: uint32 
* @作者: Lwb (2011-9-5)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint32 DoNoting(uint8 index,uint8 cmd,void *pvoid)
{
    index=index;
    cmd=cmd;
    pvoid=pvoid;
    return 0;
}
 
const GSE2DATA  code gs_E2DataTable[]=
{
    { ((unsigned short)&FlashInfo.SafeInfo.TRx_Num),      ASC2BCD,     4},     //表号         0x00
   
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[0][0]),        ASC2BCD,     2},     //结算日        0x01
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[1][0]),        ASC2BCD,     2},     //结算日        0x02
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[2][0]),        ASC2BCD,     2},     //结算日        0x03
 #ifdef PX_OPT
    { EEP_XLZQ,        ASC2BCD,     1},     //需量周期      0x04
    { EEP_MANUDATE,    ASC2BCD,     3},     //生产日期      0x05
    { EEP_JBDATE,      ASC2BCD,     3},     //校表日期      0x06
    { EEP_FEEMDATE,    ASC2BCD,     5},     //费率修改日期   0x07
    { EEP_FHQXZQ,      ASC2BCD,     1},     //负荷记录周期   0x08
    { EEP_RDPASSWORD,  0x00,        8},     //等级1密码     0x09
    { EEP_WRPASSWORD,  0x00,        8},     //等级2密码     0x0A
    { EEP_BATTERYSTAT, ASC2BCD,     1},     //电池状态      0x0b
    { EEP_WORK_FEE_TIME,ASC2BCD,    16},    //工作日费率时间 0x0c
    { EEP_SAT_FEE_TIME, ASC2BCD,    16},    //星期六费率时间 0x0d
    { EEP_SUN_FEE_TIME, ASC2BCD,    16},    //星期日费率时间 0x0e

    { EEP_WORK_FEE,     ASC2BCD,    4},     //工作日费率     0x0f
    { EEP_SAT_FEE,      ASC2BCD,    4},     //星期六费率     0x10
    { EEP_SUN_FEE,      ASC2BCD,    4},     //星期日费率     0x11
#endif
};

const  uint8 code ConstE2DataTableCnt=dim(gs_E2DataTable);
/*=========================================================================================\n
* @function_name: E2DataProc
* @function_file: Ptl_1107.c
* @描述: 读取指定E2地址和长度的数据
* 
* 
* @参数： 
* @param:index  E2地址和读取数据长度表格的索引
* @param:cmd    Const_DataCom-通讯、Const_DataDisp—显示
* @param:pvoid  读取数据缓存
* 
* @返回： 
* @return: uint32 
* @作者: Lwb (2011-9-2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容:  
===========================================================================================*/
uint32 E2DataProc(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucData[16];
    uint8 ASCII[32];
 
    if(Const_DataCOmWR==cmd)                    //写
    {
        if(gs_E2DataTable[index].ucAtb&ASC2BCD)
        {
            ASCII2BCD(ucData,pvoid,gs_E2DataTable[index].ucLen*2);
        }
        else
        {
            MemCpy(ucData,pvoid,gs_E2DataTable[index].ucLen);
        }
            
        if((index>=0x0f)&&(index<=0x11))        //费率
        {
            //把4个字节的BCD转换成8个字节的BCD
            for(uint8 i=0;i<4;i++)
            {
                ASCII[2*i]=(ucData[i]&0x0F);
                ASCII[2*i+1]=((ucData[i]&0xF0)>>4);
            }
          //opt =============   BE_WriteP(gs_E2DataTable[index].uiE2Adrr,ASCII,8);
        }else
        {
        //opt =============     BE_WriteP(gs_E2DataTable[index].uiE2Adrr,ucData,gs_E2DataTable[index].ucLen);
        }
        if((index>=0x0C)&&(index<=0x11))    //费率修改
        {
          //opt =============BE_WriteP(EEP_FEEMDATE,(uint8*)&gs_DateTime.ucMinute,5);
            gui_RefreshEvent|=flgEtPara_Fee;
        }
        return 0;
    }
    

    if(index<ConstE2DataTableCnt)                 //读取指定E2地址和数据长度的数据
    {
        if(index==0x0b)
        {
            ucData[0]=0;//opt =====================guc_MeterSysSta;     //ucData[0]=guc_MeterSysSta;
        }
        else if((index>=0x0f)&&(index<=0x11))        //费率
        {
            BE_ReadP(gs_E2DataTable[index].uiE2Adrr,ASCII,8);
            //把8个字节的BCD转换成4个字节的BCD
            for(uint8 i=0;i<4;i++)
            {
                ucData[i]=((ASCII[2*i]&0x0F)|((ASCII[2*i+1]&0x0F)<<4));
            }
        } 
        else 
        {
          //opt====================  BE_ReadP(gs_E2DataTable[index].uiE2Adrr,ucData,gs_E2DataTable[index].ucLen);
          CopyRam ( ucData,(char *)(gs_E2DataTable[index].uiE2Adrr),gs_E2DataTable[index].ucLen);
        }
 

        BCD2ASCII(ucData,ASCII,gs_E2DataTable[index].ucLen);    //把读取的数据转化成ASCII

        if((index==0x05)||(index==0x06))        //生产和校表日期
        {
            DateFormat(0,ASCII);                  //转化日期
            MemCpy(pvoid,ASCII,8);
            return  8;
        } 
        else if(index==0x07)                    //费率修改日期
        {
            DateAndTmFormat(ASCII);             //转化日期和时间的格式
            MemCpy(pvoid,ASCII,14);
            return 14;
        }
    }
 
    MemCpy(pvoid,ASCII,gs_E2DataTable[index].ucLen*2);
    return gs_E2DataTable[index].ucLen*2;
}
/*=========================================================================================\n
* @function_name: ClearMeterProc
* @function_file: Ptl_1107.c
* @描述: 清零电量
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @作者: lwb (2014/3/25)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint32 ClearMeterProc(uint8 index,uint8 cmd,void *pvoid)
{
    SetCRCWord(guc_InitWd);
    Data_ClearMeter();
    return 0;
}
/*=========================================================================================\n
* @function_name: ReadInsData
* @function_file: Ptl_1107.c
* @描述: 读取瞬时值
* 
* 
* @参数： 
* @param:index  高位0x00 电压   0x10 电流，低位 0x00 A  0x01 B  0x02 C
* @param:cmd     Const_DataCom-通讯、Const_DataDisp—显示
* @param:pvoid  
* 
* @返回： 
* @return: uint32 
* @作者: Lwb (2011-9-13)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint32 ReadInsData(uint8 index,uint8 cmd,void *pvoid)
{
    Word32 ulData;
    uint8 ASCII[10];
    if(index==0x01)
    {
        ulData.lword=EnyB_CalRMS(RMSU);
    }
    else
    {
        ulData.lword=EnyB_CalRMS(RMSI1);
    }

    if(index==0x01)
    {
        BCD2ASCII(ulData.byte,ASCII,2);    //把读取的数据转化成ASCII
        MemCpy((uint8*)pvoid,ASCII,3);
        ((uint8*)pvoid)[3]='.';
        ((uint8*)pvoid)[4]=ASCII[3];
        return 5;

    }else
    {
        BCD2ASCII(ulData.byte,ASCII,3);    //把读取的数据转化成ASCII
        MemCpy((uint8*)pvoid,ASCII,3);
        ((uint8*)pvoid)[3]='.';
        MemCpy((uint8*)pvoid+4,ASCII+3,3);
        return 7;
    }
}
/*=========================================================================================\n
* @function_name: ReadPowDnJl
* @function_file: Ptl_1107.c
* @描述: 读取掉电记录
* 
* @param: index 
* @param: cmd 
* @param: pviod 
* 
* @return: uint32 
* @作者: lwb (2014/4/3)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
/*
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pviod)
{
    uint8 ucbuf[10];
    uint8 ASCII[15];
    uint8 ucMonth=(0xf0&index)>>4;
   //opt  DataProcRead2Slice(DDJLID, ucMonth, 0, 10, ucbuf); 
    BCD2ASCII(ucbuf,ASCII,5);               //把日期转化成ASCii
    DateAndTmFormat(ASCII);                 //转化日期和时间的格式
    MemCpy((uint8*)pviod,ASCII,14);
    ((uint8*)pviod)[14]=',';
    BCD2ASCII(ucbuf+5,ASCII,5);             //把日期转化成ASCii
    DateAndTmFormat(ASCII);                 //转化日期和时间的格式
    MemCpy( ((uint8*)pviod)+15,ASCII,14);
    return 29;
 }
*/
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucbuf[10],ctemp;
    uint8 ASCII[15];
    struct   ST645CommTimeFormat *stp =(struct   ST645CommTimeFormat *)ComData; 
    strDispCode  pCode = { 0x03110000 ,0};     
    pCode.Code +=index;
     
    if ( index )
      debug_break(50);
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );    
    RamData.InDisp = ctemp;    
     
   
    BCD2ASCII(&(stp->cMin),ASCII,5);               //把日期转化成ASCii
    DateAndTmFormat(ASCII);                 //转化日期和时间的格式
    MemCpy((uint8*)pvoid,ASCII,14);
    ((uint8*)pvoid)[14]=',';
    
    stp++;
    BCD2ASCII(&(stp->cMin),ASCII,5);             //把日期转化成ASCii
    DateAndTmFormat(ASCII);                 //转化日期和时间的格式
    MemCpy( ((uint8*)pvoid)+15,ASCII,14);
    return 29;
 }

/*=========================================================================================\n
* @function_name: RdData
* @function_file: Ptl_1107.c
* @描述: 读取OBSI码对应的数据
* 
* 
* @参数: 
* @param:index  
* @param:buf  
* 
* @返回: 
* @return: uint8 
* @作者: Lwb  (2011-8-25)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 RdData(uint8 index,uint8*buf)
{
    uint8 bufpos=0;

    StrCpy(buf, (uint8 const code *)gs_OBSCom[index].pOBS);                     //发送OBSI
    bufpos +=StrLen((uint8 const code *)gs_OBSCom[index].pOBS);
    buf[bufpos++]='(';
    if(gs_OBSCom[index].ucFPidx<ConstOBSFunCnt)                                 //读取OBSI码对应的数据
    {
         Vector8_Disable() ;
    Vector9_Disable()   ;//============================
        bufpos+=gs_OBSFuction[gs_OBSCom[index].ucFPidx](gs_OBSCom[index].param,
                                                        Const_DataCOmRD,
                                                        buf+bufpos);
     Vector9_Enable()         ;//============================
      Vector8_Enable()     ;    
    }

    StrCpy(buf+bufpos, (uint8 const code *)gs_OBSCom[index].pUint);             //发送单位
    bufpos +=StrLen((uint8 const code *)gs_OBSCom[index].pUint);
    return bufpos;
}
/*=========================================================================================\n
* @function_name: EncodeReadFrame
* @function_file: Ptl_1107.c
* @描述: 
* 
* 
* @参数： 
* @param:port  串口号
* @param:buf  发送缓存
* @param:len  发送长度
* @返回: 
* @作者: Lwb (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void EncodeReadFrame(S_COM *ComProcCtr)
{
    uint8 i;
    uint8 bufpos=0;
    //切换波特率

    gs_PtlCtnRd.uc_1107RdFrmCnt=0;

    ComProcCtr->ucBuf[bufpos++]=AS_STX;                                   //STX
    bufpos=0;
    for(i=0;i<6;i++)
    {
        bufpos+=RdData(gs_PtlCtnRd.uc_1107RdFrmCnt++,ComProcCtr->ucBuf+bufpos);
    }
    gs_PtlCtnRd.uc_CkBcc= CalBCC(0,ComProcCtr->ucBuf,bufpos);      //BCC
    gs_PtlCtnRd.uc_1107RdStatus=CNTRD_START;
    //最后一个放到外面发送
    ComProcCtr->ucLen=bufpos;
}
/*=========================================================================================\n
* @function_name: ContinueRead
* @function_file: Ptl_1107.c
* @描述: 连续读数据处理
* 
* 
* @参数: 
* @param:ComProcCtr  
* 
* @返回: 
* @return: uint8 
* @作者: Lwb (2011-8-25)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 ContinueRead(S_COM *ComProcCtr)
{
    uint8 i,bufpos,ucBCCTemp[4];
    bufpos=0;
    for(i=0;i<6;i++)
    {
        if(gs_PtlCtnRd.uc_1107RdFrmCnt>=ComFrmLen)                                 //连续读已经到最后的数据标识，直接退出
        {
            break;
        }
        bufpos+=RdData(gs_PtlCtnRd.uc_1107RdFrmCnt++,ComProcCtr->ucBuf+bufpos);  //读取对应数据标识的数据内容
    }

    gs_PtlCtnRd.uc_CkBcc= CalBCC(gs_PtlCtnRd.uc_CkBcc,ComProcCtr->ucBuf,bufpos);      //BCC
    ComProcCtr->ucLen=bufpos;

    gs_PtlCtnRd.uc_CkBcc=CNTRD_START;
    if(gs_PtlCtnRd.uc_1107RdFrmCnt==ComFrmLen)                                     //发送最后一帧
    {
        ucBCCTemp[0]='!';
        ucBCCTemp[1]='\r';
        ucBCCTemp[2]='\n';
        ucBCCTemp[3]=AS_ETX;
        for(i=0;i<4;i++)
        {
            ComProcCtr->ucBuf[bufpos++]=ucBCCTemp[i];
        }
        gs_PtlCtnRd.uc_CkBcc= CalBCC(gs_PtlCtnRd.uc_CkBcc,ucBCCTemp,4);                 //计算BCC
        ComProcCtr->ucBuf[bufpos++]=gs_PtlCtnRd.uc_CkBcc;                     //赋值BCC
        ComProcCtr->ucLen=bufpos;
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCtnRd.uc_1107RdStatus=CNTRD_STOP;
        gs_PtlCtnRd.uc_1107RdFrmCnt=0;
    }
    return  Ret_OK;

}
/*=========================================================================================\n
* @function_name: JbComHd
* @function_file: Ptl_1107.c
* @描述: 通讯握手阶段判断
* 
* 
* @参数： 
* @param:ComProcCtr  
* 
* @返回： 
* @return: uint8 
* @作者:  Lwb (2011-9-6) 
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 JbComHd(S_COM *ComProcCtr)
{	
	uint8 i;
    //uint8  MeterID[7],
#define                 MeterID               FlashInfo.SafeInfo.TRx_Num
    uint8 RevID[14];//AscZeroCnt=0;


        
    if(CmpStr(ComProcCtr->ucBuf,guc_InitCmd, sizeof(guc_InitCmd))==Ret_OK)
    {//初始化
        SetCRCWord(guc_InitWd);
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        ComProcCtr->ucBuf[0]=AS_ACK;
        ComProcCtr->ucLen=1;
        gui_RefreshEvent|=flgEtPara_Init;
        return Ret_OK;
    }

    CopyRam( MeterID , FlashInfo.SafeInfo.TRx_Num ,4) ;//BE_ReadP(EEP_COMADD,MeterID,4);                    //读取表地址

    BCD2ASCII(MeterID,RevID,4);
    if(CmpStr(ComProcCtr->ucBuf,guc_Frmhd, dim(guc_Frmhd)))
    {
        //判断是否带地址的 / ? x x x x x x x x ! Cr lf
        if(CmpStr(ComProcCtr->ucBuf,guc_FrmADrrhd, 2))         //判断是否是 /  ?
        {
              return Ret_Err; 
        }else
        {//判断地址是否正确
            //读取表号
            if(ApiBufCmp((uint8*)&RevID,ComProcCtr->ucBuf+2,8)!=CMP_EQU)
            {
                return Ret_Err;  //地址不对的话，不回复数据                          
            }
        }
    }
//通讯帧是 /?!CRLF或者/?xxxxxx!CRLF并且地址对的话进入下面阶段
    for(i=0;i<sizeof(guc_BpsCheck);i++)
    {
        ComProcCtr->ucBuf[i]=guc_BpsCheck[i];
    }

    for(i=0;i<8;i++)
    {
        ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+i]=RevID[i];
    }

    ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+8]='\r';
    ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+8]='\n';

    ComProcCtr->ucLen=sizeof(guc_BpsCheck)+10;
    gs_PtlCrt.uc_ComStep=Com_BpsCk;         //进入波特率确认      
    gs_PtlCrt.uc_CompLevel=0;
    gs_PtlCrt.uc_TimeOut=COMOUTTM;                
    return Ret_OK;                          //正确帧
}
/*=========================================================================================\n
* @function_name: JbMode
* @function_file: Ptl_1107.c
* @描述: 通讯模式判断
* 
* 
* @参数： 
* @param:ComProcCtr  
* 
* @返回: 
* @return: uint8 
* @作者: Lwb (2011-9-6)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 JbMode(S_COM *ComProcCtr)
{
    //判断Data readout（读数据）、rogramming mode（编程） 、Manufactory（制造厂商）
    uint8 i;
    if(CmpStr(ComProcCtr->ucBuf,guc_ACKHd1,6))
    {
        ReturnErr();
    }

    switch(ComProcCtr->ucBuf[3])
    {
    case '0':                            //读数据
//      EncodeReadFrame(ComProcCtr);
//      gs_PtlCrt.uc_ComStep=Com_CntRd;
//      gs_PtlCrt.uc_CompLevel=0;
//      gs_PtlCrt.uc_TimeOut=COMOUTTM;
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        break;
    case '1':                            //进入编程模式
        ComProcCtr->ucLen=8;
        for(i=0;i<8;i++)
        {
            ComProcCtr->ucBuf[i]=guc_PgAck[i];
        }
        gs_PtlCrt.uc_CompLevel=0;
        //调整bps到2400
        if(ComProcCtr->ucPort==ComIndex_Uart4)
        {
        //  Init_Uart4(_bps2400_);        // 初始化模拟串口,由于这个是波特率固定的所以不需要切换波特率
        }
        else
        {
          Init_Uart2 (_bps2400_);        // 初始化模拟串口,由于这个是波特率固定的所以不需要切换波特率
        }
        DelayXms(100);                                                 //睡眠20ms
        gs_PtlCrt.uc_ComStep=Com_PRdWr;
        gs_PtlCrt.uc_TimeOut=COMOUTTM;
        break;
    case 'Y':                                                           //读取厂家信息
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        break;
    default:
        ReturnErr();
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: CoreDataProc
* @function_file: Ptl_1107.c
* @描述: 核心数据处理
* 
* 
* @参数: 
* @param:ComProcCtr  
* @返回: 
* @作者:   Lwb (2011-10-9)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人:  
* @修改内容: 
===========================================================================================*/
void CoreDataProc(S_COM *ComProcCtr)
{
    uint8 Pos;
    uint8 OBSI[17];
    uint8 *pData;
    uint8 ObsiLen=0;

    //首先要判断BCC是否正确，然后判断0BSI码是否正确
//  if(CalBCC(0,ComProcCtr->ucBuf+1,ComProcCtr->ucLen-2)==ComProcCtr->ucBuf[ComProcCtr->ucLen-1])
    {
        //BCC正确
        //然后查找0BS码，从第5个字节到（前字节为0BSI
            uint8 i;
            for(i=4;i<21;i++)
            {
                if(ComProcCtr->ucBuf[i]!='(')
                {
                    OBSI[ObsiLen++]=ComProcCtr->ucBuf[i];
                }else
                {
                    break;
                }
            }
            i++;                //去掉'('
            pData=ComProcCtr->ucBuf+i;         //赋值数据首地址
            //读取数据
            Pos=FindObsiPoint(OBSI,ObsiLen);        //根据0BSI码读取数据项

            if(Pos<0xff)
            {
                if(gs_OBSCom[Pos].ucAtb&IEC_WO)
                {
                    if(gs_OBSFuction[gs_OBSCom[Pos].ucFPidx]
                        (gs_OBSCom[Pos].param,Const_DataCOmWR,pData)
                       )
                    {
                        ComProcCtr->ucBuf[0]=AS_NAK;      //NAK
                    }else
                    {
                        ComProcCtr->ucBuf[0]=AS_ACK;      //ACK
                    }
                    ComProcCtr->ucLen=1;
                }else
                {
                    ReturnNAK();
                }
            }else
            {
                //返回错误信息
                ComProcCtr->ucBuf[0]=0x02;      
                ComProcCtr->ucBuf[1]=0x28; 
                ComProcCtr->ucBuf[2]=0x45; 
                ComProcCtr->ucBuf[3]=0x52;
                ComProcCtr->ucBuf[4]=0x52;
                ComProcCtr->ucBuf[5]=0x4F; 
                ComProcCtr->ucBuf[6]=0x52; 
                ComProcCtr->ucBuf[7]=0x29; 
                ComProcCtr->ucBuf[8]=0x03; 
                ComProcCtr->ucBuf[9]=0x5A;
                ComProcCtr->ucLen=10;
            }
    }
//  else
//  {
//      //BCC 错误
//      ReturnNAK();
//  }
}
/*=========================================================================================\n
* @function_name: PrRdWr
* @function_file: Ptl_1107.c
* @描述: 读写模式
* 
* @param: ComProcCtr 
* 
* @return: uint8 
* @作者: lwb (2014/3/24)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 PrRdWr(S_COM *ComProcCtr)
{
  
    uint8 i;
    uint8 BCC;
    uint8 OBSI[17];
    uint8 ObsiLen;
    uint8 Pos;
    BCC=0;

    if(!(CmpStr(ComProcCtr->ucBuf,guc_PcComEd,sizeof(guc_PcComEd))))  //判断是否是中断指令
    {
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        ComProcCtr->ucBuf[0]=AS_ACK;
        ComProcCtr->ucLen=1;
        //切换波特率到300
        guc_BodeDely=40;
        return Ret_OK;
    }

    if(CmpStr(ComProcCtr->ucBuf,guc_PgPCAck,dim(guc_PgPCAck)))      //是密码判断
    {
        //SOH W1 STX AAAA() ETX BCC
        if(CmpStr(ComProcCtr->ucBuf,guc_WROBS,dim(guc_WROBS)))         //判断写命令
        {
            if(CmpStr(ComProcCtr->ucBuf,guc_RdOBS,4))                  //判断是否是读命令
            {
                return Ret_Err;
            }
            else
            {
                gs_PtlCrt.uc_TimeOut=COMOUTTM;
                //首先要判断BCC是否正确，然后判断0BSI码是否正确
//                if(CalBCC(BCC,ComProcCtr->ucBuf+1,ComProcCtr->ucLen-2)==ComProcCtr->ucBuf[ComProcCtr->ucLen-1])
                {
                    //BCC正确
                    //然后查找0BS码，从第5个字节到（前字节为0BSI
                    ObsiLen=0;
                    for(i=4;i<21;i++)
                    {
                        if(ComProcCtr->ucBuf[i]!='(')
                        {
                            OBSI[ObsiLen++]=ComProcCtr->ucBuf[i];
                        }else
                        {
                            break;
                        }
                    }
                    Pos=FindObsiPoint(OBSI,ObsiLen);
                    if(Pos<0xff)                    //找到对应的BOSI码
                    {
                        if(gs_OBSCom[Pos].ucAtb&IEC_RO)
                        {
                            //相等话                            
                            ComProcCtr->ucBuf[0]=AS_STX;                                          //STX
                            ComProcCtr->ucLen=1;
                            ComProcCtr->ucLen += RdData(Pos,ComProcCtr->ucBuf+(ComProcCtr->ucLen));
                            ComProcCtr->ucBuf[(ComProcCtr->ucLen)++]=AS_ETX;                        //ETX
                            BCC= CalBCC(0,ComProcCtr->ucBuf+1,(ComProcCtr->ucLen)-1);               //BCC
                            ComProcCtr->ucBuf[(ComProcCtr->ucLen)++]=BCC;                           //BCC
                        }else
                        {
                            ReturnNAK();
                        }
                    }
                    else
                    {
                        ComProcCtr->ucBuf[0]=0x02;      
                        ComProcCtr->ucBuf[1]=0x28; 
                        ComProcCtr->ucBuf[2]=0x45; 
                        ComProcCtr->ucBuf[3]=0x52;
                        ComProcCtr->ucBuf[4]=0x52;
                        ComProcCtr->ucBuf[5]=0x4F; 
                        ComProcCtr->ucBuf[6]=0x52; 
                        ComProcCtr->ucBuf[7]=0x29; 
                        ComProcCtr->ucBuf[8]=0x03; 
                        ComProcCtr->ucBuf[9]=0x5A;
                        ComProcCtr->ucLen=10;                    
                    }
                }
//                else
//                {
//                    //BCC 错误
//                    ReturnNAK();
//                }
            }
        }
        else                                                    //写数据
        {
            gs_PtlCrt.uc_TimeOut=COMOUTTM;
            if(//(gui_SystemState&flgStSys_Program)&&
                 (gs_PtlCrt.uc_CompLevel==COMPRLEVEL))          //判断是否有权限写
            {
                CoreDataProc(ComProcCtr);                       //核心数据处理
            }
            else
            {
                ReturnNAK();
            }
        }
    }
    else
    {
        if(JudgeOBSPsw(ComProcCtr->ucBuf+5,ComProcCtr->ucBuf[2]-0x30))
        {
            for(uint8 i=0;i<sizeof(guc_PcComEd);i++)
            {
                ComProcCtr->ucBuf[i]=guc_PcComEd[i];
            }
            ComProcCtr->ucBuf[4]=0x71;
            gs_PtlCrt.uc_CompLevel=0;
            gs_PtlCrt.uc_ComStep=Com_HD;
            guc_BodeDely=40;
            ComProcCtr->ucLen=5;
        }
        else
        {
            gs_PtlCrt.uc_CompLevel=COMPRLEVEL;
            gs_PtlCrt.uc_TimeOut=COMOUTTM;
            ComProcCtr->ucBuf[0]=AS_ACK;                  //回复ACK
            ComProcCtr->ucLen=1;
        }
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: AutoJB
* @function_file: Ptl_1107.c
* @描述: 自动校表
* 
* @param: index 
* @param: buf 
* 
* @return: uint8 
* @作者: lwb (2014/4/4)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint32 AutoJB(uint8 index,uint8 cmd,void *pvoid)
{
    if(index==0x01)
    {
        EnyB_IBAutoCheck(); 
    }
    else
    {
        EnyB_AutoChkAngle();
    }
    return 0;
}
