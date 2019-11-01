/***************************** Copyright by Vango ***********************************
	文件名：SetMChannel.c
	相关头文件：EXTigReg.h,chipdefine.h


	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*功能：配置M通道
入口：val_channel：M 通道的测量通道选择：
	0x0: measure the ground;
	0x1: measure temperature
	0x22: measure battery SETM_VBAT1// 分压后
	0x23: measure battery SETM_VBAT2//  分压后
	0x03: measure external input VM//  不分压
	0x04: measure SEG33//  不分压
	0x05: measure SEG34//  不分压
	0x06: measure SEG35//  不分压
	0x07: measure SEG36//  不分压
	0x24: measure SEG33//  分压后
	0x25: measure SEG34//  分压后
	0x26: measure SEG35//  分压后
	0x27: measure SEG36//  分压后
	val_para：M 通道增益选择：
		SETM_T1 对应1倍增益
		SETM_T2 对应2倍增益
		SETM_CLOSE 表示关闭M通道

	val_para：M 通道增益选择：0，1，0x11，0x31 分别对应1，2，4，8 倍增益
								0x80表示关闭M通道
出口：无*/

void SetMChannel(unsigned char val_channel,unsigned char val_para)
{

	if(val_para&0x80)
	{
		CtrlADC &= ~0x08;//关m通道
		CtrlMEAS = 0;	
		return;
	}
	
	CtrlADC |= 0x08;//开m通道
	CtrlGM = val_para&0x01;
	CtrlMEAS &= 0x80;
	CtrlMEAS |= val_channel;	
}