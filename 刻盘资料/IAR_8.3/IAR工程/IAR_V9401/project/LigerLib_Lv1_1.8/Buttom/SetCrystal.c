/***************************** Copyright by Vango ***********************************
	�ļ�����SetCrystal.c
	���ͷ�ļ���EXTigReg.h,chipdefine.h

	�� �� �ˣ�huangsufang
	�������ڣ�2010-03-03
	��ǰ�汾��1.0

	�޸ļ�¼ : 
	�� ��        �汾     �޸���              �޸�����

**************************************************************************************/

#include "ExLigReg.h"
#include "chipdefine.h"


/*	���ܣ����þ���ߵ͹��ģ����þ���Ƶ�ʡ�
	��ڣ�
	val_power��
	���񹦺�ѡ��8----����͹��ģ�0----����߹��ģ�
	val_freq��
	����Ƶ��ѡ��0��1��2��3��4��5��6��7����Ƶ�ʵݼ���
	���ڣ���
*/
void SetCrystal(unsigned char val_power, unsigned char val_freq)
{
	CtrlCry &= 0xf0;
	CtrlCry = val_power|val_freq;
}
