/***************************** Copyright by Vango ***********************************
	文件名：SetLDOVolt.c
	相关头文件：EXTigReg.h,chipdefine.h


	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*
	函数功能：配置LDO电压

*/
void SetLDOVolt(unsigned char val_volt)
{
	unsigned char tmp;

	tmp = CtrlLDO;
	tmp &= ~0x07;
	tmp |= val_volt;
	CtrlLDO = tmp;	
}
