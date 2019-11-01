/***************************** Copyright by Vango ***********************************
	�ļ�����SetLDOVolt.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h


	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*
	�������ܣ�����LDO��ѹ

*/
void SetLDOVolt(unsigned char val_volt)
{
	unsigned char tmp;

	tmp = CtrlLDO;
	tmp &= ~0x07;
	tmp |= val_volt;
	CtrlLDO = tmp;	
}
