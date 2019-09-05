/********************  C) COPYRIGHT 2011 Vangotech ********************
* File Name          : ADC.C
* Author             : LIM
* Version            : V0.1
* Date               : 2/15/2011
* Description        : register define
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, VANGOTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifndef _LEOPARTREG_H_
#define _LEOPARTREG_H_
#include "dw8051.h"


#define xdata __xdata  
#define _at_ @

#define XBYTE       ((unsigned char volatile xdata *) 0)

/*******************************************
            sys ctrl registers
*******************************************/
__sfr __no_init volatile unsigned char Systate @0xa1;
__sfr __no_init volatile unsigned char version @0xa2;
__sfr __no_init volatile unsigned char wdt0    @0xce;   // 0xa5
__sfr __no_init volatile unsigned char wdt1    @0xcf;   // 0x5a



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

#define MCUFRQ SysCtrl_bit.MCUFRQ
#define SLEEP0 SysCtrl_bit.SLEEP0
#define SLEEP1 SysCtrl_bit.SLEEP1
#define LCDG SysCtrl_bit.LCDG
#define PMG SysCtrl_bit.PMG
#define FSC SysCtrl_bit.FSC
#define FWC SysCtrl_bit.FWC
#define MEAFRQ SysCtrl_bit.MEAFRQ


__sfr __no_init volatile unsigned char PLLLCK @0xa3;
__sfr __no_init volatile unsigned char CBANK  @0xa0;
__sfr __no_init volatile unsigned char SPCFNC @0X8F;
/**************************************
FAST IO register
****************************************/

__sfr __no_init volatile unsigned char P9OE @0xa4;
__sfr __no_init volatile unsigned char P9IE @0xa5;
__sfr __no_init volatile unsigned char P9OD @0xa6;
__sfr __no_init volatile unsigned char P9ID @0xa7;
__sfr __no_init volatile unsigned char P9FC @0xad;

__sfr __no_init volatile unsigned char P10OE @0xa9;
__sfr __no_init volatile unsigned char P10IE @0xaa;
__sfr __no_init volatile unsigned char P10OD @0xab;
__sfr __no_init volatile unsigned char P10ID @0xac;
__sfr __no_init volatile unsigned char P10FC @0xae;

/******************************************
RTC register
*******************************************/
__sfr __no_init volatile unsigned char RTCPEN @0x90;    // 0x96
__sfr __no_init volatile unsigned char RTCPWD @0x97;    // 0x57, 0xd7
__sfr __no_init volatile unsigned char INTRTC @0x96;
__sfr __no_init volatile unsigned char RTCCH  @0x94;
__sfr __no_init volatile unsigned char RTCCL  @0x95;
__sfr __no_init volatile unsigned char RTCLATCH @0xDA;
__sfr __no_init volatile unsigned char DIVTHH @0xDB;
__sfr __no_init volatile unsigned char DIVTHM @0xDC;
__sfr __no_init volatile unsigned char DIVTHL @0xDD;
__sfr __no_init volatile unsigned char RTCCNT @0xDE;
__sfr __no_init volatile unsigned char RTCSC  @0x9a;
__sfr __no_init volatile unsigned char RTCMiC @0x9b;
__sfr __no_init volatile unsigned char RTCHC  @0x9c;
__sfr __no_init volatile unsigned char RTCDC  @0x9d;
__sfr __no_init volatile unsigned char RTCWC  @0x9E;
__sfr __no_init volatile unsigned char RTCMoC @0x9f;
__sfr __no_init volatile unsigned char RTCYC  @0x93; 


    
/**************************************************
			Analog Interface regist
**************************************************/
__no_init  volatile unsigned char xdata  CtrlADC0 _at_  0x2858;     //ADC �������  
__no_init  volatile unsigned char xdata  CtrlADC1 _at_  0x2859;     //ADC ����ƫ�ÿ���
__no_init  volatile unsigned char xdata  CtrlADC2 _at_  0x285a;     //ADC���������ƼĴ���
__no_init  volatile unsigned char xdata  CtrlADC3 _at_  0x285b;     //ADC ���ԼĴ���

__no_init  volatile unsigned char xdata  CtrlADC4 _at_  0x285d;     //

