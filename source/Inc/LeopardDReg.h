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
 *                  ��չ����Ĵ������趨��
 *************************************************************************/
/********* base address ********/ 
#define __EX_PER_BASE	        0x2000	
     
/************  IIC  ************/
#define I2C_BASE	    (__EX_PER_BASE+0xf00)	  //I2C 
__no_init volatile unsigned char xdata     SICFG	_at_	I2C_BASE+0x01;	    //0x2f01 �շ����ƼĴ��� 
__no_init volatile unsigned char xdata     SITHL	_at_	I2C_BASE+0x02;	    //0x2f02 ��Ƶ�Ĵ�����8λ
__no_init volatile unsigned char xdata     SITHH	_at_	I2C_BASE+0x03;	    //0x2f03 ��Ƶ�Ĵ�����8λ
__no_init volatile unsigned char xdata     SIDAT	_at_	I2C_BASE+0x04;	    //0x2f04 ���ݼĴ���
__no_init volatile unsigned char xdata     SIFLG	_at_	I2C_BASE+0x05;	    //0x2f05 Ӧ��Ĵ���

/************  UART  ************/
#define UART2_BASE		(__EX_PER_BASE+0x820)	  //UART2
__no_init volatile unsigned char xdata     TCON2  	_at_    UART2_BASE+0x00;    //0x2820 ����״̬�Ĵ���
__no_init volatile unsigned char xdata     TMOD2  	_at_    UART2_BASE+0x01;    //0x2821 ��ʱ��ģʽ����
__no_init volatile unsigned char xdata     TH20 	_at_	UART2_BASE+0x02;	//0x2822 ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TH21	    _at_	UART2_BASE+0x03;	//0x2823 �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     TL20	    _at_	UART2_BASE+0x04;	//0x2824 ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TL21	    _at_	UART2_BASE+0x05;	//0x2825 �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     SCON2	_at_	UART2_BASE+0x06;	//0x2826 ���ƼĴ���
__no_init volatile unsigned char xdata     SBUF2	_at_	UART2_BASE+0x07;	//0x2827 ���ݻ���Ĵ���

#define UART3_BASE		(__EX_PER_BASE+0x828)	  //UART3
__no_init volatile unsigned char xdata     TCON3  	_at_    UART3_BASE+0x00;	//0x2828 ����״̬�Ĵ���
__no_init volatile unsigned char xdata     TMOD3  	_at_    UART3_BASE+0x01;	//0x2829 ��ʱ��ģʽ����
__no_init volatile unsigned char xdata     TH30 	_at_	UART3_BASE+0x02;	//0x282A ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TH31	    _at_	UART3_BASE+0x03;	//0x282B �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     TL30	    _at_	UART3_BASE+0x04;	//0x282C ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TL31	    _at_	UART3_BASE+0x05;	//0x282D �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     SCON3	_at_	UART3_BASE+0x06;	//0x282E ���ƼĴ���
__no_init volatile unsigned char xdata     SBUF3	_at_	UART3_BASE+0x07;	//0x282F ���ݻ���Ĵ���

#define UART4_BASE		(__EX_PER_BASE+0x830)	  //UART4
__no_init volatile unsigned char xdata     TCON4  	_at_    UART4_BASE+0x00;	//0x2830 ����״̬�Ĵ���
__no_init volatile unsigned char xdata     TMOD4  	_at_    UART4_BASE+0x01;	//0x2831 ��ʱ��ģʽ����
__no_init volatile unsigned char xdata     TH40 	_at_	UART4_BASE+0x02;	//0x2832 ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TH41	    _at_	UART4_BASE+0x03;	//0x2833 �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     TL40	    _at_	UART4_BASE+0x04;	//0x2834 ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TL41	    _at_	UART4_BASE+0x05;	//0x2835 �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     SCON4	_at_	UART4_BASE+0x06;	//0x2836 ���ƼĴ���
__no_init volatile unsigned char xdata     SBUF4	_at_	UART4_BASE+0x07;	//0x2837 ���ݻ���Ĵ���

#define UART5_BASE		(__EX_PER_BASE+0x838)	  //UART5
__no_init volatile unsigned char xdata     TCON5  	_at_    UART5_BASE+0x00;	//0x2838 ����״̬�Ĵ���
__no_init volatile unsigned char xdata     TMOD5  	_at_    UART5_BASE+0x01;	//0x2839 ��ʱ��ģʽ����
__no_init volatile unsigned char xdata     TH50 	_at_	UART5_BASE+0x02;	//0x283A ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TH51	    _at_	UART5_BASE+0x03;	//0x283B �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     TL50	    _at_	UART5_BASE+0x04;	//0x283C ��ͨ��ʱ����λ�ֽ�
__no_init volatile unsigned char xdata     TL51	    _at_	UART5_BASE+0x05;	//0x283D �����ʼĴ�����λ�ֽ�
__no_init volatile unsigned char xdata     SCON5	_at_	UART5_BASE+0x06;	//0x283E ���ƼĴ���
__no_init volatile unsigned char xdata     SBUF5	_at_	UART5_BASE+0x07;	//0x283F ���ݻ���Ĵ���


