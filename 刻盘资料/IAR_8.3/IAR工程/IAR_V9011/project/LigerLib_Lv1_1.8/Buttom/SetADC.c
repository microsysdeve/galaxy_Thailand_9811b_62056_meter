
/***************************** Copyright by Vango ***********************************
	文件名：SetADC.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/

#include "ExLigReg.h"
#include "chipdefine.h"
//#include "absacc.h"
//#include "exlib.h"
/*	功能：配置电流、电压通道。
	入口：
	val_channel：ADC 选择通道：
			SETADC_IA ----电流A 通道;
			SETADC_IB ----电流B 通道;
			SETADC_U ----电压通道
	val_para：ADC 增益选择：
			SETADC_IT1 对应IA、IB通道1倍增益;
			SETADC_IT4 对应IA、IB通道4倍增益;
			SETADC_IT8 对应IA、IB通道8倍增益;
			SETADC_IT16 对应IA、IB通道16倍增益;
			SETADC_UT1 对应U通道1倍增益;
			SETADC_CLOSE 关闭相应通道
		#define SETADC_IA 		0
		#define SETADC_IB 		1
		#define SETADC_U 		2
		#define SETADC_IT1 		0
		#define SETADC_IT4 		1
		#define SETADC_IT8 		2
		#define SETADC_IT16 	3		
		#define SETADC_UT1 		0
		#define SETADC_CLOSE 		0x80
	出口：无
	  注意：电压ADC只有1倍增益（无增益），电流ADC只有1、4、8、16四种增益。
*/


void SetADC(unsigned char val_channel,unsigned char val_para)
{
//	unsigned char xdata *point;
	unsigned char  tmp;
	val_channel &= 0x03;
	tmp = CtrlADC;

	if(val_para&0x80)
	{
		CtrlADC =tmp&(~(0x01<<val_channel));
		return;
	}
	val_para = val_para&0x0f;
	tmp |=(0x01<< val_channel);

	CtrlADC = tmp;

	XBYTE[0x2858+val_channel] = val_para;
}
