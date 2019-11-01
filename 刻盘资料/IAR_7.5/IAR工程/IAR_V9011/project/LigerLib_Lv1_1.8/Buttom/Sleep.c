/***************************** Copyright by Vango ***********************************
	文件名：Sleep.c
	相关头文件XTigReg.h,chipdefine.h

	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"



/*功能：
	关LDO33
	设置LDO25输出电压最低 大约2.1V；
	关AD；
	禁止计量电路访问双口ram；关闭所有计量通道；关PM时钟；
	将系统切到低频工作；
	关PLL；
	让系统慢速进入浅睡眠。
*/

void Sleep(void)
{
	F0 = 0;
	CtrlMEAS = 0x80;
	CtrlLDO  &= ~0x07;
	CtrlLDO  |= LDOVSEL1;//LDO25输出电压最低 大约2.1V
	CtrlADC = 0;	//关AD
	//关闭所有计量通道；关PM时钟
	PMCtrl1 = 0;
	PMCtrl4 = 0;
	PMG = 1;
//	switch_clk = 0;//将主时钟切换到OSC
//	F1 = 1;// PLL切换到OSC，关闭PLL，系统进入浅睡眠
	CLKFRQ = 0;//将主时钟切换到32k
	while(CLKFRQ);
	CtrlCLK = 0;//关PLL
	SLEEP1 = 0;
	SLEEP0 = 1;// 系统慢速进入深睡眠
	while(1);
}