#define AP_CORETAB_EXT
#include "Include.h"

/*=========================================================================================\n
* @function_name: FunList
* @function_file: ComCoretab.c
* @����: �������⴦����������������������Ӻ���ֻ����ĩβ���ӣ��벻Ҫ���м����ӣ����������
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-17)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
const PFUNC code FunList[] = 
{
    ADK_ReadVar,                    //0x00   ���Ͽ˼���
    ComReadRunCode,                 //0x01 ��ȡ����״̬��
    ReadAccuEgy,                    //0x02 ��ȡ���ڵ���
    ReadCurEgy,                     //0x03 ��ȡ��ǰ�ĵ���
    ReadHisEgy,                     //0x04 ��ȡ��ʷ�ĵ���ReadHisEgy
    ComRWE2Para,                    //0x05 ��ȡE2����
    ComMeterConst,                  //0x06 ��ȡ������� 
    ADK_ReadFlash,                      //0x07 ��ȡ�¼���¼����ComRdEvCnt
    FunToBeDef,                     //0x08 �������ն�дRwGGJR
    FunToBeDef,                     //0x09 ��ȡ��̼�¼��������㡢������..��ReadJL
    FunToBeDef,                     //0x0A ��д��ʱ��ʱ����RwSqSd
    FunToBeDef,                     //0x0B ��ȡ��������
    FunToBeDef,                     //0x0C ��д��ʾ��
    RwSysTime,                      //0x0D ��дϵͳʱ��
    RwRamE2,                        //0x0E ֱ�Ӷ�дE2��Ram
    ADK_Backup,                     //0x0F ��ȡ������õ��� ReadZHLYEgy
    ReadVar,                        //0x10 ��ȡ����˲ʱֵ
#ifdef LOADCURVE
    FunToBeDef,                    //0x11 ���ɼ�¼ReadCurveJl
#else
    FunToBeDef,                     //0x12 
#endif
    ReadSwVersion,                  //0x13 ��ȡ�汾��
    FunToBeDef,                 //0x14 ��ȡ�����ַ������ݿ�ReadEnyD0Block
    FunToBeDef,                     //0x15 д��ͨ����WrPassWord
    FunToBeDef,                      //0x16  IrShowLcd
    FunToBeDef,                  //0x17  ��ʷ����ʱ��ReadHisJSTime
    FunToBeDef,                         //0x18  �����ϱ�Report
};
//��������ݱ�ʶ�����С��������

/*=========================================================================================\n
 ���ı�0 ��Ҫ�ǵ���������
===========================================================================================*/
const S_CORETAB code gs_CoreTab0[] = 
{               
//  ID              Atb LEN D1  D0   FUNID   ADDR
    {0x00000000,    0,  4,  0,  0,  0x03,   0,              0,}, //����ǰ������й��ܵ���
    {0x00010000,    0,  4,  0,  0,  0x03,   0,              0,}, //����ǰ�������й��ܵ���
    {0x00020000,    0,  4,  0,  0,  0x03,   0,              0,}, //����ǰ�������й��ܵ���
};
/*=========================================================================================\n
 ���ı�1 ��Ҫ����������
===========================================================================================*/
const S_CORETAB code gs_CoreTab1[] = 
{
//  ID              Atb LEN D1  D0   FUNID   ADDR
    {0x01010000,    0,  4,  0,  0,  0x11,   0,              0,}, //����ǰ������
};  
/*=========================================================================================\n
 ���ı�2����Ҫ��˲ʱֵ����
===========================================================================================*/
const S_CORETAB code gs_CoreTab2[] = 
{
//  ID              Atb         LEN D1  D0      FUNID   ADDR
    {0x02010000,  Data_BCD,     2,  0,  0,      0x10,   0,      0,      },//��ѹ���ݿ���ң����ݱ�ʶ�൱��0x0201FF00
    {0x02010100,  Data_BCD,     2,  0,  0,      0x10,   0,      0,      },//A���ѹ
//  {0x0201FF00,  Data_BCD,     6,  0,  0,      0x10,   0,      1,      },//��ѹ���ݿ�

    {0x02020000,  Data_BCD,     3,  0,  0,      0x10,   0,      2,      },//�������ݿ���ң����ݱ�ʶ�൱��0x0202FF00
    {0x02020100,  Data_BCD,     3,  0,  0,      0x10,   0,      2,      },//A�����
//  {0x0202FF00,  Data_BCD,     9,  0,  0,      0x10,   0,      3,      },//�������ݿ�

    {0x02030000,  Data_BCD,     3,  0,  0,      0x10,   0,      5,      },//˲ʱ���й�����
    {0x02030100,  Data_BCD,     3,  0,  0,      0x10,   0,      5,      },//˲ʱA���й�����
    {0x02040000,  Data_BCD,     3,  0,  0,      0x10,   0,      12,      },//˲ʱ���޹�����
    {0x02040100,  Data_BCD,     3,  0,  0,      0x10,   0,      12,      },//˲ʱA���޹�����
//  {0x0203FF00,  Data_BCD,     12, 0,  0,      0x10,   0,      6,      },//�������ݿ�

    {0x02060000,  Data_BCD,     2,  0,  0,      0x10,   0,      8,      },//�ܹ�������
    {0x02060100,  Data_BCD,     2,  0,  0,      0x10,   0,      8,      },//A�������
//  {0x0206FF00,  Data_BCD,     8,  0,  0,      0x10,   0,      9,      },//A�������

    {0x02800001,  Data_BCD,     3,  0,  0,      0x10,   0,      4,      },//���ߵ���
    {0x02800008,  Data_BCD,     2,  0,  0,      0x10,   0,      11,     },//ʱ�ӵ�ص�ѹ(�ڲ�)
};   
/*******************************************************************************
**���ı�4����Ҫ�Ǳ��Ƶ�һЩ����
*******************************************************************************/
const S_CORETAB code gs_CoreTab4[] = 
{
    //  ID              Atb                 LEN     D1  D0  FUNID   ADDR
    {0x04000101,    Data_RF,                4,      0,  0,  0x0D,   EEP_DATETIME,           0,      },//���ڼ�����(����0����������)
    {0x04000102,    Data_RF,                3,      0,  0,  0x0D,   EEP_DATETIME + 4,       0,      },//ʱ��

    {0x04000401,    0,                      6,      0,  0,  0x05,   EEP_COMADD,             26,     },//ͨ�ŵ�ַ
    {0x04000402,    0,                      6,      0,  0,  0x05,   EEP_METERNO,            12,     },//����
    //{0x04000403,    0,                      32,     0,  0,  0x05,   EEP_ASSETNO,            0,      },//�ʲ���������(ASCII��)
    {0x04000404,    Data_RO,       6,      0,  0,  0x07,   0,            0,      },//���ѹ(ASCII��)
    {0x04000405,    Data_RO,       6,      0,  0,  0x07,   0,            0,      },//�����/��������(ASCII��)
    {0x04000406,    Data_RO,       6,      0,  0,  0x07,   0,            0,      },//������(ASCII��)
    {0x04000409,    Data_RO,       3,      0,  0,  0x07,   0,            0,      },//����й�����
    
    {0x04000501,    Data_RO,                1,      0,  6,  0x07,   0,                      0,      },//�������״̬��1
    {0x04000C01,    Data_WO,                16,     0,  9,  0x14,   EEP_645PASSWD1,         0,      },//0������
    {0x04800001,    Data_RO,            32,     0,  0,  0x07,   0,                      0,      },//���������汾��(ASCII��)
    {0x04800002,    Data_RO,            32,     0,  0,  0x07,   0,                      0,      },//����Ӳ���汾��(ASCII��)    
};
/*******************************************************************************
**���ı�4F����Ҫ�ǳ�������
*******************************************************************************/
const   S_CORETAB code gs_CoreTab4F[] = 
{
    //  ID          Atb         LEN D1  D0  FUNID   ADDR
    {0x4F000001,    0,  27, 0,  0,  0x08,   EEP_AUTOCAL,    0,},//�Զ�У��ָ��
    {0x4F000A00,    0,  8,  0,  0,  0x12,   0,              0,},//��ȡ�汾��
    {0x4F010000,    0,  68, 0,  0,  0x0E,   0,              0,},//ֱ��E2��д
};
/*******************************************************************************
**���ı�AA����Ҫ�ǰ��Ͽ�����֧��
*******************************************************************************/
const   S_CORETAB code gs_CoreTabAA[] = 
{
    //  ID          Atb         LEN D1  D0  FUNID   ADDR
    {0xAAAAAAAA,    0,  21,  0,  0,  0x00,   0,    0,},//���Ͽ���չ����
    {0xAAAAAAAB,    0,  16,  0,  0,  0x0F,   0,    0,},//���Ͽ���չ������׶�
};
/*=========================================================================================\n
* @function_name: gs_CoreID
* @function_file: ComCoretab.c
* @����: ������ı�������ID3�Ĺ�ϵ
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-10)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
const   S_COREID code gs_CoreID[] =       //�������ݱ���ID�Ķ�Ӧ��ϵ
{
    {0x00,  (S_CORETAB code*)gs_CoreTab0, sizeof(gs_CoreTab0) / sizeof(S_CORETAB)},
    {0x01,  (S_CORETAB code*)gs_CoreTab1, sizeof(gs_CoreTab1) / sizeof(S_CORETAB)},
    {0x02,  (S_CORETAB code*)gs_CoreTab2, sizeof(gs_CoreTab2) / sizeof(S_CORETAB)},
    {0x04,  (S_CORETAB code*)gs_CoreTab4, sizeof(gs_CoreTab4) / sizeof(S_CORETAB)},
    {0x4F,  (S_CORETAB code*)gs_CoreTab4F, sizeof(gs_CoreTab4F) / sizeof(S_CORETAB)},
    {0xAA,  (S_CORETAB code*)gs_CoreTabAA, sizeof(gs_CoreTabAA) / sizeof(S_CORETAB)},
};

const   uint8 code NumofCoreID = sizeof(gs_CoreID) / sizeof(S_COREID);

/*=========================================================================================\n
* @function_name: gs_CoreTab97
* @function_file: ComCoretab.c
* @����: ����97��Լ��07��Լ���ݱ�ʶӳ���ϵ
* 
* @����: 
* @����: 
* @����:   lwb (2016-02-23)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
const   S_CORETAB97 code gs_CoreTab97[] =       //�������ݱ���ID�Ķ�Ӧ��ϵ
{
  //  97ID      07ID  
    {0x9010,  0x00000000,    },     //����ǰ�������й��ܵ���

    {0xAABC,  0xAAAAAAAA,    },     //���Ͽ���չ��������
    {0xAABD,  0xAAAAAAAB,    },     //���Ͽ���չ����׶�ֵ   

    {0xC020,  0x04000501     },//�������״̬��
    {0xC030,  0x04000409,    },//����й�����     
    {0xC032,  0x04000401,    },//ͨѶ��ַ 
    {0xC034,  0x04000402,    },//���� 
};

const   uint8 code NumofCore97ID = sizeof(gs_CoreTab97) / sizeof(S_CORETAB97);
