
/***************** Copyright by Vango ***********************************
	文件名：ExLigLib.h

	创 建 人：huangsufang
	创建日期：2010-03-03 
	当前版本：1.0

	修改记录 : 
	日 期        版本     修改人              修改内容
	2010-03-03   1.0      huangsufang         初建用于V9011和V9311的头文件

**********************************************************************/
#ifndef _DEFINE_H
#define _DEFINE_H
/*
功能：判断当前频率是否为用户目标频率，如果不是，切换PLL频率，
	并将系统主时钟切换到当前PLL频率，
	设置ADC功耗，调整ref温度系数，开BGPCHOP
入口：val_para：
		SETPLL_CLOSE 如果当前系统主时钟不是32k，则将系统主时钟切到32k，关闭PLL。
		SETPLL_800K 如果当前PLL 不是工作在 800k，则将PLL切到800k，设置ADC低功耗
		SETPLL_1_6M 如果当前PLL 不是工作在 1.6M，则将PLL切到1.6M，设置ADC低功耗
		SETPLL_3_2M 如果当前PLL 不是工作在 3.2M，则将PLL切到3.2M，设置ADC高功耗
		SETPLL_6_4M 如果当前PLL 不是工作在 6.4M，则将PLL切到6.4M，设置ADC高功耗
*/
extern void SetPLL(unsigned char val_para);
#define SETPLL_CLOSE 0x00
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6f

/*
	功能：配置电流、电压通道。
	入口：
	val_number：ADC 选择通道：
			SETADC_IA ----电流A 通道；
			SETADC_IB ----电流B 通道；
			SETADC_U ----电压通道
	val_para：ADC 增益选择：
			SETADC_IT1 对应IA、IB通道1倍增益;
			SETADC_IT4 对应IA、IB通道4倍增益;
			SETADC_IT8 对应IA、IB通道8倍增益;
			SETADC_IT16 对应IA、IB通道16倍增益;
			SETADC_UT1 对应U通道1倍增益;
			SETADC_CLOSE 关闭相应通道
	
	出口：无
	  注意：电压ADC只有1倍模拟增益（无增益），电流ADC只有1、4、8、16四种模拟增益
*/
extern void SetADC(unsigned char val_channel,unsigned char val_para);
#define SETADC_IA 		0
#define SETADC_IB 		1
#define SETADC_U 		2
#define SETADC_IT1 		0
#define SETADC_IT4 		1
#define SETADC_IT8 		2
#define SETADC_IT16 	3

#define SETADC_UT1 		0
#define SETADC_CLOSE 		0x80

/*功能：配置M通道
入口：val_channel：M 通道的测量通道选择：
	0x0: measure the ground;
	0x1: measure temperature
	0x22: measure battery SETM_VBAT1// 分压后
	0x23: measure battery SETM_VBAT2//  分压后
	0x03: measure external input VM//  不分压
	0x04: measure SEG33//  不分压
	0x05: measure SEG34//  不分压
	0x06: measure SEG35//  不分压
	0x07: measure SEG36//  不分压
	0x24: measure SEG33//  分压后
	0x25: measure SEG34//  分压后
	0x26: measure SEG35//  分压后
	0x27: measure SEG36//  分压后
	val_para：M 通道增益选择：
		SETM_T1 对应1倍增益
		SETM_T2 对应2倍增益
		SETM_CLOSE 表示关闭M通道
出口：无*/
extern void SetMChannel(unsigned char val_channel,unsigned char val_para);

#define SETM_GROUND	0x0
#define SETM_TEMP	0x1
#define SETM_VBAT1	0x22
#define SETM_VBAT2	0x23
#define SETM_EXT	0x03
#define SETM_S_SEG33	0x04
#define SETM_S_SEG34	0x05
#define SETM_S_SEG35	0x06
#define SETM_S_SEG36	0x07
#define SETM_L_SEG33	0x24
#define SETM_L_SEG34	0x25
#define SETM_L_SEG35	0x26
#define SETM_L_SEG36	0x27
#define SETM_T1	 	0
#define SETM_T2		1
#define SETM_CLOSE 	0x80

/*	功能： 50/60 Hz 选择
	入口： val_frq：
		ALT_50HZ ----选择50Hz，
		ALT_60HZ ----选择60Hz
	出口：无
*/
extern void Alt_50_60Hz(unsigned char val_frq);
#define ALT_50HZ 0
#define ALT_60HZ 1
/*	功能： 读取50/60 Hz 设置
	入口：无
	出口： 0----选择50Hz;
		1----选择60Hz

*/
extern unsigned char Read_50_60Hz(void);

/*	功能：
	关闭LDO33
	设置LDO25输出电压最低 大约2.1V；
	关AD；
	关SEG输出；关LCD；关LCD时钟；
	禁止计量电路访问双口ram；关闭所有计量通道；关PM时钟；
	将系统切到低频工作；
	关PLL；
	让系统进入深睡眠。
*/
extern void DeepSleep(void);

/*	功能：
	关闭LDO33
	设置LDO25输出电压最低 大约2.1V；
	关AD；
	禁止计量电路访问双口ram；关闭所有计量通道；关PM时钟；
	将系统切到低频工作；
	关PLL；
	让系统快速进入浅睡眠。
*/
extern void Sleep(void);

/*
功能：将模拟寄存器没有用到的位清零。
*/
extern void InitAnalog(void);


/*
	函数功能：配置LCD驱动电压
	函数入口：val_volt: 
		SETLCD_30V -- 3.0v
		SETLCD_33V -- 3.3v
		SETLCD_35V -- 3.5v
*/

extern void SetLCDVolt(unsigned char val_volt);
#define SETLCD_30V 0x80	
#define SETLCD_33V 0
#define SETLCD_35V 0x10

