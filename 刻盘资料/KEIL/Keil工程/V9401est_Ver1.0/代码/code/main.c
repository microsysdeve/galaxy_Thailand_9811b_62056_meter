 /***************************** Copyright by Vango ***********************************

	文件类型：V9401TEST C51 Keil3编写编译
	文件作用：主要用于SuperDebug下载实验,下载完成后，若看见LED连续间隔300ms闪烁4次，停顿1.8S左右
			  继续闪烁。并以此为循环。则实验成功。

	创 建 人：DL
	创建日期：2011年12月31日
	当前版本：V9401Test_Ver1.0
	
	版本信息：V9401Test_ver1.0
**************************************************************************************/
#include "dw8051.h"
#include "ExLigReg.h"
#include "ExLigLib.h"
#include "delay.h"
#include "func.h"


void main()
{
	Init_Port();
	SetPLL(SETPLL_3_2M);//设置3.2M的MCU时钟，单独调试（F11）此函数会失去调试连接
	ClearWDT();
	while(1)
	{
		Led_Twin(4);
		ClearWDT();
		delayms(500);//加上面灭灯时的300ms所以，间隔为1.8s
		delayms(500);
		delayms(500);
		ClearWDT();
	}
		
}