#ifndef _V98xx_H_
#define _V98xx_H_
#include "dw8051.h"

#define XBYTE 		((unsigned char volatile xdata *) 0)

sfr SysCtrl = 0x80; //Clock Switchover Control Register

sbit MCUFRQ = SysCtrl^0;
sbit SLEEP0 = SysCtrl^1;
sbit SLEEP1 = SysCtrl^2;
sbit LCDG = SysCtrl^3;
sbit PMG = SysCtrl^4;
sbit FSC = SysCtrl^5;
sbit FWC = SysCtrl^6;
sbit MEAFRQ = SysCtrl^7;



sfr RTCPEN = 0x90; //RTC Password Enable Register
sfr RTCYC = 0x93; //to set the year information
sfr RTCCH = 0x94; //RTC Calibration Registers
sfr RTCCL = 0x95; //RTC Calibration Registers
sfr INTRTC = 0x96; //RTC Wake-up Interval Register
sfr RTCPWD = 0x97; //RTC Password Register
sfr RTCSC = 0x9A; //to set the second information
sfr RTCMiC = 0x9B; //to set the minute information
sfr RTCHC = 0x9C; //to set the hour information
sfr RTCDC = 0x9D; //to set the day information
sfr RTCWC = 0x9E; //to set the day of week information
sfr RTC_MON = 0x9F; //to set the month information
sfr CBANK = 0xA0; //code bank
sfr Systate = 0xA1; //System State Register
sfr PLLLCK = 0xA3; //PLL Clock State Register
sfr P9OE = 0xA4; //P9 Output Enable Register
sfr P9IE = 0xA5; //P9 Input Enable Register
sfr P9OD = 0xA6; //P9 Output Data Register
sfr P9ID = 0xA7; //P9 Input Data Register
sfr P10OE = 0xA9; //P10 Output Enable Register
sfr P10IE = 0xAA; //P10 Input Enable Register
sfr P10OD = 0xAB; //P10 Output Data Register
sfr P10ID = 0xAC; //P10 Input Data Register
sfr P9FS = 0xAD; //P9 Special Function Register
sfr IOWKDET = 0xAF; //P0 IO Wakeup Flag Register
sfr IOEDG = 0xC7; //IO Wakeup Edge Control Register
sfr IOWK = 0xC9; //IO Wakeup Control Register
sfr WDTEN = 0xCE; //
sfr WDTCLR = 0xCF; //
sfr RDRTC = 0xDA; //RTC Data Reading Enable Register
sfr DIVTHH = 0xDB; //PLL Clock Divider Registers
sfr DIVTHM = 0xDC; //PLL Clock Divider Registers
sfr DIVTHL = 0xDD; //PLL Clock Divider Registers
sfr PLLCNT = 0xDE; //PLL Counter State Register
sfr SECINT = 0xDF; //RTC Seconds Wake-up Interval Configuration Register



