#ifndef _EXLIGREG_H_
#define _EXLIGREG_H_
#include "dw8051.h"
#define XBYTE 		((unsigned char volatile xdata *) 0)
/*******************************************
				LCD Reg
*******************************************/
#define LCDM0    	XBYTE[0x2800]//显示缓冲寄存器 0x2800 
#define LCDM1    	XBYTE[0x2801]//显示缓冲寄存器 0x2801
#define LCDM2    	XBYTE[0x2802]//显示缓冲寄存器 0x2802
#define LCDM3    	XBYTE[0x2803]//显示缓冲寄存器 0x2803
#define LCDM4    	XBYTE[0x2804]//显示缓冲寄存器 0x2804
#define LCDM5    	XBYTE[0x2805]//显示缓冲寄存器 0x2805
#define LCDM6    	XBYTE[0x2806]//显示缓冲寄存器 0x2806
#define LCDM7    	XBYTE[0x2807]//显示缓冲寄存器 0x2807
#define LCDM8    	XBYTE[0x2808]//显示缓冲寄存器 0x2808
#define LCDM9    	XBYTE[0x2809]//显示缓冲寄存器 0x2809
#define LCDM10    	XBYTE[0x280a]//显示缓冲寄存器 0x280a
#define LCDM11    	XBYTE[0x280b]//显示缓冲寄存器 0x280b
#define LCDM12    	XBYTE[0x280c]//显示缓冲寄存器 0x280c
#define LCDM13    	XBYTE[0x280d]//显示缓冲寄存器 0x280d
#define LCDM14    	XBYTE[0x280e]//显示缓冲寄存器 0x280e
#define LCDM15    	XBYTE[0x280f]//显示缓冲寄存器 0x280f
#define LCDM16    	XBYTE[0x2810]//显示缓冲寄存器 0x2810
#define LCDM17    	XBYTE[0x2811]//显示缓冲寄存器 0x2811
#define LCDM18    	XBYTE[0x2812]//显示缓冲寄存器 0x2812
#define LCDM19    	XBYTE[0x2813]//显示缓冲寄存器 0x2813
#define LCDCtrl    	XBYTE[0x2814]// 显示控制寄存器 0x2814
#define SegCtrl0    XBYTE[0x2815]// 显示控制寄存器2 0x2815
#define SegCtrl1    XBYTE[0x2816]// 显示控制寄存器3 0x2816
#define SegCtrl2    XBYTE[0x2817]// 显示控制寄存器4 0x2817
#define SegCtrl3    XBYTE[0x2818]// 显示控制寄存器5 0x2818
#define SegCtrl4    XBYTE[0x2819]// 显示控制寄存器6 0x2819

/*********************************************
			timer & uart regist
*********************************************/

/* extern uart2 & extern timer2-0 */
#define TCON2    	XBYTE[0x2820]//timer2控制/状态寄存器 0x2820
#define TMOD2    	XBYTE[0x2821]//timer2 TMOD 0x2821
#define TH20    	XBYTE[0x2822]//UART2 TH0 0x2822
#define TH21    	XBYTE[0x2823]//UART2 TH1 0x2823
#define TL20    	XBYTE[0x2824]//UART2 TL0 0x2824
#define TL21    	XBYTE[0x2825]//UART2 TL1 0x2825
#define SCON2    	XBYTE[0x2826]//UART2 串行口控制寄存器SCON 0x2826
#define SBUF2    	XBYTE[0x2827]//UART2 串行口缓存寄存器SBUF 0x2827
/* extern uart3 & extern timer3-0 */
#define TCON3    	XBYTE[0x2828]//timer3控制/状态寄存器 0x2828
#define TMOD3    	XBYTE[0x2829]//timer3 TMOD 0x2829
#define TH30    	XBYTE[0x282a]//UART3 TH0 0x282a
#define TH31    	XBYTE[0x282b]//UART3 TH1 0x282b
#define TL30    	XBYTE[0x282c]//UART3 TL0 0x282c
#define TL31    	XBYTE[0x282d]//UART3 TL1 0x282d
#define SCON3    	XBYTE[0x282e]//UART3 串行口控制寄存器SCON 0x282e
#define SBUF3    	XBYTE[0x282f]//UART3 串行口缓存寄存器SBUF 0x282f
/* extern uart4 & extern timer4-0 */
#define TCON4    	XBYTE[0x2830]//timer4控制/状态寄存器 0x2830
#define TMOD4    	XBYTE[0x2831]//timer4 TMOD 0x2831
#define TH40    	XBYTE[0x2832]//UART4 TH0 0x2832
#define TH41    	XBYTE[0x2833]//UART4 TH1 0x2833
#define TL40    	XBYTE[0x2834]//UART4 TL0 0x2834
#define TL41    	XBYTE[0x2835]//UART4 TL1 0x2835
#define SCON4    	XBYTE[0x2836]//UART4 串行口控制寄存器SCON 0x2836
#define SBUF4    	XBYTE[0x2837]//UART4 串行口缓存寄存器SBUF 0x2837
/* extern uart5 & extern timer5-0 */
#define TCON5    	XBYTE[0x2838]//timer5控制/状态寄存器 0x2838
#define TMOD5    	XBYTE[0x2839]//timer5 TMOD 0x2839
#define TH50    	XBYTE[0x283a]//UART5 TH0 0x283a
#define TH51    	XBYTE[0x283b]//UART5 TH1 0x283b
#define TL50    	XBYTE[0x283c]//UART5 TL0 0x283c
#define TL51    	XBYTE[0x283d]//UART5 TL1 0x283d
#define SCON5    	XBYTE[0x283e]//UART5 串行口控制寄存器SCON 0x283e
#define SBUF5    	XBYTE[0x283f]//UART5 串行口缓存寄存器SBUF 0x283f

