/***************************** Copyright by Vango ***********************************
	�ļ�����Alt_50_60Hz.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/
#include "ExLigReg.h"
#include "chipdefine.h"
/*���ܣ� 50/60 Hz ѡ��
��ڣ� val_frq��0----ѡ��50Hz��1----ѡ��60Hz
���ڣ���
*/
void Alt_50_60Hz(unsigned char val_frq)
{
	F0 = 0;		
	if(val_frq==0)CtrlPLL &= (~0x20);
	else CtrlPLL |= 0x20;
}