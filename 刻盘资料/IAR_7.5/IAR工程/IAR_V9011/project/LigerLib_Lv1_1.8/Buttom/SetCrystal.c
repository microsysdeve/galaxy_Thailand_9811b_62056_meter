/***************************** Copyright by Vango ***********************************
	文件名：SetCrystal.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/

#include "ExLigReg.h"
#include "chipdefine.h"


/*	功能：配置晶振高低功耗，配置晶振频率。
	入口：
	val_power：
	晶振功耗选择：8----晶振低功耗；0----晶振高功耗；
	val_freq：
	晶振频率选择：0、1、2、3、4、5、6、7晶振频率递减。
	出口：无
*/
void SetCrystal(unsigned char val_power, unsigned char val_freq)
{
	CtrlCry &= 0xf0;
	CtrlCry = val_power|val_freq;
}
