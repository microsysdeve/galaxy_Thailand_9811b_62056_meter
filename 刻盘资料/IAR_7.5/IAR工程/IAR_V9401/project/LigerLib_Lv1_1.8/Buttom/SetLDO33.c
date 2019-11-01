
/***************************** Copyright by Vango ***********************************
	文件名：SetLDO33.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：JJJ
	创建日期：2011-02-21
	当前版本：1.4

	修改记录 : 
	日 期        版本     修改人              修改内容
	

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"

//函数名：SetLDO33
//函数作用：设置LDO33开启或关闭
//入口参数:
//			0,关闭LDO33
//			1，开启LDO33
//			
//出口参数：无
//
void SetLDO33(unsigned char Val_LDO33)
{
	
	if(!Val_LDO33)
		CtrlMEAS |= 0x80;
	else
		CtrlMEAS &= ~0x80;		
}