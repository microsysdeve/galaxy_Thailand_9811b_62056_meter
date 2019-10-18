#define	AP_1107_EXT
#include "Include.h"
struct            ST645CommTimeFormat
{
    unsigned char               cSec;
    unsigned char               cMin;
    unsigned char               cHour;
    unsigned char               cDay;
    unsigned char               cMonth;
    unsigned char               cYear;
};

const uint8 code guc_PcComEd[]=
{
    AS_SOH, 'B','0',AS_ETX,//0x71
};//SOH,B0,ETX,

const uint8 code guc_WROBS[]=
{
    AS_SOH,'W',0xaa,AS_STX
};//SOH W1 STX

const uint8 code guc_RdOBS[]=
{
    AS_SOH,'R','2',AS_STX
};//SOH R1 STX

const uint8 code guc_Frmhd[]=
{   
  '/','?','!','\r','\n'         //"/?!CRLF"
};

const uint8 code guc_FrmADrrhd[]=
{   
  '/','?',0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,'!','\r','\n'         //"/?xxxxxx!CRLF"
};
 #define                 _defbps_    _bps300_
//#define                 _defbps_    _bps2400_
const uint8 code guc_BpsCheck[]=
{
    '/','L','U','N',0x30+_defbps_,'<','1','>','L','U','N','1','0',//'0','0','0','\r','\n'
};//�ظ�ʶ��֡ͷ��ȷ��������

const uint8 code guc_ACKHd1[6]=
{
    AS_ACK,'0',0x30+_defbps_,0xAA,'\r','\n'
};//ACK 0 Z��3��2400BPS 

const uint8 code  guc_PgAck[]=
{
    AS_SOH,'P','0',AS_STX,'(',')',AS_ETX,0x60,
};//SOH P0 STX () ETX 

const uint8 code guc_PgPCAck[]=
{
    AS_SOH,'P',0xaa,AS_STX,'(',0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,')',AS_ETX
};//SOH PX STX(XXXXXX)ETX

//const string code guc_OwId[]=
//{
//    "VANGO",
//};

const uint8 code guc_InitCmd[]=
{
    AS_SOH,'V','G',AS_STX,'C','L','R','-','0','0',AS_ETX,0x60,
};

