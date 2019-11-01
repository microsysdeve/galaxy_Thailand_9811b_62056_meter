
/***************** Copyright by Vango ***********************************
	�ļ�����ExLigLib.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03 
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����
	2010-03-03   1.0      huangsufang         ��������V9011��V9311��ͷ�ļ�

**********************************************************************/
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
#define SETPLL_CLOSE 0x00
#define SETPLL_800K 0x60
#define SETPLL_1_6M 0x65
#define SETPLL_3_2M 0x6a
#define SETPLL_6_4M 0x6f

/*
	���ܣ����õ�������ѹͨ����
	��ڣ�
	val_number��ADC ѡ��ͨ����
			SETADC_IA ----����A ͨ����
			SETADC_IB ----����B ͨ����
			SETADC_U ----��ѹͨ��
	val_para��ADC ����ѡ��
			SETADC_IT1 ��ӦIA��IBͨ��1������;
			SETADC_IT4 ��ӦIA��IBͨ��4������;
			SETADC_IT8 ��ӦIA��IBͨ��8������;
			SETADC_IT16 ��ӦIA��IBͨ��16������;
			SETADC_UT1 ��ӦUͨ��1������;
			SETADC_CLOSE �ر���Ӧͨ��
	
	���ڣ���
	  ע�⣺��ѹADCֻ��1��ģ�����棨�����棩������ADCֻ��1��4��8��16����ģ������
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

/*���ܣ�����Mͨ��
��ڣ�val_channel��M ͨ���Ĳ���ͨ��ѡ��
	0x0: measure the ground;
	0x1: measure temperature
	0x22: measure battery SETM_VBAT1// ��ѹ��
	0x23: measure battery SETM_VBAT2//  ��ѹ��
	0x03: measure external input VM//  ����ѹ
	0x04: measure SEG33//  ����ѹ
	0x05: measure SEG34//  ����ѹ
	0x06: measure SEG35//  ����ѹ
	0x07: measure SEG36//  ����ѹ
	0x24: measure SEG33//  ��ѹ��
	0x25: measure SEG34//  ��ѹ��
	0x26: measure SEG35//  ��ѹ��
	0x27: measure SEG36//  ��ѹ��
	val_para��M ͨ������ѡ��
		SETM_T1 ��Ӧ1������
		SETM_T2 ��Ӧ2������
		SETM_CLOSE ��ʾ�ر�Mͨ��
���ڣ���*/
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
	�ر�LDO33
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
	�ر�LDO33
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
	�������ܣ�����LCD������ѹ
	������ڣ�val_volt: 
		SETLCD_30V -- 3.0v
		SETLCD_33V -- 3.3v
		SETLCD_35V -- 3.5v
*/

extern void SetLCDVolt(unsigned char val_volt);
#define SETLCD_30V 0x80	
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
	���ܣ����þ���ߵ͹��ģ����þ���Ƶ�ʡ�
	��ڣ�
	val_power��
	���񹦺�ѡ��8----����߹��ģ�0----����͹��ģ�
	val_freq��
	����Ƶ��ѡ��0��1��2��3��4��5��6��7����Ƶ�ʵݼ���
	���ڣ���
*/
extern void SetCrystal(unsigned char val_power, unsigned char val_freq);
#define SETCRY_POWERL 0		//����͹���
#define SETCRY_POWERH 0x08	//����߹���

#define SETCRY_FREQ0 0
#define SETCRY_FREQ1 1
#define SETCRY_FREQ2 2
#define SETCRY_FREQ3 3
#define SETCRY_FREQ4 4
#define SETCRY_FREQ5 5
#define SETCRY_FREQ6 6
#define SETCRY_FREQ7 7

/*���ܣ� ��طŵ�ѡ��
��ڣ� val_para��0----�رյ�طŵ繦�ܣ�1----�򿪵�طŵ繦��
���ڣ���

����س�ʱ�䲻ʹ��ʱ��ʹ�ܵ�طŵ�Alt_BatDisc(Enable_BatDisc)���Է�ֹ��ؽ��жۻ�״̬��
��طŵ�����У���������ĵĵ���ԼΪ3mA,��Լ��500ms���رյ�طŵ繦��Alt_BatDisc(Disable_BatDis),
����ʱ������������ء�
*/

extern  void Alt_BatDisc(unsigned char val_para);

