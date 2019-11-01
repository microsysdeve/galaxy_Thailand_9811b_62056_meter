#ifndef _AP_MULTARIFF_H_
    #define _AP_MULTARIFF_H_

#ifndef AP_MULTARIFF_EXT
    #define AP_MULTARIFF_EXT extern
#endif
#define MAXSDTAB   0x08
#define MAXFEE     0x04
typedef struct strFeeData
{
    uint8   uc_FeeSQN;                          //�ڼ���ʱ��  1-2
    uint8   uc_FeeRSDN;                         //�ڼ���ʱ��  1-2
    uint8   uc_FeeRSD;                          //��ʱ�κ�    1-8
    uint8   uc_FeeNo;                           //���ʺ�      1-63
}FEEDATA;

AP_MULTARIFF_EXT FEEDATA gs_FeeData;
AP_MULTARIFF_EXT uint16 gui_NextFeeTime;        //��һ�������л�ʱ��
AP_MULTARIFF_EXT uint8 guc_SdNum;
AP_MULTARIFF_EXT uint8 guc_Pulse;
AP_MULTARIFF_EXT uint8 guc_DayType;

uint8 Search_Pos(uint8 *buff,Word16 time,uint8 len);
uint8 Search_SdNum(uint8 *buff,Word16 time,uint8 len);
uint8 IsZXR(void);
uint8 IsJR(void);
void IsNumSQ(void);
void IsNumSD(void);
void IsValidSQ(void);
void getFee(void);
void getTimeZone(void);


#endif
