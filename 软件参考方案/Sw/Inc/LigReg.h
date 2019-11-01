#ifndef _EXLIGREG_H_
#define _EXLIGREG_H_
#include "dw8051.h"


#define xdata   __xdata  
#define _at_    @

#define XBYTE   ((unsigned char volatile xdata *) 0)

 
/*================================================== 
				LCD Reg
===================================================*/
__no_init  volatile unsigned char xdata   LCDM0     _at_    0x2800;     //��ʾ����Ĵ��� 0x2800 
__no_init  volatile unsigned char xdata   LCDM1     _at_    0x2801;     //��ʾ����Ĵ��� 0x2801
__no_init  volatile unsigned char xdata   LCDM2     _at_    0x2802;     //��ʾ����Ĵ��� 0x2802
__no_init  volatile unsigned char xdata   LCDM3     _at_    0x2803;     //��ʾ����Ĵ��� 0x2803
__no_init  volatile unsigned char xdata   LCDM4     _at_    0x2804;     //��ʾ����Ĵ��� 0x2804
__no_init  volatile unsigned char xdata   LCDM5     _at_    0x2805;     //��ʾ����Ĵ��� 0x2805
__no_init  volatile unsigned char xdata   LCDM6     _at_    0x2806;     //��ʾ����Ĵ��� 0x2806
__no_init  volatile unsigned char xdata   LCDM7     _at_    0x2807;     //��ʾ����Ĵ��� 0x2807
__no_init  volatile unsigned char xdata   LCDM8     _at_    0x2808;     //��ʾ����Ĵ��� 0x2808
__no_init  volatile unsigned char xdata   LCDM9     _at_    0x2809;     //��ʾ����Ĵ��� 0x2809
__no_init  volatile unsigned char xdata   LCDM10    _at_    0x280a;     //��ʾ����Ĵ��� 0x280a
__no_init  volatile unsigned char xdata   LCDM11    _at_    0x280b;     //��ʾ����Ĵ��� 0x280b
__no_init  volatile unsigned char xdata   LCDM12    _at_    0x280c;     //��ʾ����Ĵ��� 0x280c
__no_init  volatile unsigned char xdata   LCDM13    _at_    0x280d;     //��ʾ����Ĵ��� 0x280d
__no_init  volatile unsigned char xdata   LCDM14    _at_    0x280e;     //��ʾ����Ĵ��� 0x280e
__no_init  volatile unsigned char xdata   LCDM15    _at_    0x280f;     //��ʾ����Ĵ��� 0x280f
__no_init  volatile unsigned char xdata   LCDM16    _at_    0x2810;     //��ʾ����Ĵ��� 0x2810
__no_init  volatile unsigned char xdata   LCDM17    _at_    0x2811;     //��ʾ����Ĵ��� 0x2811
__no_init  volatile unsigned char xdata   LCDM18    _at_    0x2812;     //��ʾ����Ĵ��� 0x2812
__no_init  volatile unsigned char xdata   LCDM19    _at_    0x2813;     //��ʾ����Ĵ��� 0x2813
__no_init  volatile unsigned char xdata   LCDCtrl   _at_    0x2814;     // ��ʾ���ƼĴ��� 0x2814
__no_init  volatile unsigned char xdata   SegCtrl0  _at_    0x2815;     // ��ʾ���ƼĴ���2 0x2815
__no_init  volatile unsigned char xdata   SegCtrl1  _at_    0x2816;     // ��ʾ���ƼĴ���3 0x2816
__no_init  volatile unsigned char xdata   SegCtrl2  _at_    0x2817;     // ��ʾ���ƼĴ���4 0x2817
__no_init  volatile unsigned char xdata   SegCtrl3  _at_    0x2818;     // ��ʾ���ƼĴ���5 0x2818
__no_init  volatile unsigned char xdata   SegCtrl4  _at_    0x2819;     // ��ʾ���ƼĴ���6 0x2819

/*================================================
			timer & uart regist
================================================*/

