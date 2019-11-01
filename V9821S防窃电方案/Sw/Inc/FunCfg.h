#ifndef __FUNCFG_H__
#define __FUNCFG_H__

#ifndef FUNCFGEXT
    #define FUNCFGEXT extern
#endif

typedef struct
{
    uint8   uc_CfSaveCfg;          //CF���������������
    uint8   uc_CbrCfg;             //�����ղ��������������
    uint8   uc_DJCfg;              //���Ჹ�������������
    uint16  uc_PWLCfg;             //����ȼ���Ч�����������
    uint8   uc_SQSDCfg;            //ʱ����ʱ���л�ʱ�������б������������
    uint8   uc_ENSHOWCfg;          //������ʾ��ʽ�����������
    uint8   uc_TMSHOWCfg;          //ʱ����ʾ��ʽ�����������
    uint8   uc_PWOFFSHOWMDCfg;     //ͣ����ʾģʽ�����������
    uint8   uc_JDQCKCfg;           //�̵�����ⷽʽ�����������
    uint8   uc_ClrMeterCntCfg;     //������������������
    uint32  ul_ClrMeterEnyValCfg;  //������������ֵ��������
    uint16  ul_CRC;                //������crc
}GSFUNCFG;


FUNCFGEXT GSFUNCFG   gs_FunCfg;


void RecoverCfg(void);
void Up_FunCfg(void);
void CfgCheck(void);

#define _SQ_
#define _JR_
#define _ZXR_     //ũ����������
 
 





#endif