/************  Carrier 38K  ************/
#define	CARRY38K_BASE 	(__EX_PER_BASE+0x898)     //38K�ز�
__no_init volatile unsigned char xdata     CARRHH	_at_	CARRY38K_BASE+0x00; //0x2898 �ز������Ĵ���1��ռ�ձȿ��ƣ��ߵ�ƽ����ʱ���λ�Ĵ���
__no_init volatile unsigned char xdata     CARRHL	_at_	CARRY38K_BASE+0x01; //0x2899 �ز������Ĵ���2��ռ�ձȿ��ƣ��ߵ�ƽ����ʱ���λ�Ĵ���
__no_init volatile unsigned char xdata     CARRLH	_at_	CARRY38K_BASE+0x02; //0x289A �ز������Ĵ���1��ռ�ձȿ��ƣ��͵�ƽ����ʱ���λ�Ĵ���
__no_init volatile unsigned char xdata     CARRLL	_at_	CARRY38K_BASE+0x03; //0x289B �ز������Ĵ���2��ռ�ձȿ��ƣ��͵�ƽ����ʱ���λ�Ĵ���
__no_init volatile unsigned char xdata     Txd2FS	_at_    0x28cf;		        //0x28CF TXD2�ز�����,0��38K�ز�;1����38K�ز�

/************  TIMER  ************/
#define TIMA_BASE		(__EX_PER_BASE+0x900)	  //TIMER A
__no_init volatile unsigned char xdata     TACTL	_at_	TIMA_BASE+0x00;	    //0x2900 ���ƼĴ���
__no_init volatile unsigned char xdata     TARL	    _at_	TIMA_BASE+0x02;	    //0x2902 TIMA�����Ĵ�����8λ
__no_init volatile unsigned char xdata     TARH	    _at_	TIMA_BASE+0x03;	    //0x2903 TIMA�����Ĵ�����8λ
__no_init volatile unsigned char xdata     TACCTL0	_at_    TIMA_BASE+0x04;	    //0x2904 0ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCTH0	_at_    TIMA_BASE+0x05;	    //0x2905 0ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCTL1	_at_    TIMA_BASE+0x06;	    //0x2906 1ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCTH1	_at_    TIMA_BASE+0x07;	    //0x2907 1ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCTL2	_at_    TIMA_BASE+0x08;	    //0x2908 2ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCTH2	_at_    TIMA_BASE+0x09;	    //0x2909 2ͨ������ȽϿ��ƼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR0L	_at_    TIMA_BASE+0x0a;	    //0x290A 0ͨ������Ƚ����ݼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR0H	_at_    TIMA_BASE+0x0b;	    //0x290B 0ͨ������Ƚ����ݼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR1L	_at_    TIMA_BASE+0x0c;	    //0x290C 1ͨ������Ƚ����ݼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR1H	_at_    TIMA_BASE+0x0d;	    //0x290D 1ͨ������Ƚ����ݼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR2L	_at_    TIMA_BASE+0x0e;	    //0x290E 2ͨ������Ƚ����ݼĴ�����8λ
__no_init volatile unsigned char xdata     TACCR2H	_at_    TIMA_BASE+0x0f;	    //0x290F 2ͨ������Ƚ����ݼĴ�����8λ

/************  ESAM  ************/
#define ESAM1_BASE		(__EX_PER_BASE+0xA00)	  //ESAM1
__no_init volatile unsigned char xdata     DIVLA	_at_	ESAM1_BASE+0x01;	//0x2A01 �����ʵ�λ
__no_init volatile unsigned char xdata     DIVHA	_at_	ESAM1_BASE+0x02; 	//0x2A02 �����ʸ�λ
__no_init volatile unsigned char xdata     DATAA	_at_	ESAM1_BASE+0x03;	//0x2A03 ���ݼĴ���
__no_init volatile unsigned char xdata     INFOA	_at_	ESAM1_BASE+0x04;	//0x2A04 ��Ϣ�Ĵ���
__no_init volatile unsigned char xdata     CFGA	    _at_	ESAM1_BASE+0x05;	//0x2A05 ���üĴ���

