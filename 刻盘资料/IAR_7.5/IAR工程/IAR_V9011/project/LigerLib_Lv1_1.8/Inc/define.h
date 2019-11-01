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
#define SETPLL_CLOSE 0x20
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6e

/*
	功能：配置电流、电压通道。
	入口：
	val_number：ADC 选择通道：
			SETADC_IA ----电流A 通道；
			SETADC_IB ----电流B 通道；
			SETADC_U ----电压通道
	val_para：ADC 增益选择：
			SETADC_IT1 对应IA、IB通道1倍增益;
			SETADC_IT 对应IA、IB通道2倍增益;
			SETADC_IT4 对应IA、IB通道4倍增益;
			SETADC_IT8 对应IA、IB通道8倍增益;
			SETADC_IT16 对应IA、IB通道16倍增益;
			SETADC_IT32 对应IA、IB通道32倍增益;
			SETADC_IT64 对应IA、IB通道64倍增益;
			SETADC_UT1 对应U通道1倍增益;
			SETADC_UT2 对应U通道2倍增益;
			SETADC_UT4 对应U通道4倍增益;
			SETADC_UT8 对应U通道8倍增益;
			SETADC_CLOSE 关闭相应通道
	
	出口：无
*/
extern void SetADC(unsigned char val_channel,unsigned char val_para);
#define SETADC_IA 		0
#define SETADC_IB 		1
#define SETADC_U 		2
#define SETADC_IT1 		0
#define SETADC_IT2 		1
#define SETADC_IT4 		2
#define SETADC_IT8 		3
#define SETADC_IT16 	7
#define SETADC_IT32 	0x17
#define SETADC_IT64 	0x27
#define SETADC_UT1 		0
#define SETADC_UT2 		1
#define SETADC_UT4 		0x11
#define SETADC_UT8 		0x21
#define SETADC_CLOSE 	0x80

/*功能：配置M通道
入口：val_channel：M 通道的测量通道选择：
 		SETM_TEMP ----测温；
		SETM_VBAT1 ----通过VBAT测电池电压；
		SETM_VBAT2 ----通过UM测试电池电压，
 		SETM_EXT----其它外部输入信号
	val_para：M 通道增益选择：
		SETM_T1 对应1倍增益
		SETM_T2 对应2倍增益
		SETM_T4 对应4倍增益
		SETM_T8 对应8倍增益
		SETM_CLOSE 表示关闭M通道
出口：无*/
extern void SetMChannel(unsigned char val_channel,unsigned char val_para);

#define SETM_TEMP	0x11
#define SETM_VBAT1	0x22
#define SETM_VBAT2	0x42
#define SETM_EXT	0x03
#define SETM_T1	 	0
#define SETM_T2		1
#define SETM_T4 	0x11
#define SETM_T8 	0x21
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
功能：打开BGP，打开powerdown 检测。
*/
extern void OpenPDT(void);

/*
	函数功能：配置LCD驱动电压
	函数入口：val_volt: 
		SETLCD_30V -- 3.0v//只针对电阻分压
		SETLCD_33V  -- 3.3v
		SETLCD_35V -- 3.5v
*/

extern void SetLCDVolt(unsigned char val_volt);
#define SETLCD_30V 0x80	//3V 只针对电阻分压驱动模式，对于电荷泵驱动模式设置LCD 3V无效
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
功能：将所有可读可写计量寄存器（0x1000 ～ 0x1089）清零，
再对有功功率门限值和电流有效值门限值赋经验值
*/
extern void InitMeter(void);

/*
	功能：读取计量模块参数。
	入口：val_addr：目标操作地址0到33；
	出口：目标地址内的32 位数据。此函数可以读0到33寄存器值，即0x1068～0x1089。
*/
extern unsigned long ReadMeterPara(unsigned char val_addr);

//寄存器名称	            	功能							地址（16进制）
#define DATA_FREQ			0	//频率输出						1068
#define DATA_LP_M			1	//M通道低通输出					1069
#define DATA_NOP_M			2	//M通道直接输出					106A
#define DATA_P 				3	//有功功率输出					106B
#define DATA_RMS_IA 		4	//IA通道有效值					106C
#define DATA_RMS_IB 		5	//IB通道有效值					106D
#define DATA_RMS_L 			6	//启动潜动通道有效值			106E
#define DATA_RMS_M 			7	//M通道有效值					106F
#define DATA_RMS_U 			8	//电压通道有效值				1070
#define ENERGY_NEG_COUNT 	9	//反相有功计数器				1071
#define ENERGY_NEG_HIG 		10	//反相有功能量高位				1072
#define ENERGY_NEG_LOW 		11	//反相有功能量低位				1073
#define ENERGY_POS_COUNT 	12	//正相有功计数器				1074
#define ENERGY_POS_HIG 		13	//正相有功能量高位				1075
#define ENERGY_POS_LOW 		14	//正相有功能量地位				1076
#define RMSI_ACC_CNT 		15	//有效值通道计数器				1077
#define RMSI_ACC_HIG 		16	//有效值高位					1078
#define RMSI_ACC_LOW 		17	//有效值低位					1079

#define PARA_GATE_HIG 		18	//有功门限值高位				107A
#define PARA_GATE_LOW 		19	//有功门限值低位				107B
#define PARA_IRMS_HIG 		20	//有效值门限值高位				107C
#define PARA_IRMS_LOW 		21	//有效值门限值低位				107D
#define PARA_RMS_L_GATE_H 	22	//启动潜动门限值高位			107E
#define PARA_RMS_L_GATE_L 	23	//启动潜动门限值低位			107F
#define PARA_SCALE_IA 		24	//IA的比差校正值				1080
#define PARA_SCALE_IB 		25	//IB的比差校正值				1081
#define PARA_SCALE_LA 		26	//LA的比差校正值				1082
#define PARA_SCALE_LB 		27	//LB的比差校正值				1083
#define PARA_SCALE_MD 		28	//M通道直流输入的比差校正值		1084
#define PARA_SCALE_MN 		29	//M通道直接输入的比差校正值		1085
#define PARA_SCALE_MR 		30	//M通道电流有效值的比差校正值	1086
#define PARA_SCALE_PA 		31	//有功PA的比差校正值			1087
#define PARA_SCALE_PB 		32	//有功PB的比差校正值			1088
#define PARA_SCALE_U 		33	//电压的比差校正值				1089
/*
	功能：设置计量电路各项参数。
	入口：val_data：32 位数据；
	val_addr：操作事项。只能设置18到33寄存器的值,即0x107a～0x1089。
*/
extern void SetMeterCfg(unsigned long val_data,unsigned char val_addr);

#endif







