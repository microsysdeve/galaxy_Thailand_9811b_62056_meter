
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

#endif