#define BE_ReadP(a,b,c)   {}  //gs_E2DataTable[index].uiE2Adrr,ASCII,8);
#define  EnyB_IBAutoCheck()   {}  //g
#define  EnyB_AutoChkAngle()   {}  //g
#define   _ReadBodyOpOrMdTrDate_time_           0xfe 
/*=========================================================================================\n
* @function_name: gs_OBSCom
* @function_file: Ptl_1107.c
* @����: ͨѶ��ʾ ��ʶ���ı�
* 
* @����: 
* @����: 
* @����: Lwb (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
    
    
    
const char as[]="";
const GS_IECCOM    gs_OBSCom[]=
{   //obsi              uint             param     atb           pfindex  

    //��ǰ���� 
    { "1.8.0",          "*kWh)\r\n",    _code645_00000000_,       IEC_RO,       _ReadCurEgy_},
    { "1.8.1",          "*kWh)\r\n",    _code645_00010000_-_code645_00000000_,       IEC_RO,     _ReadCurEgy_},
    { "1.8.2",          "*kWh)\r\n",    _code645_00020000_-_code645_00000000_,       IEC_RO,     _ReadCurEgy_},
    //{ "1.8.3",          "*kWh)\r\n",     _code645_00010000-_code645_00000000,      IEC_RO,     _ReadCurEgy_},
    //{ "1.8.4",          "*kWh)\r\n",     _code645_00020000-_code645_00000000,      IEC_RO,     _ReadCurEgy_},

 
    //��1�µ���
    { "1.8.0*1",        "*kWh)\r\n",    _code645_00000001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*1",        "*kWh)\r\n",    _code645_00010001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*1",        "*kWh)\r\n",    _code645_00020001_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*1",        "*kWh)\r\n",    0x03,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*1",        "*kWh)\r\n",    0x04,       IEC_RO,     _ReadHisEgy_},

    //��2�µ���
    { "1.8.0*2",        "*kWh)\r\n",    _code645_00000002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*2",        "*kWh)\r\n",    _code645_00010002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*2",        "*kWh)\r\n",    _code645_00020002_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
   // { "1.8.3*2",        "*kWh)\r\n",    0x13,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*2",        "*kWh)\r\n",    0x14,       IEC_RO,     _ReadHisEgy_},


    //��3�µ���
    { "1.8.0*3",        "*kWh)\r\n",    _code645_00000003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*3",        "*kWh)\r\n",    _code645_00010003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*3",        "*kWh)\r\n",    _code645_00020003_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*3",        "*kWh)\r\n",    0x23,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*3",        "*kWh)\r\n",    0x24,       IEC_RO,     _ReadHisEgy_},

    //��4�µ���
    { "1.8.0*4",        "*kWh)\r\n",    _code645_00000004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*4",        "*kWh)\r\n",    _code645_00010004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*4",        "*kWh)\r\n",    _code645_00020004_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*4",        "*kWh)\r\n",    0x33,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*4",        "*kWh)\r\n",    0x34,       IEC_RO,     _ReadHisEgy_},

    //��5�µ���
    { "1.8.0*5",        "*kWh)\r\n",    _code645_00000005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*5",        "*kWh)\r\n",    _code645_00010005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_}, 
    { "1.8.2*5",        "*kWh)\r\n",    _code645_00020005_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*5",        "*kWh)\r\n",    0x43,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*5",        "*kWh)\r\n",    0x44,       IEC_RO,     _ReadHisEgy_},

    //��6�µ���
    { "1.8.0*6",        "*kWh)\r\n",    _code645_00000006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*6",        "*kWh)\r\n",    _code645_00010006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*6",        "*kWh)\r\n",    _code645_00020006_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*6",        "*kWh)\r\n",    0x53,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*6",        "*kWh)\r\n",    0x54,       IEC_RO,     _ReadHisEgy_},

    //��7�µ���
    { "1.8.0*7",        "*kWh)\r\n",    _code645_00000007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*7",        "*kWh)\r\n",    _code645_00010007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*7",        "*kWh)\r\n",    _code645_00020007_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*7",        "*kWh)\r\n",    0x63,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*7",        "*kWh)\r\n",    0x64,       IEC_RO,     _ReadHisEgy_},

    //��8�µ���
    { "1.8.0*8",        "*kWh)\r\n",    _code645_00000008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*8",        "*kWh)\r\n",    _code645_00010008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*8",        "*kWh)\r\n",    _code645_00020008_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*8",        "*kWh)\r\n",    0x73,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*8",        "*kWh)\r\n",    0x74,       IEC_RO,     _ReadHisEgy_},

    //��9�µ���
    { "1.8.0*9",        "*kWh)\r\n",    _code645_00000009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*9",        "*kWh)\r\n",    _code645_00010009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*9",        "*kWh)\r\n",    _code645_00020009_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*9",        "*kWh)\r\n",    0x83,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*9",        "*kWh)\r\n",    0x84,       IEC_RO,     _ReadHisEgy_},

    //��10�µ���
    { "1.8.0*10",       "*kWh)\r\n",    _code645_0000000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*10",       "*kWh)\r\n",    _code645_0001000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*10",       "*kWh)\r\n",    _code645_0002000A_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*10",       "*kWh)\r\n",    0x93,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*10",       "*kWh)\r\n",    0x94,       IEC_RO,     _ReadHisEgy_},

    //��11�µ���
    { "1.8.0*11",       "*kWh)\r\n",    _code645_0000000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*11",       "*kWh)\r\n",    _code645_0001000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*11",       "*kWh)\r\n",    _code645_0002000B_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*11",       "*kWh)\r\n",    0xA3,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*11",       "*kWh)\r\n",    0xA4,       IEC_RO,     _ReadHisEgy_},

    //��12�µ���
    { "1.8.0*12",       "*kWh)\r\n",    _code645_0000000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.1*12",       "*kWh)\r\n",    _code645_0001000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    { "1.8.2*12",       "*kWh)\r\n",    _code645_0002000C_-_code645_prevbase_,   IEC_RO,     _ReadHisEgy_},
    //{ "1.8.3*12",       "*kWh)\r\n",    0xB3,       IEC_RO,     _ReadHisEgy_},
    //{ "1.8.4*12",       "*kWh)\r\n",    0xB4,       IEC_RO,     _ReadHisEgy_},


    {"1.6.0",           ")",            0x00,       IEC_RO,     0x02},    //��ǰ�������������ʱ��
    {"1.6.0*1",         ")",            0x10,       IEC_RO,     0x02},    //��1���������������ʱ��
    {"1.6.0*2",         ")",            0x20,       IEC_RO,     0x02},    //��2���������������ʱ��
    {"1.6.0*3",         ")",            0x30,       IEC_RO,     0x02},    //��3���������������ʱ��
    {"1.6.0*4",         ")",            0x40,       IEC_RO,     0x02},    //��4���������������ʱ��
    {"1.6.0*5",         ")",            0x50,       IEC_RO,     0x02},    //��5���������������ʱ��
    {"1.6.0*6",         ")",            0x60,       IEC_RO,     0x02},    //��6���������������ʱ��
    {"1.6.0*7",         ")",            0x70,       IEC_RO,     0x02},    //��7���������������ʱ��
    {"1.6.0*8",         ")",            0x80,       IEC_RO,     0x02},    //��8���������������ʱ��
    {"1.6.0*9",         ")",            0x90,       IEC_RO,     0x02},    //��9���������������ʱ��
    {"1.6.0*10",        ")",            0xA0,       IEC_RO,     0x02},    //��10���������������ʱ��
    {"1.6.0*11",        ")",            0xB0,       IEC_RO,     0x02},    //��11���������������ʱ��
    {"1.6.0*12",        ")",            0xC0,       IEC_RO,     0x02},    //��12���������������ʱ��


    //�¼�
    {"96.70",           ")",            _ReadBodyOpOrMdTrDate_time_,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //�����ʱ��

    {"96.71",           ")",            0,         IEC_RO,     _ReadBodyOpOrMdTrDate_},    //����ť��ʱ�估����
    {"96.71*1",         ")",            0x1,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��1�ο���ť��ʱ�估����
    {"96.71*2",         ")",            0x2,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��2�ο���ť��ʱ�估����
    {"96.71*3",         ")",            0x3,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��3�ο���ť��ʱ�估����
    {"96.71*4",         ")",            0x4,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��4�ο���ť��ʱ�估����
    {"96.71*5",         ")",            0x5,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��5�ο���ť��ʱ�估����
    {"96.71*6",         ")",            0x6,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��6�ο���ť��ʱ�估����
    {"96.71*7",         ")",            0x7,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��7�ο���ť��ʱ�估����
    {"96.71*8",         ")",            0x8,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��8�ο���ť��ʱ�估����
    {"96.71*9",         ")",            0x9,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��9�ο���ť��ʱ�估����
    {"96.71*10",        ")",            0xa,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��10�ο���ť��ʱ�估����
    {"96.71*11",        ")",            0xb,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��11�ο���ť��ʱ�估����
    {"96.71*12",        ")",            0xc,       IEC_RO,     _ReadBodyOpOrMdTrDate_},    //��12�ο���ť��ʱ�估����

    {"96.7.1",          ")",      _code645_03110000_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //�����ܴ���
    {"96.77.1*1",       ")",      _code645_03110001_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��1�ε���ʱ��ͽ���ʱ��
    {"96.77.1*2",       ")",      _code645_03110002_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��2�ε���ʱ��ͽ���ʱ��
    {"96.77.1*3",       ")",      _code645_03110003_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��3�ε���ʱ��ͽ���ʱ��
    {"96.77.1*4",       ")",      _code645_03110004_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��4�ε���ʱ��ͽ���ʱ��
    {"96.77.1*5",       ")",      _code645_03110005_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��5�ε���ʱ��ͽ���ʱ��
    {"96.77.1*6",       ")",      _code645_03110006_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��6�ε���ʱ��ͽ���ʱ��
    {"96.77.1*7",       ")",      _code645_03110007_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��7�ε���ʱ��ͽ���ʱ��
    {"96.77.1*8",       ")",      _code645_03110008_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��8�ε���ʱ��ͽ���ʱ��
    {"96.77.1*9",       ")",      _code645_03110009_-_code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��9�ε���ʱ��ͽ���ʱ��
    {"96.77.1*10",      ")",      _code645_0311000A_- _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��10�ε���ʱ��ͽ���ʱ��
    //{"96.77.1*11",      ")",      _code645_03110000_ _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��11�ε���ʱ��ͽ���ʱ��
    //{"96.77.1*12",      ")",      _code645_03110000_ _code645_OnLineEvent_,       IEC_RO,     _ReadPowDnJl_},    //��12�ε���ʱ��ͽ���ʱ��

    //���
    {"0.0.0",           ")",            0x00,       IEC_RW,     _E2DataProc_},
    {"96.97.1",         ")",            0x01,       IEC_RW,     _E2DataProc_},    //д�������1
    {"96.97.2",         ")",            0x02,       IEC_RW,     _E2DataProc_},    //д�������2
    {"96.97.3",         ")",            0x03,       IEC_RW,     _E2DataProc_},    //д�������3
    {"0.8.0",           "*min)",        0x04,       IEC_RW,     _E2DataProc_},    //��������
    {"96.1.3",          ")",            0x05,       IEC_RO,     _E2DataProc_},    //��������
    {"96.2.5",          ")",            0x06,       IEC_RO,     _E2DataProc_},    //У������
    {"96.2.2",          ")",            0x07,       IEC_RO,     _E2DataProc_},    //�����޸�����
    {"96.8.0",          "*min)",        0x08,       IEC_RW,     _E2DataProc_},    //���ɼ�¼����

    {"96.96.1",         ")",            0x09,       IEC_WO,     _E2DataProc_},    //д��P1����
    {"96.96.2",         ")",            0x0A,       IEC_WO,     _E2DataProc_},    //д��P2��

    {"96.6.1",          ")",            0x0b,       IEC_RO,     _E2DataProc_},    //���״̬��

    {"96.50",          ")",             0x0C,       IEC_RW,     _E2DataProc_},    //�����շ���ʱ��
    {"96.51",          ")",             0x0D,       IEC_RW,     _E2DataProc_},    //�����շ���ʱ��
    {"96.52",          ")",             0x0E,       IEC_RW,     _E2DataProc_},    //�����շ���ʱ��


    {"96.60",          ")",             0x0F,       IEC_RW,     _E2DataProc_},    //�����շ���
    {"96.61",          ")",             0x10,       IEC_RW,     _E2DataProc_},    //�����շ���
    {"96.62",          ")",             0x11,       IEC_RW,     _E2DataProc_},    //�����շ���


    { "0.9.1",          ")",            0x01,       IEC_RW,     _DateAndTimeProc_},    //ʱ��

    { "0.9.2",          ")",            0x00,       IEC_RW,     _DateAndTimeProc_},    //����

    { "0.9.5",          ")",            0x02,       IEC_RW,     _DateAndTimeProc_},    //����

    
    {"32.7.0",          "*V)",          0x01,       IEC_RO,     _ReadInsData_},    //��ѹ
    {"31.7.0",          "*A)",          0x02,       IEC_RO,     _ReadInsData_},    //����
    
    //��������
    {"FF.0.0",          ")",            0x00,       IEC_WO,     0x08},
    {"FF.0.1",          ")",            0x01,       IEC_WO,     0x09},
 
};

const uint8 code Cosnt_OBSLen=dim(gs_OBSCom);
/*=========================================================================================\n
* @function_name: gs_OBSFuction
* @function_file: Ptl_1107.c
* @����: ͨѶ��ʾ�������б�
* 
* @����: 
* @����: 
* @����: Lwb (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
 const PFOBSProc code gs_OBSFuction[]=
{
    ReadCurEgy,                 //��ȡ��ǰ�й�����   0
    ReadHisEgy,                 //��ȡ��ʷ�й�����   1
    ReadHisDemad,               //��ȡ��ʷ����      2
    ReadBodyOpOrMdTrDate,       //����Ǻ��߸��¼�   3
    ReadPowDnJl,                //�����¼         4
    E2DataProc,                 //��ȡE2����       5
    DateAndTimeProc,            //��ȡ���ں�ʱ��    6 
    ReadInsData,                //��ȡ˲ʱ����      7
    ClearMeterProc,             //�����������      8
    AutoJB,                     //�Զ�У��

};
 
const  uint8 code ConstOBSFunCnt=dim(gs_OBSFuction);  

/*=========================================================================================\n
* @function_name: CmpStr
* @function_file: Ptl_1107.c
* @����: �Ƚ��ַ����Ƿ���ȷ��������Ƚϵ�λ�ò���0xaa
*        ���Ҳ���ȵĻ������ش���
* 
* 
* @������ 
* @param:cmped  
* @param:cmp  
* @param:len  
* 
* @���أ� 
* @return: uint8 
* @����: Lwb (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
uint8 CmpStr(uint8* cmped,const uint8 code * cmp,uint16 len)
{
	uint8 i;
    for(i=0;i<len;i++)
    {
        if(cmped[i]!=cmp[i]
		&&((uint8)cmp[i]!=0xAA))	 //���ﲻǿ��ת��,�Ƚ��ַ���uint8�᲻�� 
        {
            return Ret_Err;
        }
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: FindObsiPoint
* @function_file: Ptl_1107.c
* @����: ��ͨѶ���ı��в��Ҷ�ӦOBSI���λ�ã��ж�Ӧ��OBSI ����λ�ã����򷵻�0XFF
* 
* 
* @����: 
* @param:Obsi  ͨѶ������ʾ���Ӧ��OBSI
* @param:len   OBSI���Ӧ�ĳ���
* 
* @����: 
* @return: uint8 ����OBSI���λ��
* @����: Lwb (2011-8-29)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 FindObsiPoint(uint8* Obsi,uint8 len)
{
    uint8 i;
    for(i=0;i<Cosnt_OBSLen;i++)
    {
        if(ApiCodeBufCmp((uint8 code  *)gs_OBSCom[i].pOBS,(uint8   *)Obsi,len)==CMP_EQU)//�Ƚ��ַ���
        {
            return i;
        }
    }
    return 0xff;   
}
/*=========================================================================================\n
* @function_name: CalBCC
* @function_file: Ptl_1107.c
* @����: ��������֡�е�BCC
* 
* 
* @������ 
* @param:OrgBCC  ԭʼBCC
* @param:Data  ������������
* @param:len  �����������ݳ���
* 
* @���أ� 
* @return: uint8  ���صļ�����BCC
* @����: Lwb (2011-9-5)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
uint8 CalBCC(uint8 OrgBCC, uint8 *Data,uint8 len)
{
	uint8 i;
    for(i=0;i<len;i++)
    {
        OrgBCC^=Data[i];
    }
    return OrgBCC;
}
/*=========================================================================================\n
* @function_name: DateFormat
* @function_file: Ptl_1107.c
* @����: ���ڡ�ʱ�䴦��
* 
* 
* @������ 
* @param:op     0-- ����  1--ʱ��
* @param:Ascii  ��������ڻ���ʱ���ASC
* @���أ� 
* @����: Lwb (2011-9-5)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void DateFormat(uint8 op,uint8 *ASCII)
{

    ASCII[7]=ASCII[5];      //�������
    ASCII[6]=ASCII[4];

    ASCII[4]=ASCII[3];      //�ֻ�����
    ASCII[3]=ASCII[2];


    if(op==0)               //���ڻ���ʱ���ʽ
    {
        ASCII[5]='-';
        ASCII[2]='-';
    }else 
    {
        ASCII[5]=':';
        ASCII[2]=':';
    }
}
/*=========================================================================================\n
* @function_name: DateAndTmFormat
* @function_file: Ptl_1107.c
* @����: ���ں�ʱ���ʽ����������ʱ�ָ��ĳ� ��-��-��,ʱ:��
* 
* 
* @������ 
* @param:ASCII  
* @����: 
* @����: Lwb  (2011-9-5)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
void DateAndTmFormat(uint8 *ASCII)
{
    ASCII[13]=ASCII[9];     //��
    ASCII[12]=ASCII[8];

    ASCII[10]=ASCII[7];     //ʱ
    ASCII[9]=ASCII[6];

    ASCII[7]=ASCII[5];     //��
    ASCII[6]=ASCII[4];

    ASCII[4]=ASCII[3];      //��
    ASCII[3]=ASCII[2];

    //��λ����ȷ
                            //���ڻ���ʱ���ʽ
    ASCII[5]='-';
    ASCII[2]='-';
    ASCII[8]=',';
    ASCII[11]=':';
}
/*=========================================================================================\n
* @function_name: DataorTmCpy
* @function_file: Ptl_1107.c
* @����: ��������ʱ�䣬ȥ�����ں�ʱ���ʽ�е�-����:,����11-09-12��� 110912
* 
* 
* @����: 
* @param:Ascii     ���������ں�ʱ���ascii��
* @param:OrgAscii  δ��������ں�ʱ���ʽ
* @����: 
* @����:   Lwb (2011-9-15)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void DataorTmCpy(uint8 *Ascii,uint8* OrgAscii)
{
    Ascii[0]=OrgAscii[0];      //��   ʱ

    Ascii[1]=OrgAscii[1];

    Ascii[2]=OrgAscii[3];     //��   ��

    Ascii[3]=OrgAscii[4];
    
    Ascii[4]=OrgAscii[6];     //��  ��
    
    Ascii[5]=OrgAscii[7];
}
/*=========================================================================================\n
* @function_name: JudgeOBSPsw
* @function_file: Ptl_1107.c
* @����: �ж������Ƿ���ȷ
* 
* 
* @������ 
* @param:buff  
* @param:type  
* 
* @���أ� 
* @return: uint8 
* @����: Lwb  (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
uint8 JudgeOBSPsw(uint8 *buff,uint8 ucLevel)
{
    uint32 E2Adrr;
	uint8 i;
    uint8 PassWord[8];
#ifdef PX_OPT
    if(ucLevel>0x02)
    {
        return Ret_Err;
    }
    E2Adrr=EEP_RDPASSWORD+(ucLevel-1)*8;
    BE_ReadP(E2Adrr,PassWord,8);

    for(i=0;i<8;i++)
    {
        if(buff[i]!=PassWord[i])
        {
            break;
        }
    }
    
    if(i>=8)
    {
         return Ret_OK;                         //����������ȷ
    }else
    {//����������
        return Ret_Err;                         //�������벻��ȷ
    }
#endif
   return Ret_OK;                         //����������ȷ
}
/*=========================================================================================\n
* @function_name: ReadCurEgy
* @function_file: Ptl_1107.c
* @����: ��ȡ�й�����
* 
* 
* @������ 
* @param:index  0~4���ܡ�����1~4
* @param:cmd    Const_DataCom-ͨѶ��Const_DataDisp����ʾ
* @param:pvoid  ��ȡ���ݻ���
* 
* @���أ� 
* @return: uint32 ���ݳ���
* @����: Lwb  (2011-9-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/

uint32 ReadCurEgy(uint8 index,uint8 cmd,void *pvoid)
{
    char        ctemp;
    Word32 Data;
    int16 Eadd;
    uint8 ASCII[9];
    strDispCode  pCode = { 0x0000000 ,0};
    //ȡ��ĳ����������
    switch ( index)
    {
    case   _code645_00000000_ - _code645_00000000_ :
          pCode.Code = 0x0 ;
          break;
    case   _code645_00010000_- _code645_00000000_ :
          pCode.Code = 0x00010000;
          break;
    case     _code645_00020000_- _code645_00000000_ :
        pCode.Code =0x00020000;
        break;
        
    } 
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );    
    RamData.InDisp = ctemp;    
    
    //Eadd = Eny_GetEp1(0, index);    
    //Data.lword =  gs_EnergyA.lCP[index]; 
    //Data.lword += Eadd;
    //Data.lword =123456;
    Data.lword = *((uint32 *)ComData);
    if ( Data.lword & 0x80000000)
        Data.lword &=0x7fffffff;
    Data.lword= Hex2BCD(Data.lword);        //����ת��ΪBCD��
    BCD2ASCII(Data.byte,ASCII,4);
    MemCpy(pvoid,ASCII,5);
    ((uint8*)pvoid)[5]='.';
    MemCpy(((uint8*)pvoid)+6,ASCII+5,3);
    return 9;
}

/*=========================================================================================\n
* @function_name: ReadHisEgy
* @function_file: Ptl_1107.c
* @����: ��ȡ��ʷ����
* 
* 
* @������ 
* @param:index  ��4λ���·ݣ���4λ�Ƿ��ʺ�
* @param:cmd    Const_DataCom-ͨѶ��Const_DataDisp����ʾ
* @param:pvoid  ��ȡ���ݻ���
* 
* @���أ� 
* @return: uint32 
* @����: Lwb (2011-9-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/

uint32 ReadHisEgy(uint8 index,uint8 cmd,void *pvoid)
{
    char        ctemp,cMonth ,cType;
   // uint8 ucMonth=(0xf0&index)>>4;
    //uint8 offset=0x0f&index;
    Word32 Data;
    uint8 ASCII[9];
    //DataProcRead2Slice(LSDLID,ucMonth,offset*4,4,Data.byte);
     strDispCode  pCode = { 0x0000000 ,0};
    //ȡ��ĳ����������
     cMonth = index /3;
     cType = index % 3;
     pCode.Code =  cType;
     pCode.Code <<=16;
       pCode.Code+= cMonth ;
     
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );
    RamData.InDisp = ctemp;    
    Data.lword = *((uint32 *)ComData);
     if ( Data.lword & 0x80000000)
        Data.lword &=0x7fffffff;
     
    Data.lword= Hex2BCD(Data.lword);    //����ת��ΪBCD��
    BCD2ASCII(Data.byte,ASCII,4);
    MemCpy(pvoid,ASCII,5);
    ((uint8*)pvoid)[5]='.';
    MemCpy(((uint8*)pvoid)+6,ASCII+5,3);
    return 9;
}
 
/*=========================================================================================\n
* @function_name: ReadHisDemad
* @function_file: Ptl_1107.c
* @����: ��ȡ��ʷ����
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @����: lwb (2014/4/2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint32 ReadHisDemad(uint8 index,uint8 cmd,void *pvoid)
{
 
    uint8 ucMonth=(0xf0&index)>>4;
    uint8 offset=0x0f&index;
    Word32 Data;
    uint8 buff[8];
    uint8 ASCII[10];
  //opt   DataProcRead2Slice(LSXLID,ucMonth,offset*4,8,buff);
    Data.lword=0;
    MemCpy(Data.byte,buff,3);

    Data.lword= Hex2BCD(Data.lword);    //����ת��ΪBCD��
    BCD2ASCII(Data.byte,ASCII,3);

    MemCpy(pvoid,ASCII,3);
    ((uint8*)pvoid)[3]='.';
    MemCpy(((uint8*)pvoid)+4,ASCII+3,3);
    ((uint8*)pvoid)[7]='*';
    ((uint8*)pvoid)[8]='k';
    ((uint8*)pvoid)[9]='W';
    ((uint8*)pvoid)[10]=')';
    ((uint8*)pvoid)[11]='(';
    //(003.088*kW)(06-07-05,10:08)
    //����

    BCD2ASCII(buff+3,ASCII,5);      //������ת����ASCii
    DateAndTmFormat(ASCII);         //ת�����ں�ʱ��ĸ�ʽ
    MemCpy(((uint8*)pvoid)+12,ASCII,14);

    return 26;
}
/*=========================================================================================\n
* @function_name: DateAndTimeProc
* @function_file: Ptl_1107.c
* @����: ��ȡ���ں�ʱ��,����
* 
* 
* @������ 
* @param:index  
* @param:cmd    Const_DataCom-ͨѶ��Const_DataDisp����ʾ
* @param:pvoid  ��ȡ���ݻ��� 
* 
* @���أ� 
* @return: uint32 
* @����: Lwb (2011-9-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:
* @�޸�����:  
===========================================================================================*/
uint32 DateAndTimeProc(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucData[4];
    uint8 ASCII[8];
    uint8 len;
    uint8 DtorTm=0xff;
    if(Const_DataCOmWR!=cmd)
    {
        switch(index)
        {
        case 0x00:                                      //����
        default:
            GetSysClock(ucData,Const_YYMMDD);
            DtorTm=0;
            len=3;
            break;
        case 0x01:                                      //ʱ��
            GetSysClock(ucData,Const_hhmmss);
            DtorTm=1;
            len=3;
            break;
        case 0x02:                                      //����
           ucData[0]=gs_DateTime.ucWeek+1;
           ucData[0]<<=4;
           len=1;
           break;
        }
    }
    else if(Const_DataCOmWR==cmd)                            //д
    {
        switch(index)
        {
        case 0x00:                                      //����
        default:
            DataorTmCpy(ASCII,pvoid);
            ASCII2BCD(ucData,ASCII,6);
            SetSysClock(ucData,Const_YYMMDD);
            break;
        case 0x01:                                      //ʱ��
            DataorTmCpy(ASCII,pvoid);
            ASCII2BCD(ucData,ASCII,6);
            SetSysClock(ucData,Const_hhmmss);
            break;
        case 0x02:                                      //����
            ucData[0]=*(uint8*)pvoid-0x31;              //���ڴ�1~7���0~6
            SetSysClock(ucData,Const_WW);
            break;
        }
        gui_RefreshEvent|=flgEtPara_Fee;
        return 0;
    }

    BCD2ASCII(ucData,ASCII,len);
    len=1;
    if(DtorTm!=0xff)
    {
        DateFormat(DtorTm,ASCII);
        len=8;
    }
    MemCpy(pvoid,ASCII,len);
    return len;
}
/*=========================================================================================\n
* @function_name: ReadBodyOpOrMdTrDate
* @function_file: Ptl_1107.c
* @����: ��ȡ������߸��¼�
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @����: lwb (2014/4/3)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/


uint32 ReadBodyOpOrMdTrDate(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 *ucbuf;//[10];
    uint8 ASCII[20];
    uint8 ucMonth=(0xf0&index)>>4;
    uint8 uctype=index;  //=0x0f&index;
   uint8 ctemp ;
   long  ltemp ;
    
    struct   ST645CommTimeFormat *stp =(struct   ST645CommTimeFormat *)ComData; 
    
    strDispCode  pCode = { 0x03300d01 ,0};
    
    if (   _ReadBodyOpOrMdTrDate_time_ != index ) 
             pCode.Code  += index ;
    
 tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );
    RamData.InDisp = ctemp;      
    if( _ReadBodyOpOrMdTrDate_time_ == uctype)                //�������ʱ��
    {
        ucbuf = &(stp->cMin); //opt      DataProcRead2Slice(KBGJLID, ucMonth, 0, 5, ucbuf); 
    }
    else                            //�����߸�ʱ��ʹ���
    {
     //optv   DataProcRead2Slice(KXGJLID, ucMonth, 0, 6, ucbuf); 
      ucbuf = &(stp->cMin);    
    }      
 //   BCD2ASCII(&(stp->cMin),ASCII,5);               //������ת����ASCii
  //  DateAndTmFormat(ASCII);                 //ת�����ں�ʱ��ĸ�ʽ
    //MemCpy(pvoid,ASCII,14);
    
    BCD2ASCII(&(stp->cMin),pvoid,5);               //������ת����ASCii
    DateAndTmFormat(pvoid);                 //ת�����ں�ʱ��ĸ�ʽ
   // MemCpy(pvoid,ASCII,14);    
    if( _ReadBodyOpOrMdTrDate_time_ == uctype )                        //�������ʱ��
    {
        return 14;
    }
    else
    {
      ((uint8*)pvoid)[14]=')';
      ((uint8*)pvoid)[15]='(';        
      ltemp = GetFrozeCnt(_FROZE_EOPEN_1_) + (FlashInfo.FrozeCnt[_FROZE_EK_1_]&1)?1:0;      
      ltemp -= index ;
      ctemp = ( ltemp < 0) ? 0:ltemp;
      ctemp = BCD(ctemp) ;
      BCD2ASCII((char *)&ctemp,((uint8*)pvoid)+16,1); //    BCD2ASCII(ucbuf,ASCII+5,1);         //������ת���ɴ���      
      return 18;
    }
 
}
/*=========================================================================================\n
* @function_name: DoNoting
* @function_file: Ptl_1107.c
* @����: �����������κ�����
* 
* 
* @������ 
* @param:index  
* @param:cmd  
* @param:pvoid  
* 
* @���أ� 
* @return: uint32 
* @����: Lwb (2011-9-5)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint32 DoNoting(uint8 index,uint8 cmd,void *pvoid)
{
    index=index;
    cmd=cmd;
    pvoid=pvoid;
    return 0;
}
 
const GSE2DATA  code gs_E2DataTable[]=
{
    { ((unsigned short)&FlashInfo.SafeInfo.TRx_Num),      ASC2BCD,     4},     //���         0x00
   
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[0][0]),        ASC2BCD,     2},     //������        0x01
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[1][0]),        ASC2BCD,     2},     //������        0x02
    { ((unsigned short)&FlashInfo.SetInfo.FrozeDT[2][0]),        ASC2BCD,     2},     //������        0x03
 #ifdef PX_OPT
    { EEP_XLZQ,        ASC2BCD,     1},     //��������      0x04
    { EEP_MANUDATE,    ASC2BCD,     3},     //��������      0x05
    { EEP_JBDATE,      ASC2BCD,     3},     //У������      0x06
    { EEP_FEEMDATE,    ASC2BCD,     5},     //�����޸�����   0x07
    { EEP_FHQXZQ,      ASC2BCD,     1},     //���ɼ�¼����   0x08
    { EEP_RDPASSWORD,  0x00,        8},     //�ȼ�1����     0x09
    { EEP_WRPASSWORD,  0x00,        8},     //�ȼ�2����     0x0A
    { EEP_BATTERYSTAT, ASC2BCD,     1},     //���״̬      0x0b
    { EEP_WORK_FEE_TIME,ASC2BCD,    16},    //�����շ���ʱ�� 0x0c
    { EEP_SAT_FEE_TIME, ASC2BCD,    16},    //����������ʱ�� 0x0d
    { EEP_SUN_FEE_TIME, ASC2BCD,    16},    //�����շ���ʱ�� 0x0e

    { EEP_WORK_FEE,     ASC2BCD,    4},     //�����շ���     0x0f
    { EEP_SAT_FEE,      ASC2BCD,    4},     //����������     0x10
    { EEP_SUN_FEE,      ASC2BCD,    4},     //�����շ���     0x11
#endif
};

const  uint8 code ConstE2DataTableCnt=dim(gs_E2DataTable);
/*=========================================================================================\n
* @function_name: E2DataProc
* @function_file: Ptl_1107.c
* @����: ��ȡָ��E2��ַ�ͳ��ȵ�����
* 
* 
* @������ 
* @param:index  E2��ַ�Ͷ�ȡ���ݳ��ȱ�������
* @param:cmd    Const_DataCom-ͨѶ��Const_DataDisp����ʾ
* @param:pvoid  ��ȡ���ݻ���
* 
* @���أ� 
* @return: uint32 
* @����: Lwb (2011-9-2)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����:  
===========================================================================================*/
uint32 E2DataProc(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucData[16];
    uint8 ASCII[32];
 
    if(Const_DataCOmWR==cmd)                    //д
    {
        if(gs_E2DataTable[index].ucAtb&ASC2BCD)
        {
            ASCII2BCD(ucData,pvoid,gs_E2DataTable[index].ucLen*2);
        }
        else
        {
            MemCpy(ucData,pvoid,gs_E2DataTable[index].ucLen);
        }
            
        if((index>=0x0f)&&(index<=0x11))        //����
        {
            //��4���ֽڵ�BCDת����8���ֽڵ�BCD
            for(uint8 i=0;i<4;i++)
            {
                ASCII[2*i]=(ucData[i]&0x0F);
                ASCII[2*i+1]=((ucData[i]&0xF0)>>4);
            }
          //opt =============   BE_WriteP(gs_E2DataTable[index].uiE2Adrr,ASCII,8);
        }else
        {
        //opt =============     BE_WriteP(gs_E2DataTable[index].uiE2Adrr,ucData,gs_E2DataTable[index].ucLen);
        }
        if((index>=0x0C)&&(index<=0x11))    //�����޸�
        {
          //opt =============BE_WriteP(EEP_FEEMDATE,(uint8*)&gs_DateTime.ucMinute,5);
            gui_RefreshEvent|=flgEtPara_Fee;
        }
        return 0;
    }
    

    if(index<ConstE2DataTableCnt)                 //��ȡָ��E2��ַ�����ݳ��ȵ�����
    {
        if(index==0x0b)
        {
            ucData[0]=0;//opt =====================guc_MeterSysSta;     //ucData[0]=guc_MeterSysSta;
        }
        else if((index>=0x0f)&&(index<=0x11))        //����
        {
            BE_ReadP(gs_E2DataTable[index].uiE2Adrr,ASCII,8);
            //��8���ֽڵ�BCDת����4���ֽڵ�BCD
            for(uint8 i=0;i<4;i++)
            {
                ucData[i]=((ASCII[2*i]&0x0F)|((ASCII[2*i+1]&0x0F)<<4));
            }
        } 
        else 
        {
          //opt====================  BE_ReadP(gs_E2DataTable[index].uiE2Adrr,ucData,gs_E2DataTable[index].ucLen);
          CopyRam ( ucData,(char *)(gs_E2DataTable[index].uiE2Adrr),gs_E2DataTable[index].ucLen);
        }
 

        BCD2ASCII(ucData,ASCII,gs_E2DataTable[index].ucLen);    //�Ѷ�ȡ������ת����ASCII

        if((index==0x05)||(index==0x06))        //������У������
        {
            DateFormat(0,ASCII);                  //ת������
            MemCpy(pvoid,ASCII,8);
            return  8;
        } 
        else if(index==0x07)                    //�����޸�����
        {
            DateAndTmFormat(ASCII);             //ת�����ں�ʱ��ĸ�ʽ
            MemCpy(pvoid,ASCII,14);
            return 14;
        }
    }
 
    MemCpy(pvoid,ASCII,gs_E2DataTable[index].ucLen*2);
    return gs_E2DataTable[index].ucLen*2;
}
/*=========================================================================================\n
* @function_name: ClearMeterProc
* @function_file: Ptl_1107.c
* @����: �������
* 
* @param: index 
* @param: cmd 
* @param: pvoid 
* 
* @return: uint32 
* @����: lwb (2014/3/25)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint32 ClearMeterProc(uint8 index,uint8 cmd,void *pvoid)
{
    SetCRCWord(guc_InitWd);
    Data_ClearMeter();
    return 0;
}
/*=========================================================================================\n
* @function_name: ReadInsData
* @function_file: Ptl_1107.c
* @����: ��ȡ˲ʱֵ
* 
* 
* @������ 
* @param:index  ��λ0x00 ��ѹ   0x10 ��������λ 0x00 A  0x01 B  0x02 C
* @param:cmd     Const_DataCom-ͨѶ��Const_DataDisp����ʾ
* @param:pvoid  
* 
* @���أ� 
* @return: uint32 
* @����: Lwb (2011-9-13)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint32 ReadInsData(uint8 index,uint8 cmd,void *pvoid)
{
    Word32 ulData;
    uint8 ASCII[10];
    if(index==0x01)
    {
        ulData.lword=EnyB_CalRMS(RMSU);
    }
    else
    {
        ulData.lword=EnyB_CalRMS(RMSI1);
    }

    if(index==0x01)
    {
        BCD2ASCII(ulData.byte,ASCII,2);    //�Ѷ�ȡ������ת����ASCII
        MemCpy((uint8*)pvoid,ASCII,3);
        ((uint8*)pvoid)[3]='.';
        ((uint8*)pvoid)[4]=ASCII[3];
        return 5;

    }else
    {
        BCD2ASCII(ulData.byte,ASCII,3);    //�Ѷ�ȡ������ת����ASCII
        MemCpy((uint8*)pvoid,ASCII,3);
        ((uint8*)pvoid)[3]='.';
        MemCpy((uint8*)pvoid+4,ASCII+3,3);
        return 7;
    }
}
/*=========================================================================================\n
* @function_name: ReadPowDnJl
* @function_file: Ptl_1107.c
* @����: ��ȡ�����¼
* 
* @param: index 
* @param: cmd 
* @param: pviod 
* 
* @return: uint32 
* @����: lwb (2014/4/3)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
/*
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pviod)
{
    uint8 ucbuf[10];
    uint8 ASCII[15];
    uint8 ucMonth=(0xf0&index)>>4;
   //opt  DataProcRead2Slice(DDJLID, ucMonth, 0, 10, ucbuf); 
    BCD2ASCII(ucbuf,ASCII,5);               //������ת����ASCii
    DateAndTmFormat(ASCII);                 //ת�����ں�ʱ��ĸ�ʽ
    MemCpy((uint8*)pviod,ASCII,14);
    ((uint8*)pviod)[14]=',';
    BCD2ASCII(ucbuf+5,ASCII,5);             //������ת����ASCii
    DateAndTmFormat(ASCII);                 //ת�����ں�ʱ��ĸ�ʽ
    MemCpy( ((uint8*)pviod)+15,ASCII,14);
    return 29;
 }
*/
uint32 ReadPowDnJl(uint8 index,uint8 cmd,void *pvoid)
{
    uint8 ucbuf[10],ctemp;
    uint8 ASCII[15];
    struct   ST645CommTimeFormat *stp =(struct   ST645CommTimeFormat *)ComData; 
    strDispCode  pCode = { 0x03110000 ,0};     
    pCode.Code +=index;
     
    if ( index )
      debug_break(50);
    tpChar = ComData ;
    ctemp = RamData.InDisp;
    RamData.InDisp = 0;
    Get645Data( &pCode );    
    RamData.InDisp = ctemp;    
     
   
    BCD2ASCII(&(stp->cMin),ASCII,5);               //������ת����ASCii
    DateAndTmFormat(ASCII);                 //ת�����ں�ʱ��ĸ�ʽ
    MemCpy((uint8*)pvoid,ASCII,14);
    ((uint8*)pvoid)[14]=',';
    
    stp++;
    BCD2ASCII(&(stp->cMin),ASCII,5);             //������ת����ASCii
    DateAndTmFormat(ASCII);                 //ת�����ں�ʱ��ĸ�ʽ
    MemCpy( ((uint8*)pvoid)+15,ASCII,14);
    return 29;
 }

