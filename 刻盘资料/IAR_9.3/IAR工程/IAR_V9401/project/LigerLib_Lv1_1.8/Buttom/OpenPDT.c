/***************************** Copyright by Vango ***********************************
	文件名：OpenPDT.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2008—12-0
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*功能：打开BGP，打开powerdown 检测。
出口：无
*/
void OpenPDT(void)
{
	CtrlCLK |= BGPPDN;//打开BGP
	CtrlLDO |= DGEN;
}