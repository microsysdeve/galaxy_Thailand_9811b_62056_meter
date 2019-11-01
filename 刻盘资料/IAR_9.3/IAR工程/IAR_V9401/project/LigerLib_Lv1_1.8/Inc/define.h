#ifndef _DEFINE_H
#define _DEFINE_H
/*
���ܣ��жϵ�ǰƵ���Ƿ�Ϊ�û�Ŀ��Ƶ�ʣ�������ǣ��л�PLLƵ�ʣ�
	����ϵͳ��ʱ���л�����ǰPLLƵ�ʣ�
	����ADC���ģ�����ref�¶�ϵ������BGPCHOP
��ڣ�val_para��
		SETPLL_CLOSE �����ǰϵͳ��ʱ�Ӳ���32k����ϵͳ��ʱ���е�32k���ر�PLL��
		SETPLL_800K �����ǰPLL ���ǹ����� 800k����PLL�е�800k������ADC�͹���
		SETPLL_1_6M �����ǰPLL ���ǹ����� 1.6M����PLL�е�1.6M������ADC�͹���
		SETPLL_3_2M �����ǰPLL ���ǹ����� 3.2M����PLL�е�3.2M������ADC�߹���
		SETPLL_6_4M �����ǰPLL ���ǹ����� 6.4M����PLL�е�6.4M������ADC�߹���
*/
extern void SetPLL(unsigned char val_para);
#define SETPLL_CLOSE 0x20
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6e

/*
	���ܣ����õ�������ѹͨ����
	��ڣ�
	val_number��ADC ѡ��ͨ����
			SETADC_IA ----����A ͨ����
			SETADC_IB ----����B ͨ����
			SETADC_U ----��ѹͨ��
	val_para��ADC ����ѡ��
			SETADC_IT1 ��ӦIA��IBͨ��1������;
			SETADC_IT ��ӦIA��IBͨ��2������;
			SETADC_IT4 ��ӦIA��IBͨ��4������;
			SETADC_IT8 ��ӦIA��IBͨ��8������;
			SETADC_IT16 ��ӦIA��IBͨ��16������;
			SETADC_IT32 ��ӦIA��IBͨ��32������;
			SETADC_IT64 ��ӦIA��IBͨ��64������;
			SETADC_UT1 ��ӦUͨ��1������;
			SETADC_UT2 ��ӦUͨ��2������;
			SETADC_UT4 ��ӦUͨ��4������;
			SETADC_UT8 ��ӦUͨ��8������;
			SETADC_CLOSE �ر���Ӧͨ��
	
	���ڣ���
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

/*���ܣ�����Mͨ��
��ڣ�val_channel��M ͨ���Ĳ���ͨ��ѡ��
 		SETM_TEMP ----���£�
		SETM_VBAT1 ----ͨ��VBAT���ص�ѹ��
		SETM_VBAT2 ----ͨ��UM���Ե�ص�ѹ��
 		SETM_EXT----�����ⲿ�����ź�
	val_para��M ͨ������ѡ��
		SETM_T1 ��Ӧ1������
		SETM_T2 ��Ӧ2������
		SETM_T4 ��Ӧ4������
		SETM_T8 ��Ӧ8������
		SETM_CLOSE ��ʾ�ر�Mͨ��
���ڣ���*/
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

/*	���ܣ� 50/60 Hz ѡ��
	��ڣ� val_frq��
		ALT_50HZ ----ѡ��50Hz��
		ALT_60HZ ----ѡ��60Hz
	���ڣ���
*/
extern void Alt_50_60Hz(unsigned char val_frq);
#define ALT_50HZ 0
#define ALT_60HZ 1
/*	���ܣ� ��ȡ50/60 Hz ����
	��ڣ���
	���ڣ� 0----ѡ��50Hz;
		1----ѡ��60Hz

*/
extern unsigned char Read_50_60Hz(void);

/*	���ܣ�
	����LDO25�����ѹ��� ��Լ2.1V��
	��AD��
	��SEG�������LCD����LCDʱ�ӣ�
	��ֹ������·����˫��ram���ر����м���ͨ������PMʱ�ӣ�
	��ϵͳ�е���Ƶ������
	��PLL��
	��ϵͳ������˯�ߡ�
*/
extern void DeepSleep(void);

/*	���ܣ�
	����LDO25�����ѹ��� ��Լ2.1V��
	��AD��
	��ֹ������·����˫��ram���ر����м���ͨ������PMʱ�ӣ�
	��ϵͳ�е���Ƶ������
	��PLL��
	��ϵͳ���ٽ���ǳ˯�ߡ�
*/
extern void Sleep(void);

/*
���ܣ���ģ��Ĵ���û���õ���λ���㡣
*/
extern void InitAnalog(void);

/*
���ܣ���BGP����powerdown ��⡣
*/
extern void OpenPDT(void);

