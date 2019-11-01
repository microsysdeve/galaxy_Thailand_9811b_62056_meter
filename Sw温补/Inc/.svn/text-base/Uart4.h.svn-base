#ifndef __Uart4_H__
#define __ComBottom_Uart4_H__

#define Const_DyUart4Over   0xff                        // 模拟口的溢出保护，在10ms中执行，等于0xff则初始化
//#define RS485_TWOLINE

#define Uart4_RevEn()       {P9OE&=~BIT5;P9IE&=~BIT5;P9OD|=BIT5;}
#define Uart4_SendEn()      {P9OE&=~BIT5;P9IE&=~BIT5;P9OD&=~BIT5;}

#define Uart4_CtrIoIdle()   {P9OE|=BIT5;P9IE&=~BIT5;}

#define CONST_UART4_DEFBPS  Const_BPS_2400


void Init_Uart4(uint8 ucBode);
void Uart4_Dy10ms(void);
void Uart4_Receive(void);
void Uart4_Transmit(void);



#endif