/********************************************
		interrupt control regist
********************************************/

/* External interrupt 2 */
#define ExInt2IFG    	XBYTE[0x2840]//中断向量8中断标志（请求）寄存器 0x2840
#define ExInt2IN    	XBYTE[0x2841]//中断向量8扩展中断输入类型寄存器 0x2841
#define ExInt2OUT    	XBYTE[0x2842]//中断向量8扩展中断输出类型寄存器 0x2842
#define ExInt2IE    	XBYTE[0x2843]//中断向量8扩展中断使能寄存器 0x2843
#define ExInt2OV    	XBYTE[0x2844]//中断向量8扩展中断队列寄存器 0x2844
/* External interrupt 3 */
#define ExInt3IFG    	XBYTE[0x2848]//中断向量9中断标志（请求）寄存器 0x2848
#define ExInt3IN    	XBYTE[0x2849]//中断向量9扩展中断输入类型寄存器 0x2849
#define ExInt3OUT    	XBYTE[0x284a]//中断向量9扩展中断使能寄存器 0x284a
#define ExInt3IE    	XBYTE[0x284b]//中断向量9扩展中断使能寄存器 0x284b
#define ExInt3OV    	XBYTE[0x284c]//中断向量9扩展中断队列寄存器 0x284c
/* External interrupt 4 */
#define ExInt4IFG    	XBYTE[0x2850]//中断向量10中断标志（请求）寄存器 0x2850
#define ExInt4IN    	XBYTE[0x2851]//中断向量10扩展中断输入类型寄存器 0x2851
#define ExInt4OUT    	XBYTE[0x2852]//中断向量10扩展中断使能寄存器 0x2852
#define ExInt4IE    	XBYTE[0x2853]//中断向量10扩展中断使能寄存器 0x2853
#define ExInt4OV    	XBYTE[0x2854]//中断向量10扩展中断队列寄存器 0x2854

/**************************************************
			Analog Interface regist
**************************************************/

#define CtrlGA    	XBYTE[0x2858]	//0x2858,ia control	 
#define CtrlGB    	XBYTE[0x2859]	//0x2859,ib control
#define CtrlGU    	XBYTE[0x285a]	//0x285a,U control
#define CtrlGM    	XBYTE[0x285b]	//0x285b,M control
#define CtrlIAT    	XBYTE[0x285c]	// 0x285c,ia translation
#define CtrlSHORT   XBYTE[0x285d]	//0x285d,I,U short control
#define CtrlIBT    	XBYTE[0x285e]	// 0x285e,ib translation
#define CtrlBAT    	XBYTE[0x285f]	// 0x285f,battery discharge control
#define CtrlUT    	XBYTE[0x2860]		//0x2860 u translation
#define CtrlMT    	XBYTE[0x2861]		//0x2861 m translation
#define CtrlBGP    	XBYTE[0x2862]	// 0x2862 bandgap control
#define CtrlMEAS    XBYTE[0x2863]	//0x2863 measure  channel control
#define CtrlADC    	XBYTE[0x2864]	// 0x2864 ADC control
#define CtrlCry    	XBYTE[0x2865]	//0x2865 crystal control
#define CtrlLDO    	XBYTE[0x2866]	//0x2866 LDO control
#define CtrlCLK    	XBYTE[0x2867]	//0x2867 clock control
#define CtrlPLL    	XBYTE[0x2868]	//0x2868 PLL control

