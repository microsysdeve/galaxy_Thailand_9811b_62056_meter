/***************************** Copyright by Vango ***********************************
	文件名：Alt_50_60Hz.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*功能： 50/60 Hz 选择
入口： val_frq：0----选择50Hz，1----选择60Hz
出口：无
*/
void Alt_50_60Hz(unsigned char val_frq)
{
	F0 = 0;		
	if(val_frq==0)CtrlPLL &= (~0x20);
	else CtrlPLL |= 0x20;
}