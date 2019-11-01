/****************************************Copyright (c)**************************************************
**                                        �򹤿Ƽ����޹�˾
**                                          ϵͳ���̲�
**
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: Uart4.h
**��   ��   ��: lwb
**����޸�����: 2011��8��17��
**��        ��: Uart4
**ע        �⣺
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: lwb
** ��  ��: v1.0
** �ա���: 2011��8��17��
** �衡��: ԭʼ�汾
********************************************************************************************************/

#ifndef __Uart4_H__
#define __Uart4_H__

#ifndef Uart4_EXT
#define Uart4_EXT extern
#endif

#define Const_DyUart4Over   0xff                        // ģ��ڵ������������10ms��ִ�У�����0xff���ʼ��
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





