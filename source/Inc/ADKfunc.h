#ifndef _ADKFUNC_H_
#define _ADKFUNC_H_

#ifndef ADK_EXT
    #define ADK_EXT extern
#else
    #define ADK_SELF 
#endif

#ifdef ADK_SELF
const uint8 code guc_ADKcmd[]={0x11,0x07,0x34,0x2F};//阿迪克初始化
#else
extern const uint8 code guc_ADKcmd[];
#endif

#define ADK_Cal         0x00        //正确
#define ADK_Init        0xAA        //初始化
#define ADK_None        0x55        //错误

typedef struct
{
    uint8 undef0:1;     //bit0抄表：自动(0)/手动(1)
    uint8 bDmd:1;       //bit1最大需量计算方式：滑差(0)/区间(1)
    uint8 bBat:1;       //bit2电池电压：正常(0)/欠压(1)
    uint8 undef3:1;     //bit3 0
    uint8 bPdir:1;      //bit4有功电能方向;正向(0)/反向(1)
    uint8 undef5:1;     //bit5无功电能方向;正向(0)/反向(1)
    uint8 bChannel:1;   //bit6 1：主回路，0：负回路，默认为主回路
    uint8 undef7:1;     //bit7 0
}S_RUNCODE;

typedef union 
{
    uint8 ucSta;
    S_RUNCODE sSta;
}GT_RUNCODE;

ADK_EXT GT_RUNCODE gt_RunCode;
ADK_EXT uint8 guc_ADKcal;           //阿迪克校表命令

/*以下函数声明*/
uint8 ADK_CalFun(S_FRAMEINFO *s_FrmInfo);
uint8 ParaInit(S_FRAMEINFO *s_FrmInfo);
//uint8 ADK_ReadVar(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable);
#define  ADK_ReadVar(a,b) {}
uint8 ADK_Backup(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable);
void ADK_AutoChkPW(uint8);
void ADK_AutoChkTinyPW(uint8);
void ADK_AutoChkIrms(uint8);
void ADK_AutoChkUrms(void);
void ADK_AutoChkAngle(uint8);
uint8 ADK_ReadFlash(S_FRAMEINFO *s_FrmInfo, S_CORETAB code * CTable);
#endif