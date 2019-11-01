
/***************************** Copyright by Vango ***********************************
	�ļ�����SetADC.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/

#include "ExLigReg.h"
#include "chipdefine.h"
//#include "absacc.h"
//#include "exlib.h"
/*	���ܣ����õ�������ѹͨ����
	��ڣ�
	val_channel��ADC ѡ��ͨ����
			SETADC_IA ----����A ͨ��;
			SETADC_IB ----����B ͨ��;
			SETADC_U ----��ѹͨ��
	val_para��ADC ����ѡ��
			SETADC_IT1 ��ӦIA��IBͨ��1������;
			SETADC_IT4 ��ӦIA��IBͨ��4������;
			SETADC_IT8 ��ӦIA��IBͨ��8������;
			SETADC_IT16 ��ӦIA��IBͨ��16������;
			SETADC_UT1 ��ӦUͨ��1������;
			SETADC_CLOSE �ر���Ӧͨ��
		#define SETADC_IA 		0
		#define SETADC_IB 		1
		#define SETADC_U 		2
		#define SETADC_IT1 		0
		#define SETADC_IT4 		1
		#define SETADC_IT8 		2
		#define SETADC_IT16 	3		
		#define SETADC_UT1 		0
		#define SETADC_CLOSE 		0x80
	���ڣ���
	  ע�⣺��ѹADCֻ��1�����棨�����棩������ADCֻ��1��4��8��16�������档
*/


void SetADC(unsigned char val_channel,unsigned char val_para)
{
//	unsigned char xdata *point;
	unsigned char  tmp;
	val_channel &= 0x03;
	tmp = CtrlADC;

	if(val_para&0x80)
	{
		CtrlADC =tmp&(~(0x01<<val_channel));
		return;
	}
	val_para = val_para&0x0f;
	tmp |=(0x01<< val_channel);

	CtrlADC = tmp;

	XBYTE[0x2858+val_channel] = val_para;
}
