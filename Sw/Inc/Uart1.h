#ifndef __Uart1_H__
#define __ComBottom_Uart1_H__
#define FRCom
#define Const_DyUart1Over   0xff                        // ģ��ڵ������������10ms��ִ�У�����0xff���ʼ��

#define Uart1_RevEn()
#define Uart1_SendEn()

#define CONST_UART1_DEFBPS  Const_BPS_2400


void Init_Uart1(void);
void Uart1_Dy10ms(void);
void Uart1_Receive(void);
void Uart1_Transmit(void);



#endif
