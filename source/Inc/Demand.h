////////////////////////////////////////////////////////////////////////////////
// Demand.h
// 最大需量模块变量声明
////////////////////////////////////////////////////////////////////////////////


#ifndef __DEMAND_H__
#define __DEMAND_H__

#ifndef DEMANDEXT
#define DEMANDEXT extern
#endif 

#define DemandLen           8
#define DEMAND_VALUE_NUM    2
#define DEMAND_ITEMS        15                  //计算得到滑差式占用的中间量的数量
#define MAX_D_HCTM          15                  //本模块最大允许使用的滑差时间
#define MAX_D_PERIOD        (DEMAND_ITEMS*2)    //本模块最大允许使用的需量周期

#if (MAX_D_PERIOD < MAX_D_HCTM)
    #error "DemandExt.h: MAX_D_PERIOD is less than MAX_D_HCTM"
#endif




//计量到的脉冲(1)，最近脉冲总耗时(100ms)，总计时(100ms), 计算后的平均功率
typedef struct strDEMANDCALCDATA
{
    uint16 uiEnergy;        //计量到的能量(0.001kWh)
    uint16 uiEnergyTime;    //能量脉冲对应的耗时(100ms)
    uint16 uiTotalTime;     //本次计算总计时(100ms)
    uint32 ulPower;         //计算后的平均功率
} S_DEMANDCALCDATA;




//模块内部变量定义
DEMANDEXT S_DEMANDCALCDATA gs_DemanCalcData;        //需量计算数据
DEMANDEXT uint8   guc_DeamandTimer;            		//需量计算走时(分)，确定是否需要启动一次需量计算，是否输出结果取决于需量周期和滑差时间
//DEMANDEXT uint8   guc_DemandDelay;   				//上电需量计算延时(分)
DEMANDEXT int32   gl_DemandValue;	                //一个需量周期结束后，得到的一个结果，用于与上次进行比较
DEMANDEXT uint32  gul_Power;                        //显示功率值
DEMANDEXT int32   gl_XPm;                           //有功需量(正)
DEMANDEXT uint8   guc_Demandflag;
DEMANDEXT uint8   guc_DmdCnt;
DEMANDEXT uint8   guc_DmdFrscnt;
DEMANDEXT uint8   guc_Dmd250msCnt;                  //250ms计数


void      Demand_Init(void);               //初始化需量 
//void      StartDemand(void);              //开启计算需量
void      ResetMinuteDemand(uint8 type);  // 函数声明
void      Demand_Calc(void);
void      Demand_1s(void);
void      Demand_250ms(void);
//void      Demand_EnergyPulse(void);
#define       Demand_EnergyPulse()  {} //    (void);
void      Demand_Proc(void);
void      ClearDemand(uint8 type);
//void      DemandClrCur(void);



#endif
