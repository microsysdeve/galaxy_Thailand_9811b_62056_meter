/****************************************Copyright (c)**************************************************
**                                  �����򹤿Ƽ����޹�˾
**                                          ϵͳ���̲�
**
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: Ptl_1107.h
**��   ��   ��: LWB
**����޸�����: 2011��8��25��
**��        ��: 1107��Լ��������
**ע        �⣺
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: LWB
** ��  ��: v1.0
** �ա���: 2010��12��25��
** �衡��: ԭʼ�汾
********************************************************************************************************/
#ifndef _AP_1107_H_
#define _AP_1107_H_

#ifndef AP_1107_EXT
#define AP_1107_EXT extern
#endif

#define ComFrmLen       0x29

#define RDPWD           0x01        //������
#define WRPWD           0x02        //д����

#define Ret_OK          0x00        //��ȷ
#define Ret_Err         0xff        //����



#define  ReturnErr() {  /*�ָ���֡ͷ�ж�*/   gs_PtlCrt.uc_ComStep=Com_HD;\
                                          gs_PtlCrt.uc_CompLevel=0;\
                                          ComProcCtr->ucBuf[0]=AS_NAK;\
                                          ComProcCtr->ucLen=1;\
                                          guc_BodeDely=40;\
                        /*���ش�����*/      return Ret_OK;}




#define  ReturnNAK()    {ComProcCtr->ucBuf[0]=AS_NAK;\
                         ComProcCtr->ucLen=1;}

//ASCII�еĿ��Ʒ�
enum
{
    AS_NULL=0,
    AS_SOH,
    AS_STX,
    AS_ETX,
    AS_EOT,
    AS_END,
    AS_ACK,
    AS_BEL,
    AS_BS,
    AS_HT,
    AS_LF,
    AS_VT,
    AS_FF,
    AS_CR,
    AS_SO,
    AS_SI,
    AS_DLE,
    AS_DC1,
    AS_DC2,
    AS_DC3,
    AS_DC4,
    AS_NAK,
    AS_SYN,
    AS_ETB,
    AS_CAN,
    AS_EM,
    AS_SUB,
    AS_ESC,
    AS_FS,
    AS_GS,
    AS_RS,
    AS_US
};


enum  ENUMCOMSTATU
{//ͨѶ����
    Com_HD = 0,             //��ʼ����
    Com_BpsCk,              //������ȷ��֡
    Com_CntRd,              //������
//  Com_PR,                 //���״̬
    Com_PRdWr,              //��̶�д����
//  Com_PSet,               //���д����
};

#define COMOUTTM   5
#define COMPRLEVEL 0x55
typedef struct
{
    uint8 uc_ComStep;       //����
    uint8 uc_CompLevel;     //Ȩ��
    uint8 uc_TimeOut;       //��ʱ       
}PTL_1107CTR;

AP_1107_EXT PTL_1107CTR gs_PtlCrt;

#define     CNTRD_START       0x55
#define     CNTRD_STOP        0x00

typedef struct
{
    uint8 uc_CkBcc;
    uint8 uc_1107RdFrmCnt;
    uint8 uc_1107RdStatus;
}PTL_1107CTNRD;

AP_1107_EXT PTL_1107CTNRD gs_PtlCtnRd;

typedef code uint8 (*ComFPro)(S_COM *);   //������

//Atb����
//BIT7 ��Ҫת��ASCII��
#define TOASC    BIT7
#define IEC_WO   BIT6       //��д
#define IEC_RO   BIT5
#define IEC_RW   BIT5+BIT6
#define IEC_E2   BIT4


typedef struct
{
    string pOBS;        //OBSI��
    string pUint;       //��λ
    uint8 param;        //����������ָ��Ҫ���õĲ���
    uint8 ucAtb;        //����
    uint8 ucFPidx;      //��������ƫ��
}GS_IECCOM;


typedef uint32(*PFOBSProc)(uint8,uint8,void*);//����ָ��

#define     CNTRD_START       0x55
#define     CNTRD_STOP        0x00

//AP_1107_EXT uint8     guc_CheckBCC;
//AP_1107_EXT uint8     guc_1107RdFrmCnt;
//AP_1107_EXT uint8     guc_1107RdStatus;


extern const GS_IECCOM code gs_OBSCom[];
extern const PFOBSProc code gs_OBSFuction[];
extern const uint8 code ConstOBSFunCnt;
extern const uint8 code Cosnt_OBSLen;

