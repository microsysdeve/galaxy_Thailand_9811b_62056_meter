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
    uint8   Type;              //T1M和SMOD的取值
}GS_BaudRate;

#ifdef COMBOTTOMSELT
const GS_BaudRate code BaudRateTable[6] =
{

    {0xC7,   0x82},  //300
    {0x55,   0x22},  //600
    {0x55,   0xA2},  //1200
    {0xAB,   0xA2},  //2400
    {0xD5,   0xA2},  //4800
    {0xEB,   0xA2},  //9600
};
#else 
extern const GS_BaudRate code BaudRateTable[6];
#endif


//变量
typedef struct s_com
{
    uint8   ucPort;
    uint8   ucStt;                                                  // 通讯状态ComStt_Recv/ComStt_Send/COM_IDLE
    uint8   ucRecvTmr;                                              // 单位10ms,相当于调用周期为10ms
    uint8   ucOverTmr;                                              // 单位10ms,相当于调用周期为10ms,保护用
//    uint8   ucFrmHeadCnt;                                           // 帧头处理
    uint8   ucLen;                                                  // 收发的数据总长度
    uint8   ucPos;                                                  // 当前处理数据的位置,相当于指向ucBuf的一个指针
    uint8   ucBuf[Const_MaxBufLen];                                             // 通讯收发数据缓冲区
}S_COM;

COMBOTTOMEXT S_COM gs_ComGroup[Const_MaxComNum];                    // 通讯用的缓存


COMBOTTOMEXT uint8 guc_485Bode;         //485波特率
COMBOTTOMEXT uint8 guc_BodeDely;        //波特率切换延时
//函数
void ComBom_Init(uint8 ucNo);
void ComBom_InitAll(void);
void ComBom_StartSend(uint8 ucNo);
void ComBom_10msDy(void);



#endif