#define ESAM2_BASE		(__EX_PER_BASE+0xB00)	  //ESAM2
__no_init volatile unsigned char xdata     DIVLB	_at_	ESAM2_BASE+0x01;	//0x2B01 �����ʵ�λ
__no_init volatile unsigned char xdata     DIVHB	_at_	ESAM2_BASE+0x02; 	//0x2B02 �����ʸ�λ
__no_init volatile unsigned char xdata     DATAB	_at_	ESAM2_BASE+0x03;	//0x2B03 ���ݼĴ���
__no_init volatile unsigned char xdata     INFOB	_at_	ESAM2_BASE+0x04;	//0x2B04 ��Ϣ�Ĵ���
__no_init volatile unsigned char xdata     CFGB	    _at_    ESAM2_BASE+0x05;	//0x2B05 ���üĴ���

/*** �ɷ�Ƶʱ����� P9.7 ***/
#define PWM_BASE        (__EX_PER_BASE+0x89c)
__no_init volatile unsigned char xdata     PWMCLK1H _at_    PWM_BASE+0x00;      //0x289C �ߵ�ƽ����ʱ����ֽ�
__no_init volatile unsigned char xdata     PWMCLK1L _at_    PWM_BASE+0x01;      //0x289D �ߵ�ƽ����ʱ����ֽ�
__no_init volatile unsigned char xdata     PWMCLK2H _at_    PWM_BASE+0x02;      //0x289E �͵�ƽ����ʱ����ֽ�
__no_init volatile unsigned char xdata     PWMCLK2L _at_    PWM_BASE+0x03;      //0x289F �͵�ƽ����ʱ����ֽ�	

/************  GPIO  ************/
#define GPIO_BASE		(__EX_PER_BASE+0x800)	  //GPIO
#define P0_BASE			(GPIO_BASE+0xa8)	      //P1
__no_init volatile unsigned char xdata     P0OE	    _at_	P0_BASE+0x00;	    //0x28A8 P0���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P0IE	    _at_	P0_BASE+0x01;	    //0x28A9 P0����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P0OD	    _at_	P0_BASE+0x02;	    //0x28AA P0������ݼĴ���
__no_init volatile unsigned char xdata     P0ID	    _at_	P0_BASE+0x03;	    //0x28AB P0�������ݼĴ���

#define P1_BASE			(GPIO_BASE+0xac)	      //P1
__no_init volatile unsigned char xdata     P1OE	    _at_	P1_BASE+0x00;	    //0x28AC P1���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P1IE	    _at_	P1_BASE+0x01;	    //0x28AD P1����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P1OD	    _at_	P1_BASE+0x02;	    //0x28AE P1������ݼĴ���
__no_init volatile unsigned char xdata     P1ID	    _at_	P1_BASE+0x03;	    //0x28AF P1�������ݼĴ���

#define P2_BASE			(GPIO_BASE+0xb0)	      //P2
__no_init volatile unsigned char xdata     P2OE	    _at_	P2_BASE+0x00;	    //0x28B0 P2���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P2IE	    _at_	P2_BASE+0x01;	    //0x28B1 P2����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P2OD	    _at_	P2_BASE+0x02;	    //0x28B2 P2������ݼĴ���
__no_init volatile unsigned char xdata     P2ID	    _at_	P2_BASE+0x03;	    //0x28B3 P2�������ݼĴ���

#define P3_BASE			(GPIO_BASE+0xb4)	      //P3
__no_init volatile unsigned char xdata     P3OE     _at_    P3_BASE+0x00;       //0x28B4 P3���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P3IE	    _at_	P3_BASE+0x01;	    //0x28B5 P3����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P3OD	    _at_	P3_BASE+0x02;	    //0x28B6 P3������ݼĴ���
__no_init volatile unsigned char xdata     P3ID	    _at_	P3_BASE+0x03;	    //0x28B7 P3�������ݼĴ���

#define P4_BASE			(GPIO_BASE+0xb8)	      //P4
__no_init volatile unsigned char xdata     P4OE	    _at_	P4_BASE+0x00;	    //P4���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P4IE	    _at_	P4_BASE+0x01;	    //P4����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P4OD	    _at_	P4_BASE+0x02;	    //P4������ݼĴ���
__no_init volatile unsigned char xdata     P4ID	    _at_	P4_BASE+0x03;	    //P4�������ݼĴ���

#define P5_BASE			(GPIO_BASE+0xbc)	      //P5
__no_init volatile unsigned char xdata     P5OE	    _at_	P5_BASE+0x00;	    //P5���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P5IE	    _at_	P5_BASE+0x01;	    //P5����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P5OD	    _at_	P5_BASE+0x02;	    //P5������ݼĴ���
__no_init volatile unsigned char xdata     P5ID	    _at_	P5_BASE+0x03;	    //P5�������ݼĴ���

#define P6_BASE			(GPIO_BASE+0xc0)	      //P6
__no_init volatile unsigned char xdata     P6OE	    _at_	P6_BASE+0x00;	    //P6���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P6IE	    _at_	P6_BASE+0x01;	    //P6����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P6OD	    _at_	P6_BASE+0x02;	    //P6������ݼĴ���
__no_init volatile unsigned char xdata     P6ID	    _at_	P6_BASE+0x03;	    //P6�������ݼĴ���

