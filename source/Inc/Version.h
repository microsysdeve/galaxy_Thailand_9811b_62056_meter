/*
*版本控制
*每添加一个版本请注明当前版本与上一版本不同之处,在哪几个源文件中有变动,具体指明
*
*/
#ifndef __VERSION_H__
#define __VERSION_H__
//系统工作电压
#define CONFIG_VCC      0               //0-3.3V工作系统 1-5V工作系统
//上电稳定时间
#define CONFIG_DELAY    1              //上电判断电源稳定延时，单位20ms？
//通道配置
#define CONFIG_CH       2               //1-单通道 2-双通道
#define CONFIG_CH_DLY   2               //通道切换延时，单位S
//PT配置
#define CONFIG_PT       1               //0-不带PT 1-带PT
//电流接线方式
#define CONFIG_JUNC     1              //0-反接 1-正接
#define CONFIG_POW_DLY  1               //电流反向判断延时
//RTC配置
#define CONFIG_RTC      1               //0-无 1-内部 2-外部
//SOC时钟源配置，默认0为全开
#define CONFIG_PRCTRL0  0               //
#define CONFIG_PRCTRL1  0               //
//Uart相关配置见ComConfig.h
//部分底层配置见McuDriver.h
//计量相关配置
#define MEA_AMUL        12800*2979      //3.2M/800K计量门限与32K计量门限差值比例系数
#define MEA_BMUL        1               //电流通道1与电流通道2输入信号比例关系 A>B-* A<B-/

#define MEA_SLP_PLL     1               //唤醒时的计量时钟配置    0-800K,   1-3.2M
#define MEA_SLP_FMCU    1               //唤醒时的MCU时钟配置    0-800K,   1-3.2M
#define MEA_SLP_CF      1               //休眠计量是否出CF脉冲    0-不出,   1-出
#define POW_OFF_DISP    0               //休眠唤醒时是否显示      0-不显示, 1-显示
#define POW_OFF_ENYPROC  1              //休眠唤醒时是否电量处理  0-不处理, 1-处理


#define START_TH_1A       0x01
#define START_TH_0A5     0x02

#define START_TH   START_TH_0A5   //启动门限宏定义

#if( START_TH == START_TH_1A)  //1A启动

  #define IDET_STARTA     10608000           //A路快速电流检测阀值 1A x 0.8
  #define IDET_STARTB     11040000           //B路快速电流检测阀值 1A x 0.8
  #define RMSII1_TH       6538500     //1A x 0.9  要保证RMSII1大于此门限的时候 快速电流检测能一直检测到电流

#elif( START_TH == START_TH_0A5)  //0.5A启动

  #define IDET_STARTA     3978000           //A路快速电流检测阀值 1A x 0.3
  #define IDET_STARTB     4140000           //B路快速电流检测阀值 1A x 0.3
  #define RMSII1_TH       (2906000 *8)    //1A x 0.4

#endif

//快速电流检测阀值，必须是在比差为0时得到的寄存器RMSII1、RMSII2的值
//#define IDET_STARTA     6600000           //A路快速电流检测阀值 1A
//#define IDET_STARTB     6800000           //B路快速电流检测阀值 1A

//#define IDET_STARTA     5280000           //A路快速电流检测阀值 1A x 0.8
//#define IDET_STARTB     5440000           //B路快速电流检测阀值 1A x 0.8

//#define IDET_STARTA     1980000           //A路快速电流检测阀值 1A x 0.3
//#define IDET_STARTB     2040000           //B路快速电流检测阀值 1A x 0.3

//x.xA启动时寄存器RMSII1的值(经过比差计算之后的值)
//#define RMSII1_TH       3620000   //1A

//#define RMSII1_TH       3258000     //1A x 0.9  要保证RMSII1大于此门限的时候 快速电流检测能一直检测到电流

//#define RMSII1_TH       1448000     //1A x 0.4

//表计类型
#define CONST_A_METER   0               //三相液晶表
#define CONST_B_METER   1               //单相表
#define CONST_C_METER   2


#define __D143__                     //海外防窃电

/**表计选择和版本控制
版本定义
*/

#if defined(__D143__)
    #define __METER_TYPE__ CONST_B_METER
#endif

#if (__METER_TYPE__ != CONST_B_METER)
    #error "VersionExt.h: system not define B meter type!!!"
#endif

#define __VER_SOFT_B__  "D143F9821S03"      //当前软件版本
#define __VER_HARD_B__  0x01            //当前硬件版本

extern const __root uint8 code gCuc_VerSoft[];
extern const __root uint8 code gCuc_VerHard[];


#endif

