////////////////////////////////////////////////////////////////////////////////
// Demand.h
// �������ģ���������
////////////////////////////////////////////////////////////////////////////////


#ifndef __DEMAND_H__
#define __DEMAND_H__

#ifndef DEMANDEXT
#define DEMANDEXT extern
#endif 

#define DemandLen           8
#define DEMAND_VALUE_NUM    2
#define DEMAND_ITEMS        15                  //����õ�����ʽռ�õ��м���������
#define MAX_D_HCTM          15                  //��ģ���������ʹ�õĻ���ʱ��
#define MAX_D_PERIOD        (DEMAND_ITEMS*2)    //��ģ���������ʹ�õ���������

#if (MAX_D_PERIOD < MAX_D_HCTM)
    #error "DemandExt.h: MAX_D_PERIOD is less than MAX_D_HCTM"
#endif




//������������(1)����������ܺ�ʱ(100ms)���ܼ�ʱ(100ms), ������ƽ������
typedef struct strDEMANDCALCDATA
{
    uint16 uiEnergy;        //������������(0.001kWh)
    uint16 uiEnergyTime;    //���������Ӧ�ĺ�ʱ(100ms)
    uint16 uiTotalTime;     //���μ����ܼ�ʱ(100ms)
    uint32 ulPower;         //������ƽ������
} S_DEMANDCALCDATA;




//ģ���ڲ���������
DEMANDEXT S_DEMANDCALCDATA gs_DemanCalcData;        //������������
DEMANDEXT uint8   guc_DeamandTimer;            		//����������ʱ(��)��ȷ���Ƿ���Ҫ����һ���������㣬�Ƿ�������ȡ�����������ںͻ���ʱ��
//DEMANDEXT uint8   guc_DemandDelay;   				//�ϵ�����������ʱ(��)
DEMANDEXT int32   gl_DemandValue;	                //һ���������ڽ����󣬵õ���һ��������������ϴν��бȽ�
DEMANDEXT uint32  gul_Power;                        //��ʾ����ֵ
DEMANDEXT int32   gl_XPm;                           //�й�����(��)
DEMANDEXT uint8   guc_Demandflag;
DEMANDEXT uint8   guc_DmdCnt;
DEMANDEXT uint8   guc_DmdFrscnt;
DEMANDEXT uint8   guc_Dmd250msCnt;                  //250ms����


void      Demand_Init(void);               //��ʼ������ 
//void      StartDemand(void);              //������������
void      ResetMinuteDemand(uint8 type);  // ��������
void      Demand_Calc(void);
void      Demand_1s(void);
void      Demand_250ms(void);
//void      Demand_EnergyPulse(void);
#define       Demand_EnergyPulse()  {} //    (void);
void      Demand_Proc(void);
void      ClearDemand(uint8 type);
//void      DemandClrCur(void);



#endif
