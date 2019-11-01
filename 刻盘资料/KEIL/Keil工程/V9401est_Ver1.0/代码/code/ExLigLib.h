
/***************** Copyright by Vango ***********************************
	文件名：ExLigLib.h

	创 建 人：huangsufang
	创建日期：2010-03-03 
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容
	2010-03-03   1.0      huangsufang         初建用于V9011和V9311的头文件

**********************************************************************/
#ifndef _DEFINE_H
#define _DEFINE_H
/*
功能：判断当前频率是否为用户目标频率，如果不是，切换PLL频率，
	并将系统主时钟切换到当前PLL频率，
	设置ADC功耗，调整ref温度系数，开BGPCHOP
入口：val_para：
		SETPLL_CLOSE 如果当前系统主时钟不是32k，则将系统主时钟切到32k，关闭PLL。
		SETPLL_800K 如果当前PLL 不是工作在 800k，则将PLL切到800k，设置ADC低功耗
		SETPLL_1_6M 如果当前PLL 不是工作在 1.6M，则将PLL切到1.6M，设置ADC低功耗
		SETPLL_3_2M 如果当前PLL 不是工作在 3.2M，则将PLL切到3.2M，设置ADC高功耗
		SETPLL_6_4M 如果当前PLL 不是工作在 6.4M，则将PLL切到6.4M，设置ADC高功耗
*/
extern void SetPLL(unsigned char val_para);
#define SETPLL_CLOSE 0x00
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6f

#endif