#define Enable_BatDisc 1//�򿪷ŵ�
#define Disable_BatDisc 0//�رշŵ�
/*
���ܣ������пɶ���д�����Ĵ������㣬
�ٶ��й���������ֵ�͵�����Чֵ����ֵ������ֵ
*/
extern void InitMeter(void);

/*
	���ܣ���ȡ����ģ�������
	��ڣ�val_addr��Ŀ�������ַ0x1000��0x10FD��
	���ڣ���
	�������ݴ���ȫ�ֱ�����u8PMdatahΪ��8λ��u32PMdatalΪ��32λ��
*/
extern void ReadMeterPara(unsigned int val_addr);
/*
	���ܣ����ü�����·���������
	��ڣ�val_addr�������Ĵ�����ַ:Ŀ�������ַ0x1000��0x10FD��
	���ڣ��ޡ�
	����д��ȫ�ֱ�����u8PMdatahΪ��8λ��u32PMdatalΪ��32λ��
*/
extern void SetMeterCfg(unsigned int val_addr);
 
#define DATAIP	0x10D1			//˲ʱ�й�����
#define DATAIQ 0x10D2			//˲ʱ�޹�����
#define RMSIU 0x10D3			//˲ʱ��ѹ��Чֵ
#define RMSII1	0x10D4			//I1ͨ��˲ʱ������Чֵ
#define RMSII2	0x10D5			//I2ͨ��˲ʱ������Чֵ
#define DATAP	0x10D6			//��ƽ���й�����
#define DATAQ	0x10D7			//��ƽ���޹�����
#define RMSU	0x10D8			//��ƽ����ѹ��Чֵ
#define RMSI1	0x10D9			//I1ͨ����ƽ��������Чֵ
#define RMSI2	0x10DA			//I2ͨ����ƽ��������Чֵ
#define DATAAP1 0x10DB		        //I1ͨ����ƽ�����ڹ���
#define DATAAP2 0x10DC		        //I2ͨ����ƽ�����ڹ���

#define SCP 0x10DD		//�й����ʱȲ�Ĵ���
#define SCQ 0x10DE		//�޹����ʱȲ�Ĵ���
#define SCU 0x10DF		//��ѹ��Чֵ�Ȳ�Ĵ���
#define SCI1 0x10E0		//ͨ��I1������Чֵ�Ȳ�Ĵ���
#define SCI2 0x10E1		//ͨ��I2������Чֵ�Ȳ�Ĵ���

#define PARAPC 0x10E2			//�й����ʶ��β����Ĵ���
#define PARAQC 0x10E3			//�޹����ʶ��β����Ĵ���

#define PPCNT 0x10F0				//�����й�����������
#define NPCNT 0x10F1				//�����й�����������
#define PPCFCNT	0x10F2			//�����й��������������
#define NPCFCNT	0x10F3			//�����й��������������
#define PQCNT 0x10F6				//�����޹�����������
#define NQCNT 0x10F7				//�����޹�����������
#define PQCFCNT	0x10F8			//�����޹��������������
#define NQCFCNT	0x10F9			//�����޹��������������

#define GATEP 0x10F4			//�й�������������ֵ�Ĵ���
#define GATECP 0x10F5			//�й�����Ǳ������ֵ�Ĵ���
#define GATEQ 0x10FA			//�޹�������������ֵ�Ĵ���
#define GATECQ 0x10FB			//�޹�����Ǳ������ֵ�Ĵ���
#define DATACP	0x10FC			//��������ֵ�Ĵ���

#define DATAFREQ 0x10FD 		//Ƶ��ֵ�Ĵ���

#define DATAOM	0x10CE			//Mͨ��ԭʼ����ֵ�Ĵ���
#define DATADM	0x10CF			//Mͨ��ֱ������ֵ�Ĵ���
#define DATAADM 0x10D0		//Mͨ��ֱ����ƽ������ֵ�Ĵ���


/*
	���ܣ�����LDO33������رա�
	��ڣ�Val_LDO33�������͹ر�LDO33����ָ�0----�ر�LDO33,1----����LDO33
	���ڣ��ޡ�
	
	LDO33ֻ���ڵ��������²��ܹص�����������ϵ�״̬LDO33�޷��رգ�һֱ���ڿ���״̬
		
*/

extern unsigned char SetLDO33(unsigned char Val_LDO33);
#define CloseLDO33    0  	//�ر�LDO33
#define OpenLDO33    1	//����LDO33



#endif







