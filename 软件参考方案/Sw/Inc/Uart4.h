/****************************************Copyright (c)**************************************************
**                                        万工科技有限公司
**                                          系统工程部
**
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: Uart4.h
**创   建   人: lwb
**最后修改日期: 2011年8月17日
**描        述: Uart4
**注        意：
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: lwb
** 版  本: v1.0
** 日　期: 2011年8月17日
** 描　述: 原始版本
********************************************************************************************************/

#ifndef __Uart4_H__
#define __Uart4_H__

#ifndef Uart4_EXT
#define Uart4_EXT extern
#endif

#define Const_DyUart4Over   0xff                        // 模拟口的溢出保护，在10ms中执行，等于0xff则初始化
//#define RS485_TWOLINE

#define Uart4_RevEn()       {ExInt2IE|=BIT3;ExInt2IE&=~BIT2;}
#define Uart4_SendEn()      {ExInt2IE&=~BIT3;ExInt2IE|=BIT2;}

#define Uart4_CtrIoIdle()   {/*P9OE|=BIT5;P9IE&=~BIT5;*/}

#define CONST_UART4_DEFBPS  Const_BPS_2400


void Init_Uart4(uint8 ucBode,uint8 uctype);
void Uart4_Dy10ms(void);
void Uart4_Receive(void);
void Uart4_Transmit(void);


#endif





