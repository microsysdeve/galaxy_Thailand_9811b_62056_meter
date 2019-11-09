/****************************************Copyright (c)**************************************************
**                                  杭州万工科技有限公司
**                                          系统工程部
**
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: Ptl_1107.h
**创   建   人: LWB
**最后修改日期: 2011年8月25日
**描        述: 1107规约处理函数集
**注        意：
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: LWB
** 版  本: v1.0
** 日　期: 2010年12月25日
** 描　述: 原始版本
********************************************************************************************************/
#ifndef _AP_1107_H_
#define _AP_1107_H_

#ifndef AP_1107_EXT
#define AP_1107_EXT extern
#endif

#define ComFrmLen       0x29

#define RDPWD           0x01        //读密码
#define WRPWD           0x02        //写密码

#define Ret_OK          0x00        //正确
#define Ret_Err         0xff        //错误



#define  ReturnErr() {  /*恢复到帧头判断*/   gs_PtlCrt.uc_ComStep=Com_HD;\
                                          gs_PtlCrt.uc_CompLevel=0;\
                                          ComProcCtr->ucBuf[0]=AS_NAK;\
                                          ComProcCtr->ucLen=1;\
                                          guc_BodeDely=40;\
                        /*返回错误字*/      return Ret_OK;}




#define  ReturnNAK()    {ComProcCtr->ucBuf[0]=AS_NAK;\
                         ComProcCtr->ucLen=1;}

//ASCII中的控制符
enum
{
    AS_NULL=0,
    AS_SOH,
    AS_STX,
    AS_ETX,
    AS_EOT,
    AS_END,
    AS_ACK,
    AS_BEL,
    AS_BS,
    AS_HT,
    AS_LF,
    AS_VT,
    AS_FF,
    AS_CR,
    AS_SO,
    AS_SI,
    AS_DLE,
    AS_DC1,
    AS_DC2,
    AS_DC3,
    AS_DC4,
    AS_NAK,
    AS_SYN,
    AS_ETB,
    AS_CAN,
    AS_EM,
    AS_SUB,
    AS_ESC,
    AS_FS,
    AS_GS,
    AS_RS,
    AS_US
};


enum  ENUMCOMSTATU
{//通讯步骤
    Com_HD = 0,             //起始步骤
    Com_BpsCk,              //波特率确认帧
    Com_CntRd,              //连续读
//  Com_PR,                 //编程状态
    Com_PRdWr,              //编程读写数据
//  Com_PSet,               //编程写数据
};

#define COMOUTTM   5
#define COMPRLEVEL 0x55
typedef struct
{
    uint8 uc_ComStep;       //步骤
    uint8 uc_CompLevel;     //权限
    uint8 uc_TimeOut;       //超时       
}PTL_1107CTR;

AP_1107_EXT PTL_1107CTR gs_PtlCrt;

#define     CNTRD_START       0x55
#define     CNTRD_STOP        0x00

typedef struct
{
    uint8 uc_CkBcc;
    uint8 uc_1107RdFrmCnt;
    uint8 uc_1107RdStatus;
}PTL_1107CTNRD;

AP_1107_EXT PTL_1107CTNRD gs_PtlCtnRd;

typedef code uint8 (*ComFPro)(S_COM *);   //处理函数

//Atb定义
//BIT7 需要转换ASCII，
#define TOASC    BIT7
#define IEC_WO   BIT6       //可写
#define IEC_RO   BIT5
#define IEC_RW   BIT5+BIT6
#define IEC_E2   BIT4


typedef struct
{
    string pOBS;        //OBSI码
    string pUint;       //单位
    uint8 param;        //参数，函数指针要调用的参数
    uint8 ucAtb;        //属性
    uint8 ucFPidx;      //函数调用偏移
}GS_IECCOM;


typedef uint32(*PFOBSProc)(uint8,uint8,void*);//函数指针

#define     CNTRD_START       0x55
#define     CNTRD_STOP        0x00

//AP_1107_EXT uint8     guc_CheckBCC;
//AP_1107_EXT uint8     guc_1107RdFrmCnt;
//AP_1107_EXT uint8     guc_1107RdStatus;


