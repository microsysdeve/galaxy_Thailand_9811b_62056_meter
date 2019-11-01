
#ifndef _FUNC_H_
#define _FUNC_H

//****************置位标志宏定义*******************************
#define BIT0 0X01
#define BIT1 0X02
#define BIT2 0X04
#define BIT3 0X08
#define BIT4 0X10
#define BIT5 0X20
#define BIT6 0X40
#define BIT7 0X80
//**************************************************************
#define LED_ON() {P1OE &= (~BIT4);P1IE &= ~BIT4; P1OD |= BIT4;}//开启LED。PCBIO1.4
#define LED_OFF() {P1OE &= (~BIT4);P1IE &= ~BIT4;P1OD &= (~BIT4);}//关闭LED
/*****************************************************************************
//*****************************************************************************

/******************************************************************************
 * @brief 
 * 喂狗操作
 * 注意：在调试模式下，看门狗失效，请不要检测看门狗是否复位。
 * 看门狗假如没有喂，1.5秒复位一次，通常在秒中断时清除WDT 计数值.
 *******************************************************************************/
#define ClearWDT() {WDTEN=0xa5;WDTCLR=0x5a;}

extern void Led_Twin(unsigned char i);//测试LED函数

extern void delay(unsigned int sec);//延时函数
extern void delayms(unsigned int j);//延时
extern void Init_Port(void);

 #endif
