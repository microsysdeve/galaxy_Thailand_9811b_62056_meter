#ifndef __TAMPERPROC_H__
    #define __TAMPERPROC_H__

#ifndef TAMPEREXT
    #define TAMPEREXT extern
#endif
//实测值处理
#define Voltage_100V 27000000       //800K 判断阀值
#define Current_2A    14500000    //0xDD2160   //800K 判断阀值
#define Current_1A    7250000     //800K 判断阀值
#define Current_STARTA   250000   //0x46C02//启动电流A
#define Current_STARTB   250000   //启动电流B

#define Power_STARTA   32768   //启动功率A
#define Power_STARTB   32768   //启动功率B
#define imBlance_Ref     0       //不平衡判断来源：0-电流，1-功率，2-电流+功率
#define imBlance_Rate    12      //
#define imBlance_Cmp     0       //不平衡比分母：0当前通道，1大值，2小值
//WorkMode                         
#define NormalMode   0x50        //正常计量
#define TamperMode   0x05        //常数计量
#define SleepMode    0x0A        //休眠计量
TAMPEREXT uint8 guc_WorkMd;

TAMPEREXT uint32 gul_Urms800k;
TAMPEREXT uint32 gul_I1rms800k;
TAMPEREXT uint32 gul_I2rms800k;

#define PendReady  0x00
#define PendUGO    0x05
#define PendUEND   0x0A
#define PendI1GO   0x55
#define PendI1END  0x5A
#define PendI2GO   0xA5
#define PendI2END  0xAA
TAMPEREXT uint8 guc_PendSta;
TAMPEREXT uint8 guc_PendCnt;

TAMPEREXT uint32 gul_I1DCval;
TAMPEREXT uint32 gul_I2DCval;



void SwitchMode(uint8);
void Tamp_ChkPLL(void);
void Tamp_DspProc(void);
bool Tamp_ChkUrms(void);
bool Tamp_ChkBlance(uint32); 
void Tamp_ChkCurrent(void);
void Tamp_BlanceProc(void); 
void Tamp_Sleep(void);
void Tamp_Init(void);
__near_func void Tamp_IntProc(void);
#endif