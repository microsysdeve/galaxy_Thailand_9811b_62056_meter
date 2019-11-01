/****************************************Copyright (c)**************************************************
**                                        �򹤿Ƽ����޹�˾
**                                          ϵͳ���̲�
**
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: Uart2.h
**��   ��   ��: lwb
**����޸�����: 2011��8��17��
**��        ��: Uart2
**ע        �⣺
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: lwb
** ��  ��: v1.0
** �ա���: 2011��8��17��
** �衡��: ԭʼ�汾
********************************************************************************************************/

#ifndef __UART2_H__
#define __UART2_H__

#ifndef UART2_EXT
#define UART2_EXT extern
#endif

#define Const_DyUart2Over   0xff                        // ģ��ڵ������������10ms��ִ�У�����0xff���ʼ��

#define Uart2_RevEn()  {ExInt2IE|=BIT1;ExInt2IE&=~BIT0;}
#define Uart2_SendEn()  {ExInt2IE&=~BIT1;ExInt2IE|=BIT0;}

#define CONST_UART2_DEFBPS  Const_BPS_1200


void Init_Uart2(uint8 ucBode,uint8 uctype);
void Uart2_Dy10ms(void);
void Uart2_Receive(void);
void Uart2_Transmit(void);


#endif