extern const GS_IECCOM code gs_OBSCom[];
extern const PFOBSProc code gs_OBSFuction[];
extern const uint8 code ConstOBSFunCnt;
extern const uint8 code Cosnt_OBSLen;

enum
{
    Const_DataDisp=0,       //LCD显示读
    Const_DataCOmRD,        //通讯读
    Const_DataCOmWR,        //通讯写
};

#define  HEX2BCD    0x80
#define  ASC2BCD    0x40
typedef struct 
{
    uint16 uiE2Adrr;    //E2地址
    uint8  ucAtb;       //属性
    uint8  ucLen;       //数据长度
}GSE2DATA;

/*******************************************************************************
**下面是函数申明
*******************************************************************************/
uint8 JbComHd(S_COM *ComProcCtr);
uint8 JbMode(S_COM *ComProcCtr);
uint8 PrRdWr(S_COM *ComProcCtr);
uint32 AutoJB(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadCurEgy(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadHisEgy(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadHisDemad(uint8 index,uint8 cmd,void *pvoid);
uint32 DateAndTimeProc(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadBodyOpOrMdTrDate(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadAlmFroze(uint8 index,uint8 cmd,void *pvoid);
uint32 E2DataProc(uint8 index,uint8 cmd,void *pvoid);
uint32 FlashDataProc(uint8 index,uint8 cmd,void *pvoid);

uint32 ClearMeterProc(uint8 index,uint8 cmd,void *pvoid);
uint32 DoNoting(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pviod);
uint32 ReadInsData(uint8 index,uint8 cmd,void *pvoid);
uint8 ContinueRead(S_COM *ComProcCtr);
uint8 FindObsiPoint(uint8* Obsi,uint8 len);

 enum ENUMOBSMFUNLIST 
{
    _ReadCurEgy_ = 0,                 //读取当前有功电量   0
    _ReadHisEgy_,                 //读取历史有功电量   1
    _ReadHisDemad_,               //读取历史需量      2
    _ReadBodyOpOrMdTrDate_,       //开表盖和线盖事件   3
    _ReadPowDnJl_,                //掉电记录         4
    _E2DataProc_,                 //读取E2数据       5    
    _DateAndTimeProc_,            //读取日期和时间    6 
    _ReadInsData_,                //读取瞬时数据      7
    _ClearMeterProc_,             //清零电量处理      8
    _FlashDataProc_,                 //读取FLASH据       9
    _ReadAlmFroze_,
    _AutoJB_,                     //自动校表
    _ENUMOBSMFUNLIST_End_, 

};


enum    ENUMENGRYDEF
{
    _code645_00000000_ = 0,
    _code645_00010000_,
    _code645_00020000_,
    
    _code645_prevbase_,
    _code645_00000001_ =_code645_prevbase_,
    _code645_00010001_,
    _code645_00020001_,
    
    _code645_00000002_,
    _code645_00010002_,
    _code645_00020002_,
    
     _code645_00000003_,
    _code645_00010003_,
    _code645_00020003_,
    
     _code645_00000004_,
    _code645_00010004_,
    _code645_00020004_,
    
    _code645_00000005_,
    _code645_00010005_,
    _code645_00020005_,
    
     _code645_00000006_,
    _code645_00010006_,
    _code645_00020006_ ,
    
     _code645_00000007_,
    _code645_00010007_,
    _code645_00020007_,
    
     _code645_00000008_,
    _code645_00010008_,
    _code645_00020008_ ,
    
     _code645_00000009_,
    _code645_00010009_,
    _code645_00020009_ ,
    
    _code645_0000000A_,
    _code645_0001000A_,
    _code645_0002000A_,
    
     _code645_0000000B_,
    _code645_0001000B_,
    _code645_0002000B_,
    
     _code645_0000000C_,
    _code645_0001000C_,
    _code645_0002000C_ ,
    
    _code645_OnLineEvent_,  //   上下电记录
    _code645_03110000_ = _code645_OnLineEvent_,
    _code645_03110001_,
    _code645_03110002_,
    _code645_03110003_,
    _code645_03110004_,
    _code645_03110005_,
    _code645_03110006_,
    _code645_03110007_,
    _code645_03110008_,
    _code645_03110009_,
    _code645_0311000A_,  
    
}   ;
            
      
#endif 