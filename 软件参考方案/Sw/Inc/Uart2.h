/****************************************Copyright (c)**************************************************
**                                        万工科技有限公司
**                                          系统工程部
**
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: Uart2.h
**创   建   人: lwb
**最后修改日期: 2011年8月17日
**描        述: Uart2
**注        意：
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: lwb
** 版  本: v1.0
** 日　期: 2011年8月17日
** 描　述: 原始版本
********************************************************************************************************/

#ifndef __UART2_H__
#define __UART2_H__

#ifndef UART2_EXT
#define UART2_EXT extern
#endif

#define Const_DyUart2Over   0xff                        // 模拟口的溢出保护，在10ms中执行，等于0xff则初始化

#define Uart2_RevEn()  {ExInt2IE|=BIT1;ExInt2IE&=~BIT0;}
#define Uart2_SendEn()  {ExInt2IE&=~BIT1;ExInt2IE|=BIT0;}

#define CONST_UART2_DEFBPS  Const_BPS_1200


void Init_Uart2(uint8 ucBode,uint8 uctype);
void Uart2_Dy10ms(void);
void Uart2_Receive(void);
void Uart2_Transmit(void);


#endif





