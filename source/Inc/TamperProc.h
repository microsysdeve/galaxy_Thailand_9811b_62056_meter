#ifndef __TAMPERPROC_H__
    #define __TAMPERPROC_H__

#ifndef TAMPEREXT
    #define TAMPEREXT extern
#endif
//ʵ��ֵ����
#define Voltage_100V 27000000       //800K �жϷ�ֵ
#define Current_2A    14500000    //0xDD2160   //800K �жϷ�ֵ
#define Current_1A    7250000     //800K �жϷ�ֵ
#define Current_STARTA   250000   //0x46C02//��������A
#define Current_STARTB   250000   //��������B

#define Power_STARTA   32768   //��������A
#define Power_STARTB   32768   //��������B
#define imBlance_Ref     0       //��ƽ���ж���Դ��0-������1-���ʣ�2-����+����
#define imBlance_Rate    12      //
#define imBlance_Cmp     0       //��ƽ��ȷ�ĸ��0��ǰͨ����1��ֵ��2Сֵ
//WorkMode                         
#define NormalMode   0x50        //��������
#define TamperMode   0x05        //��������
#define SleepMode    0x0A        //���߼���
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