enum
{
    Const_DataDisp=0,       //LCD��ʾ��
    Const_DataCOmRD,        //ͨѶ��
    Const_DataCOmWR,        //ͨѶд
};

#define  HEX2BCD    0x80
#define  ASC2BCD    0x40
typedef struct 
{
    uint16 uiE2Adrr;    //E2��ַ
    uint8  ucAtb;       //����
    uint8  ucLen;       //���ݳ���
}GSE2DATA;

/*******************************************************************************
**�����Ǻ�������
*******************************************************************************/
uint8 JbComHd(S_COM *ComProcCtr);
uint8 JbMode(S_COM *ComProcCtr);
uint8 PrRdWr(S_COM *ComProcCtr);
uint32 AutoJB(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadCurEgy(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadHisEgy(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadHisDemad(uint8 index,uint8 cmd,void *pvoid);
uint32 DateAndTimeProc(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadBodyOpOrMdTrDate(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadAlmFroze(uint8 index,uint8 cmd,void *pvoid);
uint32 E2DataProc(uint8 index,uint8 cmd,void *pvoid);
uint32 FlashDataProc(uint8 index,uint8 cmd,void *pvoid);

uint32 ClearMeterProc(uint8 index,uint8 cmd,void *pvoid);
uint32 DoNoting(uint8 index,uint8 cmd,void *pvoid);
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pviod);
uint32 ReadInsData(uint8 index,uint8 cmd,void *pvoid);
uint8 ContinueRead(S_COM *ComProcCtr);
uint8 FindObsiPoint(uint8* Obsi,uint8 len);

 enum ENUMOBSMFUNLIST 
{
    _ReadCurEgy_ = 0,                 //��ȡ��ǰ�й�����   0
    _ReadHisEgy_,                 //��ȡ��ʷ�й�����   1
    _ReadHisDemad_,               //��ȡ��ʷ����      2
    _ReadBodyOpOrMdTrDate_,       //����Ǻ��߸��¼�   3
    _ReadPowDnJl_,                //�����¼         4
    _E2DataProc_,                 //��ȡE2����       5    
    _DateAndTimeProc_,            //��ȡ���ں�ʱ��    6 
    _ReadInsData_,                //��ȡ˲ʱ����      7
    _ClearMeterProc_,             //�����������      8
    _FlashDataProc_,                 //��ȡFLASH��       9
    _ReadAlmFroze_,
    _AutoJB_,                     //�Զ�У��
    _ENUMOBSMFUNLIST_End_, 

};


enum    ENUMENGRYDEF
{
    _code645_00000000_ = 0,
    _code645_00010000_,
    _code645_00020000_,
    
    _code645_prevbase_,
    _code645_00000001_ =_code645_prevbase_,
    _code645_00010001_,
    _code645_00020001_,
    
    _code645_00000002_,
    _code645_00010002_,
    _code645_00020002_,
    
     _code645_00000003_,
    _code645_00010003_,
    _code645_00020003_,
    
     _code645_00000004_,
    _code645_00010004_,
    _code645_00020004_,
    
    _code645_00000005_,
    _code645_00010005_,
    _code645_00020005_,
    
     _code645_00000006_,
    _code645_00010006_,
    _code645_00020006_ ,
    
     _code645_00000007_,
    _code645_00010007_,
    _code645_00020007_,
    
     _code645_00000008_,
    _code645_00010008_,
    _code645_00020008_ ,
    
     _code645_00000009_,
    _code645_00010009_,
    _code645_00020009_ ,
    
    _code645_0000000A_,
    _code645_0001000A_,
    _code645_0002000A_,
    
     _code645_0000000B_,
    _code645_0001000B_,
    _code645_0002000B_,
    
     _code645_0000000C_,
    _code645_0001000C_,
    _code645_0002000C_ ,
    
    _code645_OnLineEvent_,  //   ���µ��¼
    _code645_03110000_ = _code645_OnLineEvent_,
    _code645_03110001_,
    _code645_03110002_,
    _code645_03110003_,
    _code645_03110004_,
    _code645_03110005_,
    _code645_03110006_,
    _code645_03110007_,
    _code645_03110008_,
    _code645_03110009_,
    _code645_0311000A_,  
    
}   ;
            
      
#endif 