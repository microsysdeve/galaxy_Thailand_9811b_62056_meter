#ifndef _DR_ENERGY_H_
    #define _DR_ENERGY_H_

#ifndef ENERGYBOTTOMEXT
    #define ENERGYBOTTOMEXT extern
#else
    #define DR_ENERGYSELF
#endif

#define CFGDELAY 32   //读取双口RAM延时时间
#define INITGATEP  0x10462d9
#define INITGATEQ  0x10462d9
#define INITGATECP 0X214ABA

#define MEA800K   0x55
#define MEA3D2M   0x00

/*======================PMCTLR1 CHANNEL====================*/
#define ONU   BIT0
#define ONI1  BIT1
#define ONI2  BIT2
#define ONM   BIT3

/*======================ADC CHANNEL====================*/
#define ADCAPDN   BIT0
#define ADCBPDN   BIT1
#define ADCUPDN   BIT2
#define ADCMPDN   BIT3
//open adc
#define ADCOPEN(Channel)  {CtrlADC6|=Channel;}
//close adc
#define ADCCLOSE(Channel) {CtrlADC6&=(~Channel);}

/***********************ADC PARA****************/
#define ADCA1X    0
#define ADCA4X    BIT0
#define ADCA8X    BIT1
#define ADCA16X  BIT0+BIT1
#define ADCA32X  BIT0+BIT1+BIT2
#define ADCB1X    0
#define ADCB4X    BIT3
#define ADCB8X    BIT4
#define ADCB16X  BIT3+BIT4
#define ADCB32X  BIT3+BIT4+BIT5
#define ADCU1X    0
#define ADCU2X    BIT6
#define ADCM1X    0
#define ADCM2X    BIT7




 
#define Const_MaxCf     0x05//最大脉冲数
#define ADCFRE   819200
#define PLEVEL   65         //启动功率
#define IALEVEL  25         //启动电流
#define IBLEVEL  70
#define ULEVEL   200         //开始有显示的电压20.0V
#define CRIULEVEL1  1694
#define CRIULEVEL2  2640
 
typedef struct
{
    uint16 ui_MeterC;   // 表常数
    uint16 ui_Un;       // 标称电压
    uint16 ui_Ib;       // 标称电流

    uint32 ul_Gatep;    //有功能量脉冲门限值32位
    uint32 ul_Gateq;    //有功能量脉冲门限值32位
    uint32 ul_Gatecp;   //有功能量潜动门限值32
    uint32 ul_GateOSC;  //

    uint32 ul_SCP;      //有功比差值 
    uint32 ul_SCQ;      //无功功率比差
    uint32 ul_SCU;      //电压有效值比差
    uint32 ul_SCI1;     //通道I1电流有效值比差
    uint32 ul_SCI2;     //通道I2电流有效值比差
 
    uint32 ul_PARAPC;   //有功功率二次补偿
    uint32 ul_PARAQC;   //无功功率二次补偿

    uint8 uc_PhcCtrl1;  //I1通道角差
    uint8 uc_PhcCtrl2;  //I2通道角差

    uint32 ul_PG;       //功率比例系数
    uint32 ul_QG;       //功率比例系数
    uint32 ul_URmG;     //电压通道比例系数
    uint32 ul_I1RmG;    //电流通道1比例系数
//    uint32 ul_I1RmGOSC;    //电流通道1比例系数 OSC
//    uint32 ul_I1RmG800;    //电流通道1比例系数 MEA800k
    uint32 ul_I2RmG;    //电流通道2比例系数    
//    uint32 ul_I2RmGOSC;    //电流通道2比例系数 OSC   
//    uint32 ul_I2RmG800;    //电流通道2比例系数 MEA800k
    uint32 ul_SCI1_800; //通道I1电流有效值比差
    uint32 ul_SCI2_800; //通道I2电流有效值比差
    
    uint8 uc_AnaG;     //模拟增益(包含I2 bit[12:9]，I1 bit[7:4]，U bit[3:0])
    uint16 ui_JbCRC;    // 校表参数的CRC结果
}S_JBPM;

ENERGYBOTTOMEXT S_JBPM gs_JbPm;            //校表参数
ENERGYBOTTOMEXT uint32 u32PMdatal;
ENERGYBOTTOMEXT uint8  u8PMdatah;

