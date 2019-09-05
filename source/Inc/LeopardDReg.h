/******************** (C) COPYRIGHT 2014 Vangotech ****************************
* File Name          : leopardDReg.h
* Author             : liming
* Version            : V1.0
* Date               : 2014-07-11
* Description        : register define
V1.0.1  for leopardD
*******************************************************************************/
#ifndef	__V98x1_H__
#define	__V98x1_H__

#ifdef __cplusplus
 extern "C" {
#endif//__cplusplus

#include "dw8051.h" 

#define xdata __xdata 
#define _at_        @
#define sfr         __sfr __no_init volatile unsigned char
#define XBYTE		((unsigned char volatile xdata *)0)
#define _nop()		asm("NOP");
/*************************************************************************
 *                  扩展外设寄存器外设定义
 *************************************************************************/
/********* base address ********/ 
#define __EX_PER_BASE	        0x2000	
     
/************  IIC  ************/
#define I2C_BASE	    (__EX_PER_BASE+0xf00)	  //I2C 
__no_init volatile unsigned char xdata     SICFG	_at_	I2C_BASE+0x01;	    //0x2f01 收发控制寄存器 
__no_init volatile unsigned char xdata     SITHL	_at_	I2C_BASE+0x02;	    //0x2f02 分频寄存器低8位
__no_init volatile unsigned char xdata     SITHH	_at_	I2C_BASE+0x03;	    //0x2f03 分频寄存器高8位
__no_init volatile unsigned char xdata     SIDAT	_at_	I2C_BASE+0x04;	    //0x2f04 数据寄存器
__no_init volatile unsigned char xdata     SIFLG	_at_	I2C_BASE+0x05;	    //0x2f05 应答寄存器

/************  UART  ************/
#define UART2_BASE		(__EX_PER_BASE+0x820)	  //UART2
__no_init volatile unsigned char xdata     TCON2  	_at_    UART2_BASE+0x00;    //0x2820 控制状态寄存器
__no_init volatile unsigned char xdata     TMOD2  	_at_    UART2_BASE+0x01;    //0x2821 定时器模式控制
__no_init volatile unsigned char xdata     TH20 	_at_	UART2_BASE+0x02;	//0x2822 普通定时器高位字节
__no_init volatile unsigned char xdata     TH21	    _at_	UART2_BASE+0x03;	//0x2823 波特率寄存器高位字节
__no_init volatile unsigned char xdata     TL20	    _at_	UART2_BASE+0x04;	//0x2824 普通定时器低位字节
__no_init volatile unsigned char xdata     TL21	    _at_	UART2_BASE+0x05;	//0x2825 波特率寄存器低位字节
__no_init volatile unsigned char xdata     SCON2	_at_	UART2_BASE+0x06;	//0x2826 控制寄存器
__no_init volatile unsigned char xdata     SBUF2	_at_	UART2_BASE+0x07;	//0x2827 数据缓冲寄存器

#define UART3_BASE		(__EX_PER_BASE+0x828)	  //UART3
__no_init volatile unsigned char xdata     TCON3  	_at_    UART3_BASE+0x00;	//0x2828 控制状态寄存器
__no_init volatile unsigned char xdata     TMOD3  	_at_    UART3_BASE+0x01;	//0x2829 定时器模式控制
__no_init volatile unsigned char xdata     TH30 	_at_	UART3_BASE+0x02;	//0x282A 普通定时器高位字节
__no_init volatile unsigned char xdata     TH31	    _at_	UART3_BASE+0x03;	//0x282B 波特率寄存器高位字节
__no_init volatile unsigned char xdata     TL30	    _at_	UART3_BASE+0x04;	//0x282C 普通定时器低位字节
__no_init volatile unsigned char xdata     TL31	    _at_	UART3_BASE+0x05;	//0x282D 波特率寄存器低位字节
__no_init volatile unsigned char xdata     SCON3	_at_	UART3_BASE+0x06;	//0x282E 控制寄存器
__no_init volatile unsigned char xdata     SBUF3	_at_	UART3_BASE+0x07;	//0x282F 数据缓冲寄存器

#define UART4_BASE		(__EX_PER_BASE+0x830)	  //UART4
__no_init volatile unsigned char xdata     TCON4  	_at_    UART4_BASE+0x00;	//0x2830 控制状态寄存器
__no_init volatile unsigned char xdata     TMOD4  	_at_    UART4_BASE+0x01;	//0x2831 定时器模式控制
__no_init volatile unsigned char xdata     TH40 	_at_	UART4_BASE+0x02;	//0x2832 普通定时器高位字节
__no_init volatile unsigned char xdata     TH41	    _at_	UART4_BASE+0x03;	//0x2833 波特率寄存器高位字节
__no_init volatile unsigned char xdata     TL40	    _at_	UART4_BASE+0x04;	//0x2834 普通定时器低位字节
__no_init volatile unsigned char xdata     TL41	    _at_	UART4_BASE+0x05;	//0x2835 波特率寄存器低位字节
__no_init volatile unsigned char xdata     SCON4	_at_	UART4_BASE+0x06;	//0x2836 控制寄存器
__no_init volatile unsigned char xdata     SBUF4	_at_	UART4_BASE+0x07;	//0x2837 数据缓冲寄存器

#define UART5_BASE		(__EX_PER_BASE+0x838)	  //UART5
__no_init volatile unsigned char xdata     TCON5  	_at_    UART5_BASE+0x00;	//0x2838 控制状态寄存器
__no_init volatile unsigned char xdata     TMOD5  	_at_    UART5_BASE+0x01;	//0x2839 定时器模式控制
__no_init volatile unsigned char xdata     TH50 	_at_	UART5_BASE+0x02;	//0x283A 普通定时器高位字节
__no_init volatile unsigned char xdata     TH51	    _at_	UART5_BASE+0x03;	//0x283B 波特率寄存器高位字节
__no_init volatile unsigned char xdata     TL50	    _at_	UART5_BASE+0x04;	//0x283C 普通定时器低位字节
__no_init volatile unsigned char xdata     TL51	    _at_	UART5_BASE+0x05;	//0x283D 波特率寄存器低位字节
__no_init volatile unsigned char xdata     SCON5	_at_	UART5_BASE+0x06;	//0x283E 控制寄存器
__no_init volatile unsigned char xdata     SBUF5	_at_	UART5_BASE+0x07;	//0x283F 数据缓冲寄存器


/************  Carrier 38K  ************/
#define	CARRY38K_BASE 	(__EX_PER_BASE+0x898)     //38K载波
__no_init volatile unsigned char xdata     CARRHH	_at_	CARRY38K_BASE+0x00; //0x2898 载波产生寄存器1：占空比控制，高电平持续时间高位寄存器
__no_init volatile unsigned char xdata     CARRHL	_at_	CARRY38K_BASE+0x01; //0x2899 载波产生寄存器2：占空比控制，高电平持续时间低位寄存器
__no_init volatile unsigned char xdata     CARRLH	_at_	CARRY38K_BASE+0x02; //0x289A 载波产生寄存器1：占空比控制，低电平持续时间高位寄存器
__no_init volatile unsigned char xdata     CARRLL	_at_	CARRY38K_BASE+0x03; //0x289B 载波产生寄存器2：占空比控制，低电平持续时间低位寄存器
__no_init volatile unsigned char xdata     Txd2FS	_at_    0x28cf;		        //0x28CF TXD2载波控制,0带38K载波;1不带38K载波

/************  TIMER  ************/
#define TIMA_BASE		(__EX_PER_BASE+0x900)	  //TIMER A
__no_init volatile unsigned char xdata     TACTL	_at_	TIMA_BASE+0x00;	    //0x2900 控制寄存器
__no_init volatile unsigned char xdata     TARL	    _at_	TIMA_BASE+0x02;	    //0x2902 TIMA计数寄存器低8位
__no_init volatile unsigned char xdata     TARH	    _at_	TIMA_BASE+0x03;	    //0x2903 TIMA计数寄存器高8位
__no_init volatile unsigned char xdata     TACCTL0	_at_    TIMA_BASE+0x04;	    //0x2904 0通道捕获比较控制寄存器低8位
__no_init volatile unsigned char xdata     TACCTH0	_at_    TIMA_BASE+0x05;	    //0x2905 0通道捕获比较控制寄存器高8位
__no_init volatile unsigned char xdata     TACCTL1	_at_    TIMA_BASE+0x06;	    //0x2906 1通道捕获比较控制寄存器低8位
__no_init volatile unsigned char xdata     TACCTH1	_at_    TIMA_BASE+0x07;	    //0x2907 1通道捕获比较控制寄存器高8位
__no_init volatile unsigned char xdata     TACCTL2	_at_    TIMA_BASE+0x08;	    //0x2908 2通道捕获比较控制寄存器低8位
__no_init volatile unsigned char xdata     TACCTH2	_at_    TIMA_BASE+0x09;	    //0x2909 2通道捕获比较控制寄存器高8位
__no_init volatile unsigned char xdata     TACCR0L	_at_    TIMA_BASE+0x0a;	    //0x290A 0通道捕获比较数据寄存器低8位
__no_init volatile unsigned char xdata     TACCR0H	_at_    TIMA_BASE+0x0b;	    //0x290B 0通道捕获比较数据寄存器高8位
__no_init volatile unsigned char xdata     TACCR1L	_at_    TIMA_BASE+0x0c;	    //0x290C 1通道捕获比较数据寄存器低8位
__no_init volatile unsigned char xdata     TACCR1H	_at_    TIMA_BASE+0x0d;	    //0x290D 1通道捕获比较数据寄存器高8位
__no_init volatile unsigned char xdata     TACCR2L	_at_    TIMA_BASE+0x0e;	    //0x290E 2通道捕获比较数据寄存器低8位
__no_init volatile unsigned char xdata     TACCR2H	_at_    TIMA_BASE+0x0f;	    //0x290F 2通道捕获比较数据寄存器高8位

/************  ESAM  ************/
#define ESAM1_BASE		(__EX_PER_BASE+0xA00)	  //ESAM1
__no_init volatile unsigned char xdata     DIVLA	_at_	ESAM1_BASE+0x01;	//0x2A01 波特率低位
__no_init volatile unsigned char xdata     DIVHA	_at_	ESAM1_BASE+0x02; 	//0x2A02 波特率高位
__no_init volatile unsigned char xdata     DATAA	_at_	ESAM1_BASE+0x03;	//0x2A03 数据寄存器
__no_init volatile unsigned char xdata     INFOA	_at_	ESAM1_BASE+0x04;	//0x2A04 信息寄存器
__no_init volatile unsigned char xdata     CFGA	    _at_	ESAM1_BASE+0x05;	//0x2A05 配置寄存器

#define ESAM2_BASE		(__EX_PER_BASE+0xB00)	  //ESAM2
__no_init volatile unsigned char xdata     DIVLB	_at_	ESAM2_BASE+0x01;	//0x2B01 波特率低位
__no_init volatile unsigned char xdata     DIVHB	_at_	ESAM2_BASE+0x02; 	//0x2B02 波特率高位
__no_init volatile unsigned char xdata     DATAB	_at_	ESAM2_BASE+0x03;	//0x2B03 数据寄存器
__no_init volatile unsigned char xdata     INFOB	_at_	ESAM2_BASE+0x04;	//0x2B04 信息寄存器
__no_init volatile unsigned char xdata     CFGB	    _at_    ESAM2_BASE+0x05;	//0x2B05 配置寄存器

/*** 可分频时钟输出 P9.7 ***/
#define PWM_BASE        (__EX_PER_BASE+0x89c)
__no_init volatile unsigned char xdata     PWMCLK1H _at_    PWM_BASE+0x00;      //0x289C 高电平持续时间高字节
__no_init volatile unsigned char xdata     PWMCLK1L _at_    PWM_BASE+0x01;      //0x289D 高电平持续时间低字节
__no_init volatile unsigned char xdata     PWMCLK2H _at_    PWM_BASE+0x02;      //0x289E 低电平持续时间高字节
__no_init volatile unsigned char xdata     PWMCLK2L _at_    PWM_BASE+0x03;      //0x289F 低电平持续时间低字节	

/************  GPIO  ************/
#define GPIO_BASE		(__EX_PER_BASE+0x800)	  //GPIO
#define P0_BASE			(GPIO_BASE+0xa8)	      //P1
__no_init volatile unsigned char xdata     P0OE	    _at_	P0_BASE+0x00;	    //0x28A8 P0输出使能寄存器
__no_init volatile unsigned char xdata     P0IE	    _at_	P0_BASE+0x01;	    //0x28A9 P0输入使能寄存器
__no_init volatile unsigned char xdata     P0OD	    _at_	P0_BASE+0x02;	    //0x28AA P0输出数据寄存器
__no_init volatile unsigned char xdata     P0ID	    _at_	P0_BASE+0x03;	    //0x28AB P0输入数据寄存器

#define P1_BASE			(GPIO_BASE+0xac)	      //P1
__no_init volatile unsigned char xdata     P1OE	    _at_	P1_BASE+0x00;	    //0x28AC P1输出使能寄存器
__no_init volatile unsigned char xdata     P1IE	    _at_	P1_BASE+0x01;	    //0x28AD P1输入使能寄存器
__no_init volatile unsigned char xdata     P1OD	    _at_	P1_BASE+0x02;	    //0x28AE P1输出数据寄存器
__no_init volatile unsigned char xdata     P1ID	    _at_	P1_BASE+0x03;	    //0x28AF P1输入数据寄存器

#define P2_BASE			(GPIO_BASE+0xb0)	      //P2
__no_init volatile unsigned char xdata     P2OE	    _at_	P2_BASE+0x00;	    //0x28B0 P2输出使能寄存器
__no_init volatile unsigned char xdata     P2IE	    _at_	P2_BASE+0x01;	    //0x28B1 P2输入使能寄存器
__no_init volatile unsigned char xdata     P2OD	    _at_	P2_BASE+0x02;	    //0x28B2 P2输出数据寄存器
__no_init volatile unsigned char xdata     P2ID	    _at_	P2_BASE+0x03;	    //0x28B3 P2输入数据寄存器

#define P3_BASE			(GPIO_BASE+0xb4)	      //P3
__no_init volatile unsigned char xdata     P3OE     _at_    P3_BASE+0x00;       //0x28B4 P3输出使能寄存器
__no_init volatile unsigned char xdata     P3IE	    _at_	P3_BASE+0x01;	    //0x28B5 P3输入使能寄存器
__no_init volatile unsigned char xdata     P3OD	    _at_	P3_BASE+0x02;	    //0x28B6 P3输出数据寄存器
__no_init volatile unsigned char xdata     P3ID	    _at_	P3_BASE+0x03;	    //0x28B7 P3输入数据寄存器

#define P4_BASE			(GPIO_BASE+0xb8)	      //P4
__no_init volatile unsigned char xdata     P4OE	    _at_	P4_BASE+0x00;	    //P4输出使能寄存器
__no_init volatile unsigned char xdata     P4IE	    _at_	P4_BASE+0x01;	    //P4输入使能寄存器
__no_init volatile unsigned char xdata     P4OD	    _at_	P4_BASE+0x02;	    //P4输出数据寄存器
__no_init volatile unsigned char xdata     P4ID	    _at_	P4_BASE+0x03;	    //P4输入数据寄存器

#define P5_BASE			(GPIO_BASE+0xbc)	      //P5
__no_init volatile unsigned char xdata     P5OE	    _at_	P5_BASE+0x00;	    //P5输出使能寄存器
__no_init volatile unsigned char xdata     P5IE	    _at_	P5_BASE+0x01;	    //P5输入使能寄存器
__no_init volatile unsigned char xdata     P5OD	    _at_	P5_BASE+0x02;	    //P5输出数据寄存器
__no_init volatile unsigned char xdata     P5ID	    _at_	P5_BASE+0x03;	    //P5输入数据寄存器

#define P6_BASE			(GPIO_BASE+0xc0)	      //P6
__no_init volatile unsigned char xdata     P6OE	    _at_	P6_BASE+0x00;	    //P6输出使能寄存器
__no_init volatile unsigned char xdata     P6IE	    _at_	P6_BASE+0x01;	    //P6输入使能寄存器
__no_init volatile unsigned char xdata     P6OD	    _at_	P6_BASE+0x02;	    //P6输出数据寄存器
__no_init volatile unsigned char xdata     P6ID	    _at_	P6_BASE+0x03;	    //P6输入数据寄存器

#define P7_BASE			(GPIO_BASE+0xd5)	      //P7
__no_init volatile unsigned char xdata     P7OE	    _at_	P7_BASE+0x00;	    //P7输出使能寄存器
__no_init volatile unsigned char xdata     P7IE	    _at_	P7_BASE+0x01;	    //P7输入使能寄存器
__no_init volatile unsigned char xdata     P7OD	    _at_	P7_BASE+0x02;	    //P7输出数据寄存器
__no_init volatile unsigned char xdata     P7ID	    _at_	P7_BASE+0x03;	    //P7输入数据寄存器

#define P8_BASE			(GPIO_BASE+0xd9)	      //P8
__no_init volatile unsigned char xdata     P8OE	    _at_	P8_BASE+0x00;	    //P8输出使能寄存器
__no_init volatile unsigned char xdata     P8IE	    _at_	P8_BASE+0x01;	    //P8输入使能寄存器
__no_init volatile unsigned char xdata     P8OD	    _at_	P8_BASE+0x02;	    //P8输出数据寄存器
__no_init volatile unsigned char xdata     P8ID	    _at_	P8_BASE+0x03;	    //P8输入数据寄存器

#define P9_BASE	        (0xa4)			          //P9
sfr	    P9OE      _at_  0xa4;	                  //P9输出使能寄存器
sfr	    P9IE      _at_  0xa5;	                  //P9输入使能寄存器
sfr	    P9OD      _at_  0xa6;		              //P9输出数据寄存器
sfr	    P9ID      _at_  0xa7;			          //P9输入数据寄存器
sfr     P9FS      _at_  0xad;			          //P9第二功能寄存器			

#define P10_BASE        (0xa9)				      //P10
sfr	    P10OE     _at_  0xa9;	  			      //P10输出使能寄存器
sfr	    P10IE     _at_  0xaa;				      //P10输入使能寄存器
sfr	    P10OD     _at_  0xab;				      //P10输出数据寄存器
sfr	    P10ID     _at_  0xac;				      //P10输入数据寄存器
    
/******** IO  Function  ***********/
#define P1FS_BASE		(GPIO_BASE+0xc4)	      //P1第二功能选择
__no_init volatile unsigned char xdata     P10FS	  _at_	P1FS_BASE+0x00;	  //P1.0功能 RTC秒脉冲输出;ADC多功能通道数据输出
__no_init volatile unsigned char xdata     P11FS	  _at_	P1FS_BASE+0x01;	  //P1.1功能 RTC高频时钟分频输出;RXD1;T1;端口中断2
__no_init volatile unsigned char xdata     P12FS	  _at_	P1FS_BASE+0x02;	  //P1.2功能 RC时钟输出;TXD1;T2EX;端口中断3
__no_init volatile unsigned char xdata     P13FS	  _at_	P1FS_BASE+0x03;   //P1.3功能 CF1;RXD5;端口中断0
__no_init volatile unsigned char xdata     P14FS	  _at_	P1FS_BASE+0x04;	  //P1.4功能 TXD5;端口中断1

#define P2FS_BASE		(GPIO_BASE+0xc9)	      //P2第二功能
__no_init volatile unsigned char xdata     P20FS	  _at_	P2FS_BASE+0x00;	  //P2.0功能 OSC时钟信号输出;RXD4;T2
__no_init volatile unsigned char xdata     P21FS	  _at_	P2FS_BASE+0x01;	  //P2.1功能 PLL时钟信号输出;TXD4;T0
__no_init volatile unsigned char xdata     P22FS	  _at_	P2FS_BASE+0x02;	  //P2.2功能 ADC CLK时钟信号输出;RXD3
__no_init volatile unsigned char xdata     P23FS	  _at_	P2FS_BASE+0x03;	  //P2.3功能 TXD3
__no_init volatile unsigned char xdata     P24FS	  _at_	P2FS_BASE+0x04;	  //P2.4功能 RXD2
__no_init volatile unsigned char xdata     P25FS	  _at_	P2FS_BASE+0x05;	  //P2.5功能 不带有/带有载波的的TXD2

/************  LCD  ************/
#define	LCD_BASE		(__EX_PER_BASE+0xC00)
__no_init volatile unsigned char xdata     LCDM0      _at_	LCD_BASE+0x00;	  //显示缓冲寄存器 0x2c00 
__no_init volatile unsigned char xdata     LCDM1      _at_	LCD_BASE+0x01;	  //显示缓冲寄存器 0x2c01
__no_init volatile unsigned char xdata     LCDM2      _at_	LCD_BASE+0x02;	  //显示缓冲寄存器 0x2c02
__no_init volatile unsigned char xdata     LCDM3      _at_	LCD_BASE+0x03;	  //显示缓冲寄存器 0x2c03
__no_init volatile unsigned char xdata     LCDM4      _at_	LCD_BASE+0x04;	  //显示缓冲寄存器 0x2c04
__no_init volatile unsigned char xdata     LCDM5      _at_	LCD_BASE+0x05;	  //显示缓冲寄存器 0x2c05
__no_init volatile unsigned char xdata     LCDM6      _at_	LCD_BASE+0x06;	  //显示缓冲寄存器 0x2c06
__no_init volatile unsigned char xdata     LCDM7      _at_	LCD_BASE+0x07;	  //显示缓冲寄存器 0x2c07
__no_init volatile unsigned char xdata     LCDM8      _at_	LCD_BASE+0x08;	  //显示缓冲寄存器 0x2c08
__no_init volatile unsigned char xdata     LCDM9      _at_	LCD_BASE+0x09;	  //显示缓冲寄存器 0x2c09
__no_init volatile unsigned char xdata     LCDM10     _at_	LCD_BASE+0x0a;	  //显示缓冲寄存器 0x2c0a
__no_init volatile unsigned char xdata     LCDM11     _at_	LCD_BASE+0x0b;	  //显示缓冲寄存器 0x2c0b
__no_init volatile unsigned char xdata     LCDM12     _at_	LCD_BASE+0x0c;	  //显示缓冲寄存器 0x2c0c
__no_init volatile unsigned char xdata     LCDM13     _at_	LCD_BASE+0x0d;	  //显示缓冲寄存器 0x2c0d
__no_init volatile unsigned char xdata     LCDM14     _at_	LCD_BASE+0x0e;	  //显示缓冲寄存器 0x2c0e
__no_init volatile unsigned char xdata     LCDM15     _at_	LCD_BASE+0x0f;	  //显示缓冲寄存器 0x2c0f
__no_init volatile unsigned char xdata     LCDM16     _at_	LCD_BASE+0x10;	  //显示缓冲寄存器 0x2c10
__no_init volatile unsigned char xdata     LCDM17     _at_	LCD_BASE+0x11;	  //显示缓冲寄存器 0x2c11
__no_init volatile unsigned char xdata     LCDM18     _at_	LCD_BASE+0x12;	  //显示缓冲寄存器 0x2c12
__no_init volatile unsigned char xdata     LCDM19     _at_	LCD_BASE+0x13;	  //显示缓冲寄存器 0x2c13
__no_init volatile unsigned char xdata     LCDM20     _at_	LCD_BASE+0x14;      //显示缓冲寄存器 0x2c14
__no_init volatile unsigned char xdata     LCDM21     _at_	LCD_BASE+0x15;      //显示缓冲寄存器 0x2c15
__no_init volatile unsigned char xdata     LCDM22     _at_	LCD_BASE+0x16;      //显示缓冲寄存器 0x2c16
__no_init volatile unsigned char xdata     LCDM23     _at_  LCD_BASE+0x17;      //显示缓冲寄存器 0x2c17
__no_init volatile unsigned char xdata     LCDM24     _at_	LCD_BASE+0x18;      //显示缓冲寄存器 0x2c18
__no_init volatile unsigned char xdata     LCDM25     _at_	LCD_BASE+0x19;      //显示缓冲寄存器 0x2c19
__no_init volatile unsigned char xdata     LCDM26     _at_	LCD_BASE+0x1a;      //显示缓冲寄存器 0x2c1a
__no_init volatile unsigned char xdata     LCDM27     _at_	LCD_BASE+0x1b;      //显示缓冲寄存器 0x2c1b
__no_init volatile unsigned char xdata     LCDM28     _at_	LCD_BASE+0x1c;      //显示缓冲寄存器 0x2c1c
__no_init volatile unsigned char xdata     LCDM29     _at_	LCD_BASE+0x1d;      //显示缓冲寄存器 0x2c1d
 
__no_init volatile unsigned char xdata     LCDM30     _at_	LCD_BASE+0x28;      //显示缓冲寄存器 0x2c28
__no_init volatile unsigned char xdata     LCDM31     _at_	LCD_BASE+0x29;      //显示缓冲寄存器 0x2c29
__no_init volatile unsigned char xdata     LCDM32     _at_	LCD_BASE+0x2a;      //显示缓冲寄存器 0x2c2a
__no_init volatile unsigned char xdata     LCDM33     _at_	LCD_BASE+0x2b;      //显示缓冲寄存器 0x2c2b
__no_init volatile unsigned char xdata     LCDM34     _at_	LCD_BASE+0x2c;      //显示缓冲寄存器 0x2c2c
__no_init volatile unsigned char xdata     LCDM35     _at_	LCD_BASE+0x2d;      //显示缓冲寄存器 0x2c2d
__no_init volatile unsigned char xdata     LCDM36     _at_	LCD_BASE+0x2e;      //显示缓冲寄存器 0x2c2e
__no_init volatile unsigned char xdata     LCDM37     _at_	LCD_BASE+0x2f;      //显示缓冲寄存器 0x2c2f
__no_init volatile unsigned char xdata     LCDM38     _at_	LCD_BASE+0x30;      //显示缓冲寄存器 0x2c30
__no_init volatile unsigned char xdata     LCDM39     _at_  LCD_BASE+0x31;      //显示缓冲寄存器 0x2c31
    
__no_init volatile unsigned char xdata     LCDCtrl    _at_	LCD_BASE+0x1e;	    //显示控制寄存器 
__no_init volatile unsigned char xdata     SegCtrl0   _at_	LCD_BASE+0x1f;	    //SEG开关控制寄存器0
__no_init volatile unsigned char xdata     SegCtrl1   _at_	LCD_BASE+0x20;	    //SEG开关控制寄存器1
__no_init volatile unsigned char xdata     SegCtrl2   _at_	LCD_BASE+0x21;	    //SEG开关控制寄存器2
__no_init volatile unsigned char xdata     SegCtrl3   _at_	LCD_BASE+0x22;	    //SEG开关控制寄存器3
__no_init volatile unsigned char xdata     SegCtrl4   _at_	LCD_BASE+0x23;	    //SEG开关控制寄存器4
__no_init volatile unsigned char xdata     LCDVCtrl   _at_ 	0x285e; 		    //LCD驱动电压控制寄存器

/************  CTRL REGS  ************/
#define ANALOG_BASE		(__EX_PER_BASE+0x858)	  //模拟控制寄存器
__no_init volatile unsigned char xdata     CtrlADC0	  _at_	ANALOG_BASE+0x00;	//0x2858 ADC增益控制	
__no_init volatile unsigned char xdata     CtrlADC1	  _at_	ANALOG_BASE+0x01;	//0x2859 ADC电流偏置控制
__no_init volatile unsigned char xdata     CtrlADC2	  _at_	ANALOG_BASE+0x02;	//0x285a ADC积分器控制
__no_init volatile unsigned char xdata     CtrlADC3	  _at_	ANALOG_BASE+0x03;	//0x285b ADC测试控制
__no_init volatile unsigned char xdata     CtrlBAT	  _at_	ANALOG_BASE+0x04;	//0x285c 电池放电
__no_init volatile unsigned char xdata     CtrlADC4	  _at_	ANALOG_BASE+0x05;	//0x285d ADC电压裕度
__no_init volatile unsigned char xdata     CtrlLCDV	  _at_	ANALOG_BASE+0x06;	//0x285e LCD电压控制
__no_init volatile unsigned char xdata     CtrlCry0	  _at_	ANALOG_BASE+0x07;	//0x285f 晶振微调
__no_init volatile unsigned char xdata     CtrlCry1	  _at_	ANALOG_BASE+0x08;	//0x2860 起振电容调节
__no_init volatile unsigned char xdata     CtrlCry2	  _at_	ANALOG_BASE+0x09;	//0x2861 晶振调节
__no_init volatile unsigned char xdata     CtrlBGP	  _at_  ANALOG_BASE+0x0a;	//0x2862 BGP控制
__no_init volatile unsigned char xdata     CtrlADC5	  _at_	ANALOG_BASE+0x0b;	//0x2863 M通道功能设置
__no_init volatile unsigned char xdata     CtrlADC6	  _at_	ANALOG_BASE+0x0c;	//0x2864 M通道开关控制
__no_init volatile unsigned char xdata     CtrlM	  _at_  ANALOG_BASE+0x0d;	//0x2865 M通道去直流控制
__no_init volatile unsigned char xdata     CtrlLDO	  _at_  ANALOG_BASE+0x0e;	//0x2866 LDO电压控制
__no_init volatile unsigned char xdata     CtrlCLK	  _at_  ANALOG_BASE+0x0f;	//0x2867 PLL DSP ADC 工作频率设置
__no_init volatile unsigned char xdata     CtrlPLL	  _at_  ANALOG_BASE+0x10;	//0x2868 PLL 设置
__no_init volatile unsigned char xdata     CtrlLDO33  _at_  ANALOG_BASE+0x11;	//0x2869
__no_init volatile unsigned char xdata     CtrlInfo   _at_  ANALOG_BASE+0x12;	//0x286a

/************  Expand Interrupt  ************/
#define ExInt2_BASE		(__EX_PER_BASE+0x840)
__no_init volatile unsigned char xdata     ExInt2IFG   _at_ ExInt2_BASE+0x00;	//中断向量8中断标志(请求)寄存器
__no_init volatile unsigned char xdata     ExInt2IN    _at_	ExInt2_BASE+0x01;	//中断向量8扩展中断输入类型寄存器
__no_init volatile unsigned char xdata     ExInt2OUT   _at_ ExInt2_BASE+0x02;	//中断向量8扩展中断输出类型寄存器
__no_init volatile unsigned char xdata     ExInt2IE    _at_	ExInt2_BASE+0x03;	//中断向量8扩展中断使能寄存器
__no_init volatile unsigned char xdata     ExInt2OV    _at_	ExInt2_BASE+0x04;	//中断向量8扩展中断队列寄存器

#define ExInt3_BASE		(__EX_PER_BASE+0x848)
__no_init volatile unsigned char xdata     ExInt3IFG   _at_ ExInt3_BASE+0x00;	//中断向量9中断标志(请求)寄存器
__no_init volatile unsigned char xdata     ExInt3IN    _at_	ExInt3_BASE+0x01;	//中断向量9扩展中断输入类型寄存器
__no_init volatile unsigned char xdata     ExInt3OUT   _at_ ExInt3_BASE+0x02;	//中断向量9扩展中断输出类型寄存器
__no_init volatile unsigned char xdata     ExInt3IE    _at_	ExInt3_BASE+0x03;	//中断向量9扩展中断使能寄存器
__no_init volatile unsigned char xdata     ExInt3OV    _at_	ExInt3_BASE+0x04;	//中断向量9扩展中断队列寄存器

#define ExInt4_BASE		(__EX_PER_BASE+0x850)
__no_init volatile unsigned char xdata     ExInt4IFG   _at_ ExInt4_BASE+0x00;	//中断向量10中断标志(请求)寄存器
__no_init volatile unsigned char xdata     ExInt4IN    _at_	ExInt4_BASE+0x01;	//中断向量10扩展中断输入类型寄存器
__no_init volatile unsigned char xdata     ExInt4OUT   _at_ ExInt4_BASE+0x02;	//中断向量10扩展中断输出类型寄存器
__no_init volatile unsigned char xdata     ExInt4IE    _at_	ExInt4_BASE+0x03;	//中断向量10扩展中断使能寄存器
__no_init volatile unsigned char xdata     ExInt4OV    _at_	ExInt4_BASE+0x04;	//中断向量10扩展中断队列寄存器

#define ExInt5_BASE		(__EX_PER_BASE+0x8a2)
__no_init volatile unsigned char xdata     ExInt5IFG   _at_ ExInt5_BASE+0x00;	//中断向量11中断标志(请求)寄存器
__no_init volatile unsigned char xdata     ExInt5IN    _at_	ExInt5_BASE+0x01;	//中断向量11扩展中断输入类型寄存器
__no_init volatile unsigned char xdata     ExInt5OUT   _at_ ExInt5_BASE+0x02;	//中断向量11扩展中断输出类型寄存器
__no_init volatile unsigned char xdata     ExInt5IE    _at_	ExInt5_BASE+0x03;	//中断向量11扩展中断使能寄存器
__no_init volatile unsigned char xdata     ExInt5OV    _at_	ExInt5_BASE+0x04;	//中断向量11扩展中断队列寄存器

/************  PM计量相关  ************/
#define BUFF0	        0x2880		//PM写缓存[7:0]
#define BUFF1	        0x2881		//PM写缓存[15:8]
#define BUFF2	        0x2882		//PM写缓存[23:16]
#define BUFF3	        0x2883		//PM写缓存[31:24]
#define INVD		    0x2884		//计量读写使能寄存器		
#define ACK		        0X2885		//PM状态寄存器
//计量控制
#define PMCtrl1         0x2878      //PM控制寄存器1
#define PMCtrl2         0x2879      //PM控制寄存器2
#define PMCtrl3         0x287a      //PM控制寄存器3
#define PHCCtrl1        0x287b      //角差校正控制寄存器1
#define PHCCtrl2        0x287c      //角差校正控制寄存器2
#define PMCtrl4         0x287d      //PM控制寄存器4
#define CFCtrl          0x287e      //脉冲输出控制寄存器
#define CRPST           0x287F      //防潜标志寄存器
#define IDET            0x2886      //电流检测

#define IDETTH          0x1002      //电流检测门限值寄存器
//原始波形寄存器
#define DATAOIU         0x1005      //瞬时电压原始值
#define DATAOII1        0x100A      //通道I1瞬时电流原始值
#define DATAOII2        0x100F      //通道I2瞬时电流原始值
#define DATAIAU         0x1051      //瞬时电压交流值
#define DATAIAI1        0x1052      //通道I1瞬时电流交流值
#define DATAIAI2        0x1053      //通道I2瞬时电流交流值
#define DATAIDU         0x103A      //瞬时电压直流值
#define DATAIDI1        0x1041      //通道I1瞬时电流直流值
#define DATAIDI2        0x1048      //通道I2瞬时电流直流值


//功率/电流数据寄存器
#define DATAIP          0x10d1
#define DATAIQ          0X10D2
#define RMSIU           0x10d3
#define RMSII1          0x10D4
#define RMSII2          0x10d5
#define DATAP           0X10D6
#define DATAQ           0x10d7
#define RMSU            0x10D8
#define RMSI1           0x10d9
#define RMSI2           0x10da
#define DATAAP1         0x10db
#define DATAAP2         0x10dc

//功率/有效值比差寄存器
#define SCP             0x10e8
#define SCQ             0x10e9
#define SCU             0x10ea
#define SCI1            0x10eb
#define SCI2            0x10ec
#define PARAPC          0x10ed
#define PARAQC          0x10ee
#define PARABPF         0x10ef
//能量累加寄存器/能量脉冲计数器
#define PPCNT           0x10f0
#define NPCNT           0x10f1
#define PPCFCNT         0x10f2
#define NPCFCNT         0x10f3
#define PQCNT           0x10f6
#define NQCNT           0x10f7
#define PQCFCNT         0x10f8
#define NQCFCNT         0x10f9
//门限值寄存器/常数功率值寄存器
#define GATEP           0x10f4
#define GATECP          0x10f5
#define GATEQ           0x10fa
#define GATECQ          0x10fb
#define DATACP          0x10fc
//频率值寄存器
#define DATAFREQ        0x10fd
//M通道数据寄存器
#define DATAOM          0x10ce
#define DATADM          0x10cf
#define DATAADM         0x10d0

/************  WDT  ************/
sfr WDTEN      _at_  0xce;	                        //WDT使能，密钥0xa5
sfr WDTCLR     _at_  0xcf;	                        //WDT清除，密钥0x5a

/************  SYSTEM CTRL  ************/
__no_init volatile unsigned char xdata     PRCtrl0  _at_       0x2d00;           //外设开关控制0
__no_init volatile unsigned char xdata     PRCtrl1  _at_       0x2d01;           //外设开关控制0
__no_init volatile unsigned char xdata     VERSION  _at_       0x286b;           //模拟电路版本和OSC状态监控 

sfr CBANK       _at_  0xa0;                             //代码段选择寄存器
sfr Systate	    _at_  0xa1;                             //系统状态
sfr WAKE_CTRL	_at_  0xc9;                             //休眠唤醒控制
sfr IOWK_STATE  _at_  0xaf;                             //IO休眠唤醒状态
sfr IOWK_CTRL	_at_  0xc7;                             //IO唤醒边沿控制  

sfr PLLLCK      _at_  0xa3;
__sfr __no_init volatile union
{
  unsigned char SysCtrl;
  struct 
  {
    unsigned char MCUFRQ :1;
    unsigned char SLEEP0 :1;
    unsigned char SLEEP1 :1;
    unsigned char LCDG :1;
    unsigned char PMG :1;
    unsigned char FSC :1;
    unsigned char FWC :1;
    unsigned char MEAFRQ :1;
  } SysCtrl_bit;
} @ 0x80;

#define MCUFRQ  SysCtrl_bit.MCUFRQ
#define SLEEP0  SysCtrl_bit.SLEEP0
#define SLEEP1  SysCtrl_bit.SLEEP1
#define LCDG    SysCtrl_bit.LCDG
#define PMG     SysCtrl_bit.PMG
#define FSC     SysCtrl_bit.FSC
#define FWC     SysCtrl_bit.FWC
#define MEAFRQ  SysCtrl_bit.MEAFRQ                        

/************  RTC  ************/
sfr RTCSC 	_at_ 0x9a;			//秒
sfr RTCMiC 	_at_ 0x9b;			//分
sfr RTCHC 	_at_ 0x9c;		 	//时
sfr RTCDC 	_at_ 0x9d;			//天
sfr RTCWC 	_at_ 0x9e;			//周
sfr RTCMoC 	_at_ 0x9f;			//月
sfr RTCYC 	_at_ 0x93;			//年
sfr RTCCH   _at_ 0x94;			//校正寄存器[15:8;
sfr RTCCL 	_at_ 0x95;			//校正寄存器[7:0;
sfr INTRTC 	_at_ 0x96;			//系统休眠唤醒间隔寄存器
sfr RTCPWD 	_at_ 0x97;			//密码寄存器
sfr RTCPEN  _at_ 0x90;			//密码使能寄存器
sfr RDRTC   _at_ 0xda;			//数据读取寄存器
sfr DIVTHH 	_at_ 0xdb;		   	//高频分频门限值高寄存器[23:16;
sfr DIVTHM 	_at_ 0xdc;			//高频分频门限值高寄存器[15:8;
sfr DIVTHL	_at_ 0xdd;			//高频分频门限值高寄存器[7:0;
sfr PLLCNT 	_at_ 0xde;	 		//高频计数状态寄存器
sfr SECINT  _at_ 0xdf;			//秒休眠唤醒间隔扩展寄存器

#ifdef __cplusplus
}
#endif//__cplusplus

#endif

