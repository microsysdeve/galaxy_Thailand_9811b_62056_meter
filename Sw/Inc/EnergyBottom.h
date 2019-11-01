#ifndef _DR_ENERGY_H_
    #define _DR_ENERGY_H_

#ifndef ENERGYBOTTOMEXT
    #define ENERGYBOTTOMEXT extern
#else
    #define DR_ENERGYSELF
#endif

#define CFGDELAY 32   //��ȡ˫��RAM��ʱʱ��
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




 
#define Const_MaxCf     0x05//���������
#define ADCFRE   819200
#define PLEVEL   65         //��������
#define IALEVEL  25         //��������
#define IBLEVEL  70
#define ULEVEL   200         //��ʼ����ʾ�ĵ�ѹ20.0V
#define CRIULEVEL1  1694
#define CRIULEVEL2  2640
 
typedef struct
{
    uint16 ui_MeterC;   // ����
    uint16 ui_Un;       // ��Ƶ�ѹ
    uint16 ui_Ib;       // ��Ƶ���

    uint32 ul_Gatep;    //�й�������������ֵ32λ
    uint32 ul_Gateq;    //�й�������������ֵ32λ
    uint32 ul_Gatecp;   //�й�����Ǳ������ֵ32
    uint32 ul_GateOSC;  //

    uint32 ul_SCP;      //�й��Ȳ�ֵ 
    uint32 ul_SCQ;      //�޹����ʱȲ�
    uint32 ul_SCU;      //��ѹ��Чֵ�Ȳ�
    uint32 ul_SCI1;     //ͨ��I1������Чֵ�Ȳ�
    uint32 ul_SCI2;     //ͨ��I2������Чֵ�Ȳ�
 
    uint32 ul_PARAPC;   //�й����ʶ��β���
    uint32 ul_PARAQC;   //�޹����ʶ��β���

    uint8 uc_PhcCtrl1;  //I1ͨ���ǲ�
    uint8 uc_PhcCtrl2;  //I2ͨ���ǲ�

    uint32 ul_PG;       //���ʱ���ϵ��
    uint32 ul_QG;       //���ʱ���ϵ��
    uint32 ul_URmG;     //��ѹͨ������ϵ��
    uint32 ul_I1RmG;    //����ͨ��1����ϵ��
//    uint32 ul_I1RmGOSC;    //����ͨ��1����ϵ�� OSC
//    uint32 ul_I1RmG800;    //����ͨ��1����ϵ�� MEA800k
    uint32 ul_I2RmG;    //����ͨ��2����ϵ��    
//    uint32 ul_I2RmGOSC;    //����ͨ��2����ϵ�� OSC   
//    uint32 ul_I2RmG800;    //����ͨ��2����ϵ�� MEA800k
    uint32 ul_SCI1_800; //ͨ��I1������Чֵ�Ȳ�
    uint32 ul_SCI2_800; //ͨ��I2������Чֵ�Ȳ�
    
    uint8 uc_AnaG;     //ģ������(����I2 bit[12:9]��I1 bit[7:4]��U bit[3:0])
    uint16 ui_JbCRC;    // У�������CRC���
}S_JBPM;

ENERGYBOTTOMEXT S_JBPM gs_JbPm;            //У�����
ENERGYBOTTOMEXT uint32 u32PMdatal;
ENERGYBOTTOMEXT uint8  u8PMdatah;

typedef struct
{
    int32 ul_Adjust;    // ������Ȳ��
    uint16 ui_CRC;       // CRC
}S_GSCP;

ENERGYBOTTOMEXT S_GSCP gs_GiantSCP;
ENERGYBOTTOMEXT uint8 guc_GiantSCPflag;
ENERGYBOTTOMEXT uint8 guc_GiantSCPcnt;

//����Ϊ����������޹������Ľṹ�嶨�壬
typedef struct                   
{
    uint8 uc_Pz;       // ����������������
//    uint8 uc_P1;       // �����й�����1
//    uint8 uc_P2;       // �����й�����2����������
//    uint8 uc_P3;       // �����й�����3����������
//    uint8 uc_P4;       // �����й�����3����������

    uint8 uc_Nz;       // ����������������
//    uint8 uc_N1;       // �����й�����1
//    uint8 uc_N2;       // �����й�����2����������
//    uint8 uc_N3;       // �����й�����3����������
//    uint8 uc_N4;       // �����й�����3����������
} S_POWERCF; 

ENERGYBOTTOMEXT S_POWERCF gs_PowerCf;

//ENERGYBOTTOMEXT  uint8 guc_PowRCnt;        //���ʷ������
//ENERGYBOTTOMEXT  uint8 guc_PowRExitCnt;    //���ʷ����˳�����

typedef struct
{
    uint32 Pa;                          //����2λС�� ��λΪW
    uint16 Ua;                          //����2λС�� ��λΪV
    uint16 Ia;                          //����3ΪС�� ��λΪA
}S_CHECKMETER;

ENERGYBOTTOMEXT S_CHECKMETER gs_Checkmeter;//У���ʱȶ�����


ENERGYBOTTOMEXT uint8 guc_CfOpenCnt;
ENERGYBOTTOMEXT uint8 guc_CfOpenFlg;

#define SETA 0x00
#define SETB 0x55
typedef struct
{
    uint8 ucSta;                //��ǰͨ��
    uint8 ucACnt;               //Aͨ������
    uint8 ucBCnt;               //Bͨ������
    uint8 ucGate;               //��������
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

//��������
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
