
#define POWMANGE_EXT

#include "Include.h"

uint8 guc_ChkPowDn;                 // 下电检测寄存器
/*=========================================================================================\n
* @function_name: PowDownChk
* @function_file: Powmanger.c
* @描述:
*
* @参数:
* @返回:
* @作者:   lwb (2012-03-23)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void PowDownChk(void)
{
    if (!(gui_SystemState & flgStSys_PowOff))   // 是否处于掉电状态
    {                                           // 有电才进行后续的判断
        guc_ChkPowDn <<= 1;

        if(!(Systate&BIT0))                      // 判断是否电压低
        {
            guc_ChkPowDn |=0x1;                 // 把当前电压状态存入寄存器，只有连续有低电平才可以判定是下电
        }

        if(0x0f == (guc_ChkPowDn&0x0f))         // 有连续的4次，也就是8ms低电平，设置下电事件
        {
            gui_SystemEvent |= flgEtGlb_PowDown;
            guc_ChkPowDn =0x0;
        }
    }
}
/*=========================================================================================\n
* @function_name: PowerDnPro
* @function_file: System.c
* @描述: 掉电处理函数
*
* @参数:
* @返回:
* @作者:   lwb (2012-01-31)
* @备注:
*-------------------------------------------------------------------------------------------
* @修改人:
* @修改内容:
===========================================================================================*/
void PowerDnPro(void)
{
    //保存电量增量到E2中处理
    //IO口处理
    uint16 CRC;
    EA=0;                   //开中断
    PMCtrl4 &=~0x18;                        //关闭CF 
    IdleIO();
    IntOFF();
    UARTOFF();

    MemCpy(XDATA_RAMZONE,   (uint8*)&gs_EnergyData.uiEP,    4);          //当前电量增量
    MemCpy(XDATA_RAMZONE+4, (uint8*)&gs_PowerCf.uc_P,       1);         //当前CF数
    MemCpy(XDATA_RAMZONE+5, (uint8*)&gs_Energy.ucP,         1);         //当前CF对于的能量
    MemCpy(XDATA_RAMZONE+6, (uint8*)&gs_FeeData.uc_FeeNo,   1);         //当前费率

    CRC=do_CRC(XDATA_RAMZONE, 7);
    MemCpy(XDATA_RAMZONE+7,(uint8*)&CRC,2);
    BE_WriteP(EEP_POWDWENERGY,(uint8*)XDATA_RAMZONE,9);

    //低功耗处理
//  gs_DispStt.ucIndex=0;
//  gs_DispStt.ucTmr=0;
//  ShowRefresh();
    //关闭显示
    BE_I2C_SDA_1();
    BE_I2C_CLK_1();
    LCD_Off();
    Init_RTC(RTC_DAY);                      //初始化为DAY RTC唤醒
    gui_SystemState |= flgStSys_PowOff;

    Sleep();
}





