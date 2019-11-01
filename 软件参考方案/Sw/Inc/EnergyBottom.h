#ifndef _DR_ENERGY_H_
    #define _DR_ENERGY_H_

#ifndef ENERGYBOTTOMEXT
    #define ENERGYBOTTOMEXT extern
#else
    #define DR_ENERGYSELF
#endif

#define Const_MaxCf     0x05//最大脉冲数

#define ULEVEL   200         //开始有显示的电压20.0V
#define ADCFRE   819200

#define DATAOIU     0x1005          //瞬时电压原始值
#define DATAOII1    0x100A          //通道I1瞬时电流原始值
#define DATAOII2    0x100F          //通道I2瞬时电流原始值
#define DATAIAU     0x1051          //瞬时电压交流值
#define DATAIAI1    0x1052          //通道I1瞬时电流交流值
#define DATAIAI2    0x1053          //通道I2瞬时电流交流值
#define DATAIDU     0x103A          //瞬时电压直流值
#define DATAIDI1    0x1041          //通道I1瞬时电流直流值
#define DATAIDI2    0x1048          //通道I2瞬时电流直流值

#define DATAOM      0x10CE          //M通道原始数据值寄存器
#define DATADM      0x10CF          //M通道直流数据值寄存器

#define DATAADM     0x10D0          //M通道直流秒平均数据值寄存器
#define DATAIP      0x10D1          //瞬时有功功率
#define DATAIQ      0x10D2          //瞬时无功功率
#define RMSIU       0x10D3          //瞬时电压有效值
#define RMSII1      0x10D4          //I1通道瞬时电流有效值
#define RMSII2      0x10D5          //I2通道瞬时电流有效值
#define DATAP       0x10D6          //秒平均有功功率
#define DATAQ       0x10D7          //秒平均无功功率
#define RMSU        0x10D8          //秒平均电压有效值
#define RMSI1       0x10D9          //I1通道秒平均电流有效值
#define RMSI2       0x10DA          //I2通道秒平均电流有效值
#define DATAAP1     0x10DB          //I1通道秒平均视在功率
#define DATAAP2     0x10DC          //I2通道秒平均视在功率

#define SCP         0x10DD          //有功功率比差寄存器
#define SCQ         0x10DE          //无功功率比差寄存器
#define SCU         0x10DF          //电压有效值比差寄存器
#define SCI1        0x10E0          //通道I1电流有效值比差寄存器
#define SCI2        0x10E1          //通道I2电流有效值比差寄存器
#define PARAPC      0x10E2          //有功功率二次补偿寄存器
#define PARAQC      0x10E3          //无功功率二次补偿寄存器

#define PPCNT       0x10F0          //正相有功能量计数器
#define NPCNT       0x10F1          //反相有功能量计数器
#define PPCFCNT     0x10F2          //正相有功能量脉冲计数器
#define NPCFCNT     0x10F3          //反相有功能量脉冲计数器

#define GATEP       0x10F4          //有功能量脉冲门限值寄存器
#define GATECP      0x10F5          //有功能量潜动门限值寄存器

#define PQCNT       0x10F6          //正相无功能量计数器
#define NQCNT       0x10F7          //反相无功能量计数器
#define PQCFCNT     0x10F8          //正相无功能量脉冲计数器
#define NQCFCNT     0x10F9          //反相无功能量脉冲计数器

#define GATEQ       0x10FA          //无功能量脉冲门限值寄存器
#define GATECQ      0x10FB          //无功能量潜动门限值寄存器
#define DATACP      0x10FC          //常数功率值寄存器

#define DATAFREQ    0x10FD          //频率值寄存器


#define SETADC_IA       0
#define SETADC_IB       1
#define SETADC_U        2
#define SETADC_IT1      0
#define SETADC_IT4      1
#define SETADC_IT8      2
#define SETADC_IT16     3
#define SETADC_UT1      0
#define SETADC_CLOSE    0x80



#define SETM_GROUND     0x00
#define SETM_TEMP       0x01
#define SETM_VBAT1      0x22
#define SETM_VBAT2      0x23
#define SETM_EXT        0x03
#define SETM_S_SEG33    0x04
#define SETM_S_SEG34    0x05
#define SETM_S_SEG35    0x06
#define SETM_S_SEG36    0x07
#define SETM_L_SEG33    0x24
#define SETM_L_SEG34    0x25
#define SETM_L_SEG35    0x26
#define SETM_L_SEG36    0x27
#define SETM_T1         0x00
#define SETM_T2         0x01
#define SETM_CLOSE      0x80



typedef struct
{
    uint16 ui_MeterC;   // 表常数
    uint16 ui_Un;       // 标称电压
    uint16 ui_Ib;       // 标称电流
    
    uint8  uc_GatepH;   //有功门限值高8位
    uint32 ul_GatepL;   //有功能量脉冲门限值低32位
    uint32 ul_Gatecp;   //有功能量潜动门限值32


    uint32 ul_SCP;      //有功比差值
    uint32 ul_SCQ;      //无功功率比差
    uint32 ul_SCU;      //电压有效值比差
    uint32 ul_SCI1;     //通道I1电流有效值比差
    uint32 ul_SCI2;     //通道I2电流有效值比差

    uint32 ul_PARAPC;   //有功功率二次补偿
    uint32 ul_PARAQC;   //无功功率二次补偿

    uint8 uc_PhcCtrl1;  //I1通道角差
    uint8 uc_PhcCtrl2;  //I2通道角差

    uint32 ul_PG;
    uint32 ul_URmG;
    uint32 ul_I1RmG;
    uint32 ul_I2RmG;
    uint8  uc_ADCGain;
    uint16 ui_JbCRC;       // 校表参数的CRC结果
}S_JBPM;

ENERGYBOTTOMEXT S_JBPM gs_JbPm;            //校表参数
ENERGYBOTTOMEXT uint32 u32PMdatal;
ENERGYBOTTOMEXT uint8  u8PMdatah;


typedef struct
{
   uint8 ucRevDirCnt;
   uint8 ucDirCnt;
   uint8 PDir;
}GS_PDIR;

ENERGYBOTTOMEXT GS_PDIR gs_PDirCnt;

//以下为能量脉冲和无功能量的结构体定义，
typedef struct
{
    uint8 uc_P;       // 正向有功能量脉冲数
//  uint8 uc_N;       // 反向有功能量脉冲数
} S_POWERCF;

ENERGYBOTTOMEXT S_POWERCF gs_PowerCf;
ENERGYBOTTOMEXT uint8 guc_OpenCfTmCnt;
ENERGYBOTTOMEXT uint8 guc_CfOpenFlg;
ENERGYBOTTOMEXT uint8 guc_ResetFlg;
//函数声明
void EnyB_PurInit(void);
void EnyB_JbPm_Init(void);
void EnyB_Check_PowRev(void);
void EnyB_AutoChkPW(uint8 *buf);
void EnyB_AutoChkIrms(uint8 *buf);
void EnyB_AutoChkUrms(uint8 *buf);
void EnyB_AutoCheck(uint8* buf);
void EnyB_IBAutoCheck(void);
void EnyB_AutoChkAngle(void);

void EnyB_JbPm_Updata(void);
void EnyB_InitCFInt(void);
void EnyB_IntCF(void);
void EnyB_MeasBat(void);
int16 EnyB_Cal_Cos(void);
void EnyB_SetMeterRule(void);
void EnyB_Open_Cf(void);
void EnyB_FstPluseProc(void);
uint32 ReadMeterPara(uint16 addr);
uint32 EnyB_CalRMS(uint16 addr);


#endif
