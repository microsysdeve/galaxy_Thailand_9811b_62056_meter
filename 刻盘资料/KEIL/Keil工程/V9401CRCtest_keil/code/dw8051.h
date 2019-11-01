/***************** Copyright by Vango ***********************************
	文件名：DW8051.h

	创 建 人：huangsufang
	创建日期：2010-03-03 
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容
	2010-03-03   1.0      huangsufang         初建用于V9011和V9311的头文件

**********************************************************************/
#ifndef _DW8051_H_
#define _DW8051_H_

/* STANDARD 8052 */
#include "reg52.h"

/* NEWADD FOR ZEBOR */
/* DW8051 NEW_REG */
sfr	CKCON = 0x8E;	
sfr EICON = 0xd8;

sfr EIE = 0xE8;
sfr EXIF = 0x91;
sfr EIP	= 0xf8;

sfr SCON1 = 0xC0;
sfr SBUF1 = 0xC1;

sfr DPL1   = 0x84;
sfr DPH1   = 0x85;
sfr isfr   = 0xf1;
sfr debug  = 0xff;
sfr SPCFNC  = 0x8F; //wrs


#endif
