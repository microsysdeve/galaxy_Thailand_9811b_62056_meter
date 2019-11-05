#ifndef __ComBottom_H__
#define __ComBottom_H__


#ifndef COMBOTTOMEXT
    #define COMBOTTOMEXT extern
#else 
    #define COMBOTTOMSELT
#endif

#define COMHEAD             0x68
#define COMTAIL             0x16
#define COMINITLEN          10
#define DLT2007DATALEN      100

typedef struct 
{
    uint8   THValue;
    uint8   Type;              //T1M��SMOD��ȡֵ
}GS_BaudRate;

#ifdef COMBOTTOMSELT
const GS_BaudRate code BaudRateTable[5] =
{
   {0xe4,   0x82},  //600
   {0xf2,   0x82},  //1200
   {0xd5,   0x22},  //2400
   {0xd5,   0xa2},  //4800
   {0xeb,   0xa2},  //9600
};
#else 
extern const GS_BaudRate code BaudRateTable[5];
#endif

//����
typedef struct s_com
{
    uint8   ucPort;
    uint8   ucStt;                                                  // ͨѶ״̬ComStt_Recv/ComStt_Send/COM_IDLE
    uint8   ucRecvTmr;                                              // ��λ10ms,�൱�ڵ�������Ϊ10ms
    uint8   ucOverTmr;                                              // ��λ10ms,�൱�ڵ�������Ϊ10ms,������
    uint8   ucFrmHeadCnt;                                           // ֡ͷ����
    uint8   ucLen;                                                  // �շ��������ܳ���
    uint8   ucPos;                                                  // ��ǰ�������ݵ�λ��,�൱��ָ��ucBuf��һ��ָ��
    uint8   ucBuf[360];                                             // ͨѶ�շ����ݻ�����
}S_COM;

COMBOTTOMEXT S_COM gs_ComGroup[Const_MaxComNum];                    // ͨѶ�õĻ���


typedef struct
{
    volatile uint8 ucStt;
    volatile uint8 ucOverTmr;
    uint8 ucSendLen;
    uint8 ucSendPos;
    uint8 ucRevLen;
    uint8 ucRevPos;
    volatile uint8 ucBuf[128];
}S_7816COM;


//COMBOTTOMEXT  S_7816COM gs_7816Com;                    // ͨѶ�õĻ���
//COMBOTTOMEXT  uint8 guc_IRWakeupBgcnt;



COMBOTTOMEXT uint8 guc_485Bode;         //485������
COMBOTTOMEXT uint8 guc_BodeDely;        //�������л���ʱ
COMBOTTOMEXT uint8 guc_ComSendDy;       //ͨѶ�ظ���ʱ��20ms
//����
void ComBom_Init(uint8 ucNo);
void ComBom_InitAll(void);
void ComBom_StartSend(uint8 ucNo);
void ComBom_10msDy(void);



#endif