/*=========================================================================================\n
* @function_name: RdData
* @function_file: Ptl_1107.c
* @����: ��ȡOBSI���Ӧ������
* 
* 
* @����: 
* @param:index  
* @param:buf  
* 
* @����: 
* @return: uint8 
* @����: Lwb  (2011-8-25)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 RdData(uint8 index,uint8*buf)
{
    uint8 bufpos=0;

    StrCpy(buf, (uint8 const code *)gs_OBSCom[index].pOBS);                     //����OBSI
    bufpos +=StrLen((uint8 const code *)gs_OBSCom[index].pOBS);
    buf[bufpos++]='(';
    if(gs_OBSCom[index].ucFPidx<ConstOBSFunCnt)                                 //��ȡOBSI���Ӧ������
    {
         Vector8_Disable() ;
    Vector9_Disable()   ;//============================
        bufpos+=gs_OBSFuction[gs_OBSCom[index].ucFPidx](gs_OBSCom[index].param,
                                                        Const_DataCOmRD,
                                                        buf+bufpos);
     Vector9_Enable()         ;//============================
      Vector8_Enable()     ;    
    }

    StrCpy(buf+bufpos, (uint8 const code *)gs_OBSCom[index].pUint);             //���͵�λ
    bufpos +=StrLen((uint8 const code *)gs_OBSCom[index].pUint);
    return bufpos;
}
/*=========================================================================================\n
* @function_name: EncodeReadFrame
* @function_file: Ptl_1107.c
* @����: 
* 
* 
* @������ 
* @param:port  ���ں�
* @param:buf  ���ͻ���
* @param:len  ���ͳ���
* @����: 
* @����: Lwb (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
void EncodeReadFrame(S_COM *ComProcCtr)
{
    uint8 i;
    uint8 bufpos=0;
    //�л�������

    gs_PtlCtnRd.uc_1107RdFrmCnt=0;

    ComProcCtr->ucBuf[bufpos++]=AS_STX;                                   //STX
    bufpos=0;
    for(i=0;i<6;i++)
    {
        bufpos+=RdData(gs_PtlCtnRd.uc_1107RdFrmCnt++,ComProcCtr->ucBuf+bufpos);
    }
    gs_PtlCtnRd.uc_CkBcc= CalBCC(0,ComProcCtr->ucBuf,bufpos);      //BCC
    gs_PtlCtnRd.uc_1107RdStatus=CNTRD_START;
    //���һ���ŵ����淢��
    ComProcCtr->ucLen=bufpos;
}
/*=========================================================================================\n
* @function_name: ContinueRead
* @function_file: Ptl_1107.c
* @����: ���������ݴ���
* 
* 
* @����: 
* @param:ComProcCtr  
* 
* @����: 
* @return: uint8 
* @����: Lwb (2011-8-25)
* @��ע:
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 ContinueRead(S_COM *ComProcCtr)
{
    uint8 i,bufpos,ucBCCTemp[4];
    bufpos=0;
    for(i=0;i<6;i++)
    {
        if(gs_PtlCtnRd.uc_1107RdFrmCnt>=ComFrmLen)                                 //�������Ѿ����������ݱ�ʶ��ֱ���˳�
        {
            break;
        }
        bufpos+=RdData(gs_PtlCtnRd.uc_1107RdFrmCnt++,ComProcCtr->ucBuf+bufpos);  //��ȡ��Ӧ���ݱ�ʶ����������
    }

    gs_PtlCtnRd.uc_CkBcc= CalBCC(gs_PtlCtnRd.uc_CkBcc,ComProcCtr->ucBuf,bufpos);      //BCC
    ComProcCtr->ucLen=bufpos;

    gs_PtlCtnRd.uc_CkBcc=CNTRD_START;
    if(gs_PtlCtnRd.uc_1107RdFrmCnt==ComFrmLen)                                     //�������һ֡
    {
        ucBCCTemp[0]='!';
        ucBCCTemp[1]='\r';
        ucBCCTemp[2]='\n';
        ucBCCTemp[3]=AS_ETX;
        for(i=0;i<4;i++)
        {
            ComProcCtr->ucBuf[bufpos++]=ucBCCTemp[i];
        }
        gs_PtlCtnRd.uc_CkBcc= CalBCC(gs_PtlCtnRd.uc_CkBcc,ucBCCTemp,4);                 //����BCC
        ComProcCtr->ucBuf[bufpos++]=gs_PtlCtnRd.uc_CkBcc;                     //��ֵBCC
        ComProcCtr->ucLen=bufpos;
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCtnRd.uc_1107RdStatus=CNTRD_STOP;
        gs_PtlCtnRd.uc_1107RdFrmCnt=0;
    }
    return  Ret_OK;

}
/*=========================================================================================\n
* @function_name: JbComHd
* @function_file: Ptl_1107.c
* @����: ͨѶ���ֽ׶��ж�
* 
* 
* @������ 
* @param:ComProcCtr  
* 
* @���أ� 
* @return: uint8 
* @����:  Lwb (2011-9-6) 
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 JbComHd(S_COM *ComProcCtr)
{	
	uint8 i;
    //uint8  MeterID[7],
#define                 MeterID               FlashInfo.SafeInfo.TRx_Num
    uint8 RevID[14];//AscZeroCnt=0;


        
    if(CmpStr(ComProcCtr->ucBuf,guc_InitCmd, sizeof(guc_InitCmd))==Ret_OK)
    {//��ʼ��
        SetCRCWord(guc_InitWd);
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        ComProcCtr->ucBuf[0]=AS_ACK;
        ComProcCtr->ucLen=1;
        gui_RefreshEvent|=flgEtPara_Init;
        return Ret_OK;
    }

    CopyRam( MeterID , FlashInfo.SafeInfo.TRx_Num ,4) ;//BE_ReadP(EEP_COMADD,MeterID,4);                    //��ȡ���ַ

    BCD2ASCII(MeterID,RevID,4);
    if(CmpStr(ComProcCtr->ucBuf,guc_Frmhd, dim(guc_Frmhd)))
    {
        //�ж��Ƿ����ַ�� / ? x x x x x x x x ! Cr lf
        if(CmpStr(ComProcCtr->ucBuf,guc_FrmADrrhd, 2))         //�ж��Ƿ��� /  ?
        {
              return Ret_Err; 
        }else
        {//�жϵ�ַ�Ƿ���ȷ
            //��ȡ���
            if(ApiBufCmp((uint8*)&RevID,ComProcCtr->ucBuf+2,8)!=CMP_EQU)
            {
                return Ret_Err;  //��ַ���ԵĻ������ظ�����                          
            }
        }
    }
//ͨѶ֡�� /?!CRLF����/?xxxxxx!CRLF���ҵ�ַ�ԵĻ���������׶�
    for(i=0;i<sizeof(guc_BpsCheck);i++)
    {
        ComProcCtr->ucBuf[i]=guc_BpsCheck[i];
    }

    for(i=0;i<8;i++)
    {
        ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+i]=RevID[i];
    }

    ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+8]='\r';
    ComProcCtr->ucBuf[sizeof(guc_BpsCheck)+8]='\n';

    ComProcCtr->ucLen=sizeof(guc_BpsCheck)+10;
    gs_PtlCrt.uc_ComStep=Com_BpsCk;         //���벨����ȷ��      
    gs_PtlCrt.uc_CompLevel=0;
    gs_PtlCrt.uc_TimeOut=COMOUTTM;                
    return Ret_OK;                          //��ȷ֡
}
/*=========================================================================================\n
* @function_name: JbMode
* @function_file: Ptl_1107.c
* @����: ͨѶģʽ�ж�
* 
* 
* @������ 
* @param:ComProcCtr  
* 
* @����: 
* @return: uint8 
* @����: Lwb (2011-9-6)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 JbMode(S_COM *ComProcCtr)
{
    //�ж�Data readout�������ݣ���rogramming mode����̣� ��Manufactory�����쳧�̣�
    uint8 i;
    if(CmpStr(ComProcCtr->ucBuf,guc_ACKHd1,6))
    {
        ReturnErr();
    }

    switch(ComProcCtr->ucBuf[3])
    {
    case '0':                            //������
//      EncodeReadFrame(ComProcCtr);
//      gs_PtlCrt.uc_ComStep=Com_CntRd;
//      gs_PtlCrt.uc_CompLevel=0;
//      gs_PtlCrt.uc_TimeOut=COMOUTTM;
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        break;
    case '1':                            //������ģʽ
        ComProcCtr->ucLen=8;
        for(i=0;i<8;i++)
        {
            ComProcCtr->ucBuf[i]=guc_PgAck[i];
        }
        gs_PtlCrt.uc_CompLevel=0;
        //����bps��2400
        if(ComProcCtr->ucPort==ComIndex_Uart4)
        {
        //  Init_Uart4(_bps2400_);        // ��ʼ��ģ�⴮��,��������ǲ����ʹ̶������Բ���Ҫ�л�������
        }
        else
        {
          Init_Uart2 (_bps2400_);        // ��ʼ��ģ�⴮��,��������ǲ����ʹ̶������Բ���Ҫ�л�������
        }
        DelayXms(100);                                                 //˯��20ms
        gs_PtlCrt.uc_ComStep=Com_PRdWr;
        gs_PtlCrt.uc_TimeOut=COMOUTTM;
        break;
    case 'Y':                                                           //��ȡ������Ϣ
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        break;
    default:
        ReturnErr();
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: CoreDataProc
* @function_file: Ptl_1107.c
* @����: �������ݴ���
* 
* 
* @����: 
* @param:ComProcCtr  
* @����: 
* @����:   Lwb (2011-10-9)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void CoreDataProc(S_COM *ComProcCtr)
{
    uint8 Pos;
    uint8 OBSI[17];
    uint8 *pData;
    uint8 ObsiLen=0;

    //����Ҫ�ж�BCC�Ƿ���ȷ��Ȼ���ж�0BSI���Ƿ���ȷ
//  if(CalBCC(0,ComProcCtr->ucBuf+1,ComProcCtr->ucLen-2)==ComProcCtr->ucBuf[ComProcCtr->ucLen-1])
    {
        //BCC��ȷ
        //Ȼ�����0BS�룬�ӵ�5���ֽڵ���ǰ�ֽ�Ϊ0BSI
            uint8 i;
            for(i=4;i<21;i++)
            {
                if(ComProcCtr->ucBuf[i]!='(')
                {
                    OBSI[ObsiLen++]=ComProcCtr->ucBuf[i];
                }else
                {
                    break;
                }
            }
            i++;                //ȥ��'('
            pData=ComProcCtr->ucBuf+i;         //��ֵ�����׵�ַ
            //��ȡ����
            Pos=FindObsiPoint(OBSI,ObsiLen);        //����0BSI���ȡ������

            if(Pos<0xff)
            {
                if(gs_OBSCom[Pos].ucAtb&IEC_WO)
                {
                    if(gs_OBSFuction[gs_OBSCom[Pos].ucFPidx]
                        (gs_OBSCom[Pos].param,Const_DataCOmWR,pData)
                       )
                    {
                        ComProcCtr->ucBuf[0]=AS_NAK;      //NAK
                    }else
                    {
                        ComProcCtr->ucBuf[0]=AS_ACK;      //ACK
                    }
                    ComProcCtr->ucLen=1;
                }else
                {
                    ReturnNAK();
                }
            }else
            {
                //���ش�����Ϣ
                ComProcCtr->ucBuf[0]=0x02;      
                ComProcCtr->ucBuf[1]=0x28; 
                ComProcCtr->ucBuf[2]=0x45; 
                ComProcCtr->ucBuf[3]=0x52;
                ComProcCtr->ucBuf[4]=0x52;
                ComProcCtr->ucBuf[5]=0x4F; 
                ComProcCtr->ucBuf[6]=0x52; 
                ComProcCtr->ucBuf[7]=0x29; 
                ComProcCtr->ucBuf[8]=0x03; 
                ComProcCtr->ucBuf[9]=0x5A;
                ComProcCtr->ucLen=10;
            }
    }
//  else
//  {
//      //BCC ����
//      ReturnNAK();
//  }
}
/*=========================================================================================\n
* @function_name: PrRdWr
* @function_file: Ptl_1107.c
* @����: ��дģʽ
* 
* @param: ComProcCtr 
* 
* @return: uint8 
* @����: lwb (2014/3/24)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint8 PrRdWr(S_COM *ComProcCtr)
{
  
    uint8 i;
    uint8 BCC;
    uint8 OBSI[17];
    uint8 ObsiLen;
    uint8 Pos;
    BCC=0;

    if(!(CmpStr(ComProcCtr->ucBuf,guc_PcComEd,sizeof(guc_PcComEd))))  //�ж��Ƿ����ж�ָ��
    {
        gs_PtlCrt.uc_ComStep=Com_HD;
        gs_PtlCrt.uc_CompLevel=0;
        ComProcCtr->ucBuf[0]=AS_ACK;
        ComProcCtr->ucLen=1;
        //�л������ʵ�300
        guc_BodeDely=40;
        return Ret_OK;
    }

    if(CmpStr(ComProcCtr->ucBuf,guc_PgPCAck,dim(guc_PgPCAck)))      //�������ж�
    {
        //SOH W1 STX AAAA() ETX BCC
        if(CmpStr(ComProcCtr->ucBuf,guc_WROBS,dim(guc_WROBS)))         //�ж�д����
        {
            if(CmpStr(ComProcCtr->ucBuf,guc_RdOBS,4))                  //�ж��Ƿ��Ƕ�����
            {
                return Ret_Err;
            }
            else
            {
                gs_PtlCrt.uc_TimeOut=COMOUTTM;
                //����Ҫ�ж�BCC�Ƿ���ȷ��Ȼ���ж�0BSI���Ƿ���ȷ
//                if(CalBCC(BCC,ComProcCtr->ucBuf+1,ComProcCtr->ucLen-2)==ComProcCtr->ucBuf[ComProcCtr->ucLen-1])
                {
                    //BCC��ȷ
                    //Ȼ�����0BS�룬�ӵ�5���ֽڵ���ǰ�ֽ�Ϊ0BSI
                    ObsiLen=0;
                    for(i=4;i<21;i++)
                    {
                        if(ComProcCtr->ucBuf[i]!='(')
                        {
                            OBSI[ObsiLen++]=ComProcCtr->ucBuf[i];
                        }else
                        {
                            break;
                        }
                    }
                    Pos=FindObsiPoint(OBSI,ObsiLen);
                    if(Pos<0xff)                    //�ҵ���Ӧ��BOSI��
                    {
                        if(gs_OBSCom[Pos].ucAtb&IEC_RO)
                        {
                            //��Ȼ�                            
                            ComProcCtr->ucBuf[0]=AS_STX;                                          //STX
                            ComProcCtr->ucLen=1;
                            ComProcCtr->ucLen += RdData(Pos,ComProcCtr->ucBuf+(ComProcCtr->ucLen));
                            ComProcCtr->ucBuf[(ComProcCtr->ucLen)++]=AS_ETX;                        //ETX
                            BCC= CalBCC(0,ComProcCtr->ucBuf+1,(ComProcCtr->ucLen)-1);               //BCC
                            ComProcCtr->ucBuf[(ComProcCtr->ucLen)++]=BCC;                           //BCC
                        }else
                        {
                            ReturnNAK();
                        }
                    }
                    else
                    {
                        ComProcCtr->ucBuf[0]=0x02;      
                        ComProcCtr->ucBuf[1]=0x28; 
                        ComProcCtr->ucBuf[2]=0x45; 
                        ComProcCtr->ucBuf[3]=0x52;
                        ComProcCtr->ucBuf[4]=0x52;
                        ComProcCtr->ucBuf[5]=0x4F; 
                        ComProcCtr->ucBuf[6]=0x52; 
                        ComProcCtr->ucBuf[7]=0x29; 
                        ComProcCtr->ucBuf[8]=0x03; 
                        ComProcCtr->ucBuf[9]=0x5A;
                        ComProcCtr->ucLen=10;                    
                    }
                }
//                else
//                {
//                    //BCC ����
//                    ReturnNAK();
//                }
            }
        }
        else                                                    //д����
        {
            gs_PtlCrt.uc_TimeOut=COMOUTTM;
            if(//(gui_SystemState&flgStSys_Program)&&
                 (gs_PtlCrt.uc_CompLevel==COMPRLEVEL))          //�ж��Ƿ���Ȩ��д
            {
                CoreDataProc(ComProcCtr);                       //�������ݴ���
            }
            else
            {
                ReturnNAK();
            }
        }
    }
    else
    {
        if(JudgeOBSPsw(ComProcCtr->ucBuf+5,ComProcCtr->ucBuf[2]-0x30))
        {
            for(uint8 i=0;i<sizeof(guc_PcComEd);i++)
            {
                ComProcCtr->ucBuf[i]=guc_PcComEd[i];
            }
            ComProcCtr->ucBuf[4]=0x71;
            gs_PtlCrt.uc_CompLevel=0;
            gs_PtlCrt.uc_ComStep=Com_HD;
            guc_BodeDely=40;
            ComProcCtr->ucLen=5;
        }
        else
        {
            gs_PtlCrt.uc_CompLevel=COMPRLEVEL;
            gs_PtlCrt.uc_TimeOut=COMOUTTM;
            ComProcCtr->ucBuf[0]=AS_ACK;                  //�ظ�ACK
            ComProcCtr->ucLen=1;
        }
    }
    return Ret_OK;
}
/*=========================================================================================\n
* @function_name: AutoJB
* @function_file: Ptl_1107.c
* @����: �Զ�У��
* 
* @param: index 
* @param: buf 
* 
* @return: uint8 
* @����: lwb (2014/4/4)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���: 
* @�޸�����:  
===========================================================================================*/
uint32 AutoJB(uint8 index,uint8 cmd,void *pvoid)
{
    if(index==0x01)
    {
        EnyB_IBAutoCheck(); 
    }
    else
    {
        EnyB_AutoChkAngle();
    }
    return 0;
}