#define FCtrl1 XBYTE[0x402] //Flash Control Register 1
#define TCON2 XBYTE[0x2820] //UART2 Control / Status Register
#define TMOD2 XBYTE[0x2821] //UART2 Timers Mode Control Register
#define TH20 XBYTE[0x2822] //Higher Byte of General Timer of UART2
#define TH21 XBYTE[0x2823] //Higher Byte of Baud Rate Generator of UART2
#define TL20 XBYTE[0x2824] //Lower Byte of General Timer of UART2
#define TL21 XBYTE[0x2825] //Lower Byte of Baud Rate Generator of UART2
#define SCON2 XBYTE[0x2826] //UART2 Control Register
#define SBUF2 XBYTE[0x2827] //UART2 Buffer Register
#define TCON3 XBYTE[0x2828] //UART3 Control / Status Register
#define TMOD3 XBYTE[0x2829] //UART3 Timers Mode Control Register
#define TH30 XBYTE[0x282A] //Higher Byte of General Timer of UART3
#define TH31 XBYTE[0x282B] //Higher Byte of Baud Rate Generator of UART3
#define TL30 XBYTE[0x282C] //Lower Byte of General Timer of UART3
#define TL31 XBYTE[0x282D] //Lower Byte of Baud Rate Generator of UART3
#define SCON3 XBYTE[0x282E] //UART3 Control Register
#define SBUF3 XBYTE[0x282F] //UART3 Buffer Register
#define TCON4 XBYTE[0x2830] //UART4 Control / Status Register
#define TMOD4 XBYTE[0x2831] //UART4 Timers Mode Control Register
#define TH40 XBYTE[0x2832] //Higher Byte of General Timer of UART4
#define TH41 XBYTE[0x2833] //Higher Byte of Baud Rate Generator of UART4
#define TL40 XBYTE[0x2834] //Lower Byte of General Timer of UART4
#define TL41 XBYTE[0x2835] //Lower Byte of Baud Rate Generator of UART4
#define SCON4 XBYTE[0x2836] //UART4 Control Register
#define SBUF4 XBYTE[0x2837] //UART4 Buffer Register
#define TCON5 XBYTE[0x2838] //UART5 Control / Status Register
#define TMOD5 XBYTE[0x2839] //UART5 Timers Mode Control Register
#define TH50 XBYTE[0x283A] //Higher Byte of General Timer of UART5
#define TH51 XBYTE[0x283B] //Higher Byte of Baud Rate Generator of UART5
#define TL50 XBYTE[0x283C] //Lower Byte of General Timer of UART5
#define TL51 XBYTE[0x283D] //Lower Byte of Baud Rate Generator of UART5
#define SCON5 XBYTE[0x283E] //UART5 Control Register
#define SBUF5 XBYTE[0x283F] //UART5 Buffer Register
#define ExInt2IFG XBYTE[0x2840] //Extended Interrupt Flag (Request) Register
#define ExInt2IN XBYTE[0x2841] //Extended Interrupt Input Type Register
#define ExInt2OUT XBYTE[0x2842] //Extended Interrupt Output Type Register
#define ExInt2IE XBYTE[0x2843] //Extended Interrupt Enable Register
#define ExInt2OV XBYTE[0x2844] //Extended Interrupt Pending Register
#define ExInt3IFG XBYTE[0x2848] //Extended Interrupt Flag (Request) Register
#define ExInt3IN XBYTE[0x2849] //Extended Interrupt Input Type Register
#define ExInt3OUT XBYTE[0x284A] //Extended Interrupt Output Type Register
#define ExInt3IE XBYTE[0x284B] //Extended Interrupt Enable Register
#define ExInt3OV XBYTE[0x284C] //Extended Interrupt Pending Register
#define ExInt4IFG XBYTE[0x2850] //Extended Interrupt Flag (Request) Register
#define ExInt4IN XBYTE[0x2851] //Extended Interrupt Input Type Register
#define ExInt4OUT XBYTE[0x2852] //Extended Interrupt Output Type Register
#define ExInt4IE XBYTE[0x2853] //Extended Interrupt Enable Register
#define ExInt4OV XBYTE[0x2854] //Extended Interrupt Pending Register
#define CtrlADC0 XBYTE[0x2858] // ADC Control Register 0
#define CtrlADC1 XBYTE[0x2859] //ADC Control Register 1
#define CtrlADC2 XBYTE[0x285A] //ADC Control Register 2
#define CtrlADC3 XBYTE[0x285B] //ADC Control Register 3 
#define CtrlBAT XBYTE[0x285C] //Battery Discharge Control Registe
#define CtrlADC4 XBYTE[0x285D] //ADC Control Register 4
#define CtrlLCDV XBYTE[0x285E] //LCD Driver Voltage Control Register
#define CtrlCry0 XBYTE[0x285F] //Crystal Control Register 0
#define CtrlCry1 XBYTE[0x2860] //Crystal Control Register 1
#define CtrlCry2 XBYTE[0x2861] //Crystal Control Register 2
#define CtrlBGP XBYTE[0x2862] //BandGap Control Register
#define CtrlADC5 XBYTE[0x2863] //ADC Control Register 5
#define CtrlADC6 XBYTE[0x2864] //ADC Control Register 6
#define CtrlM XBYTE[0x2865] //Channel M Control Register
#define CtrlLDO XBYTE[0x2866] //LDO Control Register
#define CtrlCLK XBYTE[0x2867] // Clock Control Register
#define CtrlPLL XBYTE[0x2868] //PLL Control Register
#define ANState XBYTE[0x286B] //Analog Circuits State Register
#define PMCtrl1 0x2878 //PM Control Register 1
#define PMCtrl2 0x2879 //PM Control Register 2
#define PMCtrl3 0x287A //PM Control Register 3
#define PHCCtrl1 0x287B //Phase Compensation Control Register 1
#define PHCCtrl2 0x287C //Phase Compensation Control Register 2
#define PMCtrl4 0x287D //PM Control Register 4
#define CFCtrl 0x287E //CF Pulse Output Control Register
#define CRPST 0x287F //No-Load Detection Indication Register
#define BUFF0 XBYTE[0x2880] //
#define BUFF1 XBYTE[0x2881] //
#define BUFF2 XBYTE[0x2882] //
#define BUFF3 XBYTE[0x2883] //
#define INVD XBYTE[0x2884] //
#define ACK XBYTE[0x2885] //
#define IDET 0x2886 //Current Detection Control Register
#define CARRHH XBYTE[0x2898] //Higher byte of Carrier Wave Generation Register 1
#define CARRHL XBYTE[0x2899] //Lower byte of Carrier Wave Generation Register 1
#define CARRLH XBYTE[0x289A] //Higher Byte of Carrier Wave Generation Register 2
#define CARRLL XBYTE[0x289B] //Lower byte of Carrier Wave Generation Register 2
#define PWMCLK1H XBYTE[0x289C] //Higher byte of pulse width modulation clock generator 1
#define PWMCLK1L XBYTE[0x289D] //Lower byte of pulse width modulation clock generator 1
#define PWMCLK2H XBYTE[0x289E] //Higher byte of pulse width modulation clock generator 2
#define PWMCLK2L XBYTE[0x289F] //Lower byte of pulse width modulation clock generator 2
#define ExInt5IFG XBYTE[0x28A2] //Extended Interrupt Flag (Request) Register
#define ExInt5IN XBYTE[0x28A3] //Extended Interrupt Input Type Register
#define ExInt5OUT XBYTE[0x28A4] //Extended Interrupt Output Type Register
#define ExInt5IE XBYTE[0x28A5] //Extended Interrupt Enable Register
#define ExInt5OV XBYTE[0x28A6] //Extended Interrupt Pending Register
#define P0OE XBYTE[0x28A8] //P0 Output Enable Register
#define P0IE XBYTE[0x28A9] //P0 Input Enable Register
#define P0OD XBYTE[0x28AA] //P0 Output Data Register
#define P0ID XBYTE[0x28AB] //P0 Input Data Register
#define P1OE XBYTE[0x28AC] //P1 Output Enable Register
#define P1IE XBYTE[0x28AD] //P1 Input Enable Register
#define P1OD XBYTE[0x28AE] //P1 Output Data Register
#define P1ID XBYTE[0x28AF] //P1 Input Data Register
#define P2OE XBYTE[0x28B0] //P2 Output Enable Register
#define P2IE XBYTE[0x28B1] //P2 Input Enable Register
#define P2OD XBYTE[0x28B2] //P2 Output Data Register
#define P2ID XBYTE[0x28B3] //P2 Input Data Register
#define P3OE XBYTE[0x28B4] //P3 Output Enable Register
#define P3IE XBYTE[0x28B5] //P3 Input Enable Register
#define P3OD XBYTE[0x28B6] //P3 Output Data Register
#define P3ID XBYTE[0x28B7] //P3 Input Data Register
#define P4OE XBYTE[0x28B8] //P4 Output Enable Register
#define P4IE XBYTE[0x28B9] //P4 Input Enable Register
#define P4OD XBYTE[0x28BA] //P4 Output Data Register
#define P4ID XBYTE[0x28BB] //P4 Input Data Register
#define P5OE XBYTE[0x28BC] //P5 Output Enable Register
#define P5IE XBYTE[0x28BD] //P5 Input Enable Register
#define P5OD XBYTE[0x28BE] //P5 Output Data Register
#define P5ID XBYTE[0x28BF] //P5 Input Data Register
#define P6OE XBYTE[0x28C0] //P6 Output Enable Register
#define P6IE XBYTE[0x28C1] //P6 Input Enable Register
#define P6OD XBYTE[0x28C2] //P6 Output Data Register
#define P6ID XBYTE[0x28C3] //P6 Input Data Register
#define P10FS XBYTE[0x28C4] //P1.0 Special Function Register
#define P11FS XBYTE[0x28C5] //P1.1 Special Function Register
#define P12FS XBYTE[0x28C6] //P1.2 Special Function Register
#define P13FS XBYTE[0x28C7] //P1.3 Special Function Register
#define P14FS XBYTE[0x28C8] //P1.4 Special Function Register
#define P20FS XBYTE[0x28C9] //P2.0 Special Function Register
#define P21FS XBYTE[0x28CA] //P2.1 Special Function Register
#define P22FS XBYTE[0x28CB] //P2.2 Special Function Register
#define P23FS XBYTE[0x28CC] //P2.3 Special Function Register
#define P24FS XBYTE[0x28CD] //P2.4 Special Function Register
#define P25FS XBYTE[0x28CE] //P2.5 Special Function Register
#define Txd2FS XBYTE[0x28CF] //TXD2 Type Register
#define P7OE XBYTE[0x28D5] //P7 Output Enable Register
#define P7IE XBYTE[0x28D6] //P7 Input Enable Register
#define P7OD XBYTE[0x28D7] //P7 Output Data Register
#define P7ID XBYTE[0x28D8] //P7 Input Data Register
#define P8OE XBYTE[0x28D9] //P8 Output Enable Register
#define P8IE XBYTE[0x28DA] //P8 Input Enable Register
#define P8OD XBYTE[0x28DB] //P8 Output Data Register
#define P8ID XBYTE[0x28DC] //P8 Input Data Register
#define TACTL XBYTE[0x2900] //Timer A Control Register
#define TARL XBYTE[0x2902] //TimerA Timer/Counter Register
#define TARH XBYTE[0x2903] //TimerA Timer/Counter Register
#define TACCTL0 XBYTE[0x2904] //Timer A Compare/Capture Control Register 0
#define TACCTH0 XBYTE[0x2905] //Timer A Compare/Capture Control Register 0
#define TACCTL1 XBYTE[0x2906] //Timer A Compare/Capture Control Register 1
#define TACCTH1 XBYTE[0x2907] //Timer A Compare/Capture Control Register 1
#define TACCTL2 XBYTE[0x2908] //Timer A Compare/Capture Control Register 2
#define TACCTH2 XBYTE[0x2909] //Timer A Compare/Capture Control Register 2
#define TACCR0L XBYTE[0x290A] //Timer A Compare/Capture Register 0
#define TACCR0H XBYTE[0x290B] //Timer A Compare/Capture Register 0
#define TACCR1L XBYTE[0x290C] //Timer A Compare/Capture Register 1
#define TACCR1H XBYTE[0x290D] //Timer A Compare/Capture Register 1
#define TACCR2L XBYTE[0x290E] //Timer A Compare/Capture Register 2
#define TACCR2H XBYTE[0x290F] //Timer A Compare/Capture Register 2
#define DIVLA XBYTE[0x2A01] //Lower byte of EUART1 baud rate generator
#define DIVHA XBYTE[0x2A02] //Higher byte of EUART1 baud rate generator
#define DATAA XBYTE[0x2A03] //EUART1 Buffer Register
#define INFOA XBYTE[0x2A04] //EUART1 Information Register
#define CFGA XBYTE[0x2A05] //EUART1 Configuration Register
#define DIVLB XBYTE[0x2B01] //Lower byte of EUART2 baud rate generator
#define DIVHB XBYTE[0x2B02] //Higher byte of EUART2 baud rate generator
#define DATAB XBYTE[0x2B03] //EUART2 Buffer Register
#define INFOB XBYTE[0x2B04] //EUART2 Information Register
#define CFGB XBYTE[0x2B05] //EUART2 Configuration Register
#define LCDM0 XBYTE[0x2C00] //
#define LCDM1 XBYTE[0x2C01] //
#define LCDM2 XBYTE[0x2C02] //
#define LCDM3 XBYTE[0x2C03] //
#define LCDM4 XBYTE[0x2C04] //
#define LCDM5 XBYTE[0x2C05] //
#define LCDM6 XBYTE[0x2C06] //
#define LCDM7 XBYTE[0x2C07] //
#define LCDM8 XBYTE[0x2C08] //
#define LCDM9 XBYTE[0x2C09] //
#define LCDM10 XBYTE[0x2C0A] //
#define LCDM11 XBYTE[0x2C0B] //
#define LCDM12 XBYTE[0x2C0C] //
#define LCDM13 XBYTE[0x2C0D] //
#define LCDM14 XBYTE[0x2C0E] //
#define LCDM15 XBYTE[0x2C0F] //
#define LCDM16 XBYTE[0x2C10] //
#define LCDM17 XBYTE[0x2C11] //
#define LCDM18 XBYTE[0x2C12] //
#define LCDM19 XBYTE[0x2C13] //
#define LCDM20 XBYTE[0x2C14] //
#define LCDM21 XBYTE[0x2C15] //
#define LCDM22 XBYTE[0x2C16] //
#define LCDM23 XBYTE[0x2C17] //
#define LCDM24 XBYTE[0x2C18] //
#define LCDM25 XBYTE[0x2C19] //
#define LCDM26 XBYTE[0x2C1A] //
#define LCDM27 XBYTE[0x2C1B] //
#define LCDM28 XBYTE[0x2C1C] //
#define LCDM29 XBYTE[0x2C1D] //
#define LCDCtrl XBYTE[0x2C1E] //LCD Control Register
#define SegCtrl0 XBYTE[0x2C1F] //SEG Control Registers
#define SegCtrl1 XBYTE[0x2C20] //SEG Control Registers
#define SegCtrl2 XBYTE[0x2C21] //SEG Control Registers
#define SegCtrl3 XBYTE[0x2C22] //SEG Control Registers
#define SegCtrl4 XBYTE[0x2C23] //SEG Control Registers
#define LCDM30 XBYTE[0x2C28] //
#define LCDM31 XBYTE[0x2C29] //
#define LCDM32 XBYTE[0x2C2A] //
#define LCDM33 XBYTE[0x2C2B] //
#define LCDM34 XBYTE[0x2C2C] //
#define LCDM35 XBYTE[0x2C2D] //
#define LCDM36 XBYTE[0x2C2E] //
#define LCDM37 XBYTE[0x2C2F] //
#define LCDM38 XBYTE[0x2C30] //
#define LCDM39 XBYTE[0x2C31] //
#define PRCtrl0 XBYTE[0x2D00] //Peripheral Control Register 0
#define PRCtrl1 XBYTE[0x2D01] //Peripheral Control Register 1
#define SICFG XBYTE[0x2F01] //GPSI Control Register
#define SITHL XBYTE[0x2F02] //GPSI Timer Divider Registers
#define SITHH XBYTE[0x2F03] //GPSI Timer Divider Registers
#define SIDAT XBYTE[0x2F04] //GPSI Data Register
#define SIFLG XBYTE[0x2F05] //GPSI Communication Flag Registe