/* extern uart2 & extern timer2-0 */
__no_init  volatile unsigned char xdata   TCON2     _at_    0x2820;     //timer2����/״̬�Ĵ��� 0x2820
__no_init  volatile unsigned char xdata   TMOD2    	_at_    0x2821;     //timer2 TMOD 0x2821
__no_init  volatile unsigned char xdata   TH20    	_at_    0x2822;     //UART2 TH0 0x2822
__no_init  volatile unsigned char xdata   TH21    	_at_    0x2823;     //UART2 TH1 0x2823
__no_init  volatile unsigned char xdata   TL20    	_at_    0x2824;     //UART2 TL0 0x2824
__no_init  volatile unsigned char xdata   TL21    	_at_    0x2825;     //UART2 TL1 0x2825
__no_init  volatile unsigned char xdata   SCON2    	_at_    0x2826;     //UART2 ���пڿ��ƼĴ���SCON 0x2826
__no_init  volatile unsigned char xdata   SBUF2    	_at_    0x2827;     //UART2 ���пڻ���Ĵ���SBUF 0x2827
/* extern uart3 & extern timer3-0 */
__no_init  volatile unsigned char xdata   TCON3    	_at_    0x2828;     //timer3����/״̬�Ĵ��� 0x2828
__no_init  volatile unsigned char xdata   TMOD3    	_at_    0x2829;     //timer3 TMOD 0x2829
__no_init  volatile unsigned char xdata   TH30    	_at_    0x282a;     //UART3 TH0 0x282a
__no_init  volatile unsigned char xdata   TH31    	_at_    0x282b;     //UART3 TH1 0x282b
__no_init  volatile unsigned char xdata   TL30    	_at_    0x282c;     //UART3 TL0 0x282c
__no_init  volatile unsigned char xdata   TL31    	_at_    0x282d;     //UART3 TL1 0x282d
__no_init  volatile unsigned char xdata   SCON3    	_at_    0x282e;     //UART3 ���пڿ��ƼĴ���SCON 0x282e
__no_init  volatile unsigned char xdata   SBUF3    	_at_    0x282f;     //UART3 ���пڻ���Ĵ���SBUF 0x282f
/* extern uart4 & extern timer4-0 */
__no_init  volatile unsigned char xdata   TCON4    	_at_    0x2830;     //timer4����/״̬�Ĵ��� 0x2830
__no_init  volatile unsigned char xdata   TMOD4    	_at_    0x2831;     //timer4 TMOD 0x2831
__no_init  volatile unsigned char xdata   TH40    	_at_    0x2832;     //UART4 TH0 0x2832
__no_init  volatile unsigned char xdata   TH41    	_at_    0x2833;     //UART4 TH1 0x2833
__no_init  volatile unsigned char xdata   TL40    	_at_    0x2834;     //UART4 TL0 0x2834
__no_init  volatile unsigned char xdata   TL41    	_at_    0x2835;     //UART4 TL1 0x2835
__no_init  volatile unsigned char xdata   SCON4    	_at_    0x2836;     //UART4 ���пڿ��ƼĴ���SCON 0x2836
__no_init  volatile unsigned char xdata   SBUF4    	_at_    0x2837;     //UART4 ���пڻ���Ĵ���SBUF 0x2837
/* extern uart5 & extern timer5-0 */
__no_init  volatile unsigned char xdata   TCON5    	_at_    0x2838;     //timer5����/״̬�Ĵ��� 0x2838
__no_init  volatile unsigned char xdata   TMOD5    	_at_    0x2839;     //timer5 TMOD 0x2839
__no_init  volatile unsigned char xdata   TH50    	_at_    0x283a;     //UART5 TH0 0x283a
__no_init  volatile unsigned char xdata   TH51    	_at_    0x283b;     //UART5 TH1 0x283b
__no_init  volatile unsigned char xdata   TL50    	_at_    0x283c;     //UART5 TL0 0x283c
__no_init  volatile unsigned char xdata   TL51    	_at_    0x283d;     //UART5 TL1 0x283d
__no_init  volatile unsigned char xdata   SCON5    	_at_    0x283e;     //UART5 ���пڿ��ƼĴ���SCON 0x283e
__no_init  volatile unsigned char xdata   SBUF5    	_at_    0x283f;     //UART5 ���пڻ���Ĵ���SBUF 0x283f