/**************************************************
			PM ctrl
**************************************************/

#define PMCtrl1    	XBYTE[0x2878]	// PM控制寄存器1  0x2878;
#define PMCtrl2    	XBYTE[0x2879]	// PM控制寄存器2  0x2879;
#define PMCtrl3    	XBYTE[0x287a]	// PM控制寄存器3  0x287a;
#define PHCCtrl1    XBYTE[0x287b]// 角差校正控制寄存器1  0x287b;
#define PHCCtrl2    XBYTE[0x287c]// 角差校正控制寄存器2  0x287c;
#define PMCtrl4    	XBYTE[0x287d]	// PM控制寄存器4  0x287d;
#define CFCtrl    	XBYTE[0x287e]	// 脉冲输出控制寄存器  0x287e;

/**************************************************
			38KHz carrier generation
**************************************************/
#define CARRH    	XBYTE[0x2898]// 载波产生寄存器1：占空比控制，高电平持续时间 0x2898
#define CARRL    	XBYTE[0x2899]// 载波产生寄存器2：占空比控制，低电平持续时间 0x2899

/**************************************************
    write protection for 128 bytes in XRAM 
**************************************************/

#define XRamPwd    	XBYTE[0x28a0]    // XRAM的高128字节写入保护寄存器 0x28a0

/****************************************** 
			gpio regist 
******************************************/

/* port0_4_bits */
#define P0OE    	XBYTE[0x28a8]//P0输出使能寄存器 0x28a8
#define P0IE    	XBYTE[0x28a9]//P0输入使能寄存器 0x28a9
#define P0OD    	XBYTE[0x28aa]//P0输出数据寄存器 0x28aa
#define P0ID    	XBYTE[0x28ab]//P0输入数据寄存器 0x28ab
/* port1_5_bits */
#define P1OE    	XBYTE[0x28ac]//P1输出使能寄存器 0x28ac
#define P1IE    	XBYTE[0x28ad]//P1输入使能寄存器 0x28ad
#define P1OD    	XBYTE[0x28ae]//P1输出数据寄存器 0x28ae
#define P1ID    	XBYTE[0x28af]//P1输入数据寄存器 0x28af
/* port2_6_bits */
#define P2OE    	XBYTE[0x28b0]//P2输出使能寄存器 0x28b0
#define P2IE    	XBYTE[0x28b1]//P2输入使能寄存器 0x28b1
#define P2OD    	XBYTE[0x28b2]//P2输出数据寄存器 0x28b2
#define P2ID    	XBYTE[0x28b3]//P2输入数据寄存器 0x28b3
/* port3_4_bits */
#define P3OE    	XBYTE[0x28b4]//P3输出使能寄存器 0x28b4
#define P3IE    	XBYTE[0x28b5]//P3输入使能寄存器 0x28b5
#define P3OD    	XBYTE[0x28b6]//P3输出数据寄存器 0x28b6
#define P3ID    	XBYTE[0x28b7]//P3输入数据寄存器 0x28b7
/* port4_8_bits */
#define P4OE    	XBYTE[0x28b8]//P4输出使能寄存器 0x28b8
#define P4IE    	XBYTE[0x28b9]//P4输入使能寄存器 0x28b9
#define P4OD    	XBYTE[0x28ba]//P4输出数据寄存器 0x28ba
#define P4ID    	XBYTE[0x28bb]//P4输入数据寄存器 0x28bb
/* port5_8_bits */
#define P5OE    	XBYTE[0x28bc]//P5输出使能寄存器 0x28bc
#define P5IE    	XBYTE[0x28bd]//P5输入使能寄存器 0x28bd
#define P5OD    	XBYTE[0x28be]//P5输出数据寄存器 0x28be
#define P5ID    	XBYTE[0x28bf]//P5输入数据寄存器 0x28bf
/* port6_8_bits */
#define P6OE    	XBYTE[0x28c0]//P6输出使能寄存器 0x28c0
#define P6IE    	XBYTE[0x28c1]//P6输入使能寄存器 0x28c1
#define P6OD    	XBYTE[0x28c2]//P6输出数据寄存器 0x28c2
#define P6ID    	XBYTE[0x28c3]//P6输入数据寄存器 0x28c3
/* special function select regist */
#define P10FS    	XBYTE[0x28c4]//P1.0功能选择寄存器 0x28c4
#define P11FS    	XBYTE[0x28c5]//P1.1功能选择寄存器 0x28c5
#define P12FS    	XBYTE[0x28c6]//P1.2功能选择寄存器 0x28c6
#define P13FS    	XBYTE[0x28c7]//P1.3功能选择寄存器 0x28c7
#define P14FS    	XBYTE[0x28c8]//P1.4功能选择寄存器 0x28c8
#define P20FS    	XBYTE[0x28c9]//P2.0功能选择寄存器 0x28c9
#define P21FS    	XBYTE[0x28ca]//P2.1功能选择寄存器 0x28ca
#define P22FS    	XBYTE[0x28cb]//P2.2功能选择寄存器 0x28cb
#define P23FS    	XBYTE[0x28cc]//P2.3功能选择寄存器 0x28cc
#define P24FS    	XBYTE[0x28cd]//P2.4功能选择寄存器 0x28cd
#define P25FS    	XBYTE[0x28ce]//P2.5功能选择寄存器 0x28ce
#define Txd2FS    	XBYTE[0x28cf]//TXD2类型选择寄存器 0x28cf