/*
	�������ܣ�����LCD������ѹ
	������ڣ�val_volt: 
		SETLCD_30V -- 3.0v//ֻ��Ե����ѹ
		SETLCD_33V  -- 3.3v
		SETLCD_35V -- 3.5v
*/

extern void SetLCDVolt(unsigned char val_volt);
#define SETLCD_30V 0x80	//3V ֻ��Ե����ѹ����ģʽ�����ڵ�ɱ�����ģʽ����LCD 3V��Ч
#define SETLCD_33V 0
#define SETLCD_35V 0x10

/*
���ܣ�����LDO��ѹʹ���ֲ��ִ��ڲ�ͬ�Ĺ��ġ�
������ڣ�val_volt��
		SETLDO_25V  :LDO25���2.5V
		SETLDO_28V  :LDO25���2.8V
		SETLDO_22V  :LDO25���2.2V
		SETLDO_24V  :LDO25���2.4V
*/
extern void SetLDOVolt(unsigned char val_volt);
#define SETLDO_25V 0
#define SETLDO_28V 1
#define SETLDO_22V 2
#define SETLDO_24V 3

/*
���ܣ������пɶ���д�����Ĵ�����0x1000 �� 0x1089�����㣬
�ٶ��й���������ֵ�͵�����Чֵ����ֵ������ֵ
*/
extern void InitMeter(void);

/*
	���ܣ���ȡ����ģ�������
	��ڣ�val_addr��Ŀ�������ַ0��33��
	���ڣ�Ŀ���ַ�ڵ�32 λ���ݡ��˺������Զ�0��33�Ĵ���ֵ����0x1068��0x1089��
*/
extern unsigned long ReadMeterPara(unsigned char val_addr);

//�Ĵ�������	            	����							��ַ��16���ƣ�
#define DATA_FREQ			0	//Ƶ�����						1068
#define DATA_LP_M			1	//Mͨ����ͨ���					1069
#define DATA_NOP_M			2	//Mͨ��ֱ�����					106A
#define DATA_P 				3	//�й��������					106B
#define DATA_RMS_IA 		4	//IAͨ����Чֵ					106C
#define DATA_RMS_IB 		5	//IBͨ����Чֵ					106D
#define DATA_RMS_L 			6	//����Ǳ��ͨ����Чֵ			106E
#define DATA_RMS_M 			7	//Mͨ����Чֵ					106F
#define DATA_RMS_U 			8	//��ѹͨ����Чֵ				1070
#define ENERGY_NEG_COUNT 	9	//�����й�������				1071
#define ENERGY_NEG_HIG 		10	//�����й�������λ				1072
#define ENERGY_NEG_LOW 		11	//�����й�������λ				1073
#define ENERGY_POS_COUNT 	12	//�����й�������				1074
#define ENERGY_POS_HIG 		13	//�����й�������λ				1075
#define ENERGY_POS_LOW 		14	//�����й�������λ				1076
#define RMSI_ACC_CNT 		15	//��Чֵͨ��������				1077
#define RMSI_ACC_HIG 		16	//��Чֵ��λ					1078
#define RMSI_ACC_LOW 		17	//��Чֵ��λ					1079

#define PARA_GATE_HIG 		18	//�й�����ֵ��λ				107A
#define PARA_GATE_LOW 		19	//�й�����ֵ��λ				107B
#define PARA_IRMS_HIG 		20	//��Чֵ����ֵ��λ				107C
#define PARA_IRMS_LOW 		21	//��Чֵ����ֵ��λ				107D
#define PARA_RMS_L_GATE_H 	22	//����Ǳ������ֵ��λ			107E
#define PARA_RMS_L_GATE_L 	23	//����Ǳ������ֵ��λ			107F
#define PARA_SCALE_IA 		24	//IA�ıȲ�У��ֵ				1080
#define PARA_SCALE_IB 		25	//IB�ıȲ�У��ֵ				1081
#define PARA_SCALE_LA 		26	//LA�ıȲ�У��ֵ				1082
#define PARA_SCALE_LB 		27	//LB�ıȲ�У��ֵ				1083
#define PARA_SCALE_MD 		28	//Mͨ��ֱ������ıȲ�У��ֵ		1084
#define PARA_SCALE_MN 		29	//Mͨ��ֱ������ıȲ�У��ֵ		1085
#define PARA_SCALE_MR 		30	//Mͨ��������Чֵ�ıȲ�У��ֵ	1086
#define PARA_SCALE_PA 		31	//�й�PA�ıȲ�У��ֵ			1087
#define PARA_SCALE_PB 		32	//�й�PB�ıȲ�У��ֵ			1088
#define PARA_SCALE_U 		33	//��ѹ�ıȲ�У��ֵ				1089
/*
	���ܣ����ü�����·���������
	��ڣ�val_data��32 λ���ݣ�
	val_addr���������ֻ������18��33�Ĵ�����ֵ,��0x107a��0x1089��
*/
extern void SetMeterCfg(unsigned long val_data,unsigned char val_addr);

#endif







