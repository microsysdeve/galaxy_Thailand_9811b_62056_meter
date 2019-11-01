/***************************** Copyright by Vango ***********************************
	文件名：InitAnalog.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//将没有用到过的寄存器位清零
void InitAnalog(void)
{
	volatile unsigned char xdata *point;
	point = &CtrlSHORT;
	*point = 0;
	point++;
	point++;
	*point = 0;	
	point = &CtrlPLL;
	*point = 0;	
}