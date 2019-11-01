#ifndef _AP_MULTARIFF_H_
    #define _AP_MULTARIFF_H_

#ifndef AP_MULTARIFF_EXT
    #define AP_MULTARIFF_EXT extern
#endif
#define MAXSDTAB   0x08
#define MAXFEE     0x04
typedef struct strFeeData
{
    uint8   uc_FeeNo;                           //费率号      1-63
}FEEDATA;
AP_MULTARIFF_EXT FEEDATA gs_FeeData;
//AP_MULTARIFF_EXT uint16 gui_NextFeeTime;        //下一个费率切换时间

uint8 search_tim(uint8 *tim,uint8 *feetim);
void getFee(void);
void swap(uint8 *feetim,uint8 num);


#endif
