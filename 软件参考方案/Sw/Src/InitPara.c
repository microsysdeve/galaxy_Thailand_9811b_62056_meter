#define INIT_EXT
#include"Include.h"

const uint8 code InitPara0[]=
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,     //ͨѶ��ַ
    0x15,                                   //��������
    0x15,                                   //������������
    0x05,0x04,0x14,                         //��������
    0x05,0x04,0x14,                         //У������
    0x05,0x10,0x05,0x04,0x14,               //�����޸�����
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,//������
    0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,//д����  
    0x00,0x01,                              //��1������
    0x99,0x99,                              //��2������
    0x99,0x99,                              //��3������
    0x01,                                   //���״̬
};

const uint8 code InitPara1[]=
{
    0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,
    0x00,0x22,0x00,0x10,0x00,0x09,0x00,0x08,//�����շ���ʱ��
    0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,
    0x00,0x22,0x00,0x10,0x00,0x09,0x00,0x08,//����������ʱ��
    0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,
    0x00,0x22,0x00,0x10,0x00,0x09,0x00,0x08,//���������ʱ��
};

const uint8 code InitPara2[]=
{
    0x99,0x99,0x99,0x99,0x04,0x03,0x02,0x01,    //�����շ���
    0x99,0x99,0x99,0x99,0x04,0x03,0x02,0x01,    //����������
    0x99,0x99,0x99,0x99,0x04,0x03,0x02,0x01,    //���������
};

const uint8 code InitPara3[sizeof(S_JBPM)-2]=
{
    0xE8,0x03,     //����
    0xf0,0x55,     //��Ƶ�ѹ
    0x88,0x13,     //��Ƶ���
    0x00,
    0xA2,0xD3,0x3D,0x92,//�й�������������ֵ
    0x8B,0xE6,0x4F,0x00,//�й�����Ǳ������ֵ

    0x32,0x88,0x9B,0x0C,//�й��Ȳ�ֵ
    0x00,0x00,0x00,0x00,//�޹��Ȳ�ֵ
    0x1C,0x76,0xA4,0x04,//��ѹ��Чֵ�Ȳ�
    0x81,0x63,0x32,0xC5,//ͨ��I1������Чֵ�Ȳ�
    0x00,0x00,0x00,0x00,//ͨ��I2������Чֵ�Ȳ�

    0xDD,0xFF,0xFF,0xFF,//�й����ʶ��β���ֵ
    0x00,0x00,0x00,0x00,//�޹����ʶ��β���ֵ

    0x07,               //ͨ��I1�ǲ�У��ֵ
    0x01,               //ͨ��I2�ǲ�У��ֵ

    0xA6,0x10,0x00,0x00,//������ʾ����ϵ��k
    0x1E,0x3D,0x00,0x00,//��ѹ��ʾ����ϵ��k
    0xA5,0x0B,0x00,0x00,//����I1��ʾ����ϵ��k
    0xA5,0x16,0x00,0x00,//����I2��ʾ����ϵ��k
    0x0F,               //ͨ������
    //CRC
};

typedef struct 
{
    const uint8 code* E2ParaTabAdrr;    //E2��������ַ
    uint16 E2Adrr;                      //E2��ַ
    uint8  uclen;                       //���ݳ���
}GS_E2PARA;

const  GS_E2PARA code PageCRCAddr[]=
{
    {InitPara0,     EEP_COMADD,         sizeof(InitPara0),  },
    {InitPara1,     EEP_WORK_FEE_TIME,  sizeof(InitPara1),  },
    {InitPara2,     EEP_WORK_FEE,       sizeof(InitPara2),  },
    {InitPara3,     EEP_JBTOTAL,        sizeof(InitPara3),  },
};

/*=========================================================================================\n
* @function_name: InitE2Data
* @function_file: InitPara.c
* @����: 
* 
* @����: 
* @����: 
* @����:   lwb (2012-05-04)
* @��ע: 
*-------------------------------------------------------------------------------------------
* @�޸���:  
* @�޸�����: 
===========================================================================================*/
void InitE2Data(void)
{
    Word16 CRC;
    ClRCRCWord(guc_InitWd);
    for(uint8 i=0;i<sizeof(PageCRCAddr)/sizeof(GS_E2PARA);i++)
    {
        CLRWDT();                           //ι��
        MemSet(XDATA_RAMZONE,0x00,64);
        FCpyTMem(XDATA_RAMZONE,PageCRCAddr[i].E2ParaTabAdrr,PageCRCAddr[i].uclen);//����Flash���ݵ�RAM��
        CRC.word=do_CRC(XDATA_RAMZONE,62);
        XDATA_RAMZONE[62]=CRC.byte[0];
        XDATA_RAMZONE[63]=CRC.byte[1];                          //����CRC��RAM��
        BE_WriteP(PageCRCAddr[i].E2Adrr,XDATA_RAMZONE,64);      //д�뵽E2��
    }
    
    SetCRCWord(guc_InitWd);
    Data_ClearMeter();                                          //�������
    gui_RefreshEvent|=flgEtPara_EnyBottom;
}
