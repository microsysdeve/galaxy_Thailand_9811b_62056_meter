
#ifndef __DELAY_H__
#define __DELAY_H__
#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long
extern void delay_100ms(unsigned int sec);//MCU=13MHZ时为100ms延时
extern void delayms(unsigned int ms);//mcu=13MHZ时为1ms延时

#endif