__no_init  volatile unsigned char xdata  CtrlCry0 _at_  0x285F;     //����΢��
__no_init  volatile unsigned char xdata  CtrlCry1 _at_  0x2860;     //������ݵ���
__no_init  volatile unsigned char xdata  CtrlCry2 _at_  0x2861;     //�������
__no_init  volatile unsigned char xdata  CtrlBGP  _at_  0X2862;     //BGP REF���������Ĵ���
__no_init  volatile unsigned char xdata  CtrlADC5 _at_  0x2863;     //Mͨ����������
__no_init  volatile unsigned char xdata  CtrlADC6 _at_  0x2864;     //ADC ͨ�����ؼĴ���
__no_init  volatile unsigned char xdata  CtrlM    _at_  0x2865;     //Mͨ�����ƼĴ���
__no_init  volatile unsigned char xdata  CtrlLDO  _at_  0X2866;
__no_init  volatile unsigned char xdata  CtrlCLK  _at_  0x2867;     //PLL DSP ADC ����Ƶ������
__no_init  volatile unsigned char xdata  CtrlPLL  _at_  0x2868;     //PLL ����
__no_init  volatile unsigned char xdata  XRAMPWD  _at_  0x28a0;


/********************************************
    interrupt control regist
********************************************/

/* External interrupt 2 */
__no_init  volatile unsigned char xdata  ExInt2IFG  _at_ 0x2840;//�ж�����8�жϱ�־�����󣩼Ĵ��� 0x2840
__no_init  volatile unsigned char xdata  ExInt2IN   _at_ 0x2841;//�ж�����8��չ�ж��������ͼĴ��� 0x2841
__no_init  volatile unsigned char xdata  ExInt2OUT  _at_ 0x2842;//�ж�����8��չ�ж�������ͼĴ��� 0x2842
__no_init  volatile unsigned char xdata  ExInt2IE   _at_ 0x2843;//�ж�����8��չ�ж�ʹ�ܼĴ��� 0x2843
__no_init  volatile unsigned char xdata  ExInt2OV   _at_ 0x2844;//�ж�����8��չ�ж϶��мĴ��� 0x2844
/* External interrupt 3 */
__no_init  volatile unsigned char xdata  ExInt3IFG  _at_ 0x2848;//�ж�����9�жϱ�־�����󣩼Ĵ��� 0x2848
__no_init  volatile unsigned char xdata  ExInt3IN   _at_ 0x2849;//�ж�����9��չ�ж��������ͼĴ��� 0x2849
__no_init  volatile unsigned char xdata  ExInt3OUT  _at_ 0x284a;//�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284a
__no_init  volatile unsigned char xdata  ExInt3IE   _at_ 0x284b;//�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284b
__no_init  volatile unsigned char xdata  ExInt3OV   _at_ 0x284c;//�ж�����9��չ�ж϶��мĴ��� 0x284c
/* External interrupt 4 */
__no_init  volatile unsigned char xdata  ExInt4IFG  _at_ 0x2850;//�ж�����10�жϱ�־�����󣩼Ĵ��� 0x2850
__no_init  volatile unsigned char xdata  ExInt4IN   _at_ 0x2851;//�ж�����10��չ�ж��������ͼĴ��� 0x2851
__no_init  volatile unsigned char xdata  ExInt4OUT  _at_ 0x2852;//�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2852
__no_init  volatile unsigned char xdata  ExInt4IE   _at_ 0x2853;//�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2853
__no_init  volatile unsigned char xdata  ExInt4OV   _at_ 0x2854;//�ж�����10��չ�ж϶��мĴ��� 0x2854

