#ifndef _AP_ENERGY_H_
    #define _AP_ENERGY_H_

#ifndef AP_ENERGYEXT
    #define AP_ENERGYEXT extern
#else
    #define AP_ENERGYSELF
#endif


#define ENERGY_CLR_RAM  0x01    //�嵱ǰ������ram��������,һ��������ʱ��ram��У�����ʱ���
#define ENERGY_CLR_E2   0x02    //�嵱ǰ����E2�е�����,һ��������ʱ���
#define ENERGY_CLR      (ENERGY_CLR_RAM + ENERGY_CLR_E2)    //��������


// ��������
#define     MAX_E       2200                    // ���������ŵ����ֵ
#define     SAVEVALUE   2000                    // ����ת�������ֵ


enum
{
    ENERGY_ERR_NONE,                            //RAM����У��û�д�
    ENERGY_ERR_RAM,                             //RAMУ���д�
};

//��Ӧ�ò�ӿڵ�һ�º�ͳһ���������ݵ�λΪ0.01kwh
typedef struct
{                   // ��λ��0.01kwh
    uint8 ucP;        // ������������
    uint8 ucN;        // ������������

}S_ENERGY;
AP_ENERGYEXT    S_ENERGY gs_Energy;       // �����һ���ṹ�壬�ɱ�֤���ݵ�������ͬʱ�����ģ��Ľӿ���ͳһ��

AP_ENERGYEXT uint8 guc_GateCF;                  // CF����ķ�Ƶ��ϵ����ͨ������ȡ
AP_ENERGYEXT uint8 guc_UnitCF;                  //CF����ĵ�λ���ݣ�ͨ������ȡ



// ���������ṹ
typedef struct
{
    uint16 uiEP;                                //�����й�����
//  uint16 uiEN;                                //�����й�����
    uint16 uiCRC;                               //��������CRCУ��
} ENERGYDATA;

#define MultariffMeter

// �й������ֽ���
typedef struct
{
#ifndef MultariffMeter
    int32   lCP[1];                           //����й�,c��calculate����˼
    uint32  ulP[1];                           //�����й�
    uint32  ulN[1];                           //�����й�   
#else 
    int32   lCP[1+4];                           //����й�,c��calculate����˼
//  uint32  ulP[1+4];                           //�����й�
//  uint32  ulN[1+4];                           //�����й�
#endif
    uint16  uiCRC;                              //CRCУ���
}ENERGYACTIVE;

AP_ENERGYEXT ENERGYDATA gs_EnergyData;          //��ǰ��������
AP_ENERGYEXT ENERGYDATA gs_EnergyData_bak;      //��ǰ������������
AP_ENERGYEXT ENERGYACTIVE gs_EnergyA;           //��ǰ�����й�����(����������)
AP_ENERGYEXT uint8 guc_EPCalcType;              //����й���ʽ��

//�ṹ���壬����ʵ�������ı궨
typedef struct meterc
{
  uint16 ui_MC;             // ���峣��
  uint8 uc_CFGate;          // CF��������ֵ
  uint8 uc_CFUinit;         // ÿ����λ�����Ĵ�С
}S_METERC;

#define MeterConstLen    9   // �����б�ĸ���

#ifdef AP_ENERGYSELF
const S_METERC code gs_MeterConstT[MeterConstLen]=      //���ݱ�����ȷ��CF�ķ�Ƶϵ����ÿ����λ�����Ĵ�С
{
//  {10000,   10, 1},           // ������10000�����CF����10��Ƶ�������������С��0.001 x1
//  {8000,    8,  1},           // ������8000�����CF����8��Ƶ�������������С��0.001 x1
//  {5000,    5,  1},
  {3000,    3,  1},
  {2000,    2,  1},
  {1000,    1,  1},
  {6400,    64, 10},          // ������6400�����CF����64��Ƶ�������������С��0.001  x10
  {3200,    32, 10},
  {1600,    16, 10},
  {1200,    12, 10},
  {800, 8,  10},
//  {500, 5,  10},
//  {400, 4,  10},
//  {200, 2,  10},
  {100, 1,  10},
};
#else

#endif




void TaskEnergy(void);
void Eny_EnergyProc(void);
void Eny_EnergyClrCur(uint8 ucType);
void Eny_CheckEnergy(void);
uint8 Eny_CheckEnergyActiveRAM(void);
int16 Eny_GetEp1(uint8 index, uint8 fee);
void Eny_EnergyActiveSave(void);
void Eny_PurCheckRAMEny(void);
void Eny_RefCalcType(void);

void Eny_JbPm_GetE2(void);
void Eny_RefVar(void);
void Eny_JbPm_MeterConst(void);
void Eny_JbPm_UpdateRam(uint8 *pjb);
void EnergyCBRManage(void);
#endif
