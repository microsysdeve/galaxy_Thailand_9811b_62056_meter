/***************************** Copyright by Vango ***********************************
	文件名：Read_50_60Hz.c
	相关头文件：EXTigReg.h,chipdefine.h


	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*功能： 读取50/60 Hz 设置
入口：无
出口： 0----选择50Hz，1----选择60Hz

*/
unsigned char Read_50_60Hz(void)
{
//	unsigned char val_frq;
//	val_frq = ((CtrlCLK&PLLSEL))?1:0;
//	return val_frq;
	if((CtrlPLL&0x20))
		return 1;
	else return 0;
}