#define IDETTH 0x1002 //To set a threshold for current detection
#define DATAOIU 0x1005 //Raw waveform of voltage
#define DATAOII1 0x100A //Raw waveform of Current I1
#define DATAOII2 0x100F //Raw waveform of Current I2
#define DATAIDU 0x103A //DC component of instantaneous voltage
#define DATAIDI1 0x1041 //DC component of instantaneous Current I1
#define DATAIDI2 0x1048 //DC component of instantaneous Current I2
#define DATAIAU 0x1051 //AC component of instantaneous voltage
#define DATAIAI1 0x1052 //AC component of instantaneous Current I1
#define DATAIAI2 0x1053 //AC component of instantaneous Current I2
#define DATAOM 0x10CE //Raw waveform of Channel M
#define DATADM 0x10CF //DC component of the measurement of Channel M
#define DATAADM 0x10D0 //Average DC component of the measurement of Channel M
#define DATAIP 0x10D1 //Instantaneous active power in E1 path
#define DATAIQ 0x10D2 //Instantaneous active/reactive power in E2 path
#define RMSIU 0x10D3 //Instantaneous voltage RMS
#define RMSII1 0x10D4 //Instantaneous current I1 RMS
#define RMSII2 0x10D5 //Instantaneous current I2 RMS
#define DATAP 0x10D6 //Average active power in E1 path
#define DATAQ 0x10D7 //Average active/reactive power in E2 path
#define RMSU 0x10D8 //Average voltage RMS
#define RMSI1 0x10D9 //Average current I1 RMS
#define RMSI2 0x10DA //Average current I2 RMS
#define DATAAP1 0x10DB //Average apparent power calculated based on average current I1 and voltage RMS
#define DATAAP2 0x10DC //Average apparent power calculated based on average current I2 and voltage RMS
#define SCP 0x10E8 //To set a value to gain calibrate active power in E1 path
#define SCQ 0x10E9 //To set a value to gain calibrate active/reactive power in E2 path
#define SCU 0x10EA //To set a value to gain calibrate voltage RMS
#define SCI1 0x10EB //To set a value to gain calibrate current I1 RMS
#define SCI2 0x10EC //To set a value to gain calibrate current I2 RMS
#define PARAPC 0x10ED //To set a value to offset calibrate active power in E1 path
#define PARAQC 0x10EE //To set a value to offset calibrate active/reactive power in E2 path
#define PARABPF 0x10EF //Band-pass Filter Coefficient Register
#define PPCNT 0x10F0 //Positive active energy accumulator in E1 path
#define NPCNT 0x10F1 //Negative active energy accumulator in E1 path
#define PPCFCNT 0x10F2 //Positive active energy pulse counter in E1 path
#define NPCFCNT 0x10F3 //Negative active energy pulse counter in E1 path
#define GATEP 0x10F4 //To set a threshold for active energy-to-pulse conversion in E1 path
#define GATECP 0x10F5 //To set a threshold for no-load detection in E1 path
#define PQCNT 0x10F6 //Positive active/reactive energy accumulator in E2 path
#define NQCNT 0x10F7 //Negative active/reactive energy accumulator in E2 path
#define PQCFCNT 0x10F8 //Positive active/reactive energy pulse counter in E2 path
#define NQCFCNT 0x10F9 //Negative active/reactive energy pulse counter in E2 path
#define GATEQ 0x10FA //To set a threshold for active or reactive energy-to-pulse conversion in E2 path
#define GATECQ 0x10FB //To set a threshold for no-load detection in E2 path
#define DATACP 0x10FC //To set a constant for active energy accumulation in E1 path
#define DATAFREQ 0x10FD //Line Frequency Register

#endif