/*******************************************
                LCD Reg
*******************************************/
__no_init  volatile unsigned char xdata  LCDM0      _at_ 0x2C00;//��ʾ����Ĵ��� 0x2800 
__no_init  volatile unsigned char xdata  LCDM1      _at_ 0x2C01;//��ʾ����Ĵ��� 0x2801
__no_init  volatile unsigned char xdata  LCDM2      _at_ 0x2C02;//��ʾ����Ĵ��� 0x2802
__no_init  volatile unsigned char xdata  LCDM3      _at_ 0x2C03;//��ʾ����Ĵ��� 0x2803
__no_init  volatile unsigned char xdata  LCDM4      _at_ 0x2C04;//��ʾ����Ĵ��� 0x2804
__no_init  volatile unsigned char xdata  LCDM5      _at_ 0x2C05;//��ʾ����Ĵ��� 0x2805
__no_init  volatile unsigned char xdata  LCDM6      _at_ 0x2C06;//��ʾ����Ĵ��� 0x2806
__no_init  volatile unsigned char xdata  LCDM7      _at_ 0x2C07;//��ʾ����Ĵ��� 0x2807
__no_init  volatile unsigned char xdata  LCDM8      _at_ 0x2C08;//��ʾ����Ĵ��� 0x2808
__no_init  volatile unsigned char xdata  LCDM9      _at_ 0x2C09;//��ʾ����Ĵ��� 0x2809
__no_init  volatile unsigned char xdata  LCDM10     _at_ 0x2C0a;//��ʾ����Ĵ��� 0x280a
__no_init  volatile unsigned char xdata  LCDM11     _at_ 0x2C0b;//��ʾ����Ĵ��� 0x280b
__no_init  volatile unsigned char xdata  LCDM12     _at_ 0x2C0c;//��ʾ����Ĵ��� 0x280c
__no_init  volatile unsigned char xdata  LCDM13     _at_ 0x2C0d;//��ʾ����Ĵ��� 0x280d
__no_init  volatile unsigned char xdata  LCDM14     _at_ 0x2C0e;//��ʾ����Ĵ��� 0x280e
__no_init  volatile unsigned char xdata  LCDM15     _at_ 0x2C0f;//��ʾ����Ĵ��� 0x280f
__no_init  volatile unsigned char xdata  LCDM16     _at_ 0x2C10;//��ʾ����Ĵ��� 0x2810
__no_init  volatile unsigned char xdata  LCDM17     _at_ 0x2C11;//��ʾ����Ĵ��� 0x2811
__no_init  volatile unsigned char xdata  LCDM18     _at_ 0x2C12;//��ʾ����Ĵ��� 0x2812
__no_init  volatile unsigned char xdata  LCDM19     _at_ 0x2C13;//��ʾ����Ĵ��� 0x2813
__no_init  volatile unsigned char xdata  LCDM20     _at_ 0X2C14;
__no_init  volatile unsigned char xdata  LCDM21     _at_ 0X2C15;
__no_init  volatile unsigned char xdata  LCDM22     _at_ 0X2C16;
__no_init  volatile unsigned char xdata  LCDM23     _at_ 0X2C17;
__no_init  volatile unsigned char xdata  LCDM24     _at_ 0X2C18;
__no_init  volatile unsigned char xdata  LCDM26     _at_ 0X2C19;
__no_init  volatile unsigned char xdata  LCDM27     _at_ 0X2C1a;
__no_init  volatile unsigned char xdata  LCDM28     _at_ 0X2C1b;
__no_init  volatile unsigned char xdata  LCDM29     _at_ 0X2C1c;
__no_init  volatile unsigned char xdata  LCDM30     _at_ 0X2C1d;

__no_init  volatile unsigned char xdata  CtrlLCDV   _at_ 0x285e;//LCD��ѹ������

__no_init  volatile unsigned char xdata  LCDCtrl    _at_ 0x2c1E;// ��ʾ���ƼĴ��� 0x2814
__no_init  volatile unsigned char xdata  SegCtrl0   _at_ 0x2c1F;// ��ʾ���ƼĴ���2 0x2815
__no_init  volatile unsigned char xdata  SegCtrl1   _at_ 0x2c20;// ��ʾ���ƼĴ���3 0x2816
__no_init  volatile unsigned char xdata  SegCtrl2   _at_ 0x2c21;// ��ʾ���ƼĴ���4 0x2817
__no_init  volatile unsigned char xdata  SegCtrl3   _at_ 0x2c22;// ��ʾ���ƼĴ���5 0x2818
__no_init  volatile unsigned char xdata  SegCtrl4   _at_ 0x2c23;// ��ʾ���ƼĴ���6 0x2819
__no_init  volatile unsigned char xdata  LCDVCtrl   _at_ 0x2c5e; //LCD������ѹ���ƼĴ���

/*********************************************
			timer & uart regist
*********************************************/

/* extern uart2 & extern timer2-0 */
__no_init  volatile unsigned char xdata  TCON2      _at_ 0x2820;//timer2����/״̬�Ĵ��� 0x2820
__no_init  volatile unsigned char xdata  TMOD2      _at_ 0x2821;//timer2 TMOD 0x2821
__no_init  volatile unsigned char xdata  TH20       _at_ 0x2822;//UART2 TH0 0x2822
__no_init  volatile unsigned char xdata  TH21       _at_ 0x2823;//UART2 TH1 0x2823
__no_init  volatile unsigned char xdata  TL20       _at_ 0x2824;//UART2 TL0 0x2824
__no_init  volatile unsigned char xdata  TL21       _at_ 0x2825;//UART2 TL1 0x2825
__no_init  volatile unsigned char xdata  SCON2      _at_ 0x2826;//UART2 ���пڿ��ƼĴ���SCON 0x2826
__no_init  volatile unsigned char xdata  SBUF2      _at_ 0x2827;//UART2 ���пڻ���Ĵ���SBUF 0x2827
__no_init  volatile unsigned char xdata  CARRHH     _at_ 0X2898; //�ز������Ĵ���1��λ�ֽ�
__no_init  volatile unsigned char xdata  CARRHL     _at_ 0X2899; //�ز������Ĵ���1��λ�ֽ�
__no_init  volatile unsigned char xdata  CARRLH     _at_ 0x289a; //
__no_init  volatile unsigned char xdata  CARRLL     _at_ 0X289B;
/* extern uart3 & extern timer3-0 */
__no_init  volatile unsigned char xdata  TCON3      _at_ 0x2828;//timer3����/״̬�Ĵ��� 0x2828
__no_init  volatile unsigned char xdata  TMOD3      _at_ 0x2829;//timer3 TMOD 0x2829
__no_init  volatile unsigned char xdata  TH30       _at_ 0x282a;//UART3 TH0 0x282a
__no_init  volatile unsigned char xdata  TH31       _at_ 0x282b;//UART3 TH1 0x282b
__no_init  volatile unsigned char xdata  TL30       _at_ 0x282c;//UART3 TL0 0x282c
__no_init  volatile unsigned char xdata  TL31       _at_ 0x282d;//UART3 TL1 0x282d
__no_init  volatile unsigned char xdata  SCON3      _at_ 0x282e;//UART3 ���пڿ��ƼĴ���SCON 0x282e
__no_init  volatile unsigned char xdata  SBUF3      _at_ 0x282f;//UART3 ���пڻ���Ĵ���SBUF 0x282f
/* extern uart4 & extern timer4-0 */
__no_init  volatile unsigned char xdata  TCON4      _at_ 0x2830;//timer4����/״̬�Ĵ��� 0x2830
__no_init  volatile unsigned char xdata  TMOD4      _at_ 0x2831;//timer4 TMOD 0x2831
__no_init  volatile unsigned char xdata  TH40       _at_ 0x2832;//UART4 TH0 0x2832
__no_init  volatile unsigned char xdata  TH41       _at_ 0x2833;//UART4 TH1 0x2833
__no_init  volatile unsigned char xdata  TL40       _at_ 0x2834;//UART4 TL0 0x2834
__no_init  volatile unsigned char xdata  TL41       _at_ 0x2835;//UART4 TL1 0x2835
__no_init  volatile unsigned char xdata  SCON4      _at_ 0x2836;//UART4 ���пڿ��ƼĴ���SCON 0x2836
__no_init  volatile unsigned char xdata  SBUF4      _at_ 0x2837;//UART4 ���пڻ���Ĵ���SBUF 0x2837
/* extern uart5 & extern timer5-0 */
__no_init  volatile unsigned char xdata  TCON5      _at_ 0x2838;//timer5����/״̬�Ĵ��� 0x2838
__no_init  volatile unsigned char xdata  TMOD5      _at_ 0x2839;//timer5 TMOD 0x2839
__no_init  volatile unsigned char xdata  TH50       _at_ 0x283a;//UART5 TH0 0x283a
__no_init  volatile unsigned char xdata  TH51       _at_ 0x283b;//UART5 TH1 0x283b
__no_init  volatile unsigned char xdata  TL50       _at_ 0x283c;//UART5 TL0 0x283c
__no_init  volatile unsigned char xdata  TL51       _at_ 0x283d;//UART5 TL1 0x283d
__no_init  volatile unsigned char xdata  SCON5      _at_ 0x283e;//UART5 ���пڿ��ƼĴ���SCON 0x283e
__no_init  volatile unsigned char xdata  SBUF5      _at_ 0x283f;//UART5 ���пڻ���Ĵ���SBUF 0x283f



