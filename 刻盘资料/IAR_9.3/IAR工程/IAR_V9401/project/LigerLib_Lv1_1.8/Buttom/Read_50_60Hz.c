/***************************** Copyright by Vango ***********************************
	�ļ�����Read_50_60Hz.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h


	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*���ܣ� ��ȡ50/60 Hz ����
��ڣ���
���ڣ� 0----ѡ��50Hz��1----ѡ��60Hz

*/
unsigned char Read_50_60Hz(void)
{
//	unsigned char val_frq;
//	val_frq = ((CtrlCLK&PLLSEL))?1:0;
//	return val_frq;
	if((CtrlPLL&0x20))
		return 1;
	else return 0;
}