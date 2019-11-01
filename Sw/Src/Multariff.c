#define AP_MULTARIFF_EXT
#include "Include.h"
/*=========================================================================================\n
* @function_name: getFee
* @function_file: Multariff.c
* @描述: 判断费率，工作日，星期六，星期天
* 
* @作者: lwb (2014/4/2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
void getFee(void)
{
    uint8 Feedata[8];
    uint8 Feetime[16];
    uint8 tim[2];
    uint8 pos;
    tim[0]=gs_DateTime.ucHour;
    tim[1]=gs_DateTime.ucMinute;
    switch(gs_DateTime.ucWeek)                  //判断工作日、星期六、星期天
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        default:
           BE_ReadP(EEP_WORK_FEE,Feedata,8);
           BE_ReadP(EEP_WORK_FEE_TIME,Feetime,16);  
           break;
        case 5:
           BE_ReadP(EEP_SAT_FEE,Feedata,8);
           BE_ReadP(EEP_SAT_FEE_TIME,Feetime,16); 
           break;
        case 6:
           BE_ReadP(EEP_SUN_FEE,Feedata,8);  
           BE_ReadP(EEP_SUN_FEE_TIME,Feetime,16); 
           break;
    }
    pos = search_tim(tim,Feetime);
    swap(Feedata,7);
    gs_FeeData.uc_FeeNo = Feedata[pos]-1;
    if(gs_FeeData.uc_FeeNo>=MAXFEE)
    {
        gs_FeeData.uc_FeeNo=0x00;
    }
}
/*=========================================================================================\n
* @function_name: search_tim
* @function_file: Multariff.c
* @描述: 比对时间，找到对应费率
* 
* @param: tim  当前时间
* @param: feetim 费率时间
*  
* @return: uint8 对应的费率位置
* @作者: lwb (2014/4/2)
* @备注: 
*-------------------------------------------------------------------------------------------
* @修改人: 
* @修改内容:  
===========================================================================================*/
uint8 search_tim(uint8 *tim,uint8 *feetim)
{
    uint8 num;
    uint8 i;
    uint16 tim_sec;
    swap(feetim,15);
    tim_sec = APIByteBCD2HEX(tim[0])*60 +APIByteBCD2HEX(tim[1]);
    for(i =0;i<8;i++)
    {
        if(feetim[i*2] == 0x99)
        {
            //i++;
            break;
        }
    }
    num = i;           //根据99判断有几个费率
    for( i=0;i<15;i++)
    {
         feetim[i] = APIByteBCD2HEX(feetim[i]);
    }
    for( i=0;i<num;i++)
    {
       
        if(tim_sec<(feetim[i*2]*60 +feetim[i*2 +1]))
        {
            if(i == 0)
            {
                return num -1;
            }
            else
            {
                return i-1;
            }
            
        }
    }
    return num -1;
}

void swap(uint8 *feetim,uint8 num)
{
    uint8 tmp;
    for(uint8 i =0;i<((num+1)/2);i++)
    {
        tmp = feetim[i];
        feetim[i] = feetim[num-i];
        feetim[num -i] = tmp;
    }
}