/*========================================
		interrupt control regist
==========================================*/

/* External interrupt 2 */
__no_init  volatile unsigned char xdata   ExInt2IFG _at_    0x2840;     //�ж�����8�жϱ�־�����󣩼Ĵ��� 0x2840
__no_init  volatile unsigned char xdata   ExInt2IN  _at_    0x2841;     //�ж�����8��չ�ж��������ͼĴ��� 0x2841
__no_init  volatile unsigned char xdata   ExInt2OUT _at_    0x2842;     //�ж�����8��չ�ж�������ͼĴ��� 0x2842
__no_init  volatile unsigned char xdata   ExInt2IE  _at_    0x2843;     //�ж�����8��չ�ж�ʹ�ܼĴ��� 0x2843
__no_init  volatile unsigned char xdata   ExInt2OV  _at_    0x2844;     //�ж�����8��չ�ж϶��мĴ��� 0x2844
/* External interrupt 3 */
__no_init  volatile unsigned char xdata   ExInt3IFG _at_    0x2848;     //�ж�����9�жϱ�־�����󣩼Ĵ��� 0x2848
__no_init  volatile unsigned char xdata   ExInt3IN  _at_    0x2849;     //�ж�����9��չ�ж��������ͼĴ��� 0x2849
__no_init  volatile unsigned char xdata   ExInt3OUT _at_    0x284a;     //�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284a
__no_init  volatile unsigned char xdata   ExInt3IE  _at_    0x284b;     //�ж�����9��չ�ж�ʹ�ܼĴ��� 0x284b
__no_init  volatile unsigned char xdata   ExInt3OV  _at_    0x284c;     //�ж�����9��չ�ж϶��мĴ��� 0x284c
/* External interrupt 4 */
__no_init  volatile unsigned char xdata   ExInt4IFG _at_    0x2850;     //�ж�����10�жϱ�־�����󣩼Ĵ��� 0x2850
__no_init  volatile unsigned char xdata   ExInt4IN  _at_    0x2851;     //�ж�����10��չ�ж��������ͼĴ��� 0x2851
__no_init  volatile unsigned char xdata   ExInt4OUT _at_    0x2852;     //�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2852
__no_init  volatile unsigned char xdata   ExInt4IE  _at_    0x2853;     //�ж�����10��չ�ж�ʹ�ܼĴ��� 0x2853
__no_init  volatile unsigned char xdata   ExInt4OV  _at_    0x2854;     //�ж�����10��չ�ж϶��мĴ��� 0x2854

/*===========================================
			Analog Interface regist
============================================*/

__no_init  volatile unsigned char xdata   CtrlGA    _at_    0x2858;	    //0x2858,ia control	 
__no_init  volatile unsigned char xdata   CtrlGB    _at_    0x2859;	    //0x2859,ib control
__no_init  volatile unsigned char xdata   CtrlGU    _at_    0x285a;	    //0x285a,U control
__no_init  volatile unsigned char xdata   CtrlGM    _at_    0x285b;	    //0x285b,M control
__no_init  volatile unsigned char xdata   CtrlIAT   _at_    0x285c;	    //0x285c,ia translation
__no_init  volatile unsigned char xdata   CtrlSHORT _at_    0x285d;	    //0x285d,I,U short control
__no_init  volatile unsigned char xdata   CtrlIBT   _at_    0x285e;	    //0x285e,ib translation
__no_init  volatile unsigned char xdata   CtrlBAT   _at_    0x285f;	    //0x285f,battery discharge control
__no_init  volatile unsigned char xdata   CtrlUT    _at_    0x2860;		//0x2860 u translation
__no_init  volatile unsigned char xdata   CtrlMT    _at_    0x2861;		//0x2861 m translation
__no_init  volatile unsigned char xdata   CtrlBGP   _at_    0x2862;	    //0x2862 bandgap control
__no_init  volatile unsigned char xdata   CtrlMEAS  _at_    0x2863;	    //0x2863 measure  channel control
__no_init  volatile unsigned char xdata   CtrlADC   _at_    0x2864;	    //0x2864 ADC control
__no_init  volatile unsigned char xdata   CtrlCry   _at_    0x2865;	    //0x2865 crystal control
__no_init  volatile unsigned char xdata   CtrlLDO   _at_    0x2866;	    //0x2866 LDO control
__no_init  volatile unsigned char xdata   CtrlCLK   _at_    0x2867;	    //0x2867 clock control
__no_init  volatile unsigned char xdata   CtrlPLL   _at_    0x2868;	    //0x2868 PLL control

