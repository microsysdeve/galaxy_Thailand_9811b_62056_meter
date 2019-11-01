#ifndef _DR_ENERGY_H_
    #define _DR_ENERGY_H_

#ifndef ENERGYBOTTOMEXT
    #define ENERGYBOTTOMEXT extern
#else
    #define DR_ENERGYSELF
#endif

#define Const_MaxCf     0x05//���������

#define ULEVEL   200         //��ʼ����ʾ�ĵ�ѹ20.0V
#define ADCFRE   819200

#define DATAOIU     0x1005          //˲ʱ��ѹԭʼֵ
#define DATAOII1    0x100A          //ͨ��I1˲ʱ����ԭʼֵ
#define DATAOII2    0x100F          //ͨ��I2˲ʱ����ԭʼֵ
#define DATAIAU     0x1051          //˲ʱ��ѹ����ֵ
#define DATAIAI1    0x1052          //ͨ��I1˲ʱ��������ֵ
#define DATAIAI2    0x1053          //ͨ��I2˲ʱ��������ֵ
#define DATAIDU     0x103A          //˲ʱ��ѹֱ��ֵ
#define DATAIDI1    0x1041          //ͨ��I1˲ʱ����ֱ��ֵ
#define DATAIDI2    0x1048          //ͨ��I2˲ʱ����ֱ��ֵ

#define DATAOM      0x10CE          //Mͨ��ԭʼ����ֵ�Ĵ���
#define DATADM      0x10CF          //Mͨ��ֱ������ֵ�Ĵ���

#define DATAADM     0x10D0          //Mͨ��ֱ����ƽ������ֵ�Ĵ���
#define DATAIP      0x10D1          //˲ʱ�й�����
#define DATAIQ      0x10D2          //˲ʱ�޹�����
#define RMSIU       0x10D3          //˲ʱ��ѹ��Чֵ
#define RMSII1      0x10D4          //I1ͨ��˲ʱ������Чֵ
#define RMSII2      0x10D5          //I2ͨ��˲ʱ������Чֵ
#define DATAP       0x10D6          //��ƽ���й�����
#define DATAQ       0x10D7          //��ƽ���޹�����
#define RMSU        0x10D8          //��ƽ����ѹ��Чֵ
#define RMSI1       0x10D9          //I1ͨ����ƽ��������Чֵ
#define RMSI2       0x10DA          //I2ͨ����ƽ��������Чֵ
#define DATAAP1     0x10DB          //I1ͨ����ƽ�����ڹ���
#define DATAAP2     0x10DC          //I2ͨ����ƽ�����ڹ���

#define SCP         0x10DD          //�й����ʱȲ�Ĵ���
#define SCQ         0x10DE          //�޹����ʱȲ�Ĵ���
#define SCU         0x10DF          //��ѹ��Чֵ�Ȳ�Ĵ���
#define SCI1        0x10E0          //ͨ��I1������Чֵ�Ȳ�Ĵ���
#define SCI2        0x10E1          //ͨ��I2������Чֵ�Ȳ�Ĵ���
#define PARAPC      0x10E2          //�й����ʶ��β����Ĵ���
#define PARAQC      0x10E3          //�޹����ʶ��β����Ĵ���

#define PPCNT       0x10F0          //�����й�����������
#define NPCNT       0x10F1          //�����й�����������
#define PPCFCNT     0x10F2          //�����й��������������
#define NPCFCNT     0x10F3          //�����й��������������

#define GATEP       0x10F4          //�й�������������ֵ�Ĵ���
#define GATECP      0x10F5          //�й�����Ǳ������ֵ�Ĵ���

#define PQCNT       0x10F6          //�����޹�����������
#define NQCNT       0x10F7          //�����޹�����������
#define PQCFCNT     0x10F8          //�����޹��������������
#define NQCFCNT     0x10F9          //�����޹��������������

#define GATEQ       0x10FA          //�޹�������������ֵ�Ĵ���
#define GATECQ      0x10FB          //�޹�����Ǳ������ֵ�Ĵ���
#define DATACP      0x10FC          //��������ֵ�Ĵ���

#define DATAFREQ    0x10FD          //Ƶ��ֵ�Ĵ���


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
    uint16 ui_MeterC;   // ����
    uint16 ui_Un;       // ��Ƶ�ѹ
    uint16 ui_Ib;       // ��Ƶ���
    
    uint8  uc_GatepH;   //�й�����ֵ��8λ
    uint32 ul_GatepL;   //�й�������������ֵ��32λ
    uint32 ul_Gatecp;   //�й�����Ǳ������ֵ32


    uint32 ul_SCP;      //�й��Ȳ�ֵ
    uint32 ul_SCQ;      //�޹����ʱȲ�
    uint32 ul_SCU;      //��ѹ��Чֵ�Ȳ�
    uint32 ul_SCI1;     //ͨ��I1������Чֵ�Ȳ�
    uint32 ul_SCI2;     //ͨ��I2������Чֵ�Ȳ�

    uint32 ul_PARAPC;   //�й����ʶ��β���
    uint32 ul_PARAQC;   //�޹����ʶ��β���

    uint8 uc_PhcCtrl1;  //I1ͨ���ǲ�
    uint8 uc_PhcCtrl2;  //I2ͨ���ǲ�

    uint32 ul_PG;
    uint32 ul_URmG;
    uint32 ul_I1RmG;
    uint32 ul_I2RmG;
    uint8  uc_ADCGain;
    uint16 ui_JbCRC;       // У�������CRC���
}S_JBPM;

ENERGYBOTTOMEXT S_JBPM gs_JbPm;            //У�����
ENERGYBOTTOMEXT uint32 u32PMdatal;
ENERGYBOTTOMEXT uint8  u8PMdatah;


typedef struct
{
   uint8 ucRevDirCnt;
   uint8 ucDirCnt;
   uint8 PDir;
}GS_PDIR;

ENERGYBOTTOMEXT GS_PDIR gs_PDirCnt;

//����Ϊ����������޹������Ľṹ�嶨�壬
typedef struct
{
    uint8 uc_P;       // �����й�����������
//  uint8 uc_N;       // �����й�����������
} S_POWERCF;

ENERGYBOTTOMEXT S_POWERCF gs_PowerCf;
ENERGYBOTTOMEXT uint8 guc_OpenCfTmCnt;
ENERGYBOTTOMEXT uint8 guc_CfOpenFlg;
ENERGYBOTTOMEXT uint8 guc_ResetFlg;
//��������
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