#define P7_BASE			(GPIO_BASE+0xd5)	      //P7
__no_init volatile unsigned char xdata     P7OE	    _at_	P7_BASE+0x00;	    //P7���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P7IE	    _at_	P7_BASE+0x01;	    //P7����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P7OD	    _at_	P7_BASE+0x02;	    //P7������ݼĴ���
__no_init volatile unsigned char xdata     P7ID	    _at_	P7_BASE+0x03;	    //P7�������ݼĴ���

#define P8_BASE			(GPIO_BASE+0xd9)	      //P8
__no_init volatile unsigned char xdata     P8OE	    _at_	P8_BASE+0x00;	    //P8���ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P8IE	    _at_	P8_BASE+0x01;	    //P8����ʹ�ܼĴ���
__no_init volatile unsigned char xdata     P8OD	    _at_	P8_BASE+0x02;	    //P8������ݼĴ���
__no_init volatile unsigned char xdata     P8ID	    _at_	P8_BASE+0x03;	    //P8�������ݼĴ���

#define P9_BASE	        (0xa4)			          //P9
sfr	    P9OE      _at_  0xa4;	                  //P9���ʹ�ܼĴ���
sfr	    P9IE      _at_  0xa5;	                  //P9����ʹ�ܼĴ���
sfr	    P9OD      _at_  0xa6;		              //P9������ݼĴ���
sfr	    P9ID      _at_  0xa7;			          //P9�������ݼĴ���
sfr     P9FS      _at_  0xad;			          //P9�ڶ����ܼĴ���			

#define P10_BASE        (0xa9)				      //P10
sfr	    P10OE     _at_  0xa9;	  			      //P10���ʹ�ܼĴ���
sfr	    P10IE     _at_  0xaa;				      //P10����ʹ�ܼĴ���
sfr	    P10OD     _at_  0xab;				      //P10������ݼĴ���
sfr	    P10ID     _at_  0xac;				      //P10�������ݼĴ���
    
/******** IO  Function  ***********/
#define P1FS_BASE		(GPIO_BASE+0xc4)	      //P1�ڶ�����ѡ��
__no_init volatile unsigned char xdata     P10FS	  _at_	P1FS_BASE+0x00;	  //P1.0���� RTC���������;ADC�๦��ͨ���������
__no_init volatile unsigned char xdata     P11FS	  _at_	P1FS_BASE+0x01;	  //P1.1���� RTC��Ƶʱ�ӷ�Ƶ���;RXD1;T1;�˿��ж�2
__no_init volatile unsigned char xdata     P12FS	  _at_	P1FS_BASE+0x02;	  //P1.2���� RCʱ�����;TXD1;T2EX;�˿��ж�3
__no_init volatile unsigned char xdata     P13FS	  _at_	P1FS_BASE+0x03;   //P1.3���� CF1;RXD5;�˿��ж�0
__no_init volatile unsigned char xdata     P14FS	  _at_	P1FS_BASE+0x04;	  //P1.4���� TXD5;�˿��ж�1

#define P2FS_BASE		(GPIO_BASE+0xc9)	      //P2�ڶ�����
__no_init volatile unsigned char xdata     P20FS	  _at_	P2FS_BASE+0x00;	  //P2.0���� OSCʱ���ź����;RXD4;T2
__no_init volatile unsigned char xdata     P21FS	  _at_	P2FS_BASE+0x01;	  //P2.1���� PLLʱ���ź����;TXD4;T0
__no_init volatile unsigned char xdata     P22FS	  _at_	P2FS_BASE+0x02;	  //P2.2���� ADC CLKʱ���ź����;RXD3
__no_init volatile unsigned char xdata     P23FS	  _at_	P2FS_BASE+0x03;	  //P2.3���� TXD3
__no_init volatile unsigned char xdata     P24FS	  _at_	P2FS_BASE+0x04;	  //P2.4���� RXD2
__no_init volatile unsigned char xdata     P25FS	  _at_	P2FS_BASE+0x05;	  //P2.5���� ������/�����ز��ĵ�TXD2