/**************************************************
			PM ctrl
**************************************************/

__no_init  volatile unsigned char xdata   PMCtrl1   _at_    0x2878;     // PM���ƼĴ���1  0x2878;
__no_init  volatile unsigned char xdata   PMCtrl2   _at_    0x2879;	    // PM���ƼĴ���2  0x2879;
__no_init  volatile unsigned char xdata   PMCtrl3   _at_    0x287a;	    // PM���ƼĴ���3  0x287a;
__no_init  volatile unsigned char xdata   PHCCtrl1  _at_    0x287b;     // �ǲ�У�����ƼĴ���1  0x287b;
__no_init  volatile unsigned char xdata   PHCCtrl2  _at_    0x287c;     // �ǲ�У�����ƼĴ���2  0x287c;
__no_init  volatile unsigned char xdata   PMCtrl4   _at_    0x287d;	    // PM���ƼĴ���4  0x287d;
__no_init  volatile unsigned char xdata   CFCtrl    _at_    0x287e;	    // ����������ƼĴ���  0x287e;

/**************************************************
			38KHz carrier generation
**************************************************/
__no_init  volatile unsigned char xdata   CARRH    	_at_    0x2898;     // �ز������Ĵ���1��ռ�ձȿ��ƣ��ߵ�ƽ����ʱ�� 0x2898
__no_init  volatile unsigned char xdata   CARRL    	_at_    0x2899;     // �ز������Ĵ���2��ռ�ձȿ��ƣ��͵�ƽ����ʱ�� 0x2899

/**************************************************
    write protection for 128 bytes in XRAM 
**************************************************/

__no_init  volatile unsigned char xdata   XRAMPWD   _at_    0x28a0;     // XRAM�ĸ�128�ֽ�д�뱣���Ĵ��� 0x28a0

/****************************************** 
			gpio regist 
******************************************/