/****************************************** 
			gpio regist 
******************************************/

/* port0_4_bits */
__no_init  volatile unsigned char xdata  P0OE       _at_ 0x28a8;//P0���ʹ�ܼĴ��� 0x28a8
__no_init  volatile unsigned char xdata  P0IE       _at_ 0x28a9;//P0����ʹ�ܼĴ��� 0x28a9
__no_init  volatile unsigned char xdata  P0OD       _at_ 0x28aa;//P0������ݼĴ��� 0x28aa
__no_init  volatile unsigned char xdata  P0ID       _at_ 0x28ab;//P0�������ݼĴ��� 0x28ab
/* port1_5_bits */
__no_init  volatile unsigned char xdata  P1OE       _at_ 0x28ac;//P1���ʹ�ܼĴ��� 0x28ac
__no_init  volatile unsigned char xdata  P1IE       _at_ 0x28ad;//P1����ʹ�ܼĴ��� 0x28ad
__no_init  volatile unsigned char xdata  P1OD       _at_ 0x28ae;//P1������ݼĴ��� 0x28ae
__no_init  volatile unsigned char xdata  P1ID       _at_ 0x28af;//P1�������ݼĴ��� 0x28af
/* port2_6_bits */
__no_init  volatile unsigned char xdata  P2OE       _at_ 0x28b0;//P2���ʹ�ܼĴ��� 0x28b0
__no_init  volatile unsigned char xdata  P2IE       _at_ 0x28b1;//P2����ʹ�ܼĴ��� 0x28b1
__no_init  volatile unsigned char xdata  P2OD       _at_ 0x28b2;//P2������ݼĴ��� 0x28b2
__no_init  volatile unsigned char xdata  P2ID       _at_ 0x28b3;//P2�������ݼĴ��� 0x28b3
/* port3_4_bits */
__no_init  volatile unsigned char xdata  P3OE       _at_ 0x28b4;//P3���ʹ�ܼĴ��� 0x28b4
__no_init  volatile unsigned char xdata  P3IE       _at_ 0x28b5;//P3����ʹ�ܼĴ��� 0x28b5
__no_init  volatile unsigned char xdata  P3OD       _at_ 0x28b6;//P3������ݼĴ��� 0x28b6
__no_init  volatile unsigned char xdata  P3ID       _at_ 0x28b7;//P3�������ݼĴ��� 0x28b7
/* port4_8_bits */
__no_init  volatile unsigned char xdata  P4OE       _at_ 0x28b8;//P4���ʹ�ܼĴ��� 0x28b8
__no_init  volatile unsigned char xdata  P4IE       _at_ 0x28b9;//P4����ʹ�ܼĴ��� 0x28b9
__no_init  volatile unsigned char xdata  P4OD       _at_ 0x28ba;//P4������ݼĴ��� 0x28ba
__no_init  volatile unsigned char xdata  P4ID       _at_ 0x28bb;//P4�������ݼĴ��� 0x28bb
/* port5_8_bits */
__no_init  volatile unsigned char xdata  P5OE       _at_ 0x28bc;//P5���ʹ�ܼĴ��� 0x28bc
__no_init  volatile unsigned char xdata  P5IE       _at_ 0x28bd;//P5����ʹ�ܼĴ��� 0x28bd
__no_init  volatile unsigned char xdata  P5OD       _at_ 0x28be;//P5������ݼĴ��� 0x28be
__no_init  volatile unsigned char xdata  P5ID       _at_ 0x28bf;//P5�������ݼĴ��� 0x28bf
/* port6_8_bits */
__no_init  volatile unsigned char xdata  P6OE       _at_ 0x28c0;//P6���ʹ�ܼĴ��� 0x28c0
__no_init  volatile unsigned char xdata  P6IE       _at_ 0x28c1;//P6����ʹ�ܼĴ��� 0x28c1
__no_init  volatile unsigned char xdata  P6OD       _at_ 0x28c2;//P6������ݼĴ��� 0x28c2
__no_init  volatile unsigned char xdata  P6ID       _at_ 0x28c3;//P6�������ݼĴ��� 0x28c3
/* special function select regist */
__no_init  volatile unsigned char xdata  P10FS      _at_ 0x28c4;//P1.0����ѡ��Ĵ��� 0x28c4
__no_init  volatile unsigned char xdata  P11FS      _at_ 0x28c5;//P1.1����ѡ��Ĵ��� 0x28c5
__no_init  volatile unsigned char xdata  P12FS      _at_ 0x28c6;//P1.2����ѡ��Ĵ��� 0x28c6
__no_init  volatile unsigned char xdata  P13FS      _at_ 0x28c7;//P1.3����ѡ��Ĵ��� 0x28c7
__no_init  volatile unsigned char xdata  P14FS      _at_ 0x28c8;//P1.4����ѡ��Ĵ��� 0x28c8
__no_init  volatile unsigned char xdata  P20FS      _at_ 0x28c9;//P2.0����ѡ��Ĵ��� 0x28c9
__no_init  volatile unsigned char xdata  P21FS      _at_ 0x28ca;//P2.1����ѡ��Ĵ��� 0x28ca
__no_init  volatile unsigned char xdata  P22FS      _at_ 0x28cb;//P2.2����ѡ��Ĵ��� 0x28cb
__no_init  volatile unsigned char xdata  P23FS      _at_ 0x28cc;//P2.3����ѡ��Ĵ��� 0x28cc
__no_init  volatile unsigned char xdata  P24FS      _at_ 0x28cd;//P2.4����ѡ��Ĵ��� 0x28cd
__no_init  volatile unsigned char xdata  P25FS      _at_ 0x28ce;//P2.5����ѡ��Ĵ��� 0x28ce
__no_init  volatile unsigned char xdata  Txd2FS     _at_ 0x28cf;//TXD2����ѡ��Ĵ��� 0x28cf

