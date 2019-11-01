/***************************** Copyright by Vango ***********************************
	文件名：Alt_BatDisc.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*功能： 电池放电选择
入口： val_para：0----关闭电池放电功能，1----打开电池放电功能
出口：无
#define Enable_BatDisc 1
#define Disable_BatDisc 0
当电池长时间不使用时，使能电池放电Alt_BatDisc(Enable_BatDisc)，以防止电池进行钝化状态。
电池放电过程中，电池上消耗的电流约为3mA,大约过500ms，关闭电池放电功能Alt_BatDisc(Disable_BatDis),
具体时间与电池性能相关。
*/

void Alt_BatDisc(unsigned char val_para)
{
	if(val_para==0)
		CtrlBAT &= ~0x08;
	else CtrlBAT |= 0x08;
}