#define P7OE    	XBYTE[0x28d5]//P7输出使能寄存器 0x28d5
#define P7IE    	XBYTE[0x28d6]//P7输入使能寄存器 0x28d6
#define P7OD    	XBYTE[0x28d7]//P7输出数据寄存器 0x28d7
#define P7ID    	XBYTE[0x28d8]//P7输入数据寄存器 0x28d8

#define P8OE    	XBYTE[0x28d9]//P8输出使能寄存器 0x28d9
#define P8IE    	XBYTE[0x28da]//P8输入使能寄存器 0x28da
#define P8OD    	XBYTE[0x28db]//P8输出数据寄存器 0x28db 
#define P8ID    	XBYTE[0x28dc]//P8输入数据寄存器 0x28dc



/*******************************************
			sys ctrl registers
*******************************************/
sfr  SysCtrl    = 0x80;

sbit CLKFRQ		= SysCtrl^0;
sbit SLEEP0		= SysCtrl^1;
sbit SLEEP1		= SysCtrl^2;
sbit LCDG		= SysCtrl^3;
sbit PMG		= SysCtrl^4;
sbit PLLLCK		= SysCtrl^7;

sfr  Systate	 = 0xa1;//POR WDT IO	RTC	PWRDN	PWRUP
sfr  version     = 0xa2;

sfr  WDTEN      = 0xce;    // 0xa5
sfr  WDTCLR     = 0xcf;    // 0x5a

sfr  RTCPEN     = 0xd9;    // 0x96
sfr  RTCPWD      = 0xc9;    // 0x57, 0xd7

sfr  RTCSC    	 = 0x9a;
sfr  RTCMiC   	 = 0x9b;
sfr  RTCHC	     = 0x9c;
sfr  RTCDC	     = 0x9d;
sfr  RTCMoC	     = 0x9e;
sfr  RTCYC	  	 = 0x9f;
sfr  RTCWC		 = 0x93;
sfr  RTCHCH		 = 0x94;
sfr  RTCHCL		 = 0x95;
sfr  RTCLCH		 = 0x96;
sfr  RTCLCL		 = 0xa0;
sfr  INTRTC     = 0x97;

sfr  RTCSFTO	 = 0x90;
sbit TSRC      = RTCSFTO^0;
sbit TTYPE     = RTCSFTO^1;
sbit TERROR     = RTCSFTO^7;


sbit F1    = PSW^1;
//全局变量
//extern unsigned long data u32PMdatal;//计量寄存器数据低32位，用于计量寄存器数据读写存放
//extern unsigned char data u8PMdatah;//计量寄存器数据高8位，用于计量寄存器数据读写存放

#endif