/*
功能：配置LDO电压使数字部分处于不同的功耗。
函数入口：val_volt：
		SETLDO_25V  :LDO25输出2.5V
		SETLDO_28V  :LDO25输出2.8V
		SETLDO_22V  :LDO25输出2.2V
		SETLDO_24V  :LDO25输出2.4V
*/
extern void SetLDOVolt(unsigned char val_volt);
#define SETLDO_25V 0
#define SETLDO_28V 1
#define SETLDO_22V 2
#define SETLDO_24V 3

/*
	功能：配置晶振高低功耗，配置晶振频率。
	入口：
	val_power：
	晶振功耗选择：8----晶振高功耗；0----晶振低功耗；
	val_freq：
	晶振频率选择：0、1、2、3、4、5、6、7晶振频率递减。
	出口：无
*/
extern void SetCrystal(unsigned char val_power, unsigned char val_freq);
#define SETCRY_POWERL 0		//晶振低功耗
#define SETCRY_POWERH 0x08	//晶振高功耗

#define SETCRY_FREQ0 0
#define SETCRY_FREQ1 1
#define SETCRY_FREQ2 2
#define SETCRY_FREQ3 3
#define SETCRY_FREQ4 4
#define SETCRY_FREQ5 5
#define SETCRY_FREQ6 6
#define SETCRY_FREQ7 7

/*功能： 电池放电选择
入口： val_para：0----关闭电池放电功能，1----打开电池放电功能
出口：无

当电池长时间不使用时，使能电池放电Alt_BatDisc(Enable_BatDisc)，以防止电池进行钝化状态。
电池放电过程中，电池上消耗的电流约为3mA,大约过500ms，关闭电池放电功能Alt_BatDisc(Disable_BatDis),
具体时间与电池性能相关。
*/

extern  void Alt_BatDisc(unsigned char val_para);

#define Enable_BatDisc 1//打开放电
#define Disable_BatDisc 0//关闭放电
/*
功能：将所有可读可写计量寄存器清零，
再对有功功率门限值和电流有效值门限值赋经验值
*/
extern void InitMeter(void);

/*
	功能：读取计量模块参数。
	入口：val_addr：目标操作地址0x1000到0x10FD。
	出口：无
	读出数据存入全局变量，u8PMdatah为高8位，u32PMdatal为低32位。
*/
extern void ReadMeterPara(unsigned int val_addr);
/*
	功能：设置计量电路各项参数。
	入口：val_addr：计量寄存器地址:目标操作地址0x1000到0x10FD。
	出口：无。
	参数写入全局变量，u8PMdatah为高8位，u32PMdatal为低32位。
*/
extern void SetMeterCfg(unsigned int val_addr);
 
#define DATAIP	0x10D1			//瞬时有功功率
#define DATAIQ 0x10D2			//瞬时无功功率
#define RMSIU 0x10D3			//瞬时电压有效值
#define RMSII1	0x10D4			//I1通道瞬时电流有效值
#define RMSII2	0x10D5			//I2通道瞬时电流有效值
#define DATAP	0x10D6			//秒平均有功功率
#define DATAQ	0x10D7			//秒平均无功功率
#define RMSU	0x10D8			//秒平均电压有效值
#define RMSI1	0x10D9			//I1通道秒平均电流有效值
#define RMSI2	0x10DA			//I2通道秒平均电流有效值
#define DATAAP1 0x10DB		        //I1通道秒平均视在功率
#define DATAAP2 0x10DC		        //I2通道秒平均视在功率

#define SCP 0x10DD		//有功功率比差寄存器
#define SCQ 0x10DE		//无功功率比差寄存器
#define SCU 0x10DF		//电压有效值比差寄存器
#define SCI1 0x10E0		//通道I1电流有效值比差寄存器
#define SCI2 0x10E1		//通道I2电流有效值比差寄存器

#define PARAPC 0x10E2			//有功功率二次补偿寄存器
#define PARAQC 0x10E3			//无功功率二次补偿寄存器

#define PPCNT 0x10F0				//正相有功能量计数器
#define NPCNT 0x10F1				//反相有功能量计数器
#define PPCFCNT	0x10F2			//正相有功能量脉冲计数器
#define NPCFCNT	0x10F3			//反相有功能量脉冲计数器
#define PQCNT 0x10F6				//正相无功能量计数器
#define NQCNT 0x10F7				//反相无功能量计数器
#define PQCFCNT	0x10F8			//正相无功能量脉冲计数器
#define NQCFCNT	0x10F9			//反相无功能量脉冲计数器

#define GATEP 0x10F4			//有功能量脉冲门限值寄存器
#define GATECP 0x10F5			//有功能量潜动门限值寄存器
#define GATEQ 0x10FA			//无功能量脉冲门限值寄存器
#define GATECQ 0x10FB			//无功能量潜动门限值寄存器
#define DATACP	0x10FC			//常数功率值寄存器

#define DATAFREQ 0x10FD 		//频率值寄存器

#define DATAOM	0x10CE			//M通道原始数据值寄存器
#define DATADM	0x10CF			//M通道直流数据值寄存器
#define DATAADM 0x10D0		//M通道直流秒平均数据值寄存器


/*
	功能：设置LDO33开启或关闭。
	入口：Val_LDO33：开启和关闭LDO33操作指令：0----关闭LDO33,1----开启LDO33
	出口：无。
	
	LDO33只有在掉电的情况下才能关掉，如果出于上电状态LDO33无法关闭，一直出于开启状态
		
*/

extern unsigned char SetLDO33(unsigned char Val_LDO33);
#define CloseLDO33    0  	//关闭LDO33
#define OpenLDO33    1	//开启LDO33



#endif







