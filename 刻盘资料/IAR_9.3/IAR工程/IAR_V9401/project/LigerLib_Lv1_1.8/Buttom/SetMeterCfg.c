/***************************** Copyright by Vango ***********************************
	文件名：SetMeterCfg.c
	相关头文件：EXTigReg.h,chipdefine.h,intrins.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//#include "pmWrite.h"
#include <INTRINSICS.H>

/*
	功能：设置计量电路各项参数。
	配置数据用全局变量u32PMdatal、8PMdatah
	val_addr：计量寄存器地址
*/


void SetMeterCfg(unsigned int addr)
{
    volatile unsigned char xdata *p;
    
  //  mt_wr_buff(dat_h, dat_l);
    p  = (volatile unsigned char xdata *)0x10e8;
    *p = (unsigned char)(u32PMdatal);
    p++;
    *p = (unsigned char)(u32PMdatal>>8);
    p++;
    *p = (unsigned char)(u32PMdatal>>16);
    p++;
    *p = (unsigned char)(u32PMdatal>>24);
    p++;
    *p = (unsigned char)(u8PMdatah);
    p  = (volatile unsigned char xdata *)addr;
    *p = 0;
    __no_operation();__no_operation();__no_operation();
}