__no_init  volatile unsigned char xdata  P7OE       _at_ 0x28d5;//P7���ʹ�ܼĴ��� 0x28d5
__no_init  volatile unsigned char xdata  P7IE       _at_ 0x28d6;//P7����ʹ�ܼĴ��� 0x28d6
__no_init  volatile unsigned char xdata  P7OD       _at_ 0x28d7;//P7������ݼĴ��� 0x28d7
__no_init  volatile unsigned char xdata  P7ID       _at_ 0x28d8;//P7�������ݼĴ��� 0x28d8

__no_init  volatile unsigned char xdata  P8OE       _at_ 0x28d9;//P8���ʹ�ܼĴ��� 0x28d9
__no_init  volatile unsigned char xdata  P8IE       _at_ 0x28da;//P8����ʹ�ܼĴ��� 0x28da
__no_init  volatile unsigned char xdata  P8OD       _at_ 0x28db;//P8������ݼĴ��� 0x28db 
__no_init  volatile unsigned char xdata  P8ID       _at_ 0x28dc;//P8�������ݼĴ��� 0x28dc

/**�ɷ�Ƶʱ����� P9.7*/
__no_init  volatile unsigned char xdata  PWMCLK1H   _at_ 0x289c; //�ߵ�ƽ����ʱ����ֽ�
__no_init  volatile unsigned char xdata  PWMCLK1L   _at_ 0x289d;//�ߵ�ƽ����ʱ����ֽ�
__no_init  volatile unsigned char xdata  PWMCLK2H   _at_ 0X289E;//�͵�ƽ����ʱ����ֽ�
__no_init  volatile unsigned char xdata  PWMCLK2L   _at_ 0X289F;//�͵�ƽ����ʱ����ֽ�

/**ESAM */
__no_init  volatile unsigned char xdata  DIVLA      _at_ 0X2A01; //ESAM1 ��Ƶ��λ
__no_init  volatile unsigned char xdata  DIVHA      _at_ 0X2A02; //ESAM1 ��Ƶ��λ
__no_init  volatile unsigned char xdata  DATAA      _at_ 0X2A03; //esam1 ����
__no_init  volatile unsigned char xdata  INFOA      _at_ 0x2a04;  //ESAM1 ��Ϣ�Ĵ���
__no_init  volatile unsigned char xdata  CFGA       _at_ 0X2a05; //ESAM1 ���üĴ���
__no_init  volatile unsigned char xdata  DIVLB      _at_ 0X2b01; //ESAM2 ��Ƶ��λ
__no_init  volatile unsigned char xdata  DIVHB      _at_ 0X2b02; //ESAM2 ��Ƶ��λ
__no_init  volatile unsigned char xdata  DATAB      _at_ 0X2b03; //esam2 ����
__no_init  volatile unsigned char xdata  INFOB      _at_ 0x2b04;  //ESAM2 ��Ϣ�Ĵ���
__no_init  volatile unsigned char xdata  CFGB       _at_ 0X2b05; //ESAM2 ���üĴ���

/**************************************************
			PM ctrl
**************************************************/

#define PMCtrl1     0x2878  // PM���ƼĴ���1  0x2878;
#define PMCtrl2     0x2879  // PM���ƼĴ���2  0x2879;
#define PMCtrl3     0x287a  // PM���ƼĴ���3  0x287a;
#define PHCCtrl1    0x287b  // �ǲ�У�����ƼĴ���1  0x287b;
#define PHCCtrl2    0x287c  // �ǲ�У�����ƼĴ���2  0x287c;
#define PMCtrl4     0x287d  // PM���ƼĴ���4  0x287d;
#define CFCtrl      0x287e  // ����������ƼĴ���  0x287e;
#define CRPST       0x287F  // ��Ǳ��־�Ĵ��� 0x287f;

/*=================================================
 V9801 PM ������صļĴ���
===================================================*/
//��д����Ĵ���
#define ACK        0x2885  
#define INVD       0x2884
#define BUFF3      0x2883
#define BUFF2      0x2882
#define BUFF1      0x2881
#define BUFF0      0x2880


//ԭʼ���μĴ���
#define DATAOIU     0x1005      //˲ʱ��ѹԭʼֵ
#define DATAOII1    0x100A      //ͨ��I1˲ʱ����ԭʼֵ
#define DATAOII2    0x100F      //ͨ��I2˲ʱ����ԭʼֵ
#define DATAIAU     0x1051      //˲ʱ��ѹ����ֵ
#define DATAIAI1    0x1052      //ͨ��I1˲ʱ����ֵ
#define DATAIAI2    0x1053      //ͨ��I2˲ʱ��������ֵ
#define DATAIDU     0x103A      //˲ʱ��ѹֱ��ֵ
#define DATAIDI1    0x1041      //ͨ��I1˲ʱ����ֱ��ֵ
#define DATAIDI2    0x1048      //ͨ��I2˲ʱ����ֱ��ֵ


//����/�������ݼĴ���
#define DATAIP      0x10d1
#define DATAIQ      0X10D2
#define RMSIU       0x10d3
#define RMSII1      0x10D4
#define RMSII2      0x10d5
#define DATAP       0X10D6
#define DATAQ       0x10d7
#define RMSU        0x10D8
#define RMSI1       0x10d9
#define RMSI2       0x10da
#define DATAAP1     0x10db
#define DATAAP2     0x10dc


//����/��Чֵ�Ȳ�Ĵ���

#define SCP         0x10e8
#define SCQ         0x10e9
#define SCU         0x10ea
#define SCI1        0x10eb
#define SCI2        0x10ec
#define PARAPC      0x10ed
#define PARAQC      0x10ee
#define PARABPF     0x10ef

#define PPCNT       0x10f0
#define PPCFCNT     0x10f2
#define GATEP       0x10f4
#define GATECP      0x10f5
#define GATEQ       0x10fa
#define GATECQ      0x10fb
#define DATACP      0x10fc


#define DATAFREQ    0x10fd


#define DATAOM      0x10ce
#define DATADM      0x10cf
#define DATAADM     0x10d0



#endif

