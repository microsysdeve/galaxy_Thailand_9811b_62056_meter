/***************************** Copyright by Vango ***********************************
	�ļ�����SetLCDVolt.c
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
	�������ܣ�����LCD������ѹ
	������ڣ�val_volt: 0x80 -- 3.0v//ֻ��Ե����ѹ
						0 -- 3.3v
						0x10 -- 3.5v
						others -- no effect	
*/

void SetLCDVolt(unsigned char val_volt)
{

		CtrlCry &= ~P3V; 		// ѡ��3.3V
		CtrlLDO &= ~P3V5;
		CtrlCry |= (val_volt&P3V);
		CtrlLDO |= (val_volt&P3V5);
}