/* port0_4_bits */
__no_init  volatile unsigned char xdata   P0OE    	_at_    0x28a8;//P0���ʹ�ܼĴ��� 0x28a8
__no_init  volatile unsigned char xdata   P0IE    	_at_    0x28a9;//P0����ʹ�ܼĴ��� 0x28a9
__no_init  volatile unsigned char xdata   P0OD    	_at_    0x28aa;//P0������ݼĴ��� 0x28aa
__no_init  volatile unsigned char xdata   P0ID    	_at_    0x28ab;//P0�������ݼĴ��� 0x28ab
/* port1_5_bits */
__no_init  volatile unsigned char xdata   P1OE    	_at_    0x28ac;//P1���ʹ�ܼĴ��� 0x28ac
__no_init  volatile unsigned char xdata   P1IE    	_at_    0x28ad;//P1����ʹ�ܼĴ��� 0x28ad
__no_init  volatile unsigned char xdata   P1OD    	_at_    0x28ae;//P1������ݼĴ��� 0x28ae
__no_init  volatile unsigned char xdata   P1ID    	_at_    0x28af;//P1�������ݼĴ��� 0x28af
/* port2_6_bits */
__no_init  volatile unsigned char xdata   P2OE    	_at_    0x28b0;//P2���ʹ�ܼĴ��� 0x28b0
__no_init  volatile unsigned char xdata   P2IE    	_at_    0x28b1;//P2����ʹ�ܼĴ��� 0x28b1
__no_init  volatile unsigned char xdata   P2OD    	_at_    0x28b2;//P2������ݼĴ��� 0x28b2
__no_init  volatile unsigned char xdata   P2ID    	_at_    0x28b3;//P2�������ݼĴ��� 0x28b3
/* port3_4_bits */
__no_init  volatile unsigned char xdata   P3OE    	_at_    0x28b4;//P3���ʹ�ܼĴ��� 0x28b4
__no_init  volatile unsigned char xdata   P3IE    	_at_    0x28b5;//P3����ʹ�ܼĴ��� 0x28b5
__no_init  volatile unsigned char xdata   P3OD    	_at_    0x28b6;//P3������ݼĴ��� 0x28b6
__no_init  volatile unsigned char xdata   P3ID    	_at_    0x28b7;//P3�������ݼĴ��� 0x28b7
/* port4_8_bits */
__no_init  volatile unsigned char xdata   P4OE    	_at_    0x28b8;//P4���ʹ�ܼĴ��� 0x28b8
__no_init  volatile unsigned char xdata   P4IE    	_at_    0x28b9;//P4����ʹ�ܼĴ��� 0x28b9
__no_init  volatile unsigned char xdata   P4OD    	_at_    0x28ba;//P4������ݼĴ��� 0x28ba
__no_init  volatile unsigned char xdata   P4ID    	_at_    0x28bb;//P4�������ݼĴ��� 0x28bb
/* port5_8_bits */
__no_init  volatile unsigned char xdata   P5OE    	_at_    0x28bc;//P5���ʹ�ܼĴ��� 0x28bc
__no_init  volatile unsigned char xdata   P5IE    	_at_    0x28bd;//P5����ʹ�ܼĴ��� 0x28bd
__no_init  volatile unsigned char xdata   P5OD    	_at_    0x28be;//P5������ݼĴ��� 0x28be
__no_init  volatile unsigned char xdata   P5ID    	_at_    0x28bf;//P5�������ݼĴ��� 0x28bf
/* port6_8_bits */
__no_init  volatile unsigned char xdata   P6OE    	_at_    0x28c0;//P6���ʹ�ܼĴ��� 0x28c0
__no_init  volatile unsigned char xdata   P6IE    	_at_    0x28c1;//P6����ʹ�ܼĴ��� 0x28c1
__no_init  volatile unsigned char xdata   P6OD    	_at_    0x28c2;//P6������ݼĴ��� 0x28c2
__no_init  volatile unsigned char xdata   P6ID    	_at_    0x28c3;//P6�������ݼĴ��� 0x28c3
/* special function select regist */
__no_init  volatile unsigned char xdata   P10FS    	_at_    0x28c4;//P1.0����ѡ��Ĵ��� 0x28c4
__no_init  volatile unsigned char xdata   P11FS    	_at_    0x28c5;//P1.1����ѡ��Ĵ��� 0x28c5
__no_init  volatile unsigned char xdata   P12FS    	_at_    0x28c6;//P1.2����ѡ��Ĵ��� 0x28c6
__no_init  volatile unsigned char xdata   P13FS    	_at_    0x28c7;//P1.3����ѡ��Ĵ��� 0x28c7
__no_init  volatile unsigned char xdata   P14FS    	_at_    0x28c8;//P1.4����ѡ��Ĵ��� 0x28c8
__no_init  volatile unsigned char xdata   P20FS    	_at_    0x28c9;//P2.0����ѡ��Ĵ��� 0x28c9
__no_init  volatile unsigned char xdata   P21FS    	_at_    0x28ca;//P2.1����ѡ��Ĵ��� 0x28ca
__no_init  volatile unsigned char xdata   P22FS    	_at_    0x28cb;//P2.2����ѡ��Ĵ��� 0x28cb
__no_init  volatile unsigned char xdata   P23FS    	_at_    0x28cc;//P2.3����ѡ��Ĵ��� 0x28cc
__no_init  volatile unsigned char xdata   P24FS    	_at_    0x28cd;//P2.4����ѡ��Ĵ��� 0x28cd
__no_init  volatile unsigned char xdata   P25FS    	_at_    0x28ce;//P2.5����ѡ��Ĵ��� 0x28ce
__no_init  volatile unsigned char xdata   Txd2FS    _at_    0x28cf;//TXD2����ѡ��Ĵ��� 0x28cf

