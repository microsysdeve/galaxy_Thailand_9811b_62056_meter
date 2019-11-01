/***************************** Copyright by Vango ***********************************
	文件名：SetPLL.c
	相关头文件：EXTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容
	2011.2.22	 1.4	  JJJ				去掉SetPLL中开启和关闭LDO33的操作
	2011.3.21	 1.5	  JJJ				将SetPLL中正常计量下CtrlBGP = 0x02，修改为CtrlBGP = 0x62  改善跳差

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//=======================================================
//函数名：Set_PLL
//函数作用：开关PLL，并将系统时钟切换至PLL或32k
//入口参数：:
//			PLLClk=0x00-- 切换到32K并关PLL 
//			PLLClk=0x60-- pll 800k, adc 200k,并切换到800kPLL
//			PLLClk=0x65-- pll 1.6M, adc 400k,并切换到1.6MPLL
//			PLLClk=0x6a-- pll 3.2M, adc 800k,并切换到3.2PLL
//			PLLClk=0x6f -- pll 6.4M, adc 1.6M,并切换到6.4MPLL
//			

//出口参数：无
//
//=======================================================


void SetPLL(unsigned char PLLClk)
{
	unsigned char tmp = 0;
	unsigned char i;
//	if(Systate&0x02)
//		CtrlMEAS |= 0x80;
//	else
//	CtrlMEAS &= ~0x80;
	if(PLLClk&PLLPDN)
	{
		tmp = 1;
	}
	F0 = 0;		//F0是用于快速开启PLL，如果F0=1，则CtrlCLK就无法修改系统时钟

	if((CtrlCLK != PLLClk))
	{
		CLKFRQ = 0;
		while(CLKFRQ);//先将系统主时钟切到32k
		CtrlCLK = 0x20;
		for(i=0;i<10;i++);
		CtrlCLK = PLLClk;//再切换PLL时钟
		for(i=0;i<5;i++);	
	}
	
	CLKFRQ = tmp;//最后切换主时钟到目标状态	

//	CtrlBGP &= ~0xf0;//PLL高频时，设置ADC高功耗
	if((PLLClk&0x0c)==0x0)
	{	
		//CtrlBGP |= ADPOWER;//PLL低频时，设置ADC低功耗
		CtrlBGP = 0xe2;;
		CtrlIAT = 0x1A;
		CtrlIBT = 0x1A;
		CtrlUT = 0x1A;
		CtrlMT = 0x1A;
	}
	else
	{
		CtrlIAT = 0x0;
		CtrlIBT = 0x0;
		CtrlUT = 0x0;
		CtrlMT = 0x0;
		CtrlBGP = 0x62;		 //配置改善跳差
	}
	if(CLKFRQ==0)
		CtrlADC = 0;//系统32k时，关闭ADC

	CtrlCry &= ~0x70;//调整ref电压温度系数
//	CtrlBGP |= BGPCHOP;//开BGPCHOP

}