/************  LCD  ************/
#define	LCD_BASE		(__EX_PER_BASE+0xC00)
__no_init volatile unsigned char xdata     LCDM0      _at_	LCD_BASE+0x00;	  //��ʾ����Ĵ��� 0x2c00 
__no_init volatile unsigned char xdata     LCDM1      _at_	LCD_BASE+0x01;	  //��ʾ����Ĵ��� 0x2c01
__no_init volatile unsigned char xdata     LCDM2      _at_	LCD_BASE+0x02;	  //��ʾ����Ĵ��� 0x2c02
__no_init volatile unsigned char xdata     LCDM3      _at_	LCD_BASE+0x03;	  //��ʾ����Ĵ��� 0x2c03
__no_init volatile unsigned char xdata     LCDM4      _at_	LCD_BASE+0x04;	  //��ʾ����Ĵ��� 0x2c04
__no_init volatile unsigned char xdata     LCDM5      _at_	LCD_BASE+0x05;	  //��ʾ����Ĵ��� 0x2c05
__no_init volatile unsigned char xdata     LCDM6      _at_	LCD_BASE+0x06;	  //��ʾ����Ĵ��� 0x2c06
__no_init volatile unsigned char xdata     LCDM7      _at_	LCD_BASE+0x07;	  //��ʾ����Ĵ��� 0x2c07
__no_init volatile unsigned char xdata     LCDM8      _at_	LCD_BASE+0x08;	  //��ʾ����Ĵ��� 0x2c08
__no_init volatile unsigned char xdata     LCDM9      _at_	LCD_BASE+0x09;	  //��ʾ����Ĵ��� 0x2c09
__no_init volatile unsigned char xdata     LCDM10     _at_	LCD_BASE+0x0a;	  //��ʾ����Ĵ��� 0x2c0a
__no_init volatile unsigned char xdata     LCDM11     _at_	LCD_BASE+0x0b;	  //��ʾ����Ĵ��� 0x2c0b
__no_init volatile unsigned char xdata     LCDM12     _at_	LCD_BASE+0x0c;	  //��ʾ����Ĵ��� 0x2c0c
__no_init volatile unsigned char xdata     LCDM13     _at_	LCD_BASE+0x0d;	  //��ʾ����Ĵ��� 0x2c0d
__no_init volatile unsigned char xdata     LCDM14     _at_	LCD_BASE+0x0e;	  //��ʾ����Ĵ��� 0x2c0e
__no_init volatile unsigned char xdata     LCDM15     _at_	LCD_BASE+0x0f;	  //��ʾ����Ĵ��� 0x2c0f
__no_init volatile unsigned char xdata     LCDM16     _at_	LCD_BASE+0x10;	  //��ʾ����Ĵ��� 0x2c10
__no_init volatile unsigned char xdata     LCDM17     _at_	LCD_BASE+0x11;	  //��ʾ����Ĵ��� 0x2c11
__no_init volatile unsigned char xdata     LCDM18     _at_	LCD_BASE+0x12;	  //��ʾ����Ĵ��� 0x2c12
__no_init volatile unsigned char xdata     LCDM19     _at_	LCD_BASE+0x13;	  //��ʾ����Ĵ��� 0x2c13
__no_init volatile unsigned char xdata     LCDM20     _at_	LCD_BASE+0x14;      //��ʾ����Ĵ��� 0x2c14
__no_init volatile unsigned char xdata     LCDM21     _at_	LCD_BASE+0x15;      //��ʾ����Ĵ��� 0x2c15
__no_init volatile unsigned char xdata     LCDM22     _at_	LCD_BASE+0x16;      //��ʾ����Ĵ��� 0x2c16
__no_init volatile unsigned char xdata     LCDM23     _at_  LCD_BASE+0x17;      //��ʾ����Ĵ��� 0x2c17
__no_init volatile unsigned char xdata     LCDM24     _at_	LCD_BASE+0x18;      //��ʾ����Ĵ��� 0x2c18
__no_init volatile unsigned char xdata     LCDM25     _at_	LCD_BASE+0x19;      //��ʾ����Ĵ��� 0x2c19
__no_init volatile unsigned char xdata     LCDM26     _at_	LCD_BASE+0x1a;      //��ʾ����Ĵ��� 0x2c1a
__no_init volatile unsigned char xdata     LCDM27     _at_	LCD_BASE+0x1b;      //��ʾ����Ĵ��� 0x2c1b
__no_init volatile unsigned char xdata     LCDM28     _at_	LCD_BASE+0x1c;      //��ʾ����Ĵ��� 0x2c1c
__no_init volatile unsigned char xdata     LCDM29     _at_	LCD_BASE+0x1d;      //��ʾ����Ĵ��� 0x2c1d
 