typedef struct
{
    int32 ul_Adjust;    // 大电流比差补偿
    uint16 ui_CRC;       // CRC
}S_GSCP;

ENERGYBOTTOMEXT S_GSCP gs_GiantSCP;
ENERGYBOTTOMEXT uint8 guc_GiantSCPflag;
ENERGYBOTTOMEXT uint8 guc_GiantSCPcnt;

//以下为能量脉冲和无功能量的结构体定义，
typedef struct                   
{
    uint8 uc_Pz;       // 正向总能量脉冲数
//    uint8 uc_P1;       // 正向有功费率1
//    uint8 uc_P2;       // 正向有功费率2能量脉冲数
//    uint8 uc_P3;       // 正向有功费率3能量脉冲数
//    uint8 uc_P4;       // 正向有功费率3能量脉冲数

    uint8 uc_Nz;       // 反向总能量脉冲数
//    uint8 uc_N1;       // 反向有功费率1
//    uint8 uc_N2;       // 反向有功费率2能量脉冲数
//    uint8 uc_N3;       // 反向有功费率3能量脉冲数
//    uint8 uc_N4;       // 反向有功费率3能量脉冲数
} S_POWERCF; 

ENERGYBOTTOMEXT S_POWERCF gs_PowerCf;

//ENERGYBOTTOMEXT  uint8 guc_PowRCnt;        //功率反向计数
//ENERGYBOTTOMEXT  uint8 guc_PowRExitCnt;    //功率反向退出计数

typedef struct
{
    uint32 Pa;                          //保留2位小数 单位为W
    uint16 Ua;                          //保留2位小数 单位为V
    uint16 Ia;                          //保留3为小数 单位为A
}S_CHECKMETER;

ENERGYBOTTOMEXT S_CHECKMETER gs_Checkmeter;//校表功率比对数据


ENERGYBOTTOMEXT uint8 guc_CfOpenCnt;
ENERGYBOTTOMEXT uint8 guc_CfOpenFlg;

#define SETA 0x00
#define SETB 0x55
typedef struct
{
    uint8 ucSta;                //当前通道
    uint8 ucACnt;               //A通道计数
    uint8 ucBCnt;               //B通道计数
    uint8 ucGate;               //计数门限
}S_CHANNEL;
ENERGYBOTTOMEXT S_CHANNEL gs_Channel;



typedef struct
{
    uint8   ucDelayTm;
    uint32  ulPDirGate;
}S_PDIRCTR;
ENERGYBOTTOMEXT S_PDIRCTR gs_PDirCtr;

typedef struct
{
    uint8   ucDirCnt;
    uint8   ucRevDirCnt;
}S_PDIRCNT;

ENERGYBOTTOMEXT S_PDIRCNT gs_PDirCnt;

//函数声明
void EnyB_PurInit(void);
void EnyB_JbPm_Init(void);



void EnyB_AutoChkPW(uint8);                                              
void EnyB_AutoChkIrms(uint8);
void EnyB_AutoChkUrms(void);
void EnyB_AutoChkAngle(void);
void EnyB_AutoCheck(void);
void EnyB_AutoCheck2(void);
void EnyB_CloseAutoCheck(void);
void EnyB_OpenAutoCheck(void);
void EnyB_AutoChkInrms(uint16 ui_SdCurrent);
void EnyB_JbPm_Updata(void);
void EnyB_InitCFInt(void);
void EnyB_IntCF(void);
void EnyB_Check_Irms(void);
void EnyB_AutoChkSP(void);
 
uint8 EnyB_ChkPowRev(uint8 *, uint8);

int16 EnyB_Cal_Cos(void);
void EnyB_SetMeterRule(uint8);
void Mea_Init(void);
void EnyB_Open_Cf(void);
void EnyB_FstPluseProc(void);

uint32 CalRMS(uint16 addr);
uint16 CalCos(void);
uint32 EnyB_ReadMeterParaACK(uint16 addr);
uint8 EnyB_SetMeterCfgACK(uint32 u32PMdatal ,uint16 addr);
uint8 EnyB_SetMeterL2H(uint32 u32PMdatal ,uint16 addr);
uint8 EnyB_SetMeterH2L(uint32 u32PMdatal ,uint16 addr);
void EnyB_Init(void);
#endif
