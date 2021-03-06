#ifndef _AP_ENERGY_H_
    #define _AP_ENERGY_H_

#ifndef AP_ENERGYEXT
    #define AP_ENERGYEXT extern
#else
    #define AP_ENERGYSELF
#endif


#define ENERGY_CLR_RAM  0x01    //清当前电量的ram增量部分,一般是总清时或ram区校验出错时完成
#define ENERGY_CLR_E2   0x02    //清当前电量E2中的数据,一般在总清时完成
#define ENERGY_CLR      (ENERGY_CLR_RAM + ENERGY_CLR_E2)    //用于总清


// 其他定义
#define     MAX_E       2200                    // 增量允许存放的最大值
#define     SAVEVALUE   2000                    // 增量转存的门限值


enum
{
    ENERGY_ERR_NONE,                            //RAM电量校验没有错
    ENERGY_ERR_RAM,                             //RAM校验有错
};

//与应用层接口的一致和统一，以下数据单位为0.01kwh
typedef struct               
{                     // 单位：0.01kwh
    uint8 ucPz;       // 正向总脉冲
//    uint8 ucP1;       // 正向有功费率1或者总能量数据
//    uint8 ucP2;       // 正向有功费率2能量数据
//    uint8 ucP3;       // 正向有功费率3能量数据
//    uint8 ucP4;       // 正向有功费率3能量数据


    uint8 ucNz;       // 反向总脉冲
//    uint8 ucN1;       // 反向有功费率1或者总能量数据
//    uint8 ucN2;       // 反向有功费率2能量数据
//    uint8 ucN3;       // 反向有功费率3能量数据
//    uint8 ucN4;       // 反向有功费率3能量数据

}S_ENERGY;                                      
AP_ENERGYEXT    S_ENERGY gs_Energy;       // 定义成一个结构体，可保证数据的连续，同时与计量模块的接口是统一的

AP_ENERGYEXT uint8 guc_GateCF;                  // CF脉冲的分频率系数，通过查表获取
AP_ENERGYEXT uint8 guc_UnitCF;                  //CF脉冲的单位数据，通过查表获取



// 电量增量结构
typedef struct  
{
    uint16 uiEPZ;                                //正向总能量增量

//    uint16 uiEP1;                                //正向费率1有功增量
//    uint16 uiEP2;                                //正向费率2有功增量
//    uint16 uiEP3;                                //正向费率3有功增量
//    uint16 uiEP4;                                //正向费率4有功增量

    uint16 uiENZ;                                //反向总能量增量

//    uint16 uiEN1;                                //反向费率1有功增量
//    uint16 uiEN2;                                //反向费率2有功增量
//    uint16 uiEN3;                                //反向费率3有功增量
//    uint16 uiEN4;                                //反向费率4有功增量

    uint16 uiCRC;                                //电量增量CRC校验 
} ENERGYDATA;


// 有功电量字节数
typedef struct 
{
    int32   lCP[1];                        //组合有功,c是calculate的意思
    uint32  ulP;                           //正向有功
    uint32  ulN;                           //反向有功
    uint16  uiCRC;                              //CRC校验和
}ENERGYACTIVE;

//AP_ENERGYEXT ENERGYDATA gs_EnergyData;          //当前电量增量
//AP_ENERGYEXT ENERGYDATA gs_EnergyData_bak;      //当前电量增量备份
//AP_ENERGYEXT ENERGYACTIVE gs_EnergyA;           //当前电量有功部分(不包含增量)
//AP_ENERGYEXT uint8 guc_EPCalcType;              //组合有功方式字
#define  guc_EPCalcType         FlashInfo.SetInfo.ActUseMode              //组合有功方式字
//结构定义，用于实现能量的标定
typedef struct meterc 
{                                                    
  uint16 ui_MC;             // 脉冲常数
  uint8 uc_CFGate;          // CF脉冲门限值
  uint8 uc_CFUinit;         // 每个单位能量的大小
}S_METERC; 
   
#define MeterConstLen    17  // 表常数列表的个数

#ifdef AP_ENERGYSELF
const S_METERC code gs_MeterConstT[MeterConstLen]=      //根据表常数，确定CF的分频系数和每个单位能量的大小
{

  {12000,   12, 1},           // 表常数是12000，则对CF进行10分频，输出的能量大小是0.001 x1
  {10000,   10, 1},           // 表常数是10000，则对CF进行10分频，输出的能量大小是0.001 x1
  {8000,    8,  1},           // 表常数是8000，则对CF进行8分频，输出的能量大小是0.001 x1
  {5000,    5,  1},  
  {3000,    3,  1},  
  {2000,    2,  1}, 
  {1000,    10,  10},  
  {6400,    64, 10},          // 表常数是6400，则对CF进行64分频，输出的能量大小是0.001  x10
  {3200,    32, 10}, 
  {2400,    24, 10},
  {1600,    16, 10}, 
  {1200,    12, 10},
  {800, 8,  10}, 
  {500, 5,  10}, 
  {400, 4,  10}, 
  {200, 2,  10}, 
  {100, 1,  10}, 
};
#else

#endif




void TaskEnergy(void);
void Eny_EnergyProc(void);
//void Eny_EnergyClrCur(uint8 ucType);
#define  Eny_EnergyClrCur(A)   {} //
//void Eny_CheckEnergy(void);
#define  Eny_CheckEnergy()  {}

//uint8 Eny_CheckEnergyActiveRAM(void);
#define Eny_CheckEnergyActiveRAM()   (ENERGY_ERR_NONE)
//int16 Eny_GetEp1(uint8 index, uint8 fee);
#define Eny_GetEp1(a,b)                       (0)          
//void Eny_EnergyActiveSave(void);
#define  Eny_EnergyActiveSave()  {}
//void Eny_PurCheckRAMEny(void);
#define Eny_PurCheckRAMEny()                    {}
//void Eny_RefCalcType(void);
#define  Eny_RefCalcType()  {}
void Eny_JbPm_GetE2(void);
void Eny_RefVar(void);
void Eny_JbPm_MeterConst(void);
void Eny_JbPm_UpdateRam(uint8 *pjb);
void EnergyCBRManage(void);
//void WriteHisEP(void);
#define WriteHisEP()   {} 
void SaveJSTime(uint32 time);
void MonthLYDL(uint8 uc_Save);
void Eny_SlpEnergyProc(void);
#endif