__no_init volatile unsigned char xdata     LCDM30     _at_	LCD_BASE+0x28;      //��ʾ����Ĵ��� 0x2c28
__no_init volatile unsigned char xdata     LCDM31     _at_	LCD_BASE+0x29;      //��ʾ����Ĵ��� 0x2c29
__no_init volatile unsigned char xdata     LCDM32     _at_	LCD_BASE+0x2a;      //��ʾ����Ĵ��� 0x2c2a
__no_init volatile unsigned char xdata     LCDM33     _at_	LCD_BASE+0x2b;      //��ʾ����Ĵ��� 0x2c2b
__no_init volatile unsigned char xdata     LCDM34     _at_	LCD_BASE+0x2c;      //��ʾ����Ĵ��� 0x2c2c
__no_init volatile unsigned char xdata     LCDM35     _at_	LCD_BASE+0x2d;      //��ʾ����Ĵ��� 0x2c2d
__no_init volatile unsigned char xdata     LCDM36     _at_	LCD_BASE+0x2e;      //��ʾ����Ĵ��� 0x2c2e
__no_init volatile unsigned char xdata     LCDM37     _at_	LCD_BASE+0x2f;      //��ʾ����Ĵ��� 0x2c2f
__no_init volatile unsigned char xdata     LCDM38     _at_	LCD_BASE+0x30;      //��ʾ����Ĵ��� 0x2c30
__no_init volatile unsigned char xdata     LCDM39     _at_  LCD_BASE+0x31;      //��ʾ����Ĵ��� 0x2c31
    
__no_init volatile unsigned char xdata     LCDCtrl    _at_	LCD_BASE+0x1e;	    //��ʾ���ƼĴ��� 
__no_init volatile unsigned char xdata     SegCtrl0   _at_	LCD_BASE+0x1f;	    //SEG���ؿ��ƼĴ���0
__no_init volatile unsigned char xdata     SegCtrl1   _at_	LCD_BASE+0x20;	    //SEG���ؿ��ƼĴ���1
__no_init volatile unsigned char xdata     SegCtrl2   _at_	LCD_BASE+0x21;	    //SEG���ؿ��ƼĴ���2
__no_init volatile unsigned char xdata     SegCtrl3   _at_	LCD_BASE+0x22;	    //SEG���ؿ��ƼĴ���3
__no_init volatile unsigned char xdata     SegCtrl4   _at_	LCD_BASE+0x23;	    //SEG���ؿ��ƼĴ���4
__no_init volatile unsigned char xdata     LCDVCtrl   _at_ 	0x285e; 		    //LCD������ѹ���ƼĴ���

/************  CTRL REGS  ************/
#define ANALOG_BASE		(__EX_PER_BASE+0x858)	  //ģ����ƼĴ���
__no_init volatile unsigned char xdata     CtrlADC0	  _at_	ANALOG_BASE+0x00;	//0x2858 ADC�������	
__no_init volatile unsigned char xdata     CtrlADC1	  _at_	ANALOG_BASE+0x01;	//0x2859 ADC����ƫ�ÿ���
__no_init volatile unsigned char xdata     CtrlADC2	  _at_	ANALOG_BASE+0x02;	//0x285a ADC����������
__no_init volatile unsigned char xdata     CtrlADC3	  _at_	ANALOG_BASE+0x03;	//0x285b ADC���Կ���
__no_init volatile unsigned char xdata     CtrlBAT	  _at_	ANALOG_BASE+0x04;	//0x285c ��طŵ�
__no_init volatile unsigned char xdata     CtrlADC4	  _at_	ANALOG_BASE+0x05;	//0x285d ADC��ѹԣ��
__no_init volatile unsigned char xdata     CtrlLCDV	  _at_	ANALOG_BASE+0x06;	//0x285e LCD��ѹ����
__no_init volatile unsigned char xdata     CtrlCry0	  _at_	ANALOG_BASE+0x07;	//0x285f ����΢��
__no_init volatile unsigned char xdata     CtrlCry1	  _at_	ANALOG_BASE+0x08;	//0x2860 ������ݵ���
__no_init volatile unsigned char xdata     CtrlCry2	  _at_	ANALOG_BASE+0x09;	//0x2861 �������
__no_init volatile unsigned char xdata     CtrlBGP	  _at_  ANALOG_BASE+0x0a;	//0x2862 BGP����
__no_init volatile unsigned char xdata     CtrlADC5	  _at_	ANALOG_BASE+0x0b;	//0x2863 Mͨ����������
__no_init volatile unsigned char xdata     CtrlADC6	  _at_	ANALOG_BASE+0x0c;	//0x2864 Mͨ�����ؿ���
__no_init volatile unsigned char xdata     CtrlM	  _at_  ANALOG_BASE+0x0d;	//0x2865 Mͨ��ȥֱ������
__no_init volatile unsigned char xdata     CtrlLDO	  _at_  ANALOG_BASE+0x0e;	//0x2866 LDO��ѹ����
__no_init volatile unsigned char xdata     CtrlCLK	  _at_  ANALOG_BASE+0x0f;	//0x2867 PLL DSP ADC ����Ƶ������
__no_init volatile unsigned char xdata     CtrlPLL	  _at_  ANALOG_BASE+0x10;	//0x2868 PLL ����
__no_init volatile unsigned char xdata     CtrlLDO33  _at_  ANALOG_BASE+0x11;	//0x2869
__no_init volatile unsigned char xdata     CtrlInfo   _at_  ANALOG_BASE+0x12;	//0x286a