__no_init  volatile unsigned char xdata   P7OE    	_at_    0x28d5;//P7���ʹ�ܼĴ��� 0x28d5
__no_init  volatile unsigned char xdata   P7IE    	_at_    0x28d6;//P7����ʹ�ܼĴ��� 0x28d6
__no_init  volatile unsigned char xdata   P7OD    	_at_    0x28d7;//P7������ݼĴ��� 0x28d7
__no_init  volatile unsigned char xdata   P7ID    	_at_    0x28d8;//P7�������ݼĴ��� 0x28d8

__no_init  volatile unsigned char xdata   P8OE    	_at_    0x28d9;//P8���ʹ�ܼĴ��� 0x28d9
__no_init  volatile unsigned char xdata   P8IE    	_at_    0x28da;//P8����ʹ�ܼĴ��� 0x28da
__no_init  volatile unsigned char xdata   P8OD    	_at_    0x28db;//P8������ݼĴ��� 0x28db 
__no_init  volatile unsigned char xdata   P8ID    	_at_    0x28dc;//P8�������ݼĴ��� 0x28dc




__no_init  volatile unsigned char xdata  FlashPw    _at_    0x8002;//FLASH���Ŀ��ƼĴ���



/*====================================================
			sys ctrl registers
=====================================================*/
__sfr __no_init volatile union
{
  unsigned char SysCtrl;
  struct 
  {
    unsigned char CLKFRQ :1;
    unsigned char SLEEP0 :1;
    unsigned char SLEEP1 :1;
    unsigned char LCDG :1;
    unsigned char PMG :1;
    unsigned char :1;
    unsigned char :1;
    unsigned char PLLLCK :1;
  } SysCtrl_bit;
} @ 0x80;

#define CLKFRQ  SysCtrl_bit.CLKFRQ
#define SLEEP0  SysCtrl_bit.SLEEP0
#define SLEEP1  SysCtrl_bit.SLEEP1
#define LCDG    SysCtrl_bit.LCDG
#define PMG     SysCtrl_bit.PMG
#define PLLLCK  SysCtrl_bit.PLLLCK

__sfr __no_init volatile unsigned char   Systate    @ 0xa1;//POR WDT IO	RTC	PWRDN	PWRUP
__sfr __no_init volatile unsigned char   version 	@ 0xa2;

__sfr __no_init volatile unsigned char   WDTEN      @ 0xce;    // 0xa5
__sfr __no_init volatile unsigned char   WDTCLR     @ 0xcf;    // 0x5a

__sfr __no_init volatile unsigned char   RTCPEN     @ 0xd9;    // 0x96
__sfr __no_init volatile unsigned char   RTCPWD     @ 0xc9;    // 0x57, 0xd7

__sfr __no_init volatile unsigned char   RTCSC      @ 0x9a;
__sfr __no_init volatile unsigned char   RTCMiC     @ 0x9b;
__sfr __no_init volatile unsigned char   RTCHC      @ 0x9c;
__sfr __no_init volatile unsigned char   RTCDC      @ 0x9d;
__sfr __no_init volatile unsigned char   RTCMoC     @ 0x9e;
__sfr __no_init volatile unsigned char   RTCYC      @ 0x9f;
__sfr __no_init volatile unsigned char   RTCWC      @ 0x93;
__sfr __no_init volatile unsigned char   RTCHCH     @ 0x94;
__sfr __no_init volatile unsigned char   RTCHCL     @ 0x95;
__sfr __no_init volatile unsigned char   RTCLCH     @ 0x96;
__sfr __no_init volatile unsigned char   RTCLCL     @ 0xa0;
__sfr __no_init volatile unsigned char   INTRTC     @ 0x97;


__sfr __no_init volatile union
{
  unsigned char RTCSFTO;
  struct 
  {
    unsigned char TSRC  :1;
    unsigned char TTYPE :1;
    unsigned char :1;
    unsigned char :1;
    unsigned char :1;
    unsigned char :1;
    unsigned char :1;
    unsigned char TERROR :1;
  } RTCSFTO_bit;
} @ 0x90;

#define TSRC    RTCSFTO_bit.TSRC
#define TTYPE 	RTCSFTO_bit.TTYPE
#define TERROR 	RTCSFTO_bit.TERROR



#endif

