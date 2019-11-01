#ifndef __RTCCPT_H__
    #define __RTCCPT_H__

#ifndef RTCCPTEXT
    #define RTCCPTEXT extern
#endif


typedef struct
{
    uint32 ul_TempParaA;      //ϵ��A
    uint32 ul_TempParaB;      //ϵ��B
    uint32 ul_TempParaC;      //ϵ��C
    uint32 ul_TempParaD;      //ϵ��D
    uint32 ul_TempParaE;      //ϵ��E
    uint8  uc_Add33;          //��У��
}S_TEMPPARA;

RTCCPTEXT uint32 gul_CellVoltage;
RTCCPTEXT uint8  guc_CheckBatFlg;
RTCCPTEXT int16  gi_Temprature;
RTCCPTEXT uint8  guc_FrsCalRTCDelay;
RTCCPTEXT uint16 gui_Kpara;

void SetRTCNormal(int16 offset);
void CalRTC(void);
void RecoverRtcPara(void);
void RecoverRtcParaFrmFalsh(void);


#endif