/************  Expand Interrupt  ************/
#define ExInt2_BASE		(__EX_PER_BASE+0x840)
__no_init volatile unsigned char xdata     ExInt2IFG   _at_ ExInt2_BASE+0x00;	//�ж�����8�жϱ�־(����)�Ĵ���
__no_init volatile unsigned char xdata     ExInt2IN    _at_	ExInt2_BASE+0x01;	//�ж�����8��չ�ж��������ͼĴ���
__no_init volatile unsigned char xdata     ExInt2OUT   _at_ ExInt2_BASE+0x02;	//�ж�����8��չ�ж�������ͼĴ���
__no_init volatile unsigned char xdata     ExInt2IE    _at_	ExInt2_BASE+0x03;	//�ж�����8��չ�ж�ʹ�ܼĴ���
__no_init volatile unsigned char xdata     ExInt2OV    _at_	ExInt2_BASE+0x04;	//�ж�����8��չ�ж϶��мĴ���

#define ExInt3_BASE		(__EX_PER_BASE+0x848)
__no_init volatile unsigned char xdata     ExInt3IFG   _at_ ExInt3_BASE+0x00;	//�ж�����9�жϱ�־(����)�Ĵ���
__no_init volatile unsigned char xdata     ExInt3IN    _at_	ExInt3_BASE+0x01;	//�ж�����9��չ�ж��������ͼĴ���
__no_init volatile unsigned char xdata     ExInt3OUT   _at_ ExInt3_BASE+0x02;	//�ж�����9��չ�ж�������ͼĴ���
__no_init volatile unsigned char xdata     ExInt3IE    _at_	ExInt3_BASE+0x03;	//�ж�����9��չ�ж�ʹ�ܼĴ���
__no_init volatile unsigned char xdata     ExInt3OV    _at_	ExInt3_BASE+0x04;	//�ж�����9��չ�ж϶��мĴ���

#define ExInt4_BASE		(__EX_PER_BASE+0x850)
__no_init volatile unsigned char xdata     ExInt4IFG   _at_ ExInt4_BASE+0x00;	//�ж�����10�жϱ�־(����)�Ĵ���
__no_init volatile unsigned char xdata     ExInt4IN    _at_	ExInt4_BASE+0x01;	//�ж�����10��չ�ж��������ͼĴ���
__no_init volatile unsigned char xdata     ExInt4OUT   _at_ ExInt4_BASE+0x02;	//�ж�����10��չ�ж�������ͼĴ���
__no_init volatile unsigned char xdata     ExInt4IE    _at_	ExInt4_BASE+0x03;	//�ж�����10��չ�ж�ʹ�ܼĴ���
__no_init volatile unsigned char xdata     ExInt4OV    _at_	ExInt4_BASE+0x04;	//�ж�����10��չ�ж϶��мĴ���

#define ExInt5_BASE		(__EX_PER_BASE+0x8a2)
__no_init volatile unsigned char xdata     ExInt5IFG   _at_ ExInt5_BASE+0x00;	//�ж�����11�жϱ�־(����)�Ĵ���
__no_init volatile unsigned char xdata     ExInt5IN    _at_	ExInt5_BASE+0x01;	//�ж�����11��չ�ж��������ͼĴ���
__no_init volatile unsigned char xdata     ExInt5OUT   _at_ ExInt5_BASE+0x02;	//�ж�����11��չ�ж�������ͼĴ���
__no_init volatile unsigned char xdata     ExInt5IE    _at_	ExInt5_BASE+0x03;	//�ж�����11��չ�ж�ʹ�ܼĴ���
__no_init volatile unsigned char xdata     ExInt5OV    _at_	ExInt5_BASE+0x04;	//�ж�����11��չ�ж϶��мĴ���

/************  PM�������  ************/
#define BUFF0	        0x2880		//PMд����[7:0]
#define BUFF1	        0x2881		//PMд����[15:8]
#define BUFF2	        0x2882		//PMд����[23:16]
#define BUFF3	        0x2883		//PMд����[31:24]
#define INVD		    0x2884		//������дʹ�ܼĴ���		
#define ACK		        0X2885		//PM״̬�Ĵ���
//��������
#define PMCtrl1         0x2878      //PM���ƼĴ���1
#define PMCtrl2         0x2879      //PM���ƼĴ���2
#define PMCtrl3         0x287a      //PM���ƼĴ���3
#define PHCCtrl1        0x287b      //�ǲ�У�����ƼĴ���1
#define PHCCtrl2        0x287c      //�ǲ�У�����ƼĴ���2
#define PMCtrl4         0x287d      //PM���ƼĴ���4
#define CFCtrl          0x287e      //����������ƼĴ���
#define CRPST           0x287F      //��Ǳ��־�Ĵ���
#define IDET            0x2886      //�������

