/***************************** Copyright by Vango ***********************************
	文件名：SetLCDVolt.c
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
	函数功能：配置LCD驱动电压
	函数入口：val_volt: 0x80 -- 3.0v//只针对电阻分压
						0 -- 3.3v
						0x10 -- 3.5v
						others -- no effect	
*/

void SetLCDVolt(unsigned char val_volt)
{

		CtrlCry &= ~P3V; 		// 选择3.3V
		CtrlLDO &= ~P3V5;
		CtrlCry |= (val_volt&P3V);
		CtrlLDO |= (val_volt&P3V5);
}