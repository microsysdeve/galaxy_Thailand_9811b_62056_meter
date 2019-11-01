/***************************** Copyright by Vango ***********************************
	文件名：ReadMeterPara.c
	相关头文件：EXTigReg.h,chipdefine.h,intrins.h


	创 建 人：huangsufang
	创建日期：2010-03-03
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
//#include "pmRead.h"
#include <INTRINSICS.H>

/*功能：读取计量模块参数
	addr：计量寄存器地址
	读取数据存放在全局变量u32PMdatal、8PMdatah
	
*/

void ReadMeterPara(unsigned int addr)
{
      volatile unsigned char xdata* u8Point;
      volatile unsigned long xdata* u32Point;
      unsigned long u32Data;
     // unsigned char i;


      u8Point = (volatile unsigned char xdata*)addr;
    //  i  = *u8Point;
       __no_operation();__no_operation();__no_operation();
    
 //   mt_rd_buff();
    u8Point = (volatile unsigned char xdata*)0x10ec;
    u8PMdatah = *u8Point;
    u32Point = (volatile unsigned long xdata*)0x10e8;
    u32Data = *u32Point;
    u32PMdatal = ((u32Data&0xff)<<24)|((u32Data&0xff00)<<8)|((u32Data&0xff0000)>>8)|((u32Data)>>24);

}