#define IDETTH          0x1002      //�����������ֵ�Ĵ���
//ԭʼ���μĴ���
#define DATAOIU         0x1005      //˲ʱ��ѹԭʼֵ
#define DATAOII1        0x100A      //ͨ��I1˲ʱ����ԭʼֵ
#define DATAOII2        0x100F      //ͨ��I2˲ʱ����ԭʼֵ
#define DATAIAU         0x1051      //˲ʱ��ѹ����ֵ
#define DATAIAI1        0x1052      //ͨ��I1˲ʱ��������ֵ
#define DATAIAI2        0x1053      //ͨ��I2˲ʱ��������ֵ
#define DATAIDU         0x103A      //˲ʱ��ѹֱ��ֵ
#define DATAIDI1        0x1041      //ͨ��I1˲ʱ����ֱ��ֵ
#define DATAIDI2        0x1048      //ͨ��I2˲ʱ����ֱ��ֵ


//����/�������ݼĴ���
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

//����/��Чֵ�Ȳ�Ĵ���
#define SCP             0x10e8
#define SCQ             0x10e9
#define SCU             0x10ea
#define SCI1            0x10eb
#define SCI2            0x10ec
#define PARAPC          0x10ed
#define PARAQC          0x10ee
#define PARABPF         0x10ef
//�����ۼӼĴ���/�������������
#define PPCNT           0x10f0
#define NPCNT           0x10f1
#define PPCFCNT         0x10f2
#define NPCFCNT         0x10f3
#define PQCNT           0x10f6
#define NQCNT           0x10f7
#define PQCFCNT         0x10f8
#define NQCFCNT         0x10f9
//����ֵ�Ĵ���/��������ֵ�Ĵ���
#define GATEP           0x10f4
#define GATECP          0x10f5
#define GATEQ           0x10fa
#define GATECQ          0x10fb
#define DATACP          0x10fc
//Ƶ��ֵ�Ĵ���
#define DATAFREQ        0x10fd
//Mͨ�����ݼĴ���
#define DATAOM          0x10ce
#define DATADM          0x10cf
#define DATAADM         0x10d0

/************  WDT  ************/
sfr WDTEN      _at_  0xce;	                        //WDTʹ�ܣ���Կ0xa5
sfr WDTCLR     _at_  0xcf;	                        //WDT�������Կ0x5a

/************  SYSTEM CTRL  ************/
__no_init volatile unsigned char xdata     PRCtrl0  _at_       0x2d00;           //���迪�ؿ���0
__no_init volatile unsigned char xdata     PRCtrl1  _at_       0x2d01;           //���迪�ؿ���0
__no_init volatile unsigned char xdata     VERSION  _at_       0x286b;           //ģ���·�汾��OSC״̬��� 

sfr CBANK       _at_  0xa0;                             //�����ѡ��Ĵ���
sfr Systate	    _at_  0xa1;                             //ϵͳ״̬
sfr WAKE_CTRL	_at_  0xc9;                             //���߻��ѿ���
sfr IOWK_STATE  _at_  0xaf;                             //IO���߻���״̬
sfr IOWK_CTRL	_at_  0xc7;                             //IO���ѱ��ؿ���  

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
sfr RTCSC 	_at_ 0x9a;			//��
sfr RTCMiC 	_at_ 0x9b;			//��
sfr RTCHC 	_at_ 0x9c;		 	//ʱ
sfr RTCDC 	_at_ 0x9d;			//��
sfr RTCWC 	_at_ 0x9e;			//��
sfr RTCMoC 	_at_ 0x9f;			//��
sfr RTCYC 	_at_ 0x93;			//��
sfr RTCCH   _at_ 0x94;			//У���Ĵ���[15:8;
sfr RTCCL 	_at_ 0x95;			//У���Ĵ���[7:0;
sfr INTRTC 	_at_ 0x96;			//ϵͳ���߻��Ѽ���Ĵ���
sfr RTCPWD 	_at_ 0x97;			//����Ĵ���
sfr RTCPEN  _at_ 0x90;			//����ʹ�ܼĴ���
sfr RDRTC   _at_ 0xda;			//���ݶ�ȡ�Ĵ���
sfr DIVTHH 	_at_ 0xdb;		   	//��Ƶ��Ƶ����ֵ�߼Ĵ���[23:16;
sfr DIVTHM 	_at_ 0xdc;			//��Ƶ��Ƶ����ֵ�߼Ĵ���[15:8;
sfr DIVTHL	_at_ 0xdd;			//��Ƶ��Ƶ����ֵ�߼Ĵ���[7:0;
sfr PLLCNT 	_at_ 0xde;	 		//��Ƶ����״̬�Ĵ���
sfr SECINT  _at_ 0xdf;			//�����߻��Ѽ����չ�Ĵ���

#ifdef __cplusplus
}
#endif//__cplusplus

#endif

