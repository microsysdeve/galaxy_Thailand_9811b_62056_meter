#ifndef __DATA_PROTECTEXT_H__
#define __DATA_PROTECTEXT_H__

#ifndef DATAPROTECTEXT
    #define DATAPROTECTEXT extern 
#endif

#define E2_PARAMAX_LEN  0x60
#define E2_PROTECT_LEN  0x40            //96�ֽ�,��ĿǰE2�����������й�

#define JBLEN (sizeof(S_JBPM))
#define RTC_LEN 28
#define TIME_LEN 9
#define LOAD_LEN 16

typedef struct s_datachk
{//���ݰ�ȫ�Լ�����,���ڶ�����ԱȽϵ��������ֵ����Сֵ
    uint8   ucMin;
    uint8   ucMax;
}S_DATACHK;

#define DATA_CHECK_USE_DEF  0x80        //��Ҫʹ��Ĭ��ֵ

typedef struct s_e2parachk
{//��СE2��Ӧ�ı�־λ�趨��gui_BEParaCheck��gui_SEParaCheck֮��
    uint8   ucLen;                      //����У�����������ܳ���,����crc�����ֽ�
    uint16  uiAddr;                     //��Ӧ�Ĵ�СE2�Ĳ������׵�ַ
}S_E2PARACHK;

 
 

DATAPROTECTEXT uint32   gul_E2ParaStt;          //E2��Ӧ�Ĳ���������crcУ��ȶ�
//DATAPROTECTEXT uint8  guc_RtcConflict;          //rtcУ����ͻ��־λ



uint8 DataCheck(uint8 ucNum, uint8* p, S_DATACHK code* psDC);
void RefreshPara(void);
void DataSecurityInit(void);
void SysE2ParaSetManage(uint16 uiAddr, uint8* pucBuf,uint8 ucLen);
void SysE2ReadData(uint16 uiAddr, uint8* pucBuf,uint8 ucLen);
void E2ParaCheck(void);
uint8 ComCheckFormat(uint8 *Databuf,uint8 type,uint8 len);

#endif
